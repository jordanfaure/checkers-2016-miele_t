#include "draughts.h"

#include <QCoreApplication>

#include <QTextStream>

Draughts::Draughts(QObject *parent) :
    QObject(parent)
{
    _board = new Board(this);
    _black = new Player(this);
    _white = new Player(this);

    _black->setColor(checkers::Black);
    _white->setColor(checkers::White);

    _black->setMode(checkers::Cpu);

    connect(this, SIGNAL(launch()), this, SLOT(play()));
    connect(this, SIGNAL(stop()), qApp, SLOT(quit()));
}

void Draughts::play()
{
    QTextStream qcout(stdout);

    checkers::Color player;
    checkers::Move move;

    while (!_board->isGameOver()) {
        player = _board->currentPlayer();
        _board->display();
        do {
            if (player == checkers::White) {
                _white->think(move, _board);
            } else if (player == checkers::Black) {
                _black->think(move, _board);
            }
            _board->checkMove(move);
        }
        while (!move.valid);
        _board->pushMove(move);
    }
    qcout << "GAME OVER" << endl;
    emit this->stop();
}
