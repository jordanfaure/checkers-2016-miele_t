#!/usr/bin/env python

import commons

class Referee:
    """Referee : implementation of International Checkers / Draughts rules"""
    def __init__(self, ihm, black, white, board):
        self.game_is_over = False
        self.ihm = ihm
        self.black = black
        self.white = white
        self.board = board
        self.color = commons.White

    def checkHit(self, hit):
        if hit == commons.Hit.Bad:
            return False
        elif hit == commons.Hit.Quit:
            self.game_is_over = True
            return True
        else:
            ## Well formatted entry -> update board
            if commons.Hit.isFormat(hit):
                # well formated -> check is legal
                (s_c, s_l, e_c, e_l) = commons.Hit.explode(hit)

                if self.board.action_is_move(hit, stone=self.board.board[s_l][s_c].stone.state, color=self.board.board[s_l][s_c].stone.color):
                    self.board.board[s_l][s_c].fill()
                    self.board.board[e_l][e_c].stone.color = self.board.board[s_l][s_c].stone.color
                    self.board.board[e_l][e_c].stone.state = self.board.board[s_l][s_c].stone.state
                    self.board.board[e_l][e_c].stone.is_exist = self.board.board[s_l][s_c].stone.is_exist
                    self.board.board[s_l][s_c].clean()
                    return True
                elif self.board.action_is_take(hit, stone=self.board.board[s_l][s_c].stone.state, color=self.board.board[s_l][s_c].stone.color):
                    pass
                else:
                    return False
            else:
                return False

    def isGameOver(self):
        return self.game_is_over

    def switch(self, color):
        if color == commons.White:
            return commons.Black
        elif color == commons.Black:
            return commons.White
        else:
            raise Exception("Referee.switch error")

    def think(self):
        self.ihm.display()
        if self.color == commons.Black:
            return self.black.think()
        elif self.color == commons.White:
            return self.white.think()
        else:
            raise Exception("Referee.think error")

    def launch(self):
        while not self.game_is_over:
            is_legal = False
            hit = ""
            while not is_legal:
                hit = self.think()
                is_legal = self.checkHit(hit)
            self.color = self.switch(self.color)
            self.game_is_over = self.isGameOver()
        ## end game
