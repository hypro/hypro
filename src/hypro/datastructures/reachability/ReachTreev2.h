#pragma once

#include <vector>
#include "../HybridAutomaton/Path.h"
#include "../HybridAutomaton/Location.h"
#include "util/typetraits.h"
#include "TreeNodev2.h"


template<class Representation>
class ReachTreeNodev2 : TreeNodev2<ReachTreeNodev2<Representation>> {

    using Number = rep_number<Representation>;

    Location<Number>* mLocation; 
    std::vector<Representation>* mFlowpipe{};
    Path<Number, int> mPath;
    
    



};