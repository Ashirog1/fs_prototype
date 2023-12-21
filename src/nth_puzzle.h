//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_NTH_PUZZLE_H
#define FS_PROTOTYPE_NTH_PUZZLE_H
#include <vector>
#include <algorithm>
class NthPuzzle {
    /*
     * NthPuzzle problem
     */
private:
    using state = std::vector<int>;

    NthPuzzle(const std::vector<std::vector<int>> &init_state);

    std::vector<int> current, final_state;
    int h, w;
    /*
     * helper func
     */
    int encode(int r, int c);
    bool inside(int r, int c);
public:
    NthPuzzle(int n, state init);
    explicit NthPuzzle(std::vector<std::vector<int>> init_state);
    std::vector<state> GetNeighbour();
};
#endif //FS_PROTOTYPE_NTH_PUZZLE_H
