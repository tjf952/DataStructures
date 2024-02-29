#!/usr/bin/env python3

"""Passing Yearbooks

There are n students, numbered from 1 to n, each with their own yearbook. 
They would like to pass their yearbooks around and get them signed by other 
students.

You're given a list of n integers arr[1..n], which is guaranteed to be a 
permutation of 1..n (in other words, it includes the integers from 1 to n exactly 
once each, in some order). The meaning of this list is described below.
Initially, each student is holding their own yearbook. The students will then 
repeat the following two steps each minute: Each student i will first sign the 
yearbook that they're currently holding (which may either belong to themselves 
or to another student), and then they'll pass it to student arr[i-1]. It's 
possible that arr[i-1] = i for any given i, in which case student i will pass 
their yearbook back to themselves. Once a student has received their own yearbook 
back, they will hold on to it and no longer participate in the passing process.
It's guaranteed that, for any possible valid input, each student will eventually 
receive their own yearbook back and will never end up holding more than one 
yearbook at a time.

You must compute a list of n integers output, whose element at i-1 is equal to 
the number of signatures that will be present in student i's yearbook once they 
receive it back.

Usage: $ python3 passing_yearbooks.py

Example:
arr =   [1, 2, 4, 3]
                     < Everyone signs their own yearbooks and passes
                     < Pass works by student i passing to arr[i-1]
         1  2  3  4
                     < Student 1 and 2 have their yearbooks, but 3 and 4 pass
         -  -  4  3
                     < Now everyone has their yearbook
count = [1, 1, 2, 2]
"""

### Import Statements ###

import math


### Functions ###


def find_signature_counts(arr: list) -> list:
    """Finds how many times each yearbook is signed

    Args:
        arr (list): List of size n where arr[i] is in range [1, n]

    Returns:
        list: List of n integers that represent count of Student i+1
    """
    prev_arr = list(range(1, len(arr) + 1))
    counter_arr = [1] * len(arr)

    while prev_arr != arr:
        next_arr = [0] * len(arr)
        for i in range(len(arr)):
            if prev_arr[i] != arr[i]:
                counter_arr[i] += 1
                next_arr[arr[i] - 1] = prev_arr[i]
            else:
                next_arr[i] = prev_arr[i]
        prev_arr = next_arr
    return counter_arr


### GIVEN FUNCTIONS ###


def printInteger(n: int) -> None:
    """Given Function"""
    print("[", n, "]", sep="", end="")


def printIntegerList(array: list) -> None:
    """Given Function"""
    size = len(array)
    print("[", end="")
    for i in range(size):
        if i != 0:
            print(", ", end="")
        print(array[i], end="")
    print("]", end="")


test_case_number = 1


def check(expected, output):
    """Given Function"""
    global test_case_number
    expected_size = len(expected)
    output_size = len(output)
    result = True
    if expected_size != output_size:
        result = False
    for i in range(min(expected_size, output_size)):
        result &= output[i] == expected[i]
    rightTick = "\u2713"
    wrongTick = "\u2717"
    if result:
        print(rightTick, "Test #", test_case_number, sep="")
    else:
        print(wrongTick, "Test #", test_case_number, ": Expected ", sep="", end="")
        printIntegerList(expected)
        print(" Your output: ", end="")
        printIntegerList(output)
        print()
    test_case_number += 1


### MAIN FUNCTION ###


if __name__ == "__main__":
    arr = [2, 1]
    expected = [2, 2]
    output = find_signature_counts(arr)
    check(expected, output)

    arr = [1, 2]
    expected = [1, 1]
    output = find_signature_counts(arr)
    check(expected, output)

    arr = [4, 1, 2, 3]
    expected = [4, 4, 4, 4]
    output = find_signature_counts(arr)
    check(expected, output)

    arr = [1, 2, 4, 3]
    expected = [1, 1, 2, 2]
    output = find_signature_counts(arr)
    check(expected, output)

    arr = [2, 1, 4, 3]
    expected = [2, 2, 2, 2]
    output = find_signature_counts(arr)
    check(expected, output)
