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
    double f,g, h;
    double hFocal;
    GameBoard board;

    Node(double _f,double _g, double _h, double _hFocal, const GameBoard &_board);

    bool operator<(const Node &oth) const;
};

/// focal comparator


//For open list
struct CompareG {  
    bool operator()(const Node &a, const Node &b);
};


//For focal list
struct CompareH{  
    bool operator()(const Node &a, const Node &b);
};

class focal_search {
    std::map<GameBoard, int> visited;
    //std::priority_queue<Node> open;
    std::set<Node> open;
    std::map<GameBoard, Node> link_open;

public:
    focal_search();

    template<class T>
    inline int AStarSearch(std::vector<std::vector<int>> &v, T heuristic) {
        GameBoard start(v);
        open.push({0, start.GetHeuristic(heuristic), start});
        visited[start] = 0;


        while (!open.empty()) {
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

    template<class T, class Q>
    inline int FocalSearch(std::vector<std::vector<int>> &v, T heuristic, double epsilon = (double) 1.5,Q open_value,Q focal_value ) {
        visited.clear();
        std::priority_queue<Node, std::vector<Node>, CompareH> focal;
        GameBoard start(v);
    
        open.insert({open_value(0,start.GetHeuristic(heuristic)),0,start.GetHeuristic(heuristic),focal_value(0,start.GetHeuristic(heuristic)),start});
        focal.push({open_value(0,start.GetHeuristic(heuristic)),0,start.GetHeuristic(heuristic),focal_value(0,start.GetHeuristic(heuristic)),start});

        //map link_open to find state and value in open set when pop state from focal
        link_open[start] = Node(open_value(0,start.GetHeuristic(heuristic)),0,start.GetHeuristic(heuristic),focal_value(0,start.GetHeuristic(heuristic)),start);
        visited[start] = 0;
        
        while(! focal.empty()){
            std::set<Node>::iterator fmin = open.begin();
          //  open.erase(fmin);
            double f_min = *fmin.f;
            auto [f,g, h,hFocal,board] = focal.top();
            if (visited[board] != g) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(g);
            focal.pop();
            open.erase(Node(f,g,h,hFocal,board));

           
            if(hFocal==0)
                return static_cast<int> g;

            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1) {
                    visited[next_board] = g + 1;
                   // int f = next_board.GetHeuristic(heuristic);
                    int h_new=next_board.GetHeuristic(heuristic);
                    if(link_open.find(next_board)!=visited.end())
                    {
                        Node old_open=link_open[next_board];
                        open.erase(old_open);
                    }

                    open.insert(Node(open_value(g+1,h_new),g+1,h_new,focal_value(g+1,h_new),next_board));
                    //open.insert({g + 1, next_board.GetHeuristic(heuristic), next_board});
                    link_open[next_board]=Node(open_value(g+1,h_new),g+1,h_new,focal_value(g+1,h_new),next_board);
                    
                    if(open_value(g+1,h_new)<epsilon*f_min)
                    {
                        focal.push(Node(open_value(g+1,h_new),g+1,h_new,focal_value(g+1,h_new),next_board));
                    }
                }
            }

            fmin = open.begin();
            double f_head = *fmin.g + *fmin.h;

            if(open.size() &&  f_min<f_head)
            {
                for (std::set<Node>::iterator it = open.begin(); it != open.end(); ++it) {
                          if(*it.g+*it.h>=epsilon*f_head)
                              break;
                          if(*it.g+*it.h>=epsilon*f_min)
                          {
                              focal.push({*it.g, *it.board.GetHeuristic(focal_search), *it.board});
                          }
                }
            }
            
            }
        return static_cast<int>(-1);
    }
    
    template<class T>
    inline int FocalSearchWithLowerBound(std::vector<std::vector<int>> &v, T heuristic, T focal_heuristic, double epsilon = (double) 1.5,double lowerBound=1.2) {
        visited.clear();
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
                    //skip until lowerbound 
                    if(cur_h<lowerBound*h_min)
                        continue;
                    if (cur_h > epsilon * h_min) break;
                    open.pop();

                    focal.push({f_, board_.GetHeuristic(focal_heuristic), board_});
                }
            }
//            assert(focal.size() > 0);
            auto [f,g,board]
            //if focal empty pop from open set
            if (focal.empty()) 
            {
                [f,g,board]=open.top()
                open.pop()
            }
            else
            {
              [f, g, board] = focal.top();
               focal.pop();
            };
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
   

    template<class T>
    inline int RandomWeightedFocal(std::vector<std::vector<int>> &v, T heuristic, T focal_heuristic, std::vector<double> epsilons = {1.2, 1.3}) {
        GameBoard start(v);
        open.push({0, start.GetHeuristic(heuristic), start});
        visited[start] = 0;
        std::priority_queue<Node, std::vector<Node>, CompareG> focal[epsilons.size()];
        double best_h_score = 0;

        while (not open.empty()) {
            {
                /// update focal
                auto [f, g, board] = open.top();
                double h_min = f + g;
                best_h_score = std::max(best_h_score, h_min);
                int focal_idx = 0;
                double l = 1.0, r = epsilons[0];

                while (not open.empty()) {
                    auto [f_, g_, board_] = open.top();
                    double cur_h = f_ + g_;
                    if (cur_h > best_h_score * epsilons.back()) break;
                    if (cur_h > best_h_score * epsilons[focal_idx]) {
                        ++focal_idx;
                    }
                    open.pop();

                    focal[focal_idx].push({f_, board_.GetHeuristic(focal_heuristic), board_});
                }
            }
//            assert(focal.size() > 0);
            /// find node to expand
            double f, g; GameBoard board;
            {
                int focal_set = RNG::RandUniform(0, epsilons.size() - 1);
                if (focal[focal_set].empty()) break;
                auto [f_, g_, board_] = focal[focal_set].top();
                f = f_; g = g_; board = board_;
                focal[focal_set].pop();
            }
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
