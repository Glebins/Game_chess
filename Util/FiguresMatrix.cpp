#include "FiguresMatrix.h"

// Matrix - обычная матрица, шаблонный класс с типом T**

FiguresMatrix::FiguresMatrix(int rows, int cols) : Matrix(rows, cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Figure *tmp = Figure().symbol_to_figure(disposition[i][j]);
            data[i][j] = tmp;
        }
    }
}

FiguresMatrix::FiguresMatrix(const FiguresMatrix &fm) : Matrix(fm.get_rows(), fm.get_cols())
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Figure * current_figure = fm.get_figure(8 * i + j);
            if (current_figure != nullptr)
            {
                char symbol = current_figure->figure_to_symbol();
                char color = (current_figure->get_color() == 0) ? 'W' : 'B';
                std::string fig;
                fig.push_back(symbol);
                fig.push_back(color);

                Figure *tmp = Figure().symbol_to_figure(fig);
                data[i][j] = tmp;
            }
            else
                data[i][j] = fm.data[i][j];
        }
    }
}

void FiguresMatrix::set_start_disposition()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Figure *tmp = Figure().symbol_to_figure(disposition[i][j]);
            data[i][j] = tmp;
        }
    }
}

void FiguresMatrix::move_figure(int from_position, int move_position)
{
    Figure *current_figure = get_figure(from_position);

    if (!can_do_move(from_position, move_position))
    {
        throw std::logic_error("Can't do move");
        // throw or nothing
        // std::cout << "Can't do move\n";
        // return;
    }

    Figure *figure_on_new_position = data[move_position / 8][move_position % 8];

    if (figure_on_new_position != nullptr)
    {
        delete figure_on_new_position;
    }

    data[move_position / 8][move_position % 8] = current_figure;
    data[from_position / 8][from_position % 8] = nullptr;
}

void FiguresMatrix::forcibly_move_figure(int from_position, int move_position)
{
    Figure *current_figure = get_figure(from_position);
    Figure *figure_on_new_position = data[move_position / 8][move_position % 8];

    if (figure_on_new_position != nullptr)
        delete figure_on_new_position;

    data[move_position / 8][move_position % 8] = current_figure;
    data[from_position / 8][from_position % 8] = nullptr;
}

void FiguresMatrix::delete_all_figures()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Figure *current_figure = get_figure(8 * i + j);
            if (current_figure != nullptr)
                delete current_figure;
        }
    }
}

bool FiguresMatrix::can_do_move(int from_position, int move_position)
{
    Figure *figure = get_figure(from_position);
    bool can_move = figure->can_do_move(figure, from_position, move_position);

    if (!can_move) return false;

    Figure *figure_on_new_position = data[move_position / 8][move_position % 8];

    int x0 = from_position / 8;
    int y0 = from_position % 8;
    int x1 = move_position / 8;
    int y1 = move_position % 8;

    if (figure->get_name_of_figure() == "King")
    {
        // pass out
    }

    else if (figure->get_name_of_figure() == "Pawn")
    {
        if (abs(x1 - x0) == 2)
        {
            if (get_figure(Figure().create_position((x1 + x0) / 2, y0)) != nullptr)
                return false;
        }

        if ((y0 == y1) and (figure_on_new_position != nullptr))
            return false;

        if ((y0 != y1) and (figure_on_new_position == nullptr or
            figure_on_new_position->get_color() == figure->get_color()))
            return false;
    }

    else if (figure->get_name_of_figure() == "Rook")
    {
        int difference = (x0 == x1) ? (y1 - y0) : (x1 - x0);

        while (abs(difference) != 1)
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
        int difference_y = y1 - y0;

        while (abs(difference_x) != 1)
        {
            int i = x0 + difference_x - sign_x;
            int j = y0 + difference_y - sign_y;

            if (get_figure(Figure().create_position(i, j)) != nullptr)
                return false;

            difference_x -= sign_x;
            difference_y -= sign_y;
        }
    }

    else if (figure->get_name_of_figure() == "Queen")
    {
        int difference = (x0 == x1) ? (y1 - y0) : (x1 - x0);

        if (x0 == x1)
        {
            while (abs(difference) != 1)
            {
                int i = x0;
                int j = y0 + difference - (int) difference / abs(difference);
                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;

                difference -= (int) (difference) / abs(difference);
            }
        }

        else if (y0 == y1)
        {
            while (abs(difference) != 1)
            {
                int i = x0 + difference - (int) difference / abs(difference);
                int j = y0;
                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;

                difference -= (int) (difference) / abs(difference);
            }
        }

        else
        {
            int sign_x = (x1 - x0) / abs(x1 - x0);
            int sign_y = (y1 - y0) / abs(y1 - y0);

            int difference_x = x1 - x0;
            int difference_y = y1 - y0;

            while (abs(difference_x) != 1)
            {
                int i = x0 + difference_x - sign_x;
                int j = y0 + difference_y - sign_y;

                if (get_figure(Figure().create_position(i, j)) != nullptr)
                    return false;

                difference_x -= sign_x;
                difference_y -= sign_y;
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
            if (data[i][j] != nullptr and !strcmp(data[i][j]->get_name_of_figure().c_str(),
                figure->get_name_of_figure().c_str()) && figure->get_color() == data[i][j]->get_color())
            {
                return i * 8 + j;
            }
        }
    }

    throw std::out_of_range("Element wasn't found");
}



Figure* FiguresMatrix::get_figure(int position) const
{
    return at(position / 8, position % 8);
}


int FiguresMatrix::find_king(bool color) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Figure *current_figure = get_figure(8 * i + j);
            if (current_figure != nullptr and !strcmp(current_figure->get_name_of_figure().c_str(), "King") and
                current_figure->get_color() == color)
            {
                return 8 * i + j;
            }
        }
    }
}


