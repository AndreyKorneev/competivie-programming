def readlines(path: str) -> str:
    with open(path, 'r') as f:
        return [s.rstrip() for s in f.readlines()]
