#ifndef GAME_CHESS_FIGURES_H
#define GAME_CHESS_FIGURES_H

#include <iostream>
#include <cstring>
#include <vector>

class Figures {

private:
    int color;

public:
    virtual Figures symbol_to_figure(char symbol);
    virtual char figure_to_symbol(Figures figure);

    virtual std::vector<std::string> array_moves(Figures figure, std::string position);
    virtual bool can_do_move(Figures figure, std::string position, std::string move);

    virtual std::string get_name_of_figure();

};

class King : Figures {

public:
    Figures symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figures figure) override;

    std::vector<std::string> array_moves(Figures figure, std::string position) override;
    bool can_do_move(Figures figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "King"; }

};

class Queen : Figures {

public:
    Figures symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figures figure) override;

    std::vector<std::string> array_moves(Figures figure, std::string position) override;
    bool can_do_move(Figures figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Queen"; }

};

class Rook : Figures {

public:
    Figures symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figures figure) override;

    std::vector<std::string> array_moves(Figures figure, std::string position) override;
    bool can_do_move(Figures figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Rook"; }

};

class Bishop : Figures {

public:
    Figures symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figures figure) override;

    std::vector<std::string> array_moves(Figures figure, std::string position) override;
    bool can_do_move(Figures figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Bishop"; }

};

class Knight : Figures {

public:
    Figures symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figures figure) override;

    std::vector<std::string> array_moves(Figures figure, std::string position) override;
    bool can_do_move(Figures figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Knight"; }

};

class Pawn : Figures {

public:
    Figures symbol_to_figure(char symbol) override;
    char figure_to_symbol(Figures figure) override;

    std::vector<std::string> array_moves(Figures figure, std::string position) override;
    bool can_do_move(Figures figure, std::string position, std::string move) override;

    std::string get_name_of_figure() override { return "Pawn"; }

};


#endif // GAME_CHESS_FIGURES_H
