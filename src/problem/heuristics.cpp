//
// Created by only_u on 12/21/23.
//

#include <complex>
#include <iostream>
#include "heuristics.h"

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

double open_funct(double g, double h) {
    return g + h;
}

double focal_funct(double g, double h) {
    return h;
}
