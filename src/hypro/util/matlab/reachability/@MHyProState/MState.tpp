#include "MState.h"

template<class T>
void MState<T>::del_state(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MState - del_label: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - del_label: One or more arguments were ignored.");

    destroyObject<hypro::State<double, T>>(prhs[2]);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - copy: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - copy: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - copy: One or more input arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::State<double, T>>(st);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::getSetType(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getSetType: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getSetType: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getSetType: One or more input arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    hypro::representation_name name = st->getSetType();
    std::string ans;
    ObjectHandle::convert2Matlab(name,ans);
    plhs[0] = mxCreateString(ans.c_str());
}


/**
 * @breif
 **/
template<class T>
void MState<T>::getSets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getSets: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getSets: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getSets: One or more input arguments were ignored.");

    hypro::State<double, T>* init = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    hypro::representation_name name = init->getSetType();
    std::vector<T> states = init->getSets();
    mxArray* m_array_out;
    int len = states.size();
    const mwSize dims[2] = {1,(mwSize) len};
    plhs[0]  = mxCreateCellArray(2,dims);
    objArray2Matlab(states, plhs[0], len);

}


/**
 * @breif
 **/
template<class T>
void MState<T>::getTimestamp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getTimestamp: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getTimestamp: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getTimestamp: One or more input arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    const carl::Interval<double> inter = st->getTimestamp();
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(inter, plhs[0], 1, 2);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::isEmpty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MState - isEmpty: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - isEmpty: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - isEmpty: One or more arguments were ignored.");
    
    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    bool tmp = st->isEmpty();
    mxLogical ans = tmp;
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::vertices(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MState - vertices: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MState - vertices: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - vertices: One or more arguments were ignored.");
    
    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[3]);
    std::vector<hypro::Point<double>> vertices = st->vertices(offset);
    int dimy = vertices.size();
    if (dimy != 0){
        int dimx = vertices[0].dimension();
        plhs[0] = mxCreateDoubleMatrix( dimx, dimy, mxREAL );
        ObjectHandle::convert2Matlab( vertices, plhs[0] );
    }else{
        mexWarnMsgTxt("MState - vertices: The object has no vertices.");
        plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL );
    }
}

/**
 * @breif
 **/
template<class T>
void MState<T>::project(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MState - vertices: Expecting an output.");
    if(nrhs < 5)
        mexErrMsgTxt("MState - vertices: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - vertices: One or more arguments were ignored.");

    mxArray *m_in_dimensions;
    const mwSize *dims;
    double *in_dimensions;
    int len;

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    m_in_dimensions = mxDuplicateArray(prhs[3]);
    dims = mxGetDimensions(prhs[3]);
    len = (int) dims[1]; 
    std::vector<std::size_t> dimensions = ObjectHandle::mSizeVector2Hypro(m_in_dimensions,len);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[4]);

    hypro::State<double, T> new_st = st->project(dimensions, offset);
    plhs[0] = convertPtr2Mat<hypro::State<double, T>>(new hypro::State<double, T>(new_st));
}

/**
 * @breif
 **/
template<class T>
void MState<T>::getDimension(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MState - getDimension: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MState - getDimension: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - getDimension: One or more arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[3]);

    std::size_t dim = st->getDimension(offset);
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::getDimensionOffset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MState - getDimensionOffset: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MState - getDimensionOffset: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - getDimensionOffset: One or more arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    std::size_t offset = (std::size_t) mxGetScalar(prhs[3]);

    std::size_t dim = st->getDimensionOffset(offset);
    plhs[0] = mxCreateDoubleScalar(dim);
}



//----------------------------------------------------------------------

/**
 * @breif
 **/
// void MState<T>::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - new_empty: Expecting an output.");
//     hypro::State<double, T>* st = new hypro::State<double, T>();
//     plhs[0] = convertPtr2Mat<hypro::State<double, T>>(st);
// }


/**
 * @breif
 **/
// void MState<T>::new_loc(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - new_loc: Expecting an output.");
//     if(nrhs < 3)
//         mexErrMsgTxt("MState - new_loc: One or more input arguments are missing.");
//     if(nrhs > 3)
//         mexWarnMsgTxt("MState - new_loc: One or more input arguments were ignored.");

//     hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
//     hypro::State<double, T>* st = new hypro::State<double, T>(loc);
//     plhs[0] = convertPtr2Mat<hypro::State<double, T>>(st);
// }

// /**
//  * @breif
//  **/
// void MState<T>::new_repr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //TODO
// }

/**
 * @breif
 **/
template<class T>
void MState<T>::getLocation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getLocation: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getLocation: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getLocation: One or more input arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    const hypro::Location<double>* tmp = st->getLocation();
    hypro::Location<double>* loc = new hypro::Location<double>(*tmp);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::getNumberSets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MState - getNumberSets: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MState - getNumberSets: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MState - getNumberSets: One or more input arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    std::size_t tmp = st->getNumberSets();
    plhs[0] = mxCreateDoubleScalar(tmp);
}

