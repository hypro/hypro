#include "MState.h"

/**
 * @breif
 **/
void MState::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - new_empty: Expecting an output.");
    hypro::State_t<double>* st = new hypro::State_t<double>();
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(st);
}

/**
 * @breif
 **/
void MState::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - copy: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - copy: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - copy: One or more input arguments were ignored.");

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(st);
}

/**
 * @breif
 **/
void MState::new_loc(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - new_loc: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - new_loc: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - new_loc: One or more input arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::State_t<double>* st = new hypro::State_t<double>(loc);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(st);
}

/**
 * @breif
 **/
void MState::new_repr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @breif
 **/
void MState::getLocation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getLocation: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getLocation: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getLocation: One or more input arguments were ignored.");

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::Location<double>* tmp = st->getLocation();
    hypro::Location<double>* loc = new hypro::Location<double>(*tmp);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);
}

/**
 * @breif
 **/
void MState::getNumberSets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getNumberSets: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getNumberSets: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getNumberSets: One or more input arguments were ignored.");

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    std::size_t tmp = st->getNumberSets();
    plhs[0] = mxCreateDoubleScalar(tmp);
}

/**
 * @breif
 **/
void MState::getSet(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @breif
 **/
void MState::getSetType(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getSetType: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getSetType: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getSetType: One or more input arguments were ignored.");

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::representation_name name = st->getSetType();

    std::string ans;
    ObjectHandle::convert2Matlab(name,ans);
    plhs[0] = mxCreateString(ans.c_str());
}

/**
 * @breif
 **/
void MState::getSets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @breif
 **/
void MState::getTypes(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

/**
 * @breif
 **/
void MState::getTimestamp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getTimestamp: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getTimestamp: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getTimestamp: One or more input arguments were ignored.");

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    //const carl::Interval<double> inter = st->getTimestamp();
}

/**
 * @breif
 **/
void MState::isEmpty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MState - isEmpty: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - isEmpty: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - isEmpty: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    bool tmp = st->isEmpty();
    mxLogical ans = tmp;
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @breif
 **/
void MState::setLocation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MState - setLocation: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - setLocation: One or more arguments were ignored.");

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    st->setLocation(loc);
}

/**
 * @breif
 **/
void MState::setSet_untyped(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //?
}

/**
 * @breif
 **/
void MState::setSet(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 6)
        mexErrMsgTxt("MState - setSet: One or more arguments are missing.");
    if(nrhs > 6)
        mexWarnMsgTxt("MState - setSet: One or more arguments were ignored.");
     
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    std::size_t at = mxGetScalar(prhs[5]);

    if(!strcmp("Box", type)){
        hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[3]);
        st->setSet(box, at);
    }else if(!strcmp("ConstraintSet", type)){
        hypro::ConstraintSet<double>* set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
        st->setSet(set, at);
    }else if(!strcmp("SupportFunction", type)){
        hypro::SupportFunction<double>* fct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
        st->setSet(fct, at);
    }else if(!strcmp("TaylorModel", type)){
        mexErrMsgTxt("MState - setSet: Taylor models are not implemented yet.");
    }else{
        mexErrMsgTxt("MState - setSet: Unknown set type.");
    }

}

/**
 * @breif
 **/
void MState::setSetType(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MState - setSetType: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - setSetType: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    hypro::representation_name name = ObjectHandle::mRepresentationName2Hypro(type);
    std::size_t pos = mxGetScalar(prhs[4]);
    st->setSetType(name, pos);
}

/**
 * @breif
 **/
void MState::setTimestamp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MState - setTimestamp: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - setTimestamp: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    // MPQ does not compile - linker
    // const carl::Interval<hypro::tNumber> inter = ObjectHandle::mMPQInterval2Hypro(prhs[3]);
    // st->setTimestamp(inter);
}

/**
 * @breif
 **/
void MState::setSets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MState - setSets: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - setSets: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    const mwSize* dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    if(!strcmp("Box", type)){
        const std::vector<hypro::Box<double>> boxes = objArray2Hypro<hypro::Box<double>>(prhs[3], len);
        // st->setSets(boxes);?

    }else if(!strcmp("ConstraintSet", type)){

    }else if(!strcmp("SupportFunction", type)){

    }else if(!strcmp("TaylorModel", type)){
        mexErrMsgTxt("MState - setSet: Taylor models are not implemented yet.");
    }else{
        mexErrMsgTxt("MState - setSet: Unknown set type.");
    }
}

