#ifndef GAME_CHESS_CONTROLLER_H
#define GAME_CHESS_CONTROLLER_H

#include <iostream>
#include <cstring>

#include "Player.h"
#include "Figure.h"
#include "../Util/FiguresMatrix.h"

#include "../View/Field.h"

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

class Field;
class FiguresMatrix;

class Controller {

private:
    States state;

    Player player_whites;
    Player player_blacks;

    FiguresMatrix &game_field;
    Field &field_view;
    std::string game_history;

    std::pair<Player, Figure> get_figure_by_position(std::string position);

public:
    Controller(FiguresMatrix &fm, Field &f, std::string player_whites_name, std::string player_blacks_name,
               int rating_player_whites, int rating_player_blacks);
    // Controller(std::string path);

    void start_new_game();
    void make_move(int from, int to);
    // void save_game_to_file(std::string path);
    // void load_game_from_file(std::string path);

    States get_state() const;
    // Situations get_situation() const;

    std::string get_game_history() const;

    void button_is_pressed(int x_board, int y_board, int cell_size);

    void run() {};

    void print_debug() const;
    // void create_window_debug() const;

};


#endif // GAME_CHESS_CONTROLLER_H