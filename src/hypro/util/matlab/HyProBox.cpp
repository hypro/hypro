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
   mexErrMsgTxt("NOT IMPLEMENTED"); 
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
    std::vector<carl::Interval<double>> intervals = ObjectHandle::mPoints2HyProIntervals(in);
    hypro::Box<double>* box = new hypro::Box<double>(intervals);
    plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
}

/**
 * @brief Creates a box from a matrix and a vector
 **/
void boxFromMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1){
        mexErrMsgTxt("new_matrix: Expecting an output!");
    }
    if(nrhs < 3){
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
    if (nlhs < 0)
        mexErrMsgTxt("getSettings: Expecting an output!");
    box->getSettings();
}

/**
 * @brief Returns the intervals from which the box is constructed
 **/
void intervals(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
    if(nlhs < 0){
        mexErrMsgTxt("intervals: Expecting an output!");
    }   
    mxArray* m_out_intervals;
    double* out;
    int dimy, dimx;

    hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

    std::vector<carl::Interval<double>> intervals = box->intervals();

    dimy = intervals.size();
    dimx = 2;
    m_out_intervals = plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
    out = mxGetPr(m_out_intervals);
    ObjectHandle::hyProIntervals2mIntervals(intervals, out, dimx, dimy);
}

/**
 * @brief Extends a box by a further interval
 **/
void insert(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 0){
        mexErrMsgTxt("insert: Expecting an output!");
    }
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

    if (!strcmp("getSettings", cmd)){
        getSettings(nlhs, plhs,  prhs);
        return;
    }

    if(!strcmp("intervals", cmd)){
        intervals(nlhs, plhs, prhs);
        return;
    }

    if(!strcmp("insert",cmd)){
        insert(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    mexErrMsgTxt("Command not recognized");
}






