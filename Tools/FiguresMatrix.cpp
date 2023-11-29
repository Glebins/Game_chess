#include "FiguresMatrix.h"

FiguresMatrix::FiguresMatrix()
{

}

void FiguresMatrix::set_start_disposition()
{

}

void FiguresMatrix::set_figure(Figure &figure, int position)
{

}

void FiguresMatrix::move_figure()
{

}

Figure& FiguresMatrix::get_figure(int position)
{
    Figure &ref = matrix[1][1];
    return ref;
}

FiguresMatrix::~FiguresMatrix()
{
    delete matrix;
}
