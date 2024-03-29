#include "src/problem/game_board.h"
#include "src/problem/heuristics.h"
#include "src/search/focal_search.h"
#include "src/search/BoundedFocalSearch.h"
#include "src/search/RWFocalSearch.h"
#include "src/search/PotentialFocalSearch.h"
#include "src/search/generalizedVersion.h"
#include <iostream>
#include <vector>

namespace global_testing {
    void test() {
        std::vector<std::vector<int>> v = {{0, 2, 4, 8},
                                           {1, 5, 3, 12},
                                           {6, 7, 10, 15},
                                           {9, 13, 14, 11}};
        GameBoard gb(v);


    }
};

namespace benchmark {
    void NPuzzleDemo() {
        /*
         * about benchmark expansion node
         * how about compare visited???
         */
        for (int i = 0; i <= 20; ++i) {
            /// 3 puzzle 10 swap
            GameBoard gb = generator(4, 10);
            std::cout << gb << '\n';

            {
                int num_expansion = 0;

                BasicAStar fs;

                std::cout << "AStarSearch\n" << fs.AStarSearch(gb, ManhattanDistance, num_expansion) << '\n';

                std::cout << "AStarSearch with num_expansion is " << num_expansion << '\n';
            }
            {
                BasicFocalSearch fs;
                int num_expansion = 0;

                std::cout << "BasicFocalSearch\n" << fs.FocalSearch(gb, open_funct, focal_funct, ManhattanDistance, num_expansion) << '\n';

                std::cout << "BasicFocalSearch with num_expansion is " << num_expansion << '\n';
            }
            {
                BoundedFocalSearch fs;
//                std::cout << "BoundedFocalSearch\n" << fs.FocalSearch(v, open_funct, focal_funct, ManhattanDistance);
            }
//            {
//                int num_expansion = 0;
//                PotentialFocalSearch fs;
//                std::cout << "PotentialFocalSearch\n" << fs.FocalSearch(gb, open_funct, focal_funct, ManhattanDistance, num_expansion) << '\n';
//                std::cout << "PotentialFocalSearch with num_expansion is " << num_expansion << '\n';
//            }
//            {
//                int num_expansion = 0;
//                RWFocalSearch fs;
//                std::cout << "RWFocalSearch\n" << fs.FocalSearch(gb, open_funct, focal_funct, ManhattanDistance, num_expansion) << '\n';
//                std::cout << "RWFocalSearch with num_expansion is " << num_expansion << '\n';
//            }
        }
    }
};

int main() {
//    global_testing::test();
    benchmark::NPuzzleDemo();
    return 0;
}
