#!/usr/bin/env python

import commons, ihm, player, referee, board

def launch():
    Board = board.Board()
    Ihm = ihm.IHM(Board)
    white_player = player.Player(commons.White, commons.Human, Ihm, Board)
    black_player = player.Player(commons.Black, commons.Human, Ihm, Board)
    Referee = referee.Referee(Ihm, black_player, white_player, Board)
    Referee.launch()

if __name__ == '__main__':
    launch()
