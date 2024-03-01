#include "src/problem/game_board.h"
#include "src/heuristics.h"
#include "src/search/focal_search.h"
#include "src/search/BoundedFocalSearch.h"
#include "src/search/RWFocalSearch.h"
#include "src/search/PotentialFocalSearch.h"
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
        PotentialFocalSearch fs;
        std::cout << gb.GetHeuristic(ManhattanDistance) << '\n';
//        std::cout << "AStarSearch\n" << fs.AStarSearch(v, HammingDistance) << '\n';
        std::cout << "BasicFocalSearch\n" << fs.PotentialSearch(v, open_funct, focal_funct, ManhattanDistance);

    }
};

int main() {
    global_testing::test();
    return 0;
}
