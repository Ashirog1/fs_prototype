#include "tsp_board.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <random>

bool TspBoard::operator<(const TspBoard &oth) const {
    if(visited.size()!=oth.visited.size()) return true;
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] != oth.visited[i]) {
            return visited[i] < oth.visited[i];
        }
    }
    return false;

}