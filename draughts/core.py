#!/usr/bin/env python

import commons, ihm, player, referee

def launch():
    Ihm = ihm.IHM()
    white_player = player.Player(commons.White, commons.Human, Ihm)
    black_player = player.Player(commons.Black, commons.Human, Ihm)
    Referee = referee.Referee(Ihm, black_player, white_player)
    Referee.launch()

if __name__ == '__main__':
    launch()
