#ifndef GAME_CHESS_CONTROLLER_H
#define GAME_CHESS_CONTROLLER_H

#include "Player.h"
#include "Clock.h"

class Controller {

private:
    bool is_whites_move;

    Player player_whites;
    Player player_blacks;

    Clock clock;

};


#endif //GAME_CHESS_CONTROLLER_H
