//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_FOCAL_SEARCH_H
#define FS_PROTOTYPE_FOCAL_SEARCH_H

#include "game_board.h"
#include "heuristics.h"
#include <map>
#include <queue>
#include <utility>
#include <cassert>

class Node {
public:
    double f, g;
    GameBoard board;

    Node(double _f, double _g, const GameBoard &_board);

    bool operator<(const Node &oth) const;
};

/// focal comparator


struct CompareG {
    bool operator()(const Node &a, const Node &b);
};

class focal_search {
    std::map<GameBoard, int> visited;
    std::priority_queue<Node> open;
public:
    focal_search();

    template<class T>
    inline int AStarSearch(std::vector<std::vector<int>> &v, T heuristic) {
        GameBoard start(v);
        open.push({0, start.GetHeuristic(heuristic), start});
        visited[start] = 0;


        while (not open.empty()) {
            auto [f, g, board] = open.top();
            open.pop();
            if (visited[board] != f) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(f);
            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > f + 1) {
                    visited[next_board] = f + 1;
                    open.push({f + 1, next_board.GetHeuristic(heuristic), next_board});
                }
            }
        }
        return static_cast<int>(-1);
    }

    template<class T>
    inline int FocalSearch(std::vector<std::vector<int>> &v, T heuristic, T focal_heuristic, double epsilon = (double) 1.5) {
        visited.clear();
        std::cout << "Open size " << open.size() << '\n';
        std::priority_queue<Node, std::vector<Node>, CompareG> focal;
        GameBoard start(v);
        open.push({0, start.GetHeuristic(heuristic), start});
        visited[start] = 0;
        double best_h_score = 0;

        while (not open.empty()) {
            {
                /// update focal
                auto [f, g, board] = open.top();
                double h_min = f + g;
                best_h_score = std::max(best_h_score, h_min);
                while (not open.empty()) {
                    auto [f_, g_, board_] = open.top();
                    double cur_h = f_ + g_;
                    if (cur_h > epsilon * h_min) break;
                    open.pop();

                    focal.push({f_, board_.GetHeuristic(focal_heuristic), board_});
                }
            }
//            assert(focal.size() > 0);
            if (focal.empty()) break;
            auto [f, g, board] = focal.top();
            focal.pop();
//            std::cout << f << ' ' << g << ' ' << board << '\n';

            if (visited[board] != f) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(f);
            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > f + 1) {
                    visited[next_board] = f + 1;
                    open.push({f + 1, next_board.GetHeuristic(heuristic), next_board});
//                    std::cout << "neighbour " << next_board << '\n';
                }
            }
        }
        return static_cast<int>(-1);
    }
};


#endif //FS_PROTOTYPE_FOCAL_SEARCH_H
