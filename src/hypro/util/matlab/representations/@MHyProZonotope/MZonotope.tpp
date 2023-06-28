/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MZonotope.h"

void MZonotope::newZonotopeDimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - newZonotopeDimension: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - newZonotopeDimension: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - newZonotopeDimension: One or more input arguments were ignored.");

    std::size_t dimension = (std::size_t) mxGetScalar(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(dimension));
}

void MZonotope::newZonotopeCG(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - newZonotopeCG: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MZonotope - newZonotopeCG: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - newZonotopeCG: One or more input arguments were ignored.");

    const mwSize *gen_dims, *cen_dims;
    int gen_rows, gen_cols, len;

    cen_dims = mxGetDimensions(prhs[2]);
    len = (int) cen_dims[0];
    gen_dims = mxGetDimensions(prhs[3]);
    gen_cols = (int) gen_dims[1];
    gen_rows = (int) gen_dims[0];
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[2], len);
    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[3], gen_rows, gen_cols);

    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(vector, matrix));
}

void MZonotope::copyDimensions(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - copyDimensions: One output expected.");
    if (nrhs < 5) mexErrMsgTxt("MZonotope - copyDimensions: One or more input arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MZonotope - copyDimensions: One or more input arguments were ignored.");

    hypro::Zonotope<double> *origin = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    unsigned d1 = (unsigned) mxGetScalar(prhs[3]);
    unsigned d2 = (unsigned) mxGetScalar(prhs[4]);
    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(*origin, d1, d2));
}

void MZonotope::supremum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - supremum: Expecting an output!");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - supremum: One argument missing!");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - supremum: One or more input arguments were ignored.");

    hypro::Zonotope<double> *obj = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    double supremum = obj->supremum();
    plhs[0] = mxCreateDoubleScalar(supremum);
}

void MZonotope::emptyAt(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - emptyAt: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MZonotope - emptyAt: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - emptyAt: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    std::size_t at_dim = (std::size_t) mxGetScalar(prhs[3]);
    hypro::Zonotope<double> temp = zono->Empty(at_dim);
    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(temp));
}

void MZonotope::setCenter(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MZonotope - setCenter: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - setCenter: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    const mwSize *cen_dims;
    int len;
    cen_dims = mxGetDimensions(prhs[3]);
    len = (int) cen_dims[0];
    hypro::vector_t<double> center = ObjectHandle::mVector2Hypro(prhs[3], len);
    zono->setCenter(center);
}

void MZonotope::setGenerators(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MZonotope - setGenerators: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - setGenerators: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    const mwSize *gen_dims;
    int gen_rows, gen_cols;

    gen_dims = mxGetDimensions(prhs[3]);
    gen_cols = (int) gen_dims[1];
    gen_rows = (int) gen_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[3], gen_rows, gen_cols);

    zono->setGenerators(matrix);
}

void MZonotope::addGenerators(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - addGenerators: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MZonotope - addGenerators: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - addGenerators: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    const mwSize *gen_dims;
    int gen_rows, gen_cols;

    gen_dims = mxGetDimensions(prhs[3]);
    gen_cols = (int) gen_dims[1];
    gen_rows = (int) gen_dims[0];
    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[3], gen_rows, gen_cols);

    bool added = zono->addGenerators(matrix);

    mxLogical ans = false;
    if (added) {
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);
}

void MZonotope::center(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - center: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - center: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - center: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    hypro::vector_t<double> cen = zono->center();

    plhs[0] = mxCreateDoubleMatrix(cen.rows(), 1, mxREAL);
    ObjectHandle::convert2Matlab(cen, plhs[0], cen.rows(), 1);
}

void MZonotope::generators(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - generators: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - generators: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - generators: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);

    hypro::matrix_t<double> mat = zono->generators();

    int rows = mat.rows();
    int cols = mat.cols();

    plhs[0] = mxCreateDoubleMatrix(rows, cols, mxREAL);
    ObjectHandle::convert2Matlab(mat, plhs[0], rows, cols);
}

