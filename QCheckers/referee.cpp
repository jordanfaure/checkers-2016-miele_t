#include "referee.h"

Referee::Referee(QObject *parent) :
    QObject(parent)
{
    _player = checkers::White;
    _isOver = false;
}

/*
 * function
 */

checkers::Color Referee::getCurrentPlayer() const
{
    return _player;
}

bool Referee::isOver() const
{
    return _isOver;
}

void Referee::GETgameOver()
{
    _isOver = true;
}

bool Referee::checkMove(checkers::Move &move)
{
    /*
     * if move is valid about syntax and range value
     * not about is validity.
     */
    if (!move.valid)
        return false;
    else
    {
        emit this->requestMoveValidity(move);
        if (move.valid)
        {
            emit this->update(move);
            return true;
        }
        else
            return false;
    }
}

/*
 * slots
 */

void Referee::switchPlayer()
{
    if (_player == checkers::White)
        _player = checkers::Black;
    else if (_player == checkers::Black)
        _player = checkers::White;
}
