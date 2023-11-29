#ifndef GAME_CHESS_FIGURE_H
#define GAME_CHESS_FIGURE_H

#include <iostream>
#include <cstring>
#include <vector>

class Figure {

private:
    int color;

public:
    virtual Figure symbol_to_figure(char symbol) {};
    virtual char figure_to_symbol(Figure figure) {};

    virtual std::vector<std::string> array_moves(Figure figure, std::string position) {};
    virtual bool can_do_move(Figure figure, std::string position, std::string move) {};

    virtual std::string get_name_of_figure() {};

};

class King : Figure {

public:
    Figure symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figure figure) override;

    std::vector<std::string> array_moves(Figure figure, std::string position) override;
    bool can_do_move(Figure figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "King"; }

};

class Queen : Figure {

public:
    Figure symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figure figure) override;

    std::vector<std::string> array_moves(Figure figure, std::string position) override;
    bool can_do_move(Figure figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Queen"; }

};

class Rook : Figure {

public:
    Figure symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figure figure) override;

    std::vector<std::string> array_moves(Figure figure, std::string position) override;
    bool can_do_move(Figure figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Rook"; }

};

class Bishop : Figure {

public:
    Figure symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figure figure) override;

    std::vector<std::string> array_moves(Figure figure, std::string position) override;
    bool can_do_move(Figure figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Bishop"; }

};

class Knight : Figure {

public:
    Figure symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figure figure) override;

    std::vector<std::string> array_moves(Figure figure, std::string position) override;
    bool can_do_move(Figure figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Knight"; }

};

class Pawn : Figure {

public:
    Figure symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figure figure) override;

    std::vector<std::string> array_moves(Figure figure, std::string position) override;
    bool can_do_move(Figure figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Pawn"; }

};


#endif // GAME_CHESS_FIGURE_H