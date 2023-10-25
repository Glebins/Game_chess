#ifndef GAME_CHESS_PLAYER_H
#define GAME_CHESS_PLAYER_H

#include <iostream>
#include <cstring>

#include "Figures.h"

class Player {

private:
    int elapsed_time;

    int rating;
    std::string player_name;

public:
    int get_elapsed_time();

};


#endif // GAME_CHESS_PLAYER_H
