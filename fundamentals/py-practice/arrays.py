#!/usr/bin/env python3

"""Arrays

Coding exercise focused on resizable arrays.
Uses numpy's array type to create java or c like arrays

Usage: $ python3 arrays.py
"""

### Import Statements ###

import numpy

### Functions ###


class Array(object):
    array = None
    length = None
    idx = None

    def __init__(self, size: int = 1):
        """Makes array given size

        Args:
            size (int): Length of array
        """
        self.array = numpy.empty(size, dtype=object)
        self.length = size
        self.idx = 0

    def __str__(self):
        """Prints numpy array object"""
        return str(self.array)

    def resize(self) -> int:
        """Resizes array when new space is needed

        Returns:
            int: New length
        """
        new_length = self.length * 2
        new_array = numpy.empty(new_length, dtype=object)

        for i in range(self.length):
            new_array[i] = self.array[i]

        self.array = new_array
        self.length = new_length

        return self.length

    def append(self, value: object) -> None:
        """Adds object value to next open space on array

        Args:
            value (object): Any data type
        """
        if self.idx == self.length:
            self.resize()

        self.array[self.idx] = value
        self.idx += 1


if __name__ == "__main__":
    array = Array(3)
    print(array)
    array.append(1)
    print(array)
    array.append(2)
    print(array)
    array.append(3)
    print(array)
    array.append(4)
    print(array)
