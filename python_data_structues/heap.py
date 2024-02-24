#!/usr/bin/env python3

"""_title_

_description_

Usage: $ python3 heap.py <_args_>

Arguments:
    -_param_ <type>: _description_
"""

### Import Statements ###

import os

print(f"Hello {os.getlogin()}")


###Classes ###


class Class1():
    """_title_

    _description_
    """

    def __init__(self, _param_: type):
        """_description_

        Args:
            _param_ (type): _description_
        """
        self.attr = _param_

    def example_method(self, _param_: type) -> type:
        """_description_

        Args:
            _param_ (type): _description_

        Returns:
            type: _description_
        """
        self.attr = _param_
        return self.attr

    def __special__(self):
        """_description_

        Returns:
            type: _description_
        """
        return self.attr


if __name__ == "__main__":
    print("This is a template python file.")
