#ifndef GAME_CHESS_FIGURESMATRIX_H
#define GAME_CHESS_FIGURESMATRIX_H

#include "Figure.h"

class FiguresMatrix {

private:
    const int rows = 8;
    const int cols = 8;
    Figure **matrix;

public:
    FiguresMatrix();

    void set_start_disposition();
    void set_figure(Figure &figure, int position);
    void move_figure();

    Figure &get_figure(int position);

    ~FiguresMatrix();

};


#endif //GAME_CHESS_FIGURESMATRIX_H
