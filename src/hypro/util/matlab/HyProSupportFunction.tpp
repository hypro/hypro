#include "HyProSupportFunction.h"

// /**
//  * @brief
//  **/
// void HyProSupportFunction::new_points(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("HyProSupportFunction - new_points: One output is expected.");
//     if(nrhs < 3)
//         mexErrMsgTxt("HyProSupportFunction - new_points: At least one argument is missing.");
    
//     mxArray *m_in_points;
//     double *in_points;
//     const mwSize *dims;
//     int dimy;

//     dims = mxGetDimensions(prhs[2]);
//     dimy = (const int) dims[0];
//     m_in_points = mxDuplicateArray(prhs[2]);
//     in_points = mxGetPr(m_in_points);

//     const std::vector<hypro::Point<double>> points = ObjectHandle::mPointsVector2Hypro(in_points, dimy);
//     hypro::SupportFunction<double>* temp = new hypro::SupportFunction<double>(points);
//     plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(temp);

// }

/**
 * @brief
 **/
void HyProSupportFunction::new_intervals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProSupportFunction - new_intervals: One output is expected.");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - new_intervals: At least one argument is missing.");
    
    mxArray *m_in_intervals;
    double *in_intervals;
    const mwSize *dims;
    int dimy;

    dims = mxGetDimensions(prhs[2]);
    dimy = (const int) dims[0];
    m_in_intervals = mxDuplicateArray(prhs[2]);
    in_intervals = mxGetPr(m_in_intervals);

    std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro(in_intervals, 2, dimy);
    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(intervals));
}

/**
 * @brief
 **/
void HyProSupportFunction::new_halfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProSupportFunction - new_halfspaces: One output is expected.");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - new_halfspaces: At least one argument is missing.");
    
    mxArray *m_in_halfspaces;
    double *in_halfspaces;
    const mwSize *dims;
    int dimy;

    dims = mxGetDimensions(prhs[2]);
    dimy = (const int) dims[0];
    m_in_halfspaces = mxDuplicateArray(prhs[2]);
    in_halfspaces = mxGetPr(m_in_halfspaces);

    std::vector<hypro::Halfspace<double>> halfspaces = ObjectHandle::mHalfspaceVector2Hypro(in_halfspaces);
    plhs[0] = convertPtr2Mat<hypro::SupportFunction<double>>(new hypro::SupportFunction<double>(halfspaces));
}
/**
 * @brief
 **/
void HyProSupportFunction::cleanUp(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
   if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - cleanUp: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - cleanUp: One or more arguments are missing!");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    temp->cleanUp();
}

/**
 * @brief
 **/
void HyProSupportFunction::depth(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - depth: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - depth: One or more arguments are missing!");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    unsigned depth = temp->depth();
    plhs[0] = mxCreateDoubleScalar(depth);
}

/**
 * @brief
 **/
void HyProSupportFunction::operationCount(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - operationCount: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - operationCount: One or more arguments are missing!");

    hypro::SupportFunction<double>* temp = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    unsigned count = temp->operationCount();
    plhs[0] = mxCreateDoubleScalar(count);
}

/**
 * @brief
 **/
void HyProSupportFunction::type(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){
    mexPrintf("HyProSupportFunction");
}

/**
 * @brief
 **/
void HyProSupportFunction::contains_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - contains_vector: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("HyProSupportFunction - contains_vector: One or more arguments are missing!");

    mxArray* m_in_vector;
    double* in_vector;
    const mwSize *dims;
    int vec_len;
    
    hypro::SupportFunction<double>* obj = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    m_in_vector = mxDuplicateArray(prhs[3]);
    in_vector = mxGetPr(m_in_vector);
    dims = mxGetDimensions(prhs[3]);
    vec_len = (const int) dims[0];

    const hypro::vector_t<double> hy_vector = ObjectHandle::mVector2Hypro(in_vector, vec_len);
    const bool ans = obj->contains(hy_vector);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void HyProSupportFunction::contains_dir(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - contains_dir: Expecting one output value!");
    if(nrhs < 5)
        mexErrMsgTxt("HyProSupportFunction - contains_dir: One or more arguments are missing!");
    
    hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
    std::size_t directions = (std::size_t) mxGetScalar(prhs[4]);

    const bool ans = sfct_1->contains(*sfct_2, directions);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void HyProSupportFunction::scale(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - scale: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("HyProSupportFunction - scale: One or more arguments are missing!");
    
    mxArray *m_in_point;
    double *in_point;
    const mwSize *dims;
    int len;

    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    m_in_point = mxDuplicateArray(prhs[3]);
    dims = mxGetDimensions(prhs[3]);
    len = dims[0];
    in_point = mxGetPr(m_in_point);
    hypro::Point<double> point = ObjectHandle::mPoint2Hypro(in_point, len);

    const bool ans = sfct->contains(point);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void HyProSupportFunction::swap(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("HyProSupportFunction - swap: One or more arguments are missing!");
    
    hypro::SupportFunction<double>* origin = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    hypro::SupportFunction<double>* sfct_1 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[3]);
    hypro::SupportFunction<double>* sfct_2 = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[4]);

    origin->swap(*sfct_1, *sfct_2);
}

/**
 * @brief
 **/
void HyProSupportFunction::forceLinTransReduction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - forcedLinTransReduction: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - forcedLinTransReduction: One or more arguments are missing!");
    
    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    sfct->forceLinTransReduction();
}

/**
 * @brief
 **/
void HyProSupportFunction::multiplicationsPerEvaluation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - muliplicationsPerEvaluation: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - muliplicationsPerEvaluation: One or more arguments are missing!");
    
    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    const unsigned ans = sfct->multiplicationsPerEvaluation();
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void HyProSupportFunction::collectProjections(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - collectProjections: Expecting one output value!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - collectProjections: One or more arguments are missing!");
    
    mxArray *m_out;
    double *out;

    hypro::SupportFunction<double>* sfct = convertMat2Ptr<hypro::SupportFunction<double>>(prhs[2]);
    std::vector<std::size_t> vec = sfct->collectProjections();

    m_out = plhs[0] = mxCreateDoubleMatrix(vec.size(), 1, mxREAL);
    out = mxGetPr(m_out);
    ObjectHandle::vector2matlab(vec, out, 1, (int)vec.size());
}

/**
 * @brief
 **/
void HyProSupportFunction::evaluateTemplate(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 5)
        mexErrMsgTxt("HyProSupportFunction - evaluateTemplate: One or more arguments are missing!");
    

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
void HyProSupportFunction::reduceNumberRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProSupportFunction - reduceNumberRepresentation: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("HyProSupportFunction - reduceNumberRepresentation: One or more arguments are missing!");
    
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
void HyProSupportFunction::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("HyProConstraintSet - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if (!strcmp("new_matrix", cmd) && nrhs == 2){  
        new_matrix(nlhs, plhs, nrhs ,prhs);
        return;
    }

    if (!strcmp("new_mat_vec", cmd) && nrhs == 2){  
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    // if (!strcmp("new_points", cmd)){
    //     new_points(nlhs, plhs, nrhs, prhs);
    // }


    // Check if there is a second input, which should be the class instance handle
    if (nrhs < 2){
        mexErrMsgTxt("Second input should be a Box instance handle.");
    }
    
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

    mexErrMsgTxt("HyProHyProConstraintSet - Command not recognized.");
}