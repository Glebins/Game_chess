#include <iostream>

#include "Tools/Figure.h"
#include "Tools/Player.h"
#include "Tools/Controller.h"

int main()
{
    std::string name_whites = "James";
    std::string name_blacks = "Robert";
    int rating_whites = 100;
    int rating_blacks = 130;

    Controller game(name_whites, name_blacks,
                    rating_whites, rating_blacks);

    int x0s[] = { 6, 1, 7, 1, 5 };
    int y0s[] = { 0, 0, 0, 1, 0 };
    int x1s[] = { 4, 2, 5, 2, 5 };
    int y1s[] = { 0, 0, 0, 1, 7 };

    int k = 0;

    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k = 1;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k = 2;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k = 3;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k = 4;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k = 5;

    game.print_debug();

    return 0;
}
