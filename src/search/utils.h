//
// Created by only_u on 3/1/24.
//

#ifndef FS_PROTOTYPE_UTILS_H
#define FS_PROTOTYPE_UTILS_H

#include "random"


int generate_random_number(int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a random number between min and max
    std::uniform_int_distribution<int> dist(min, max);
    int random_number = dist(gen);

    return random_number;
};


#endif //FS_PROTOTYPE_UTILS_H
