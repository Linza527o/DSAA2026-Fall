"""Minimal Notion REST client. Only a dedicated generated toggle is replaced."""
from __future__ import annotations

import hashlib
import logging
import random
import re
import time
from collections.abc import Iterator
from typing import Any
from urllib.parse import quote

import requests

LOGGER = logging.getLogger(__name__)
API_URL = "https://api.notion.com/v1"
NOTION_VERSION = "2026-03-11"
MANAGED_PREFIX = "AI C++ Notes | "
COMPLETION_PREFIX = "SYNC_COMPLETE:"
INDEX_TITLE = "📚 主题索引（按标签自动整理）"

# Decoration only: the stored tag is always the plain word, so indexes written
# before/after this table stay compatible.
TAG_EMOJI = {
    "数组": "🧮", "链表": "🔗", "栈": "🥞", "队列": "🚏", "字符串": "🧵",
    "哈希表": "🗂️", "树": "🌳", "二叉搜索树": "🌲", "堆": "⛰️", "图": "🕸️",
    "并查集": "🤝", "排序": "🔀", "二分查找": "🎯", "递归": "🌀", "分治": "✂️",
    "贪心": "🍬", "动态规划": "🧠", "回溯": "↩️", "搜索": "🔍", "数学": "📐",
    "模拟": "🎭", "其他": "📦",
}
DEFAULT_TAG_EMOJI = "🏷️"


def tag_label(tag: str) -> str:
    """Display form used for the heading_2 in the topic index."""
    return f"{TAG_EMOJI.get(tag, DEFAULT_TAG_EMOJI)} {tag}"


def tag_of(label: str) -> str:
    """Undo tag_label(); a leading symbol/emoji token is dropped."""
    label = label.strip()
    head, _, rest = label.partition(" ")
    if rest and not re.search(r"[\w\u4e00-\u9fff]", head):
        return rest.strip()
    return label
# Titles written before v4 of this tool ended with a hidden identity marker.
LEGACY_MARKER_RE = re.compile(r"\s*\[cpp-sync:[0-9a-f]{16}\]\s*$")
TEXT_CHUNK = 1800
BLOCK_BATCH = 40
MAX_BULLETS = 6


def chunks(value: str, chunk_size: int = TEXT_CHUNK) -> Iterator[str]:
    if not value:
        yield " "
    else:
        for index in range(0, len(value), chunk_size):
            yield value[index:index + chunk_size]


def rich_text(value: str, max_chars: int = 15_000) -> list[dict[str, Any]]:
    """Notion text.content max length is 2,000 characters."""
    value = value[:max_chars]
    return [{"type": "text", "text": {"content": segment}}
            for segment in chunks(value)]


def block(kind: str, text: str) -> dict[str, Any]:
    return {"object": "block", "type": kind,
            kind: {"rich_text": rich_text(text)}}


def page_mention(page_id: str) -> dict[str, Any]:
    """Inline @page link; Notion renders the live page title."""
    return {"type": "mention", "mention": {"type": "page", "page": {"id": page_id}}}


def page_link_bullet(page_id: str) -> dict[str, Any]:
    return {"object": "block", "type": "bulleted_list_item",
            "bulleted_list_item": {"rich_text": [page_mention(page_id)]}}


def plain_text(rich: list[dict[str, Any]]) -> str:
    return "".join(item.get("plain_text", item.get("text", {}).get("content", ""))
                   for item in rich)


def mention_page_id(rich: list[dict[str, Any]]) -> str | None:
    if len(rich) == 1 and rich[0].get("type") == "mention":
        page = (rich[0].get("mention") or {}).get("page") or {}
        return page.get("id")
    return None


def link_paragraph(label: str, url: str) -> dict[str, Any]:
    return {"object": "block", "type": "paragraph", "paragraph": {"rich_text": [
        {"type": "text", "text": {"content": label, "link": {"url": url}}}
    ]}}


def bullet_list(items: list[str]) -> list[dict[str, Any]]:
    if not items:
        return [block("paragraph", "（此文件不涉及或无法从代码确认）")]
    return [block("bulleted_list_item", item) for item in items[:MAX_BULLETS]]


