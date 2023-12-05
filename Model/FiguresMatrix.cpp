#include "FiguresMatrix.h"

// Matrix - обычная матрица, шаблонный класс с типом T**

FiguresMatrix::FiguresMatrix()
{
    matrix = new Figure** [rows];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new Figure* [cols];

        for (int j = 0; j < cols; j++)
        {
            Figure* tmp = Figure().symbol_to_figure(disposition[i][j]);
            matrix[i][j] = tmp;
        }
    }
}

void FiguresMatrix::set_start_disposition()
{
    matrix = new Figure** [rows];

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new Figure* [cols];

        for (int j = 0; j < cols; j++)
        {
            Figure* tmp = Figure().symbol_to_figure(disposition[i][j]);
            matrix[i][j] = tmp;
        }
    }
}

void FiguresMatrix::move_figure(int from_position, int move_position)
{
    Figure *current_figure = get_figure(from_position);
    std::cout << current_figure->get_name_of_figure() << "\n\n";

    if (!can_do_move(from_position, move_position))
    {
        // throw
        std::cout << "Can't do move\n";

        return;
    }

    Figure *figure_on_new_position = matrix[move_position / 8][move_position % 8];

    if (figure_on_new_position != nullptr)
    {
        delete figure_on_new_position;
    }

    matrix[move_position / 8][move_position % 8] = current_figure;
    matrix[from_position / 8][from_position % 8] = nullptr;
}

bool FiguresMatrix::can_do_move(int from_position, int move_position)
{
    Figure *figure = get_figure(from_position);
    bool can_move = figure->can_do_move(figure, from_position, move_position);

    if (!can_move) return false;

    Figure *figure_on_new_position = matrix[move_position / 8][move_position % 8];

    int x0 = from_position / 8;
    int y0 = from_position % 8;
    int x1 = move_position / 8;
    int y1 = move_position % 8;

    if (x0 > x1)
    {
        int tmp = x1;
        x1 = x0;
        x0 = tmp;
    }

    if (figure->get_name_of_figure() == "Pawn" or figure->get_name_of_figure() == "King")
    {
        // pass out
    }

    else if (figure->get_name_of_figure() == "Rook")
    {
        int difference = (x0 == x1) ? (y1 - y0) : (x1 - x0);

        while (difference != 1)
        {
            int i, j;

            if (x0 == x1)
            {
                i = x0;
                j = y0 + difference - (int) difference / abs(difference);
                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;
            }

            else
            {
                i = x0 + difference - (int) difference / abs(difference);
                j = y0;
                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;
            }

            difference -= (int) (difference) / abs(difference);
        }
    }

    else if (figure->get_name_of_figure() == "Bishop")
    {
        int sign_x = (x1 - x0) / abs(x1 - x0);
        int sign_y = (y1 - y0) / abs(y1 - y0);

        int difference_x = x1 - x0;

        while (difference_x != 0)
        {
            int i = x0 + difference_x - sign_x;
            int j = y0 + difference_x - sign_y;

            if (get_figure(Figure().create_position(i, j)) != nullptr)
                return false;

            difference_x -= sign_x;
        }
    }

    else if (figure->get_name_of_figure() == "Queen")
    {
        int difference = (x0 == x1) ? (y1 - y0) : (x1 - x0);

        if (x0 == x1)
        {
            while (difference != 1)
            {
                int i = x0;
                int j = y0 + difference - (int) difference / abs(difference);
                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;
            }
        }

        else if (y0 == y1)
        {
            while (difference != 1)
            {
                int i = x0 + difference - (int) difference / abs(difference);
                int j = y0;
                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;
            }
        }

        else
        {
            int sign_x = (x1 - x0) / abs(x1 - x0);
            int sign_y = (y1 - y0) / abs(y1 - y0);

            int difference_x = x1 - x0;

            while (difference_x != 0)
            {
                int i = x0 + difference_x - sign_x;
                int j = y0 + difference_x - sign_y;

                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;

                difference_x -= sign_x;
            }
        }
    }


    if (figure_on_new_position == nullptr)
        return true;

    else if (figure_on_new_position->get_color() != figure->get_color())
        return true;

    else
        return false;
}

int FiguresMatrix::find_figure(Figure *figure) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != nullptr and !strcmp(matrix[i][j]->get_name_of_figure().c_str(),
                figure->get_name_of_figure().c_str()) && figure->get_color() == matrix[i][j]->get_color())
            {
                return i * 8 + j;
            }
        }
    }

    throw std::invalid_argument("Couldn't find");
}

Figure* FiguresMatrix::get_figure(int position)
{
    if (position < 0 || position >= cols * rows)
        throw std::invalid_argument("Bad position");

    return matrix[position / 8][position % 8];
}

void FiguresMatrix::print_debug() const
{
    std::cout << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Figure *tmp = matrix[i][j];
            if (tmp != nullptr)
                std::cout << (tmp->get_color() ? "b" : "w") << tmp->get_name_of_figure() << "\t";
            else
                std::cout << "-" << "\t\t";
        }

        std::cout << "\n";
    }

    std::cout << std::endl;
}

void FiguresMatrix::free_memory()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            delete matrix[i][j];

        delete[] matrix[i];
    }

    delete[] matrix;
}

FiguresMatrix::~FiguresMatrix()
{
    free_memory();
}
