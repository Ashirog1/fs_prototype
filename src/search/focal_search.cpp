///
// Created by only_u on 12/21/23.
//

#include "focal_search.h"

BasicFocalSearch::BasicFocalSearch() {
    visited.clear();
    open.clear();
    link_open.clear();
    while (!focal.empty()) focal.pop();
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
    return a.f > b.f;
}

bool CompareH::operator()(const Node &a, const Node &b) {
    return a.hFocal > b.hFocal;
    return false;
}

