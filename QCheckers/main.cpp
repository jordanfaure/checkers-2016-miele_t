#include <QCoreApplication>

#include "draughts.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Draughts game;

    emit game.launch();
    return app.exec();
}
