//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_HEURISTICS_H
#define FS_PROTOTYPE_HEURISTICS_H

#include <vector>
#include <set>

double HammingDistance(int size, const std::vector<int> &board);

double CartesianDistance(int size, const std::vector<int> &board);

double ManhattanDistance(int size, const std::vector<int> &board);

double LinearConflictDistance(int size, const std::vector<int> &board);

double MST(int size,const std::vector<int> visited, const std::set<int> unvisited, const std::vector<std::vector<double>> dis );

double open_funct(double g, double h);

double focal_funct(double g, double h,double dis_to_go,double C,double w);

double distance_to_go_funct(double g,double h, double weight,double initial);


#endif //FS_PROTOTYPE_HEURISTICS_H
