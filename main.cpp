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
    template<class T,class open,class focal>
    void runExperiment(TspBoard &gb,std::string type, bool &checkLog, std::vector<int> &result, std::vector<int> &expansion,std::vector<std::string> &version ,
    open open_value , focal focal_value,T heuristic,std::vector<std::vector<double>> &dist_matrix, double pickRate=(double) 0.6
    )
    {
       if(checkLog){
            version.push_back(type);
       }
       int num_expansion = 0;
       int res;
       if(type=="Astar"){
                 BasicAStar<TspBoard> fs;
                 res = fs.AStarSearch(gb, heuristic, num_expansion,dist_matrix);
                 std::cout << "AStarSearch\n"
                         << res << '\n';
                 std::cout << "AStarSearch with num_expansion is " << num_expansion << '\n';
                 
        
       } else if(type=="FocalSearch"){
                BasicFocalSearch<TspBoard> fs;
                res = fs.FocalSearch(gb, open_value, focal_value, heuristic, num_expansion,dist_matrix);
                std::cout << "FocalSearch\n"
                         << res << '\n';

                 std::cout << "FocalSearch with num_expansion is " << num_expansion << '\n';

       }else{
                ProbabilityFocalSearch<TspBoard> fs;
                res = fs.ProbabilitySearch(gb, open_value, focal_value, heuristic, num_expansion,dist_matrix,1.1,1.0,pickRate);

                std::cout << type<<'\n'
                          << res << '\n';

                std::cout << type<<" with num_expansion is " << num_expansion << '\n';
        
       }
        result.push_back(res);
        expansion.push_back(num_expansion);
       
    }


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
        resultFile << "Parameter: epsilon=1.1; 30 nodes; grid size (-100,100)*(-100,100),1k test \n";

        bool checkLog = true;

        for (int i = 0; i <=test; ++i)
        {
            std::cout<<i<<'\n'<<'\n';
            //Change first parameter for number of nodes
            std::vector<std::vector<double>> dist_matrix=generator_TSP(10,100);
            TspBoard tsp = TspBoard(dist_matrix.size());
            result.clear();
            expansion.clear();

            //runExperiment(tsp, "Astar", checkLog, result, expansion, version,open_funct,focal_funct,MST,dist_matrix);
            runExperiment(tsp, "FocalSearch", checkLog, result, expansion, version, open_funct, focal_funct, MST,dist_matrix);
            runExperiment(tsp, "ProbabilityFocalSearch 60/40", checkLog, result, expansion, version, open_funct, focal_funct, MST,dist_matrix,0.6);
            runExperiment(tsp, "ProbabilityFocalSearch 70/30", checkLog, result, expansion, version, open_funct, focal_funct, MST,dist_matrix,0.7);
            runExperiment(tsp, "ProbabilityFocalSearch dist_to_go 60/40", checkLog, result, expansion, version, open_funct, distance_to_go_funct, MST,dist_matrix,0.6);
            runExperiment(tsp, "ProbabilityFocalSearch dist_to_go 70/30", checkLog, result, expansion, version, open_funct, distance_to_go_funct, MST,dist_matrix,0.7);
            runExperiment(tsp, "ProbabilityFocalSearch potential func 60/40", checkLog, result, expansion, version, open_funct, focal_potential, MST,dist_matrix, 0.6);
            runExperiment(tsp, "ProbabilityFocalSearch potential func 70/30", checkLog, result, expansion, version, open_funct, focal_potential, MST,dist_matrix, 0.7);    

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

            logFile << tsp << ",";
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
