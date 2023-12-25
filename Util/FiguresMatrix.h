#ifndef GAME_CHESS_FIGURESMATRIX_H
#define GAME_CHESS_FIGURESMATRIX_H

#include "../Model/Figure.h"
#include "Matrix.h"

class FiguresMatrix : public Matrix<Figure *> {

private:
    const std::string disposition[8][8] = {
            "rB", "nB", "bB", "qB", "kB", "bB", "nB", "rB",
            "pB", "pB", "pB", "pB", "pB", "pB", "pB", "pB",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "-", "-", "-", "-", "-", "-", "-", "-",
            "pW", "pW", "pW", "pW", "pW", "pW", "pW", "pW",
            "rW", "nW", "bW", "qW", "kW", "bW", "nW", "rW"
    };

public:
    FiguresMatrix(int rows, int cols);
    FiguresMatrix(const FiguresMatrix& fm);

    void set_start_disposition();
    void move_figure(int from_position, int move_position);
    void forcibly_move_figure(int from_position, int move_position);
    void delete_all_figures();

    std::vector<int> array_moves(int position);
    bool can_do_move(int from_position, int move_position);

    int find_figure(Figure *figure) const;
    int find_king(bool color) const;

    Figure *get_figure(int position) const;

    bool is_check(bool check_figures_color);
    bool is_checkmate(bool check_figures_color);
    bool is_stalemate(bool check_figures_color);

    ~FiguresMatrix() = default;

};


#endif //GAME_CHESS_FIGURESMATRIX_H
