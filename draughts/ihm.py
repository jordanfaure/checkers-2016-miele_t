#!/usr/bin/env python

# display game
# wait hit
# clear screen

import platform
import os

import commons
import board

class IHM:
    def __init__(self, board):
        self.board = board

    def clear(self):
        arch = platform.system()
        if arch == "Windows":
            os.system("cls")
        else:
            os.system("clear")

    def display(self):
        self.board.display()

    def convertHit(self, entry):
        """Capitalize input str and convert into commons.Hit
        Test only Clear and Quit commands
        Leave check format at Referee"""
        hit = entry.capitalize()
        if hit == commons.Hit.Clear:
            self.clear()
            hit = commons.Hit.Bad
        elif hit == commons.Hit.Quit:
            hit = commons.Hit.Quit
        else:
            hit = hit.lower()
        return hit
    
    def think(self, color):
        try:
            hit = input(color + " # ")
        except KeyboardInterrupt:
            print("")
            print("Use Quit or quit for exit game")
            hit =  commons.Hit.Bad
        else:
            return self.convertHit(hit)
