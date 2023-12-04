#include "Controller.h"

#include <utility>

std::pair<Player, Figure> Controller::get_figure_by_position(std::string position)
{
    // pass
    return {};
}

Controller::Controller(std::string name_player_whites, std::string name_player_blacks, int rating_player_whites,
                       int rating_player_blacks)
{
    player_blacks.set_name(std::move(name_player_blacks));
    player_blacks.set_rating(rating_player_blacks);
    player_whites.set_name(std::move(name_player_whites));
    player_whites.set_rating(rating_player_whites);

    state = States::move_whites;
    game_field.set_start_disposition();
    game_history = "";
}

Controller::Controller(std::string path)
{
    // parse path
}

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

        if (state == States::move_whites)
            state = States::move_blacks;
        else if (state == States::move_blacks)
            state = States::move_whites;
    }
}

void Controller::save_game_to_file(std::string path)
{

}

void Controller::load_game_from_file(std::string path)
{

}

States Controller::get_state() const
{
    return state;
}

Situations Controller::get_situation() const
{
    // check situation

    return {};
}

std::string Controller::get_game_history() const
{
    return game_history;
}


void Controller::print_debug() const
{
    game_field.print_debug();
}

void Controller::create_window_debug() const
{
    Field f;
    f.create_window((FiguresMatrix &) game_field);
}
