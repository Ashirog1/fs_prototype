#include "src/game_board.h"
#include <iostream>
#include <vector>

namespace global_testing {
    void test() {
        std::vector<std::vector<int>> v = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
        GameBoard gb(v);

    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
