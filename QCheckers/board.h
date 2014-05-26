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

    Board *make_AIcopy();
    bool isGameOver() const;

signals:
    void gameIsOver();

public slots:
    void update(checkers::Move &);
    void checkMove(checkers::Move &);
    void display();

private:
    checkers::Case _board[10][10];
    int _blackStones;
    int _whiteStones;
};

#endif // BOARD_H
