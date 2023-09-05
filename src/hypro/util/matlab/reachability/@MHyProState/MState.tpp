/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MState.h"

void MState::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - new_empty: Expecting an output.");
    hypro::State_t<double> *st = new hypro::State_t<double>();
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(st);
}

void MState::new_loc(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - new_loc: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - new_loc: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - new_loc: One or more input arguments were ignored.");

    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::State_t<double> *st = new hypro::State_t<double>(loc);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(st);
}

void MState::del_state(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MState - del_state: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - del_state: One or more arguments were ignored.");

    destroyObject<hypro::State_t<double>>(prhs[2]);
}

void MState::vertices(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MState - vertices: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MState - vertices: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - vertices: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[3]);
    std::vector<hypro::Point<double>> vertices = st->vertices(offset);
    int cols = vertices.size();
    if (cols != 0) {
        int rows = vertices[0].dimension();
        plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);
        ObjectHandle::convert2Matlab(vertices, plhs[0]);
    } else {
        mexWarnMsgTxt("MState - vertices: The object has no vertices.");
        plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    }

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "vertices output:\n" );
    // if ( cols != 0 ) {
    // 	int rows = vertices[0].dimension();
    // 	for ( int j = 0; j < cols; j++ ) {
    // 		hypro::Point<double> p = vertices[j];
    // 		for ( int i = 0; i < rows; i++ ) {
    // 			mexPrintf( " %f", p[i] );
    // 		}
    // 		mexPrintf( "\n" );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - copy: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - copy: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - copy: One or more input arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(st);
}

void MState::getSetType(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - getSetType: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - getSetType: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - getSetType: One or more input arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::representation_name name = st->getSetType();
    std::string ans;
    ObjectHandle::convert2Matlab(name, ans);
    plhs[0] = mxCreateString(ans.c_str());

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getSetType output:\n" );
    // mexPrintf("type: %s\n", ans.c_str());
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getSets(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - getSets: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - getSets: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - getSets: One or more input arguments were ignored.");

    hypro::State_t<double> *init = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::representation_name name = init->getSetType();
    std::vector states = init->getSets();
    mxArray *m_array_out;
    int len = states.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(states, plhs[0], len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getSets output:\n" );
    // mexPrintf("len: %d\n", len);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getTimestamp(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - getTimestamp: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - getTimestamp: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - getTimestamp: One or more input arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const carl::Interval <mpq_class> temp = st->getTimestamp();
    double lower = temp.lower().get_d();
    double upper = temp.upper().get_d();
    carl::Interval<double> inter(lower, upper);
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(inter, plhs[0], 1, 2);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getTimestamp output:\n" );
    // mexPrintf( "[%d, %d]\n", inter.lower(), inter.upper() );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::isEmpty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MState - isEmpty: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - isEmpty: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - isEmpty: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    bool tmp = st->isEmpty();
    mxLogical ans = tmp;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "is_empty input:\n" );
    // if ( tmp ) {
    // 	mexPrintf( "empty\n" );
    // } else {
    // 	mexPrintf( "not empty\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::projectOn(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MState - vertices: Expecting an output.");
    if (nrhs < 5) mexErrMsgTxt("MState - vertices: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MState - vertices: One or more arguments were ignored.");

    mxArray *m_in_dimensions;
    const mwSize *dims;
    double *in_dimensions;
    int len;

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    m_in_dimensions = mxDuplicateArray(prhs[3]);
    dims = mxGetDimensions(prhs[3]);
    len = (int) dims[1];
    std::vector<std::size_t> dimensions = ObjectHandle::mSizeVector2Hypro(m_in_dimensions, len);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[4]);

    hypro::State_t<double> new_st = st->projectOn(dimensions, offset);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(new_st));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "project input:\n" );
    // mexPrintf(" vector:\n");
    // for ( int j = 0; j < dimensions.size(); j++ ) {
    // 	mexPrintf( " %f", dimensions[j] );
    // }
    // mexPrintf("\noffset: %d\n", (double) offset);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getDimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MState - getDimension: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MState - getDimension: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - getDimension: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[3]);

    std::size_t dim = st->getDimension(offset);
    plhs[0] = mxCreateDoubleScalar(dim);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getDimension output:\n" );
    // mexPrintf("dim: %d\n", (double) dim);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getDimensionOffset(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs < 1) mexErrMsgTxt("MState - getDimensionOffset: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MState - getDimensionOffset: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - getDimensionOffset: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[3]);

    std::size_t dim = st->getDimensionOffset(offset);
    plhs[0] = mxCreateDoubleScalar(dim);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getDimensionOffset input:\n" );
    // mexPrintf("offset: %d\n", (double)dim);
    // mexPrintf("output\n");
    // mexPrintf("dim: %d\n", dim);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getLocation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - getLocation: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - getLocation: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - getLocation: One or more input arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::Location<double> *tmp = st->getLocation();
    hypro::Location<double> *loc = new hypro::Location<double>(*tmp);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLocations output:\n" );
    // mexPrintf("name: %s\n", loc->getName().c_str());
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getNumberSets(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - getNumberSets: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - getNumberSets: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - getNumberSets: One or more input arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    std::size_t tmp = st->getNumberSets();
    plhs[0] = mxCreateDoubleScalar(tmp);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getNumberSets output:\n" );
    // mexPrintf("num: %d\n", (double) tmp);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::getTypes(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - getTypes: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MState - getTypes: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MState - getTypes: One or more input arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    std::vector<hypro::representation_name> types = st->getTypes();
    const int rows = types.size();
    plhs[0] = mxCreateDoubleMatrix(rows, 1, mxREAL);
    vector2Matlab(types, plhs[0]);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getTypes output:\n" );
    // for(int i = 0; i < types.size(); i++){
    // 	hypro::representation_name name = types[i];
    // 	std::string n;
    // 	ObjectHandle::convert2Matlab(name, n);
    // 	mexPrintf("type %d: %s\n", i, n.c_str());

    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::setLocation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MState - setLocation: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - setLocation: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    st->setLocation(loc);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setLocation input:\n" );
    // std::string name = loc->getName();
    // mexPrintf("name: %s\n", name.c_str());
    // //+++++++++++++TESTING++++++++++++++++++++
}

