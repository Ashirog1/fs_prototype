///
// Created by only_u on 12/21/23.
//

#include "focal_search.h"

focal_search::focal_search() {
    visited.clear();
    while (not open.empty()) open.pop();
}

template<typename heuristic>
void focal_search::AStarSearch(std::vector<std::vector<int>>&v) {
    GameBoard start(v);
    open.push({0, heuristic(v), start});
    visited[start] = 0;

    while (not open.empty()) {
        auto [f, g, board] = open.top(); open.pop();
        if (visited[board] != f) continue;

        for (const auto&next_board : GetNeighbour(board)) {
            if (visited.find(next_board) == visited.end() or visited[next_board] > f + 1) {
                visited[next_board] = f + 1;
                open.push({f + 1, GetHeuristic<heuristic>(next_board), next_board});
            }
        }
    }
}

Node::Node(double _f, double _g, const GameBoard&_board) {
    f = _f; g = _g;
    board = _board;
}

bool Node::operator<(const Node &oth) const {
    return f + g < oth.f + oth.g;
}
