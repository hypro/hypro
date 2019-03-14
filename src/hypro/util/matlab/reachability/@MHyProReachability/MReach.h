#pragma once

#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"

class MReach{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_reach(int, mxArray**, int, const mxArray**);
        static void computeForwardReachability(int, mxArray**, int, const mxArray**);
};

#include "MReach.tpp"