#ifndef CHECHERS_H
#define CHECHERS_H

#include <utility>

namespace checkers {

typedef std::pair<int, int> Position;

enum Color {NoColor, White, Black};

enum CaseState {Empty, Fill};

enum PieceType {NoPiece, Pawn, Lady};

enum PlayerType {Cpu, Human};

/*
 * InvalidMove erase other flags
 * ValidMove can be also promotion of a pawn
 * and a take.
 */

enum MoveType{
    InvalidMove = 0,
    isPromotion = 1 << 0,
    isTake = 1 << 1,
    ValidMove = 1 << 2
};

struct Move {
    Position start;
    Position taken; // used only when MoveType isTake
    Position finish;
    Color color;
    MoveType type;
    bool valid;

    Move()
        : start(0, 0), taken(0, 0), finish(0, 0),
          color(NoColor), type(InvalidMove),
          valid(false)
    {}

    bool convert(char l, char c, Position &pos)
    {
        int line(0);
        int column(0);

        column = c - '0' - '0' - 1;
        line = l - '0';
        if (line < 0 || line >= 10
                && column <0 || column >= 10)
        {
            pos.first  = -1;
            pos.second = -1;
            return false;
        }
        else
        {
            pos.first = line;
            pos.second = column;
            return true;
        }
    }
};

struct Case {
    Case() :
        state(Empty), color(NoColor), piece(NoPiece),
        pos(0, 0), repr('.')
    {
    }

    CaseState state;
    Color color;
    PieceType piece;
    Position pos;
    char repr;

    void clean()
    {
        state = Empty;
        color = NoColor;
        piece = NoPiece;
        repr = '.';
    }

    void setPosition(int line, int column)
    {
        pos.first = line;
        pos.second = column;
    }

    void setRepr()
    {
        repr = '.';

        if (state == Fill)
        {
            if (color == White)
            {
                if (piece == Pawn)
                {
                    repr = 'w';
                }
                else if (piece == Lady)
                {
                    repr = 'W';
                }
            }
            else if (color == Black)
            {
                if (piece == Pawn)
                {
                    repr = 'b';
                }
                else if (piece == Lady)
                {
                    repr = 'B';
                }
            }
        }
    }
};

}

#endif // CHECHERS_H
