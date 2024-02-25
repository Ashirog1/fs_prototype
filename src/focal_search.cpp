///
// Created by only_u on 12/21/23.
//

#include "focal_search.h"

focal_search::focal_search() {
    visited.clear();
    open.clear();
}

bool Node::operator<(const Node &oth) const {
    return f + g > oth.f + oth.g;
}

Node::Node(double _f, double _g, double _h, double _hFocal, const GameBoard &_board) {
    f = _f;
    g = _g;
    h = _h;
    board = _board;
    hFocal = _hFocal;
}

bool CompareG::operator()(const Node &a, const Node &b) {
    return a.g > b.g;
}

bool CompareH::operator()(const Node &a, const Node &b) {
    return false;
}

