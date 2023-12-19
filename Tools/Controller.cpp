#include "Controller.h"

#include <utility>

std::pair<Player, Figure> Controller::get_figure_by_position(std::string position)
{
    // pass
    return {};
}

Controller::Controller(FiguresMatrix& fm, Field &f, std::string name_player_whites, std::string name_player_blacks,
                       int rating_player_whites, int rating_player_blacks) : game_field(fm),
                       field_view(f)
{
    player_blacks.set_name(std::move(name_player_blacks));
    player_blacks.set_rating(rating_player_blacks);
    player_whites.set_name(std::move(name_player_whites));
    player_whites.set_rating(rating_player_whites);

    state = States::move_whites;
    game_field.set_start_disposition();
    game_history = "";

    field_view.create_window();
}

// Controller::Controller(std::string path) : game_field(0, 0) { }

void Controller::start_new_game()
{
    game_field.free_memory();
    game_field.set_start_disposition();
    state = States::move_whites;
    game_history = "";
}

void Controller::make_move(int from, int to)
{
    Figure *figure_from_position = game_field.get_figure(from);

    if ((state == States::move_whites and figure_from_position->get_color() == 0) or
            (state == States::move_blacks and figure_from_position->get_color() == 1))
    {
        std::cout << "\nmake move\n";
        game_field.move_figure(from, to);
        field_view.display_current_disposition();

        if (state == States::move_whites)
            state = States::move_blacks;
        else if (state == States::move_blacks)
            state = States::move_whites;
    }
}

void Controller::button_is_pressed(int x_board, int y_board, int cell_size)
{
    Figure* current_figure = game_field.get_figure(y_board * 8 + x_board);

    if (current_figure != nullptr and ((current_figure->get_color() == 1 and state == States::move_blacks) or
                                       (current_figure->get_color() == 0 and state == States::move_whites)))
        field_view.draw_accessible_moves(x_board, y_board, cell_size);
}

States Controller::get_state() const
{
    return state;
}

std::string Controller::get_game_history() const
{
    return game_history;
}


void Controller::print_debug() const
{
    game_field.print();
}

/* void Controller::create_window_debug() const
{
    Field f((FiguresMatrix &) game_field);
    f.create_window();
} */
