#ifndef GAME_CHESS_FIGURESMATRIX_H
#define GAME_CHESS_FIGURESMATRIX_H

#include "Figure.h"

class FiguresMatrix {

private:
    const std::string disposition[8][8] = {
            "rB", "kB", "bB", "qB", "KB", "bB", "kB", "rB",
            "pB", "pB", "pB", "pB", "pB", "pB", "pB", "pB",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "pW", "pW", "pW", "pW", "pW", "pW", "pW", "pW",
            "rW", "kW", "bW", "qW", "KW", "bW", "kW", "rW"
    };

    Figure ***matrix;

public:
    FiguresMatrix();

    void set_start_disposition();
    void set_figure(Figure &figure, int position);
    void move_figure(int from_position, int move_position);

    bool can_do_move(int from_position, int move_position);

    int find_figure(Figure *figure) const;

    Figure *get_figure(int position);

    void print_debug() const;

    void free_memory();

    ~FiguresMatrix();

};


#endif //GAME_CHESS_FIGURESMATRIX_H