def generated_blocks(*, report: dict[str, Any], code: str, path: str,
                     repo: str, commit: str, model: str, truncated: bool) -> list[dict[str, Any]]:
    """Convert structured AI notes + complete source to native Notion blocks."""
    repository_url = f"https://github.com/{repo}"
    file_url = f"{repository_url}/blob/{commit}/{quote(path, safe='/')}"
    commit_url = f"{repository_url}/commit/{commit}"
    topic = " ".join(str(report.get("topic", "")).split())[:40]
    tags = "、".join(str(t) for t in (report.get("tags") or []))
    meta = f"文件：{path}  |  仓库：{repo}  |  模型：{model}  |  提交：{commit[:12]}"
    if topic:
        meta = f"主题：{topic}  |  " + meta
    if tags:
        meta += f"  |  标签：{tags}"
    content: list[dict[str, Any]] = [
        block("paragraph", meta),
        link_paragraph("在 GitHub 查看此版本的源代码", file_url),
        link_paragraph("查看对应 Git Commit", commit_url),
        block("heading_2", "一句话概述"),
        block("paragraph", report["summary"]),
        block("heading_2", "问题与适用场景"),
        block("paragraph", report["problem"]),
        block("heading_2", "算法思路 / 处理流程"),
        *bullet_list(report["approach"]),
        block("heading_2", "数据结构与关键函数"),
        *bullet_list(report["data_structures"]),
        *bullet_list(report["key_functions"]),
        block("heading_2", "复杂度分析"),
        block("paragraph", f"时间复杂度：{report['time_complexity']}\n空间复杂度：{report['space_complexity']}\n原因与条件：{report['complexity_reason']}"),
        block("heading_2", "潜在问题与边界条件（未经执行验证）"),
        *bullet_list(report["pitfalls"]),
    ]
    if truncated:
        content.append(block("paragraph", "注意：AI 仅分析了源文件前一部分；下方保存了本次提交的完整源码。"))
    # Sections absent from the (lite) schema are simply omitted.
    for heading, key in (("正确性推理", "correctness"),
                         ("本次提交的改动", "changes"),
                         ("改进建议", "improvements"),
                         ("例子 / 复习提示", "example")):
        value = report.get(key)
        if value:
            content.append(block("heading_2", heading))
            content.extend(bullet_list(value) if isinstance(value, list) else [block("paragraph", value)])
    content.extend([block("heading_2", "完整 C++ 源代码（Push 时的版本）")])
    code_parts = list(chunks(code))
    for i, part in enumerate(code_parts, 1):
        content.append({
            "object": "block", "type": "code",
            "code": {
                "language": "c++",
                "rich_text": rich_text(part),
                "caption": rich_text(f"{path} · 第 {i}/{len(code_parts)} 段"),
            },
        })
    return content


def file_key(repo: str, path: str) -> str:
    return hashlib.sha256(f"{repo}\0{path}".encode("utf-8")).hexdigest()[:16]


def page_marker(repo: str, path: str) -> str:
    """Legacy identity marker; only used to find pages created before v4 titles."""
    return f"[cpp-sync:{file_key(repo, path)}]"


def page_title(repo: str, path: str, topic: str = "") -> str:
    """Topic first so the Notion page list reads like a study index.

    No hidden marker: the title ends with the repository-relative path, which is
    unique inside one parent page and survives AI re-wording of the topic.
    """
    topic = " ".join((topic or "").split())[:40]
    return f"{topic} · {path}" if topic else path


def title_matches_path(title: str, path: str) -> bool:
    return title == path or title.endswith("· " + path)


def strip_marker(title: str) -> str:
    return LEGACY_MARKER_RE.sub("", title).strip()


