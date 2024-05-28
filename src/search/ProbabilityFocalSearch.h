//
// Created by only_u on 2/26/24.
//

#include "focal_search.h"
#include "utils.h"
#include <vector>

/*
 60/40 focal search
*/

template <class G> struct cmp {
    bool operator()(const Node<G> &a, const Node<G> &b) const {
        if (a.hFocal != b.hFocal)
            return a.hFocal < b.hFocal;
        if (a.g != b.g)
            return a.g < b.g;
        if(a.h!=b.h)
        return a.h < b.h;
        return a.board < b.board;

    }
};

template <class G> class ProbabilityFocalSearch {
  public:
    double C;
    std::set<Node<G>> open;
    std::map<G, double> visited;
    std::map<G, Node<G>> link_open;
    std::set<Node<G>, cmp<G>> focalSet;
    template <class T, class open_funct, class focal_funct>
    inline int ProbabilitySearch(G &start, open_funct open_value, focal_funct focal_value, T heuristic,int &num_expansion,
                           double epsilon = (double)1.1, double w =(double) 1.0 ,double pickRate = (double)0.6)
    {
        const auto nodeValue = [&](double g, G &board)
        {
            double h = board.GetHeuristic(heuristic);
            return Node<G>(open_value(g, h), g, h, focal_value(g, h, board.getDistanceToGo(), C, w), board);
        };

        const auto assignValue = [&](double &f, double &g, double &h, double &hFocal, G &board, Node<G> node) {
            f = node.f;
            g = node.g;
            h = node.h;
            hFocal = node.hFocal;
            board = node.board;
        };
        visited.clear();
        G startState = start;
        bool foundDestination = false;
        double minDistance = (double)INT_MAX;

        open.insert({open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                     focal_value(0, start.GetHeuristic(heuristic), start.getDistanceToGo(), C, w), start});

        // map link_open to find state and value in open set when pop state from focal
        Node<G> tmp = Node<G>(open_value(0, start.GetHeuristic(heuristic)), 0, start.GetHeuristic(heuristic),
                              focal_value(0, start.GetHeuristic(heuristic), start.getDistanceToGo(), C, w), start);

        focalSet.insert(nodeValue(0, start));
        link_open.emplace(start, tmp);
        visited[start] = 0;
        int dem = 0;

        while (!open.empty()) {
           // assert(!open.empty());
            int pick = generate_random_number(0, 100);
            num_expansion = visited.size();
             if(num_expansion >= 40000000){
                num_expansion = -1;
                return -1;
            }

            double f, g, h, hFocal;
            G board;
            double f_min=open.begin()->f;
            
            if (pick <= pickRate*100 && !focalSet.empty())
            {
                Node<G> a=*focalSet.begin();
                assignValue(f,g,h,hFocal,board,a);
                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);
                int a1=focalSet.size();
                focalSet.erase(focalSet.begin());
                int b1=focalSet.size();
                open.erase(Node<G>(f, g, h, hFocal, board));

                if (hFocal == 0)
                    return static_cast<double>(g);
            }
            // Pop from open
            else {
                Node<G> a = *open.begin();
                assignValue(f, g, h, hFocal, board, a);

                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<double>(g);
             
                open.erase(open.begin());
                int a1=focalSet.size();

                focalSet.erase(Node<G>(f, g, h, hFocal, board));
             

                if (hFocal == 0)
                    return static_cast<double>(g);
            }
          

            if(visited[board]!=g) continue;
             
             
            for (G &next_board : GetNeighbour(board))
            {
                if (visited.find(next_board) == visited.end() || visited[next_board] > g + cost_move(board,next_board))
                {
                    
                    visited[next_board] = g + cost_move(board,next_board);
                    double h_new = next_board.GetHeuristic(heuristic);
                   
                    if (link_open.find(next_board) != link_open.end()) {
                        auto old_open = link_open.find(next_board);
                        open.erase(old_open->second);
                    }
                    /*
                     * insert new node into open
                     */

                    auto check = open.insert(nodeValue(g + cost_move(board, next_board), next_board));

                    link_open.emplace(next_board,
                                      nodeValue(g + cost_move(board,next_board), next_board));
                    int a1=focalSet.size();
                    
                    if (open_value(g + cost_move(board,next_board), h_new) <=epsilon * f_min)
                    {
                        
                        int a=focalSet.size();
                        focalSet.insert(nodeValue(g + cost_move(board,next_board), next_board));
                        int b=focalSet.size();
                        if(b!=a+1) std::cout<<a<<" "<<b<<'\n';
                    }
                    int b1=focalSet.size();

                }
            }
            if (foundDestination) {
                return static_cast<double> (minDistance);
            }

            auto f_head = open.begin()->f;
            
            
            if (!open.empty() && f_min <f_head)
            {
                /*
                 * update focal: insert new node from open to focal with f <= epsilon * fmin
                 */
                for(auto it=open.lower_bound(Node<G>(f_min*epsilon,(double)-1,(double)-1,(double)-1,board));it!=open.end();++it)
                {
                    //Node node=*it;
                    auto board = it->board;
                    
                    if (it->f > epsilon * f_head)
                        break;
                    if (it->f >= f_min)
                    {
                        focalSet.insert(nodeValue(it->g, board));
                    }
                    
                }
            }
            if(focalSet.size()==0){
                        std::cout<<" "<<f_min<<" "<<f_head<<" false "<<'\n';
            }
         
        }
        return static_cast<int>(-1);
    }
};

// #endif // FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
