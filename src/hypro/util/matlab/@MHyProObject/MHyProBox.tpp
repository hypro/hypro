#include "MHyProBox.h"

/**
 * @brief Creates an empty box
 **/
void MHyProBox::emptyBox(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProBox - new_empty: One output expected.");
    if(nrhs > 2)
        mexWarnMsgTxt("MHyProBox - new_empty: One or more input arguments were ignored.");

    plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>);
}

/**
 * @brief Creates a box from a single interval
 **/
void MHyProBox::boxFromSingleInterval(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProBox - new_interval: One output expected."); 
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - new_interval: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - new_interval: One or more input arguments were ignored."); 
 
    const mwSize *dims;
    int dimx, dimy;
    dims = mxGetDimensions(prhs[2]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    carl::Interval<double> inter = ObjectHandle::mInterval2Hypro(prhs[2]);
    hypro::Box<double>* box = new hypro::Box<double>(inter);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Creates a box from a list of intervals
 **/
void MHyProBox::boxFromIntervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProBox - new_intervals: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - new_intervals: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - new_intervals: One or more input arguments were ignored."); 
 
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
void MHyProBox::boxFromPoints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProBox - new_points: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - new_points: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - new_points: One or more input arguments were ignored."); 

    const mwSize *dims;
    int dimy, dimx, numdims;

    dims = mxGetDimensions(prhs[2]);
    numdims = mxGetNumberOfDimensions(prhs[2]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    if(numdims > 2 || dimy != 2 || dimx != 2){
        mexErrMsgTxt("MHyProBox - new_points: You have to input a 2x2-matrix containing the min. and max. point!");
    }

    std::pair<hypro::Point<double>, hypro::Point<double>> pair = ObjectHandle::mPointPair2Hypro(prhs[2]);
    hypro::Box<double>* box = new hypro::Box<double>(pair);
    plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
    return;
}

/**
 * @brief Returns setting of a box
 **/
void MHyProBox::test(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    
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
void MHyProBox::empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - empty: Expecting one output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - empty: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - new_interval: One or more input arguments were ignored."); 

    const mwSize *dims;
    int dimy, dimx;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    size_t in = (size_t) mxGetScalar(prhs[3]);
    hypro::Box<double> temp = box->Empty(in);
    hypro::Box<double>* b = new hypro::Box<double>(temp);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
}

/**
 * @brief Returns the intervals from which the box is constructed
 **/
void MHyProBox::intervals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - intervals: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - intervals: One or more input arguments are missing."); 
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - intervals: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::vector<carl::Interval<double>> intervals = box->intervals();

    const int dimy = intervals.size();
    const int dimx = 2;
    plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
    vector2Matlab(intervals, plhs[0]);
}

/**
 * @brief Extends a box by a further interval
 **/
void MHyProBox::insert(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MHyProBox - insert: One argument is missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProBox - insert: One or more input arguments were ignored."); 
    
    const mwSize *dims;
    double *in_box, *in_interval, *out;
    int dimy, dimx, numdims;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);

    dims = mxGetDimensions(prhs[3]);
    numdims = mxGetNumberOfDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    if(numdims > 2 || dimy != 1 || dimx != 2){
        mexErrMsgTxt("MHyProBox - insert: You have to input a 1x2-matrix!");
    }

    carl::Interval<double> interval = ObjectHandle::mInterval2Hypro(prhs[3]);
    box->insert(interval);
}

/**
 * @brief Getter for the limiting points.
 **/
void MHyProBox::limits(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - limits: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - limits: One argument is missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - limits: One or more input arguments were ignored."); 
 
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::pair<hypro::Point<double>, hypro::Point<double>> p = box->limits();
    
    plhs[0] = mxCreateDoubleMatrix(2, 2, mxREAL);
    pair2Matlab(p, plhs[0], 1, 2);
}

/**
 * @brief Getter for the hyperplanar representation of the current box.
 **/
void MHyProBox::constraints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 2)
        mexErrMsgTxt("MHyProBox - constraints: Expecting two output values!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - constraints: One argument is missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - constraints: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const std::vector<hypro::Halfspace<double>> hSpaces = box->constraints();

    const int dimx = hSpaces[0].dimension();
    const int dimy = hSpaces.size();

    plhs[0] = mxCreateDoubleMatrix(dimy,dimx, mxREAL);
    plhs[1] = mxCreateDoubleMatrix(dimy,1,mxREAL);
    vector2Matlab(hSpaces, plhs[0], plhs[1]);
}

/**
 * @brief Getter for an interval representation of one specific dimension.
 **/
void MHyProBox::interval(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - interval: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProBox - interval: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProBox - interval: One or more input arguments were ignored."); 

    size_t dim = (size_t) mxGetScalar(prhs[3]);
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const carl::Interval<double> inter = box->interval(dim);
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(inter, plhs[0], 2, 1);
}

/**
 * @brief Getter for an interval representation of one specific dimension.
 **/
