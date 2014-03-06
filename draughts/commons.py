#!/usr/bin/env python

#regex
import re

"""Define Color enum and Type enum"""

Ether = "Ether"
Black = "Black"
White = "White"

Human = "Human"
CPU = "CPU"

# Stone State enum
Pawn = "Pawn"
Lady = "Lady"

# Cell of Board State
Empty = "Empty"
Fill = "Fill"

class Hit:
    """Class for separate entry from user to internal logic"""
    Bad = "Bad"
    Clear = "Clear"
    Quit = "Quit"
    Pattern = re.compile(r'^([a-jA-J]\d){2}$')

    def isFormat(entry):
        if Hit.Pattern.match(entry) != None:
            return True
        else:
            return False
    def explode(entry):
        """"""
        if Hit.Pattern.match(entry) != None:
            return (entry[0], entry[1], entry[2], entry[3])
        else:
            raise ("Hit.explode error: Hit Pattern match error !")
