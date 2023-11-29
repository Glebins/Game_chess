#ifndef GAME_CHESS_FIGURE_H
#define GAME_CHESS_FIGURE_H

#include <iostream>
#include <cstring>
#include <vector>

#include "Player.h"

const int rows = 8;
const int cols = 8;

class Figure {

private:
    int color;

protected:
    static bool is_position_valid(int x, int y);
    static int create_position(int x, int y);

public:
    virtual Figure* symbol_to_figure(std::string symbol);
    virtual char figure_to_symbol(Figure figure) {};

    virtual std::vector<int> array_moves(Figure *figure, int position) {};
    bool can_do_move(Figure *figure, int position, int move_position);

    virtual std::string get_name_of_figure() { return "Unknown"; };
    [[nodiscard]] int get_color() const { return color; }

};

class King : public Figure {

public:
    char figure_to_symbol(Figure figure) override;

    std::vector<int> array_moves(Figure *figure, int position) override;

    std::string get_name_of_figure() override { return "King"; }

};

class Queen : public Figure {

public:
    char figure_to_symbol(Figure figure) override;

    std::vector<int> array_moves(Figure *figure, int position) override;

    std::string get_name_of_figure() override { return "Queen"; }

};

class Rook : public Figure {

public:
    char figure_to_symbol(Figure figure) override;

    std::vector<int> array_moves(Figure *figure, int position) override;

    std::string get_name_of_figure() override { return "Rook"; }

};

class Bishop : public Figure {

public:
    char figure_to_symbol(Figure figure) override;

    std::vector<int> array_moves(Figure *figure, int position) override;

    std::string get_name_of_figure() override { return "Bishop"; }

};

class Knight : public Figure {

public:
    char figure_to_symbol(Figure figure) override;

    std::vector<int> array_moves(Figure *figure, int position) override;

    std::string get_name_of_figure() override { return "Knight"; }

};

class Pawn : public Figure {

public:
    char figure_to_symbol(Figure figure) override;

    std::vector<int> array_moves(Figure *figure, int position) override;

    std::string get_name_of_figure() override { return "Pawn"; }

};


#endif // GAME_CHESS_FIGURE_H