#include "Field.h"

void Field::create_window(FiguresMatrix &matrix)
{
    window.create(sf::VideoMode(window_width, window_height), "Chess");

    while (window.isOpen())
    {
        sf::Event event {};


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                window.close();
        }

        window.clear();

        draw_initial_disposition(matrix);

        window.display();
    }
}

void Field::draw_initial_disposition(FiguresMatrix& matrix)
{
    int cell_width = window_width / cols;
    int cell_height = window_height / rows;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int start_x = j * cell_width;
            int start_y = i * cell_height;

            sf::RectangleShape cell(sf::Vector2f(cell_width, cell_height));
            cell.setPosition(start_x, start_y);

            if ((i + j) % 2 == 1)
                cell.setFillColor(sf::Color(132, 86, 60));
            else
                cell.setFillColor(sf::Color(212, 184, 126));

            window.draw(cell);

            Figure *current_figure = matrix.get_figure(rows * i + j);

            if (!current_figure)
                continue;

            if (std::strcmp(current_figure->get_name_of_figure().c_str(), "Pawn") != 0)
                continue;

            sf::Texture figure_texture;
            sf::Image figure_image;
            std::string path = "../Pictures/" + current_figure->get_name_of_figure() + "_2.png";

            figure_image.loadFromFile(path);
            figure_image.createMaskFromColor(sf::Color::Magenta);
            figure_texture.loadFromImage(figure_image);

            sf::Sprite figure_sprite;
            figure_sprite.setTexture(figure_texture);
            // figure_sprite.setTextureRect(sf::IntRect(0, 0, 800, 800));
            figure_sprite.setScale((float) cell_width / figure_texture.getSize().x,
                                   (float) cell_height / figure_texture.getSize().y);
            figure_sprite.setPosition(start_x, start_y);

            figure_sprite.setColor(sf::Color(255, 255, 255, 250));

            window.draw(figure_sprite);
        }
    }
}
