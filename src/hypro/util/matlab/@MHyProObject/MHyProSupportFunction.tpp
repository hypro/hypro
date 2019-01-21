#include "MHyProSupportFunction.h"

// /**
//  * @brief
//  **/
// void MHyProSupportFunction::new_points(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MHyProSupportFunction - new_points: One output is expected.");
//     if(nrhs < 3)
//         mexErrMsgTxt("MHyProSupportFunction - new_points: At least one argument is missing.");
    
//     mxArray *m_in_points;
//     double *in_points;
//     const mwSize *dims;
//     int dimy;

//     dims = mxGetDimensions(prhs[2]);
//     dimy = (const int) dims[0];
//     m_in_points = mxDuplicateArray(prhs[2]);
//     in_points = mxGetPr(m_in_points);

//     const std::vector<hypro::Point<double>> points = ObjectHandle::mPointsVector2Hypro(in_points, dimy);
//     plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(points));
// }

/**
 * @brief
 **/
void MHyProSupportFunction::new_intervals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProSupportFunction - new_intervals: One output is expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - new_intervals: At least one argument is missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - new_intervals: At least one argument were ignored.");
    
    const mwSize *dims;
    int dimy;
    dims = mxGetDimensions(prhs[2]);
    dimy = (const int) dims[0];

    std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro(prhs[2], 2, dimy);
    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(intervals));
}

/**
 * @brief
 **/
void MHyProSupportFunction::new_halfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProSupportFunction - new_halfspaces: One output is expected.");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProSupportFunction - new_halfspaces: At least one argument is missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProSupportFunction - new_halfspaces: At least one argument were ignored.");
    
    mxArray *m_in_matrix, *m_in_vector;
    double *in_matrix, *in_vector;
    const mwSize *mat_dims, *vec_dims;
    int mat_dimy, mat_dimx, vec_len;

    mat_dims = mxGetDimensions(prhs[2]);
    vec_dims = mxGetDimensions(prhs[3]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_len = (int) vec_dims[0];
    m_in_matrix = mxDuplicateArray(prhs[2]);
    m_in_vector = mxDuplicateArray(prhs[3]);

    std::vector<hypro::Halfspace<double>> halfspaces = ObjectHandle::mHalfspaces2Hypro(m_in_matrix, m_in_vector, mat_dimx, mat_dimy, vec_len);
    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(halfspaces));
}
/**
 * @brief
 **/
void MHyProSupportFunction::cleanUp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
   if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - cleanUp: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - cleanUp: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - cleanUp: At least one argument were ignored.");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    temp->cleanUp();
}

/**
 * @brief
 **/
void MHyProSupportFunction::depth(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - depth: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - depth: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - depth: At least one argument were ignored.");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    unsigned depth = temp->depth();
    plhs[0] = mxCreateDoubleScalar(depth);
}

/**
 * @brief
 **/
void MHyProSupportFunction::operationCount(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - operationCount: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - operationCount: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - operationCount: At least one argument were ignored.");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    unsigned count = temp->operationCount();
    plhs[0] = mxCreateDoubleScalar(count);
}

/**
 * @brief
 **/
void MHyProSupportFunction::type(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){
    mexPrintf("MHyProSupportFunction");
}

/**
 * @brief
 **/
void MHyProSupportFunction::contains_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - contains_vector: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProSupportFunction - contains_vector: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProSupportFunction - contains_vector: At least one argument were ignored.");

    const mwSize *dims;
    int vec_len;
    
    hypro::SupportFunction<double>* obj = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    vec_len = (const int) dims[0];

    const hypro::vector_t<double> hy_vector = ObjectHandle::mVector2Hypro(prhs[3], vec_len);
    const bool ans = obj->contains(hy_vector);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MHyProSupportFunction::contains_dir(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - contains_dir: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProSupportFunction - contains_dir: One or more arguments are missing!");
    if(nrhs > 4)    
        mexWarnMsgTxt("MHyProSupportFunction - contains_dir: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
    std::size_t directions = (std::size_t) mxGetScalar(prhs[4]);

    const bool ans = sfct_1->contains(*sfct_2, directions);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MHyProSupportFunction::scale(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - scale: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - scale: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - scale: At least one argument were ignored.");

    hypro::SupportFunction<double>* obj = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    const double factor = (double) mxGetScalar(prhs[3]);
    
    hypro::SupportFunction<double> temp = obj->scale(factor);
    hypro::SupportFunction<double>* b = new hypro::SupportFunction<double>(temp);
    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(b);
}

/**
 * @brief
 **/
void MHyProSupportFunction::swap(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MHyProSupportFunction - swap: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProSupportFunction - swap: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* origin = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
    hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[4]);

    origin->swap(*sfct_1, *sfct_2);
}

/**
 * @brief
 **/
void MHyProSupportFunction::forceLinTransReduction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - forcedLinTransReduction: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - forcedLinTransReduction: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    sfct->forceLinTransReduction();
}

