//
// Created by only_u on 12/21/23.
//
#include "game_board.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <random>

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
    std::vector<int> dx = {1, -1, 0, 0};
    std::vector<int> dy = {0, 0, 1, -1};
    for (int t = 0; t < 4; ++t) {
        int nx = cx + dx[t], ny = cy + dy[t];
        if (not gameBoard.inside(nx, ny)) continue;

        int next_encode = gameBoard.encode(nx, ny);
        std::swap(next_state.current[next_encode], next_state.current[base_index]);

        adj.emplace_back(next_state);

        std::swap(next_state.current[next_encode], next_state.current[base_index]);
    }
    return adj;
}

bool GameBoard::operator<(const GameBoard &oth) const {
    for (int i = 0; i < current.size(); i++) {
        if (current[i] != oth.current[i]) {
            return current[i] < oth.current[i];
        }
    }
    return false;

}

GameBoard::GameBoard() {

}

std::ostream &operator<<(std::ostream &os, const GameBoard &gameBoard) {
    for (int i = 0; i < gameBoard.h; ++i) {
        for (int j = 0; j < gameBoard.w; ++j) {
            os << gameBoard.current[i * gameBoard.w + j] << ' ';
        }
      //  os << '\n';
    }
    return os;
}


int random_in_range(int min, int max) {
    assert(min <= max);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}


GameBoard generator(int n, int n_move) {
    assert(n >= 2);
    /// generate init state
    std::vector<int> state(n * n);
    std::iota(state.begin(), state.end(), 1);
    state.back() = 0;
    /*
     * start with init state
     * with each move, random wap with neighbour
     */
    GameBoard gb(n, state);
    for (int i = 0; i < n_move; ++i) {
        auto neighbours = GetNeighbour(gb);
        int idx = random_in_range(0, (int)neighbours.size() - 1);
        gb = neighbours[idx];
    }
    return gb;
}



