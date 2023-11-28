#include "Controller.h"

#include <utility>

Controller::Controller(std::string name_player_whites, std::string name_player_blacks, int rating_player_whites,
                       int rating_player_blacks)
{
    player_blacks.set_name(std::move(name_player_blacks));
    player_blacks.set_rating(rating_player_blacks);
    player_whites.set_name(std::move(name_player_whites));
    player_whites.set_rating(rating_player_whites);


}
