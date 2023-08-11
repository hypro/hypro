/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MLinearFlow.h"

/**
 * @brief
 **/
void MLinearFlow::new_mat(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLinearFlow - new_mat: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLinearFlow - new_mat: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLinearFlow - new_mat: One or more arguments were ignored.");

    const mwSize *mat_dims;
    int mat_rows, mat_cols;

    mat_dims = mxGetDimensions(prhs[2]);
    mat_cols = (int) mat_dims[1];
    mat_rows = (int) mat_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_rows, mat_cols);
    plhs[0] = convertPtr2Mat<hypro::linearFlow<double>>(new hypro::linearFlow<double>(matrix));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_mat input:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < matrix.rows(); i++ ) {
    // 	for ( int j = 0; j < matrix.cols(); j++ ) {
    // 		mexPrintf( " %f", matrix( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief
 **/
void MLinearFlow::setFlowMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLinearFlow - setFlowMatrix: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MLinearFlow - setFlowMatrix: One or more arguments were ignored!");

    const mwSize *dims;
    int rows, cols;

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    cols = (int) dims[1];
    rows = (int) dims[0];

    const hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[3], rows, cols);
    flow->setFlowMatrix(matrix);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setFlowMatrix input:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < matrix.rows(); i++ ) {
    // 	for ( int j = 0; j < matrix.cols(); j++ ) {
    // 		mexPrintf( " %f", matrix( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief
 **/
void MLinearFlow::addRow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLinearFlow - addRow: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MLinearFlow - addRow: One or more arguments were ignored!");

    const mwSize *dims;
    int rows;

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    rows = (int) dims[0];

    const hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], rows);
    flow->setFlowMatrix(vector);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "addRow input:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vector.rows(); j++ ) {
    // 	mexPrintf( " %f", vector( j ) );
    // }
    // mexPrintf( "\noutput:\n" );
    // hypro::matrix_t<double> matrix = flow->getFlowMatrix();
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < matrix.rows(); i++ ) {
    // 	for ( int j = 0; j < matrix.cols(); j++ ) {
    // 		mexPrintf( " %f", matrix( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief
 **/
void MLinearFlow::getFlowMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLinearFlow - getFlowMatrix: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLinearFlow - getFlowMatrix: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLinearFlow - getFlowMatrix: One or more arguments were ignored.");

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    hypro::matrix_t<double> matrix = flow->getFlowMatrix();
    int rows = matrix.rows();
    int cols = matrix.cols();
    plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);
    ObjectHandle::convert2Matlab(matrix, plhs[0], rows, cols);
    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getFlowMatrix output:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < matrix.rows(); i++ ) {
    // 	for ( int j = 0; j < matrix.cols(); j++ ) {
    // 		mexPrintf( " %f", matrix( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief
 **/
void MLinearFlow::isIdentity(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLinearFlow - isIdentity: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLinearFlow - isIdentity: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLinearFlow - isIdentity: One or more arguments were ignored.");

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    const bool ans = flow->isIdentity();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "isIdentity output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "identity\n" );
    // } else {
    // 	mexPrintf( "not identity\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief
 **/
void MLinearFlow::hasNoFlow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLinearFlow - hasNoFlow: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLinearFlow - hasNoFlow: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLinearFlow - hasNoFlow: One or more arguments were ignored.");

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[2]);
    const bool ans = flow->hasNoFlow();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "hasNoFlow output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "has no flow\n" );
    // } else {
    // 	mexPrintf( "does not have no flow\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief
 **/
void MLinearFlow::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MLinearFlow  - outstream: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLinearFlow  - outstream: One or more arguments were ignored.");

    hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    hypro::matrix_t<double> mat = flow->getFlowMatrix();

    int rows = mat.rows();
    int cols = mat.cols();

    mexPrintf("Matrix: [");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mexPrintf("%f ", mat(i, j));
        }
        mexPrintf("\n");
    }
    mexPrintf("]\n");
}

/**
 * @brief
 **/
void MLinearFlow::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        new_mat(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1) {
        delete_flow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        hasNoFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        getFlowMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        setFlowMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        addRow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        isIdentity(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        isTimed(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        isDiscrete(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        outstream(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21) {
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MLinearFlow - Command not recognized.");
}
