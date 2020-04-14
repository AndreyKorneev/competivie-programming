from __future__ import annotations

import re

from typing import List, Optional, Type

from header_file import HeaderFile
from snippet import Snippet
from util import readlines


LOCAL_INCLUDE_RE = re.compile('#include "([\w\/]+.h)"')
BEGIN_TAG = '//~ BEGIN'
REQUIRED_TAG = '//required:'
END_TAG = '//~ END'
ALWAYS_INCLUDE_TAG = 'ALWAYS_INCLUDE'
DEBUG = 0


def dprint(*args, **kwargs) -> None:
    if DEBUG:
        print(*args, **kwargs)


def parse_local_include(line: str) -> Optional[str]:
    try:
        return LOCAL_INCLUDE_RE.match(line).group(1)
    except:
        return None


class SnippetParser(object):
    def __init__(self, root_path: str):
        self.root_path = root_path

    def parse(self) -> None:
        self.processed = []
        self.seen_files = {self.root_path}
        self.snippets = {}
        self.parse_file(self.root_path)

    def parse_includes(self, path: str) -> None:
        for header_file in filter(None, map(parse_local_include, readlines(path))):
            if header_file not in self.seen_files:
                self.seen_files.add(header_file)
                self.parse_file(header_file)

    def parse_snippets(self, path: str) -> Type[HeaderFile]:
        result = HeaderFile(path)
        snippet = None
        group = []
        for line_num, line in enumerate(readlines(path), 1):
            if line.startswith(BEGIN_TAG):
                dprint(f'Process {line}')
                key = line[len(BEGIN_TAG):].strip().strip('`')
                if snippet is not None:
                    raise Exception(f'Unexpected open section '
                                    f'({key}) {path}:{line_num} {line}')
                snippet = Snippet(
                    key, enabled=key.startswith(ALWAYS_INCLUDE_TAG))
            elif line.startswith(END_TAG):
                dprint(f'Process {line}')
                key = line[len(END_TAG):].strip().strip('`')
                if snippet is None or snippet.tag != key:
                    raise Exception(f'Unexpected close section '
                                    f'({key}) {path}:{line_num} {line}')
                if key in self.snippets:
                    raise Exception(f'Duplicated key found '
                                    f'({key}) {path}:{line_num}')
                snippet.body = '\n'.join(group)
                self.snippets[snippet.tag] = snippet
                result.add_snippet(snippet)
                snippet = None
                group = []
            elif line.startswith(REQUIRED_TAG) and snippet is not None:
                for dependency in filter(
                    None,
                    map(str.strip, line[len(REQUIRED_TAG):].split(','))
                ):
                    if dependency not in self.snippets:
                        raise Exception(f'Unknown dependency {dependency} '
                                        f'for snippet {snippet.tag}'
                                        f'({key}) {path}:{line_num}')
                    snippet.add_dependency(self.snippets[dependency])
            elif snippet is not None:
                group.append(line)

        if snippet is not None:
            raise Exception(f'Missed last closing tag {path} ({snippet.tag})')

        return result

    def parse_file(self, path: str) -> None:
        dprint("parse_file", path)
        self.parse_includes(path)
        self.processed.append(self.parse_snippets(path))

    def enable_snippet(self, tag: str) -> None:
        snippet = self.snippets.get(tag)
        if (snippet is not None) and (not snippet.enabled):
            snippet.enabled = True
            for dependency in snippet.dependencies:
                self.enable_snippet(dependency)

    def get_enabled_snippets(self) -> str:
        result = []
        for header in self.processed:
            for snippet in header.snippets:
                if snippet.enabled:
                    result.append(snippet.body)
        return '\n'.join(result + [''])
