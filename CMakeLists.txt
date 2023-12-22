cmake_minimum_required(VERSION 3.24)
project(fs_prototype)

set(CMAKE_CXX_STANDARD 17)

add_executable(fs_prototype main.cpp src/game_board.cpp src/focal_search.cpp src/utils.cpp src/utils.h src/heuristics.h src/heuristics.cpp)
