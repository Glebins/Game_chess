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

    sf::RenderWindow window;

public:
    void create_window(FiguresMatrix &matrix);
    void draw_disposition(FiguresMatrix &matrix);
    void check_mouse_click(FiguresMatrix &matrix);
    void draw_accessible_moves(FiguresMatrix &matrix, int x_board, int y_board, int cell_size);

};


#endif //CHESS_FIELD_H
