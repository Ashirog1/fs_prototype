//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_GAME_BOARD_H
#define FS_PROTOTYPE_GAME_BOARD_H

#include <vector>
#include <algorithm>
#include <iostream>
#include "Problem.h"

class GameBoard  {
    /*
     * GameBoard problem
     */
private:
    using state = std::vector<int>;

    int h, w;

    /*
     * helper heuristics
     */
    int encode(int r, int c);

    bool inside(int r, int c);

    std::pair<int, int> decode(int idx);

    std::vector<int> current;

public:
    GameBoard();

    GameBoard(int n, state init);

    explicit GameBoard(const std::vector<std::vector<int>> &init_state);

    friend std::vector<GameBoard> GetNeighbour(GameBoard &gameBoard);

    bool operator<(const GameBoard &oth) const;

    bool operator == (const GameBoard &oth) const{
        for(int i=0;i<current.size();i++){
            if(current[i]!=oth.current[i]){
                return false;
            }
        }
    return true;
    };

    friend double cost_move(GameBoard &tspBoard1,GameBoard &tspBoard2){
       return 1;

    }

    double getDistanceToGo(){
        return 0;
    }


    template<class T>
    inline double GetHeuristic(T heuristic) {
        return heuristic(w, current);
    };

    void printState(){
        for(auto v:current) std::cout<<v<<" ";
    };

    friend std::ostream& operator<<(std::ostream& os, const GameBoard &gameBoard);

};

int random_in_range(int min, int max);
GameBoard generator(int n, int n_move);



#endif //FS_PROTOTYPE_GAME_BOARD_H
