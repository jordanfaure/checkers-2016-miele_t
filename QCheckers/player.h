#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QRegExp>
#include <QTextStream>

#include "board.h"
#include "chechers.h"

#define PYTHON_HUMAN_PLAYER_REGEX "^([a-jA-J]\d){2}$"
#define HUMAN_PLAYER_REGEX "^([a-j]\\d){2}$"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    void setColor(checkers::Color);
    void setMode(checkers::PlayerType);

signals:

public slots:
    void think(checkers::Move&, Board *);
    void humanThink(checkers::Move&);
    void AiThink(checkers::Move&, Board *);

private:
    checkers::Color _color;
    checkers::PlayerType _mode;
};


#endif // PLAYER_H
