#include "src/problem/game_board.h"
#include "src/problem/heuristics.h"
#include "src/problem/tsp_board.h"
#include "src/search/focal_search.h"
// #include "src/search/BoundedFocalSearch.h"
// #include "src/search/RWFocalSearch.h"
// #include "src/search/PotentialFocalSearch.h"
#include "src/search/ProbabilityFocalSearch.h"
// #include "src/search/DistanceToGoFocalSearch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace global_testing
{
    void test()
    {
        std::vector<std::vector<int>> v = {{0, 2, 4, 8}, {1, 5, 3, 12}, {6, 7, 10, 15}, {9, 13, 14, 11}};
        GameBoard gb(v);
    }
}; // namespace global_testing

namespace benchmark
{
    void NPuzzleDemo()
    {
        /*
         * about benchmark expansion node
         * how about compare visited???
         */
        /*
         * about benchmark expansion node
         * how about compare visited???
         */

        int test = 1000;
        std::vector<int> result;
        std::vector<int> expansion;
        std::vector<std::string> version;
        std::vector<std::vector<int>> compareResult(100, std::vector<int>(100));
        std::vector<std::vector<int>> compareExpansion(100, std::vector<int>(100));

        std::ofstream resultFile;
        std::ofstream logFile;
        resultFile.open("../result/result.csv");
        logFile.open("../result/log.csv");
        resultFile << "Parameter: epsilon=1.1; prob rate =0.6; weight distance_to_go = 1.1; max distance from goal less than 50 move; game board size 4x4, 100k test \n";

        bool checkLog = true;

        for (int i = 0; i <=test; ++i)
        {
            std::cout<<i<<'\n'<<'\n';
            //First parameter for size of board, second paramater for number of steps moving from initial state
            GameBoard gb = generator(4, 150);
             result.clear();
             expansion.clear();
            {
                if (checkLog)
                {
                    version.push_back("Astar");
                }
                int num_expansion = 0;

                BasicAStar<GameBoard> fs;


                int res = fs.AStarSearch(gb, ManhattanDistance, num_expansion);

               std::cout << "AStarSearch\n"
                         << res << '\n';

               std::cout << "AStarSearch with num_expansion is " << num_expansion << '\n';
                 result.push_back(res);
                 expansion.push_back(num_expansion);
            }

            {
                if (checkLog)
                {
                    version.push_back("FocalSearch");
                }

                BasicFocalSearch<GameBoard> fs;
                int num_expansion = 0;
                int res = fs.FocalSearch(gb, open_funct, focal_funct, ManhattanDistance, num_expansion);
                std::cout << "FocalSearch\n"
                         << res << '\n';

                 std::cout << "FocalSearch with num_expansion is " << num_expansion << '\n';
                 result.push_back(res);
                 expansion.push_back(num_expansion);
            }

            {
                if (checkLog)
                {
                    version.push_back("ProbFocalSearch");
                }

                ProbabilityFocalSearch<GameBoard> fs;
                int num_expansion = 0;
                int res = fs.ProbabilitySearch(gb, open_funct, focal_funct, ManhattanDistance, num_expansion);

                std::cout << "ProbabilityFocalSearch\n"
                          << res << '\n';

                std::cout << "ProbabilityFocalSearch with num_expansion is " << num_expansion << '\n';

                result.push_back(res);
                expansion.push_back(num_expansion);
            }

            {
                if (checkLog)
                {
                    version.push_back("ProbFocalSearch 70/30");
                }

                ProbabilityFocalSearch<GameBoard> fs;
                int num_expansion = 0;
                int res = fs.ProbabilitySearch(gb, open_funct, focal_funct, ManhattanDistance, num_expansion, 1.1, 1.0, 0.7);

                std::cout << "ProbabilityFocalSearch\n"
                          << res << '\n';

                std::cout << "ProbabilityFocalSearch 70/30 with num_expansion is " << num_expansion << '\n';

                result.push_back(res);
                expansion.push_back(num_expansion);
            }

            {
                if (checkLog)
                {
                    version.push_back("ProbFocalSearch version 4 60/40");
                }

                ProbabilityFocalSearch<GameBoard> fs;
                int num_expansion = 0;
                int res = fs.ProbabilitySearch(gb, open_funct, focal_potential, ManhattanDistance, num_expansion, 1.1, 1.0, 0.6);

                std::cout << "ProbabilityFocalSearch\n"
                          << res << '\n';

                std::cout << "ProbabilityFocalSearch with potential func with num_expansion is " << num_expansion << '\n';

                result.push_back(res);
                expansion.push_back(num_expansion);
            }

            {
                if (checkLog)
                {
                    version.push_back("ProbFocalSearch version 4 70/30");
                }

                ProbabilityFocalSearch<GameBoard> fs;
                int num_expansion = 0;
                int res = fs.ProbabilitySearch(gb, open_funct, focal_potential, ManhattanDistance, num_expansion, 1.1, 1.0, 0.7);

                std::cout << "ProbabilityFocalSearch\n"
                          << res << '\n';

                std::cout << "ProbabilityFocalSearch with potential func with num_expansion is " << num_expansion << '\n';

                result.push_back(res);
                expansion.push_back(num_expansion);
            }

            if (checkLog)
            {
                logFile << "state,";
                for (auto v : version)
                {
                    logFile << v << " result,";
                    logFile << v << " expansion,";
                }
                logFile << '\n';
                checkLog = false;
            }

            logFile << gb << ",";
            for (int j = 0; j < result.size(); j++)
            {
                logFile << result[j] << "," << expansion[j] << ",";
            }
            logFile << "\n";

            for (int j = 0; j < result.size(); j++)
            {
                for (int k = 0; k < result.size(); k++)
                {
                    if (expansion[j] < expansion[k])
                    {
                       
                        compareExpansion[j][k]++;
                    }

                    if (result[j] <= result[k])
                    {
                        compareResult[j][k]++;
                    }
                }
            }
        }
        logFile.close();
        resultFile << "\n Expansion: % when this search have less expansion(run faster) than other search  (not include the case when both have the same speed) \n";
        resultFile << ",";
        for (auto v : version)
        {
            resultFile << v << ",";
        }
        resultFile << '\n';
        for (int j = 0; j < result.size(); j++)
        {
            resultFile << version[j] << ",";

            for (int k = 0; k < result.size(); k++)
            {
                resultFile << (double)compareExpansion[j][k] / (test + 1) << ",";
            }
            resultFile << '\n';
        }
        resultFile << "\n Result \n";
        resultFile << ",";
        for (auto v : version)
        {
            resultFile << v << ",";
        }
        resultFile << '\n';
        for (int j = 0; j < result.size(); j++)
        {
            resultFile << version[j] << ",";
            for (int k = 0; k < result.size(); k++)
            {
                resultFile << (double)compareResult[j][k] / (test + 1) << ",";
            }
            resultFile << '\n';
        }
        resultFile.close();
    }
}

; // namespace benchmark

int main()
{
    //    global_testing::test();
    // benchmark::NPuzzleDemo();
    benchmark::NPuzzleDemo();
    return 0;
}
