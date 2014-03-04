#!/usr/bin/env python

import commons

BOARD_LINES = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]

BOARD_COLUMNS = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]

class Board:
    """A base class for implement Board"""
    def __init__(self, node):
        self.board = {}
        for line in BOARD_LINES:
            self.board[line] = {}
            for column in BOARD_COLUMNS:
                self.board[line][column] = None
    
    def updateBoard(self, entry):
        