//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_FOCAL_SEARCH_H
#define FS_PROTOTYPE_FOCAL_SEARCH_H

#include "game_board.h"
#include <map>
#include <queue>
#include <utility>

class Node {
public:
    double f, g;
    GameBoard board;
    Node(double _f, double _g, const GameBoard&_board);
    bool operator < (const Node &oth) const;
};

class focal_search {
    std::map<GameBoard, int> visited;
    std::priority_queue<Node> open;
public:
    focal_search();

    template<class T>
    inline int AStarSearch(const std::vector<std::vector<int>>&v, T heuristic) {
        GameBoard start(v);
        open.push({0, start.GetHeuristic(heuristic), start});
        visited[start] = 0;

        while (not open.empty()) {
            auto [f, g, board] = open.top(); open.pop();
            if (visited[board] != f) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(f);
            for (const auto&next_board : GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > f + 1) {
                    visited[next_board] = f + 1;
                    open.push({f + 1, next_board.GetHeuristic(heuristic), next_board});
                }
            }
        }
    }
};


#endif //FS_PROTOTYPE_FOCAL_SEARCH_H
