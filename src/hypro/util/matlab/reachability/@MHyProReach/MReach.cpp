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
    if(nrhs < 5)
        mexErrMsgTxt("MReach - new_reach: At least one input argument is missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MReach- new_reach: One or more arguments were ignored.");

    hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    double timeBound = (double) mxGetScalar(mxGetCell(prhs[3],0));
    int jumpDepth = (int) mxGetScalar(mxGetCell(prhs[3],1));
    double timeStep = (double) mxGetScalar(mxGetCell(prhs[3],2));
    char file[64];
    mxGetString(mxGetCell(prhs[3],3), file, sizeof(file));
    std::string fileName = std::string(file);
    unsigned long pplDenominator = (unsigned long) mxGetScalar(mxGetCell(prhs[3],4));
    const mwSize* dims;
    int dimx, dimy;
    dims = mxGetDimensions(mxGetCell(prhs[3],5));
    dimx = dims[0];
    dimy = dims[1];
    std::vector<std::vector<std::size_t>> plotDimensions = ObjectHandle::mVectorOfVectors2Hypro(mxGetCell(prhs[3],5), dimx, dimy);
    int temp = (int) mxGetScalar(mxGetCell(prhs[3],6));
    bool uniformBolating = false;
    if (temp == 1)
        uniformBolating = true;

    hypro::ReachabilitySettings settings;
    settings.timeBound = timeBound;
    settings.jumpDepth = jumpDepth;
    settings.timeStep = timeStep;
    settings.fileName = fileName;
    settings.pplDenomimator = pplDenominator;
    settings.plotDimensions = plotDimensions;
    settings.uniformBloating = uniformBolating;

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

}

void MReach::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
}