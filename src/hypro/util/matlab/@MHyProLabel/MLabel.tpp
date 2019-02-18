#include "MLabel.h"

void MLabel::new_name(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLabel - new_name: Expecting an output.");
    if(nrhs != 3)
        mexErrMsgTxt("MLabel - new_name: Expecting two input arguments.");

    char name[64];
    mxGetString(prhs[2], name, sizeof(name));

    hypro::Label* temp = new hypro::Label(name);
    plhs[0] = convertPtr2Mat<hypro::Label>(temp);
}

void MLabel::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLabel - copy: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MLabel - copy: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLabel - copy: One or more arguments were ignored.");
    
    hypro::Label* origin = convertMat2Ptr<hypro::Label>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Label>(new hypro::Label(*origin));
}

void MLabel::del_label(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MLabel - del_label: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLabel - del_label: One or more arguments were ignored.");

    destroyObject<hypro::Label>(prhs[2]);
}

/**
 * @brief
 **/
void MLabel::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MLabel - First input should be a command string less than 64 characters long.");

    if(!strcmp("new_name", cmd)){
        new_name(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("copy", cmd)){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete", cmd)){  
        del_label(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MLabel - Command not recognized.");
}