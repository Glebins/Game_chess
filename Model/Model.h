#ifndef CHESS_MODEL_H
#define CHESS_MODEL_H

#include <sstream>

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Figure.h"

#include "../Util/FiguresMatrix.h"
#include "../View/Field.h"

using namespace sf;

class Field;

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

struct {
    int x_board;
    int y_board;
    int color;
} ActivatedFigure;

class Model {

private:
    States state;
    Situations situation;

    Player player_whites;
    Player player_blacks;

    int number_moves;
    std::string game_history;

    FiguresMatrix &game_field;
    Field &view_field;

    void handle_press_with_figure_activated(int x_board, int y_board);
    void handle_press_without_figure_activated(int x_board, int y_board);

    bool is_figure_activated;

    // std::pair<Player, Figure> get_figure_by_position(std::string position);

public:

    Model(Field &view_field, std::string player_whites_name, std::string player_blacks_name,
          int rating_player_whites, int rating_player_blacks);

    States get_state() const;
    std::string get_game_history() const;
    Situations get_situation() const;

    void set_game_history(std::string game_history_from_file);
    void restart();

    Player get_player_whites();
    Player get_player_blacks();

    void make_move(int from, int to);
    void handle_mouse_press(int x_board, int y_board);

    void draw_situation_if_needed(bool current_move_color);

    void process_drawing();
    void analyze_the_board(bool color);
    void print_situation();

};


#endif //CHESS_MODEL_H
