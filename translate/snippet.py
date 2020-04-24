from __future__ import annotations

from typing import List, Optional, Type


class Snippet(object):
    def __init__(
        self,
        tag: str,
        body: str = None,
        dependencies: Optional[List[Type[Snippet]]] = None,
        enabled: bool = False
    ):
        self.tag = tag
        self.body = body
        self.dependencies = [] if dependencies is None else dependencies
        self.enabled = enabled

    def add_dependency(self, snippet: Type[Snippet]) -> None:
        self.dependencies.append(snippet)

    def __repr__(self):
        return self.tag

    def __hash__(self):
        return hash(self.tag)

    def __eq__(self, other):
        return isinstance(other, self.__class__) and self.tag == other.tag
