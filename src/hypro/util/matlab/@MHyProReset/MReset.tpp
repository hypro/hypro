 #include "MReset.h"   

/**
 * @brief
 **/
void MReset::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - new_empty: Expecting an output.");

    hypro::Reset<double>* temp = new hypro::Reset<double>();
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(temp);
}

/**
 * @brief
 **/
void MReset::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - copy: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - copy: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - copy: One or more arguments were ignored.");
    
    hypro::Reset<double>* origin = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(new hypro::Reset<double>(*origin));
}

/**
 * @brief
 **/
void MReset::new_mat_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - new_mat_vec: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MReset - new_mat_vec: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MReset - new_mat_vec: One or more arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, len;

    mat_dims = mxGetDimensions(prhs[2]);
    vec_dims = mxGetDimensions(prhs[3]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    len = (int) vec_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_dimx, mat_dimy);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], len);
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(new hypro::Reset<double>(matrix, vector));
}

/**
 * @brief
 **/
void MReset::new_intervals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - new_intervals: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - new_intervals: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - new_intervals: One or more input arguments were ignored."); 
 
    const mwSize *dims;
    double *in;
    int dimx, dimy;

    dims = mxGetDimensions(prhs[2]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];    
    std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro(prhs[2], dimx, dimy);
    hypro::Reset<double>* reset = new hypro::Reset<double>(intervals);
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(reset);
}

/**
 * @brief
 **/
void MReset::delete_reset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MReset - delete_reset: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - delete_reset: One or more arguments were ignored.");

    destroyObject<hypro::Reset<double>>(prhs[2]);
}

/**
 * @brief
 **/
void MReset::empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - empty: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - empty: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - empty: One or more input arguments were ignored.");

    hypro::Reset<double>* temp = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    const bool empty = temp->empty();
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief
 **/
void MReset::size(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - size: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - size: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - size: One or more input arguments were ignored.");

    hypro::Reset<double>* temp = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t dim = temp->size();
    plhs[0] = mxCreateDoubleScalar(dim);

}

/**
 * @brief
 **/
void MReset::getVector(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getVector: One output expected!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - getVector: One or more arguments are missing!");
    if(nrhs > 3)
        mexErrMsgTxt("MReset - getVector: One or more arguments were ignored!");
    
    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::vector_t<double> vec = res->getVector();
    plhs[0] = mxCreateDoubleMatrix(vec.rows(), 1, mxREAL);
    ObjectHandle::convert2Matlab(vec, plhs[0], 1, vec.rows());
}

/**
 * @brief
 **/
void MReset::getMatrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getMatrix: One output expected!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - getMatrix: One or more arguments are missing!");
    if(nrhs > 3)
        mexErrMsgTxt("MReset - getMatrix: One or more arguments were ignored!");
    
    hypro::Reset<double>* cond = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::matrix_t<double> mat = cond->getMatrix();
    plhs[0] = mxCreateDoubleMatrix(mat.rows(), mat.cols(), mxREAL);
    ObjectHandle::convert2Matlab(mat, plhs[0], mat.cols(), mat.rows());
}

/**
 * @brief
 **/
void MReset::getIntervals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getIntervals: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - getIntervals: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - getIntervals: One or more input arguments were ignored."); 

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::vector<carl::Interval<double>> intervals = res->getIntervals();

    const int dimy = intervals.size();
    const int dimx = 2;
    plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
    vector2Matlab(intervals, plhs[0]);
}

/**
* @brief
**/
void MReset::getAffineReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getAffineReset: One output expected!");
    if(nrhs < 4)
        mexErrMsgTxt("MReset - getAffineReset: One or more arguments are missing!");
    if(nrhs > 4)
        mexErrMsgTxt("MReset - getAffineReset: One or more arguments were ignored!");

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    hypro::AffineTransformation<double> affRes = res->getAffineReset(pos);
    hypro::ConstraintSet<double> cond = affRes.mTransformation;
    plhs[0] = convertPtr2Mat<hypro::ConstraintSet<double>>(new hypro::ConstraintSet<double>(cond));
}

/**
* @brief
**/
void MReset::getAffineResets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getAffineResets: One output expected!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - getAffineResets: One or more arguments are missing!");
    if(nrhs > 3)
        mexErrMsgTxt("MReset - getAffineResets: One or more arguments were ignored!");

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::vector<hypro::AffineTransformation<double>> affRests = res->getAffineResets();
    std::vector<hypro::ConstraintSet<double>> conds(affRests.size());

    for(int i = 0; i < affRests.size(); i++){
        conds[i] = affRests[i].mTransformation;
    }
    int len = conds.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0]  = mxCreateCellArray(2,dims);
    objArray2Matlab<hypro::ConstraintSet<double>>(conds, plhs[0], conds.size());

}

/**
* @brief
**/
void MReset::getIntervalReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getIntervalReset: One output expected!");
    if(nrhs < 4)
        mexErrMsgTxt("MReset - getIntervalReset: One or more arguments are missing!");
    if(nrhs > 4)
        mexErrMsgTxt("MReset - getIntervalReset: One or more arguments were ignored!");

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    hypro::IntervalAssignment<double> intAss = res->getIntervalReset(pos);
    std::vector<carl::Interval<double>> ints = intAss.mIntervals;
    plhs[0] = mxCreateDoubleMatrix(1, ints.size(), mxREAL);
    vector2Matlab<carl::Interval<double>>(ints, plhs[0]); 
}

