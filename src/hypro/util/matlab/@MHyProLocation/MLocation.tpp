#include "MLocation.h"

/**
 * @brief
 **/
void MLocation::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLocation - new_empty: Expecting an output.");

    hypro::Location<double>* loc = new hypro::Location<double>();
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);
}

/**
 * @brief
 **/
void MLocation::new_matrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - new_matrix: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - new_matrix: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - new_matrix: One or more arguments were ignored.");

    double* in_matrix;
    const mwSize* dims;
    int dimx, dimy;

    dims = mxGetDimensions(prhs[2]);
    dimy = dims[0];
    dimx = dims[1];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[2], dimx, dimy);
    hypro::Location<double>* loc = new hypro::Location<double>(mat);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);
}

/**
 * @brief
 **/
void MLocation::new_mat_tran_inv(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProLocation - new_mat_tran_inv: Expecting an output!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProLocation - new_mat_tran_inv: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProLocation - new_mat_tran_inv: One or more input arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, vec_dimy;

    mat_dims = mxGetDimensions(prhs[2]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_dims = mxGetDimensions(prhs[3]);
    vec_dimy = (int) vec_dims[1];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_dimx, mat_dimy);
    const std::vector<hypro::Transition<double>> temp = objArray2Hypro<hypro::Transition<double>>(prhs[3], vec_dimy);
    hypro::Condition<double>* inv = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);

    std::vector<std::unique_ptr<hypro::Transition<double>>> transitions;

    for(const auto &elem : temp){
        hypro::Transition<double>* t = new hypro::Transition<double>(elem);
        std::unique_ptr<hypro::Transition<double>> tran = std::make_unique<hypro::Transition<double>>(*t);
        transitions.emplace_back(std::move(tran));
    }
    hypro::Location<double>* loc = new hypro::Location<double>(matrix, std::move(transitions), *inv);
    
    plhs[0] =  convertPtr2Mat<hypro::Location<double>>(loc);
}

/**
 * @brief
 **/
void MLocation::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - copy: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - copy: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - copy: One or more arguments were ignored.");

    hypro::Location<double>* origin = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*origin));
}

/**
 * @brief
 **/
void MLocation::delete_loc(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MLocation - delete_loc: Expecting an output.");
    if(nrhs > 3)
        mexWarnMsgTxt("MLocation - delete_loc: One or more arguments were ignored.");
    destroyObject<hypro::Location<double>>(prhs[2]);
}

/**
 * @brief
 **/
void MLocation::getNumberFlow(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getNumberFlow: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getNumberFlow: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getNumberFlow: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t num = loc->getNumberFlow();
    plhs[0] = mxCreateDoubleScalar(num);
}

/**
 * @brief
 **/
void MLocation::getLinearFlow(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getLinearFlow: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getLinearFlow: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getLinearFlow: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::linearFlow<double> flow = loc->getLinearFlow();
    plhs[0] = convertPtr2Mat<hypro::linearFlow<double>>(new hypro::linearFlow<double>(flow));
}

/**
 * @brief
 **/
void MLocation::getLinearFlows(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getLinearFlows: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getLinearFlows: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getLinearFlows: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<hypro::linearFlow<double>> flows = loc->getLinearFlows();
    int len = flows.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0]  = mxCreateCellArray(2, dims);
    objArray2Matlab(flows, plhs[0], len);
}

/**
 * @brief
 **/
void MLocation::getInvariant(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getInvariant: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getInvariant: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getInvariant: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Condition<double> cond = loc->getInvariant();
    plhs[0] = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>(cond));
}

/**
 * @brief
 **/
void MLocation::getTransitions(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getTransitions: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getTransitions: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getTransitions: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<hypro::Transition<double>*> temp = loc->getTransitions();
    std::vector<hypro::Transition<double>> transitions;

    for(const auto &elem : temp){
        transitions.emplace_back(*elem);
    }

    mxArray* m_array_out;
    int len = temp.size();
    const mwSize dims[2] = {1,(mwSize) len};
    plhs[0]  = mxCreateCellArray(2,dims);
    objArray2Matlab(transitions, plhs[0], len);
}

