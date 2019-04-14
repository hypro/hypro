#include "MReach.h"

/*
* @brief
*/

void MReach::del_reach(int lhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MReach- del_reach: Expecting an output.");
    if(nrhs > 3)
        mexWarnMsgTxt("MReach- del_reach: One or more arguments were ignored.");
    destroyObject<Reacher>(prhs[2]);
}

/*
* @brief
*/

void MReach::new_reach(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReach - new_reach: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MReach - new_reach: At least one input argument is missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MReach- new_reach: One or more arguments were ignored.");

    hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);

    
    mwIndex idx = 1;
    int ifield, nfields;
    nfields = mxGetNumberOfFields(prhs[3]);
    hypro::ReachabilitySettings settings;
    for (ifield=0; ifield< nfields; ifield++){
        mxArray* tmp = mxGetFieldByNumber(prhs[3], 0, ifield);
        const char* fname = mxGetFieldNameByNumber(prhs[3], ifield);

        if(!strcmp(fname, "timeBound")){
            double timeBound = mxGetScalar(tmp);
            settings.timeBound = timeBound;
            mexPrintf("%s: %f\n", fname, timeBound);
        }else if(!strcmp(fname, "jumpDepth")){
            double jumpDepth = mxGetScalar(tmp);
            settings.jumpDepth = jumpDepth;
            mexPrintf("%s: %f\n", fname, jumpDepth);
        }else if(!strcmp(fname, "timeStep")){
            double timeStep = mxGetScalar(tmp);
            settings.timeStep = timeStep;
            mexPrintf("%s: %f\n", fname, timeStep);
        }else if(!strcmp(fname, "fileName")){
            char file[64];
            mxGetString(tmp, file, sizeof(file));
            std::string fileName = std::string(file);
            settings.fileName = fileName;
            mexPrintf("%s: %s\n", fname, fileName.c_str());
        }else if(!strcmp(fname, "pplDenomimator")){
            double pplDenomimator = mxGetScalar(tmp);
            settings.pplDenomimator = pplDenomimator;
            mexPrintf("%s: %f\n", fname, pplDenomimator);
        }else if(!strcmp(fname, "plotDimensions")){
            const mwSize* dims;
            int dimx, dimy;
            dims = mxGetDimensions(tmp);
            dimx = dims[0];
            dimy = dims[1];
            std::vector<std::vector<std::size_t>> plotDimensions = ObjectHandle::mVectorOfVectors2Hypro(tmp, dimx, dimy);
            settings.plotDimensions = plotDimensions;
        }else if(!strcmp(fname, "uniformBloating")){
            double uniformBloating = mxGetScalar(tmp);
            bool uB = false;
            if(uniformBloating == 1)
                uB = true;
            settings.uniformBloating = uB;
            mexPrintf("%s: %f\n", fname, uniformBloating);
        }else{
            mexErrMsgTxt("MHyProReach - new_reach: Unknown setting field.");
        }     
    }

    Reacher* reacher = new Reacher(*autom, settings);
    plhs[0] = convertPtr2Mat<Reacher>(reacher);
}

/*
* @brief
*/
void MReach::computeForwardReachability(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReach - computeForwardReachability: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MReach - computeForwardReachability: At least one input argument is missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MReach- computeForwardReachability: One or more arguments were ignored.");

    Reacher* reacher = convertMat2Ptr<Reacher>(prhs[2]);
    std::vector<std::pair<unsigned, flowpipe>> flowpipes = reacher->computeForwardReachability();

    int num_flowpipes = flowpipes.size();
    mexPrintf("Number of flowpipes: %d\n", num_flowpipes);
    mwSize dims[2] = {1, num_flowpipes};
    const char *field_names[] = {"num", "flowpipe"};
    plhs[0] = mxCreateStructArray(2, dims, 2, field_names);
    ObjectHandle::flowpipes2Matlab(flowpipes, plhs[0], num_flowpipes);
    

}

void MReach::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MReach - First input should be a command string less than 64 characters long.");
    
    if (!strcmp("new_reach", cmd)){  
        new_reach(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)){  
        del_reach(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("computeForwardReachability", cmd)){  
        computeForwardReachability(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MReach - Command not recognized.");
}