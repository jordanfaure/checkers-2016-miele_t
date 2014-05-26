#include "draughts.h"

#include <QCoreApplication>

#include <QTextStream>

Draughts::Draughts(QObject *parent) :
    QObject(parent)
{
    _board = new Board(this);
    _referee = new Referee(this);
    _black = new Player(this);
    _white = new Player(this);

    _black->setColor(checkers::Black);
    _white->setColor(checkers::White);

    _black->setMode(checkers::Cpu);

    connect(this, SIGNAL(launch()), this, SLOT(play()));

    connect(_referee, SIGNAL(update(checkers::Move&)), _board, SLOT(update(checkers::Move&)));
    connect(_referee, SIGNAL(requestMoveValidity(checkers::Move&)), _board, SLOT(checkMove(checkers::Move&)));

    connect(_board, SIGNAL(gameIsOver()), _referee, SLOT(GETgameOver()));

    connect(_referee, SIGNAL(gameOver()), this, SIGNAL(stop()));
    connect(this, SIGNAL(stop()), qApp, SLOT(quit()));
}

void Draughts::play()
{
    QTextStream qcout(stdout);
    bool loop(true);
    checkers::Color player;
    checkers::Move move;

    player = _referee->getCurrentPlayer();
    while(loop)
    {
        _board->display();
        do
        {
            if (player == checkers::White)
            {
                _white->think(move, _board);
            }
            else if (player == checkers::Black)
            {
                _black->think(move, _board);
            }
        }
        while (!_referee->checkMove(move));
        //_board->update(move);
        loop = !_referee->isOver();
        _referee->switchPlayer();
        player = _referee->getCurrentPlayer();
    }
    qcout << "GAME OVER" << endl;
    emit _referee->gameOver();
}
