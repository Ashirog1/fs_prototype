///
// Created by only_u on 12/21/23.
//

#include "focal_search.h"

// BasicFocalSearch::BasicFocalSearch() {
//     visited.clear();
//     open.clear();
//     link_open.clear();
//     while (!focal.empty()) focal.pop();
// }

// template<class G>
// bool Node<G>::operator<(const Node<G> &oth) const {
//     if (f != oth.f)
//         return f < oth.f;
//     if (g != oth.g)
//         return g < oth.g;
//     if (hFocal != oth.hFocal)
//         return hFocal < oth.hFocal;
//     return board < oth.board;
// }



// template<class G>
// bool CompareG<G>::operator()(const Node<G> &a, const Node<G> &b) {
//     if(a.f!=b.f)
//     return a.f > b.f;
//     if(a.g!=b.g)
//     return a.g>b.g;
//     return a.h>b.h;
//     // if(a.h!=b.h)
//     // return a.h>b.h;
//     // if(a.hFocal!=b.hFocal)
//     // return a.hFocal>b.hFocal;
// }

// template<class G>
// bool CompareH<G>::operator()(const Node<G> &a, const Node<G> &b) {
//     if(a.hFocal!=b.hFocal)
//     return a.hFocal > b.hFocal;
//     if(a.g!=b.g)
//     return a.g>b.g;
//     return a.h>b.h;
//     // if(a.h!=b.h)
//     // return a.h>b.h;
//     // if(a.hFocal!=b.hFocal)
//     // return a.hFocal>b.hFocal;
// }

