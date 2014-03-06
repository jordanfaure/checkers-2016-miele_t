#!/usr/bin/env python

import commons

BOARD_LINES = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

BOARD_COLUMNS = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]

def from_board_to_index(line, column):
    line_index = 0
    column_index = 0
    for it in BOARD_LINES:
        if it != line:
            line_index += 1
        else:
            break
    for it in BOARD_COLUMNS:
        if it != column:
            column_index += 1
        else:
            break
    return (line_index, column_index)

class Stone:
    def __init__(self, color=commons.Ether, state=commons.Pawn, is_exist=False):
        self.color = color
        self.state = state
        self.is_exist = is_exist
    def __str__(self):
        if self.color == commons.Black:
            if self.state == commons.Pawn:
                return "*"
            else:
                return "B"
        else:
            if self.state == commons.Pawn:
                return "o"
            else:
                return "W"

################################################################################

class Cell:
    """Cell represent a cell of the checkerboard, not a pawn"""

    def __init__(self, color, stone, state=commons.Empty):
        self.color = color
        self.state = state
        self.stone = stone

    def fill(self):
        """Fill cell with Stone"""
        self.state = commons.Fill
        self.stone.is_exist = True

    def clean(self):
        self.state = commons.Empty
        self.stone.is_exist = False

    def __str__(self):
        if not self.stone.is_exist:
            if self.color == commons.Black:
                return "-"
            else:
                return " "
        else:
            return (str(self.stone))

    def resolve(line, column):
        """return Color and State tuple for beginning of game
        Take int and not string"""
        # use modulo for test if cell if Black
        if (line % 2 == 0 and column % 2 != 0) or (line % 2 != 0 and column % 2 == 0):
            color = commons.Black
            if line == 4 or line == 5:
                state = commons.Empty
                stone = False
            else:
                state = commons.Fill
                if line < 4:
                    stone = commons.Black
                elif line > 5:
                    stone = commons.White
        else:
            color = commons.White
            state = commons.Empty
            stone = False
        return (color, state, stone)


################################################################################

class Board:
    """A base class for implement Board"""
    def __init__(self):
        idx = 0
        self.board = {}
        for line in BOARD_LINES:
            self.board[line] = {}
            for column in BOARD_COLUMNS:
                (line_idx, column_idx) = from_board_to_index(line, column)
                (color, state, has_stone) = Cell.resolve(line_idx, column_idx)
                if has_stone == False:
                    #void stone
                    stone = Stone()
                else:
                    stone = Stone(color=has_stone, is_exist=True)
                self.board[line][column] = Cell(color=color, stone=stone, state=state)
    
    def update(self, cell, mode=commons.Empty):
        """cell format -> '[a-j][0-9]'"""
        (line, column) = (cell[0], cell[1])
        self.board[line][column] = mode

    def display(self):
        acc = ""
        print("   ", end="")
        for column_head in BOARD_COLUMNS:
            acc += (" " + column_head + " ")
        print(acc)
        acc = ""
        for line in BOARD_LINES:
            print(" " + line + " ", end="")
            for column in BOARD_COLUMNS:
                print(" " + str(self.board[line][column]) + " ", end="")
            print("")
