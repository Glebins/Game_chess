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

    // sf::RenderWindow window(sf::VideoMode(800, 600), "Chess");
    sf::RenderWindow window;

    FiguresMatrix fm(8, 8);
    Field view_field(window, fm);
    Model model(view_field, name_whites, name_blacks,
                rating_whites, rating_blacks);
    Controller game(window, view_field, model);

    game.run();
    // view_field.draw_field();

    // game.print_debug();

    return 0;
}
