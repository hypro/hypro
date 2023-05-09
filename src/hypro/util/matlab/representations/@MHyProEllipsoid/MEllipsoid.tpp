/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MEllipsoid.h"

void MEllipsoid::ellipsoid_rad(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MEllipsoid - ellipsoid_rad: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MEllipsoid - ellipsoid_rad: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MEllipsoid - ellipsoid_rad: One or more input arguments were ignored.");

    double radius = (double) mxGetScalar(prhs[2]);
    size_t dim = (size_t) mxGetScalar(prhs[3]);

    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(new hypro::Ellipsoid<double>(radius, dim));
}

void MEllipsoid::approxEllipsoidTMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MEllipsoid - approxEllipsoidTMatrix: Expecting one output value!");
    if (nrhs < 4) mexErrMsgTxt("MEllipsoid - approxEllipsoidTMatrix: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MEllipsoid - approxEllipsoidTMatrix: One or more input arguments were ignored.");

    const mwSize *dims;
    int dimx, dimy;

    hypro::Ellipsoid<double> *ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);
    hypro::matrix_t<double> out_mat = ellipse->approxEllipsoidTMatrix(mat);
    plhs[0] = mxCreateDoubleMatrix(out_mat.rows(), out_mat.cols(), mxREAL);
    ObjectHandle::convert2Matlab(out_mat, plhs[0], out_mat.cols(), out_mat.rows());
}

void MEllipsoid::ostream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MEllipsoid - ostream: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MEllipsoid - ostream: One or more input arguments were ignored.");

    hypro::Ellipsoid<double> *obj = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    hypro::matrix_t<double> mat = obj->matrix();

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

void MEllipsoid::type(int nlhs, mxArray *plhs[], int rhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MEllipsoid - type: Expecting one output value!");
    std::string ans = "MHyProEllipsoid";
    plhs[0] = mxCreateString(ans.c_str());
}

/**
 * @brief The entry point to the HyPro Ellipsoid class for Matalb.
 * @param nlhs Number of items in plhs
 * @param plhs Array of mxArray pointers to the output variables
 * @param nrhs Number of items in prhs
 * @param prhs Array of mxArray pointers to the input variables
 **/
void MEllipsoid::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {

    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 17) {
        ellipsoid_rad(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        new_matrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 2) {
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        ostream(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        linearTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        affineTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        minkowskiSum(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21) {
        approxEllipsoidTMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MEllipsoid - Command not recognized.");
}
