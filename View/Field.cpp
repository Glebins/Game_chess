#include "Field.h"

#include <utility>

Field::Field(sf::RenderWindow &window1, FiguresMatrix &matrix, std::string player_1_name1,
             std::string player_2_name1) : game_field(matrix), window(window1), player_1_name(std::move(player_1_name1)),
             player_2_name(std::move(player_2_name1))
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
    int cell_width = board_width / cols;
    int cell_height = board_height / rows;

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
    int cell_width = board_width / cols;
    int cell_height = board_height / rows;
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

    // window.clear(background_color);
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

    // window.display();
}

void Field::display_current_disposition(bool color)
{
    draw_disposition();
    draw_side_panel(color);
}

void Field::print_debug()
{
    game_field.print();
}

FiguresMatrix& Field::get_figures_matrix()
{
    return game_field;
}

void Field::draw_side_panel(bool color)
{
    sf::Color color_circle = (color) ? sf::Color::Black : sf::Color::White;

    double radius = (window_width - board_width) * 0.1;

    sf::CircleShape move_circle(radius);
    move_circle.setFillColor(color_circle);
    move_circle.setPosition(board_width + radius * 4 / 5, radius * 2);

    sf::Text move_label;
    sf::Font font;
    font.loadFromFile("../Pictures/arial.ttf");

    move_label.setCharacterSize(50);
    move_label.setFont(font);
    move_label.setFillColor(sf::Color::White);
    move_label.setString("Move");
    move_label.setPosition(board_width + radius * 19 / 5, radius * 2);

    std::string players_poster = player_1_name + " vs " + player_2_name;

    sf::Text players;
    players.setCharacterSize(20);
    players.setFont(font);
    players.setFillColor(sf::Color::White);
    players.setString(players_poster);
    players.setPosition(board_width + radius * 4 / 5, radius * 5);

    window.draw(move_circle);
    window.draw(move_label);
    window.draw(players);
}

void Field::display_accessible_moves_and_side_panel(int x_board, int y_board, double cell_size, bool color)
{
    window.clear(background_color);

    draw_accessible_moves(x_board, y_board, cell_size);
    draw_side_panel(color);

    window.display();
}

void Field::draw_check(bool color_win)
{
    sf::Text check_label;
    sf::Font font;
    font.loadFromFile("../Pictures/arial.ttf");

    double radius = (window_width - board_width) * 0.1;

    std::string label = ((color_win) ? "Blacks" : "Whites");
    label += " checked";

    check_label.setCharacterSize(40);
    check_label.setFont(font);
    check_label.setFillColor(sf::Color::White);
    check_label.setString(label);
    check_label.setPosition(board_width + radius * 4 / 5, radius * 7);

    window.draw(check_label);
}

void Field::draw_checkmate(bool color_win)
{
    sf::Text checkmate_label;
    sf::Font font;
    font.loadFromFile("../Pictures/arial.ttf");

    double radius = (window_width - board_width) * 0.1;

    std::string label = ((color_win) ? "Blacks" : "Whites");
    label += " checkmated";

    checkmate_label.setCharacterSize(40);
    checkmate_label.setFont(font);
    checkmate_label.setFillColor(sf::Color::White);
    checkmate_label.setString(label);
    checkmate_label.setPosition(board_width + radius * 4 / 5, radius * 7);

    window.draw(checkmate_label);
}

void Field::draw_stalemate()
{
    sf::Text stalemate_label;
    sf::Font font;
    font.loadFromFile("../Pictures/arial.ttf");

    double radius = (window_width - board_width) * 0.1;

    std::string label = "There is a stalemate";

    stalemate_label.setCharacterSize(40);
    stalemate_label.setFont(font);
    stalemate_label.setFillColor(sf::Color::White);
    stalemate_label.setString(label);
    stalemate_label.setPosition(board_width + radius * 4 / 5, radius * 7);

    window.draw(stalemate_label);
}

void Field::draw_game_over()
{
    sf::Text game_over;
    sf::Font font;
    font.loadFromFile("../Pictures/arial.ttf");

    double radius = (window_width - board_width) * 0.1;

    std::string label = "Game over";

    game_over.setCharacterSize(50);
    game_over.setFont(font);
    game_over.setFillColor(sf::Color::Magenta);
    game_over.setString(label);
    game_over.setPosition(board_width + radius * 4 / 5, radius * 10);

    window.draw(game_over);
}

void Field::clear_screen()
{
    window.clear(background_color);
}

void Field::display_elements()
{
    window.display();
}
