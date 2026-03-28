#!/usr/bin/env python3
"""Towers of Hanoi solver with ASCII visualization."""

import sys


def draw(pegs: dict, n: int, step: int, move: str) -> None:
    width = 2 * n + 1
    print(f"\nSchritt {step}: {move}")
    print()
    for row in range(n, 0, -1):
        line = ""
        for peg in ("A", "B", "C"):
            stack = pegs[peg]
            if len(stack) >= row:
                disk = stack[row - 1]
                disk_str = ("=" * disk).center(width)
            else:
                disk_str = "|".center(width)
            line += disk_str + "  "
        print(line)
    print("  ".join(name.center(width) for name in ("A", "B", "C")))
    print("-" * (3 * width + 4))


def hanoi(n: int, source: str, target: str, auxiliary: str,
          pegs: dict, total: int, step: list) -> None:
    if n == 1:
        step[0] += 1
        disk = pegs[source].pop()
        pegs[target].append(disk)
        draw(pegs, total, step[0], f"Scheibe {disk}: {source} -> {target}")
        return
    hanoi(n - 1, source, auxiliary, target, pegs, total, step)
    step[0] += 1
    disk = pegs[source].pop()
    pegs[target].append(disk)
    draw(pegs, total, step[0], f"Scheibe {disk}: {source} -> {target}")
    hanoi(n - 1, auxiliary, target, source, pegs, total, step)


def solve(n: int) -> None:
    pegs = {"A": list(range(n, 0, -1)), "B": [], "C": []}
    step = [0]
    print(f"Tuerme von Hanoi mit {n} Scheibe(n)")
    draw(pegs, n, 0, "Ausgangszustand")
    hanoi(n, "A", "C", "B", pegs, n, step)
    print(f"\nFertig! Benoetigt: {step[0]} Zuege (Minimum: {2**n - 1})")


def main() -> None:
    if len(sys.argv) != 2:
        print(f"Verwendung: {sys.argv[0]} <Anzahl_Scheiben>")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("Fehler: Anzahl der Scheiben muss eine ganze Zahl sein.")
        sys.exit(1)

    if n < 1:
        print("Fehler: Mindestens 1 Scheibe erforderlich.")
        sys.exit(1)

    solve(n)


if __name__ == "__main__":
    main()
