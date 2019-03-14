#include "MSupportFunction.h"

/**
 * @brief
 **/
void MSupportFunction::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - new_empty: One output is expected.");

    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>());
}

/**
 * @brief
 **/
void MSupportFunction::new_points(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - new_points: One output is expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - new_points: At least one argument is missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - new_points: One or more input arguments were ignored."); 

    
    mxArray *m_in_points;
    double *in_points;
    const mwSize *dims;
    int dimy, dimx;

    dims = mxGetDimensions(prhs[2]);
    dimy = (const int) dims[0];
    dimx = (const int) dims[1];
    m_in_points = mxDuplicateArray(prhs[2]);

    const std::vector<hypro::Point<double>> points = ObjectHandle::mPointsVector2Hypro(m_in_points, dimx, dimy);
    // plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(points));
}

/**
 * @brief
 **/
void MSupportFunction::new_intervals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - new_intervals: One output is expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - new_intervals: At least one argument is missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - new_intervals: At least one argument were ignored.");
    
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
void MSupportFunction::new_halfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - new_halfspaces: One output is expected.");
    if(nrhs < 4)
        mexErrMsgTxt("MSupportFunction - new_halfspaces: At least one argument is missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MSupportFunction - new_halfspaces: At least one argument were ignored.");
    
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
void MSupportFunction::cleanUp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
   if(nlhs < 1)
        mexErrMsgTxt("MSupportFunction - cleanUp: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - cleanUp: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - cleanUp: At least one argument were ignored.");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    temp->cleanUp();
}

/**
 * @brief
 **/
void MSupportFunction::depth(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MSupportFunction - depth: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - depth: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - depth: At least one argument were ignored.");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    unsigned depth = temp->depth();
    plhs[0] = mxCreateDoubleScalar(depth);
}

/**
 * @brief
 **/
void MSupportFunction::operationCount(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - operationCount: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - operationCount: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - operationCount: At least one argument were ignored.");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    unsigned count = temp->operationCount();
    plhs[0] = mxCreateDoubleScalar(count);
}

/**
 * @brief
 **/
void MSupportFunction::type(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - type: Expecting one output value!");
    std::string ans = "MHyProSupportFunction";
    plhs[0] = mxCreateString(ans.c_str());
}

/**
 * @brief
 **/
void MSupportFunction::contains_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - contains_vector: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MSupportFunction - contains_vector: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MSupportFunction - contains_vector: At least one argument were ignored.");

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
void MSupportFunction::contains_dir(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MSupportFunction - contains_dir: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MSupportFunction - contains_dir: One or more arguments are missing!");
    if(nrhs > 4)    
        mexWarnMsgTxt("MSupportFunction - contains_dir: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
    std::size_t directions = (std::size_t) mxGetScalar(prhs[4]);

    const bool ans = sfct_1->contains(*sfct_2, directions);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void MSupportFunction::scale(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MSupportFunction - scale: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - scale: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - scale: At least one argument were ignored.");

    hypro::SupportFunction<double>* obj = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    const double factor = (double) mxGetScalar(prhs[3]);
    
    hypro::SupportFunction<double> temp = obj->scale(factor);
    hypro::SupportFunction<double>* b = new hypro::SupportFunction<double>(temp);
    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(b);
}

/**
 * @brief
 **/
void MSupportFunction::swap(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MSupportFunction - swap: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MSupportFunction - swap: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* origin = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
    hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[4]);

    origin->swap(*sfct_1, *sfct_2);
}

/**
 * @brief
 **/
void MSupportFunction::forceLinTransReduction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - forcedLinTransReduction: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - forcedLinTransReduction: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    sfct->forceLinTransReduction();
}

/**
 * @brief
 **/
void MSupportFunction::multiplicationsPerEvaluation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // if(nlhs < 1)
    //     mexErrMsgTxt("MSupportFunction - multiplicationsPerEvaluation: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - multiplicationsPerEvaluation: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - multiplicationsPerEvaluation: At least one argument were ignored.");
    
    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    const unsigned ans = sfct->multiplicationsPerEvaluation();
    // double temp = (double) ans;
    // plhs[0] = mxCreateDoubleScalar(temp);
}

/**
 * @brief
 **/
void MSupportFunction::collectProjections(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MSupportFunction - collectProjections: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - collectProjections: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - collectProjections: At least one argument were ignored.");
    
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
void MSupportFunction::evaluateTemplate(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("MSupportFunction - evaluateTemplate: One or more arguments are missing!"); 
    if(nrhs > 5)
        mexWarnMsgTxt("MSupportFunction - evaluateTemplate: At least one argument were ignored.");  

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
void MSupportFunction::reduceNumberRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MSupportFunction - reduceNumberRepresentation: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MSupportFunction - reduceNumberRepresentation: At least one argument were ignored.");
    
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
void MSupportFunction::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MSupportFunction - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if(!strcmp("new_empty", cmd)){
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("new_matrix", cmd)){  
        new_matrix(nlhs, plhs, nrhs ,prhs);
        return;
    }
    if(!strcmp("new_intervals", cmd)){
        new_intervals(nlhs, plhs, nrhs, prhs);
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
    if (!strcmp("new_points", cmd)){
        mexErrMsgTxt("MSupportFunction - new_points is broken!");
        new_points(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("copy", cmd)){
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
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
        intersectHalfspaces(nlhs, plhs, nrhs, prhs);
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
        mexErrMsgTxt("MSupportFunction - unite_objects is broken.");
        // unite_vec(nlhs, plhs, nrhs, prhs);
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
    mexErrMsgTxt("MSupportFunction - Command not recognized.");
}