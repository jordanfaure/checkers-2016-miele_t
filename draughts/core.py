#!/usr/bin/env python

import commons, ihm, player, referee, board

def launch():
    Board = board.Board()
    Ihm = ihm.IHM(Board)
    white_player = player.Player(color=commons.White, mode=commons.Human, ihm=Ihm, board=Board)
    black_player = player.Player(color=commons.Black, mode=commons.Human, ihm=Ihm, board=Board)
    Referee = referee.Referee(Ihm, black_player, white_player, Board)
    Referee.launch()

if __name__ == '__main__':
    launch()
