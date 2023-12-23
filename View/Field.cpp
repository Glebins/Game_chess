#include "Field.h"

Field::Field(sf::RenderWindow &window1, FiguresMatrix &matrix) : game_field(matrix), window(window1)
{ }

// Field::Field(Field &&old_field) : game_field(old_field.game_field) { }

void Field::create_window()
{
    window.create(sf::VideoMode(window_width, window_height), "Chess");

    window.clear();
    draw_disposition();
    window.display();

    while (window.isOpen())
    {
        listen_mouse_click();
    }
}

void Field::draw_disposition()
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

            Figure *current_figure = game_field.get_figure(rows * i + j);

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

void Field::listen_mouse_click()
{
    sf::Event event {};
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            window.close();
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                check_mouse_click(event);
            }
        }
    }
}

void Field::check_mouse_click(sf::Event event)
{
    int cell_width = window_width / cols;
    int cell_height = window_height / rows;
    int x_board = (int) ((double) event.mouseButton.x / ((double) cell_width));
    int y_board = (int) ((double) event.mouseButton.y / ((double) cell_height));

    // Controller().button_is_pressed();

    /* Figure* current_figure = game_field.get_figure(y_board * 8 + x_board);

    if (current_figure != nullptr)
        draw_accessible_moves(x_board, y_board, cell_width); */
}

void Field::draw_accessible_moves(int x_board, int y_board, double cell_size)
{
    int tmp = x_board;
    x_board = y_board;
    y_board = tmp;

    Figure *current_figure = game_field.get_figure(8 * x_board + y_board);

    window.clear();
    draw_disposition();

    for (int i = 0; i < game_field.get_rows(); i++)
    {
        for (int j = 0; j < game_field.get_cols(); j++)
        {
            if (i == y_board and j == x_board)
                continue;

            if (!game_field.can_do_move(8 * y_board + x_board, 8 * i + j))
                continue;

            double radius = cell_size / 5.0;
            sf::CircleShape circle((float) radius);
            circle.setFillColor(sf::Color(101, 163, 7, 200));

            double cell_center_x = cell_size * (j + 1.0 / 2) - radius;
            double cell_center_y = cell_size * (i + 1.0 / 2) - radius;

            circle.setPosition(sf::Vector2f((float) cell_center_x, (float) cell_center_y));

            window.draw(circle);
        }
    }

    double radius = cell_size / 3.0;
    sf::CircleShape circle((float) radius);
    circle.setFillColor(sf::Color(250, 0, 250, 128));

    double cell_center_x = cell_size * (x_board + 1.0 / 2) - radius;
    double cell_center_y = cell_size * (y_board + 1.0 / 2) - radius;

    circle.setPosition(sf::Vector2f((float) cell_center_x, (float) cell_center_y));

    window.draw(circle);

    window.display();
}

void Field::display_current_disposition()
{
    window.clear();
    draw_disposition();
    window.display();
}

void Field::print_debug()
{
    game_field.print();
}

FiguresMatrix& Field::get_figures_matrix()
{
    return game_field;
}
