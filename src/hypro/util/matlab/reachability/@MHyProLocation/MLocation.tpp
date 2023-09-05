/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MLocation.h"

void MLocation::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - new_empty: Expecting an output.");

    hypro::Location<double> *loc = new hypro::Location<double>();
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);
}

void MLocation::new_matrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - new_matrix: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - new_matrix: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - new_matrix: One or more arguments were ignored.");

    double *in_matrix;
    const mwSize *dims;
    int rows, cols;

    dims = mxGetDimensions(prhs[2]);
    cols = dims[1];
    rows = dims[0];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[2], rows, cols);
    hypro::Location<double> *loc = new hypro::Location<double>(mat);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_matrix input:\n" );
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

void MLocation::new_mat_tran_inv(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHyProLocation - new_mat_tran_inv: Expecting an output!");
    if (nrhs < 5) mexErrMsgTxt("MHyProLocation - new_mat_tran_inv: One or more arguments are missing!");
    if (nrhs > 5) mexWarnMsgTxt("MHyProLocation - new_mat_tran_inv: One or more input arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_rows, mat_cols, vec_len;

    mat_dims = mxGetDimensions(prhs[2]);
    mat_cols = (int) mat_dims[1];
    mat_rows = (int) mat_dims[0];
    vec_dims = mxGetDimensions(prhs[3]);
    vec_len = (int) vec_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_rows, mat_cols);
    const std::vector<hypro::Transition<double>> temp =
            ObjectHandle::objArray2Hypro<hypro::Transition<double>>(prhs[3], vec_len);
    hypro::Condition<double> *inv = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
    std::vector<std::unique_ptr<hypro::Transition<double>>> transitions;

    for (const auto &elem: temp) {
        hypro::Transition<double> *t = new hypro::Transition<double>(elem);
        std::unique_ptr<hypro::Transition<double>> tran = std::make_unique<hypro::Transition<double>>(*t);
        transitions.emplace_back(std::move(tran));
    }
    hypro::Location<double> *loc = new hypro::Location<double>(matrix, std::move(transitions), *inv);

    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_mat_tran_inv input:\n" );
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

void MLocation::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - copy: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - copy: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - copy: One or more arguments were ignored.");

    hypro::Location<double> *origin = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*origin));
}

void MLocation::delete_loc(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MLocation - delete_loc: Expecting an output.");
    if (nrhs > 3) mexWarnMsgTxt("MLocation - delete_loc: One or more arguments were ignored.");
    destroyObject<hypro::Location<double>>(prhs[2]);
}

