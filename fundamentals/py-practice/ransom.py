#!/usr/bin/env python3

"""Problem Solving - Optimizing with Space and Time
- Hash tables
- Pre-computation
- Tries
"""

import random
import time

### Functions ###


def ransom_note(n: str, m: str):
    dic = {}
    for c in m:
        if c.isalnum():
            if c in dic:
                dic[c] += 1
            else:
                dic[c] = 1
    for c in n:
        if c.isalnum():
            if c in dic and dic[c] > 0:
                dic[c] -= 1
            else:
                return False
    return True


if __name__ == "__main__":
    n = "S3cR3t C0de is: D3adB3ef"
    m = """
        Welcome to Time Magainze ISSUE 330
        Today's story is about Reynold Daniels.
        Daniels is the owner of the Secret Camel Business.
        He has over 3000 camels hidden far under his 3 houses.
    """
    print(ransom_note(n, m))
    n = "1234567890"
    print(ransom_note(n, m))
