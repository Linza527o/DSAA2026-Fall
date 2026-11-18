"""Entry point used by GitHub Actions or manually via `python -m cpp_notion_sync`."""
from __future__ import annotations

import argparse
import subprocess
from pathlib import PurePosixPath, PureWindowsPath
import json
import logging
import os
import sys
from pathlib import Path

from .ai_notes import DEFAULT_MODEL, fingerprint, generate_note
from .git_utils import changed_files, file_diff, is_valid_file
from .notion_api import NotionClient, generated_blocks, page_title, strip_marker

LOGGER = logging.getLogger(__name__)


def settings() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Sync changed C++ files to AI Notion notes")
    parser.add_argument("--dry-run", action="store_true", help="Print changed files; do not use OpenAI or Notion")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--all", action="store_true", help="Re-index all currently tracked C++ files")
    group.add_argument("--file", metavar="PATH", help="Sync exactly one tracked C++ file, relative to Git root")
    return parser.parse_args()


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(levelname)s %(message)s")
    args = settings()
    event_path = os.getenv("GITHUB_EVENT_PATH", "")
    if event_path and Path(event_path).exists():
        event = json.loads(Path(event_path).read_text(encoding="utf-8"))
    else:
        event = {}
    before = event.get("before", os.getenv("GITHUB_BEFORE", ""))
    after = event.get("after", os.getenv("GITHUB_SHA", ""))
    repo = os.getenv("GITHUB_REPOSITORY", "")
    if not repo or "/" not in repo or not after:
        raise RuntimeError("Set GITHUB_REPOSITORY=owner/repo and GITHUB_SHA (or use GitHub Actions)")

    # CLion/plugin requests are explicit paths, not local file contents. The file
    # must have been committed/pushed; workflow_dispatch checks out remote HEAD.
    if args.file:
        supplied = args.file.replace("\\", "/")
        p = PurePosixPath(supplied)
        if (not supplied or p.is_absolute() or ".." in p.parts or "." in p.parts
                or PureWindowsPath(supplied).is_absolute() or ":" in supplied):
            raise ValueError("--file requires a safe repository-relative path")
        tracked = subprocess.run(["git", "ls-files", "--error-unmatch", "--", supplied],
                                 capture_output=True, check=False)
        if tracked.returncode != 0:
            raise ValueError(f"Not a tracked file in the current checkout: {supplied}")
        if not is_valid_file(supplied):
            raise ValueError(f"Not a regular tracked C++ source: {supplied}")
        changes = type("Selected", (), {"updated": [supplied], "removed": []})()
    else:
        # An explicit --all flag uses the same tracked-file scan as a first push.
        from .git_utils import ZERO_SHA
        changes = changed_files(ZERO_SHA if args.all else before, after)
    updated = [name for name in changes.updated if is_valid_file(name)]
    skipped = sorted(set(changes.updated) - set(updated))
    for name in skipped:
        LOGGER.warning("Skipping missing/non-regular/symlink source: %s", name)
    LOGGER.info("Updated C++ files (%s): %s", len(updated), updated)
    LOGGER.info("Deleted/renamed-away C++ files (preserved in Notion): %s", changes.removed)
    if args.dry_run:
        return 0
    if not updated:
        return 0
    max_files = int(os.getenv("MAX_FILES_PER_RUN", "100"))
    if len(updated) > max_files:
        raise RuntimeError(f"{len(updated)} changed files exceeds MAX_FILES_PER_RUN={max_files}")
    model = os.getenv("DEEPSEEK_MODEL") or DEFAULT_MODEL
    max_bytes = int(os.getenv("MAX_FILE_BYTES", "120000"))
    max_ai_chars = int(os.getenv("MAX_AI_CHARS", "12000"))
    max_diff_chars = int(os.getenv("MAX_DIFF_CHARS", "4000"))
    detail = (os.getenv("NOTE_DETAIL") or "lite").strip().lower()
    if detail not in ("lite", "full"):
        raise ValueError("NOTE_DETAIL must be 'lite' or 'full'")
    if max_ai_chars < 1000:
        raise ValueError("MAX_AI_CHARS must be >= 1000")
    if max_diff_chars < 0:
        raise ValueError("MAX_DIFF_CHARS must be >= 0")
    for var in ("DEEPSEEK_API_KEY", "NOTION_TOKEN", "NOTION_PARENT_PAGE_ID"):
        if not os.getenv(var):
            raise RuntimeError(f"Missing required secret: {var}")

    notion = NotionClient(os.environ["NOTION_TOKEN"], os.environ["NOTION_PARENT_PAGE_ID"])
    index = notion.read_index()
    synced = 0
    failures = []
    for path in updated:
        try:
            raw = Path(path).read_bytes()
            if len(raw) > max_bytes:
                raise ValueError(f"File {len(raw)} bytes exceeds MAX_FILE_BYTES={max_bytes}; not uploaded")
            if b"\x00" in raw:
                raise ValueError("File contains NUL bytes; not a regular text source")
            code = raw.decode("utf-8", errors="replace")
            version = fingerprint(code, model, detail)
            page_id = notion.find_page(repo, path)
            if page_id:
                # IMPORTANT: check before API call to avoid paying again on reruns.
                previous = notion.managed_toggles(page_id)
                if any(t["title"].endswith(version) and notion.is_complete(t["id"], version)
                       for t in previous):
                    clean = strip_marker(notion.title_of(page_id))
                    if notion.set_title(page_id, clean):
                        LOGGER.info("Retitled %s -> %s", path, clean)
                    LOGGER.info("Unchanged source: %s", path)
                    continue
            LOGGER.info("Analyzing %s via %s", path, model)
            note = generate_note(path=path, repo=repo, code=code,
                                 diff=file_diff(before, after, path, limit=max_diff_chars),
                                 commit=after, model=model, max_ai_chars=max_ai_chars,
                                 detail=detail)
            blocks = generated_blocks(report=note.data, code=code, path=path,
                                      repo=repo, commit=after, model=model,
                                      truncated=note.truncated)
            title = page_title(repo, path, note.data.get("topic", ""))
            if page_id is None:
                page_id = notion.create_page(title)
            elif notion.set_title(page_id, title):
                LOGGER.info("Retitled %s -> %s", path, title)
            notion.write_generated(page_id, version, blocks)
            notion.record_index(index, page_id, note.data.get("tags", []))
            synced += 1
            LOGGER.info("Synced %s to https://www.notion.so/%s", path, page_id.replace("-", ""))
        except Exception as exc:
            LOGGER.error("Failed to sync %s: %s", path, exc)
            failures.append(path)
    if synced or notion.index_stale:
        notion.write_index(index)
        LOGGER.info("Topic index updated (%s tags, %s pages)",
                    sum(1 for pages in index.values() if pages),
                    len({page for pages in index.values() for page in pages}))
    if failures:
        LOGGER.error("Failed files: %s", ", ".join(failures))
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
