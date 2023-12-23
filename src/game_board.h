//
// Created by only_u on 12/21/23.
//

#ifndef FS_PROTOTYPE_GAME_BOARD_H
#define FS_PROTOTYPE_GAME_BOARD_H

#include <vector>
#include <algorithm>

class GameBoard {
    /*
     * GameBoard problem
     */
private:
    using state = std::vector<int>;

    int h, w;

    /*
     * helper heuristics
     */
    int encode(int r, int c);

    bool inside(int r, int c);

    std::pair<int, int> decode(int idx);

public:
    std::vector<int> current;
    GameBoard();

    GameBoard(int n, state init);

    explicit GameBoard(const std::vector<std::vector<int>> &init_state);

    friend std::vector<GameBoard> GetNeighbour(GameBoard &gameBoard);

    bool operator<(const GameBoard &oth) const;

    template<class T>
    inline double GetHeuristic(T heuristic) {
        return heuristic(w, current);
    }
};

#endif //FS_PROTOTYPE_GAME_BOARD_H
