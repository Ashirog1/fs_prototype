#include "src/game_board.h"
#include "src/heuristics.h"
#include "src/focal_search.h"
#include <iostream>
#include <vector>

namespace global_testing {
    void test() {
        std::vector<std::vector<int>> v = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
        GameBoard gb(v);
//        std::cout << gb << '\n';
//        for (auto  neigh: GetNeighbour(gb)) {
//            std::cout << neigh << '\n';
//
//            std::cout << neigh.GetHeuristic(HammingDistance) << '\n';
//        }
//        return ;
        focal_search fs;
        std::cout << gb.GetHeuristic(HammingDistance) << '\n';
//        std::cout << "AStarSearch\n" << fs.AStarSearch(v, HammingDistance) << '\n';
        fs = focal_search();
        std::cout << "FocalSearch\n" << fs.FocalSearch(v, HammingDistance, ManhattanDistance);
    }
};

int main() {
    global_testing::test();
    return 0;
}
