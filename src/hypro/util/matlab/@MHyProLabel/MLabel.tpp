#include "MLabel.h"

void MLabel::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

void MLabel::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

void MLabel::del_label(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @brief
 **/
void MLabel::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MLabel - First input should be a command string less than 64 characters long.");


    if (!strcmp("new_empty", cmd) && nrhs == 2){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("copy", cmd) && nrhs == 2){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("del_label", cmd) && nrhs == 2){  
        del_label(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MLabel - Command not recognized.");
}