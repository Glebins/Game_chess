#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H

#include <SFML/Graphics.hpp>

#include "../Tools/Controller.h"
#include "../Util/FiguresMatrix.h"

class Field {

private:
    const int rows = 8;
    const int cols = 8;
    const int window_width = 800;
    const int window_height = 800;

    FiguresMatrix &game_field;
    sf::RenderWindow &window;

public:
    // Field(Field&&);
    Field(sf::RenderWindow &window, FiguresMatrix &matrix);

    // void set_matrix(FiguresMatrix &matrix);

    void create_window();
    void draw_disposition();
    void listen_mouse_click();
    void check_mouse_click(sf::Event event);

    void draw_accessible_moves(int x_board, int y_board, double cell_size);
    void display_current_disposition();

    FiguresMatrix &get_figures_matrix();

    void print_debug();

    int get_cols() const { return cols; }
    int get_rows() const { return rows; }
    int get_window_width() const { return window_width; }
    int get_window_height() const { return window_height; }
    double get_cell_size() const { return (double) window_width / rows; }

    ~Field() = default;
};


#endif //CHESS_FIELD_H
