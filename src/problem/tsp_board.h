//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_GAME_BOARD_H
#define FS_PROTOTYPE_GAME_BOARD_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include "Problem.h"
#include "game_board.h"

class TspBoard {
    /*
     * GameBoard problem
     */
private:
   // using state = std::vector<int>;
    int n;

    std::vector<int> visited;
    std::vector<int> check_visited;
    std::set<int> unvisited;
    std::vector<std::vector<int>> dis_matrix;
    /*
     * helper heuristics
     */

public:
    TspBoard(int n, std::vector<std::vector<int>> distance){
        visited.clear();
        check_visited.resize(n,0);
        dis_matrix=distance;
        for(int i=0;i<n;i++) unvisited.insert(i);
    };



    friend std::vector<TspBoard> GetNeighbour(TspBoard &tspBoard){
        std::vector<TspBoard> adj;
         for(int i=0;i<tspBoard.n;i++){
            if(tspBoard.check_visited[i]==0){
                TspBoard newBoard=tspBoard;
                newBoard.visited.push_back(i);
                newBoard.check_visited[i]=1;
                newBoard.unvisited.erase(i);
                adj.push_back(newBoard);
            }
            
         }
         return adj;
    }
        

    template<class T>
    inline double GetHeuristic(T heuristic)  {
        return heuristic(n, visited,unvisited,dis_matrix);
    };

    void printState(){
        for(auto v:visited) std::cout<<v<<" ";
    };

    bool operator == (const TspBoard &oth) const{
        if(n!=oth.n) return true;
        if(visited.size()!=oth.visited.size()) return true;
        for(int i=0;i<visited.size();i++){
            if(visited[i]!=oth.visited[i]){
                return true;
            }
        }
    return false;
    };

};



#endif //FS_PROTOTYPE_GAME_BOARD_H