// /**
//  * @breif
//  **/
// void MState<T>::getSet(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - getNumberSets: Expecting an output.");
//     if(nrhs < 3)
//         mexErrMsgTxt("MState - getNumberSets: One or more input arguments are missing.");
//     if(nrhs > 3)
//         mexWarnMsgTxt("MState - getNumberSets: One or more input arguments were ignored.");


// }




// /**
//  * @breif
//  **/
// void MState<T>::getTypes(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //TODO
// }





/**
 * @breif
 **/
template<class T>
void MState<T>::setLocation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MState - setLocation: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - setLocation: One or more arguments were ignored.");

    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    st->setLocation(loc);
}

// /**
//  * @breif
//  **/
// void MState<T>::setSet_untyped(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //?
// }

// /**
//  * @breif
//  **/
// // void MState<T>::setSet(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
// //     if(nrhs < 6)
// //         mexErrMsgTxt("MState - setSet: One or more arguments are missing.");
// //     if(nrhs > 6)
// //         mexWarnMsgTxt("MState - setSet: One or more arguments were ignored.");
     
// //     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
// //     char type[64];
// //     mxGetString(prhs[4], type, sizeof(type));
// //     std::size_t at = mxGetScalar(prhs[5]);

// //     if(!strcmp("Box", type)){
// //         hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[3]);
// //         st->setSet(box, at);
// //     }else if(!strcmp("ConstraintSet", type)){
// //         hypro::ConstraintSet<double>* set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
// //         st->setSet(set, at);
// //     }else if(!strcmp("SupportFunction", type)){
// //         hypro::SupportFunction<double>* fct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
// //         st->setSet(fct, at);
// //     }else if(!strcmp("TaylorModel", type)){
// //         mexErrMsgTxt("MState - setSet: Taylor models are not implemented yet.");
// //     }else{
// //         mexErrMsgTxt("MState - setSet: Unknown set type.");
// //     }

// // }

/**
 * @breif
 **/
template<class T>
void MState<T>::setSetType(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MState - setSetType: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - setSetType: One or more arguments were ignored.");
    
    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    char type[64];
    mxGetString(prhs[4], type, sizeof(type));
    hypro::representation_name name = ObjectHandle::mRepresentationName2Hypro(type);
    std::size_t pos = mxGetScalar(prhs[4]);
    st->setSetType(name, pos);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::setTimestamp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MState - setTimestamp: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MState - setTimestamp: One or more arguments were ignored.");
    
    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
    // MPQ does not compile - linker
    // const carl::Interval<hypro::tNumber> inter = ObjectHandle::mMPQInterval2Hypro(prhs[3]);
    // st->setTimestamp(inter);
}

/**
 * @breif
 **/
