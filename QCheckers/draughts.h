#ifndef DRAUGHTS_H
#define DRAUGHTS_H

#include <QObject>

#include "chechers.h"
#include "board.h"
#include "player.h"

class Draughts : public QObject
{
    Q_OBJECT
public:
    explicit Draughts(QObject *parent = 0);

signals:
    void launch();
    void stop();

public slots:
    void play();

private:
    Board *_board;
    Player *_black;
    Player *_white;
};

#endif // DRAUGHTS_H
