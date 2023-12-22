//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_FOCAL_SEARCH_H
#define FS_PROTOTYPE_FOCAL_SEARCH_H

#include "game_board.h"
#include <map>
#include <queue>
#include <utility>

class Node {
public:
    double f, g;
    GameBoard board;
    Node(double _f, double _g, const GameBoard&_board);
    bool operator < (const Node &oth) const;
};

class focal_search {
    std::map<GameBoard, int> visited;
    std::priority_queue<Node, std::vector<Node>, std::greater<>> open;
public:
    focal_search();

    template<typename heuristic>
    void AStarSearch(std::vector<std::vector<int>>&v);
};


#endif //FS_PROTOTYPE_FOCAL_SEARCH_H
