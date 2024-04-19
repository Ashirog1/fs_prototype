//
// Created by only_u on 2/26/24.
//

#include <vector>
#include "focal_search.h"
#include "utils.h"

/*
 60/40 focal search
*/

struct cmp{
    bool operator() (const Node &a,const Node&b) const{
        if(a.hFocal!=b.hFocal)
         return a.hFocal < b.hFocal;
    if(a.g!=b.g)
    return a.g<b.g;
    return a.h<b.h;
    }
};

class ProbabilityFocalSearch : public BasicFocalSearch
{
public:
    std::set<Node,cmp> focalSet;

    template <class T, class open_funct, class focal_funct>
    inline int ProbabilitySearch(GameBoard &start, open_funct open_value, focal_funct focal_value, T heuristic,int &num_expansion,
                           double epsilon = (double)1.1, double pickRate = (double)0.6)
    {
        const auto nodeValue = [&](double g, GameBoard &board)
        {
            double h = board.GetHeuristic(heuristic);
            return Node(open_value(g, h), g, h, focal_value(g, h), board);
        };

        const auto assignValue =[&](double &f, double &g, double &h,double &hFocal,GameBoard &board,Node node )
        {
           f=node.f;
           g=node.g;
           h=node.h;
           hFocal=node.hFocal;
           board=node.board;
        };
        visited.clear();
        GameBoard startState=start;
        bool foundDestination = false;
        double minDistance = (double) INT_MAX;

        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic)), start});

        // map link_open to find state and value in open set when pop state from focal
        Node tmp = Node(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                        focal_value(0, start.GetHeuristic(heuristic)), start);

        focalSet.insert(nodeValue(0, start));
        link_open.emplace(start, tmp);
        visited[start] = 0;
        int dem=0;

        while (1)
        {
            assert(!open.empty());
            int pick = generate_random_number(0, 100);
            num_expansion = visited.size();

            double f,g,h,hFocal;
            GameBoard board;
            double f_min=open.begin()->f;
            //std::cout<<f_min<<'\n';
            //Pop from focal
            if (pick <= pickRate*100 && !focalSet.empty())
            {
                Node a=*focalSet.begin();
                assignValue(f,g,h,hFocal,board,a);
                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);

                focalSet.erase(focalSet.begin());
                open.erase(Node(f, g, h, hFocal, board));

                if (hFocal == 0)
                    return static_cast<int>(g);
            }
            // Pop from open
            else
            {
                //std::cout<<focalSet.size()<<'\n';
                Node a=*open.begin();
                assignValue(f,g,h,hFocal,board,a);

                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);
             
                open.erase(open.begin());
                focalSet.erase(Node(f, g, h, hFocal, board));
             

                if (hFocal == 0)
                    return static_cast<int>(g);
            }

            // board.printState();
             //std::cout<<'\n';
             //std::cout<<num_expansion<<'\n';
             
            for (GameBoard &next_board : GetNeighbour(board))
            {
               // std::cout<<g<<'\n';
                if (visited.find(next_board) == visited.end() or visited[next_board] > g + 1)
                {
                   // next_board.printState();
                    visited[next_board] = g + 1;
                    int h_new = next_board.GetHeuristic(heuristic);
                    /*
                     * delete old_value of new state in open
                     */
                    if (h_new == 0) {
                        foundDestination = true;
                        minDistance = std::min(minDistance, g + 1);
                        return static_cast<int> (g + 1);
                    }
                    if (link_open.find(next_board) != link_open.end())
                    {
                        auto old_open = link_open.find(next_board);
                        open.erase(old_open->second);
                    }
                    /*
                     * insert new node into open
                     */

                    auto check=open.insert(nodeValue(g + 1, next_board));

                    link_open.emplace(next_board,
                                      nodeValue(g + 1, next_board));
                    if (open_value(g + 1, h_new) < epsilon * f_min)
                    {
                        focalSet.insert(nodeValue(g + 1, next_board));
                    }
                }
            }
            if (foundDestination) {
                return static_cast<int> (minDistance);
            }

            auto f_head = open.begin()->f;
            
            if (!open.empty() && f_min < f_head)
            {
                /*
                 * update focal: insert new node from open to focal with f <= epsilon * fmin
                 */
                for(auto it=open.lower_bound(Node(f_min*epsilon,(double)0,(double)0,(double)0,board));it!=open.end();++it)
                {
                    //Node node=*it;
                    auto board = it->board;
                    if (it->f > epsilon * f_head)
                        break;
                    if (it->f >= epsilon * f_min)
                    {
                        focalSet.insert(nodeValue(it->g, board));
                    }
                }

            }
         
        }
                    return static_cast<int>(-1);

    }
};

//#endif // FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
