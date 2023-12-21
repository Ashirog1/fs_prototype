//
// Created by only_u on 12/21/23.
//
#include "nth_puzzle.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

NthPuzzle::NthPuzzle(int n, state init) {
    h = n; w = n;
    current.assign(h * w, -1);
    current = init;
    final_state = current;
    std::iota(final_state.begin(), final_state.end(), 1);
    final_state.back() = 0;
}

NthPuzzle::NthPuzzle(const std::vector<std::vector<int>> & init_state) {
    h = init_state.size(); w = init_state[0].size();
    /*
     * assert init_state is valid
     */
    for (int i = 0; i < h; ++i) assert(init_state[i].size() == w);

    /*
     * concat init_state
     */
    current.clear();
    for (const auto&v : init_state) for (const auto&k : v) current.push_back(k);

    std::iota(final_state.begin(), final_state.end(), 1);
    final_state.back() = 0;
}

int NthPuzzle::encode(int r, int c) {
    return r * w + c;
}

bool NthPuzzle::inside(int r, int c) {
    return false;
}