template<class T>
void MState<T>::setSets(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MState - setSets: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - setSets: One or more arguments were ignored.");
    
    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
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

// /**
//  * @breif
//  **/
// void MState<T>::setSetSave(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

/**
 * @breif
 **/
template<class T>
void MState<T>::setSetDirect(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MState - setSetDirect: One or more arguments are missing.");
    if(nrhs > 5)
        mexWarnMsgTxt("MState - setSetDirect: One or more arguments were ignored.");
    
    hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
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

// /**
//  * @breif
//  **/
// void MState<T>::setAndConvertType(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::addTimeToClocks(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::unite(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::satisfies(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 2)
//         mexErrMsgTxt("MState - satisfies: Expecting two output values.");
//     if(nrhs < 4)
//         mexErrMsgTxt("MState - satisfies: One or more arguments are missing.");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MState - satisfies: One or more arguments were ignored.");
    
//     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
//     const hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);

//     std::pair<hypro::CONTAINMENT, hypro::State<double, T>> p = st->satisfies(*cond);
    
//     std::string cont;
//     ObjectHandle::convert2Matlab(p.first, cont);
//     plhs[0] = mxCreateString(cont.c_str());
//     plhs[1] = convertPtr2Mat<hypro::State<double, T>>(new hypro::State<double, T>(p.second));
// }

// /**
//  * @breif
//  **/
// void MState<T>::satisfiesHalfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::intersectHalfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::partiallySatisfies(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::applyTimeStep(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// // void MState<T>::partiallyApplyTimeStep(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
// //     if(nlhs != 1)
// //         mexErrMsgTxt("MState - satisfies: Expecting one output.");
// //     if(nrhs < 6)
// //         mexErrMsgTxt("MState - satisfies: One or more arguments are missing.");
// //     if(nrhs > 6)
// //         mexWarnMsgTxt("MState - satisfies: One or more arguments were ignored.");
    
// //     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
// //     hypro::ConstraintSet<double>* set = convertMat2Ptr<hypro::ConstraintSet<double>>(prhs[3]);
// //     hypro::tNumber stepSize = (hypro::tNumber) mxGetScalar(prhs[4]);
// //     std::size_t index = (std::size_t) mxGetScalar(prhs[5]);

// //     hypro::State<double, T> temp = st->partiallyApplyTimeStep(*set, stepSize, index);
// //     plhs[0] = convertPtr2Mat<hypro::State<double, T>>(new hypro::State<double, T>(temp));
// // }

// /**
//  * @breif
//  **/
// void MState<T>::applyTransformation_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::applyTransformation_at(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::applyTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

/**
 * @breif
 **/
// void MState<T>::linearTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - linearTransformation: Expecting one output.");
//     if(nrhs < 4)
//         mexErrMsgTxt("MState - linearTransformation: One or more arguments are missing.");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MState - linearTransformation: One or more arguments were ignored.");
    
//     const mwSize* dims;
//     int dimx, dimy;
//     dims = mxGetDimensions(prhs[3]);
//     dimy = dims[0];
//     dimx = dims[1];
//     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
//     const hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);
    
//     hypro::State<double, T> temp = st->linearTransformation(mat);
//     plhs[0] = convertPtr2Mat<hypro::State<double, T>>(new hypro::State<double, T>(temp));
// }

/**
 * @breif
 **/
// void MState<T>::affineTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - affineTransformation: Expecting one output.");
//     if(nrhs < 5)
//         mexErrMsgTxt("MState - affineTransformation: One or more arguments are missing.");
//     if(nrhs > 5)
//         mexWarnMsgTxt("MState - affineTransformation: One or more arguments were ignored.");
    
//     const mwSize *mat_dims, *vec_dims;
//     int mat_dimx, mat_dimy, vec_len;
//     mat_dims = mxGetDimensions(prhs[3]);
//     vec_dims = mxGetDimensions(prhs[4]);
//     mat_dimy = mat_dims[0];
//     mat_dimx = mat_dims[1];
//     vec_len = vec_dims[0];

//     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
//     const hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], mat_dimx, mat_dimy);
//     const hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[4], vec_len);
    
//     hypro::State<double, T> temp = st->affineTransformation(mat, vec);
//     plhs[0] = convertPtr2Mat<hypro::State<double, T>>(new hypro::State<double, T>(temp));
// }

// /**
//  * @breif
//  **/
// void MState<T>::partialIntervalAssignment(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::partiallyApplyTransformation_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

// /**
//  * @breif
//  **/
// void MState<T>::partiallyApplyTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     //Not in reach
// }

/**
 * @breif
 **/
// void MState<T>::minkowskiSum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - minkowskiSum: Expecting one output.");
//     if(nrhs < 4)
//         mexErrMsgTxt("MState - minkowskiSum: One or more arguments are missing.");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MState - minkowskiSum: One or more arguments were ignored.");
    
//     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
//     const hypro::State<double, T>* rhs = convertMat2Ptr<hypro::State<double, T>>(prhs[3]);

//     hypro::State<double, T> temp = st->minkowskiSum(*rhs);
// }

/**
 * @breif
 **/
// void MState<T>::partiallyMinkowskiSum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MState - partiallyMinkowskiSum: Expecting one output.");
//     if(nrhs < 4)
//         mexErrMsgTxt("MState - partiallyMinkowskiSum: One or more arguments are missing.");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MState - partiallyMinkowskiSum: One or more arguments were ignored.");
    
//     hypro::State<double, T>* st = convertMat2Ptr<hypro::State<double, T>>(prhs[2]);
//     hypro::State<double, T>* rhs = convertMat2HandlePtr<hypro::State<double, T>>(prhs[3]);
// }

// /**
//  * @breif
//  **/
// void MState<T>::contains(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }


// /**
//  * @breif
//  **/
// void MState<T>::getSupremum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::removeRedundancy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::partiallyRemoveRedundancy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::reduceRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::partiallyReduceRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

// /**
//  * @breif
//  **/
// void MState<T>::unequals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

// }

/**
 * @breif
 **/
template<class T>
void MState<T>::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MState - First input should be a command string less than 64 characters long.");

    if(!strcmp("getSetType", cmd)){
        getSetType(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("copy", cmd)){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)){  
        del_state(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getSets", cmd)){  
        getSets(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getTimestamp", cmd)){  
        getTimestamp(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("isempty", cmd)){  
        isEmpty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("vertices", cmd)){  
        vertices(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("project", cmd)){  
        project(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getDimension", cmd)){  
        getDimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getDimensionOffset", cmd)){  
        getDimensionOffset(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MState - Command not recognized.");
}

