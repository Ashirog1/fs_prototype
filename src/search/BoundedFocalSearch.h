//
// Created by only_u on 2/26/24.
//

#ifndef FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
#define FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H

#include <vector>
#include "focal_search.h"

/*
 * Bounded Focal Search
 * focal will maintain Node have f in range [lower_epsilon * fmin, upper_epsilon * fmin]
 * didn't work
 */
// TODO: figure out how to find fmin?
class BoundedFocalSearch : public BasicFocalSearch {
public:
    template<class T, class open_funct, class focal_funct>
    inline int FocalSearch
            (std::vector<std::vector<int>> &v, open_funct open_value, focal_funct focal_value, T heuristic,
             double lower_epsilon = (double) 1.5, double upper_epsilon = (double) 2.0
            ) {
        visited.clear();
        GameBoard start(v);

        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic)), start});
        focal.push({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                    focal_value(0, start.GetHeuristic(heuristic)), start});

        //map link_open to find state and value in open set when pop state from focal
        Node tmp = Node(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                        focal_value(0, start.GetHeuristic(heuristic)), start);
        link_open.emplace(start, tmp);
        visited[start] = 0;

        while (!focal.empty()) {
            assert(!open.empty());

            double f_min = open.begin()->f;
            Node top_node = *open.begin();
            if (not focal.empty()) {
                top_node = focal.top();
                focal.pop();
            }
            auto [f, g, h, hFocal, board] = top_node;
            if (visited[board] != g) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(g);
            open.erase(Node(f, g, h, hFocal, board));

            if (hFocal == 0)
                return static_cast<int>(g);
            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1) {
                    visited[next_board] = g + 1;
                    int h_new = next_board.GetHeuristic(heuristic);
                    if (link_open.find(next_board) != link_open.end()) {
                        auto old_open = link_open.find(next_board);
                        open.erase(old_open->second);
                    }

                    open.insert(Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    link_open.emplace(next_board,
                                      Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new),
                                           next_board));

                    if (lower_epsilon * f_min  < open_value(g + 1, h_new) and
                        open_value(g + 1, h_new) < upper_epsilon * f_min) {
                        focal.push(Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    }
                }
            }

            auto fmin = open.begin();
            double f_head = fmin->g + fmin->h;

            if (!open.empty() && f_min < f_head) {
                /// TODO: find lower iterator faster by using lower_bound
                for (const auto &it: open) {
                    auto board = it.board;
                    if (it.g + it.h > upper_epsilon * f_head)
                        break;
                    if (it.g + it.h >= lower_epsilon * f_min) {
                        double new_f = it.g + it.h;
                        focal.push({new_f, it.g, board.GetHeuristic(heuristic),
                                    focal_value(it.g, board.GetHeuristic(heuristic)), it.board});
                    }
                }
            }

        }
        return static_cast<int>(-1);
    }
};


#endif //FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
