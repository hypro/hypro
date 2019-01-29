#include "MTransition.h"
// /**
//  * @brief
//  **/
// template<typename T>
// void MAutomatonComponents<T>::getDotRepresentation(int nlhs, mxArray* plrhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MAutomatonComponents - getDotRepresentation: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MAutomatonComponents - getDotRepresentation: One or more arguments are missing!");

//     T* obj = convertMat2Ptr<T>(plhs[2]);
//     std::vector<std::string> vec(nrhs - 3);

//     for(int i = 2; i < (nrhs - 3); i++){
//         std::string str = mxArrayToString(prhs[i]);
//         vec.emplace_back(str);
//     }
    
// }


void MTransition::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

void MTransition::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

void MTransition::del_label(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @brief
 **/
void MTransition::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MTransition - First input should be a command string less than 64 characters long.");


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

    mexErrMsgTxt("MTransition - Command not recognized.");
}