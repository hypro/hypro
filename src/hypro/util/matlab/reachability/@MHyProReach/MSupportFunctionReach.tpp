#include "MSupportFunctionReach.h"

void MSupportFunctionReach::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
     // Get the command string
        char cmd[64];
        if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
            mexErrMsgTxt("MSupportFunctionReach - First input should be a command string less than 64 characters long.");

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
        mexErrMsgTxt("MSupportFunctionReach - Command not recognized.");
}