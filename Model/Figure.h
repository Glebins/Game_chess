#ifndef GAME_CHESS_FIGURE_H
#define GAME_CHESS_FIGURE_H

#include <iostream>
#include <cstring>
#include <vector>

#include "Player.h"

const int rows = 8;
const int cols = 8;

/**
 * @brief Base class for chess figures.
 *
 * The Figure class represents a generic chess figure with common attributes and behaviors.
 */
class Figure {

private:
    int color;

protected:
    /**
     * @brief Check if the given position is valid on the chessboard.
     *
     * @param x X-coordinate of the position.
     * @param y Y-coordinate of the position.
     * @return True if the position is valid, false otherwise.
     */
    static bool is_position_valid(int x, int y);

public:
    /**
     * @brief Create a position value from given x and y coordinates.
     *
     * @param x X-coordinate of the position.
     * @param y Y-coordinate of the position.
     * @return Position value representing the given coordinates.
     */
    static int create_position(int x, int y);

    /**
     * @brief Convert a chess figure symbol to a Figure object.
     *
     * @param symbol Symbol representing the chess figure.
     * @return Pointer to the created Figure object.
     */
    virtual Figure* symbol_to_figure(std::string symbol);

    /**
     * @brief Convert the chess figure to its symbol representation.
     *
     * @return Character representing the chess figure.
     */
    virtual char figure_to_symbol() {};

    /**
     * @brief Get an array of possible moves for the chess figure independently of other figures on the board.
     *
     * @param figure Pointer to the chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions independently of other figures.
     */
    virtual std::vector<int> array_moves(Figure *figure, int position) {};

    /**
     * @brief Check if the chess figure can perform a specific move independently of other figures on the board.
     *
     * @param figure Pointer to the chess figure.
     * @param position Current position of the figure.
     * @param move_position Target position for the move.
     * @return True if the move is valid, false otherwise independently of other figures on the board.
     */
    bool can_do_move(Figure *figure, int position, int move_position);

    /**
     * @brief Get the name of the chess figure.
     *
     * @return Name of the chess figure.
     */
    virtual std::string get_name_of_figure() { return "Unknown"; };

    /**
     * @brief Get the color of the chess figure.
     *
     * @return Color of the chess figure.
     */
    [[nodiscard]] int get_color() const { return color; }

    /**
     * @brief Overloaded stream insertion operator for easy output of the chess figure.
     *
     * @param stream Output stream.
     * @param figure Pointer to the chess figure.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator << (std::ostream& stream, Figure *figure);

};


/**
 * @brief Class representing a King chess figure.
 *
 * The King class represents the King chess figure and provides specific implementations
 * for its symbol, possible moves, and name.
 */
class King : public Figure {

public:
    /**
     * @brief Convert the King chess figure to its symbol representation.
     *
     * @return Character 'k' representing the King.
     */
    char figure_to_symbol() override { return 'k'; };

    /**
     * @brief Get an array of possible moves for the King chess figure.
     *
     * @param figure Pointer to the King chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions.
     */
    std::vector<int> array_moves(Figure *figure, int position) override;

    /**
     * @brief Get the name of the King chess figure.
     *
     * @return Name of the King chess figure.
     */
    std::string get_name_of_figure() override { return "King"; }

};


/**
 * @brief Class representing a Queen chess figure.
 *
 * The Queen class represents the Queen chess figure and provides specific implementations
 * for its symbol, possible moves, and name.
 */
class Queen : public Figure {

public:
    /**
     * @brief Convert the Queen chess figure to its symbol representation.
     *
     * @return Character 'q' representing the Queen.
     */
    char figure_to_symbol() override { return 'q'; }

    /**
     * @brief Get an array of possible moves for the Queen chess figure.
     *
     * @param figure Pointer to the Queen chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions.
     */
    std::vector<int> array_moves(Figure *figure, int position) override;

    /**
     * @brief Get the name of the Queen chess figure.
     *
     * @return Name of the Queen chess figure.
     */
    std::string get_name_of_figure() override { return "Queen"; }

};


/**
 * @brief Class representing a Rook chess figure.
 *
 * The Rook class represents the Rook chess figure and provides specific implementations
 * for its symbol, possible moves, and name.
 */
class Rook : public Figure {

public:
    /**
     * @brief Convert the Rook chess figure to its symbol representation.
     *
     * @return Character 'r' representing the Rook.
     */
    char figure_to_symbol() override { return 'r'; }

    /**
     * @brief Get an array of possible moves for the Rook chess figure.
     *
     * @param figure Pointer to the Rook chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions.
     */
    std::vector<int> array_moves(Figure *figure, int position) override;

    /**
     * @brief Get the name of the Rook chess figure.
     *
     * @return Name of the Rook chess figure.
     */
    std::string get_name_of_figure() override { return "Rook"; }

};


/**
 * @brief Class representing a Bishop chess figure.
 *
 * The Bishop class represents the Bishop chess figure and provides specific implementations
 * for its symbol, possible moves, and name.
 */
class Bishop : public Figure {

public:
    /**
     * @brief Convert the Bishop chess figure to its symbol representation.
     *
     * @return Character 'b' representing the Bishop.
     */
    char figure_to_symbol() override { return 'b'; }

    /**
     * @brief Get an array of possible moves for the Bishop chess figure.
     *
     * @param figure Pointer to the Bishop chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions.
     */
    std::vector<int> array_moves(Figure *figure, int position) override;

    /**
     * @brief Get the name of the Bishop chess figure.
     *
     * @return Name of the Bishop chess figure.
     */
    std::string get_name_of_figure() override { return "Bishop"; }

};


/**
 * @brief Class representing a Knight chess figure.
 *
 * The Knight class represents the Knight chess figure and provides specific implementations
 * for its symbol, possible moves, and name.
 */
class Knight : public Figure {

public:
    /**
     * @brief Convert the Knight chess figure to its symbol representation.
     *
     * @return Character 'n' representing the Knight.
     */
    char figure_to_symbol() override { return 'n'; }

    /**
     * @brief Get an array of possible moves for the Knight chess figure.
     *
     * @param figure Pointer to the Knight chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions.
     */
    std::vector<int> array_moves(Figure *figure, int position) override;

    /**
     * @brief Get the name of the Knight chess figure.
     *
     * @return Name of the Knight chess figure.
     */
    std::string get_name_of_figure() override { return "Knight"; }

};


/**
 * @brief Class representing a Pawn chess figure.
 *
 * The Pawn class represents the Pawn chess figure and provides specific implementations
 * for its symbol, possible moves, and name.
 */
class Pawn : public Figure {

public:
    /**
     * @brief Convert the Pawn chess figure to its symbol representation.
     *
     * @return Character 'p' representing the Pawn.
     */
    char figure_to_symbol() override { return 'p'; }

    /**
     * @brief Get an array of possible moves for the Pawn chess figure.
     *
     * @param figure Pointer to the Pawn chess figure.
     * @param position Current position of the figure.
     * @return Vector of possible move positions.
     */
    std::vector<int> array_moves(Figure *figure, int position) override;

    /**
     * @brief Get the name of the Pawn chess figure.
     *
     * @return Name of the Pawn chess figure.
     */
    std::string get_name_of_figure() override { return "Pawn"; }

};


#endif // GAME_CHESS_FIGURE_H