/**
 * @brief
 **/
void MLocation::getExternalInput(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getExternalInput: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getExternalInput: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getExternalInput: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<carl::Interval<double>> input = loc->getExternalInput();
    plhs[0] = mxCreateDoubleMatrix(input.size(), 2, mxREAL);
    vector2Matlab<carl::Interval<double>>(input, plhs[0]);
}

/**
 * @brief
 **/
void MLocation::hasExternalInput(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - hasExternalInput: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - hasExternalInput: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - hasExternalInput: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    const bool ans = loc->hasExternalInput();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MLocation::hash(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - hash: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - hash: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - hash: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t h = loc->hash();
    plhs[0] = mxCreateDoubleScalar(h);
}

/**
 * @brief
 **/
void MLocation::getName(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - getName: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - getName: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - getName: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::string name = loc->getName();
    plhs[0] = mxCreateString(name.c_str());
}

/**
 * @brief
 **/
void MLocation::dimension(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - dimension: Expecting an output.");
    if(nrhs < 3)
         mexErrMsgTxt("MLocation - dimension: One or more arguments are missing.");
    if(nrhs > 3)
         mexErrMsgTxt("MLocation - dimension: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t h = loc->dimension();
    plhs[0] = mxCreateDoubleScalar(h);
}

/**
 * @brief
 **/
void MLocation::dimension_at(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
         mexErrMsgTxt("MLocation - dimension_at: Expecting an output.");
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - dimension_at: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - dimension_at: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::size_t pos = (std::size_t) mxGetScalar(prhs[3]);
    std::size_t h = loc->dimension(pos);
    plhs[0] = mxCreateDoubleScalar(h);
}

/**
 * @brief
 **/
void MLocation::setName(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - setName: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - setName: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    char* name = mxArrayToString(prhs[3]);
    loc->setName(std::string(name));
}

/**
 * @brief
 **/
void MLocation::setLinearFlow(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nrhs < 5)
         mexErrMsgTxt("MLocation - setFlow: One or more arguments are missing.");
    if(nrhs > 5)
         mexErrMsgTxt("MLocation - setFlow: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    const hypro::linearFlow<double>* flow = convertMat2Ptr<hypro::linearFlow<double>>(prhs[3]);
    std::size_t i = (std::size_t) mxGetScalar(prhs[4]);
    loc->setLinearFlow(*flow, i);
}

/**
 * @brief
 **/
void MLocation::setLinearFlow_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - setFlow_vec: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - setFlow_vec: One or more arguments were ignored.");

    const mwSize* dims;
    int len;
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    const std::vector<hypro::linearFlow<double>> flows = objArray2Hypro<hypro::linearFlow<double>>(prhs[3], len);
    loc->setLinearFlow(flows);
}

/**
 * @brief
 **/
void MLocation::setInvariant(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - setInvariant: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - setInvariant: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    loc->setInvariant(*cond);
}

/**
 * @brief
 **/
void MLocation::setTransition(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - setTransition: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - setTransition: One or more arguments were ignored.");

    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    //TODO
    // hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
    // loc->setTransition(*tran);
}

/**
 * @brief
 **/
void MLocation::addTransition(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - addTransition: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - addTransition: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
    std::unique_ptr<hypro::Transition<double>> tran(new hypro::Transition<double>(*temp));
    loc->addTransition(std::move(tran));
}

/**
 * @brief
 **/
void MLocation::setExtInput(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - setExtInput: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - setExtInput: One or more arguments were ignored.");

    const mwSize* dims;
    int dimx, dimy;

    dims = mxGetDimensions(prhs[3]);
    dimy = dims[0];
    dimx = dims[1];
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<carl::Interval<double>> ints = ObjectHandle::mIntervals2Hypro(prhs[3], dimx, dimy);

    loc->setExtInput(ints);
}

/**
 * @brief
 **/
void MLocation::isComposedOf(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLocation - isComposedOf: Expecting an output!");
    if(nrhs < 6)
        mexErrMsgTxt("MLocation - isComposedOf: One or more arguments are missing!");
    if(nrhs > 6)
        mexWarnMsgTxt("MLocation - isComposedOf: One or more arguments were ignored.");

    const mwSize *rhsvar_dim, *thisvar_dim;
    rhsvar_dim = mxGetDimensions(prhs[4]);
    thisvar_dim = mxGetDimensions(prhs[5]);
    int rhsvar_len = rhsvar_dim[1];
    int thisvar_len = thisvar_dim[1];
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* rhs = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    std::vector<std::string> rhsVars = ObjectHandle::mStringVector2Hypro(prhs[4], rhsvar_len);
    std::vector<std::string> thisVars = ObjectHandle::mStringVector2Hypro(prhs[5], thisvar_len);

    // bool ans = loc->isComposedOf(*rhs, rhsVars, thisVars);
    // plhs[0] = mxCreateLogicalScalar(ans); ---> ?
}

/**
 * @brief THIS IS CORRECT BUT CANNOT BE USED NOW
 **/
// void MLocation::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MLocation - getDotRepresentation: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("MLocation - getDotRepresentation: One or more arguments are missing!");
//     if(nrhs > 4)
//         mexWarnMsgTxt("MLocation - getDotRepresentation: One or more arguments were ignored.");
    
//     const mwSize* dims;
//     int len;
//     dims = mxGetDimensions(prhs[3]);
//     len = dims[0];

//     hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
//     std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro(prhs[3], len);
//     std::string rep = loc->getDotRepresentation(vars);
//     plhs[0] = mxCreateString(rep.c_str());
// }

/**
 * @brief
 **/
void MLocation::decompose(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    //TODO
}

/**
 * @brief
 **/
void MLocation::less(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLocation - less: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MLocation - less: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MLocation - less: One or more arguments were ignored.");
    
    hypro::Location<double>* loc_1 = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* loc_2 = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    mxLogical ans = false;
    if(*loc_1 < *loc_2)
        ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);
    
}

