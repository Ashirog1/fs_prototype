
#ifndef FS_PROTOTYPE_PANCAKE_BOARD_H
#define FS_PROTOTYPE_PANCAKE_BOARD_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>

class PancakeBoard {
    /*
     * Pancake sorting problem
     */
  private:
    int n;

  public:
    std::vector<int> stack;

    PancakeBoard() {}

    PancakeBoard(int _n) {
        n = _n;
        stack.resize(n);
        for (int i = 0; i < n; i++) {
            stack[i] = i + 1;  // Pancakes are labeled from 1 to n
        }
        std::random_shuffle(stack.begin(), stack.end());  // Random initial state
    }

    friend std::vector<PancakeBoard> GetNeighbour(PancakeBoard &pancakeBoard) {
        std::vector<PancakeBoard> adj;
        for (int i = 1; i < pancakeBoard.n; i++) {
            PancakeBoard newBoard = pancakeBoard;
            std::reverse(newBoard.stack.begin(), newBoard.stack.begin() + i + 1);
            adj.push_back(newBoard);
        }
        return adj;
    }

    friend int cost_move(PancakeBoard &pancakeBoard1, PancakeBoard &pancakeBoard2) {
        return 1;  // Each flip has a constant cost
    }

    int getDistanceToGo() {
        int distance = 0;
        for (int i = 0; i < n - 1; i++) {
            if (std::abs(stack[i] - stack[i + 1]) != 1) {
                distance++;
            }
        }
        return distance;
    }

    template <class T> inline double GetHeuristic(T heuristic) { return heuristic(stack); };

    void printState() {
        for (auto v : stack)
            std::cout << v << " ";
        std::cout << std::endl;
    }

    bool operator<(const PancakeBoard &oth) const {
        return stack < oth.stack;
    }

    friend std::ostream& operator<<(std::ostream& os, const PancakeBoard &pancakeBoard){
        os << pancakeBoard.n << " ";
        for (auto v : pancakeBoard.stack) {
            os << v << " ";
        }
        return os;
    }
};

double simpleHeuristic(const std::vector<int> &stack) {
    int misplaced = 0;
    for (int i = 0; i < stack.size() - 1; i++) {
        if (std::abs(stack[i] - stack[i + 1]) != 1) {
            misplaced++;
        }
    }
    return misplaced;
}

#endif //FS_PROTOTYPE_PANCAKE_BOARD_H

