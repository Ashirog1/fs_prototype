//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_FOCAL_SEARCH_H
#define FS_PROTOTYPE_FOCAL_SEARCH_H

#include "game_board.h"
#include "heuristics.h"
#include "utils.h"
#include <map>
#include <queue>
#include <utility>
#include <cassert>
#include <set>

class Node {
public:
    double f, g, h;
    double hFocal;
    GameBoard board;

    Node(double _f, double _g, double _h, double _hFocal, const GameBoard &_board);

    bool operator<(const Node &oth) const;
};

/// focal comparator


//For open list
struct CompareG {
    bool operator()(const Node &a, const Node &b);
};


//For focal list
struct CompareH {
    bool operator()(const Node &a, const Node &b);
};

class focal_search {
    std::map<GameBoard, int> visited;
    //std::priority_queue<Node> open;
    std::set<Node> open;
    std::map<GameBoard, Node> link_open;

public:
    focal_search();

    template<class T, class Q>
    inline int FocalSearch(std::vector<std::vector<int>> &v, T heuristic, double epsilon = (double) 1.5, Q open_value,
                           Q focal_value) {
        visited.clear();
        std::priority_queue<Node, std::vector<Node>, CompareH> focal;
        GameBoard start(v);

        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic)), start});
        focal.push({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                    focal_value(0, start.GetHeuristic(heuristic)), start});

        //map link_open to find state and value in open set when pop state from focal
        link_open[start] = Node(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                                focal_value(0, start.GetHeuristic(heuristic)), start);
        visited[start] = 0;

        while (!focal.empty()) {
            std::set<Node>::iterator fmin = open.begin();
            //  open.erase(fmin);
            double f_min = *fmin.f;
            auto [f, g, h, hFocal, board] = focal.top();
            if (visited[board] != g) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(g);
            focal.pop();
            open.erase(Node(f, g, h, hFocal, board));


            if (hFocal == 0)
                return static_cast<int> g;

            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1) {
                    visited[next_board] = g + 1;
                    // int f = next_board.GetHeuristic(heuristic);
                    int h_new = next_board.GetHeuristic(heuristic);
                    if (link_open.find(next_board) != visited.end()) {
                        Node old_open = link_open[next_board];
                        open.erase(old_open);
                    }

                    open.insert(Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    //open.insert({g + 1, next_board.GetHeuristic(heuristic), next_board});
                    link_open[next_board] = Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new),
                                                 next_board);

                    if (open_value(g + 1, h_new) < epsilon * f_min) {
                        focal.push(Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    }
                }
            }

            fmin = open.begin();
            double f_head = *fmin.g + *fmin.h;

            if (open.size() && f_min < f_head) {
                for (std::set<Node>::iterator it = open.begin(); it != open.end(); ++it) {
                    if (*it.g + *it.h >= epsilon * f_head)
                        break;
                    if (*it.g + *it.h >= epsilon * f_min) {
                        focal.push({*it.g, *it.board.GetHeuristic(focal_search), *it.board});
                    }
                }
            }

        }
        return static_cast<int>(-1);
    }
};


#endif //FS_PROTOTYPE_FOCAL_SEARCH_H
