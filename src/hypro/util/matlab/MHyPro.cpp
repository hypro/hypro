#include "@MHyProObject/MHyProBox.h"
#include "@MHyProObject/MHyProConstraintSet.h"
#include "@MHyProObject/MHyProTaylorModel.h"
#include "@MHyProObject/MHyProEllipsoid.h"
#include "@MHyProObject/MHyProSupportFunction.h"
#include "@MHyProHAutomaton/MHybridAutomaton.h"
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
    }else if(!strcmp(type, "TaylorModel")){
        // MHyProTaylorModel::process(nlhs, plhs, nrhs, prhs);
    }else if(!strcmp(type, "HybridAutomaton")){
        MHybridAutomaton::process(nlhs, plhs, nrhs, prhs);
    }else{
        mexErrMsgTxt("MHyPro - Unknown type.");
    }
    
}