std::vector<int> FiguresMatrix::array_moves(int position)
{
    std::vector<int> moves;
    Figure *current_figure = get_figure(position);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int current_position = 8 * i + j;

            if (can_do_move(position, current_position))
                moves.push_back(current_position);
        }
    }

    return moves;
}





void FiguresMatrix::is_check(bool check_figures_color, int start, int end, std::vector<bool>& results)
{
    int king_position = find_king(!check_figures_color);

    bool verdict;

    for (int i = start; i < end; i++)
    {
        verdict = false;

        for (int j = 0; j < cols; j++)
        {
            int current_position = 8 * i + j;

            Figure *current_figure = get_figure(current_position);
            if (current_figure == nullptr)
                continue;

            if (current_figure->get_color() != check_figures_color)
                continue;

            if (can_do_move(current_position, king_position))
                verdict = true;
        }

        results[i] = verdict;
    }
}

void FiguresMatrix::is_checkmate(bool check_figures_color, int start, int end, std::vector<bool>& results)
{
    check_figures_color = !check_figures_color;

    bool verdict;

    for (int i = start; i < end; i++)
    {
        verdict = true;

        for (int j = 0; j < cols; j++)
        {
            int current_position = 8 * i + j;

            Figure *current_figure = get_figure( current_position);
            if (current_figure == nullptr)
                continue;

            if (current_figure->get_color() != check_figures_color)
                continue;

            std::vector<int> moves = array_moves(current_position);

            for (int &current_move : moves)
            {
                FiguresMatrix fm = *this;

                fm.forcibly_move_figure(current_position, current_move);
                if (!fm.is_check_multi_threading(!check_figures_color))
                {
                    verdict = false;
                }
            }
        }

        results[i] = verdict;
    }
}

void FiguresMatrix::is_stalemate(bool check_figures_color, int start, int end, std::vector<bool>& results)
{
    check_figures_color = !check_figures_color;

    bool verdict;

    for (int i = start; i < end; i++)
    {
        verdict = true;

        for (int j = 0; j < cols; j++)
        {
            int current_position = 8 * i + j;

            Figure *current_figure = get_figure( current_position);
            if (current_figure == nullptr)
                continue;

            if (current_figure->get_color() != check_figures_color)
                continue;

            std::vector<int> moves = array_moves(current_position);

            for (int &current_move : moves)
            {
                FiguresMatrix fm = *this;

                fm.forcibly_move_figure(current_position, current_move);

                if (!fm.is_check_multi_threading(!check_figures_color))
                {
                    verdict = false;
                    goto end;
                }
            }
        }

        end:
        results[i] = verdict;
    }
}




bool FiguresMatrix::is_check_multi_threading(bool check_figures_color)
{
    int iterations = rows;
    int num_threads = rows / 2;

    std::vector<bool> results(iterations, false);

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        int start = i * (iterations / num_threads);
        int end = (i + 1) * (iterations / num_threads);

        if (i == num_threads - 1)
        {
            end = iterations;
        }

        threads[i] = std::thread([this, check_figures_color, start, end, &res = results]() {
            this->is_check(check_figures_color, start, end, res);
        });
    }

    for (int i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }

    for (int i = 0; i < iterations; i++)
    {
        if (results[i])
            return true;
    }

    return false;
}

bool FiguresMatrix::is_checkmate_multi_threading(bool check_figures_color)
{
    int iterations = rows;
    int num_threads = rows / 2;

    std::vector<bool> results(iterations, false);

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        int start = i * (iterations / num_threads);
        int end = (i + 1) * (iterations / num_threads);

        if (i == num_threads - 1)
        {
            end = iterations;
        }

        threads[i] = std::thread([this, check_figures_color, start, end, &res = results]() {
            this->is_checkmate(check_figures_color, start, end, res);
        });
    }

    for (int i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }

    for (int i = 0; i < iterations; i++)
    {
        if (!results[i])
            return false;
    }

    return true;
}

bool FiguresMatrix::is_stalemate_multi_threading(bool check_figures_color)
{
    int iterations = rows;
    int num_threads = rows / 2;

    std::vector<bool> results(iterations, false);

    std::thread threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        int start = i * (iterations / num_threads);
        int end = (i + 1) * (iterations / num_threads);

        if (i == num_threads - 1)
        {
            end = iterations;
        }

        threads[i] = std::thread([this, check_figures_color, start, end, &res = results]() {
            this->is_stalemate(check_figures_color, start, end, res);
        });
    }

    for (int i = 0; i < num_threads; i++)
    {
        threads[i].join();
    }

    for (int i = 0; i < iterations; i++)
    {
        if (!results[i])
            return false;
    }

    return true;
}