/**
 * @breif
 **/
void MState::setSetSave(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::setSetDirect(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MState - setSetDirect: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - setSetDirect: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    const mwSize* dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    if(!strcmp("Box", type)){
        const hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[3]);
        st->setSetDirect(*box);
    }else if(!strcmp("ConstraintSet", type)){
        const hypro::ConstraintSet<double>* set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
        st->setSetDirect(*set);
    }else if(!strcmp("SupportFunction", type)){
        const hypro::SupportFunction<double>* fct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
        st->setSetDirect(*fct);
    }else if(!strcmp("TaylorModel", type)){
        mexErrMsgTxt("MState - setSet: Taylor models are not implemented yet.");
    }else{
        mexErrMsgTxt("MState - setSetDirect: Unknown set type.");
    }
}

/**
 * @breif
 **/
void MState::setAndConvertType(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::addTimeToClocks(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::unite(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::satisfies(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 2)
        mexErrMsgTxt("MState - satisfies: Expecting two output values.");
    if(nrhs < 4)
        mexErrMsgTxt("MState - satisfies: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - satisfies: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);

    std::pair<hypro::CONTAINMENT, hypro::State_t<double>> p = st->satisfies(*cond);
    
    std::string cont;
    ObjectHandle::convert2Matlab(p.first, cont);
    plhs[0] = mxCreateString(cont.c_str());
    plhs[1] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(p.second));
}

/**
 * @breif
 **/
void MState::satisfiesHalfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::intersectHalfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::partiallySatisfies(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::applyTimeStep(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::partiallyApplyTimeStep(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - satisfies: Expecting one output.");
    if(nrhs < 6)
        mexErrMsgTxt("MState - satisfies: One or more arguments are missing.");
    if(nrhs > 6)
        mexWarnMsgTxt("MState - satisfies: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    hypro::ConstraintSet<double>* set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
    hypro::tNumber stepSize = (hypro::tNumber) mxGetScalar(prhs[4]);
    std::size_t index = (std::size_t) mxGetScalar(prhs[5]);

    hypro::State_t<double> temp = st->partiallyApplyTimeStep(*set, stepSize, index);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(temp));
}

/**
 * @breif
 **/
void MState::applyTransformation_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::applyTransformation_at(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::applyTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::linearTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - linearTransformation: Expecting one output.");
    if(nrhs < 4)
        mexErrMsgTxt("MState - linearTransformation: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - linearTransformation: One or more arguments were ignored.");
    
    const mwSize* dims;
    int dimx, dimy;
    dims = mxGetDimensions(prhs[3]);
    dimy = dims[0];
    dimx = dims[1];
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);
    
    hypro::State_t<double> temp = st->linearTransformation(mat);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(temp));
}

/**
 * @breif
 **/
void MState::affineTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - affineTransformation: Expecting one output.");
    if(nrhs < 5)
        mexErrMsgTxt("MState - affineTransformation: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - affineTransformation: One or more arguments were ignored.");
    
    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, vec_len;
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    mat_dimy = mat_dims[0];
    mat_dimx = mat_dims[1];
    vec_len = vec_dims[0];

    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], mat_dimx, mat_dimy);
    const hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[4], vec_len);
    
    hypro::State_t<double> temp = st->affineTransformation(mat, vec);
    plhs[0] = convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(temp));
}

/**
 * @breif
 **/
void MState::partialIntervalAssignment(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::partiallyApplyTransformation_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::partiallyApplyTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //Not in reach
}

/**
 * @breif
 **/
void MState::minkowskiSum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - minkowskiSum: Expecting one output.");
    if(nrhs < 4)
        mexErrMsgTxt("MState - minkowskiSum: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - minkowskiSum: One or more arguments were ignored.");
    
    hypro::State_t<double>* st = convertMat2Ptr<hypro::State_t<double>>(prhs[2]);
    const hypro::State_t<double>* rhs = convertMat2Ptr<hypro::State_t<double>>(prhs[3]);

    // hypro::State_t<double>* temp = st->minkowskiSum(*rhs);?
}

/**
 * @breif
 **/
void MState::partiallyMinkowskiSum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::contains(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::vertices(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::project(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::getDimension(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::getDimensionOffset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::getSupremum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::removeRedundancy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::partiallyRemoveRedundancy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::reduceRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::partiallyReduceRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::unequals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
 * @breif
 **/
void MState::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

