//
// Created by only_u on 12/21/23.
//

#include <complex>
#include <iostream>
#include "heuristics.h"
#include <algorithm>
#include <queue>
#include <utility>

double HammingDistance(int size, const std::vector<int> &board) {
    int hammingDistance = 0;
    for (int i = 0; i < size * size; ++i) {
        if (board[i] != i + 1 and board[i] != 0) {
            ++hammingDistance;
        }
    }
    return hammingDistance;
}

double CartesianDistance(int size, const std::vector<int> &board) {
    double cartesianDistance = 0.0;
    for (int i = 0; i < size * size; ++i) {
        if (board[i] == 0) continue;
        int row = i / size;
        int col = i % size;
        if (board[i] - 1 != i) {
            int targetRow = (board[i] - 1) / size;
            int targetCol = (board[i] - 1) % size;
            cartesianDistance += std::sqrt(std::pow(row - targetRow, 2) + std::pow(col - targetCol, 2));
        }
    }
    return cartesianDistance;
}

double ManhattanDistance(int size, const std::vector<int> &board) {
    int manhattanDistance = 0;
    for (int i = 0; i < size * size; ++i) {
        if (board[i] == 0) continue;
        if (board[i] - 1 != i) {
            int targetRow = (board[i] - 1) / size;
            int targetCol = (board[i] - 1) % size;
            int row = i / size;
            int col = i % size;
            manhattanDistance += std::abs(row - targetRow) + std::abs(col - targetCol);
        }
    }
    return manhattanDistance;
}

double LinearConflictDistance(int size, const std::vector<int> &board) {
    std::vector<std::vector<int>> puzzle(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            puzzle[i][j] = board[i * size + j];
        }
    }
    int linearConflict = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            int tileA = puzzle[i][j];
            if (tileA == 0) continue; // Skip the empty space

            for (int k = j + 1; k < size; k++) {
                int tileB = puzzle[i][k];
                if (tileB == 0) continue; // Skip the empty space

                if ((tileA / size == i) && (tileB / size == i) && (tileA > tileB)) {
                    linearConflict += 2;
                }
            }
        }
    }

    // Check columns for conflicts
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            int tileA = puzzle[j][i];
            if (tileA == 0) continue; // Skip the empty space

            for (int k = j + 1; k < size; k++) {
                int tileB = puzzle[k][i];
                if (tileB == 0) continue; // Skip the empty space

                if ((tileA % size == i) && (tileB % size == i) && (tileA > tileB)) {
                    linearConflict += 2;
                }
            }
        }
    }

    return linearConflict + ManhattanDistance(size, board);

}

double MST(int size,const std::vector<int> visited, const std::set<int> unvisited, const std::vector<std::vector<double>> dis ){
    if(visited.size()==size+1) return 0;
    if(unvisited.size()==0) return dis[visited[size-1]][visited[0]];
    double total=0;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double,int>>, std::greater<std::pair<double,int>>> prim;
    std::vector<double> d(size,INT_MAX);
    std::set<int> remain=unvisited;
    if(visited.size()){
        double min_current=INT_MAX;
        double min_depot=INT_MAX;
        for(auto v:unvisited){
            min_current=std::min(min_current,dis[visited[visited.size()-1]][v]);
            min_depot=std::min(min_depot, dis[visited[0]][v]);
        }
        total=total+min_current+min_depot;     
    }

    d[*remain.begin()]=0;
    prim.push(std::make_pair(0,*remain.begin()));

    while(prim.size()){
       // std::cout<<"check"<<'\n';
        if(remain.empty()) break;
        auto top=prim.top();
        prim.pop();
        if(top.first!=d[top.second]){
            continue;
        }
        total+=d[top.second];
        d[top.second]=INT_MIN;
        remain.erase(top.second);
        for(auto v:remain){
            if(d[v]>dis[top.second][v]){
               d[v]=dis[top.second][v];
               prim.push(std::make_pair(d[v],v));
            }
        }
    }
    return total;
}

double open_funct(double g, double h) {
    return g + h;
}

double focal_funct(double g, double h) {
    return h;
}

double distance_to_go_funct(double g,double h, double weight,double initial){
    return g+std::max((double)1,weight*h/initial);
}

