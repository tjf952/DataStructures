#!/usr/bin/env python3

"""Problem Solving - Optimizing with Space and Time
- Hash tables
- Pre-computation
- Tries
"""

import random
import time

### Functions ###


def timer(func, *args) -> int:
    st = time.time()
    ans = func(*args)
    et = time.time()
    print(f'Answer for {func.__name__}: {ans}')
    print(f'Execution time for {func}: {(et-st)*1000} ms')

def permutations(s, start=0):
    if start == len(s) - 1:
        return ["".join(s)]
    else:
        result = []
        for i in range(start, len(s)):
            s[start], s[i] = s[i], s[start]
            result.extend(permutations(s, start + 1))
            s[start], s[i] = s[i], s[start]
        return result

def perms_in_str(s, b):
    ans = []
    perms = set(permutations(list(s)))
    for idx in range(len(b)-len(s)):
        substr = b[idx:idx+len(s)]
        if substr in perms:
            ans.append(substr)
    return ans

seq = [1,1,2,3,5]
def fib(n):
    while len(seq) <= n:
        seq.append(seq[-1]+seq[-2])
    return seq[n]

def fib_rec(n):
    if n == 0 or n == 1:
        return 1
    return fib_rec(n-1) + fib_rec(n-2)

def fib_itr(n):
    x, y, c = 1, 1, 1
    while c < n:
        x, y = y, x+y
        c += 1
    return y

if __name__ == "__main__":
    s = "abc"
    b = "abcacbabc"
    timer(perms_in_str, s, b)
    print("[+] Fibonacci with Static Memory")
    timer(fib, 20)
    timer(fib, 10)
    print("[+] Fibonacci with Recursion")
    timer(fib_rec, 20)
    timer(fib_rec, 10)
    print("[+] Fibonacci with Loop")
    timer(fib_itr, 20)
    timer(fib_itr, 10)

"""
s = "abc" > abc, acb, bac, bca, cab, cba
b = "abcacbabc"
perms = abc, bca, acb, cba, abc
set = abc, acb, bca, cba
"""