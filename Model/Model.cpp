#include "Model.h"
#include <utility>

Model::Model(Field &view_field1, std::string player_whites_name, std::string player_blacks_name, int player_whites_rating,
             int player_blacks_rating) : view_field(view_field1), game_field(view_field1.get_figures_matrix())
{
    player_blacks.set_name(std::move(player_blacks_name));
    player_blacks.set_rating(player_blacks_rating);
    player_whites.set_name(std::move(player_whites_name));
    player_whites.set_rating(player_whites_rating);

    state = States::move_whites;
    situation = Situations::nothing;

    is_figure_activated = false;

    number_moves = 0;
    game_history = "";
}

void Model::restart()
{
    state = States::move_whites;
    situation = Situations::nothing;

    is_figure_activated = false;

    number_moves = 0;
    game_history = "";
}

States Model::get_state() const
{
    return state;
}

Situations Model::get_situation() const
{
    return situation;
}

std::string Model::get_game_history() const
{
    return game_history;
}

void Model::make_move(int from, int to)
{
    Figure *figure_from_position = game_field.get_figure(from);
    Figure *figure_on_new_position = game_field.get_figure(to);

    if ((state == States::move_whites and figure_from_position->get_color() == 0) or
        (state == States::move_blacks and figure_from_position->get_color() == 1))
    {
        try {
            game_field.move_figure(from, to);
        }
        catch (std::logic_error &e) {
            std::cout << "can't\n";
            return;
        }

        if (figure_on_new_position != nullptr and figure_on_new_position->figure_to_symbol() == 'k')
            state = States::game_over;

        std::cout << "\nmake move\n";
        process_drawing();

        int row_to = 8 - to / 8;
        char col_to = to % 8 + 'a';
        int row_from = 8 - from / 8;
        char col_from = from % 8 + 'a';

        if (state == States::move_whites)
        {
            game_history += (number_moves != 0 ? "\n" : "") + std::to_string(number_moves / 2 + 1) + ". ";
            state = States::move_blacks;
        }

        else if (state == States::move_blacks)
        {
            game_history += " ";
            state = States::move_whites;
        }

        game_history += figure_from_position->figure_to_symbol();
        game_history += col_from + std::to_string(row_from) + "," + col_to + std::to_string(row_to);

        number_moves++;

        is_figure_activated = false;
    }
}

void Model::handle_mouse_press(int x_board, int y_board)
{
    if (!is_figure_activated)
        handle_press_without_figure_activated(x_board, y_board);
    else
        handle_press_with_figure_activated(x_board, y_board);
}

void Model::handle_press_without_figure_activated(int x_board, int y_board)
{
    Figure* current_figure = game_field.get_figure(x_board * 8 + y_board);

    if (current_figure != nullptr)
    {
        if ((current_figure->get_color() == 1 and state == States::move_whites) or
            (current_figure->get_color() == 0 and state == States::move_blacks))
            return;

        // view_field.draw_accessible_moves(x_board, y_board, view_field.get_cell_size());
        // view_field.draw_move((state == States::move_whites) ? 0 : 1);
        bool color_move = (state == States::move_whites) ? 0 : 1;
        view_field.display_accessible_moves_and_side_panel(x_board, y_board, view_field.get_cell_size(),
                                                           color_move);
        is_figure_activated = true;

        std::cout << "\n-----------------------\n" << x_board << " " << y_board << " " <<
            current_figure->get_name_of_figure() << " " << current_figure->get_color() << "\n--------------\n";

        ActivatedFigure.x_board = x_board;
        ActivatedFigure.y_board = y_board;
        ActivatedFigure.color = current_figure->get_color();
    }
}

void Model::handle_press_with_figure_activated(int x_board, int y_board)
{
    int pos_from = ActivatedFigure.x_board * 8 + ActivatedFigure.y_board;
    int pos_to = x_board * 8 + y_board;

    Figure *old_pos_figure = game_field.get_figure(pos_from);
    Figure *new_pos_figure = game_field.get_figure(pos_to);

    if (new_pos_figure != nullptr and new_pos_figure->get_color() == old_pos_figure->get_color())
    {
        handle_press_without_figure_activated(x_board, y_board);
        return;
    }

    make_move(pos_from, pos_to);
}

