//
// Created by only_u on 12/21/23.
//

#include "heuristics.h"

#include <algorithm>
#include <bitset>
#include <climits>
#include <complex>
#include <iostream>
#include <queue>
#include <utility>

double HammingDistance(int size, const std::vector<int> &board) {
  int hammingDistance = 0;
  for (int i = 0; i < size * size; ++i) {
    if (board[i] != i + 1 and board[i] != 0) {
      ++hammingDistance;
    }
  }
  return hammingDistance;
}

double CartesianDistance(int size, const std::vector<int> &board) {
  double cartesianDistance = 0.0;
  for (int i = 0; i < size * size; ++i) {
    if (board[i] == 0) continue;
    int row = i / size;
    int col = i % size;
    if (board[i] - 1 != i) {
      int targetRow = (board[i] - 1) / size;
      int targetCol = (board[i] - 1) % size;
      cartesianDistance += std::sqrt(std::pow(row - targetRow, 2) +
                                     std::pow(col - targetCol, 2));
    }
  }
  return cartesianDistance;
}

double ManhattanDistance(int size, const std::vector<int> &board) {
  int manhattanDistance = 0;
  for (int i = 0; i < size * size; ++i) {
    if (board[i] == 0) continue;
    if (board[i] - 1 != i) {
      int targetRow = (board[i] - 1) / size;
      int targetCol = (board[i] - 1) % size;
      int row = i / size;
      int col = i % size;
      manhattanDistance +=
          std::abs(row - targetRow) + std::abs(col - targetCol);
    }
  }
  return manhattanDistance;
}

double LinearConflictDistance(int size, const std::vector<int> &board) {
  std::vector<std::vector<int>> puzzle(size, std::vector<int>(size, 0));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      puzzle[i][j] = board[i * size + j];
    }
  }
  int linearConflict = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1; j++) {
      int tileA = puzzle[i][j];
      if (tileA == 0) continue;  // Skip the empty space

      for (int k = j + 1; k < size; k++) {
        int tileB = puzzle[i][k];
        if (tileB == 0) continue;  // Skip the empty space

        if ((tileA / size == i) && (tileB / size == i) && (tileA > tileB)) {
          linearConflict += 2;
        }
      }
    }
  }

  // Check columns for conflicts
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size - 1; j++) {
      int tileA = puzzle[j][i];
      if (tileA == 0) continue;  // Skip the empty space

      for (int k = j + 1; k < size; k++) {
        int tileB = puzzle[k][i];
        if (tileB == 0) continue;  // Skip the empty space

        if ((tileA % size == i) && (tileB % size == i) && (tileA > tileB)) {
          linearConflict += 2;
        }
      }
    }
  }

  return linearConflict + ManhattanDistance(size, board);
}

// double MST(int size,const std::vector<int> visited, const std::set<int>
// unvisited, const std::vector<std::vector<double>> dis){
//     return 0;
// }

double MST(int size, const std::vector<std::vector<double>> &dis,
           const std::vector<int> &clusterId,
           //  const std::bitset<15> &unvisitedCluster) {
           const std::set<int> &unvisitedCluster) {
  if (unvisitedCluster.empty()) return 0;  // .none() checks if all bits are 0
  double total = 1;
  std::priority_queue<std::pair<double, int>,
                      std::vector<std::pair<double, int>>,
                      std::greater<std::pair<double, int>>>
      prim;
  std::vector<double> d(size, INT_MAX);
  // std::bitset<15> visitedCluster;
  std::vector<int> visitedCluster(size + 5, 0);
  std::set<int> remain;

  // Initialize remain set with nodes belonging to unvisited clusters

  for (auto v : unvisitedCluster) {
    visitedCluster[v] = true;
  }
  for (int i = 0; i < size; ++i) {
    if (visitedCluster[clusterId[i]]) remain.insert(i);
  }

  if (unvisitedCluster.size()) {
    double min_current = 0;
    double min_depot = INT_MAX;
    for (int i = 1; i < size; ++i) {
      if (visitedCluster[clusterId[i]])
        min_depot = std::min(min_depot, dis[0][i]);
    }
    total = total + min_current + min_depot;
  }

  // Start Prim's algorithm
  d[*remain.begin()] = 0;
  prim.push(std::make_pair(0, *remain.begin()));

  while (!prim.empty()) {
    if (remain.empty()) break;
    auto top = prim.top();
    prim.pop();

    if (visitedCluster[clusterId[top.second]]) continue;
    if (top.first != d[top.second]) continue;

    total += d[top.second];
    // visitedCluster.set(clusterId[top.second]);  // Mark the cluster as visited
    visitedCluster[clusterId[top.second]] = 1;
    d[top.second] = INT_MIN;                    // To prevent revisiting
    remain.erase(top.second);

    for (auto v : remain) {
      if (d[v] > dis[top.second][v]) {
        d[v] = dis[top.second][v];
        prim.push(std::make_pair(d[v], v));
      }
    }
  }
  return total;
}

double open_funct(double g, double h) { return g + h; }

double focal_funct(double g, double h, double dis_to_go, double C, double w) {
  return h;
}

double distance_to_go_funct(double g, double h, double dis_to_go, double C,
                            double w) {
  return g + std::max((double)1, w * dis_to_go) * h;
}

double focal_potential(double g, double h, double dis_to_go, double C,
                       double w) {
  return h / g;
}
