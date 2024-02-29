#!/usr/bin/env python3

"""Problem Solving - Optimizing with BUD
B - Bottleneck
U - Unnecssary work
D - Duplicate Work
"""

import time

ht = {}

### Functions ###


def timer(func, n) -> int:
    st = time.time()
    ans = func(n)
    et = time.time()
    print(f"Answer for {func.__name__}: {ans}")
    print(f"Execution time for {func}: {(et-st)*1000} ms")


def find_solutions(n: int) -> int:
    cnt = 0
    for a in range(1, n):
        for b in range(1, n):
            for c in range(1, n):
                for d in range(1, n):
                    if a**2 + b**2 == c**2 + d**2:
                        cnt += 1
    return cnt


def find_solutions_opt(n: int) -> int:
    cnt = 0
    for a in range(1, n):
        for b in range(1, n):
            for c in range(1, n):
                d = (a**2 + b**2 - c**2) ** (1 / 2)
                if d in range(1, n):
                    cnt += 1
    return cnt


def square(x: int) -> int:
    if x in ht:
        return ht[x]
    ht[x] = x**2
    return ht[x]


def find_solutions_ht(n: int) -> int:
    cnt = 0
    for a in range(1, n):
        for b in range(1, n):
            for c in range(1, n):
                d = (square(a) + square(b) - square(c)) ** (1 / 2)
                if d in range(1, n):
                    cnt += 1
    return cnt


if __name__ == "__main__":
    n = 100
    for x in range(n):
        square(x)
    print(ht)
    timer(find_solutions, n)
    timer(find_solutions_opt, n)
    timer(find_solutions_ht, n)
