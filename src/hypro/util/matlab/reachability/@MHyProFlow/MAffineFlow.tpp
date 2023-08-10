/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MAffineFlow.h"

void MAffineFlow::new_mat_vec(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MAffineFlow - new_mat_vec: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MAffineFlow - new_mat_vec: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MAffineFlow - new_mat_vec: One or more arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_rows, mat_cols, len;

    mat_dims = mxGetDimensions(prhs[2]);
    vec_dims = mxGetDimensions(prhs[3]);
    mat_cols = (int) mat_dims[1];
    mat_rows = (int) mat_dims[0];
    len = (int) vec_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_rows, mat_cols);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], len);
    plhs[0] = convertPtr2Mat<hypro::affineFlow<double>>(new hypro::affineFlow<double>(matrix, vector));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_mat_vec input:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < matrix.rows(); i++ ) {
    // 	for ( int j = 0; j < matrix.cols(); j++ ) {
    // 		mexPrintf( " %f", matrix( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vector.rows(); j++ ) {
    // 	mexPrintf( " %f", vector( j ) );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MAffineFlow::setTranslation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MAffineFlow - setTranslation: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MAffineFlow - setTranslation: One or more arguments were ignored.");

    const mwSize *dims;
    int len;

    dims = mxGetDimensions(prhs[3]);
    len = (int) dims[0];

    hypro::affineFlow<double> *flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], len);
    flow->setTranslation(vector);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setTranslation input:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vector.rows(); j++ ) {
    // 	mexPrintf( " %f", vector( j ) );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MAffineFlow::getTranslation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MAffineFlow - getTranslation: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MAffineFlow - getTranslation: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MAffineFlow - getTranslation: One or more arguments were ignored.");

    hypro::affineFlow<double> *flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    hypro::vector_t<double> vector = flow->getTranslation();

    plhs[0] = mxCreateDoubleMatrix(vector.size(), 1, mxREAL);
    ObjectHandle::convert2Matlab(vector, plhs[0], vector.size(), 1);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getTranslation output:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vector.rows(); j++ ) {
    // 	mexPrintf( " %f", vector( j ) );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MAffineFlow::hasTranslation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MAffineFlow - hasTranslation: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MAffineFlow - hasTranslation: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MAffineFlow - hasTranslation: One or more arguments were ignored.");

    hypro::affineFlow<double> *flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);
    const bool ans = flow->hasTranslation();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "hasTranslation output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "has translation\n" );
    // } else {
    // 	mexPrintf( "does not have translation\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MAffineFlow::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MAffineFlow - outstream: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MAffineFlow - outstream: One or more arguments were ignored.");

    hypro::affineFlow<double> *flow = convertMat2Ptr<hypro::affineFlow<double>>(prhs[2]);;
    hypro::matrix_t<double> mat = flow->getFlowMatrix();
    hypro::vector_t<double> vec = flow->getTranslation();

    int rows = mat.rows();
    int cols = mat.cols();

    int len = vec.size();

    mexPrintf("Matrix: [");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mexPrintf("%f ", mat(i, j));
        }
        mexPrintf("\n");
    }
    mexPrintf("]\n");

    mexPrintf("Vector: [");
    for (int i = 0; i < len; i++) {
        mexPrintf("%f ", vec(i));
    }
    mexPrintf("]\n\n");
}

void MAffineFlow::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        new_mat_vec(nlhs, plhs, nrhs, prhs);
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
    if (cmd == 6) {
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        hasTranslation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        setTranslation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        getTranslation(nlhs, plhs, nrhs, prhs);
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

    mexErrMsgTxt("MFlow - Command not recognized.");
}
