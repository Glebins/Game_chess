#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H

#include <SFML/Graphics.hpp>

#include "../Tools/Controller.h"
#include "../Model/FiguresMatrix.h"

class Field {

private:
    const int rows = 8;
    const int cols = 8;
    const int window_width = 800;
    const int window_height = 800;

    FiguresMatrix &game_field;
    States &state;
    sf::RenderWindow window;

public:
    Field(FiguresMatrix &matrix, States &state);

    void create_window();
    void draw_disposition();
    void listen_mouse_click();
    void check_mouse_click(sf::Event event);


    void draw_accessible_moves(int x_board, int y_board, int cell_size);

    ~Field() = default;
};


#endif //CHESS_FIELD_H
