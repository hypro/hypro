/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MReset.h"

void MReset::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - new_empty: Expecting an output.");

    hypro::Reset<double> *temp = new hypro::Reset<double>();
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(temp);
}

void MReset::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - copy: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MReset - copy: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MReset - copy: One or more arguments were ignored.");

    hypro::Reset<double> *origin = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(new hypro::Reset<double>(*origin));
}

void MReset::new_mat_vec(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - new_mat_vec: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MReset - new_mat_vec: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MReset - new_mat_vec: One or more arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_rows, mat_cols, len;

    mat_dims = mxGetDimensions(prhs[2]);
    vec_dims = mxGetDimensions(prhs[3]);
    mat_cols = (int) mat_dims[1];
    mat_rows = (int) mat_dims[0];
    len = (int) vec_dims[0];

    const hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_rows, mat_cols);
    const hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], len);
    // hypro::Reset<double>* reset = new hypro::Reset<double>( matrix, vector );
    // plhs[0] = convertPtr2Mat<hypro::Reset<double>>(reset);
    mexErrMsgTxt("NOT IMPLEMENTED");

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_mat_vec input:\n" );

    // for ( int i = 0; i < matrix.rows(); i++ ) {
    // 	for ( int j = 0; j < matrix.cols(); j++ ) {
    // 		mexPrintf( " %f", matrix( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "vector %d:\n");
    // for ( int j = 0; j < vector.rows(); j++ ) {
    // 	mexPrintf( " %f", vector( j ) );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::new_intervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - new_intervals: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MReset - new_intervals: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MReset - new_intervals: One or more input arguments were ignored.");

    const mwSize *dims;
    double *in;
    int rows, cols;

    dims = mxGetDimensions(prhs[2]);
    cols = (int) dims[0];
    rows = (int) dims[1];
    const std::vector<carl::Interval < double>>
    intervals = ObjectHandle::mIntervals2Hypro(prhs[2], rows, cols);
    // hypro::Reset<double>* temp = new hypro::Reset<double>(intervals);
    // plhs[0] = convertPtr2Mat<hypro::Reset<double>>(temp);
    mexErrMsgTxt("NOT IMPLEMENTED");

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_intervals input:\n" );
    // mexPrintf( "intervals:\n" );
    // for ( int j = 0; j < intervals.size(); j++ ) {
    // 	carl::Interval<double> inter = intervals[j];
    // 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::delete_reset(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MReset - delete_reset: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MReset - delete_reset: One or more arguments were ignored.");

    destroyObject<hypro::Reset<double>>(prhs[2]);
}

