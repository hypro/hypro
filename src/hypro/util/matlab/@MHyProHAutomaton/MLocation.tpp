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

    mxArray* m_in_matrix;
    double* in_matrix;
    const mwSize* dims;
    int dimx, dimy;

    m_in_matrix = mxDuplicateArray(prhs[2]);
    in_matrix = mxGetPr(m_in_matrix);
    dims = mxGetDimensions(prhs[2]);
    dimy = dims[0];
    dimx = dims[1];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, dimx, dimy);
    hypro::Location<double>* loc = new hypro::Location<double>(mat);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);
}

/**
 * @brief
 **/
void MLocation::new_mat_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
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
    //TODO
}

/**
 * @brief
 **/
void MLocation::getLinearFlows(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){
    //TODO
}

/**
 * @brief
 **/
void MLocation::getInvariant(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::getTransitions(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::getExternalInput(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

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
    if(nrhs < 4)
         mexErrMsgTxt("MLocation - setFlow: One or more arguments are missing.");
    if(nrhs > 4)
         mexErrMsgTxt("MLocation - setFlow: One or more arguments were ignored.");
    
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    //TODO
}

/**
 * @brief
 **/
void MLocation::setLinearFlow_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    
}

/**
 * @brief
 **/
void MLocation::setInvariant(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::setTransition(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

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

    mxArray* m_in_intervals;
    double* in_intervals;
    const mwSize* dims;
    int dimx, dimy;

    m_in_intervals = mxDuplicateArray(prhs[3]);
    in_intervals = mxGetPr(m_in_intervals);
    dims = mxGetDimensions(prhs[3]);
    dimy = dims[0];
    dimx = dims[1];
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    std::vector<carl::Interval<double>> ints = ObjectHandle::mIntervals2Hypro(in_intervals, dimx, dimy);
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
    
    hypro::Location<double>* obj = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    //const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars
    hypro::Location<double>* rhs = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    const mxArray *m_in_rhsVars, *m_in_thisVars;
    double *in_rhsVars, *in_thisVars;
    const mwSize *dims_rhsVars, *dims_thisVars;
    int len_rhsVars, len_thisVars;

    in_rhsVars = mxGetPr(prhs[4]);

}
// const mwSize *dims; 
// const mxArray *cell;
// const mxArray *cellArray;
// mwIndex jcell;
// double *output;
// cell = prhs[0];
// output = mxGetPr(cell);
// dims = mxGetDimensions(prhs[0]);
// for (jcell=0; jcell<dims[0]; jcell++) {
//   cellElement = mxGetCell(cell,jcell);
//   p = mxGetPr(cellElement)
//   mexPrintf("The content at %d is %g\n", jcell, *p);
/**
 * @brief
 **/
void MLocation::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::decompose(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::less(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::equals(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::unequals(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}

/**
 * @brief
 **/
void MLocation::outstream(int nlhs, mxArray* plhs[], int nrhs , const mxArray* prhs[]){

}



/**
 * @brief
 **/
/**
 * @brief
 **/
void MLocation::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MLocation - First input should be a command string less than 64 characters long.");


    if (!strcmp("new_empty", cmd) && nrhs == 2){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("new_matrix", cmd) && nrhs == 2){  
        new_matrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("new_mat_vec", cmd) && nrhs == 2){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("copy", cmd) && nrhs == 2){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete_loc", cmd) && nrhs == 2){  
        delete_loc(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getNumberFlow", cmd) && nrhs == 2){  
        getNumberFlow(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getLinearFlow", cmd) && nrhs == 2){  
        getLinearFlow(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getLinearFlows", cmd) && nrhs == 2){  
        getLinearFlows(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getInvariant", cmd) && nrhs == 2){  
        getInvariant(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getTransitions", cmd) && nrhs == 2){  
        getTransitions(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getExternalInput", cmd) && nrhs == 2){  
        getExternalInput(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("hasExternalInput", cmd) && nrhs == 2){  
        hasExternalInput(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("hash", cmd) && nrhs == 2){  
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getName", cmd) && nrhs == 2){  
        getName(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("dimension_at", cmd) && nrhs == 2){  
        dimension_at(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setName", cmd) && nrhs == 2){  
        setName(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setLinearFlow", cmd) && nrhs == 2){  
        setLinearFlow(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setLinearFlow_vec", cmd) && nrhs == 2){
        setLinearFlow_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setInvariant", cmd) && nrhs == 2){  
        setInvariant(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setTransition", cmd) && nrhs == 2){  
        setTransition(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("addTransition", cmd) && nrhs == 2){  
        addTransition(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("setExtInput", cmd) && nrhs == 2){  
        setExtInput(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("isComposedOf", cmd) && nrhs == 2){  
        isComposedOf(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("getDotRepresentation", cmd) && nrhs == 2){  
        getDotRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("decompose", cmd) && nrhs == 2){  
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("less", cmd) && nrhs == 2){  
        less(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("equals", cmd) && nrhs == 2){  
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("unequals", cmd) && nrhs == 2){  
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("outstream", cmd) && nrhs == 2){  
        outstream(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MLocation - Command not recognized.");   
}