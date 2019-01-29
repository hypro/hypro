#pragma once

#include "../../../datastructures/HybridAutomaton/Transition.h"
#include "../../../types.h"
#include <map>
#include "mex.h"
#include "matrix.h"
#include "../ClassHandle.h"
#include "../ObjectHandle.h"

class MTransition{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_empty(int, mxArray**, int, const mxArray**);
        static void copy(int, mxArray**, int, const mxArray**);
        static void del_label(int, mxArray**, int, const mxArray**);
};

#include "MTransition.h"