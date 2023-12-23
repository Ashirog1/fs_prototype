#include "src/game_board.h"
#include "src/heuristics.h"
#include "src/focal_search.h"
#include <iostream>
#include <vector>

namespace global_testing {
    void test() {
        std::vector<std::vector<int>> v = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
        GameBoard gb(v);
        focal_search fs;
        std::cout << gb.GetHeuristic(HammingDistance) << '\n';
        std::cout << fs.AStarSearch(v, HammingDistance);
    }
};

int main() {
    global_testing::test();
    return 0;
}