void MLocation::getNumberFlow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getNumberFlow: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getNumberFlow: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getNumberFlow: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t num = loc->getNumberFlow();
    plhs[0] = mxCreateDoubleScalar(num);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getNumberFlow output:\n" );
    // mexPrintf( "size: %d\n", (double) num );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::getLinearFlow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getLinearFlow: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getLinearFlow: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getLinearFlow: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::linearFlow<double> flow = loc->getLinearFlow();
    plhs[0] = convertPtr2Mat<hypro::linearFlow<double>>(new hypro::linearFlow<double>(flow));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLinearFlow output:\n" );

    // hypro::matrix_t<double> mat = flow.getFlowMatrix();

    // int rows = mat.rows();
    // int cols = mat.cols();

    // mexPrintf( "Matrix: [" );
    // for ( int i = 0; i < rows; i++ ) {
    // 	for ( int j = 0; j < cols; j++ ) {
    // 		mexPrintf( "%f ", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::getLinearFlows(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getLinearFlows: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getLinearFlows: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getLinearFlows: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<hypro::linearFlow<double>> flows = loc->getLinearFlows();
    int len = flows.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(flows, plhs[0], len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLinearFlows output:\n" );

    // for(int i = 0; i < flows.size(); i++){
    // 	mexPrintf("Flow number: %d\n", i);
    // 	hypro::matrix_t<double> mat = flows[i].getFlowMatrix();
    // 	int rows = mat.rows();
    // 	int cols = mat.cols();
    // 	mexPrintf( "Matrix: [" );
    // 	for ( int i = 0; i < rows; i++ ) {
    // 		for ( int j = 0; j < cols; j++ ) {
    // 			mexPrintf( "%f ", mat( i, j ) );
    // 		}
    // 		mexPrintf( "\n" );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf("\n");
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::getInvariant(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getInvariant: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getInvariant: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getInvariant: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Condition<double> cond = loc->getInvariant();
    plhs[0] = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>(cond));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getInvariant output:\n" );
    // hypro::matrix_t<double> mat = cond.getMatrix();
    // hypro::vector_t<double> vec = cond.getVector();
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vec.cols(); j++ ) {
    // 	mexPrintf( " %f", vec( j ) );
    // }
    // mexPrintf("\n");
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::getTransitions(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getTransitions: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getTransitions: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getTransitions: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<hypro::Transition<double> *> temp = loc->getTransitions();
    std::vector<hypro::Transition<double>> transitions;

    for (const auto &elem: temp) {
        transitions.emplace_back(*elem);
    }

    int len = temp.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(transitions, plhs[0], len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getTransions output:\n" );
    // for(int i = 0; i < temp.size(); i++){
    // 	hypro::Transition<double> tran = *temp[i];
    // 	hypro::Location<double>* source = tran.getSource();
    // 	hypro::Location<double>* target = tran.getTarget();
    // 	std::string s = source->getName();
    // 	std::string t = target->getName();
    // 	mexPrintf("transition %d: %s -> %s\n", i, s.c_str(), t.c_str());
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::getExternalInput(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getExternalInput: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getExternalInput: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getExternalInput: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<carl::Interval < double>>
    input = loc->getExternalInput();
    plhs[0] = mxCreateDoubleMatrix(input.size(), 2, mxREAL);
    vector2Matlab<carl::Interval < double>>
    (input, plhs[0]);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getExternalInput output:\n" );
    // mexPrintf( "intervals:\n" );
    // for ( int j = 0; j < input.size(); j++ ) {
    // 	carl::Interval<double> inter = input[j];
    // 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::hasExternalInput(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - hasExternalInput: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - hasExternalInput: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - hasExternalInput: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    const bool ans = loc->hasExternalInput();
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "hasExternalInput output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "has\n" );
    // } else {
    // 	mexPrintf( "does not have\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::hash(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - hash: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - hash: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - hash: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t h = loc->hash();
    plhs[0] = mxCreateDoubleScalar(h);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "hash output:\n" );
    // mexPrintf( "hash: %d\n", (double)h );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::getName(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - getName: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - getName: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - getName: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::string name = loc->getName();
    plhs[0] = mxCreateString(name.c_str());

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getName output:\n" );
    // mexPrintf( "name: %s\n", name.c_str() );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::dimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - dimension: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLocation - dimension: One or more arguments are missing.");
    if (nrhs > 3) mexErrMsgTxt("MLocation - dimension: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t h = loc->dimension();
    plhs[0] = mxCreateDoubleScalar(h);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "dimension output:\n" );
    // mexPrintf( "hash: %d\n", (double)h );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::dimension_at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - dimension_at: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MLocation - dimension_at: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - dimension_at: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t pos = (std::size_t) mxGetScalar(prhs[3]);
    std::size_t h = loc->dimension(pos);
    plhs[0] = mxCreateDoubleScalar(h);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "dimension_at input:\n" );
    // mexPrintf( "at: %d\n", (double)pos );
    // mexPrintf("output\n");
    // mexPrintf("dimension: %d\n", (double)h);

    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::setName(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLocation - setName: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - setName: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    char *name = mxArrayToString(prhs[3]);
    loc->setName(std::string(name));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setName input:\n" );
    // mexPrintf( "name: %s\n", name );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::setFlow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLocation - setFlow: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - setFlow: One or more arguments were ignored.");

    double *in_matrix;
    const mwSize *dims;
    int rows, cols;

    dims = mxGetDimensions(prhs[3]);
    cols = dims[1];
    rows = dims[0];

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], rows, cols);

    loc->setFlow(mat);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setFlow input:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf("\n");
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::setLinearFlow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MLocation - setLinearFlow: One or more arguments are missing.");
    if (nrhs > 5) mexErrMsgTxt("MLocation - setLinearFlow: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    const hypro::linearFlow<double> *flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[3]);
    std::size_t i = (std::size_t) mxGetScalar(prhs[4]);
    loc->setLinearFlow(*flow, i);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setLinearFlow input:\n" );
    // hypro::matrix_t<double> mat = flow->getFlowMatrix();
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "pos: %d\n", (double)i );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::setLinearFlow_vec(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLocation - setFlow_vec: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - setFlow_vec: One or more arguments were ignored.");

    const mwSize *dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    const std::vector<hypro::linearFlow<double>> flows =
            ObjectHandle::objArray2Hypro<hypro::linearFlow<double>>(prhs[3], len);
    loc->setLinearFlow(flows);

    // //+++++++++++++TESTING++++++++++++++++++++
    // for(int k = 0; k < flows.size(); k++){
    // 	mexPrintf( "flow %d:\n", k );
    // 	const hypro::linearFlow<double> flow = flows[k];
    // 	hypro::matrix_t<double> mat = flow.getFlowMatrix();
    // 	mexPrintf( "matrix:\n" );
    // 	for ( int i = 0; i < mat.rows(); i++ ) {
    // 		for ( int j = 0; j < mat.cols(); j++ ) {
    // 			mexPrintf( " %f", mat( i, j ) );
    // 		}
    // 		mexPrintf( "\n" );
    // 	}
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::setInvariant(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLocation - setInvariant: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - setInvariant: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    loc->setInvariant(*cond);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setInvariant output:\n" );
    // hypro::matrix_t<double> mat = cond->getMatrix();
    // hypro::vector_t<double> vec = cond->getVector();
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // mexPrintf( "\n" );
    // mexPrintf( "vector:\n" );
    // for ( int j = 0; j < vec.cols(); j++ ) {
    // 	mexPrintf( " %f", vec( j ) );
    // }
    // mexPrintf("\n");
    // //+++++++++++++TESTING++++++++++++++++++++
}

// void MLocation::setTransition(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
//     if(nrhs < 4)
//          mexErrMsgTxt("MLocation - setTransition: One or more arguments are missing.");
//     if(nrhs > 4)
//          mexErrMsgTxt("MLocation - setTransition: One or more arguments were ignored.");

//     hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
//     hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
//     loc->setTransition(*tran);
// }

void MLocation::addTransition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLocation - addTransition: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - addTransition: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Transition<double> *temp = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
    std::unique_ptr<hypro::Transition<double>> tran(new hypro::Transition<double>(*temp));
    loc->addTransition(std::move(tran));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "addTransion input:\n" );

    // hypro::Location<double>* source = temp->getSource();
    // hypro::Location<double>* target = temp->getTarget();
    // std::string s = source->getName();
    // std::string t = target->getName();
    // mexPrintf("transition: %s -> %s\n", s.c_str(), t.c_str());
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::setExtInput(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLocation - setExtInput: One or more arguments are missing.");
    if (nrhs > 4) mexErrMsgTxt("MLocation - setExtInput: One or more arguments were ignored.");

    const mwSize *dims;
    int rows, cols;

    dims = mxGetDimensions(prhs[3]);
    cols = dims[1];
    rows = dims[0];
    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<carl::Interval < double>>
    ints = ObjectHandle::mIntervals2Hypro(prhs[3], rows, cols);
    loc->setExtInput(ints);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setExtInput input:\n" );
    // mexPrintf( "intervals:\n" );
    // for ( int j = 0; j < ints.size(); j++ ) {
    // 	carl::Interval<double> inter = ints[j];
    // 	mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // }
    // mexPrintf( "\n" );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::isComposedOf(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - isComposedOf: Expecting an output!");
    if (nrhs < 6) mexErrMsgTxt("MLocation - isComposedOf: One or more arguments are missing!");
    if (nrhs > 6) mexWarnMsgTxt("MLocation - isComposedOf: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double> *rhs = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    std::vector<std::string> rhsVars = ObjectHandle::mStringVector2Hypro(prhs[4]);
    std::vector<std::string> thisVars = ObjectHandle::mStringVector2Hypro(prhs[5]);

    // bool ans = loc->isComposedOf(*rhs, rhsVars, thisVars);
    // plhs[0] = mxCreateLogicalScalar(ans); ---> ?

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("isComposedOf:\n");
    //+++++++++++++TESTING++++++++++++++++++++
}

// void MLocation::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MLocation - getDotRepresentation: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MLocation - getDotRepresentation: One or more arguments are missing!");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MLocation - getDotRepresentation: One or more arguments were ignored.");

//     hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
//     std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro(prhs[3]);
//     std::string rep = loc->getDotRepresentation(vars);
//     plhs[0] = mxCreateString(rep.c_str());
// }

void MLocation::decompose(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // TODO
}

void MLocation::less(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - less: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MLocation - less: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MLocation - less: One or more arguments were ignored.");

    hypro::Location<double> *loc_1 = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double> *loc_2 = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    mxLogical ans = false;
    if (*loc_1 < *loc_2) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "less output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "less\n" );
    // } else {
    // 	mexPrintf( "not less\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - equals: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MLocation - equals: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MLocation - equals: One or more arguments were ignored.");

    hypro::Location<double> *loc_1 = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double> *loc_2 = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    mxLogical ans = false;
    if (*loc_1 == *loc_2) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "equals output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "equal\n" );
    // } else {
    // 	mexPrintf( "not equal\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::unequals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLocation - unequals: Expecting an output!");
    if (nrhs < 4) mexErrMsgTxt("MLocation - unequals: One or more arguments are missing!");
    if (nrhs > 4) mexWarnMsgTxt("MLocation - unequals: One or more arguments were ignored.");

    hypro::Location<double> *loc_1 = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double> *loc_2 = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    mxLogical ans = false;
    if (*loc_1 != *loc_2) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "unequals output:\n" );
    // if ( ans ) {
    // 	mexPrintf( "unequal\n" );
    // } else {
    // 	mexPrintf( "unnot equal\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLocation::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MLocation - outstream: One or more arguments are missing!");
    if (nrhs > 3) mexWarnMsgTxt("MLocation - outstream: One or more arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::string name = loc->getName();
    mexPrintf("%s\n", name.c_str());
}

void MLocation::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        new_matrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        new_mat_tran_inv(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1) {
        delete_loc(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        getNumberFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        getLinearFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        getLinearFlows(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        getInvariant(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        getTransitions(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        getExternalInput(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        hasExternalInput(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        getName(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        dimension_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        setName(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        setFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        setLinearFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        setLinearFlow_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21) {
        setInvariant(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 23) {
        addTransition(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 22) {
        setExtInput(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 24) {
        isComposedOf(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if (cmd == 25){
    //     getDotRepresentation(nlhs, plhs, nrhs, prhs);
    //     return;
    // }
    if (cmd == 26) {
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 27) {
        less(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 28) {
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 29) {
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 30) {
        destroySmartObject<hypro::Location<double>>(prhs[2]);
    }
    mexErrMsgTxt("MLocation - Command not recognized.");
}
