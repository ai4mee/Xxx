#!/usr/bin/env python3
"""Towers of Hanoi solver for a variable number of disks."""

import sys


def hanoi(n: int, source: str, target: str, auxiliary: str) -> None:
    """Recursively solve Towers of Hanoi.

    Args:
        n: Number of disks to move.
        source: Name of the source peg.
        target: Name of the target peg.
        auxiliary: Name of the auxiliary peg.
    """
    if n == 1:
        print(f"Move disk 1 from {source} to {target}")
        return
    hanoi(n - 1, source, auxiliary, target)
    print(f"Move disk {n} from {source} to {target}")
    hanoi(n - 1, auxiliary, target, source)


def solve(n: int) -> None:
    print(f"Solving Towers of Hanoi with {n} disk(s):\n")
    hanoi(n, "A", "C", "B")
    print(f"\nTotal moves: {2**n - 1}")


def main() -> None:
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <number_of_disks>")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("Error: Number of disks must be an integer.")
        sys.exit(1)

    if n < 1:
        print("Error: Number of disks must be at least 1.")
        sys.exit(1)

    solve(n)


if __name__ == "__main__":
    main()
