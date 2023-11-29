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

    game.print_debug();

    int x0 = 7;
    int y0 = 6;
    int x1 = 5;
    int y1 = 7;

    // 62, 47

    game.make_move(8 * x0 + y0, 8 * x1 + y1);

    game.print_debug();

    return 0;
}
