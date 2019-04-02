#pragma once

#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../../../../algorithms/reachability/Reach.h"



template<class T>class MReach{
    public:
        using Reacher = hypro::reachability::Reach<double, hypro::reachability::ReachSettings, T>;
        using flowpipe = std::vector<hypro::State<double, T>>;
        
        static void del_reach(int lhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]);
        static void new_reach(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]);
        static void computeForwardReachability(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]);
};
#include "MReach.tpp"
