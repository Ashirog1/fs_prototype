#ifndef FS_PROTOTYPE_GAME_BOARD_H
#define FS_PROTOTYPE_GAME_BOARD_H

#include "../search/utils.h"
#include "Problem.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <math.h>

class GCTspBoard {
    /*
     * Generalized Covering Traveling Salesman Problem
     */
  private:
    int n;
    int covering_radius;

    std::vector<int> visited;
    std::vector<int> check_visited;
    std::set<int> unvisited;

  public:
    GCTspBoard(){};

    GCTspBoard(int _n, int _covering_radius) {
        n = _n;
        covering_radius = _covering_radius;
        visited.clear();
        check_visited.resize(n, 0);
        for (int i = 0; i < n; i++)
            unvisited.insert(i);
    };

    friend std::vector<GCTspBoard> GetNeighbour(GCTspBoard &gctspBoard, const std::vector<std::vector<double>> &dis_matrix) {
        std::vector<GCTspBoard> adj;
        if (gctspBoard.visited.size() == gctspBoard.n) {
            GCTspBoard newBoard = gctspBoard;
            newBoard.visited.push_back(newBoard.visited[0]);
            adj.push_back(newBoard);
        }
        for (int i = 0; i < gctspBoard.n; i++) {
            if (gctspBoard.check_visited[i] == 0) {
                GCTspBoard newBoard = gctspBoard;
                newBoard.visited.push_back(i);
                newBoard.check_visited[i] = 1;
                newBoard.unvisited.erase(i);
                adj.push_back(newBoard);
            }
        }
        return adj;
    }

    friend double cost_move(GCTspBoard &gctspBoard1, GCTspBoard &gctspBoard2, const std::vector<std::vector<double>> &dis_matrix) {
        if (gctspBoard1.visited.size() == 0)
            return 0;
        return dis_matrix[gctspBoard1.visited[gctspBoard1.visited.size() - 1]]
                         [gctspBoard2.visited[gctspBoard2.visited.size() - 1]];
    }

    double getDistanceToGo() { return (double)(n - visited.size()); }

    template <class T> inline double GetHeuristic(T heuristic, const std::vector<std::vector<double>> &dis_matrix) { 
        return heuristic(n, visited, unvisited, dis_matrix); 
    };

    void printState() {
        for (auto v : visited)
            std::cout << v << " ";
    };

    bool operator<(const GCTspBoard &oth) const {
        if (visited.size() != oth.visited.size())
            return visited.size() < oth.visited.size();
        for (int i = 0; i < visited.size(); i++) {
            if (visited[i] < oth.visited[i]) {
                return true;
            } else if (visited[i] > oth.visited[i])
                return false;
        }
        return false;
    };

    friend std::ostream& operator<<(std::ostream& os, const GCTspBoard &gctspBoard) {
        os << gctspBoard.n << " " << gctspBoard.covering_radius << " ";
        return os;
    };

};

std::vector<std::vector<double>> generator_GCTSP(int n, int grid) {
    std::vector<std::vector<double>> dist(n, std::vector<double>(n, 0));

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
    return dist;
}

#endif //FS_PROTOTYPE_GAME_BOARD_H