void MReset::empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - empty: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MReset - empty: One argument missing!");
    if (nrhs > 3) mexWarnMsgTxt("MReset - empty: One or more input arguments were ignored.");

    hypro::Reset<double> *temp = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    const bool empty = temp->empty();
    plhs[0] = mxCreateLogicalScalar(empty);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "empty output:\n" );
    // if ( empty ) {
    // 	mexPrintf( "yes\n" );
    // } else {
    // 	mexPrintf( "no\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - size: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MReset - size: One or more arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MReset - size: One or more input arguments were ignored.");

    hypro::Reset<double> *temp = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t dim = temp->size();
    plhs[0] = mxCreateDoubleScalar(dim);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "size output:\n" );
    // mexPrintf("size: %d\n", (double) dim);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getVector(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getVector: One output expected!");
    if (nrhs < 4) mexErrMsgTxt("MReset - getVector: One or more arguments are missing!");
    if (nrhs > 4) mexErrMsgTxt("MReset - getVector: One or more arguments were ignored!");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    hypro::vector_t<double> vec = res->getVector(pos);
    plhs[0] = mxCreateDoubleMatrix(vec.rows(), 1, mxREAL);
    ObjectHandle::convert2Matlab(vec, plhs[0], vec.rows(), 1);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getVector output:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vec.cols(); j++ ) {
    // 	mexPrintf( " %f", vec( j ) );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getMatrix: One output expected!");
    if (nrhs < 4) mexErrMsgTxt("MReset - getMatrix: One or more arguments are missing!");
    if (nrhs > 4) mexErrMsgTxt("MReset - getMatrix: One or more arguments were ignored!");

    hypro::Reset<double> *cond = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    hypro::matrix_t<double> mat = cond->getMatrix(pos);
    plhs[0] = mxCreateDoubleMatrix(mat.rows(), mat.cols(), mxREAL);
    ObjectHandle::convert2Matlab(mat, plhs[0], mat.rows(), mat.cols());

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getMatrix output:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getIntervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getIntervals: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MReset - getIntervals: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MReset - getIntervals: One or more input arguments were ignored.");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    std::vector<carl::Interval < double>>
    intervals = res->getIntervals(pos);
    const int rows = intervals.size();
    const int cols = 2;
    plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);
    vector2Matlab(intervals, plhs[0]);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getIntervals output:\n" );
    // mexPrintf( "intervals:\n" );
    // for ( int j = 0; j < intervals.size(); j++ ) {
    // 	carl::Interval<double> inter = intervals[j];
    // 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getAffineReset_at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getAffineReset_at: One output expected!");
    if (nrhs < 4) mexErrMsgTxt("MReset - getAffineReset_at: One or more arguments are missing!");
    if (nrhs > 4) mexErrMsgTxt("MReset - getAffineReset_at: One or more arguments were ignored!");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    hypro::AffineTransformation<double> affRes = res->getAffineReset(pos);
    hypro::ConstraintSet<double> cond = affRes.mTransformation;
    plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>(new hypro::ConstraintSet<double>(cond));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getAffineReset_at input:\n" );
    // mexPrintf( "at %d:\n", (double) pos );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getAffineResets(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getAffineResets: One output expected!");
    if (nrhs < 3) mexErrMsgTxt("MReset - getAffineResets: One or more arguments are missing!");
    if (nrhs > 3) mexErrMsgTxt("MReset - getAffineResets: One or more arguments were ignored!");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::vector<hypro::AffineTransformation<double>> affRests = res->getAffineResets();
    std::vector<hypro::ConstraintSet<double>> conds(affRests.size());

    for (int i = 0; i < affRests.size(); i++) {
        conds[i] = affRests[i].mTransformation;
    }
    int len = conds.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab<hypro::ConstraintSet<double>>(conds, plhs[0], conds.size());

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getAffineResets output:\n" );
    // mexPrintf( "len %d:\n", (double) len );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getIntervalReset_at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getIntervalReset_at: One output expected!");
    if (nrhs < 4) mexErrMsgTxt("MReset - getIntervalReset_at: One or more arguments are missing!");
    if (nrhs > 4) mexErrMsgTxt("MReset - getIntervalReset_at: One or more arguments were ignored!");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    hypro::IntervalAssignment<double> intAss = res->getIntervalReset(pos);
    std::vector<carl::Interval < double>>
    ints = intAss.mIntervals;
    plhs[0] = mxCreateDoubleMatrix(1, ints.size(), mxREAL);
    vector2Matlab<carl::Interval < double>>
    (ints, plhs[0]);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getIntervalReset_at input:\n" );
    // mexPrintf( "at %d:\n", (double) pos );
    // mexPrintf("output:\n");
    // mexPrintf( "intervals:\n" );
    // for ( int j = 0; j < ints.size(); j++ ) {
    // 	carl::Interval<double> inter = ints[j];
    // 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::getIntervalResets(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - getIntervalResets: One output expected!");
    if (nrhs < 3) mexErrMsgTxt("MReset - getIntervalResets: One or more arguments are missing!");
    if (nrhs > 3) mexErrMsgTxt("MReset - getIntervalResets: One or more arguments were ignored!");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::vector<hypro::IntervalAssignment<double>> intAss = res->getIntervalResets();
    std::vector<std::vector<carl::Interval < double>> > ints(intAss.size());

    for (int i = 0; i < ints.size(); i++) {
        ints[i] = intAss[i].mIntervals;
    }

    int len = ints.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);

    for (int i = 0; i < ints.size(); i++) {
        mxArray *elem = mxCreateDoubleMatrix(ints[i].size(), 2, mxREAL);
        vector2Matlab<carl::Interval < double>>
        (ints[i], elem);
        mxSetCell(plhs[0], i, elem);
    }

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getIntervalResets output:\n" );
    // mexPrintf( "intervals:\n" );
    // for(int i = 0; i < ints.size(); i++){
    // 	if(ints.size() > 0){
    // 		std::vector<carl::Interval<double>> curr = ints[i];
    // 		for(int j = 0; j < curr.size(); j++){
    // 			carl::Interval<double> inter = curr[j];
    // 			mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // 		}
    // 	}
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::setVector(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MReset - setVector: One or more arguments are missing!");
    if (nrhs > 5) mexErrMsgTxt("MReset - setVector: One or more arguments were ignored!");

    const mwSize *dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];
    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[3], len);
    std::size_t at = mxGetScalar(prhs[4]);
    res->setVector(vec, at);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setVector input:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vec.cols(); j++ ) {
    // 	mexPrintf( " %f", vec( j ) );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::setMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MReset - setMatrix: One or more arguments are missing!");
    if (nrhs > 5) mexErrMsgTxt("MReset - setMatrix: One or more arguments were ignored!");

    const mwSize *dims;
    int rows, cols;
    dims = mxGetDimensions(prhs[3]);
    rows = dims[0];
    cols = dims[1];

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], rows, cols);
    std::size_t at = mxGetScalar(prhs[4]);
    res->setMatrix(mat, at);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setMatrix output:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::setIntervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MReset- setIntervals: One or more input arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MReset- setIntervals: One or more input arguments were ignored.");

    const mwSize *dims;
    double *in;
    int rows, cols;

    dims = mxGetDimensions(prhs[3]);
    cols = (int) dims[1];
    rows = (int) dims[0];

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::vector<carl::Interval < double>>
    intervals = ObjectHandle::mIntervals2Hypro(prhs[3], rows, cols);
    std::size_t at = mxGetScalar(prhs[4]);
    res->setIntervals(intervals, at);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setIntervals input:\n" );
    // mexPrintf( "intervals:\n" );
    // for ( int j = 0; j < intervals.size(); j++ ) {
    // 	carl::Interval<double> inter = intervals[j];
    // 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::isIdentity(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - isIdentity: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MReset - isIdentity: One argument missing!");
    if (nrhs > 3) mexWarnMsgTxt("MReset - isIdentity: One or more input arguments were ignored.");

    hypro::Reset<double> *temp = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    const bool ans = temp->isIdentity();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "isIndentity output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "yes\n" );
    // } else {
    // 	mexPrintf( "no\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::hash(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MReset - hash: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MReset - hash: One or more input arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MReset - hash: One or more input arguments were ignored!");

    hypro::Reset<double> *res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t val = res->hash();
    plhs[0] = mxCreateDoubleScalar(val);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "hash output:\n" );
    // mexPrintf("hash: %d\n", (double) val);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MReset::decompose(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
    // TODO:
}

