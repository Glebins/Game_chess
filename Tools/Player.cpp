#include "Player.h"

int Player::get_elapsed_time()
{
    return elapsed_time;
}

void Player::set_start_time()
{
    elapsed_time = game_time;
}

std::string Player::get_name()
{
    return player_name;
}

void Player::set_name(std::string name)
{
    player_name = name;
}

int Player::get_rating()
{
    return player_rating;
}

void Player::set_rating(int rating)
{
    player_rating = rating;
}



