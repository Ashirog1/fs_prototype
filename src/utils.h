//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_UTILS_H
#define FS_PROTOTYPE_UTILS_H

#include <vector>
#include <iostream>
#include <random>
#include <chrono>

namespace gui_visualize {
    void print();
};

namespace RNG {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    inline int RandUniform(int l, int r) {
        return l + rng() % (r - l + 1);
    }
};

#endif //FS_PROTOTYPE_UTILS_H