void MReset::combine(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // if(nlhs != 1)
    //     mexErrMsgTxt("MReset - combine: Expecting an output!");
    // if(nrhs < 7)
    //     mexErrMsgTxt("MReset - combine: One or more input arguments are missing!");
    // if(nrhs > 7)
    //     mexWarnMsgTxt("MReset - combine: One or more input arguments were ignored!");

    // const mwSize *dims_var, *dims_lhs, *dims_rhs;
    // int len_var, len_lhs, len_rhs;

    // hypro::Reset<double>* lhs = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    // hypro::Reset<double>* rhs = convertMat2Ptr<hypro::Reset<double>>(prhs[3]);
    // std::vector<std::string> haVar = ObjectHandle::mStringVector2Hypro(prhs[4]);
    // std::vector<std::string> lhsVar = ObjectHandle::mStringVector2Hypro(prhs[5]);
    // std::vector<std::string> rhsVar = ObjectHandle::mStringVector2Hypro(prhs[6]);

    // TODO:
    // hypro::Reset<double>* res = lhs->combine(lhs, rhs, haVar, lhsVar, rhsVar);
    // plhs[0] = convertPtr2Mat<hypro::Reset<double>>(new hypro::Reset<double>(*res));
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MReset::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if (cmd == 5){
    //     new_mat_vec(nlhs, plhs, nrhs, prhs);
    //     return;
    // }
    if (cmd == 4) {
        new_intervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1) {
        delete_reset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        getVector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        getMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        getIntervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        getAffineReset_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        getAffineResets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        getIntervalReset_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        getIntervalResets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        setVector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        setMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        setIntervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        isIdentity(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21) {
        combine(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MRest - Command not recognized.");
}
