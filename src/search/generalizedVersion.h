//
// Created by only_u on 2/26/24.
//

#include <vector>
#include "focal_search.h"
#include "utils.h"

/*
 60/40 focal search
*/

class generalizedVersion : public BasicFocalSearch
{
public:
    std::set<Node> focalSet;

    template <class T, class open_funct, class focal_funct>
    inline int FocalSearch(std::vector<std::vector<int>> &v, open_funct open_value, focal_funct focal_value, T heuristic,
                           double epsilon = (double)1.5, double pickRate = (double)0.6)
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
        GameBoard start(v);

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
            // Pop from focal
            double f,g,h,hFocal;
            GameBoard board;
         //   auto [f, g, h, hFocal, board];
            double f_min=open.begin()->f;
           // std::cout<<"ok1"<<'\n';
          //  std::cout<<pick<<'\n';
             //     std::cout<<"abc"<<' '<<pick<<" "<<'\n';
           //  std::cout<<"oke1"<<'\n';
            //dem++;
          //  std::cout<<dem<<'\n';
                     // std::cout<<"ok1"<<'\n';

            if (pick <= pickRate*100 && !focalSet.empty())
            {
                Node a=*focalSet.begin();
                a.board.printState();
                dem++;
                std::cout<<'\n'<<dem<<" "<<a.board.GetHeuristic(heuristic)<<'\n';
               // a.printState();
               // std::cout<<'\n';
                //focalSet.begin()->board.printState();
                assignValue(f,g,h,hFocal,board,a);
              //  if (visited[a.board] != g)
                //    continue;
           //     board.printState();
                //std::cout<<'\n'<<g<<"\n";
                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);
             //   std::cout<<"lol"<<"\n";

                focalSet.erase(focalSet.begin());
                open.erase(Node(f, g, h, hFocal, board));
             //   std::cout<<"lol"<<"\n";

                if (hFocal == 0)
                    return static_cast<int>(g);
            }
            // Pop from open
            else
            {
                Node a=*open.begin();
                a.board.printState();
                                dem++;
                std::cout<<'\n'<<dem<<" "<<a.board.GetHeuristic(heuristic)<<'\n';

                //a.printState();
              //  std::cout<<'\n';
                assignValue(f,g,h,hFocal,board,a);
              //  { f, g, h, hFocal, board } = *open.begin();
               // if (visited[a.board] != g)
                 //   continue;
           //     board.printState();
              //  std::cout<<'\n'<<g<<"\n";

                if (board.GetHeuristic(heuristic) == 0)
                    return static_cast<int>(g);
             //   std::cout<<"ok1"<<'\n';
                open.erase(open.begin());
                focalSet.erase(Node(f, g, h, hFocal, board));
             //   std::cout<<"lol"<<"\n";

                if (hFocal == 0)
                    return static_cast<int>(g);
            }
             // std::cout<<f<<" "<<g<<" "<<h<<" "<<" "<<hFocal<<'\n';
            
          //  board.printState();
           // std::cout<<"ok1"<<'\n';

          //  dem++;
          //  std::cout<<dem<<'\n';
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
                    if (link_open.find(next_board) != link_open.end())
                    {
                        auto old_open = link_open.find(next_board);
                        open.erase(old_open->second);
                    }
                    /*
                     * insert new node into open
                     */

                    auto check=open.insert(nodeValue(g + 1, next_board));
                    // if(check.second)
                    // {
                    //     std::cout<<"ok insert"<<'\n';
                    // }
                    // else
                    // {
                    //     std::cout<<"current board ";
                    //     next_board.printState();
                    //     std::cout<<"\n";
                    //     Node a=nodeValue(g+1,next_board);
                    //     auto ite=*open.find(a);
                    //     a.board.printState();
                    //   //  std::cout<<'\n';
                    //   //  std::cout<<a.f<<" "<<a.g<<" "<<a.h<<" "<<a.hFocal<<" "<<'\n';

                        
                    //     //if(ite!=open.end()) std::cout<<"found"<<'\n';
                    //     //else std::cout<<"not found"<<'\n';
                    //     std::cout<<ite.f<<" "<<ite.g<<" "<<ite.h<<" "<<ite.hFocal<<" "<<'\n';
                    //     ite.board.printState();
                    //     // for(auto v:open)
                    //     // {
                    //     //     v.board.printState();
                    //     //     std::cout<<"\n";
                    //     // }
                    //     // std::cout<<"false insert"<<'\n';
                    // }
            //          for(auto v:open)
            // {
            //     v.board.printState();
            //     std::cout<<'\n';
            // }
                 //   std::cout<<" "<<'\n'<<'\n';
                
                    //std::cout<<"open size "<<open.size()<<'\n';

                    link_open.emplace(next_board,
                                      nodeValue(g + 1, next_board));
                    if (open_value(g + 1, h_new) < epsilon * f_min)
                    {
                        focalSet.insert(nodeValue(g + 1, next_board));
                    }
                }
            }
            // for(auto v:open)
            // {
            //     v.board.printState();
            //     std::cout<<'\n';
            // }
            // std::cout<<"\n";
            auto f_head = open.begin()->f;
            //std::cout<<"f_head"<<'\n';
           // double f_head = fmin->g + fmin->h;
     //       std::cout<<open.size()<<" "<<focalSet.size()<<'\n';
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

                //  for (const auto &it: open) {
                //     auto board = it.board;
                //     if (it.g + it.h > epsilon * f_head)
                //         break;
                //     if (it.g + it.h >= epsilon * f_min) {
                //         focal.push(nodeValue(it.g, board));
                //     }
                // }

            }
         // std::cout<<"ok"<<'\n';
        }
                    return static_cast<int>(-1);

    }
};

//#endif // FS_PROTOTYPE_BOUNDEDFOCALSEARCH_H
