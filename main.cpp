#include <iostream>

#include "Tools/Figure.h"
#include "Tools/Player.h"
#include "Tools/Controller.h"

#include "View/Field.h"

int main()
{
    std::string name_whites = "James";
    std::string name_blacks = "Robert";
    int rating_whites = 100;
    int rating_blacks = 130;

    Controller game(name_whites, name_blacks,
                    rating_whites, rating_blacks);

    /* int x0s[] = { 6, 1, 7, 1, 5, 0 };
    int y0s[] = { 0, 0, 0, 1, 0, 1 };
    int x1s[] = { 4, 2, 5, 2, 5, 2 };
    int y1s[] = { 0, 0, 0, 1, 7, 0 };

    int k = 0;

    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++; */

    game.print_debug();

    game.create_window_debug();

    return 0;
}
