#include <iostream>

#include "Tools/Figures.h"

int main()
{
    int x = 0xA;
    std::cout << x;

    Pawn p;

    std::cout << std::endl << p.get_name_of_figure();

    return 0;
}
