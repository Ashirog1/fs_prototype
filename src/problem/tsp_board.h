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

class TspBoard {
    /*
     * GameBoard problem
     */
  private:
    int n;

    std::vector<int> visited;
    std::vector<int> check_visited;
    std::set<int> unvisited;
   

  public:
    TspBoard(){

    };
    TspBoard(int _n) {
        n = _n;
        visited.clear();
        check_visited.resize(n, 0);
       // dis_matrix = distance;
        for (int i = 0; i < n; i++)
            unvisited.insert(i);
    };

    friend std::vector<TspBoard> GetNeighbour(TspBoard &tspBoard) {
        std::vector<TspBoard> adj;
        if (tspBoard.visited.size() == tspBoard.n) {
            TspBoard newBoard = tspBoard;
            newBoard.visited.push_back(newBoard.visited[0]);
            adj.push_back(newBoard);
        }
        for (int i = 0; i < tspBoard.n; i++) {
            if (tspBoard.check_visited[i] == 0) {
                TspBoard newBoard = tspBoard;
                newBoard.visited.push_back(i);
                newBoard.check_visited[i] = 1;
                newBoard.unvisited.erase(i);
                adj.push_back(newBoard);
            }
        }
        return adj;
    }

    friend double cost_move(TspBoard &tspBoard1, TspBoard &tspBoard2, std::vector<std::vector<double>> &dis_matrix) {
        if (tspBoard1.visited.size() == 0)
            return 0;
        return dis_matrix[tspBoard1.visited[tspBoard1.visited.size() - 1]]
                                   [tspBoard2.visited[tspBoard2.visited.size() - 1]];
    }

    double getDistanceToGo() { return (double) (n - visited.size()); }

    template <class T> inline double GetHeuristic(T heuristic,std::vector<std::vector<double>> &dis_matrix) { return heuristic(n, visited, unvisited, dis_matrix); };

    void printState() {
        for (auto v : visited)
            std::cout << v << " ";
    };

    bool operator<(const TspBoard &oth) const {
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
     friend std::ostream& operator<<(std::ostream& os, const TspBoard &tspBoard){
         os << tspBoard.n << " ";
         return os;

     };

};

std::vector<std::vector<double>> generator_TSP(int n, int grid) {
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

// #endif //FS_PROTOTYPE_GAME_BOARD_H
