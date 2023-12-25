#ifndef CHESS_FIELD_H
#define CHESS_FIELD_H

#include <SFML/Graphics.hpp>

#include "../Tools/Controller.h"
#include "../Util/FiguresMatrix.h"

class Field {

private:
    const int rows = 8;
    const int cols = 8;
    const int window_width = 1200;
    const int window_height = 800;
    const int board_width = 800;
    const int board_height = 800;
    const sf::Color background_color = sf::Color(84, 57, 31);

    std::string player_1_name;
    std::string player_2_name;

    FiguresMatrix &game_field;
    sf::RenderWindow &window;

public:
    // Field(Field&&);
    Field(sf::RenderWindow &window, FiguresMatrix &matrix, std::string player_1_name1, std::string player_2_name1);

    // void set_matrix(FiguresMatrix &matrix);

    void draw_side_panel(bool color);
    void create_window();
    void draw_disposition();
    void listen_mouse_click();
    void check_mouse_click(sf::Event event);

    void draw_accessible_moves(int x_board, int y_board, double cell_size);
    void display_accessible_moves_and_side_panel(int x_board, int y_board, double cell_size, bool color);
    void display_current_disposition(bool color);

    FiguresMatrix &get_figures_matrix();

    void print_debug();
    void draw_check(bool color_win);
    void draw_checkmate(bool color_win);
    void draw_stalemate();
    void draw_game_over();

    void clear_screen();
    void display_elements();

    int get_cols() const { return cols; }
    int get_rows() const { return rows; }
    int get_window_width() const { return window_width; }
    int get_window_height() const { return window_height; }
    int get_board_width() const { return board_width; }
    int get_board_height() const { return board_height; }
    double get_cell_size() const { return (double) board_width / rows; }
    sf::Color get_background_color() const { return background_color; }

    ~Field() = default;
};


#endif //CHESS_FIELD_H
