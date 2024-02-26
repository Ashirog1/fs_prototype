#include "src/problem/game_board.h"
#include "src/heuristics.h"
#include "src/search/focal_search.h"
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
        BasicFocalSearch fs;
        std::cout << gb.GetHeuristic(HammingDistance) << '\n';
//        std::cout << "AStarSearch\n" << fs.AStarSearch(v, HammingDistance) << '\n';
        fs = BasicFocalSearch();
        std::cout << "BasicFocalSearch\n" << fs.FocalSearch(v, open_funct, focal_funct, ManhattanDistance);
    }
};

int main() {
    global_testing::test();
    return 0;
}
