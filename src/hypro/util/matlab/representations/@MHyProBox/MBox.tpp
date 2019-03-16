#include "MBox.h"

/**
 * @brief Creates an empty box
 **/
void MBox::emptyBox(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - new_empty: One output expected.");
    if(nrhs > 2)
        mexWarnMsgTxt("MBox - new_empty: One or more input arguments were ignored.");

    plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>);
}

/**
 * @brief Creates a box from a single interval
 **/
void MBox::boxFromSingleInterval(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - new_interval: One output expected."); 
    if(nrhs < 3)
        mexErrMsgTxt("MBox - new_interval: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - new_interval: One or more input arguments were ignored."); 
 
    const mwSize *dims;
    int dimx, dimy;
    dims = mxGetDimensions(prhs[2]);
    dimy = (int) dims[1];
    dimx = (int) dims[0];
    mexPrintf("box new_interval - dimx: %d, dimy: %d\n", dimx, dimy);
    carl::Interval<double> inter = ObjectHandle::mInterval2Hypro(prhs[2]);
    hypro::Box<double>* box = new hypro::Box<double>(inter);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Creates a box from a list of intervals
 **/
void MBox::boxFromIntervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - new_intervals: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - new_intervals: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - new_intervals: One or more input arguments were ignored."); 
 
    const mwSize *dims;
    double *in;
    int dimx, dimy;

    dims = mxGetDimensions(prhs[2]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];    
    std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro(prhs[2], dimx, dimy);
    hypro::Box<double>* box = new hypro::Box<double>(intervals);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Creates a box from a minimal and maximal point limiting the box
 **/
void MBox::boxFromPoints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - new_points: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - new_points: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - new_points: One or more input arguments were ignored."); 

    const mwSize *dims;
    int dimy, dimx, numdims;

    dims = mxGetDimensions(prhs[2]);
    numdims = mxGetNumberOfDimensions(prhs[2]);
    dimy = (int) dims[1];
    dimx = (int) dims[0];

    if (dimy != 2)
        mexErrMsgTxt("MBox - new_points: Put two points.");

    std::pair<hypro::Point<double>, hypro::Point<double>> pair = ObjectHandle::mPointPair2Hypro(prhs[2]);
    hypro::Box<double>* box = new hypro::Box<double>(pair);
    plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Returns setting of a box
 **/
void MBox::test(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
    const mwSize* dims;
    dims = mxGetDimensions(prhs[3]);
    const int dimx = dims[1];

    // uint64_t addr = (uint64_t) mxGetScalar(prhs[2]);
    // mexPrintf("Matlab address: %zu -> ",addr);
    // hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    

    const std::vector<hypro::Box<double>> vec = objArray2Hypro<hypro::Box<double>>(prhs[3],dimx);

    mxArray* m_array_out;
    int len = vec.size();
    const mwSize new_dims[2] = {1,(mwSize) len};
    plhs[0]  = mxCreateCellArray(2,new_dims);
    objArray2Matlab(vec, plhs[0], len);
}

/**
 * @brief Method for the construction of an empty box of required dimension.
 **/
void MBox::empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - empty: Expecting one output!");
    if(nrhs < 4)
        mexErrMsgTxt("MBox - empty: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MBox - new_interval: One or more input arguments were ignored."); 

    const mwSize *dims;
    int dimy, dimx;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::size_t in = (std::size_t) mxGetScalar(prhs[3]);
    hypro::Box<double> temp = box->Empty(in);
    hypro::Box<double>* b = new hypro::Box<double>(temp);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
}

/**
 * @brief Returns the intervals from which the box is constructed
 **/
void MBox::intervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - intervals: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - intervals: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - intervals: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::vector<carl::Interval<double>> intervals = box->intervals();

    const int dimx = intervals.size();
    const int dimy = 2;
    mexPrintf("box intervals - dimx: %d, dimy: %d\n", dimx, dimy);
    plhs[0] = mxCreateDoubleMatrix(dimx, dimy, mxREAL);
    vector2Matlab(intervals, plhs[0]);
}

/**
 * @brief Extends a box by a further interval
 **/
void MBox::insert(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MBox - insert: One argument is missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MBox - insert: One or more input arguments were ignored."); 
    
    const mwSize *dims;
    double *in_box, *in_interval, *out;
    int dimy, dimx, numdims;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);

    dims = mxGetDimensions(prhs[3]);
    numdims = mxGetNumberOfDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    if(numdims > 2 || dimy != 1 || dimx != 2){
        mexErrMsgTxt("MBox - insert: You have to input a 1x2-matrix!");
    }

    carl::Interval<double> interval = ObjectHandle::mInterval2Hypro(prhs[3]);
    box->insert(interval);
}

/**
 * @brief Getter for the limiting points.
 **/
