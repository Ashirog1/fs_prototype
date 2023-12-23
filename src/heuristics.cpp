//
// Created by only_u on 12/21/23.
//

#include <complex>
#include "heuristics.h"

double HammingDistance(int size, std::vector<int> board) {
    int hammingDistance = 0;
    for (int i = 0; i < size * size; ++i) {
        if (board[i] != i + 1 and board[i] != 0) {
            ++hammingDistance;
        }
    }
    return hammingDistance;
}
double CartesianDistance(int size, std::vector<int> board) {
    double cartesianDistance = 0.0;
    for (int i = 0; i < size * size; ++i) {
        if (board[i] == 0) continue;
        int row = i / size;
        int col = i % size;
        if (board[i] != i) {
            int targetRow = (board[i] - 1) / size;
            int targetCol = (board[i] - 1) % size;
            cartesianDistance += std::sqrt(std::pow(row - targetRow, 2) + std::pow(col - targetCol, 2));
        }
    }
    return cartesianDistance;
}

double ManhattanDistance(int size, std::vector<int> board) {
    int manhattanDistance = 0;
    for (int i = 0; i < size; ++i) {
        if (board[i] == 0) continue;
        if (board[i] != i) {
            int targetRow = board[i] / size;
            int targetCol = board[i] % size;
            int row = i / size;
            int col = i % size;
            manhattanDistance += std::abs(row - targetRow) + std::abs(col - targetCol);
        }
    }
    return manhattanDistance;
}