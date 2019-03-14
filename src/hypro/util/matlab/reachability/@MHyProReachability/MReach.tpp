#include "MReach.h"

void MReach::new_reach(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReach - new_reach: Expecting an output.");

    // hypro::reachability::Reach<double, hypro::reachability::ReachSettings, hypro::State_t<double>>
}

void MReach::computeForwardReachability(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

void MReach::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
     // Get the command string
        char cmd[64];
        if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
            mexErrMsgTxt("MReach - First input should be a command string less than 64 characters long.");

        if (!strcmp("new_reach", cmd)){  
            new_reach(nlhs, plhs, nrhs, prhs);
            return;
        }
        if (!strcmp("computeForwardReachability", cmd)){  
            computeForwardReachability(nlhs, plhs, nrhs, prhs);
            return;
        }
        mexErrMsgTxt("MReach - Command not recognized.");
}