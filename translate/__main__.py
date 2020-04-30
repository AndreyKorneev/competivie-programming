#!/usr/local/bin/python3.7
from __future__ import annotations

import itertools
import re
import sys

from typing import List, Optional, Type

from parser import SnippetParser, parse_local_include
from util import readlines


WORD_RE = re.compile('\w+')


def translate(source_path: str, output_path: str) -> None:
    input_lines = [s for s in readlines(source_path)
                   if parse_local_include(s) is None]
    parser = SnippetParser(source_path)
    parser.parse()

    vocab = set(itertools.chain.from_iterable(WORD_RE.findall(line)
                                              for line in input_lines))
    for token in vocab:
        parser.enable_snippet(token)

    with open(output_path, 'w') as output_file:
        output_file.write(parser.get_enabled_snippets())
        output_file.write('\n'.join(input_lines))


if __name__ == '__main__':
    translate(*sys.argv[1:])
