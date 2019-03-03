#include "@MHyProBox/MHyProBox.h"
#include "@MHyProConstraintSet/MHyProConstraintSet.h"
#include "@MHyProEllipsoid/MHyProEllipsoid.h"
#include "@MHyProSupportFunction/MHyProSupportFunction.h"
#include "@MHyProHAutomaton/MHybridAutomaton.h"
#include "@MHyProCondition/MCondition.h"
#include "@MHyProFlow/MLinearFlow.h"
#include "@MHyProFlow/MAffineFlow.h"
#include "@MHyProLabel/MLabel.h"
#include "@MHyProLocation/MLocation.h"
// #include "@MHyProState/MState.h"
#include "@MHyProTransition/MTransition.h"
#include "@MHyProReset/MReset.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){

    // Get type of the Matlab object
    char type[64];
    mxGetString(prhs[0], type, sizeof(type));

    if(!strcmp(type, "Box")){
        MHyProBox::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "Ellipsoid")){
        MHyProEllipsoid::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "ConstraintSet")){
        MHyProConstraintSet::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "SupportFunction")){
        MHyProSupportFunction::process(nlhs, plhs, nrhs, prhs);
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
    // }else if(!strcmp(type, "State")){
    //     MState::process(nlhs, plhs, nrhs, prhs);
    }else{
        mexErrMsgTxt("MHyPro - Unknown type.");
    }
    
}