#include "Controller.h"

#include <utility>

/* Controller::Controller(FiguresMatrix& fm, Field &f, std::string name_player_whites, std::string name_player_blacks,
                       int rating_player_whites, int rating_player_blacks) : game_field(fm),
                       field_view(f)
{
    player_blacks.set_name(std::move(name_player_blacks));
    player_blacks.set_rating(rating_player_blacks);
    player_whites.set_name(std::move(name_player_whites));
    player_whites.set_rating(rating_player_whites);

    state = States::move_whites;
    game_field.set_start_disposition();
    game_history = "";

    field_view.create_window();
} */

Controller::Controller(RenderWindow &window1, Field &f, Model &model) : game_field(f.get_figures_matrix()),
view_field(f), model(model), window(window1)
{
    window.create(VideoMode(view_field.get_window_width(), view_field.get_window_height()),
                  "Chess");
}

// Controller::Controller(std::string path) : game_field(0, 0) { }

/* void Controller::start_new_game()
{
    game_field.free_memory();
    game_field.set_start_disposition();
    state = States::move_whites;
    game_history = "";
}

void Controller::make_move(int from, int to)
{
    Figure *figure_from_position = game_field.get_figure(from);

    if ((state == States::move_whites and figure_from_position->get_color() == 0) or
            (state == States::move_blacks and figure_from_position->get_color() == 1))
    {
        std::cout << "\nmake move\n";
        game_field.move_figure(from, to);
        field_view.display_current_disposition();

        if (state == States::move_whites)
            state = States::move_blacks;
        else if (state == States::move_blacks)
            state = States::move_whites;
    }
}

void Controller::button_is_pressed(int x_board, int y_board, int cell_size)
{
    Figure* current_figure = game_field.get_figure(y_board * 8 + x_board);

    if (current_figure != nullptr and ((current_figure->get_color() == 1 and state == States::move_blacks) or
                                       (current_figure->get_color() == 0 and state == States::move_whites)))
        field_view.draw_accessible_moves(x_board, y_board, cell_size);
}

States Controller::get_state() const
{
    return state;
}

std::string Controller::get_game_history() const
{
    return game_history;
} */


void Controller::print_debug() const
{
    game_field.print();
}

void Controller::run()
{
    // start_new_game();
    window.clear(view_field.get_background_color());
    view_field.draw_disposition();
    view_field.draw_side_panel(0);

    window.display();

    while (window.isOpen())
    {
        Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed or Keyboard::isKeyPressed(Keyboard::Z))
                window.close();

            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    process_mouse_pressing(event);
                }
            }

            else if (Keyboard::isKeyPressed(Keyboard::LControl) and Keyboard::isKeyPressed(Keyboard::S))
            {
                process_saving_to_file();
            }

            else if (Keyboard::isKeyPressed(Keyboard::LControl) and Keyboard::isKeyPressed(Keyboard::O))
            {
                process_opening_file();
            }

            else if (Keyboard::isKeyPressed(Keyboard::LControl) and Keyboard::isKeyPressed(Keyboard::R))
            {
                process_starting_new_game();
            }
        }
    }
}


bool Controller::is_mouse_within_board(double mouse_x, double mouse_y)
{
    if (mouse_x < view_field.get_board_width() and mouse_y < view_field.get_board_height())
        return true;
    else return false;
}

void Controller::process_mouse_pressing(sf::Event event)
{
    // unsigned cell_size = window.getSize().x / cols;
    int x_board = (int) ((double) event.mouseButton.x / ((double) view_field.get_cell_size()));
    int y_board = (int) ((double) event.mouseButton.y / ((double) view_field.get_cell_size()));

    if (!is_mouse_within_board(event.mouseButton.x, event.mouseButton.y))
        return;

    if (model.get_state() != States::game_over)
        model.handle_mouse_press(y_board, x_board);
}

void Controller::process_starting_new_game()
{
    game_field.delete_all_figures();
    game_field.set_start_disposition();
    model.restart();
    run();
}





void Controller::process_saving_to_file()
{
    std::cout << "Saving...\n";
    std::string filePath = show_save_file_dialog();
    if (!filePath.empty()) {
        // Save content to the selected file
        std::ofstream file(filePath);
        if (file.is_open()) {
            file << model.get_game_history();
            file.close();
            std::cout << "File saved: " << filePath << std::endl;
        } else {
            std::cerr << "Error saving file\n";
        }
    }
}

void Controller::process_opening_file()
{
    std::cout << "Opening...\n";

    std::string game_history_from_file;

    std::string filePath = show_open_file_dialog();
    if (!filePath.empty()) {
        // Perform actions with the selected file, e.g., display its content
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                game_history_from_file += line;
                game_history_from_file += "\n";
            }
            file.close();
        } else {
            std::cerr << "Error opening file\n";
        }
    }

    model.set_game_history(game_history_from_file);
}


std::string Controller::show_save_file_dialog()
{
    const char *filters[] = {"*.txt", "*.cpp", "*.h", "*.csv", "*.xml", "*.json", "*.md", "*.log", nullptr};
    const char *filterDesc = "Chess Files";

    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::tm* time_info = std::localtime(&current_time);

    std::string date_in_file_name = std::to_string(time_info->tm_mday) + "." +
            std::to_string(time_info->tm_mon + 1) + "." + std::to_string(time_info->tm_year + 1900) +
            "-" + std::to_string(time_info->tm_hour) + "." + std::to_string(time_info->tm_min);

    std::string file_name = model.get_player_whites().get_name() + "-vs-" + model.get_player_blacks().get_name() +
            "-" + date_in_file_name;

    char const *result = tinyfd_saveFileDialog(
            "Save File As",
            file_name.c_str(),
            sizeof(filters) / sizeof(filters[0]) - 1,
            filters,
            filterDesc);

    if (result != nullptr) {
        return result;
    } else {
        return ""; // User canceled the dialog
    }
}

std::string Controller::show_open_file_dialog()
{
    const char *filters[] = {"*.txt", "*.cpp", "*.h", "*.csv", "*.xml", "*.json", "*.md", "*.log", nullptr};
    const char *filterDesc = "Text Files";

    char const *result = tinyfd_openFileDialog(
            "Open File",
            "",
            sizeof(filters) / sizeof(filters[0]) - 1,
            filters,
            filterDesc,
            0);

    if (result != nullptr) {
        return result;
    } else {
        return ""; // User canceled the dialog
    }
}

/* void Controller::create_window_debug() const
{
    Field f((FiguresMatrix &) game_field);
    f.create_window();
} */
