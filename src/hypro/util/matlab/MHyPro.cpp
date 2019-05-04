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
#include <iostream>
#include "mex.h"
#include "matrix.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    // Get type of the Matlab object
    // 0 = Box, 1 = Ellipsoid, 2 = ConstraintSet,
    // 3 = SupportFunction, 4 = HybridAutomaton, 5 = Condition,
    // 6 = Location, 7 = Transition, 8 = Label,
    // 9 = linearFlow, 10 = affineFlow, 11 = Reset,
    // 12 = Reacher, 13 = State
    int type = mxGetScalar(prhs[0]);

    if(type == 0){
        MBox::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 1){
        MEllipsoid::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 2){
        MConstraintSet::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 3){
        MSupportFunction::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 4){
        MHybridAutomaton::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 5){
        MCondition::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 6){
        MLocation::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 7){
        MTransition::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 8){
        MLabel::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 9){
        MLinearFlow::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 10){
        MAffineFlow::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 11){
        MReset::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 12){
        MReach::process(nlhs, plhs, nrhs, prhs);
    }else if(type == 13){
        MState::process(nlhs, plhs, nrhs, prhs);
    }else{
        mexErrMsgTxt("MHyPro - Unknown type.");
    }
    
}