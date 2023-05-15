/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MCondition.h"

void MCondition::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - new_empty: Expecting an output!");

    plhs[0] = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>());
}

void MCondition::new_mat_vec(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - new_mat_vec: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MCondition - new_mat_vec: One or more input arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MCondition - new_mat_vec: One or more input arguments were ignored!");

    const mwSize *mat_dims, *vec_dims;
    int mat_rows, mat_cols, vec_len;
    mat_dims = mxGetDimensions(prhs[2]);
    vec_dims = mxGetDimensions(prhs[3]);
    mat_rows = mat_dims[0];
    mat_cols = mat_dims[1];
    vec_len = vec_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_rows, mat_cols);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], vec_len);
    plhs[0] = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>(matrix, vector));

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

void MCondition::new_constr_set(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - new_constr_set: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MCondition - new_constr_set: One or more input arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MCondition - new_constr_set: One or more input arguments were ignored!");

    const hypro::ConstraintSet<double> *constraint = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[2]);
    // hypro::Condition<double>* cond = new hypro::Condition<double>(*constraint);
    mexErrMsgTxt("Not implemented!");
    // plhs[0] = convertPtr2Mat<hypro::Condition<double>>(cond);
}

void MCondition::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - copy: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MCondition - copy: One or more input arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MCondition - copy: One or more input arguments were ignored!");

    hypro::Condition<double> *origin = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>(*origin));
}

void MCondition::delete_condition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MCondition - delete_condition: Expecting an output.");
    if (nrhs > 3) mexWarnMsgTxt("MCondition - delete_condition: One or more arguments were ignored.");
    destroyObject<hypro::Condition<double>>(prhs[2]);
}

void MCondition::size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - size: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MCondition - size: One or more input arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MCondition - size: One or more input arguments were ignored!");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    std::size_t s = cond->size();
    plhs[0] = mxCreateDoubleScalar(s);
}

void MCondition::isempty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - isempty: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MCondition - isempty: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MCondition - isempty: One or more arguments were ignored.");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    const bool ans = cond->empty();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "is_empty input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "empty\n" );
    // } else {
    // 	mexPrintf( "not empty\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::getMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - getMatrix: One output expected!");
    if (nrhs < 3) mexErrMsgTxt("MCondition - getMatrix: One or more arguments are missing!");
    if (nrhs > 3) mexErrMsgTxt("MCondition - getMatrix: One or more arguments were ignored!");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::matrix_t<double> mat = cond->getMatrix();
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

void MCondition::getVector(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - getVector: One output expected!");
    if (nrhs < 3) mexErrMsgTxt("MCondition - getVector: One or more arguments are missing!");
    if (nrhs > 3) mexErrMsgTxt("MCondition - getVector: One or more arguments were ignored!");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::vector_t<double> vec = cond->getVector();
    plhs[0] = mxCreateDoubleMatrix(vec.rows(), 1, mxREAL);
    ObjectHandle::convert2Matlab(vec, plhs[0], vec.rows(), 1);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "vector output:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vec.cols(); j++ ) {
    // 	mexPrintf( " %f", vec( j ) );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::isAxisAligned(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - isAxisAligned: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MCondition - isAxisAligned: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MCondition - isAxisAligned: One or more arguments were ignored.");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    const bool ans = cond->isAxisAligned();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "isAxisAligned output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "aligned\n" );
    // } else {
    // 	mexPrintf( "not aligned\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::isAxisAligned_at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - isAxisAligned_at: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MCondition - isAxisAligned_at: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MCondition - isAxisAligned_at: One or more arguments were ignored.");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    std::size_t s = mxGetScalar(prhs[3]);
    const bool ans = cond->isAxisAligned(s);
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "isAxisAligned input:\n" );
    // mexPrintf( "at: %d\n", (double)s );

    // if ( ans ) {
    // 	mexPrintf( "aligned\n" );
    // } else {
    // 	mexPrintf( "not aligned\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::setMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MCondition - setMatrix: One or more arguments are missing!");
    if (nrhs > 4) mexErrMsgTxt("MCondition - setMatrix: One or more arguments were ignored!");

    const mwSize *dims;
    int rows, cols;
    dims = mxGetDimensions(prhs[3]);
    rows = dims[0];
    cols = dims[1];

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], rows, cols);
    cond->setMatrix(mat);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setMatrix input:\n" );
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

