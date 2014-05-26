#-------------------------------------------------
#
# Project created by QtCreator 2014-05-12T14:39:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QCheckers
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    referee.cpp \
    player.cpp \
    draughts.cpp \
    board.cpp

win32 {
    QMAKE_LFLAGS += /INCREMENTAL:NO
}

HEADERS += \
    referee.h \
    player.h \
    draughts.h \
    board.h \
    chechers.h