void MZonotope::order(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - order: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - order: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - order: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    double ord = zono->order();

    // std::cout << "order: " << ord << std::endl;
    plhs[0] = mxCreateDoubleScalar(ord);
}

void MZonotope::removeEmptyGenerators(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MZonotope - removeEmptyGenerators: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - removeEmptyGenerators: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    zono->removeEmptyGenerators();
}

void MZonotope::uniteEqualVectors(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MZonotope - uniteEqualVectors: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - uniteEqualVectors: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    zono->uniteEqualVectors();
}

void MZonotope::changeDimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - changeDimension: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MZonotope - changeDimension: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - changeDimension: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    std::size_t new_dim = (std::size_t) mxGetScalar(prhs[3]);
    bool change = zono->changeDimension(new_dim);

    mxLogical ans = false;
    if (change) {
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);
}

void MZonotope::print(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MZonotope::reduceOrder(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MZonotope - reduceOrder: One or more input arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MZonotope - reduceOrder: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    unsigned limit = (unsigned) mxGetScalar(prhs[3]);

    zono->reduceOrder(limit);
}

void MZonotope::computeZonotopeBoundary(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - computeZonotopeBoundary: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - computeZonotopeBoundary: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - computeZonotopeBoundary: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    std::vector<hypro::vector_t<double>> bound = zono->computeZonotopeBoundary();

    // std::cout << "computeZonotopeBoundary" << std::endl;
    // if(bound.size() > 0){
    // for(int i = 0; i < bound.size(); i++){
    // 	hypro::vector_t<double> b = bound[i];
    // 	for(int j = 0; j < bound[0].rows(); j++){
    // 		std::cout << b(j) << ", ";
    // 	}
    // 	std::cout << "" << std::endl;
    // }
    // std::cout << "" << std::endl;
    // }
    if (bound.size() > 0) {
        plhs[0] = mxCreateDoubleMatrix(bound.size(), bound[0].rows(), mxREAL);
        vector2Matlab<>(bound, plhs[0]);
    } else {
        plhs[0] = mxCreateDoubleScalar(0);
    }
}

void MZonotope::intersectHalfspacesMethod(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - intersectHalfspacesMethod: Expecting one output value!");
    if (nrhs < 6) mexErrMsgTxt("MZonotope - intersectHalfspacesMethod: One or more arguments are missing!");
    if (nrhs > 6) mexWarnMsgTxt("MZonotope - intersectHalfspacesMethod: One or more input arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_rows, mat_cols, vec_len;

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    int method = (int) mxGetScalar(prhs[5]);
    mat_cols = (int) mat_dims[1];
    mat_rows = (int) mat_dims[0];
    vec_len = (int) vec_dims[0];

    const hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[3], mat_rows, mat_cols);
    const hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[4], vec_len);

    mexErrMsgTxt("NOT IMPLEMENTED");
    // hypro::Zonotope<double> temp = zono->intersectHalfspaces( matrix, vector, method );
    // plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>( new hypro::Zonotope<double>( temp ) );
}

void MZonotope::intersectMinMax(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - intersectMinMax: Expecting one output value!");
    if (nrhs < 7) mexErrMsgTxt("MZonotope - intersectMinMax: One or more arguments are missing!");
    if (nrhs > 7) mexWarnMsgTxt("MZonotope - intersectMinMax: One or more input arguments were ignored.");

    const mwSize *hs_dim, *mat_dims;
    int len, mat_rows, mat_cols;

    hs_dim = mxGetDimensions(prhs[3]);
    mat_dims = mxGetDimensions(prhs[5]);
    len = hs_dim[0];
    mat_rows = mat_dims[0];
    mat_cols = mat_dims[1];

    hypro::Zonotope<double> *obj = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    double offset = (double) mxGetScalar(prhs[4]);
    hypro::Halfspace<double> hs = ObjectHandle::mHalfspace2Hypro(prhs[3], len, offset);
    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[5], mat_rows, mat_cols);
    int method = (int) mxGetScalar(prhs[6]);

    hypro::Zonotope<double> intersected = obj->intersect(hs, matrix, method);
    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(intersected));
}

