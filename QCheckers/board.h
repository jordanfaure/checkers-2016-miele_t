#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QLinkedList>

#include "chechers.h"

class Board : public QObject
{
    Q_OBJECT
public:
    typedef QLinkedList<checkers::Move> MoveList;

    explicit Board(QObject *parent = 0);

// functions
    bool isGameOver() const;

    int heuristic();
    MoveList nextMoves();

    void pushMove(checkers::Move &);
    void popMove();
    void checkMove(checkers::Move &);

    void display();

    checkers::Color currentPlayer() const;
    void switchPlayer();

private:
    MoveList _moves;
    checkers::Case _board[10][10];
    int _blackStones;
    int _whiteStones;
    checkers::Color _player;
};

#endif // BOARD_H
