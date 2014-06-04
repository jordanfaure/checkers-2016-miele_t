#include "player.h"

Player::Player(QObject *parent) :
    QObject(parent)
{
    _color = checkers::NoColor;
    _mode = checkers::Human;
}

void Player::setColor(checkers::Color color)
{
    _color = color;
}

void Player::setMode(checkers::PlayerType mode)
{
    _mode = mode;
}

void Player::think(checkers::Move &move, Board *board)
{
    move.color = _color;
    if (_mode == checkers::Cpu)
        this->AiThink(move, board);
    else if (_mode == checkers::Human)
        this->humanThink(move);
}

void Player::humanThink(checkers::Move &move)
{
    QRegExp pattern(HUMAN_PLAYER_REGEX);
    QTextStream qcin(stdin);
    QTextStream qcout(stdout);
    QString entry;

    if (_color == checkers::White)
        qcout << "White # ";
    else if (_color == checkers::Black)
        qcout << "Black # ";
    else
        qcout << "NoColor # ";
    qcout.flush();

    entry = qcin.readLine();
    move.valid = false;
    if (entry.contains(pattern))
    {
        QByteArray bytes(entry.toLocal8Bit());
        const char *str = bytes.data();

        qcout << str << endl;

        /* start pos : col-line*/
        if (move.convert(str[1], str[0], move.start) &&
                move.convert(str[3], str[2], move.finish))
        {
            move.valid = true;
        }
        else
        {
            move.valid = false;
        }
    }
    else
    {
        move.start.first = move.start.second = -1;
        move.finish.first = move.finish.second = -1;
        move.valid = false;
    }
    qcout << "> "
          << move.start.first << '-' << move.start.second
          << ' '
          << move.finish.first << '-' << move.finish.second
          << ' '
          << move.valid << endl;
}

void Player::AiThink(checkers::Move &best_move, Board *board)
{
    int max_val = -1000;
    int val = 0;

    Board::MoveList moves = board->nextMoves();
    Board::MoveList::iterator it;
    for (it = moves.begin(); it != moves.end(); ++it)
    {
        board->pushMove(*it);
        val = this->min(board, MINMAX_DEPTH);

        if (val > max_val)
        {
            max_val = val;
            best_move = *it;
        }
        board->popMove();
    }
}

int Player::min(Board *board, int depth)
{
    int min_val = 1000;
    int val = 0;

    if (depth == 0 || board->isGameOver())
    {
        return board->heuristic();
    }

    Board::MoveList moves = board->nextMoves();
    Board::MoveList::iterator it;
    for (it = moves.begin(); it != moves.end(); ++it)
    {
        board->pushMove(*it);
        val = this->max(board, depth - 1);

        if (val < min_val)
        {
            min_val = val;
        }

        board->popMove();
    }
    return min_val;
}

int Player::max(Board *board, int depth)
{
    int max_val = -1000;
    int val = 0;

    if (depth == 0 || board->isGameOver())
    {
        return board->heuristic();
    }

    Board::MoveList moves = board->nextMoves();
    Board::MoveList::iterator it;
    for (it = moves.begin(); it != moves.end(); ++it)
    {
        board->pushMove(*it);

        val = this->min(board, depth - 1);

        if (val > max_val)
        {
            max_val = val;
        }

        board->popMove();
    }
    return max_val;
}
