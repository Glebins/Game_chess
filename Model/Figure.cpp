#include "Figure.h"

bool Figure::is_position_valid(int x, int y)
{
    if (x >= 0 && x <= cols - 1 && y >= 0 && y <= rows - 1)
        return true;
    else return false;
}

int Figure::create_position(int x, int y)
{
    return 8 * x + y;
}

Figure* Figure::symbol_to_figure(std::string symbol)
{
    if (!strcmp(symbol.c_str(), "-"))
        return nullptr;

    int col = (symbol[1] == 'B' ? 1 : 0);
    char code = symbol[0];

    if (code == 'r')
    {
        auto *another_figure = new Rook();
        another_figure->color = col;
        return another_figure;
    }
    else if (code == 'n')
    {
        auto *another_figure = new Knight();
        another_figure->color = col;
        return another_figure;
    }
    else if (code == 'b')
    {
        auto *another_figure = new Bishop();
        another_figure->color = col;
        return another_figure;
    }
    else if (code == 'q')
    {
        auto *another_figure = new Queen();
        another_figure->color = col;
        return another_figure;
    }
    else if (code == 'k')
    {
        auto *another_figure = new King();
        another_figure->color = col;
        return another_figure;
    }
    else if (code == 'p')
    {
        auto *another_figure = new Pawn();
        another_figure->color = col;
        return another_figure;
    }

    return nullptr;
}

std::ostream& operator <<(std::ostream& stream, Figure *figure)
{
    if (figure == nullptr)
    {
        stream << "-";
        return stream;
    }

    stream << (figure->get_color() ? "b" : "w") << figure->get_name_of_figure();
    return stream;
}

bool Figure::can_do_move(Figure *figure, int position, int move_position)
{
    std::vector<int> moves = array_moves(figure, position);

    if (std::find(moves.begin(), moves.end(), move_position) != moves.end())
        return true;
    else return false;
}




std::vector<int> King::array_moves(Figure *figure, int position)
{
    int x = position / 8;
    int y = position % 8;

    std::vector<int> moves;

    if (is_position_valid(x - 1, y))
        moves.push_back(create_position(x - 1, y));
    if (is_position_valid(x + 1, y))
        moves.push_back(create_position(x + 1, y));
    if (is_position_valid(x - 1, y - 1))
        moves.push_back(create_position(x - 1, y - 1));
    if (is_position_valid(x - 1, y + 1))
        moves.push_back(create_position(x - 1, y + 1));
    if (is_position_valid(x + 1, y + 1))
        moves.push_back(create_position(x + 1, y + 1));
    if (is_position_valid(x + 1, y - 1))
        moves.push_back(create_position(x + 1, y - 1));
    if (is_position_valid(x, y - 1))
        moves.push_back(create_position(x, y - 1));
    if (is_position_valid(x, y + 1))
        moves.push_back(create_position(x, y + 1));

    return moves;
}


std::vector<int> Queen::array_moves(Figure *figure, int position)
{
    int x = position / 8;
    int y = position % 8;

    std::vector<int> moves;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (((abs(x - i) == abs(y - j)) or (x == i or y == j)) and !(i == x and j == y))
                moves.push_back(create_position(i, j));
        }
    }

    return moves;
}



std::vector<int> Rook::array_moves(Figure *figure, int position)
{
    int x = position / 8;
    int y = position % 8;

    std::vector<int> moves;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((i == x or j == y) and !(i == x and j == y))
            {
                moves.push_back(create_position(i, j));
            }
        }
    }

    return moves;
}




std::vector<int> Bishop::array_moves(Figure *figure, int position)
{
    int x = position / 8;
    int y = position % 8;

    std::vector<int> moves;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((abs(x - i) == abs(y - j)) and !(i == x and j == y))
            {
                moves.push_back(create_position(i, j));
            }
        }
    }

    return moves;
}





std::vector<int> Knight::array_moves(Figure *figure, int position)
{
    int x = position / 8;
    int y = position % 8;

    std::vector<int> moves;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (((abs(x - i) == 1 and abs(y - j) == 2) or (abs(x - i) == 2 and abs(y - j) == 1)) and
                !(i == x and j == y))
                moves.push_back(create_position(i, j));
        }
    }

    return moves;
}




std::vector<int> Pawn::array_moves(Figure *figure, int position)
{
    int x = position / 8;
    int y = position % 8;

    std::vector<int> moves;

    if (figure->get_color() == 1)
    {
        if (x == 1)
        {
            moves.push_back(create_position(x + 1, y));
            moves.push_back(create_position(x + 2, y));
        }

        else
        {
            if (is_position_valid(x + 1, y))
                moves.push_back(create_position(x + 1, y));
        }

        if (is_position_valid(x + 1, y - 1))
            moves.push_back(create_position(x + 1, y - 1));
        if (is_position_valid(x + 1, y + 1))
            moves.push_back(create_position(x + 1, y + 1));
    }

    else
    {
        if (x == 6)
        {
            moves.push_back(create_position(x - 1, y));
            moves.push_back(create_position(x - 2, y));
        }

        else
        {
            if (is_position_valid(x - 1, y))
                moves.push_back(create_position(x - 1, y));
        }

        if (is_position_valid(x - 1, y + 1))
            moves.push_back(create_position(x - 1, y + 1));
        if (is_position_valid(x - 1, y - 1))
            moves.push_back(create_position(x - 1, y - 1));
    }

    return moves;
}
