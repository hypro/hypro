#include "MEllipsoidReach.h"

void MEllipsoidReach::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
     // Get the command string
        char cmd[64];
        if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
            mexErrMsgTxt("MEllipsoidReach - First input should be a command string less than 64 characters long.");

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
        mexErrMsgTxt("MEllipsoidReach - Command not recognized.");
}