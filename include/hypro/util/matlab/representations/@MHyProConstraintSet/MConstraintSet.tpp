/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MConstraintSet.h"

void MConstraintSet::isAxisAligned(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MConstraintSet - isAxisAligned: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MConstraintSet - isAxisAligned: One argument missing!");
    if (nrhs > 3) mexWarnMsgTxt("MConstraintSet - isAxisAligned: One or more input arguments were ignored.");

    hypro::ConstraintSet<double> *temp = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    const bool aligned = temp->isAxisAligned();
    plhs[0] = mxCreateLogicalScalar(aligned);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "isAxisAligned output:\n" );
    // if ( aligned ) {
    // 	mexPrintf( "aligned\n" );
    // } else {
    // 	mexPrintf( "not aligned\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MConstraintSet::addConstraint(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MConstraintSet - addConstraint: One or more arguments are missing!");
    if (nrhs > 5) mexWarnMsgTxt("MConstraintSet - addConstraint: One or more input arguments were ignored.");

    const mwSize *dims;
    dims = mxGetDimensions(prhs[3]);
    int cols = (int) dims[1];
    hypro::ConstraintSet<double> *temp = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    const hypro::vector_t<double> hy_vec = ObjectHandle::mVector2Hypro(prhs[3], cols);
    const double offset = (const double) mxGetScalar(prhs[4]);
    temp->addConstraint(hy_vec, offset);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "Add constraint input:\n" );
    // mexPrintf( "Vector: " );
    // for ( int i = 0; i < hy_vec.size(); i++ ) {
    // 	mexPrintf( " %f", hy_vec( i ) );
    // }
    // mexPrintf( "\n offset: %d\n", offset );
    // hypro::matrix_t<double> mat = temp->matrix();
    // hypro::vector_t<double> vec = temp->vector();
    // mexPrintf( "Output:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\nvector: " );
    // for ( int i = 0; i < vec.rows(); i++ ) {
    // 	mexPrintf( " %f", vec( i ) );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MConstraintSet::type(int nlhs, mxArray *plhs[], int rhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MConstraintSet - type: Expecting one output value!");
    std::string ans = "MHyProConstraintSet";
    plhs[0] = mxCreateString(ans.c_str());
}

void MConstraintSet::reduceNumberRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("HyProConstraintSet - reduceNumberRepresentation: Expecting an output!");
    if (nrhs < 4)
        mexErrMsgTxt("HyProConstraintSet - reduceNumberRepresentation: One or more arguments are missing!");
    if (nrhs > 4)
        mexWarnMsgTxt("MConstraintSet - reduceNumberRepresentation: One or more input arguments were ignored.");

    hypro::ConstraintSet<double> *temp = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    const unsigned u = (const unsigned) mxGetScalar(prhs[3]);
    hypro::ConstraintSet<double> obj = temp->reduceNumberRepresentation(u);
    plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>(new hypro::ConstraintSet<double>(obj));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "Add reduceNumberRepresentataion input:\n" );
    // mexPrintf( "u: %d\n", u );

    // hypro::matrix_t<double> mat = temp->matrix();
    // hypro::vector_t<double> vec = temp->vector();
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\nvector: " );
    // for ( int i = 0; i < vec.rows(); i++ ) {
    // 	mexPrintf( " %f", vec( i ) );
    // }
    // mexPrintf( "\n" );

    // mexPrintf( "Output:\n" );
    // hypro::matrix_t<double> matt = obj.matrix();
    // hypro::vector_t<double> vect = obj.vector();
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < matt.rows(); i++ ) {
    // 	for ( int j = 0; j < matt.cols(); j++ ) {
    // 		mexPrintf( " %f", matt( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\nvector: " );
    // for ( int i = 0; i < vect.rows(); i++ ) {
    // 	mexPrintf( " %f", vect( i ) );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

/**
 * @brief The entry point to the HyPro Constraint Set class for Matalb.
 * @param nlhs Number of items in plhs
 * @param plhs Array of mxArray pointers to the output variables
 * @param nrhs Number of items in prhs
 * @param prhs Array of mxArray pointers to the input variables
 **/
void MConstraintSet::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 1) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 2) {
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        vertices(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        reduceRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        ostream(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        vector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        removeRedundancy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        satisfiesHalfspace(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        satisfiesHalfspaces(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        projectOn(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        linearTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        affineTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        minkowskiSum(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        intersectHalfspace(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21) {
        intersectHalfspaces(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 22) {
        contains_point(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 23) {
        contains_object(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 24) {
        reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 25) {
        intersect(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 26) {
        unite_single(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 27) {
        unite_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (cmd == 100) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 101) {
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 102) {
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 103) {
        contains_point(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 104) {
        isAxisAligned(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 105) {
        addConstraint(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MConstraintSet - Command not recognized.");
}
