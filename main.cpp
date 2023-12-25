#include <iostream>

#include "Tools/Controller.h"

#include "View/Field.h"
#include "Util/FiguresMatrix.h"

#include "Util/Matrix.h"

int main()
{
    std::string name_whites = "James";
    std::string name_blacks = "Robert";
    int rating_whites = 100;
    int rating_blacks = 130;

    // sf::RenderWindow window(sf::VideoMode(800, 600), "Chess");
    sf::RenderWindow window;

    FiguresMatrix fm(8, 8);
    Field view_field(window, fm, name_whites, name_blacks);
    Model model(view_field, name_whites, name_blacks,
                rating_whites, rating_blacks);
    Controller game(window, view_field, model);

    game.run();

    /* Matrix<int> m(3, 3);

    int value = 1;
    for (auto row = m.begin(); row != m.end(); ++row) {
        for (size_t col = 0; col < m.get_cols(); ++col) {
            (*row)[col] = value++;
        }
    }

    // Print the matrix
    for (auto row : m) {
        for (size_t col = 0; col < m.get_cols(); ++col) {
            std::cout << row[col] << ' ';
        }
        std::cout << std::endl;
    }

    Matrix<int> m1 = m.transpose();

    m1.print(); */


    /* for (int i = 0; i < m.get_rows(); ++i) {
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

    std::cout << m.find_element(2) << "\n\n"; */

    return 0;
}
