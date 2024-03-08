//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_FOCAL_SEARCH_H
#define FS_PROTOTYPE_FOCAL_SEARCH_H

#include "../problem/game_board.h"
#include "../heuristics.h"
#include <map>
#include <queue>
#include <utility>
#include <cassert>
#include <set>
#include<algorithm>

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

class BasicAStar {
    std::map<GameBoard, int> visited;
    //std::priority_queue<Node> open;
    std::set<Node> open;
    std::map<GameBoard, Node> link_open;
public:
    template<class T>
    inline int AStarSearch(std::vector<std::vector<int>> &v, T heuristic) {
        GameBoard start(v);
        open.insert({start.GetHeuristic(heuristic), 0, start.GetHeuristic(heuristic), 0, start});
        visited[start] = 0;
        while (not open.empty()) {
            auto fmin = open.begin();
            auto [f, g, h, fFocal, board] = *fmin;
            open.erase(fmin);
            if (visited[board] != f) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(f);
            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > f + 1) {
                    visited[next_board] = g + 1;
                    double h_new = next_board.GetHeuristic(heuristic);
                    open.insert({g + 1 + h_new, g + 1, static_cast<double>(h_new), 0, next_board});
                }
            }
        }
        return static_cast<int>(-1);
    }
};

/*
 * BasicFocalSearch (a* epsilon) algorithm
 */
class BasicFocalSearch {

protected:
//std::priority_queue<Node> open;
    std::set<Node> open;
// @brief visited:
    std::map<GameBoard, int> visited;
    std::priority_queue<Node, std::vector<Node>, CompareH> focal;
    std::map<GameBoard, Node> link_open;
public:
    BasicFocalSearch();

    template<class T, class open_funct, class focal_funct>
    inline int FocalSearch
            (std::vector<std::vector<int>> &v, open_funct open_value, focal_funct focal_value, T heuristic,
             double epsilon = (double) 1.5
            ) {
        /*
         * given g and gameboard, return current state
         * maybe this function take h as parameter as well?
         */
        const auto nodeValue = [&](double g, GameBoard &board) {
            double h = board.GetHeuristic(heuristic);
            return Node(open_value(g, h), g, h, focal_value(g, h), board);
        };

        bool foundDestination = false;
        double minDistance=(double)INT_MAX;

        visited.clear();
        GameBoard startState(v);

        Node startNode=nodeValue(0,startState);

        open.insert(startNode);
        focal.push(startNode);

        //map link_open to find state and value in open set when pop state from focal

        //Node tmp = nodeValue(0, start);
        link_open.emplace(startState, startNode);
        visited[startState] = 0;

        while (!open.empty()) {
            assert(!open.empty());
           // std::cout<<-2<<'\n';

            double f_min = open.begin()->f;

            auto [f, g, h, hFocal, board] = focal.top();

            if (visited[board] != g) continue;

            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(g);
            focal.pop();
            open.erase(Node(f, g, h, hFocal, board));


            // if (hFocal == 0)
            //     return static_cast<int>(g);


            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1) {
                    visited[next_board] = g + 1;
                    int h_new = next_board.GetHeuristic(heuristic);
                    if(h_new==0){
                        foundDestination=true;
                        minDistance=std::min(minDistance,g+1);
                        //return static_cast<int> g+1;
                    }
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
                    Node nextNode=nodeValue(g+1,next_board);
                    open.insert(nextNode);
                    link_open.emplace(next_board,
                                      nextNode);
                    if (open_value(g + 1, h_new) <= epsilon * f_min) {
                        focal.push(nextNode);
                    }
                }
            }

            if(foundDestination){
                return static_cast<int> (minDistance);
            }

            auto fmin = open.begin();
            double f_head = fmin->f;

            if (!open.empty() && f_min < f_head) {
                /*
                 * update focal: insert new node from open to focal with f <= epsilon * fmin
                 */
                Node middleNode=Node(f_min*epsilon,(double)-1,(double)-1,(double)-1,board);
                for(auto state=open.lower_bound(middleNode);state!=open.end();++state)
                {
                    //Node node=*it;
                    auto board = state->board;
                    if (state->f > epsilon * f_head)
                        break;
                    if (state->f >= epsilon * f_min)
                    {
                        Node focalNode=nodeValue(state->g,board);
                        focal.push(focalNode);
                    }
                }
                /*for (const auto &it: open) {
                    auto board = it.board;
                    if (it.g + it.h > epsilon * f_head)
                        break;
                    if (it.g + it.h <= epsilon * f_min) {
                        focal.push(nodeValue(it.g, board));
                    }
                }*/
            }

        }
        return static_cast<int>(-1);
    }
};


#endif //FS_PROTOTYPE_FOCAL_SEARCH_H
