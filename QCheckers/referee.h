#ifndef REFEREE_H
#define REFEREE_H

#include <QObject>

#include "chechers.h"

class Referee : public QObject
{
    Q_OBJECT
public:
    explicit Referee(QObject *parent = 0);

    checkers::Color getCurrentPlayer() const;
    bool checkMove(checkers::Move &);
    bool isOver() const;
signals:
    /* gameOver -> Draught::stop -> qApp::quit
     */
    void gameOver();
    void requestMoveValidity(checkers::Move &);
    void update(checkers::Move &);

public slots:
    void GETgameOver();
    void switchPlayer();

private:
    checkers::Color _player;
    bool _isOver;
};

#endif // REFEREE_H