void MBox::limits(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - limits: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - limits: One argument is missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - limits: One or more input arguments were ignored."); 
 
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::pair<hypro::Point<double>, hypro::Point<double>> p = box->limits();
    int dim = p.first.dimension();
    plhs[0] = mxCreateDoubleMatrix(dim, 2, mxREAL);
    pair2Matlab(p, plhs[0], dim, 2);
}

/**
 * @brief Getter for the hyperplanar representation of the current box.
 **/
void MBox::constraints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 2)
        mexErrMsgTxt("MBox - constraints: Expecting two output values!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - constraints: One argument is missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - constraints: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const std::vector<hypro::Halfspace<double>> hSpaces = box->constraints();

    const int dimx = hSpaces[0].dimension();
    const int dimy = hSpaces.size();

    plhs[0] = mxCreateDoubleMatrix(dimy,dimx, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(dimy,1,mxREAL);
    vector2Matlab<hypro::Halfspace<double>>(hSpaces, plhs[0], plhs[1]);
}

/**
 * @brief Getter for an interval representation of one specific dimension.
 **/
void MBox::interval(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - interval: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MBox - interval: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MBox - interval: One or more input arguments were ignored."); 

    // Decrease the dimension by 1 because in Matlab everything starts at 1
    size_t dim = (size_t) mxGetScalar(prhs[3]) - 1;
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const carl::Interval<double> inter = box->interval(dim);
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(inter, plhs[0], 1, 2);
}

/**
 * @brief Getter for an interval representation of one specific dimension.
 **/
void MBox::at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - at: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MBox - at: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MBox - at: One or more input arguments were ignored.");  

    size_t dim = (size_t) mxGetScalar(prhs[3]) - 1;
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const carl::Interval<double> inter = box->at(dim);

    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(inter, plhs[0], 1, 2);
}

/**
 * @brief Determines if the current box is symmetric.
 **/
void MBox::is_symmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - isSymmetric: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - isSymmetric: One argument missing!");
    if(nrhs > 3)
         mexWarnMsgTxt("MBox - isSymmetric: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const bool empty = box->isSymmetric();
    mxLogical a = empty;
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief Getter for the maximal point.
 **/
void MBox::max(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - max: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - max: One argument missing!");
    if(nrhs > 3)
         mexWarnMsgTxt("MBox - max: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    hypro::Point<double> m = box->max();
    int dim = m.dimension();
    plhs[0] = mxCreateDoubleMatrix(dim, 1, mxREAL);
    ObjectHandle::convert2Matlab(m, plhs[0], dim, 1);
}

/**
 * @brief Getter for the minimal point.
 **/
void MBox::min(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - min: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - min: One argument missing!");
    if(nrhs > 3)
         mexWarnMsgTxt("MBox - min: One or more input arguments were ignored."); 
    
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    hypro::Point<double> m = box->min();
    int dim = m.dimension();
    plhs[0] = mxCreateDoubleMatrix(dim, 1, mxREAL);
    ObjectHandle::convert2Matlab(m, plhs[0], dim, 1);
}


// /**
//  * @brief Evaluation function (convex linear optimization).
//  **/
// void MBox::evaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MBox - evaluate: Expecting an output!");
//     if(nrhs < 5)
//         mexErrMsgTxt("MBox - evaluate: One or more arguments are missing!");
//     if(nrhs > 5)
//          mexWarnMsgTxt("MBox - evaluate: One or more input arguments were ignored."); 

//     const mwSize *dims_vec;
//     int vec_len;
//     bool ans;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);

//     const double dir = (double) mxGetScalar(prhs[4]);
//     dims_vec = mxGetDimensions(prhs[3]);
//     vec_len = (int) dims_vec[0];

//     hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[3], vec_len);

//     if(dir == 0){
//         ans = false;
//     }else if (dir == 1){
//         ans = true;
//     }else{
//         mexErrMsgTxt("MBox - evaluate: The direction must be either 0 or 1!");
//     }
    
//     hypro::EvaluationResult<double> eval = box->evaluate(vec, ans);
//     plhs[0] = convertPtr2Mat<hypro::EvaluationResult<double>>(&eval);
// }

// *
//  * @brief Multi-evaluation function (convex linear optimization).
//  *
// void MBox::multiEvaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs != 1)
//         mexErrMsgTxt("MBox - multiEvaluate: Expecting an output!");
//     if(nrhs < 5)
//         mexErrMsgTxt("MBox - multiEvaluate: One or more arguments are missing!");
//     if(nrhs > 5)
//         mexWarnMsgTxt("MBox - multiEvaluate: One or more input arguments were ignored."); 
 
//     const mwSize *dims;
//     int dimx, dimy;
//     bool ans;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
//     const double dir = (double) mxGetScalar(prhs[4]);

//     dims = mxGetDimensions(prhs[3]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];

//     hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);

//     if(dir == 0){
//         ans = false;
//     }else if (dir == 1){
//         ans = true;
//     }else{
//         mexErrMsgTxt("MBox - evaluate: The direction must be either 0 or 1!");
//     }
    
//     //Does this make sense?
//     // std::vector<hypro::EvaluationResult<double>> eval = box->multiEvaluate(mat,ans);
//     // plhs[0] = convertPtr2Mat<std::vector<hypro::EvaluationResult<double>>>(&eval);
// }

/**
 * @brief Outstream operator.
 **/
void MBox::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MBox - <<: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - <<: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    if(!box->empty()){
        hypro::Point<double> min_p = box->min();
        hypro::Point<double> max_p = box->max();
        hypro::vector_t<double> vec_min =  min_p.rawCoordinates();
        hypro::vector_t<double> vec_max =  max_p.rawCoordinates();
        mexPrintf("Min: [");
        for(int i = 0; i < vec_min.size(); i++){
            mexPrintf("%f ", vec_min[i]);
        }
        mexPrintf("] Max: [");
        for(int i = 0; i < vec_max.size(); i++){
            mexPrintf("%f ", vec_max[i]);
        }
        mexPrintf("]\n");
    }
}

/**
 * @brief Storage size determination.
 **/
void MBox::box_size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - size: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - size: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - size: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::size_t dim = box->size();
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @brief
 **/
void MBox::type(int nlhs, mxArray* plhs[], int rhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - type: Expecting one output value!");
    std::string ans = "MHyProBox";
    plhs[0] = mxCreateString(ans.c_str());
}

/**
 * @brief Makes a symmetric box from the current box.
 **/
void MBox::makeSymmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - makeSymmetric: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MBox - makeSymmetric: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MBox - makeSymmetric: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    hypro::Box<double> symmBox = box->makeSymmetric();
    plhs[0] = plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>(symmBox));
}

