from __future__ import annotations

from typing import List, Optional, Type

from snippet import Snippet


class HeaderFile(object):
    def __init__(self, path: str, snippets: Optional[List[Type[Snippet]]] = None):
        self.path = path
        self.snippets = [] if snippets is None else snippets

    def add_snippet(self, snippet: Type[Snippet]) -> None:
        self.snippets.append(snippet)

    def __repr__(self):
        return self.path

    def __hash__(self):
        return hash(self.path)

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.path == other.path
