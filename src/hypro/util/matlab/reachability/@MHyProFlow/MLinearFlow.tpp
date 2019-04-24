#include "MLinearFlow.h"

/**
 * @brief
**/
void MLinearFlow::new_mat(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLinearFlow - new_mat: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MLinearFlow - new_mat: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLinearFlow - new_mat: One or more arguments were ignored.");

    const mwSize *mat_dims;
    int mat_dimx, mat_dimy;

    mat_dims = mxGetDimensions(prhs[2]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_dimx, mat_dimy);
    plhs[0] = convertPtr2Mat<hypro::linearFlow<double>>(new hypro::linearFlow<double>(matrix));
}

/**
 * @brief
**/
void MLinearFlow::setFlowMatrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MLinearFlow - setFlowMatrix: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MLinearFlow - setFlowMatrix: One or more arguments were ignored!");

    const mwSize *dims;
    int dimx, dimy;

    hypro::linearFlow<double>* flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    const hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);
    flow->setFlowMatrix(matrix);
}

/**
 * @brief
**/
void MLinearFlow::addRow(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MLinearFlow - addRow: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MLinearFlow - addRow: One or more arguments were ignored!");

    const mwSize *dims;
    int dimx, dimy;

    hypro::linearFlow<double>* flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];

    const hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], dimy);
    flow->setFlowMatrix(vector);
}

/**
 * @brief
**/
void MLinearFlow::getFlowMatrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLinearFlow - getFlowMatrix: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MLinearFlow - getFlowMatrix: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLinearFlow - getFlowMatrix: One or more arguments were ignored.");

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);  
    hypro::matrix_t<double> matrix = flow->getFlowMatrix();
    int rows = matrix.rows();
    int cols = matrix.cols();
    plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);
    ObjectHandle::convert2Matlab(matrix, plhs[0], rows, cols);
}

/**
 * @brief
**/
void MLinearFlow::isIdentity(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLinearFlow - isIdentity: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MLinearFlow - isIdentity: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLinearFlow - isIdentity: One or more arguments were ignored.");

    hypro::linearFlow<double>* flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    const bool ans = flow->isIdentity();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
**/
void MLinearFlow::hasNoFlow(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLinearFlow - hasNoFlow: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MLinearFlow - hasNoFlow: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLinearFlow - hasNoFlow: One or more arguments were ignored.");

    hypro::linearFlow<double>* flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    const bool ans = flow->hasNoFlow();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
**/
void MLinearFlow::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @brief
**/
void MLinearFlow::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
// Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MLinearFlow - First input should be a command string less than 64 characters long.");

    if (!strcmp("new_empty", cmd)){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_mat", cmd)){  
        new_mat(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("copy", cmd)){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)){  
        delete_flow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("size", cmd)){  
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("type", cmd)){  
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("hasNoFlow", cmd)){  
        hasNoFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getFlowMatrix", cmd)){  
        getFlowMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setFlowMatrix", cmd)){  
        setFlowMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("addRow", cmd)){  
        addRow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("isIdentity", cmd)){  
        isIdentity(nlhs, plhs, nrhs, prhs);
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
    if(!strcmp("dimension", cmd)){
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MLinearFlow - Command not recognized.");
}

