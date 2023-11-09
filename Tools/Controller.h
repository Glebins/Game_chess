#ifndef GAME_CHESS_CONTROLLER_H
#define GAME_CHESS_CONTROLLER_H

#include <iostream>
#include <cstring>

#include "Player.h"
#include "Figures.h"

enum class States {
    game_over,
    move_whites,
    move_blacks,
};

enum class Situations {
    check,
    stalemate,
    checkmate,
    nothing
};

class Controller {

private:
    bool state;

    Player player_whites;
    Player player_blacks;

    char** game_field;
    std::string game_history;

    std::pair<Player, Figures> get_figure_by_position(std::string position);

public:
    Controller() = default;
    Controller(std::string path);

    void start_new_game();
    void make_move(std::string move);
    void save_game_to_file(std::string path);
    void load_game_from_file(std::string path);

    States get_state();
    Situations get_situation();

    std::string get_game_history();

};


#endif // GAME_CHESS_CONTROLLER_H
