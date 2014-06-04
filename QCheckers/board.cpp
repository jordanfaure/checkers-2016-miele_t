#include "board.h"
static const char *initialBoard[] =
{
    " b b b b b",
    "b b b b b ",
    " b b b b b",
    "b b b b b ",
    " . . . . .",
    ". . . . . ",
    " w w w w w",
    "w w w w w ",
    " w w w w w",
    "w w w w w ",
};

/*
static const char *initialBoard[] =
{
    " . . . . .",
    ". . . . . ",
    " . . . . .",
    ". . . . . ",
    " . . . . .",
    ". . B . . ",
    " . W . . .",
    ". . . . . ",
    " . . . . .",
    ". . . . . ",
};
*/
Board::Board(QObject *parent) :
    QObject(parent)
{
    _blackStones = 0;
    _whiteStones = 0;
    _player = checkers::White;

    for (int l = 0; l < 10; ++l)
    {
        for (int c = 0; c < 10; ++c)
        {
            _board[l][c].pos.first = l;
            _board[l][c].pos.second = c;

            if (initialBoard[l][c] == 'b')
            {
                _board[l][c].state = checkers::Fill;
                _board[l][c].color = checkers::Black;
                _board[l][c].piece = checkers::Pawn;
                _board[l][c].setRepr();
                _blackStones += 1;
            }
            else if (initialBoard[l][c] == 'B')
            {
                _board[l][c].state = checkers::Fill;
                _board[l][c].color = checkers::Black;
                _board[l][c].piece = checkers::Lady;
                _board[l][c].setRepr();
                _blackStones += 1;
            }
            else if (initialBoard[l][c] == 'w')
            {
                _board[l][c].state = checkers::Fill;
                _board[l][c].color = checkers::White;
                _board[l][c].piece = checkers::Pawn;
                _board[l][c].setRepr();
                _whiteStones += 1;
            }
            else if (initialBoard[l][c] == 'W')
            {
                _board[l][c].state = checkers::Fill;
                _board[l][c].color = checkers::White;
                _board[l][c].piece = checkers::Lady;
                _board[l][c].setRepr();
                _whiteStones += 1;
            }
            else if (initialBoard[l][c] == '.')
            {
                _board[l][c].clean();
            }
            else
            {
                _board[l][c].clean();
                _board[l][c].repr = ' ';
            }
        }
    }
}

bool Board::isGameOver() const
{
    if (_blackStones <= 0 || _whiteStones <= 0)
        return true;
    return false;
}

void Board::pushMove(checkers::Move &move)
{
    int s_l(move.start.first);
    int s_c(move.start.second);

    int f_l(move.finish.first);
    int f_c(move.finish.second);

    if (!move.valid || move.type == checkers::InvalidMove)
        return;
    if (move.type & checkers::ValidMove)
    {
        _board[f_l][f_c].state = _board[s_l][s_c].state;
        _board[f_l][f_c].color = _board[s_l][s_c].color;
        _board[f_l][f_c].piece = _board[s_l][s_c].piece;
        _board[f_l][f_c].repr = _board[s_l][s_c].repr;

        if (move.type & checkers::isPromotion)
        {
            _board[f_l][f_c].piece = checkers::Lady;
            _board[f_l][f_c].setRepr();
        }
        if (move.type & checkers::isTake)
        {
            checkers::Color color = _board[move.taken.first][move.taken.second].color;
            if (color == checkers::Black)
                _blackStones -= 1;
            else if (color == checkers::White)
                _whiteStones -=1;
            move.takenPiece = _board[move.taken.first][move.taken.second];
            _board[move.taken.first][move.taken.second].clean();
        }
        _board[s_l][s_c].clean();
    }
    _moves.push_front(move);
    this->switchPlayer();
}

void Board::popMove()
{
    if (_moves.empty())
        return;
    checkers::Move move = _moves.last();
    int s_l(move.start.first);
    int s_c(move.start.second);

    int f_l(move.finish.first);
    int f_c(move.finish.second);

    if (!move.valid || move.type == checkers::InvalidMove)
        return;
    if (move.type & checkers::ValidMove)
    {
        _board[s_l][s_c].state = _board[f_l][f_c].state;
        _board[s_l][s_c].color = _board[f_l][f_c].color;
        _board[s_l][s_c].piece = _board[f_l][f_c].piece;
        _board[s_l][s_c].repr = _board[f_l][f_c].repr;

        if (move.type & checkers::isPromotion)
        {
            _board[s_l][s_c].piece = checkers::Pawn;
            _board[s_l][s_c].setRepr();
        }
        if (move.type & checkers::isTake)
        {
            checkers::Color color = _board[move.taken.first][move.taken.second].color;
            if (color == checkers::Black)
                _blackStones += 1;
            else if (color == checkers::White)
                _whiteStones +=1;
            _board[move.taken.first][move.taken.second] = move.takenPiece;
        }
        _board[f_l][f_c].clean();
    }
    _moves.pop_front();
    this->switchPlayer();
}

void Board::display()
{
    QTextStream qcout(stdout);

    /*
     * head : |  a b c d e f g h i j
     * body : |0 b . . B . w . . W .
     * repeat |1 . . .
     */
    qcout << "   ";
    for (int col = 0; col < 10; ++col)
    {
        qcout << static_cast<char>(col + 'a') << ' ';
    }
    qcout << endl;

    for (int line = 0; line < 10; ++line)
    {
        qcout << static_cast<char>(line + '0') << "  ";
        for (int col = 0; col < 10; ++col)
        {
            qcout << _board[line][col].repr << ' ';
        }
        qcout << endl;
    }
}

