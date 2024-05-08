cmake_minimum_required(VERSION 3.24)
project(fs_prototype)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(fs_prototype main.cpp src/problem/tsp_board.h src/problem/tsp_board.cpp src/problem/game_board.cpp src/search/focal_search.cpp src/problem/heuristics.h src/problem/heuristics.cpp )

enable_testing()

add_executable(
        hello_test
        src/tests/hello_test.cc src/tests/hello_test.cc)
target_link_libraries(
        hello_test
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)