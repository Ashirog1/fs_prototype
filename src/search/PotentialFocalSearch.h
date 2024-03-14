//
// Created by only_u on 3/1/24.
//

#ifndef FS_PROTOTYPE_POTENTIALFOCALSEARCH_H
#define FS_PROTOTYPE_POTENTIALFOCALSEARCH_H

#include "focal_search.h"
#include "vector"

/*
 * the same as basic focal search
 * only comparator in focal list changed
 * sort by ud(n) = (eps * f_min - g(n)) / h(n)
 * however fmin is not constant -> sorting focal list every iterator
 */
/// TODO: group bucket with same value (g, h) for faster sorting
class PotentialFocalSearch : public BasicFocalSearch {
public:
    template<class T, class open_funct, class focal_funct>
    inline int PotentialSearch
            (GameBoard&start, open_funct open_value, focal_funct focal_value, T heuristic, int&num_expansion,
             double epsilon = 1.5
            ) {
        visited.clear();
        std::vector<Node> focal;;
        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic)), start});
        //map link_open to find state and value in open set when pop state from focal
        Node tmp = Node(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                        focal_value(0, start.GetHeuristic(heuristic)), start);
        link_open.emplace(start, tmp);
        visited[start] = 0;

        while (!open.empty()) {
            assert(!open.empty());
            num_expansion = visited.size();
            double f_min = open.begin()->f;
            Node top_node = *open.begin();
            if (not focal.empty()) {
                top_node = focal.back();
                focal.pop_back();
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
                    /*
                     * delete old_value of new state in open
                     */
                    if (link_open.find(next_board) != link_open.end()) {
                        auto old_open = link_open.find(next_board);
                        open.erase(old_open->second);
                    }
                    /*
                     * insert new node into open
                     */
                    open.insert(Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    link_open.emplace(next_board,
                                      Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new),
                                           next_board));
                    if (open_value(g + 1, h_new) < epsilon * f_min) {
                        focal.push_back(
                                Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    }
                }
            }

            auto fmin = open.begin();
            double f_head = fmin->g + fmin->h;

            if (!open.empty() && f_min < f_head) {
                /*
                 * update focal: insert new node from open to focal with f <= epsilon * fmin
                 */
                for (const auto &it: open) {
                    auto board = it.board;
                    if (it.g + it.h > epsilon * f_head)
                        break;
                    if (it.g + it.h <= epsilon * f_min) {
                        double new_f = it.g + it.h;
                        focal.push_back({new_f, it.g, board.GetHeuristic(heuristic),
                                         focal_value(it.g, board.GetHeuristic(heuristic)), it.board});
                    }
                }
            }
            /*
             * sorting focal by potential function
             */

            std::sort(focal.begin(), focal.end(), [&](const Node &a, const Node &b) {
                /*
                 * dealing with case h = 0 (end note)
                 */
                if (a.h == 0 or b.h != 0) {
                    // a > b
                    return false;
                } else if (a.h != 0 and b.h == 0) {
                    // a < b
                    return true;
                } else {
                    // sort by g
                    return a.g > b.g;
                }
                return (double) (epsilon * f_head - a.g) / a.h < (double) (epsilon * f_head - b.g) / b.h;
            });

        }
        return static_cast<int>(-1);
    }
};


#endif //FS_PROTOTYPE_POTENTIALFOCALSEARCH_H
