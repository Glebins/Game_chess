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

    is_figure_activated = false;

    number_moves = 0;
    game_history = "";
}

States Model::get_state() const
{
    return state;
}

std::string Model::get_game_history() const
{
    return game_history;
}

void Model::make_move(int from, int to)
{
    Figure *figure_from_position = game_field.get_figure(from);

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

        std::cout << "\nmake move\n";
        view_field.display_current_disposition();

        int row = 8 - to / 8;
        char col = to % 8 + 'a';

        if (state == States::move_whites)
        {
            game_history += "\n" + std::to_string(number_moves / 2 + 1);
            state = States::move_blacks;
        }

        else if (state == States::move_blacks)
        {
            game_history += " ";
            state = States::move_whites;
        }

        game_history += figure_from_position->figure_to_symbol();
        game_history += col + std::to_string(row);

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

        view_field.draw_accessible_moves(x_board, y_board, view_field.get_cell_size());
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