/**
 * @brief Performs a Minkowski decomposition of two boxes.
 **/
void MBox::minkowskiDecomposition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MBox - minkowskiDecomposition: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MBox - minkowskiDecomposition: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MBox - minkowskiDecomposition: One or more input arguments were ignored."); 
    
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box_rhs = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[3]);

    hypro::Box<double> sum = box->minkowskiDecomposition(*box_rhs);
    hypro::Box<double>* b = new hypro::Box<double>(sum);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
}

/**
* @brief The entry point to the HyPro Box class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void MBox::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MBox - First input should be a command string less than 64 characters long.");

    if (!strcmp("new_empty", cmd) && nrhs == 2){  
        emptyBox(nlhs, plhs, nrhs, prhs);
        return;
    } 
    if(!strcmp("copy", cmd)){
        copyObj(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("new_interval", cmd)){
        boxFromSingleInterval(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("new_intervals", cmd)){
        boxFromIntervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("new_points",cmd)){
        boxFromPoints(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("new_mat_vec",cmd)){
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (!strcmp("delete", cmd)) {
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("Test", cmd)){
        test(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("empty", cmd)){
        empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("intervals", cmd)){
        intervals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("insert", cmd)){
        insert(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("limits", cmd)){
        limits(nlhs, plhs, nrhs, prhs);
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
    if(!strcmp("constraints", cmd)){
        constraints(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("interval", cmd)){
        interval(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("at", cmd)){
        at(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("isEmpty", cmd)){
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("isSymmetric", cmd)){
        is_symmetric(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("max", cmd)){
        max(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("min", cmd)){
        min(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("supremum", cmd)){
        supremum(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("vertices", cmd)){
        vertices(nlhs, plhs, nrhs, prhs);
        return;
    }
    // if(!strcmp("evaluate", cmd)){
    //     evaluate(nlhs, plhs, nrhs, prhs);
    //     return;
    // }
    // if(!strcmp("multiEvaluate", cmd)){
    //     multiEvaluate(nlhs, plhs, nrhs, prhs);
    //     return;
    // }
    if(!strcmp("==", cmd)){
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("!=", cmd)){
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("*", cmd)){
        scale(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("<<", cmd)){
        outstream(nlhs, plhs, nrhs, prhs);
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
        box_size(nlhs, plhs, nrhs, prhs);
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
    if(!strcmp("makeSymmetric", cmd)){
        makeSymmetric(nlhs, plhs, nrhs, prhs);
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
    if(!strcmp("minkowskiDecomposition", cmd)){
        minkowskiDecomposition(nlhs, plhs, nrhs, prhs);
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
    if(!strcmp("unite", cmd)){
        unite_single(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("unite_objects", cmd)){
        mexErrMsgTxt("MBox - unite_objects is broken!");
        // unite_vec(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("reduceRepresentation", cmd)){
        reduceRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if(!strcmp("clear", cmd)){
        clear(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MBox - Command not recognized.");
}