void MHyProBox::at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - at: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProBox - at: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProBox - at: One or more input arguments were ignored.");  

    size_t dim = (size_t) mxGetScalar(prhs[3]);
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const carl::Interval<double> inter = box->at(dim);

    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(inter, plhs[0], 2, 1);
}

/**
 * @brief Determines if the current box is symmetric.
 **/
void MHyProBox::is_symmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - isSymmetric: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - isSymmetric: One argument missing!");
    if(nrhs > 3)
         mexWarnMsgTxt("MHyProBox - isSymmetric: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const bool empty = box->isSymmetric();
    mxLogical a = empty;
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief Getter for the maximal point.
 **/
void MHyProBox::max(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - max: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - max: One argument missing!");
    if(nrhs > 3)
         mexWarnMsgTxt("MHyProBox - max: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    hypro::Point<double> m = box->max();
    int dim = m.rawCoordinates().size();
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(m, plhs[0], 1, dim);
}

/**
 * @brief Getter for the minimal point.
 **/
void MHyProBox::min(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - min: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - min: One argument missing!");
    if(nrhs > 3)
         mexWarnMsgTxt("MHyProBox - min: One or more input arguments were ignored."); 
    
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    hypro::Point<double> m = box->min();
    int dim = m.rawCoordinates().size();
    plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    ObjectHandle::convert2Matlab(m, plhs[0], 1, dim);
}


/**
 * @brief Evaluation function (convex linear optimization).
 **/
void MHyProBox::evaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - evaluate: Expecting an output!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProBox - evaluate: One or more arguments are missing!");
    if(nrhs > 5)
         mexWarnMsgTxt("MHyProBox - evaluate: One or more input arguments were ignored."); 

    const mwSize *dims_vec;
    int vec_len;
    bool ans;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);

    const double dir = (double) mxGetScalar(prhs[4]);
    dims_vec = mxGetDimensions(prhs[3]);
    vec_len = (int) dims_vec[0];

    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[3], vec_len);

    if(dir == 0){
        ans = false;
    }else if (dir == 1){
        ans = true;
    }else{
        mexErrMsgTxt("MHyProBox - evaluate: The direction must be either 0 or 1!");
    }
    
    hypro::EvaluationResult<double> eval = box->evaluate(vec, ans);
    plhs[0] = convertPtr2Mat<hypro::EvaluationResult<double>>(&eval);
}

/**
 * @brief Multi-evaluation function (convex linear optimization).
 **/
void MHyProBox::multiEvaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - multiEvaluate: Expecting an output!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProBox - multiEvaluate: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProBox - multiEvaluate: One or more input arguments were ignored."); 
 
    const mwSize *dims;
    int dimx, dimy;
    bool ans;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    const double dir = (double) mxGetScalar(prhs[4]);

    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);

    if(dir == 0){
        ans = false;
    }else if (dir == 1){
        ans = true;
    }else{
        mexErrMsgTxt("MHyProBox - evaluate: The direction must be either 0 or 1!");
    }
    
    //Does this make sense?
    // std::vector<hypro::EvaluationResult<double>> eval = box->multiEvaluate(mat,ans);
    // plhs[0] = convertPtr2Mat<std::vector<hypro::EvaluationResult<double>>>(&eval);
}

/**
 * @brief Outstream operator.
 **/
void MHyProBox::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - <<: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - <<: One or more input arguments were ignored."); 

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
void MHyProBox::box_size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - size: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - size: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - size: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    std::size_t dim = box->size();
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @brief Returns type of representation.
 **/
void MHyProBox::type(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexPrintf("Box");
}

/**
 * @brief Makes a symmetric box from the current box.
 **/
void MHyProBox::makeSymmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MHyProBox - makeSymmetric: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProBox - makeSymmetric: One or more input arguments were ignored."); 

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    box->makeSymmetric();
}

/**
 * @brief Performs a Minkowski decomposition of two boxes.
 **/
void MHyProBox::minkowskiDecomposition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("MHyProBox - minkowskiDecomposition: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProBox - minkowskiDecomposition: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProBox - minkowskiDecomposition: One or more input arguments were ignored."); 
    
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
void MHyProBox::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MHyProBox - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if (!strcmp("new_empty", cmd) && nrhs == 2){  
        emptyBox(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    // Check if there is a second input, which should be the class instance handle
    if (nrhs < 2){
        mexErrMsgTxt("Second input should be a Box instance handle.");
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

    if(!strcmp("new_matrix",cmd)){
        //boxFromMatrix(nlhs, plhs, nrhs, prhs);
        new_mat_vec(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete", cmd)) {
        // deleteBox(nlhs, nrhs, prhs);
        deleteObject(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    /***************************************************************************
     * Getters & setters
     **************************************************************************/ 

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

    if(!strcmp("evaluate", cmd)){
        evaluate(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("multiEvaluate", cmd)){
        multiEvaluate(nlhs, plhs, nrhs, prhs);
        return;
    }

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

    if(!strcmp("clear", cmd)){
        clear(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MMHyProBox - Command not recognized.");
}
