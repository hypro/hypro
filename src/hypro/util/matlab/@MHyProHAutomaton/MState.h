#pragma once

#include <iostream>
#include "mex.h"
#include "matrix.h"
#include "../ClassHandle.h"
#include "../ObjectHandle.h"
//#include <vector>
#include "../../datastructures/HybridAutomaton/Condition.h"
#include "../../datastructures/HybridAutomaton/Visitors.h"
#include "../../representations/types.h"
#include "../../representations/GeometricObject.h"
#include <carl/util/tuple_util.h>
#include <carl/interval/Interval.h>

class MState{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        
        static void checkConsistency(int, mxArray**, int, const mxArray**);

};

#include "MState.tpp"