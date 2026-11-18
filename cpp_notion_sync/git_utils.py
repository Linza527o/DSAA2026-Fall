"""Identify source files changed by the GitHub push without running project code."""
from __future__ import annotations

import logging
import subprocess
from dataclasses import dataclass
from pathlib import Path

LOGGER = logging.getLogger(__name__)
EXTENSIONS = frozenset({".cpp", ".cc", ".cxx", ".h", ".hpp", ".hxx"})
ZERO_SHA = "0" * 40


@dataclass(frozen=True)
class ChangedFiles:
    updated: list[str]
    removed: list[str]


def git(*args: str) -> bytes:
    return subprocess.check_output(["git", *args], stderr=subprocess.PIPE)


def is_cpp(path: str) -> bool:
    return Path(path).suffix.lower() in EXTENSIONS


def is_valid_file(path: str) -> bool:
    """Only read regular files within the current checkout; never follow symlinks."""
    root = Path.cwd()
    candidate = root / path
    return (
        is_cpp(path)
        and not candidate.is_symlink()
        and candidate.is_file()
        and candidate.resolve().is_relative_to(root.resolve())
    )


def parse_name_status_z(payload: bytes) -> ChangedFiles:
    """Parse `git diff --name-status -z -M`, including renames and copies."""
    parts = payload.decode("utf-8", errors="surrogateescape").split("\x00")
    if parts and parts[-1] == "":
        parts.pop()
    updated: set[str] = set()
    removed: set[str] = set()
    index = 0
    while index < len(parts):
        status = parts[index]
        index += 1
        if not status or index >= len(parts):
            raise ValueError("Incomplete git diff name-status output")
        old_or_path = parts[index]
        index += 1
        if status.startswith(("R", "C")):
            if index >= len(parts):
                raise ValueError("Incomplete git rename/copy output")
            new_path = parts[index]
            index += 1
            if status.startswith("R") and is_cpp(old_or_path):
                removed.add(old_or_path)
            if is_cpp(new_path):
                updated.add(new_path)
        elif status.startswith("D"):
            if is_cpp(old_or_path):
                removed.add(old_or_path)
        elif status.startswith(("A", "M", "T")):
            if is_cpp(old_or_path):
                updated.add(old_or_path)
        else:
            LOGGER.warning("Unrecognized Git change status: %s", status)
    return ChangedFiles(sorted(updated), sorted(removed))


def changed_files(before: str, after: str) -> ChangedFiles:
    """Compute before..after at the final push state (not each intermediate commit)."""
    if not after or after == ZERO_SHA:
        return ChangedFiles([], [])
    if not before or before == ZERO_SHA:
        LOGGER.info("New branch / first push: scan tracked C++ source files")
        paths = git("ls-files", "-z").decode("utf-8", errors="surrogateescape").split("\x00")
        return ChangedFiles(sorted({p for p in paths if p and is_cpp(p)}), [])
    try:
        return parse_name_status_z(git("diff", "--name-status", "-z", "-M", before, after))
    except subprocess.CalledProcessError:
        LOGGER.warning("Previous SHA unavailable (force push/shallow history); scanning tracked files")
        paths = git("ls-files", "-z").decode("utf-8", errors="surrogateescape").split("\x00")
        return ChangedFiles(sorted({p for p in paths if p and is_cpp(p)}), [])


def file_diff(before: str, after: str, path: str, limit: int = 14_000) -> str:
    if not before or before == ZERO_SHA or not after:
        return "(首次推送或无可用比较基准)"
    try:
        result = git("diff", "--no-ext-diff", "--unified=2", before, after, "--", path)
    except subprocess.CalledProcessError:
        return "(无法获取 diff，仅分析最终文件)"
    text = result.decode("utf-8", errors="replace")
    return text[:limit] + ("\n[Diff 已截断]" if len(text) > limit else "")
