//
// Created by only_u on 2/29/24.
//

#ifndef FS_PROTOTYPE_RWFOCALSEARCH_H
#define FS_PROTOTYPE_RWFOCALSEARCH_H

#include "focal_search.h"
#include "vector"
#include "utils.h"

class RWFocalSearch : public BasicFocalSearch {
public:
    template<class T, class open_funct, class focal_funct>
    inline int FocalSearch
            (std::vector <std::vector<int>> &v, open_funct open_value, focal_funct focal_value, T heuristic,
            std::vector<double> epsilons = {1, (double)1.2, (double)1.5}
            ) {
        /*
         * focals[i] maintain fmin in range [epsilons[i] * fmin, epsilons[i + 1] * fmin]
         */
        assert(epsilons.size() >= 2);
        std::vector<std::priority_queue<Node, std::vector<Node>, CompareH>> focals(epsilons.size());


        visited.clear();
        GameBoard start(v);

        Node tmp = Node(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                        focal_value(0, start.GetHeuristic(heuristic)), start);
        link_open.emplace(start, tmp);
        visited[start] = 0;
        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic)), start});

        while (!open.empty()) {
            assert(!open.empty());

            double f_min = open.begin()->f;
            Node top_node = *open.begin();

            /*
             * scan non empty focals list
             */
            std::vector<int> seeds;
            for (int i = 0; i + 1 < focals.size(); ++i) {
                if (not focals[i].empty()) {
                    seeds.push_back(i);
                }
            }
            if (not seeds.empty()) {
                int tmp = generate_random_number(0, (int)seeds.size() - 1);
                assert(not focals[tmp].empty());
                top_node = focals[tmp].top();

                focals[tmp].pop();
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

                    for (int i = 0; i + 1 < epsilons.size(); ++i) {
                        if (epsilons[i] * f_min <= g + 1 + h_new and g + 1 + h_new <= epsilons[i + 1] * f_min)
                        focal.push(Node(open_value(g + 1, h_new), g + 1, h_new, focal_value(g + 1, h_new), next_board));
                    }
                }
            }
            /*
             * reorganize focal
             */
            auto fmin = open.begin();
            double f_head = fmin->g + fmin->h;

            for (int i = (int)epsilons.size() - 2; i >= 0; --i) {
                while (not focals[i].empty()) {
                    auto cur_top = focals[i].top();
                    if (epsilons[i] * f_head <= cur_top.f and cur_top.f <= epsilons[i + 1] * f_head)
                        break;
                    focals[i].pop();
                    if (i - 1 >= 0) {
                        if (epsilons[i - 1] * f_min <= cur_top.f and cur_top.f <= epsilons[i] * f_min) {
                            focals[i - 1].push(cur_top);
                        }
                    }
                }
            }

            if (!open.empty() && f_min < f_head) {
                int current_focal_idx = 0;
                /*
                 * only iterate Node have f in range [fmin, fhead]
                 */
                auto it = open.lower_bound(Node(f_min, -1, -1,-1, board));
                for (; it != open.end(); ++it) {
                    auto board = it->board;
                    while (current_focal_idx + 1 < epsilons.size() and it->g + it->h >= epsilons[current_focal_idx + 1] * f_head) {
                        ++current_focal_idx;
                    }
                    if (current_focal_idx + 1 >= epsilons.size()) {
                        break;
                    }
                    double new_f = it->f + it->g;
                    focals[current_focal_idx].push({new_f, it->g, board.GetHeuristic(heuristic),
                                focal_value(it->g, board.GetHeuristic(heuristic)), it->board});
                }
            }

        }
        return static_cast<int>(-1);
    }
};



#endif //FS_PROTOTYPE_RWFOCALSEARCH_H