void MZonotope::intersectHalfspaceMethod(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - intersectHalfspaceMethod: Expecting one output value!");
    if (nrhs < 6) mexErrMsgTxt("MZonotope - intersectHalfspaceMethod: One or more arguments are missing!");
    if (nrhs > 6) mexWarnMsgTxt("MZonotope - intersectHalfspaceMethod: One or more input arguments were ignored.");

    hypro::Zonotope<double> *zono = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    const mwSize *dims;
    dims = mxGetDimensions(prhs[3]);
    const int rows = (int) dims[0];
    const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro(prhs[3], rows);
    const int offset = (const int) mxGetScalar(prhs[4]);
    const int method = (const int) mxGetScalar(prhs[5]);

    const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(hy_normal, offset);

    hypro::Zonotope<double> temp = zono->intersect(hSpace, method);
    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(temp));
}

void MZonotope::intervalHull(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MZonotope - intervalHull: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MZonotope - intervalHull: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - intervalHull: One or more input arguments were ignored.");

    hypro::Zonotope<double> *obj = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    hypro::Zonotope<double> tmp = obj->intervalHull();
    plhs[0] = convertPtr2Mat<hypro::Zonotope<double>>(new hypro::Zonotope<double>(tmp));
}

void MZonotope::type(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MBox - type: Expecting one output value!");
    std::string ans = "MHyProZonotope";
    plhs[0] = mxCreateString(ans.c_str());
}

void MZonotope::reduceNumberRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MZonotope - reduceNumberRepresentation: One or more input arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MZonotope - reduceNumberRepresentation: One or more input arguments were ignored.");

    hypro::Zonotope<double> *obj = convertMat2Ptr<hypro::Zonotope<double>>(prhs[2]);
    obj->reduceNumberRepresentation();
}

/**
 * @brief The entry point to the HyPro Zonotope class for Matalb.
 * @param nlhs Number of items in plhs
 * @param plhs Array of mxArray pointers to the output variables
 * @param nrhs Number of items in prhs
 * @param prhs Array of mxArray pointers to the input variables
 **/
void MZonotope::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
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
    // if ( cmd == 5 ) {
    // 	new_empty( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    if (cmd == 6) {
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if ( cmd == 8 ) {
    // 	copyObj( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    // if ( cmd == 9 ) {
    // 	matrix( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    // if ( cmd == 10 ) {
    // 	vector( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    if (cmd == 11) {
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        removeRedundancy(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if ( cmd == 13 ) {
    // 	type( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
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
    // if ( cmd == 25 ) {
    // 	intersect( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    if (cmd == 26) {
        unite_single(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if ( cmd == 27 ) {
    // 	unite_vec( nlhs, plhs, nrhs, prhs );
    // 	return;
    // }
    if (cmd == 100) {
        newZonotopeDimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 101) {
        newZonotopeCG(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 102) {
        copyDimensions(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 103) {
        supremum(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 104) {
        emptyAt(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 105) {
        setCenter(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 106) {
        setGenerators(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 107) {
        addGenerators(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 108) {
        center(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 109) {
        generators(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 110) {
        order(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 111) {
        removeEmptyGenerators(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 112) {
        uniteEqualVectors(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 113) {
        changeDimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 114) {
        clear(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 115) {
        print(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 116) {
        reduceOrder(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 117) {
        computeZonotopeBoundary(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 118) {
        intersectHalfspacesMethod(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 119) {
        intersectMinMax(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 120) {
        intervalHull(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 121) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 122) {
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 123) {
        type(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 124) {
        reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 125) {
        intersectHalfspaceMethod(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MZonotope - Command not recognized.");
}
