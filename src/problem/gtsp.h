//
// Created by only_u on 12/21/23.
//

// #ifndef FS_PROTOTYPE_GAME_BOARD_H
// #define FS_PROTOTYPE_GAME_BOARD_H

#include "../search/utils.h"
#include "Problem.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <math.h>

class GTspBoard {
    /*
     * GameBoard problem
     */
  private:
    int n;
    std::vector<int> clusterId;
    std::set<int> unvisitedCluster;
    int currentNode;

  public:
    GTspBoard() {};

    GTspBoard(int _n, const std::vector<int> &_clusterId) {
        n = _n;
        clusterId = _clusterId;
        currentNode = 0;
        for (int i = 0; i < n; i++) {
            unvisitedCluster.insert(clusterId[i]);
        }
    };

    friend std::vector<GTspBoard> GetNeighbour(GTspBoard &gtspBoard) {
        std::vector<GTspBoard> adj;
        for (int i = 0; i < gtspBoard.n; i++) {
            if (gtspBoard.unvisitedCluster.count(gtspBoard.clusterId[i])) {
                GTspBoard newBoard = gtspBoard;
                newBoard.unvisitedCluster.erase(newBoard.clusterId[i]);
                newBoard.currentNode = i;
                adj.push_back(newBoard);
            }
        }
        return adj;
    }

    friend double cost_move(GTspBoard &gtspBoard1, GTspBoard &gtspBoard2, std::vector<std::vector<double>> &dis_matrix) {
        if (gtspBoard1.unvisitedCluster.size() == 0)
            return 0;
        return dis_matrix[gtspBoard1.currentNode]
                          [gtspBoard2.currentNode];
    }

    double getDistanceToGo() { return (double)(unvisitedCluster.size()); }

    template <class T>
    inline double GetHeuristic(T heuristic, std::vector<std::vector<double>> &dis_matrix) {
        return heuristic(n,dis_matrix, clusterId, unvisitedCluster);
    };

    void printState() {
        // for (auto v : visited)
        //     std::cout << v << " ";
    };

    bool operator<(const GTspBoard &oth) const {
        if (unvisitedCluster != oth.unvisitedCluster) {
            return std::lexicographical_compare(unvisitedCluster.begin(), unvisitedCluster.end(), oth.unvisitedCluster.begin(), oth.unvisitedCluster.end());
        }
        return currentNode < oth.currentNode;
    };

    friend std::ostream& operator<<(std::ostream& os, const GTspBoard &gtspBoard){
        os << gtspBoard.n << " ";
        for (int i = 0; i < gtspBoard.n; ++i) {
            os << gtspBoard.clusterId[i] << " ";
        }
        os << '\n';
        return os;
    };
};

std::pair<std::vector<std::vector<double>>, std::vector<int>> generator_GTSP(int n, int grid) {
    // Number of clusters
    int numClusters = std::max(n, 3);
    std::vector<std::vector<double>> dist(n, std::vector<double>(n, 0));
    std::vector<int> clusterId(n, 0);

    const auto euclid = [&](std::pair<int, int> u, std::pair<int, int> v) {
        return (int)sqrt((u.first - v.first) * (u.first - v.first) + (u.second - v.second) * (u.second - v.second));
    };
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        points[i].first = generate_random_number(-grid, grid);
        points[i].second = generate_random_number(-grid, grid);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = euclid(points[i], points[j]);
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Assign clusters
    for (int i = 1; i < n; ++i) {
        clusterId[i] = generate_random_number(1, numClusters);
    }

    return {dist, clusterId};
}

// #endif //FS_PROTOTYPE_GAME_BOARD_H
