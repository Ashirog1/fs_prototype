//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_FOCAL_SEARCH_H
#define FS_PROTOTYPE_FOCAL_SEARCH_H

#include "../problem/game_board.h"
#include "../problem/heuristics.h"
#include <climits>
#include <map>
#include <queue>
#include <utility>
#include <cassert>
#include <set>
#include<algorithm>

template<class G>
class Node {
public:
    double f, g, h;
    double hFocal;
    G board;

    Node(double _f, double _g, double _h, double _hFocal, G _board){
         f = _f;
         g = _g;
         h = _h;
         board = _board;
         hFocal = _hFocal;
    };

    bool operator < (const Node<G> &oth) const{
        if (f != oth.f)
        return f < oth.f;
        if (g != oth.g)
        return g < oth.g;
        if (hFocal != oth.hFocal)
        return hFocal < oth.hFocal;
        return board < oth.board;
    };
};

/// focal comparator


//For open list
template<class G>
struct CompareG {
    bool operator()(const Node<G> &a, const Node<G> &b){
         if(a.f!=b.f)
         return a.f > b.f;
         if(a.g!=b.g)
         return a.g>b.g;
         return a.h>b.h;
    }
};


//For focal list
template<class G>
struct CompareH {
    bool operator()(const Node<G> &a, const Node<G> &b){
         if(a.hFocal!=b.hFocal)
         return a.hFocal > b.hFocal;
         if(a.g!=b.g)
         return a.g>b.g;
         if(a.h!=b.h)
         return a.h>b.h;
         return b.board<a.board;
    }
};

template<class G>
class BasicAStar {
    std::map<G, double> visited;
    //std::priority_queue<Node> open;
    std::set<Node<G>> open;
  //  std::map<G, Node<G>> link_open;
public:
     template<class T>
    inline int AStarSearch(G start, T heuristic, int &num_expansion) {
        open.insert({start.GetHeuristic(heuristic), (double)0, start.GetHeuristic(heuristic), (double)0, start});
       // std::cout<<start.GetHeuristic(heuristic)<<'\n';
        visited[start] = 0;
        while ( open.size()) {
            num_expansion = visited.size();
            auto fmin = open.begin();
            auto [f, g, h, hFocal, board] = *fmin;
   
           // std::cout<<"state"<<'\n';
           // board.printState();
           // std::cout<<'\n';
           // std::cout<<visited[board]<<" "<<g<<" "<<h<<'\n';
            open.erase(fmin);


            if (visited[board] != g) continue;
            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(f);

            for (G &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() || visited[next_board] > g+cost_move(board,next_board)) {
                    visited[next_board] = g + cost_move(board,next_board);
                    //visited[next_board]=1;
                    double h_new = next_board.GetHeuristic(heuristic);
                    // if (h_new == 0) {
                    //     return g + cost;
                    // }
                    open.insert({g + cost_move(board,next_board) + h_new, g + cost_move(board,next_board), static_cast<double>(h_new), 0, next_board});
                }
            }

        }
        return static_cast<int>(-1);
    }
};

/*
 * BasicFocalSearch (a* epsilon) algorithm
 */
template<class G>
class BasicFocalSearch {

protected:
//std::priority_queue<Node> open;
    std::set<Node<G>> open;
// @brief visited:
    std::map<G, int> visited;
    std::priority_queue<Node<G>, std::vector<Node<G>>, CompareH<G>> focal;
    std::map<G, Node<G>> link_open;
    double C;
public:
    BasicFocalSearch(){
        visited.clear();
        open.clear();
        link_open.clear();
        while (!focal.empty()) focal.pop();
    };

    template<class T, class open_funct, class focal_funct>
    inline int FocalSearch
            (G &start, open_funct open_value, focal_funct focal_value, T heuristic,
             int &num_expansion,
             double epsilon = (double) 1.1,double w = (double) 1.0
            ) {
        /*
         * given g and gameboard, return current state
         * maybe this function take h as parameter as well?
         */
        const auto nodeValue = [&](double g, G &board) {
            double h = board.GetHeuristic(heuristic);
            return Node(open_value(g, h), g, h, focal_value(g, h,board.getDistanceToGo(),C,w), board);
        };

        bool foundDestination = false;
        double minDistance = (double) INT_MAX;

        visited.clear();    

        G startState = start;

        Node<G> startNode = nodeValue(0, startState);

        open.insert(startNode);
        focal.push(startNode);

        link_open.emplace(startState, startNode);
        visited[startState] = 0;

        while (!open.empty()) {
            assert(!open.empty());
            num_expansion = visited.size();
//            std::cout << open.size() << '\n';
            double f_min = open.begin()->f;

            auto [f, g, h, hFocal, board] = focal.top();
          //  if(focal.size()==0) std::cout<<"0set"<<'\n';

         //   board.printState();
          //  std::cout<<'\n';

            focal.pop();
          //  board.printState();
            // std::cout<<h<<'\n';
           // std::cout<<board<<'\n';
            if (visited[board] != g) continue;  
            // if(board==GameBoard(4,{1,2,7,3,5,6,4,8,9,10,11,12,13,0,14,15})){
            //     GameBoard newBoard=GameBoard(4,{1,2,7,3,5,6,4,8,9,10,11,12,13,0,14,15});
            //    // std::cout<<"check "<<visited[newBoard]<<'\n';

            // }

            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(g);
            open.erase(Node<G>(f, g, h, hFocal, board));

            // board.printState();
            // std::cout<<'\n';
          //  std::cout<<num_expansion<<'\n';

            // if (hFocal == 0)
            //     return static_cast<int>(g);


            for (G &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() || visited[next_board] > g + cost_move(board,next_board)) {
                    visited[next_board] = g + cost_move(board,next_board);
                    int h_new = next_board.GetHeuristic(heuristic);
                    // if (h_new == 0) {
                    //     foundDestination = true;
                    //     minDistance = std::min(minDistance, g + );
                    //     return static_cast<int> (g + 1);
                    // }
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
                    Node<G> nextNode = nodeValue(g + cost_move(board,next_board), next_board);
                    open.insert(nextNode);
                    link_open.emplace(next_board,
                                      nextNode);
                    if (open_value(g + cost_move(board,next_board), h_new) <= epsilon * f_min) {
                        focal.push(nextNode);
                    }
                }
            }

            if (foundDestination) {
                return static_cast<int> (minDistance);
            }

            auto fmin = open.begin();
            double f_head = fmin->f;

            
                    // for (auto state = open.begin(); state != open.end(); ++state) {
                    //     auto board = state->board;
                    //     if (state->f > epsilon * f_min)
                    //         break;
                    //     else {
                    //         Node focalNode = nodeValue(state->g, board);
                    //         focal.push(focalNode);
                    //     }
                    // }

            if (!open.empty() && f_min < f_head) {  
                /*
                 * only first extraction will run this block
                 * update focal with node have f <= fmin * epsilon
                 */
                

                /*
                 * update focal: insert new node from open to focal with epsilon * fmin <= f <= epsilon * f_head
                 */
                Node<G> middleNode = Node<G>(f_min * epsilon, (double) -1, (double) -1, (double) -1, board);
                for (auto state = open.lower_bound(middleNode); state != open.end(); ++state) {
                    //Node node=*it;
                    auto board = state->board;
                    if (state->f > epsilon * f_head)
                        break;
                    if (state->f >= epsilon * f_min) {
                        Node<G> focalNode = nodeValue(state->g, board);
                        focal.push(focalNode);
                    }
                }
            }
        }
        return static_cast<int>(-1);
    }
};


#endif //FS_PROTOTYPE_FOCAL_SEARCH_H
