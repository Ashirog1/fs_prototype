cmake_minimum_required(VERSION 3.24)
project(fs_prototype)

set(CMAKE_CXX_STANDARD 17)

add_executable(fs_prototype main.cpp src/problem/game_board.cpp src/search/focal_search.cpp src/heuristics.h src/heuristics.cpp src/search/BoundedFocalSearch.h src/search/BoundedFocalSearch.cpp)
