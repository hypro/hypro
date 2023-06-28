
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
*   This file implements the gateway function 'mexFunction' which
*   allow the communication between Matlab and HyPro. This file
*   has to be compiled by Matlab.
*/


#include "representations/@MHyProBox/MBox.h"
#include "representations/@MHyProConstraintSet/MConstraintSet.h"
#include "representations/@MHyProEllipsoid/MEllipsoid.h"
#include "representations/@MHyProSupportFunction/MSupportFunction.h"
#include "reachability/@MHyProHAutomaton/MHybridAutomaton.h"
#include "reachability/@MHyProCondition/MCondition.h"
#include "reachability/@MHyProFlow/MLinearFlow.h"
#include "reachability/@MHyProFlow/MAffineFlow.h"
#include "reachability/@MHyProLabel/MLabel.h"
#include "reachability/@MHyProLocation/MLocation.h"
#include "reachability/@MHyProState/MState.h"
#include "reachability/@MHyProTransition/MTransition.h"
#include "reachability/@MHyProReset/MReset.h"
#include "reachability/@MHyProReach/MReach.h"
#include "representations/@MHyProZonotope/MZonotope.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"

/*
@brief This function is the gateway function to Matlab.
@param nlhs Number of output arguments
@param plhs Pointer to mex array that will contain various
            output arguments that will be passed to Matlab
@param nrhs Number of input arguments passed by Matlab
@param prhs Pointer to mex array containing different
            input arguments from wrapped functions in Matlab
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

    const int type = mxGetScalar(prhs[0]);

    if (type == 0) {
        MBox::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 1) {
        MEllipsoid::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 2) {
        MConstraintSet::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 3) {
        MSupportFunction::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 4) {
        MHybridAutomaton::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 5) {
        MCondition::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 6) {
        MLocation::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 7) {
        MTransition::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 8) {
        MLabel::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 9) {
        MLinearFlow::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 10) {
        MAffineFlow::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 11) {
        MReset::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 12) {
        MReach::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 13) {
        MState::process(nlhs, plhs, nrhs, prhs);
    } else if (type == 14) {
        MZonotope::process(nlhs, plhs, nrhs, prhs);
    } else {
        mexErrMsgTxt("MHyPro - Unknown type.");
    }

}
