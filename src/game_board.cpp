//
// Created by only_u on 12/21/23.
//
#include "game_board.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

GameBoard::GameBoard(int n, state init) {
    h = n;
    w = n;
    current.assign(h * w, -1);
    current = init;
}

GameBoard::GameBoard(const std::vector<std::vector<int>> &init_state) {
    h = init_state.size();
    w = init_state[0].size();
    /*
     * assert init_state is valid
     */
    for (int i = 0; i < h; ++i) assert(init_state[i].size() == w);

    /*
     * concat init_state
     */
    current.clear();
    for (const auto &v: init_state) for (const auto &k: v) current.push_back(k);
}

int GameBoard::encode(int r, int c) {
    return r * w + c;
}

bool GameBoard::inside(int r, int c) {
    return 0 <= r and r < h and 0 <= c and c < w;
}

std::pair<int, int> GameBoard::decode(int idx) {
    return std::pair<int, int>(idx / w, idx % w);
}

std::vector<GameBoard> GetNeighbour(GameBoard &gameBoard) {
    int base_index = -1;
    {
        /*
         * find index with value = 0 (only tile moveable)
         */
        auto it = std::find(gameBoard.current.begin(), gameBoard.current.end(), 0);
        base_index = std::distance(gameBoard.current.begin(), it);
    }
    auto [cx, cy] = gameBoard.decode(base_index);
    /// try to move
    auto next_state = gameBoard;
    std::vector<GameBoard> adj = {};
    for (int dx: {-1, 1}) {
        for (int dy: {-1, 1}) {
            int nx = cx + dx, ny = cy + dy;
            if (not gameBoard.inside(nx, ny)) continue;

            int next_encode = gameBoard.encode(nx, ny);
            std::swap(next_state.current[next_encode], next_state.current[base_index]);

            adj.emplace_back(next_state);

            std::swap(next_state.current[next_encode], next_state.current[base_index]);
        }
    }
    return adj;
}

bool GameBoard::operator<(const GameBoard &oth) const {
    return current < oth.current;
}

GameBoard::GameBoard() {

}

template<typename heuristic>
double GetHeuristic(GameBoard &gameBoard) {
   return heuristic(gameBoard);
}



