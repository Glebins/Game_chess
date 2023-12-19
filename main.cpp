#include <iostream>

#include "Tools/Controller.h"

#include "View/Field.h"
#include "Util/FiguresMatrix.h"

int main()
{
    std::string name_whites = "James";
    std::string name_blacks = "Robert";
    int rating_whites = 100;
    int rating_blacks = 130;

    FiguresMatrix fm(8, 8);
    Field view_field(fm);
    Controller game(fm, view_field, name_whites, name_blacks,
                    rating_whites, rating_blacks);

    game.run();

    game.print_debug();

    return 0;
}