void Model::set_game_history(std::string game_history_from_file)
{
    game_field.delete_all_figures();
    game_field.set_start_disposition();
    state = States::move_whites;
    situation = Situations::nothing;
    game_history = std::move(game_history_from_file);

    std::istringstream iss(game_history);
    std::string line;

    while (std::getline(iss, line, '\n'))
    {
        if (line.empty())
            continue;

        size_t first_space = line.find(' ');
        size_t last_space = line.rfind(' ');

        if (first_space == last_space)
        {
            std::string move = line.substr(first_space + 1);

            int col_from = move[1] - 'a';
            int row_from = 8 - (move[2] - '0');

            int col_to = move[4] - 'a';
            int row_to = 8 - (move[5] - '0');

            make_move(8 * row_from + col_from, 8 * row_to + col_to);
        }

        else
        {
            std::string move_1 = line.substr(first_space + 1, last_space - first_space - 1);
            std::string move_2 = line.substr(last_space + 1);

            int w_col_from = move_1[1] - 'a';
            int w_row_from = 8 - (move_1[2] - '0');

            int w_col_to = move_1[4] - 'a';
            int w_row_to = 8 - (move_1[5] - '0');

            int b_col_from = move_2[1] - 'a';
            int b_row_from = 8 - (move_2[2] - '0');

            int b_col_to = move_2[4] - 'a';
            int b_row_to = 8 - (move_2[5] - '0');

            make_move(8 * w_row_from + w_col_from, 8 * w_row_to + w_col_to);
            make_move(8 * b_row_from + b_col_from, 8 * b_row_to + b_col_to);
        }
    }
}

Player Model::get_player_blacks()
{
    return player_blacks;
}

Player Model::get_player_whites()
{
    return player_whites;
}





void Model::analyze_the_board(bool color)
{
    if (game_field.is_check(color))
    {
        if (game_field.is_checkmate(color))
        {
            situation = Situations::checkmate;
            state = States::game_over;
        }

        else
        {
            situation = Situations::check;
        }
    }

    else
    {
        if (game_field.is_stalemate(color))
        {
            situation = Situations::stalemate;
            state = States::game_over;
        }
        else
            situation = Situations::nothing;
    }
}

void Model::print_situation()
{
    std::cout << "\nSituation = ";

    switch (situation)
    {
        case Situations::nothing:
            std::cout << "nothing";
            break;

        case Situations::check:
            std::cout << "check";
            break;

        case Situations::checkmate:
            std::cout << "checkmate";
            break;

        case Situations::stalemate:
            std::cout << "stalemate";
            break;
    }

    std::cout << "\n";
}


void Model::draw_situation_if_needed(bool current_move_color)
{
    bool color = (state == States::move_whites) ? 1 : 0;

    analyze_the_board(color);
    Situations sit_1 = situation;

    analyze_the_board(!color);
    Situations sit_2 = situation;

    if (sit_1 == Situations::stalemate or sit_2 == Situations::stalemate)
    {
        situation = Situations::stalemate;

        view_field.draw_stalemate();
    }

    else if (sit_1 == Situations::checkmate or sit_2 == Situations::checkmate)
    {
        situation = Situations::checkmate;

        view_field.draw_checkmate((sit_1 == Situations::checkmate) == (color));
    }

    else if (sit_1 == Situations::check or sit_2 == Situations::check)
    {
        situation = Situations::check;

        view_field.draw_check((sit_1 == Situations::check) == (color));
    }
}


void Model::process_drawing()
{
    bool next_move_color = (state == States::move_whites) ? 1 : 0;

    view_field.clear_screen();

    view_field.display_current_disposition(next_move_color);
    draw_situation_if_needed(next_move_color);

    if (state == States::game_over)
        view_field.draw_game_over();

    view_field.display_elements();
}
