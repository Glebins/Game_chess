#ifndef GAME_CHESS_PLAYER_H
#define GAME_CHESS_PLAYER_H

#include <iostream>
#include <cstring>
#include <utility>

class Player {

private:
    const int game_time = 8 * 60;

    int elapsed_time;

    int player_rating;
    std::string player_name;

public:
    Player() : player_rating(0), elapsed_time(game_time) {}
    Player(std::string name, int rating) : player_name(std::move(name)),
        player_rating(rating), elapsed_time(game_time) {}
    int get_elapsed_time() const;
    void set_time(int time);
    void set_start_time();

    std::string get_name() const;
    void set_name(std::string name);

    int get_rating() const;
    void set_rating(int rating);

};


#endif // GAME_CHESS_PLAYER_H