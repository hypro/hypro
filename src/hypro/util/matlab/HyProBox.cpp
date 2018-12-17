#include "ClassHandle.h"
#include "ObjectHandle.h"
#include "../../representations/GeometricObject.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"

/**
 * @brief Creates an empy box
 **/
void emptyBox(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs != 1){
        mexErrMsgTxt("new_empty: One output expected.");
    }
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>);
}

/**
 * @brief Makes a copy of existing box
 **/
void copyBox(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs != 1){
        mexErrMsgTxt("copy: One output expected.");
    }
    hypro::Box<double> *origin = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>(*origin));
}

/**
 * @brief Creates a box from a single interval
 **/
void boxFromSingleInterval(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
   if(nlhs != 1){
        mexErrMsgTxt("new_interval: One output expected."); 
   }
    mxArray *m_in_interval;
    const mwSize *dims;
    double *in;
    int dimx, dimy;

    m_in_interval = mxDuplicateArray(prhs[1]);

    dims = mxGetDimensions(prhs[1]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    if(dimy != 1 || dimx > 2){
        mexErrMsgTxt("new_interval: You have to input a 1x2-matrix!");
    }

    in = mxGetPr(m_in_interval);
    carl::Interval<double> inter = ObjectHandle::mInterval2HyproInterval(in);
    hypro::Box<double>* box = new hypro::Box<double>(inter);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Creates a box from a list of intervals
 **/
void boxFromIntervals(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs != 1){
        mexErrMsgTxt("new_intervals: One output expected.");
    }
    mxArray *m_in_intervals;
    const mwSize *dims;
    double *in;
    int dimx, dimy;

    m_in_intervals = mxDuplicateArray(prhs[1]);

    dims = mxGetDimensions(prhs[1]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    // Ensure that the user entered a list of intervals
    if(dimx != 2){
        mexErrMsgTxt("You have to enter a nx2-matrix! (e.g.:[lower_1 upper_1; lower_2 upper_2])");
    }

    in = mxGetPr(m_in_intervals);
    
    std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2HyProIntervals(in, dimx, dimy);
    hypro::Box<double>* box = new hypro::Box<double>(intervals);
    plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Creates a box from a minimal and maximal point limiting the box
 **/
void boxFromPoints(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs != 1){
        mexErrMsgTxt("new_points: One output expected.");
    }
    mxArray *m_in_points;
    const mwSize *dims;
    double *in;
    int dimy, dimx, numdims;

    m_in_points = mxDuplicateArray(prhs[1]);

    dims = mxGetDimensions(prhs[1]);
    numdims = mxGetNumberOfDimensions(prhs[1]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    if(numdims > 2 || dimy != 2 || dimx != 2){
        mexErrMsgTxt("new_points: You have to input a 2x2-matrix containing the min. and max. point!");
    }

    in = mxGetPr(m_in_points);
    
    std::pair<hypro::Point<double>, hypro::Point<double>> pair = ObjectHandle::mPointPair2HyProPointPair(in);
    hypro::Box<double>* box = new hypro::Box<double>(pair);
    plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
    return;
}

/**
 * @brief Creates a box from a matrix and a vector
 **/
void boxFromMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1){
        mexErrMsgTxt("new_matrix: Expecting an output!");
    }
    if(nrhs != 3){
        mexErrMsgTxt("new_matrix: One or more arguments are missing!");
    }
    mxArray *m_in_matrix, *m_in_vector;
    double *in_matrix, *in_vector;
    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, vec_dimy;

    m_in_matrix = mxDuplicateArray(prhs[1]);
    m_in_vector = mxDuplicateArray(prhs[2]);

    mat_dims = mxGetDimensions(prhs[1]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_dims = mxGetDimensions(prhs[2]);
    vec_dimy = (int) vec_dims[0];
    
    in_matrix = mxGetPr(m_in_matrix);
    in_vector = mxGetPr(m_in_vector);

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2HyProMatrix(in_matrix, mat_dimx, mat_dimy);
    hypro::vector_t<double> vector = ObjectHandle::mVector2HyProVector(in_vector, vec_dimy);

    hypro::Box<double>* box = new hypro::Box<double>(matrix, vector);
    plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Deletes a box
 **/
void deleteBox(int nlhs, int nrhs, const mxArray *prhs[]){
    // Destroy the Box object
    destroyObject<hypro::Box<double>>(prhs[1]);
    // Warn if other commands were ignored
    if (nlhs != 0 || nrhs != 2)
        mexWarnMsgTxt("delete: Unexpected arguments ignored.");
}

/**
 * @brief Returns setting of a box
 **/
void getSettings(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    mexPrintf("getSettings: Not finished yet!");
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    if(nlhs != 1)
        mexErrMsgTxt("getSettings: Expecting an output!");
    box->getSettings();
}

/**
 * @brief Constructs and empty box of required dimension
 **/
void empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
    // if(nrhs < 2)
    //     mexErrMsgTxt("empty: One or more arguments are missing!");

    // mxArray *m_in_dim, *m_out_box;
    // double *out;
    // const mwSize *dims;
    // int dimy, dimx;

    // size_t in = (size_t) mxGetScalar(prhs[1]);

    // hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    // box->Empty(in);
    // //plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Returns the intervals from which the box is constructed
 **/
void intervals(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("intervals: Expecting an output!");
    }   
    mxArray* m_out_intervals;
    double* out;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

    std::vector<carl::Interval<double>> intervals = box->intervals();

    const int dimy = intervals.size();
    const int dimx = 2;
    m_out_intervals = plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
    out = mxGetPr(m_out_intervals);
    vector2mVector(intervals, out, dimx, dimy);
}

/**
 * @brief Extends a box by a further interval
 **/
void insert(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nrhs < 3){
        mexErrMsgTxt("insert: One argument is missing!");
    }
    mxArray *m_in_box, *m_in_interval;
    const mwSize *dims;
    double *in_box, *in_interval, *out;
    int dimy, dimx, numdims;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

    m_in_box = mxDuplicateArray(prhs[1]);
    m_in_interval = mxDuplicateArray(prhs[2]);

    dims = mxGetDimensions(prhs[2]);
    numdims = mxGetNumberOfDimensions(prhs[2]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    if(numdims > 2 || dimy != 1 || dimx != 2){
        mexErrMsgTxt("insert: You have to input a 1x2-matrix!");
    }

    in_box = mxGetPr(m_in_box);
    in_interval = mxGetPr(m_in_interval);
    carl::Interval<double> interval = ObjectHandle::mInterval2HyproInterval(in_interval);
    box->insert(interval);
}

/**
 * @brief
 **/
void limits(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("limits: Expecting output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("limits: One argument is missing!");
    }
    
    mxArray* m_out;
    double* out;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    std::pair<hypro::Point<double>, hypro::Point<double>> p = box->limits();
    
    m_out = plhs[0] = mxCreateDoubleMatrix(2, 2, mxREAL);
    out = mxGetPr(m_out);
    //ObjectHandle::hyProPointPair2mPointPair(p, out);
    pair2matlab(p, out, 1, 2);

}

/**
 * @brief
 **/
void constraints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void interval(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("interval: Expecting an output!");
    }
    if(nrhs < 3){
        mexErrMsgTxt("interval: One or more arguments are missing!");
    }

    mxArray *m_in_dim, *m_out;
    double *in, *out;

    size_t dim = (size_t) mxGetScalar(prhs[2]);

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    const carl::Interval<double> inter = box->interval(dim);
    m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    out = mxGetPr(m_out);
    ObjectHandle::convert2matlab(inter, out, 2, 1);

}

/**
 * @brief
 **/
void at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("at: Expecting an output!");
    }
    if(nrhs < 3){
        mexErrMsgTxt("at: One or more arguments are missing!");
    }

    mxArray *m_in_dim, *m_out;
    double* out;

    size_t dim = (size_t) mxGetScalar(prhs[2]);
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    const carl::Interval<double> inter = box->at(dim);

    m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    out = mxGetPr(m_out);
    ObjectHandle::convert2matlab(inter, out, 2, 1);
}

