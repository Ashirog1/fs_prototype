//
// Created by only_u on 2/26/24.
//

#ifndef FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
#define FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H

#include <vector>
#include "focal_search.h"
#include "utils.h"

/*
 60/40 focal search
*/

class generalizedVersion : public BasicFocalSearch
{
public:
    std::set<Node,CompareH> focalSet;

    template <class T, class open_funct, class focal_funct>
    inline int FocalSearch(std::vector<std::vector<int>> &v, open_funct open_value, focal_funct focal_value, T heuristic,
                           double epsilon = (double)1.5, double pickRate = (double)0.6)
    {
        const auto nodeValue = [&](double g, GameBoard &board) {
            double h = board.GetHeuristic(heuristic);
            return Node(open_value(g, h), g, h, focal_value(g, h), board);
        };
        visited.clear();
        GameBoard start(v);

        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic)), start});

        // map link_open to find state and value in open set when pop state from focal
        Node tmp = Node(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                        focal_value(0, start.GetHeuristic(heuristic)), start);
        link_open.emplace(start, tmp);
        visited[start] = 0;
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

        while (1)
        {
            assert(!open.empty());
            double pick = generate_random_number(0, 1);
            //Pop from focal
            auto [f,g,h,hFocal,board];
            if (pick <= pickRate && !focal.empty())
            {
                double f_min = open.begin()->f;
                [f, g, h, hFocal, board] = focal.top();
                if (visited[board] != g)
                    continue;
                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);
                focal.pop();
                open.erase(Node(f, g, h, hFocal, board));

                if (hFocal == 0)
                    return static_cast<int>(g);

            }

            //Pop from open
            else
            {
                [f, g, h, hFocal, board] = open.top();
                if (visited[board] != g)
                    continue;
                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);
                open.pop();
                focalSet.erase(Node(f, g, h, hFocal, board));
                
                if(hFocal==0)
                    return static_cast<int>(g);
            }
                for (GameBoard &next_board : GetNeighbour(board))
                {
                    if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1)
                    {
                        visited[next_board] = g + 1;
                        int h_new = next_board.GetHeuristic(heuristic);
                        /*
                         * delete old_value of new state in open
                         */
                        if (link_open.find(next_board) != link_open.end())
                        {
                            auto old_open = link_open.find(next_board);
                            open.erase(old_open->second);
                        }
                        /*
                         * insert new node into open
                         */
                        open.insert(nodeValue(g + 1, next_board));
                        link_open.emplace(next_board,
                                          nodeValue(g + 1, next_board));
                        if (open_value(g + 1, h_new) < epsilon * f_min)
                        {
                            focal.push(nodeValue(g + 1, next_board));
                        }
                    }
                }
                
        return static_cast<int>(-1);

            }
    }
};

#endif // FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
