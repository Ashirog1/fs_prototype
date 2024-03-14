//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_HEURISTICS_H
#define FS_PROTOTYPE_HEURISTICS_H

#include <vector>

double HammingDistance(int size, const std::vector<int> &board);

double CartesianDistance(int size, const std::vector<int> &board);

double ManhattanDistance(int size, const std::vector<int> &board);

double open_funct(double g, double h);

double focal_funct(double g, double h);

#endif //FS_PROTOTYPE_HEURISTICS_H
