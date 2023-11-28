#include "Controller.h"

#include <utility>

std::pair<Player, Figures> Controller::get_figure_by_position(std::string position)
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
    game_field = nullptr;
    game_history = "";
}

Controller::Controller(std::string path)
{
    // parse path
}

void Controller::start_new_game()
{
    // game_field -> starting position
    state = States::move_whites;
    game_history = "";
}

void Controller::make_move(std::string move)
{

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