void Board::checkMove(checkers::Move &move)
{
    checkers::Case startStone = _board[move.start.first][move.start.second];
    checkers::Case finishStone = _board[move.finish.first][move.finish.second];
    checkers::Position takenStone;

    int flags = checkers::InvalidMove;

    int s_l = startStone.pos.first;
    int s_c = startStone.pos.second;

    int f_l = finishStone.pos.first;
    int f_c = finishStone.pos.second;

    if (!move.valid
            || startStone.state == checkers::Empty
            || startStone.color == checkers::NoColor
            || startStone.piece == checkers::NoPiece
            || move.color != startStone.color)
    {
        goto bad;
    }
    if (finishStone.state != checkers::Empty
            || finishStone.color == startStone.color
            || finishStone.piece != checkers::NoPiece)
    {
        goto bad;
    }

    if (startStone.piece == checkers::Pawn)
    {
        if (startStone.color == checkers::Black)
        {
            if (finishStone.pos.first == 9)
            {
                flags |= checkers::isPromotion;
            }
            if ( f_l == s_l + 1 && (f_c == s_c + 1 || f_c == s_c - 1) )
            {
                flags |= checkers::ValidMove;
            }
            else if ( f_l == s_l + 2 && (f_c == s_c + 2 || f_c == s_c - 2) )
            {
                takenStone.first = finishStone.pos.first - startStone.pos.first;
                takenStone.second = finishStone.pos.second - startStone.pos.second;

                move.taken.first = (takenStone.first < 0 ? startStone.pos.first - 1 : startStone.pos.first + 1);
                move.taken.second = (takenStone.second < 0 ? startStone.pos.second - 1 : startStone.pos.second + 1);

                checkers::Case takenCase = _board[move.taken.first][move.taken.second];
                if (takenCase.state == checkers::Empty
                        || takenCase.color == startStone.color
                        || takenCase.piece == checkers::NoPiece)
                {
                    goto bad;
                }
                flags |= (checkers::ValidMove | checkers::isTake);
            }
            else
            {
                goto bad;
            }
            goto good;
        }
        else if (startStone.color == checkers::White)
        {
            if (finishStone.pos.first == 0)
            {
                flags |= checkers::isPromotion;
            }
            if ( f_l == s_l - 1 && (f_c == s_c + 1 || f_c == s_c - 1) )
            {
                flags |= checkers::ValidMove;
            }
            else if ( f_l == s_l - 2 && (f_c == s_c + 2 || f_c == s_c - 2) )
            {
                takenStone.first = finishStone.pos.first - startStone.pos.first;
                takenStone.second = finishStone.pos.second - startStone.pos.second;

                move.taken.first = (takenStone.first < 0 ? startStone.pos.first - 1 : startStone.pos.first + 1);
                move.taken.second = (takenStone.second < 0 ? startStone.pos.second - 1 : startStone.pos.second + 1);

                checkers::Case takenCase = _board[move.taken.first][move.taken.second];
                if (takenCase.state == checkers::Empty
                        || takenCase.color == startStone.color
                        || takenCase.piece == checkers::NoPiece)
                {
                    goto bad;
                }
                flags |= (checkers::ValidMove | checkers::isTake);
            }
            else
            {
                goto bad;
            }
            goto good;
        }
    }
    else if (startStone.piece == checkers::Lady)
    {
        if (startStone.color == checkers::Black
                || startStone.color == checkers::White)
        {
            if ( (f_l == s_l - 1 || f_l == s_l + 1) && (f_c == s_c + 1 || f_c == s_c - 1) )
            {
                flags |= checkers::ValidMove;
            }
            else if ( (f_l == s_l - 2 || f_l == s_l + 2) && (f_c == s_c + 2 || f_c == s_c - 2) )
            {
                // [5,0] -> [3,2] isTake [4,1]
                takenStone.first = finishStone.pos.first - startStone.pos.first; // 3 - 5 = -2
                takenStone.second = finishStone.pos.second - startStone.pos.second; // 2 - 0 = 2

                move.taken.first = (takenStone.first < 0 ? startStone.pos.first - 1 : startStone.pos.first + 1); // -2 < 0 ?  4 : 5
                move.taken.second = (takenStone.second < 0 ? startStone.pos.second - 1 : startStone.pos.second + 1); // 2 < 0 ? -1 : 1

                checkers::Case takenCase = _board[move.taken.first][move.taken.second];
                if (takenCase.state == checkers::Empty
                        || takenCase.color == startStone.color
                        || takenCase.piece == checkers::NoPiece)
                {
                    goto bad;
                }
                flags |= (checkers::ValidMove | checkers::isTake);
            }
            else
            {
                goto bad;
            }
            goto good;
        }
        goto bad;
    }
bad:
    move.type = checkers::InvalidMove;
    move.valid = false;
    return;
good:
    move.type = static_cast<checkers::MoveType>(flags);
    move.valid = true;
    return;
}

checkers::Color Board::currentPlayer() const
{
    return _player;
}

void Board::switchPlayer()
{
    /* NoColor case is not tested
     */
    _player = (_player == checkers::White ?
                   checkers::Black : checkers::White);
}

int Board::heuristic()
{
    checkers::Color player = this->currentPlayer();

    if (this->isGameOver())
    {
        if (player == checkers::White)
        {
            int i = _whiteStones - _blackStones;
            return (i < 0 ? -i : i);
        }
        else if (player == checkers::Black)
        {
            int i =  _blackStones - _whiteStones;
            return (i < 0 ? -i : i);
        }
    }
    return 1;
}

Board::MoveList Board::nextMoves()
{
    Board::MoveList moves;

    return moves;
}
