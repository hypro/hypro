/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *   Wrapper class for reach.
 */

#pragma once

#include "../../../../algorithms/reachability/Reach.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

class MReach {
public:
    using Reacher = hypro::reachability::Reach<double, hypro::reachability::ReachSettings, hypro::State_t<double>>;
    using flowpipe = std::vector<hypro::State_t<double>>;

    static void del_reach(int lhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void new_reach(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void computeForwardReachability(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void setSettings(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void setRepresentationType(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void settings(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);

    static void reachedBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
};
