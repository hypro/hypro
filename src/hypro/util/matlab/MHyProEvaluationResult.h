#pragma once

#include "../../../representations/GeometricObject.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"
#include "../ClassHandle.h"
#include "../ObjectHandle.h"

class HyProEvaluationResult{
    public:
        static void process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
    private:
        static void emptyEvaluationResult(int nlhs, mxArray *plhs[], const mxArray *prhs[]);
        static void solutionEvaluationResult(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]); 
        static void delete_evaluationResult(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]);
};


/**
 * @brief Creates an empty evaluation result struct
 **/
void HyProEvaluationResult::emptyEvaluationResult(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("EvaluationResult - new: One output expected.");

    plhs[0] = convertPtr2Mat<hypro::EvaluationResult<double>>(new hypro::EvaluationResult<double>());
}

/**
 * @brief Creates an empy evaluation result struct
 **/
void HyProEvaluationResult::solutionEvaluationResult(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("EvaluationResult - new: One output expected.");
    if(nrhs != 3)
        mexErrMsgTxt("EvaluationResult - new: Two input arguments expected.");

    char ans[7];
    mxGetString(prhs[2], ans, sizeof(ans));
    hypro::SOLUTION sol = ObjectHandle::mSolution2Hypro(ans);
    plhs[0] = convertPtr2Mat<hypro::EvaluationResult<double>>(new hypro::EvaluationResult<double>(sol));
}

/**
 * @brief Deletes an EvaluationResult object in Matlab
 **/
void HyProEvaluationResult::delete_evaluationResult(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs != 3)
        mexErrMsgTxt("EvaluationResult - delete: Three input arguments expected.");

    // Destroy the object
    destroyObject<hypro::EvaluationResult<double>>(prhs[2]);
    // Warn if other commands were ignored
    if (nlhs != 0 || nrhs != 3)
        mexWarnMsgTxt("EvaluationResult - delete: Unexpected arguments ignored.");
}



/**
* @brief The entry point to the HyPro Evaluation Result class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void HyProEvaluationResult::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 2 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if(!strcmp("newEv", cmd) && nrhs == 2){  
        emptyEvaluationResult(nlhs, plhs, prhs);
        return;
    }
    if(!strcmp("new_solEv",cmd)){
        solutionEvaluationResult(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("delete",cmd)){
        delete_evaluationResult(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("Command not recognized");
}