class NotionClient:
    def __init__(self, token: str, parent_id: str):
        self.parent_id = parent_id.replace("-", "")
        self.session = requests.Session()
        self.session.headers.update({
            "Authorization": f"Bearer {token}",
            "Notion-Version": NOTION_VERSION,
            "Content-Type": "application/json",
        })
        self._pages: dict[str, str] | None = None

    def _request(self, method: str, endpoint: str, **kwargs: Any) -> dict[str, Any]:
        # Only retry 429/529, where Notion explicitly asks clients to wait.
        # Do not automatically replay writes after ambiguous 5xx/network failures.
        for attempt in range(5):
            response = self.session.request(
                method, f"{API_URL}{endpoint}", timeout=35, **kwargs
            )
            if response.status_code in (429, 529) and attempt < 4:
                if response.status_code == 429 and response.json().get("additional_data", {}).get("rate_limit_reason") == "public_api_request_blocked":
                    break
                retry = response.headers.get("Retry-After", "1")
                try:
                    seconds = float(retry)
                except ValueError:
                    seconds = 1.0
                time.sleep(max(seconds, (2 ** attempt) + random.random()))
                continue
            break
        if not response.ok:
            # Avoid accidentally printing bearer tokens or sensitive source data.
            raise RuntimeError(f"Notion {method} {endpoint}: HTTP {response.status_code} — {response.text[:350]}")
        return response.json()

    def list_children(self, block_id: str) -> list[dict[str, Any]]:
        output: list[dict[str, Any]] = []
        cursor = None
        while True:
            params: dict[str, Any] = {"page_size": 100}
            if cursor:
                params["start_cursor"] = cursor
            data = self._request("GET", f"/blocks/{block_id}/children", params=params)
            output.extend(data["results"])
            if not data.get("has_more"):
                return output
            cursor = data.get("next_cursor")
            if not cursor:
                raise RuntimeError("Notion pagination returned has_more without next_cursor")

    def _index_parent_pages(self) -> list[dict[str, str]]:
        """Child pages of the sync parent, title plus id.

        Identity is the "· <repository path>" suffix of the title, so re-worded
        AI topics do not create duplicate pages. Pages written by older versions
        still carry a [cpp-sync:...] marker and are matched through it once.
        """
        if self._pages is None:
            self._pages = [
                {"id": child["id"], "title": child["child_page"]["title"]}
                for child in self.list_children(self.parent_id)
                if child.get("type") == "child_page"
            ]
        return self._pages

    def find_page(self, repo: str, path: str) -> str | None:
        pages = self._index_parent_pages()
        for entry in pages:
            if title_matches_path(entry["title"], path):
                return entry["id"]
        marker = page_marker(repo, path)
        for entry in pages:
            if marker in entry["title"]:
                return entry["id"]
        return None

    def _remember(self, title: str, page_id: str) -> None:
        for entry in self._index_parent_pages():
            if entry["id"] == page_id:
                entry["title"] = title
                return
        self._index_parent_pages().append({"id": page_id, "title": title})

    def create_page(self, title: str) -> str:
        data = self._request("POST", "/pages", json={
            "parent": {"type": "page_id", "page_id": self.parent_id},
            "properties": {"title": {"type": "title", "title": rich_text(title)}},
        })
        self._remember(title, data["id"])
        return data["id"]

    def title_of(self, page_id: str) -> str:
        for entry in self._index_parent_pages():
            if entry["id"] == page_id:
                return entry["title"]
        return ""

    def set_title(self, page_id: str, title: str) -> bool:
        """Rename only when the title actually changed."""
        for entry in self._index_parent_pages():
            if entry["id"] == page_id and entry["title"] == title:
                return False
        self._request("PATCH", f"/pages/{page_id}", json={
            "properties": {"title": {"type": "title", "title": rich_text(title)}}
        })
        self._remember(title, page_id)
        return True

    # ---- topic index at the bottom of the parent page -----------------
    @staticmethod
    def _index_block_kind(child: dict[str, Any], tags: set[str], page_ids: set[str]) -> bool:
        """Only touch blocks this tool is known to have written."""
        kind = child.get("type")
        if kind == "heading_1":
            return plain_text(child["heading_1"]["rich_text"]) == INDEX_TITLE
        if kind == "heading_2":
            return tag_of(plain_text(child["heading_2"]["rich_text"])) in tags
        if kind == "bulleted_list_item":
            return mention_page_id(child["bulleted_list_item"]["rich_text"]) in page_ids
        return False

    def read_index(self) -> dict[str, list[str]]:
        """Rebuild tag -> page ids from the index already on the parent page."""
        index: dict[str, list[str]] = {}
        tag: str | None = None
        for child in self.list_children(self.parent_id):
            kind = child.get("type")
            if kind == "heading_1" and plain_text(child["heading_1"]["rich_text"]) == INDEX_TITLE:
                tag = None
            elif kind == "heading_2":
                tag = tag_of(plain_text(child["heading_2"]["rich_text"]))
                index.setdefault(tag, [])
            elif kind == "bulleted_list_item" and tag:
                page_id = mention_page_id(child["bulleted_list_item"]["rich_text"])
                if page_id and page_id not in index[tag]:
                    index[tag].append(page_id)
        return index

    @staticmethod
    def record_index(index: dict[str, list[str]], page_id: str, tags: list[str]) -> None:
        for pages in index.values():
            if page_id in pages:
                pages.remove(page_id)
        for tag in tags:
            bucket = index.setdefault(tag, [])
            if page_id not in bucket:
                bucket.append(page_id)

    def write_index(self, index: dict[str, list[str]]) -> None:
        """Recreate the tag index; anything else on the page is left alone."""
        tags = set(index)
        page_ids = {page for pages in index.values() for page in pages}
        for child in self.list_children(self.parent_id):
            if self._index_block_kind(child, tags, page_ids):
                self._request("DELETE", f"/blocks/{child['id']}")
        body: list[dict[str, Any]] = [{"object": "block", "type": "heading_1",
                                       "heading_1": {"rich_text": rich_text(INDEX_TITLE)}}]
        for tag in sorted(tag for tag, pages in index.items() if pages):
            body.append({"object": "block", "type": "heading_2",
                         "heading_2": {"rich_text": rich_text(tag_label(tag))}})
            body.extend(page_link_bullet(page_id) for page_id in index[tag])
        if len(body) == 1:
            return
        for offset in range(0, len(body), BLOCK_BATCH):
            self._request("PATCH", f"/blocks/{self.parent_id}/children", json={
                "children": body[offset:offset + BLOCK_BATCH]
            })

    def managed_toggles(self, page_id: str) -> list[dict[str, Any]]:
        output = []
        for child in self.list_children(page_id):
            if child.get("type") != "toggle":
                continue
            title = "".join(x.get("plain_text", x.get("text", {}).get("content", ""))
                            for x in child["toggle"].get("rich_text", []))
            if title.startswith(MANAGED_PREFIX):
                output.append({"id": child["id"], "title": title})
        return output

    def is_complete(self, toggle_id: str, fingerprint: str) -> bool:
        sentinel = COMPLETION_PREFIX + fingerprint
        children = self.list_children(toggle_id)
        return any(
            child.get("type") == "paragraph" and any(
                item.get("plain_text", item.get("text", {}).get("content", "")) == sentinel
                for item in child["paragraph"].get("rich_text", [])
            ) for child in children
        )

    def write_generated(self, page_id: str, fingerprint: str,
                        body: list[dict[str, Any]]) -> bool:
        """Append new generated toggle fully, then trash old generated toggles."""
        old = self.managed_toggles(page_id)
        for item in old:
            if item["title"] == MANAGED_PREFIX + fingerprint and self.is_complete(item["id"], fingerprint):
                LOGGER.info("Already synced this version: %s", fingerprint)
                # Remove partial/old AI toggles left by interrupted runs.
                for previous in old:
                    if previous["id"] != item["id"]:
                        self._request("DELETE", f"/blocks/{previous['id']}")
                return False

        created = self._request("PATCH", f"/blocks/{page_id}/children", json={
            "children": [{
                "object": "block", "type": "toggle",
                "toggle": {"rich_text": rich_text(MANAGED_PREFIX + fingerprint)},
            }],
            "position": {"type": "start"},
        })
        new_toggle_id = created["results"][0]["id"]
        # If any append fails, keep previous complete notes and leave a partial
        # toggle for diagnosis. A subsequent run replaces it safely.
        for offset in range(0, len(body), BLOCK_BATCH):
            self._request("PATCH", f"/blocks/{new_toggle_id}/children", json={
                "children": body[offset:offset + BLOCK_BATCH]
            })
        self._request("PATCH", f"/blocks/{new_toggle_id}/children", json={
            "children": [block("paragraph", COMPLETION_PREFIX + fingerprint)]
        })
        for item in old:
            self._request("DELETE", f"/blocks/{item['id']}")
        return True
