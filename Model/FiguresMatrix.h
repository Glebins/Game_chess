#ifndef GAME_CHESS_FIGURESMATRIX_H
#define GAME_CHESS_FIGURESMATRIX_H

#include "../Tools/Figure.h"
#include "Matrix.h"

class FiguresMatrix : public Matrix<Figure *> {

    enum class States {
        game_over,
        move_whites,
        move_blacks,
    };

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

    // Figure ***matrix;

public:
    FiguresMatrix(int rows, int cols);

    void set_start_disposition();
    void move_figure(int from_position, int move_position);

    bool can_do_move(int from_position, int move_position);

    int find_figure(Figure *figure) const;

    Figure *get_figure(int position);

    ~FiguresMatrix() = default;

};


#endif //GAME_CHESS_FIGURESMATRIX_H