void MCondition::setVector(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MCondition - setVector: One or more arguments are missing!");
    if (nrhs > 5) mexErrMsgTxt("MCondition - setVector: One or more arguments were ignored!");

    const mwSize *dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[3], len);
    std::size_t s = (std::size_t) mxGetScalar(prhs[4]);
    cond->setVector(vec, s);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "vector input:\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vec.cols(); j++ ) {
    // 	mexPrintf( " %f", vec( j ) );
    // }
    // mexPrintf( "at: %d\n", (double)s );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::constraints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - constraints: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MCondition - constraints: One or more arguments are missing!");
    if (nrhs > 3) mexErrMsgTxt("MCondition - constraints: One or more arguments were ignored!");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    std::vector<hypro::ConstraintSet<double>> constrs = cond->constraints();

    mxArray *m_out_constrs;
    int len = constrs.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = m_out_constrs = mxCreateCellArray(2, dims);
    objArray2Matlab(constrs, m_out_constrs, len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "constraints output:\n" );
    // for ( int i = 0; i < constrs.size(); i++ ) {
    // 	hypro::matrix_t<double> mat = constrs[i].matrix();
    // 	mexPrintf( "matrix %d:\n", i );
    // 	for ( int i = 0; i < mat.rows(); i++ ) {
    // 		for ( int j = 0; j < mat.cols(); j++ ) {
    // 			mexPrintf( " %f", mat( i, j ) );
    // 		}
    // 		mexPrintf( "\n" );
    // 	}
    // 	mexPrintf( "vector %d:\n", i );
    // 	hypro::vector_t<double> vec = constrs[i].vector();
    // 	for ( int j = 0; j < vec.cols(); j++ ) {
    // 		mexPrintf( " %f", vec( j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::hash(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - hash: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MCondition - hash: One or more input arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MCondition - hash: One or more input arguments were ignored!");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    std::size_t s = cond->hash();
    plhs[0] = mxCreateDoubleScalar(s);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "hash output:\n" );
    // mexPrintf( "hash: %d\n", (double)s );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::getDotRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - getDotRepresentation: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MCondition - getDotRepresentation: One or more input arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MCondition - getDotRepresentation: One or more input arguments were ignored!");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    std::vector<std::string> strs = ObjectHandle::mStringVector2Hypro(prhs[3]);

    std::string ans = cond->getDotRepresentation(strs);
    plhs[0] = mxCreateString(ans.c_str());
}

void MCondition::decompose(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // TODO:
}

void MCondition::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MCondition - ==: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MCondition - ==: One or more arguments are missing!");

    hypro::Condition<double> *cond_1 = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::Condition<double> *cond_2 = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    mxLogical ans = false;
    if (*cond_1 == *cond_2) {
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "equals input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "equal\n" );
    // } else {
    // 	mexPrintf( "not equal\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::unequals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MCondition - !=: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MCondition - !=: One or more arguments are missing!");

    hypro::Condition<double> *cond_1 = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::Condition<double> *cond_2 = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    mxLogical ans = false;
    if (*cond_1 != *cond_2) {
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "unequals input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "unequal\n" );
    // } else {
    // 	mexPrintf( "not unequal\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MCondition::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MCondition - ostream: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MCondition - ostream: One or more input arguments were ignored.");

    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::matrix_t<double> mat = cond->getMatrix();
    hypro::vector_t<double> vec = cond->getVector();

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

void MCondition::combine(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MCondition - getDotRepresentation: Expecting an output!");
    if (nrhs < 8) mexErrMsgTxt("MCondition - getDotRepresentation: One or more input arguments are missing!");
    if (nrhs > 8) mexWarnMsgTxt("MCondition - getDotRepresentation: One or more input arguments were ignored!");

    hypro::Condition<double> *obj = convertMat2Ptr<hypro::Condition<double>>(prhs[2]);
    hypro::Condition<double> *lhs = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    hypro::Condition<double> *rhs = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
    std::vector<std::string> haVar = ObjectHandle::mStringVector2Hypro(prhs[5]);
    std::vector<std::string> lhsVar = ObjectHandle::mStringVector2Hypro(prhs[6]);
    std::vector<std::string> rhsVar = ObjectHandle::mStringVector2Hypro(prhs[7]);
}

void MCondition::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        new_constr_set(nlhs, plhs, nrhs, prhs);
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
        delete_condition(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        isempty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        getMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        getVector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        isAxisAligned(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        isAxisAligned_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        setMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        setVector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        constraints(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        getDotRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        combine(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MCondition - Command not recognized.");
}
