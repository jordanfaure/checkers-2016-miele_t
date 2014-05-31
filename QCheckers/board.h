#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QString>
#include <QTextStream>

#include "chechers.h"

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);
// functions
    bool isGameOver() const;
    int heuristic() const;

signals:

public slots:
    void update(checkers::Move &);
    void checkMove(checkers::Move &);
    void display();
    checkers::Color currentPlayer() const;
    void switchPlayer();

private:
    checkers::Case _board[10][10];
    int _blackStones;
    int _whiteStones;
    checkers::Color _player;
};

#endif // BOARD_H