/**
 * @brief
 **/
void MLocation::equals(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLocation - equals: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MLocation - equals: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MLocation - equals: One or more arguments were ignored.");
    
    hypro::Location<double>* loc_1 = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* loc_2 = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    mxLogical ans = false;
    if(*loc_1 == *loc_2)
        ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MLocation::unequals(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MLocation - unequals: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MLocation - unequals: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MLocation - unequals: One or more arguments were ignored.");
    
    hypro::Location<double>* loc_1 = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* loc_2 = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    mxLogical ans = false;
    if(*loc_1 != *loc_2)
        ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MLocation::outstream(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    //TODO
}



/**
 * @brief
 **/
void MLocation::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MLocation - First input should be a command string less than 64 characters long.");


    if (!strcmp("new_empty", cmd)){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_mat", cmd)){  
        new_matrix(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_mat_tran_inv", cmd)){  
        new_mat_tran_inv(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("copy", cmd)){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)){  
        delete_loc(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getNumberFlow", cmd)){  
        getNumberFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getLinearFlow", cmd)){  
        getLinearFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getLinearFlows", cmd)){  
        getLinearFlows(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getInvariant", cmd)){  
        getInvariant(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getTransitions", cmd)){  
        getTransitions(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getExternalInput", cmd)){  
        getExternalInput(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("hasExternalInput", cmd)){  
        hasExternalInput(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("hash", cmd)){  
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("getName", cmd)){  
        getName(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("dimension_at", cmd)){  
        dimension_at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setName", cmd)){  
        setName(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setLinearFlow", cmd)){  
        setLinearFlow(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setLinearFlows", cmd)){
        setLinearFlow_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setInvariant", cmd)){  
        setInvariant(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setTransition", cmd)){  
        setTransition(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("addTransition", cmd)){  
        addTransition(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("setExtInput", cmd)){  
        setExtInput(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("isComposedOf", cmd)){  
        isComposedOf(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if (!strcmp("getDotRepresentation", cmd)){  
    //     getDotRepresentation(nlhs, plhs, nrhs, prhs);
    //     return;
    // }
    if (!strcmp("decompose", cmd)){  
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("less", cmd)){  
        less(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("equals", cmd)){  
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("unequals", cmd)){  
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("outstream", cmd)){  
        outstream(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MLocation - Command not recognized.");   
}