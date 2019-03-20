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
// #include "reachability/@MHyProResetType/MAffineTransformation.h"
#include "reachability/@MHyProState/MState.h"
#include "reachability/@MHyProTransition/MTransition.h"
#include "reachability/@MHyProReset/MReset.h"
#include "reachability/@MHyProReachability/MReach.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    // Get type of the Matlab object
    char type[64];
    mxGetString(prhs[0], type, sizeof(type));

    if(!strcmp(type, "Box")){
        MBox::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Ellipsoid")){
        MEllipsoid::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "ConstraintSet")){
        MConstraintSet::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "SupportFunction")){
        MSupportFunction::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "HybridAutomaton")){
        MHybridAutomaton::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Condition")){
        MCondition::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Location")){
        MLocation::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Transition")){
        MTransition::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Label")){
        MLabel::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "linearFlow")){
        MLinearFlow::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "affineFlow")){
        MAffineFlow::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Reset")){
        MReset::process(nlhs, plhs, nrhs, prhs);
    // }else if(!strcmp(type, "affineTransformation")){
    //     MAffineTransformation::process(nlhs, plhs, nrhs, prhs);
    // }else if(!strcmp(type, "State")){
    //     MState::process(nlhs, plhs, nrhs, prhs);
    }else{
        mexErrMsgTxt("MHyPro - Unknown type.");
    }
    
}