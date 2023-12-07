#include "Field.h"

void Field::create_window(FiguresMatrix &matrix)
{
    window.create(sf::VideoMode(window_width, window_height), "Chess");

    window.clear();
    draw_disposition(matrix);
    window.display();

    while (window.isOpen())
    {
        check_mouse_click(matrix);
    }

    /* while (window.isOpen())
    {
        // window.clear();
        // window.display();

        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                check_mouse_click();
        }

    } */
}

void Field::draw_disposition(FiguresMatrix& matrix)
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

            sf::Texture figure_texture;
            std::string path = "../Pictures/" + current_figure->get_name_of_figure() + ".png";

            figure_texture.loadFromFile(path);

            sf::Sprite figure_sprite;
            figure_sprite.setTexture(figure_texture);
            double coefficient = (!std::strcmp(current_figure->get_name_of_figure().c_str(), "King") or
                    !std::strcmp(current_figure->get_name_of_figure().c_str(), "Queen") or
                    !std::strcmp(current_figure->get_name_of_figure().c_str(), "Knight")) ? 0.8 : 1;
            figure_sprite.setScale((float) cell_width / figure_texture.getSize().x * coefficient,
                                   (float) cell_height / figure_texture.getSize().y * coefficient);
            double x_pose = (1 - coefficient) * cell_width / 2 + start_x;
            double y_pose = (1 - coefficient) * cell_height / 2 + start_y;
            figure_sprite.setPosition((float) x_pose, (float) y_pose);

            if (current_figure->get_color() == 1)
                figure_sprite.setColor(sf::Color::Black);
            else
                figure_sprite.setColor(sf::Color::White);

            window.draw(figure_sprite);
        }
    }
}

void Field::check_mouse_click(FiguresMatrix &matrix)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                int cell_width = window_width / cols;
                int cell_height = window_height / rows;
                int x_board = (int) ((double) event.mouseButton.x / ((double) cell_width));
                int y_board = (int) ((double) event.mouseButton.y / ((double) cell_height));

                Figure* current_figure = matrix.get_figure(x_board * 8 + y_board);

                int cell_size = cell_width;
                double radius = cell_size / 3.0;
                sf::CircleShape circle(radius);
                circle.setFillColor(sf::Color::Red);

                double cell_center_x = cell_size * (x_board + 1.0 / 2) - radius;
                double cell_center_y = cell_size * (y_board + 1.0 / 2) - radius;

                circle.setPosition(sf::Vector2f(cell_center_x, cell_center_y));

                window.clear();
                draw_disposition(matrix);
                window.draw(circle);
                window.display();
            }
        }
    }
}

void Field::draw_accessible_moves(FiguresMatrix &matrix, int x_board, int y_board, int cell_size)
{
    double radius = cell_size / 3.0;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Red);

    double cell_center_x = cell_size * (x_board + 1.0 / 2) - radius;
    double cell_center_y = cell_size * (y_board + 1.0 / 2) - radius;

    circle.setPosition(sf::Vector2f(cell_center_x, cell_center_y));

    window.clear();
    draw_disposition(matrix);
    window.draw(circle);
    window.display();
}

