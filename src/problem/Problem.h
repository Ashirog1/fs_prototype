//
// Created by only_u on 3/29/24.
//

#ifndef FS_PROTOTYPE_PROBLEM_H
#define FS_PROTOTYPE_PROBLEM_H
#include <vector>

class Problem {
public:
    virtual ~Problem() {}
    virtual bool isGoal(const Problem& problem) const = 0;
    virtual std::vector<std::vector<Problem>> getSuccessors(const Problem & problem) const = 0;
    virtual int heuristic(const Problem& problem) const = 0;
};


#endif //FS_PROTOTYPE_PROBLEM_H
