#include <iostream>

#include "Tools/Figure.h"
#include "Tools/Player.h"
#include "Tools/Controller.h"

#include "View/Field.h"

#include "Model/Matrix.h"

int main()
{
    /* Matrix<int> m(3, 3);

    for (int i = 0; i < m.get_rows(); ++i) {
        for (int j = 0; j < m.get_cols(); ++j) {
            m.at(i, j) = i + j;
        }
    }

    m.add_row();

    m.at(3, 0) = 12;
    m.at(3, 1) = 13;
    m.at(3, 2) = 14;

    m.add_column();

    m.at(0, 3) = 20;
    m.at(1, 3) = 21;
    m.at(2, 3) = 22;
    m.at(3, 3) = 23;

    m.print();

    m.delete_row(1);
    m.delete_column(1);

    m.print();

    std::cout << m.find_element(2); */


    std::string name_whites = "James";
    std::string name_blacks = "Robert";
    int rating_whites = 100;
    int rating_blacks = 130;

    Controller game(name_whites, name_blacks,
                    rating_whites, rating_blacks);

    int x0s[] = { 6, 1, 7, 1, 5, 0 };
    int y0s[] = { 0, 0, 0, 1, 0, 1 };
    int x1s[] = { 4, 2, 5, 2, 5, 2 };
    int y1s[] = { 0, 0, 0, 1, 7, 0 };

    int k = 0;

    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;
    game.make_move(8 * x0s[k] + y0s[k], 8 * x1s[k] + y1s[k]); k++;

    game.print_debug();

    game.create_window_debug();

    return 0;
}