/**
* @brief
**/
void MReset::getIntervalResets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - getIntervalResets: One output expected!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - getIntervalResets: One or more arguments are missing!");
    if(nrhs > 3)
        mexErrMsgTxt("MReset - getIntervalResets: One or more arguments were ignored!");

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t pos = mxGetScalar(prhs[3]);
    std::vector<hypro::IntervalAssignment<double>> intAss = res->getIntervalResets();
    std::vector<std::vector<carl::Interval<double>>> ints(intAss.size());

    for(int i = 0; i < ints.size(); i++){
        ints[i] = intAss[i].mIntervals;
    }

    plhs[0] = mxCreateDoubleMatrix(1, ints.size(), mxREAL);

    for(int i = 0; i < ints.size(); i++){
        mxArray* elem = mxCreateDoubleMatrix(1, ints[i].size(), mxREAL);
        vector2Matlab<carl::Interval<double>>(ints[i], elem);
        mxSetCell(plhs[0], i, elem);
    }

}

/**
 * @brief
 **/
void MReset::setVector(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MReset - setVector: One or more arguments are missing!");
    if(nrhs > 5)
        mexErrMsgTxt("MReset - setVector: One or more arguments were ignored!");
    
    const mwSize* dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];
    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[3], len);
    std::size_t at = mxGetScalar(prhs[4]);
    res->setVector(vec, at);
}

/**
 * @brief
 **/
void MReset::setMatrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MReset - setMatrix: One or more arguments are missing!");
    if(nrhs > 5)
        mexErrMsgTxt("MReset - setMatrix: One or more arguments were ignored!");
    
    const mwSize* dims;
    int dimx, dimy;
    dims = mxGetDimensions(prhs[3]);
    dimx = dims[0];
    dimy = dims[1];

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);
    std::size_t at = mxGetScalar(prhs[4]);
    res->setMatrix(mat, at);
}

/**
 * @brief
 **/
void MReset::setIntervals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MReset- setIntervals: One or more input arguments are missing."); 
    if(nrhs > 5)
        mexWarnMsgTxt("MReset- setIntervals: One or more input arguments were ignored."); 
 
    const mwSize *dims;
    double *in;
    int dimx, dimy;

    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];    

    hypro::Reset<double>* res = convertmat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro(prhs[3], dimx, dimy);
    std::size_t at = mxGetScalar(prhs[4]);
    res->setIntervals(intervals, at);
}

/**
 * @brief
 **/
void MReset::isIdentity(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - isIdentity: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - isIdentity: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - isIdentity: One or more input arguments were ignored.");

    hypro::Reset<double>* temp = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    const bool ans = temp->isIdentity();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MReset::hash(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - hash: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MReset - hash: One or more input arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MReset - hash: One or more input arguments were ignored!");

    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    std::size_t val = res->hash();
    plhs[0] = mxCreateDoubleScalar(val);
}

/**
 * @brief
 **/
void MReset::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO:
}

/**
 * @brief
 **/
void MReset::combine(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MReset - combine: Expecting an output!");
    if(nrhs < 7)
        mexErrMsgTxt("MReset - combine: One or more input arguments are missing!");
    if(nrhs > 7)
        mexWarnMsgTxt("MReset - combine: One or more input arguments were ignored!");
    
    const mwSize *dims_var, *dims_lhs, *dims_rhs;
    int len_var, len_lhs, len_rhs;

    dims_var = mxGetDimensions(prhs[4]);
    dims_lhs = mxGetDimensions(prhs[5]);
    dims_lhs = mxGetDimensions(prhs[6])
    len_var = dims_var[0];
    len_lhs = dims_lhs[0];
    len_rhs = dims_rhs[0];
    
    hypro::Reset<double>* lhs = convertMat2Ptr<hypro::Reset<double>>(prhs[2]);
    hypro::Reset<double>* rhs = convertMat2Ptr<hypro::Reset<double>>(prhs[3]);
    std::vector<std::string> haVar = ObjectHandle::mStringVector2Hypro(prhs[4], len_var);
    std::vector<std::string> lhsVar = ObjectHandle::mStringVector2Hypro(prhs[5], len_lhs);
    std::vector<std::string> rhsVar = ObjectHandle::mStringVector2Hypro(prhs[6], len_rhs);

    //TODO:
    // hypro::Reset<double>* res = lhs->combine(lhs, rhs, haVar, lhsVar, rhsVar);
    // plhs[0] = convertPtr2Mat<hypro::Reset<double>>(new hypro::Reset<double>(*res));
}

/**
 * @brief
 **/
void MReset::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MReset - First input should be a command string less than 64 characters long.");


    if (!strcmp("new_empty", cmd) && nrhs == 2){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("copy", cmd) && nrhs == 2){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_mat_vec", cmd) && nrhs == 2){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_intervals", cmd) && nrhs == 2){  
        new_intervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd) && nrhs == 2){  
        delete_reset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("empty", cmd) && nrhs == 2){  
        empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("size", cmd) && nrhs == 2){  
        size(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getVector", cmd) && nrhs == 2){  
        getVector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getMatrix", cmd) && nrhs == 2){  
        getMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getIntervals", cmd) && nrhs == 2){  
        getIntervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getAffineReset_at", cmd) && nrhs == 2){  
        getAffineReset_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getAffineResets", cmd) && nrhs == 2){  
        getAffineResets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getIntervalReset_at", cmd) && nrhs == 2){  
        getIntervalReset_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getInvervalResets", cmd) && nrhs == 2){  
        getInvervalResets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setVector", cmd) && nrhs == 2){  
        setVector(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setMatrix", cmd) && nrhs == 2){  
        setMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setIntervals", cmd) && nrhs == 2){  
        setIntervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("isIdentity", cmd) && nrhs == 2){  
        isIdentity(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("hash", cmd) && nrhs == 2){  
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("decompose", cmd) && nrhs == 2){  
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("combine", cmd) && nrhs == 2){  
        combine(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MRest - Command not recognized.");
}
