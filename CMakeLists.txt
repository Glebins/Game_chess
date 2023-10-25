cmake_minimum_required(VERSION 3.25)
project(Game_chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game_chess main.cpp Tools/Controller.h Tools/Controller.cpp Tools/Clock.h Tools/Clock.cpp
        Tools/Player.h Tools/Player.cpp)