/**
 * @brief
 **/
void MHyProSupportFunction::multiplicationsPerEvaluation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // if(nlhs < 1)
    //     mexErrMsgTxt("MHyProSupportFunction - multiplicationsPerEvaluation: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - multiplicationsPerEvaluation: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - multiplicationsPerEvaluation: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    const unsigned ans = sfct->multiplicationsPerEvaluation();
    // double temp = (double) ans;
    // plhs[0] = mxCreateDoubleScalar(temp);
}

/**
 * @brief
 **/
void MHyProSupportFunction::collectProjections(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - collectProjections: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - collectProjections: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - collectProjections: At least one argument were ignored.");
    
    mxArray *m_out;
    double *out;

    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    std::vector<std::size_t> vec = sfct->collectProjections();

    m_out = plhs[0] = mxCreateDoubleMatrix(vec.size(), 1, mxREAL);
    out = mxGetPr(m_out);
    for(int i = 0; i < vec.size(); i++){
        out[i] = vec[i];
    }
}

/**
 * @brief
 **/
void MHyProSupportFunction::evaluateTemplate(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MHyProSupportFunction - evaluateTemplate: One or more arguments are missing!"); 
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProSupportFunction - evaluateTemplate: At least one argument were ignored.");  

    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    std::size_t directions = (std::size_t) mxGetScalar(prhs[3]);
    const int force = (const int) mxGetScalar(prhs[4]);
    bool f = false;
    if(force == 1)
        f = true;
    sfct->evaluateTemplate(directions, f);
}

/**
 * @brief
 **/
void MHyProSupportFunction::reduceNumberRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProSupportFunction - reduceNumberRepresentation: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProSupportFunction - reduceNumberRepresentation: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProSupportFunction - reduceNumberRepresentation: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    temp->reduceNumberRepresentation();
}


/**
* @brief The entry point to the HyPro Support Function class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void MHyProSupportFunction::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MHyProSupportFunction - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if (!strcmp("new_matrix", cmd)){  
        new_matrix(nlhs, plhs, nrhs ,prhs);
        return;
    }

    if (!strcmp("new_mat_vec", cmd)){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("new_halfspaces", cmd)){
        new_halfspaces(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    // if (!strcmp("new_points", cmd)){
    //     new_points(nlhs, plhs, nrhs, prhs);
    //     return;
    // }
    
    if(!strcmp("copy", cmd)){
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete", cmd)) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    /***************************************************************************
     * Getters & setters
     **************************************************************************/ 

    if(!strcmp("matrix", cmd)){
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("vector", cmd)){
        vector(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("isEmpty", cmd)){
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("vertices", cmd)){
        vertices(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("supremum", cmd)){
        supremum(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("==", cmd)){
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("<<", cmd)){
        ostream(nlhs, plhs, nrhs, prhs);
        return;
    }

    /**************************************************************************
     * General interface
    **************************************************************************/
    
    if(!strcmp("dimension", cmd)){
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("removeRedundancy", cmd)){
        removeRedundancy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("size", cmd)){
        size(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("type", cmd)){
        type(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("reduceNumberRepresentation", cmd)){
        reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("satisfiesHalfspace", cmd)){
        satisfiesHalfspace(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("satisfiesHalfspaces", cmd)){
        satisfiesHalfspaces(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("project", cmd)){
        project(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("linearTransformation", cmd)){
        linearTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("affineTransformation", cmd)){
        affineTransformation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("minkowskiSum", cmd)){
        minkowskiSum(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intersect", cmd)){
        intersect(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intersectHalfspace", cmd)){
        intersectHalfspace(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intersectHalfspaces", cmd)){
        reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("contains_point", cmd)){
        contains_point(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("contains_set", cmd)){
        contains_object(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("contains_vec", cmd)){
        contains_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("unite", cmd)){
        unite_single(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("unite_objects", cmd)){
        unite_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("reduceRepresentation", cmd)){
        reduceRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("cleanUp", cmd)){
        cleanUp(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("depth", cmd)){
        depth(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("operationCount", cmd)){
        operationCount(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("contains_dir", cmd)){
        contains_dir(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("*", cmd)){
        scale(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("swap", cmd)){
        swap(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("forceLinTransReduction", cmd)){
        forceLinTransReduction(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("multiplicationsPerEvaluation", cmd)){
        multiplicationsPerEvaluation(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("collectProjections", cmd)){
        collectProjections(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("evaluateTemplate", cmd)){
        evaluateTemplate(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MHyProSupportFunction - Command not recognized.");
}