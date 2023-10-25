#ifndef GAME_CHESS_FIGURES_H
#define GAME_CHESS_FIGURES_H

#include <iostream>
#include <cstring>
#include <vector>

enum class List_figures {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

class Figures {

public:
    static List_figures symbol_to_figure(char symb);
    static char figure_to_symbol(List_figures figure);

    static std::vector<std::string> array_moves(List_figures figure, std::string position);
    static bool can_do_move(List_figures figure, std::string position, std::string move);

    static std::string get_name_of_figure(List_figures figure);

};


#endif // GAME_CHESS_FIGURES_H
