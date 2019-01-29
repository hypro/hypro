#include "MAffineFlow.h"

/**
* @brief
**/
void MAffineFlow::new_mat_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineFlow - new_mat_vec: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MAffineFlow - new_mat_vec: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MAffineFlow - new_mat_vec: One or more arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, len;

    mat_dims = mxGetDimensions(prhs[2]);
    vec_dims = mxGetDimensions(prhs[3]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    len = (int) vec_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_dimx, mat_dimy);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], len);
    plhs[0] = convertPtr2Mat<hypro::affineFlow<double>>(new hypro::affineFlow<double>(matrix, vector));
}

/**
* @brief
**/
void MAffineFlow::setTranslation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MAffineFlow - setTranslation: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MAffineFlow - setTranslation: One or more arguments were ignored.");
    
    const mwSize *dims;
    int len;

    dims = mxGetDimensions(prhs[3]);
    len = (int) dims[0];

    hypro::affineFlow<double>* flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], len);
    flow->setTranslation(vector);
}


/**
* @brief
**/
void MAffineFlow::getTranslation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineFlow - getTranslation: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MAffineFlow - getTranslation: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineFlow - getTranslation: One or more arguments were ignored.");

    hypro::affineFlow<double>* flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    hypro::vector_t<double> vector = flow->getTranslation();

    plhs[0] = mxCreateDoubleMatrix(1, vector.size(), mxREAL);
    ObjectHandle::convert2Matlab(vector, plhs[0], 1, vector.size());
}


/**
* @brief
**/
void MAffineFlow::hasTranslation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MAffineFlow - hasTranslation: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MAffineFlow - hasTranslation: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MAffineFlow - hasTranslation: One or more arguments were ignored.");

    hypro::affineFlow<double>* flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    const bool ans = flow->hasTranslation();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
* @brief
**/
void MAffineFlow::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
* @brief
**/
void MAffineFlow::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
// Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MLinearFlow - First input should be a command string less than 64 characters long.");

    if (!strcmp("new_empty", cmd)){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("new_mat_vec", cmd)){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("copy", cmd)){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete_flow", cmd)){  
        delete_flow(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("type", cmd)){  
        type(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("hasTranslation", cmd)){  
        hasTranslation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setTranslation", cmd)){  
        setTranslation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getTranslation", cmd)){  
        getTranslation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("isTimed", cmd)){  
        isTimed(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("isDiscrete", cmd)){  
        isDiscrete(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("==", cmd)){  
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("!=", cmd)){  
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("outstream", cmd)){  
        outstream(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MFlow - Command not recognized.");
}