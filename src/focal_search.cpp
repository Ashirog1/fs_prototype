///
// Created by only_u on 12/21/23.
//

#include "focal_search.h"

focal_search::focal_search() {
    visited.clear();
    while (not open.empty()) open.pop();
}


Node::Node(double _f, double _g, const GameBoard&_board) {
    f = _f; g = _g;
    board = _board;
}

bool Node::operator<(const Node &oth) const {
    return f + g > oth.f + oth.g;
}
