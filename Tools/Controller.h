#ifndef GAME_CHESS_CONTROLLER_H
#define GAME_CHESS_CONTROLLER_H

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstring>

#include "tinyfiledialogs.h"
#include <fstream>

#include "../Model/Model.h"
#include "../View/Field.h"

class Field;
class FiguresMatrix;
class Model;

using namespace sf;

class Controller {

private:

    FiguresMatrix &game_field;
    Field &view_field;
    Model &model;
    RenderWindow &window;

    void process_mouse_pressing(Event event);
    void process_saving_to_file();
    std::string show_save_file_dialog();

public:
    /* Controller(FiguresMatrix &fm, Field &f, std::string player_whites_name, std::string player_blacks_name,
               int rating_player_whites, int rating_player_blacks); */
    Controller(RenderWindow &window, Field &f, Model &model);
    // Controller(std::string path);

    // void start_new_game();
    // void make_move(int from, int to);
    // void save_game_to_file(std::string path);
    // void load_game_from_file(std::string path);

    // std::string get_game_history() const;

    // void button_is_pressed(int x_board, int y_board, int cell_size);

    void run();

    void print_debug() const;
    // void create_window_debug() const;

};


#endif // GAME_CHESS_CONTROLLER_H