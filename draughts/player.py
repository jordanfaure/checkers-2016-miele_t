#!/usr/bin/env python

import commons

class Player:
    """Base class for Human and AI player
    mode : Human | Ai
    color : Black | White"""
    def __init__(self, color, mode=commons.Human, ihm=None, ai=None):
        self.ihm = ihm
        self.ai = ai
        self.mode = mode
        self.color = color
    def think(self):
        if self.mode == commons.Human and self.ihm != None:
            return self.ihm.think(self.color)
        elif self.mode == commons.CPU and self.ai != None:
            return self.ai.think()
        else:
            print("Player error: Bad init !")
    def updateBoard(self, entry):
        if self.mode == commons.CPU:
            if self.ai == None:
                raise Exception("Player.updateBoard error: bad AI config")
            else:
                self.ai.updateBoard(entry)

class AI(Player):
    """AI added to Player by composition"""
    def __init__(self):
        self.board = None

    def updateBoard(self, entry):
        pass

    def think(self):
        return commons.Hit.Bad
