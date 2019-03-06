#include "MAffineTransformation.h"


/**
 * @brief
 **/
void MAffineTransformation::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - new_empty: Expecting an output.");

    hypro::AffineTransformation<double>* tran = new hypro::AffineTransformation<double>();
    plhs[0] = convertPtr2Mat<hypro::AffineTransformation<double>>(tran);
}

/**
 * @brief
 **/
void MAffineTransformation::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - copy: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MAffineTransformation - copy: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineTransformation - copy: One or more input arguments were ignored."); 
    
    hypro::AffineTransformation<double>* origin = convertMat2Ptr<hypro::AffineTransformation<double>>(prhs[2]);
    hypro::AffineTransformation<double>* tran = new hypro::AffineTransformation<double>(*origin);
    plhs[0] = convertPtr2Mat<hypro::AffineTransformation<double>>(tran);
}

/**
 * @brief
 **/
void MAffineTransformation::new_constraints(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - new_constraints: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MAffineTransformation - new_constraints: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineTransformation - new_constraints: One or more input arguments were ignored."); 
    
    const hypro::ConstrainSet<double>* set = convertMat2Ptr<hypro::ConstrainSet<double>>(prhs[2]);
    hypro::AffineTransformation<double>* tran = new hypro::AffineTransformation<double>(*set);
    plhs[0] = convertPtr2Mat<hypro::AffineTransformation<double>>(tran);
}

/**
 * @brief
 **/
void MAffineTransformation::delete_reset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MAffineTransformation - delete_reset: Expecting an output.");
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineTransformation - delete_reset: One or more arguments were ignored.");
    destroyObject<hypro::AffineTransformation<double>>(prhs[2]);
}

/**
 * @brief
 **/
void MAffineTransformation::type(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - type: Expecting one output value!");

    std::string ans = "MAffineTransformation";
    plhs[0] = mxCreateString(ans.c_str());
}

/**
 * @brief
 **/
void MAffineTransformation::size(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - size: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MAffineTransformation - size: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineTransformation - size: One or more input arguments were ignored."); 
    
    hypro::AffineTransformation<double>* tran = convertMat2Ptr<hypro::AffineTransformation<double>>(prhs[2]);
    std::size_t s = tran->size();
    plhs[0] = mxCreateDoubleScalar(s);
}

/**
 * @brief
 **/
void MAffineTransformation::isIdentity(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - isIdentity: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MAffineTransformation - isIdentity: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineTransformation - isIdentity: One or more input arguments were ignored."); 
    
    hypro::AffineTransformation<double>* tran = convertMat2Ptr<hypro::AffineTransformation<double>>(prhs[2]);
    bool ans = tran->isIdentity();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MAffineTransformation::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineTransformation - ==: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MAffineTransformation - ==: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MAffineTransformation - ==: One or more input arguments were ignored.");

    hypro::AffineTransformation<double>* tran_1 = convertMat2Ptr<hypro::AffineTransformation<double>>(prhs[2]);
    hypro::AffineTransformation<double>* tran_2 = convertMat2Ptr<hypro::AffineTransformation<double>>(prhs[3]);
    mxLogical ans = false;
    if(*tran_1 == *tran_2){
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MAffineTransformation::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MAffineTransformation - First input should be a command string less than 64 characters long.");

    if (!strcmp("new_empty", cmd)){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_constraints", cmd)){  
        new_constraints(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("copy", cmd)){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)){  
        delete_reset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("type", cmd)){  
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("size", cmd)){  
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("isIdentity", cmd)){  
        isIdentity(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("==", cmd)){  
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MAffineTransformation - Command not recognized.");   
}