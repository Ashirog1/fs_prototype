
#include <vector>
#include "focal_search.h"
#include "utils.h"

/*
 Distance to go Focal Search
*/


class DistanceToGoFocalSearch : public BasicFocalSearch
{
public:

    template<class T, class open_funct, class focal_funct>
    inline int DistanceToGoSearch
            (GameBoard &start, open_funct open_value, focal_funct focal_value, T heuristic,
             int &num_expansion,
             double epsilon = (double) 1.1, double weight = (double) 1.1
            ) {
        double dGoal = start.GetHeuristic(heuristic);
        const auto nodeValue = [&](double g, GameBoard &board,double dGoal) {
            double h = board.GetHeuristic(heuristic);
            return Node(open_value(g, h), g, h, focal_value(g,h,weight,dGoal), board);
        };

        bool foundDestination = false;
        double minDistance = (double) INT_MAX;
    

        visited.clear();

        GameBoard startState = start;

        Node startNode = nodeValue(0, startState,dGoal);

        open.insert(startNode);
        focal.push(startNode);

        link_open.emplace(startState, startNode);
        visited[startState] = 0;

        while (!open.empty()) {
            assert(!open.empty());
            num_expansion = visited.size();
//            std::cout << open.size() << '\n';
            double f_min = open.begin()->f;

            auto [f, g, h, hFocal, board] = focal.top();

            focal.pop();

            if (visited[board] != g) continue;

            if (board.GetHeuristic(heuristic) == 0) return static_cast<int>(g);
            open.erase(Node(f, g, h, hFocal, board));

          //  board.printState();
          //  std::cout<<'\n';
          //  std::cout<<num_expansion<<'\n';

            // if (hFocal == 0)
            //     return static_cast<int>(g);


            for (GameBoard &next_board: GetNeighbour(board)) {
                if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1) {
                    visited[next_board] = g + 1;
                    int h_new = next_board.GetHeuristic(heuristic);
                    if (h_new == 0) {
                        foundDestination = true;
                        minDistance = std::min(minDistance, g + 1);
                        return static_cast<int> (g + 1);
                    }
                    /*
                     * delete old_value of new state in open
                     */
                    if (link_open.find(next_board) != link_open.end()) {
                        auto old_open = link_open.find(next_board);
                        open.erase(old_open->second);
                    }
                    /*
                     * insert new node into open
                     */
                    Node nextNode = nodeValue(g + 1, next_board,dGoal);
                    open.insert(nextNode);
                    link_open.emplace(next_board,
                                      nextNode);
                    if (open_value(g + 1, h_new) <= epsilon * f_min) {
                        focal.push(nextNode);
                    }
                }
            }

            if (foundDestination) {
                return static_cast<int> (minDistance);
            }

            auto fmin = open.begin();
            double f_head = fmin->f;

            
                    // for (auto state = open.begin(); state != open.end(); ++state) {
                    //     auto board = state->board;
                    //     if (state->f > epsilon * f_min)
                    //         break;
                    //     else {
                    //         Node focalNode = nodeValue(state->g, board);
                    //         focal.push(focalNode);
                    //     }
                    // }

            if (!open.empty() && f_min < f_head) {  
                /*
                 * only first extraction will run this block
                 * update focal with node have f <= fmin * epsilon
                 */
                

                /*
                 * update focal: insert new node from open to focal with epsilon * fmin <= f <= epsilon * f_head
                 */
                Node middleNode = Node(f_min * epsilon, (double) -1, (double) -1, (double) -1, board);
                for (auto state = open.lower_bound(middleNode); state != open.end(); ++state) {
                    //Node node=*it;
                    auto board = state->board;
                    if (state->f > epsilon * f_head)
                        break;
                    if (state->f >= epsilon * f_min) {
                        Node focalNode = nodeValue(state->g, board,dGoal);
                        focal.push(focalNode);
                    }
                }
            }
        }
        return static_cast<int>(-1);
    }

};

//#endif // FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