// void MState::setSet( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
// 	if ( nrhs < 6 ) mexErrMsgTxt( "MState - setSet: One or more arguments are missing." );
// 	if ( nrhs > 6 ) mexWarnMsgTxt( "MState - setSet: One or more arguments were ignored." );

// 	hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>( prhs[2] );
// 	int type = mxGetScalar(prhs[4]);
// 	std::size_t at = mxGetScalar( prhs[5] );

// 	if ( type == 0 ) {
// 		hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>( prhs[3] );
// 		st->setSet( box, at );
// 	} else if ( type == 2 ) {
// 		hypro::ConstraintSet<double>* set = convertMat2Ptr<hypro::ConstraintSet<double>>( prhs[3] );
// 		st->setSet( set, at );
// 	} else if (type == 7) {
// 		hypro::SupportFunction<double>* fct = convertMat2Ptr<hypro::SupportFunction<double>>( prhs[3] );
// 		st->setSet( fct, at );
// 	} else if ( type == 8 ) {
// 		mexErrMsgTxt( "MState - setSet: Taylor models are not implemented yet." );
// 	} else {
// 		mexErrMsgTxt( "MState - setSet: Unknown set type." );
// 	}
// }

void MState::setSetType(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MState - setSetType: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MState - setSetType: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    int type = mxGetScalar(prhs[3]);
    hypro::representation_name name = ObjectHandle::mRepresentationName2Hypro(type);
    std::size_t pos = mxGetScalar(prhs[4]);
    st->setSetType(name, pos);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getTypes output:\n" );
    // std::string n;
    // ObjectHandle::convert2Matlab(name, n);
    // mexPrintf("type : %s\n", n.c_str());

    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::setTimestamp(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MState - setTimestamp: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - setTimestamp: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    // MPQ does not compile - linker
    // const carl::Interval<hypro::tNumber> inter = ObjectHandle::mMPQInterval2Hypro(prhs[3]);
    // st->setTimestamp(inter);
}

void MState::setSets(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MState - setSets: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MState - setSets: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    const mwSize *dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    if (!strcmp("Box", type)) {
        const std::vector<hypro::Box<double>> boxes = ObjectHandle::objArray2Hypro<hypro::Box<double>>(prhs[3], len);
        // st->setSets(boxes);?

    } else if (!strcmp("ConstraintSet", type)) {
    } else if (!strcmp("SupportFunction", type)) {
    } else if (!strcmp("TaylorModel", type)) {
        mexErrMsgTxt("MState - setSet: Taylor models are not implemented yet.");
    } else {
        mexErrMsgTxt("MState - setSet: Unknown set type.");
    }
}

// void MState::setSetSave(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

void MState::setSetDirect(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MState - setSetDirect: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MState - setSetDirect: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    const mwSize *dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    if (!strcmp("Box", type)) {
        const hypro::Box<double> *box = convertMat2Ptr<hypro::Box<double>>(prhs[3]);
        st->setSetDirect(*box);
    } else if (!strcmp("ConstraintSet", type)) {
        const hypro::ConstraintSet<double> *set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
        st->setSetDirect(*set);
    } else if (!strcmp("SupportFunction", type)) {
        const hypro::SupportFunction<double> *fct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
        st->setSetDirect(*fct);
    } else if (!strcmp("TaylorModel", type)) {
        mexErrMsgTxt("MState - setSet: Taylor models are not implemented yet.");
    } else {
        mexErrMsgTxt("MState - setSetDirect: Unknown set type.");
    }
}

void MState::setAndConvertType(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::addTimeToClocks(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::unite(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::satisfies(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 2) mexErrMsgTxt("MState - satisfies: Expecting two output values.");
    if (nrhs < 4) mexErrMsgTxt("MState - satisfies: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - satisfies: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);

    std::pair<hypro::CONTAINMENT, hypro::State_t<double>> p = st->satisfies(*cond);

    std::string cont;
    ObjectHandle::convert2Matlab(p.first, cont);
    plhs[0] = mxCreateString(cont.c_str());
    plhs[1] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(p.second));
}

void MState::satisfiesHalfspaces(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::intersectHalfspaces(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::partiallySatisfies(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::applyTimeStep(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::partiallyApplyTimeStep(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - satisfies: Expecting one output.");
    if (nrhs < 6) mexErrMsgTxt("MState - satisfies: One or more arguments are missing.");
    if (nrhs > 6) mexWarnMsgTxt("MState - satisfies: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::ConstraintSet<double> *set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
    hypro::tNumber stepSize = (hypro::tNumber) mxGetScalar(prhs[4]);
    std::size_t index = (std::size_t) mxGetScalar(prhs[5]);

    hypro::State_t<double> temp = st->partiallyApplyTimeStep(*set, stepSize, index);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(temp));
}

void MState::applyTransformation_vec(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::applyTransformation_at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::applyTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
}

void MState::linearTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - linearTransformation: Expecting one output.");
    if (nrhs < 4) mexErrMsgTxt("MState - linearTransformation: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - linearTransformation: One or more arguments were ignored.");

    const mwSize *dims;
    int rows, cols;
    dims = mxGetDimensions(prhs[3]);
    cols = dims[1];
    rows = dims[0];
    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], rows, cols);

    hypro::State_t<double> temp = st->linearTransformation(mat);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(temp));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "linearTransformation input:\n" );
    // mexPrintf( "matrix:\n" );
    // for ( int i = 0; i < mat.rows(); i++ ) {
    // 	for ( int j = 0; j < mat.cols(); j++ ) {
    // 		mexPrintf( " %f", mat( i, j ) );
    // 	}
    // 	mexPrintf( "\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::affineTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - affineTransformation: Expecting one output.");
    if (nrhs < 5) mexErrMsgTxt("MState - affineTransformation: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MState - affineTransformation: One or more arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_rows, mat_cols, vec_len;
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    mat_cols = mat_dims[1];
    mat_rows = mat_dims[0];
    vec_len = vec_dims[0];

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], mat_rows, mat_cols);
    const hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[4], vec_len);

    hypro::State_t<double> temp = st->affineTransformation(mat, vec);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(temp));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "affineTransformation input:\n" );
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
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MState::partialIntervalAssignment(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::partiallyApplyTransformation_vec(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::partiallyApplyTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Not in reach
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::minkowskiSum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MState - minkowskiSum: Expecting one output.");
    if (nrhs < 4) mexErrMsgTxt("MState - minkowskiSum: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MState - minkowskiSum: One or more arguments were ignored.");

    hypro::State_t<double> *st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::State_t<double> *rhs = convertMat2Ptr<hypro::State_t<double>>(prhs[3]);

    hypro::State_t<double> temp = st->minkowskiSum(*rhs);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("minkowskiSum\n");
    //+++++++++++++TESTING++++++++++++++++++++
}

// void MState::partiallyMinkowskiSum( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] ) {
// 	if ( nlhs != 1 ) mexErrMsgTxt( "MState - partiallyMinkowskiSum: Expecting one output." );
// 	if ( nrhs < 4 ) mexErrMsgTxt( "MState - partiallyMinkowskiSum: One or more arguments are missing." );
// 	if ( nrhs > 4 ) mexWarnMsgTxt( "MState - partiallyMinkowskiSum: One or more arguments were ignored." );

// 	hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>( prhs[2] );
// 	hypro::State_t<double>* rhs = convertMat2HandlePtr<hypro::State_t<double>>( prhs[3] );
// }

void MState::contains(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::getSupremum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::removeRedundancy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::partiallyRemoveRedundancy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::reduceRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::partiallyReduceRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::decompose(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::unequals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MState::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 1) {
        del_state(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        new_loc(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        getSetType(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        getSets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        getTimestamp(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        isEmpty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        vertices(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        projectOn(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        getDimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        getDimensionOffset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        getLocation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        getNumberSets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        // getSet( nlhs, plhs, nrhs, prhs );
        return;
    }
    if (cmd == 16) {
        getTypes(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        setLocation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        setSetType(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if ( cmd == 19 ) {
    // 	setSet( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    mexErrMsgTxt("MState - Command not recognized.");
}