/**
 * @brief
 **/
void is_empty_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("isEmpty: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("isEmpty: One argument missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    const bool empty = box->empty();
    mxLogical a = empty;
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief
 **/
void is_symmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("isSymmetric: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("isSymmetric: One argument missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    const bool empty = box->isSymmetric();
    mxLogical a = empty;
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief
 **/
void max(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("max: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("max: One argument missing!");
    }
    mxArray *m_out;
    double* out;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    hypro::Point<double> m = box->max();
    int dim = m.rawCoordinates().size();
    m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    out = mxGetPr(m_out);
    //ObjectHandle::hyProPoint2mPoint(m, out, dim);
    ObjectHandle::convert2matlab(m, out, 1, dim);
}

/**
 * @brief
 **/
void min(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
   if(nlhs < 1){
        mexErrMsgTxt("min: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("min: One argument missing!");
    }
    mxArray *m_out;
    double* out;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    hypro::Point<double> m = box->min();
    int dim = m.rawCoordinates().size();
    m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
    out = mxGetPr(m_out);
    //ObjectHandle::hyProPoint2mPoint(m, out, dim);
    ObjectHandle::convert2matlab(m, out, 1, dim);
}

/**
 * @brief
 **/
void supremum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("supremum: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("supremum: One argument missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    double supremum = box->supremum();
    plhs[0] = mxCreateDoubleScalar(supremum);
}

/**
 * @brief
 **/
void vertices(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("vertices: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("vertices: One argument missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    std::vector<hypro::Point<double>> vertices = box->vertices();

    mxArray* m_out_vertices;
    double* out;
    int dimy = vertices.size();
    int dimx = vertices[0].dimension();
    m_out_vertices = plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
    out = mxGetPr(m_out_vertices);
    //ObjectHandle::hyProPointsVector2mPointsVector(vertices, out);
    vector2mVector<hypro::Point<double>>(vertices, out, dimx, dimy);
}

/**
 * @brief
 **/
void evaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void multiEvaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("==: Expecting an output!");
    }
    if(nrhs < 3){
        mexErrMsgTxt("==: One or more arguments are missing!");
    }
    hypro::Box<double>* box_1 = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    hypro::Box<double>* box_2 = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    mxLogical ans = false;
    if(*box_1 == *box_2){
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void unequal(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("!=: Expecting an output!");
    }
    if(nrhs < 3){
        mexErrMsgTxt("!=: One or more arguments are missing!");
    }
    hypro::Box<double>* box_1 = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    hypro::Box<double>* box_2 = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
    mxLogical ans = false;
    if(*box_1 != *box_2){
        ans = true;
    }      
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
void multiply(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
    if(nlhs < 1){
        mexErrMsgTxt("*: Expecting an output!");
    }
    if(nrhs < 3){
        mexErrMsgTxt("*: One or more arguments are missing!");
    }
    hypro::Box<double>* box_1 = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    const double factor = (double) mxGetScalar(prhs[2]);
    // hypro::BoxT<double> box_2 =  box_1->operator*(factor);
    // plhs[0] = convertPtr2Mat<hypro::Box<double>>(&box_2);
}

/**
 * @brief
 **/
void outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}


/**
 * @brief
 **/
void dimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("dimension: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("dimension: One or more arguments are missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    std::size_t dim = box->dimension();
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @brief NOT TESTED FROM HERE ON
 **/
void removeRedundancy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("removeRedundancy: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("removeRedundancy: One or more arguments are missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    box->removeRedundancy();
}

/**
 * @brief
 **/
void box_size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("size: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("size: One or more arguments are missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    std::size_t dim = box->size();
    
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @brief
 **/
void reduceNumberRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void makeSymmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("makeSymmetric: Expecting an output!");
    }
    if(nrhs < 2){
        mexErrMsgTxt("makeSymmetric: One or more arguments are missing!");
    }
    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
    box->makeSymmetric();
}

/**
 * @brief
 **/
void satisfiesHalfspace(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("makeSymmetric: Expecting an output!");
    }
    if(nrhs < 3){
        mexErrMsgTxt("makeSymmetric: One or more arguments are missing!");
    }

    if(nrhs == 2){
        //Make sth.
    }else{
        //Make sth. else
    }

}

/**
 * @brief
 **/
void project(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void linearTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void affineTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void minkowskiSum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void minkowskiDecomposition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void intersect(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void intersectHalfspace(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void intersectHalfspaces(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void contains(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void unite(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void clear_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * @brief
 **/
void print_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    mexErrMsgTxt("NOT IMPLEMENTED");
}

/**
 * The entry point to the HyPro Box class for Matalb
*@param nlhs Number of items in plhs 
*@param plhs Array of mxArray pointers to the output variables
*@param nrhs Number of items in prhs
*@param prhs Array of mxArray pointers to the input variables
*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
	if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
		mexErrMsgTxt("First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
	 * Constructors
	 **************************************************************************/

    if (!strcmp("new_empty", cmd) && nrhs == 1){  
        emptyBox(nlhs, plhs, prhs);
        return;
    }
    
    // Check if there is a second input, which should be the class instance handle
    if (nrhs < 2){
        mexErrMsgTxt("Second input should be a Box instance handle.");
    }
    
    if(!strcmp("copy", cmd)){
        copyBox(nlhs, plhs, prhs);
        return;
    }

    if(!strcmp("new_interval", cmd)){
        boxFromSingleInterval(nlhs, plhs, prhs);
        return;
    }

    if(!strcmp("new_intervals", cmd)){
        boxFromIntervals(nlhs, plhs, prhs);
        return;
    }

    if(!strcmp("new_points",cmd)){
        boxFromPoints(nlhs, plhs, prhs);
        return;
    }

    if(!strcmp("new_matrix",cmd)){
        boxFromMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete", cmd)) {
        deleteBox(nlhs, nrhs, prhs);
        return;
    }
    
    /***************************************************************************
	 * Getters & setters
	 **************************************************************************/ 

    if(!strcmp("getSettings", cmd)){
        getSettings(nlhs, plhs,  prhs);
        return;
    }

    if(!strcmp("empty", cmd)){
        empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("intervals", cmd)){
        intervals(nlhs, plhs, prhs);
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
        is_empty_box(nlhs, plhs, nrhs, prhs);
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
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("!=", cmd)){
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("*", cmd)){
        multiply(nlhs, plhs, nrhs, prhs);
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

    if(!strcmp("contains", cmd)){
        contains(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("unite", cmd)){
        unite(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("clear", cmd)){
        clear_box(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("print", cmd)){
        print_box(nlhs, plhs, nrhs, prhs);
        return;
    }

    
    //TODO make a delete routine for this
    mexErrMsgTxt("Command not recognized");
}






