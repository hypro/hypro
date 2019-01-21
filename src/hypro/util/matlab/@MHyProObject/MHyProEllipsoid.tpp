#include "MHyProEllipsoid.h"

/**
 * @brief
 **/
 void MHyProEllipsoid::ellipsoid_rad(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProEllipsoid - ellipsoid: One output expected.");
    double radius = (double) mxGetScalar(prhs[2]);
    size_t dim = (size_t) mxGetScalar(prhs[3]);

    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(new hypro::Ellipsoid<double>(radius, dim));
 }

 /**
  * @brief
  **/
 void MHyProEllipsoid::evaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs < 1)
        mexErrMsgTxt("MHyProEllipsoid - evaluate: Expecting an output!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProEllipsoid - evaluate: One or more arguments are missing!");

    const mwSize *dims_vec;
    int vec_len;
    bool ans;

    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    const double dir = (double) mxGetScalar(prhs[4]);

    dims_vec = mxGetDimensions(prhs[3]);
    vec_len = (int) dims_vec[0];

    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[3], vec_len);

    if(dir == 0){
        ans = false;
    }else if (dir == 1){
        ans = true;
    }else{
        mexErrMsgTxt("MHyProEllipsoid - evaluate: The direction must be either 0 or 1!");
    }
    
    hypro::vector_t<double> vect = ellipse->evaluate(vec);
    plhs[0] = mxCreateDoubleMatrix(vect.rows(), 1, mxREAL);
    ObjectHandle::convert2Matlab(vect, plhs[0], 1, vect.rows());
 }
 /**
  * @brief
  **/
 void MHyProEllipsoid::approxEllipsoidTMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs < 1)
        mexErrMsgTxt("HyProEllipse - approxEllipsoidTMatrix: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("HyProEllipse - approxEllipsoidTMatrix: One or more arguments are missing!");
    
    const mwSize *dims;
    double *in_matrix;
    int dimx, dimy;

    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);

    hypro::matrix_t<double> out_mat = ellipse->approxEllipsoidTMatrix(mat);
    plhs[0] = mxCreateDoubleMatrix(out_mat.rows(), out_mat.cols(), mxREAL);
    ObjectHandle::convert2Matlab(out_mat, plhs[0], out_mat.cols(), out_mat.rows());
 }

 /**
 * @brief
 **/
 void MHyProEllipsoid::ostream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
     if(nrhs < 3)
        mexErrMsgTxt("MHyProEllipsoid - ostream: One or more input arguments are missing.");

    hypro::Ellipsoid<double>* obj = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    hypro::matrix_t<double> mat = obj->matrix();

    int rows = mat.rows();
    int cols = mat.cols();

    mexPrintf("Matrix: [");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mexPrintf("%f ", mat(i,j));
        }
        mexPrintf("\n");
    }
    mexPrintf("]\n");
 }



/**
* @brief The entry point to the HyPro Ellipsoid class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void MHyProEllipsoid::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MHyProEllipsoid - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if (!strcmp("ellipsoid", cmd) && nrhs == 4){  
        ellipsoid_rad(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("ellipsoid_mat", cmd) && nrhs == 3){  
        new_matrix(nlhs, plhs, nrhs, prhs);
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
    
    /***************************************************************************
     * Getters & setters
     **************************************************************************/ 

    if(!strcmp("isEmpty", cmd)){
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("matrix", cmd)){
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("==", cmd)){
        equal(nlhs, plhs, nrhs, prhs);
        return;
    }


    /**************************************************************************
     * General interface
    **************************************************************************/

    if(!strcmp("dimension", cmd)){
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("matrix", cmd)){
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("!=", cmd)){
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("<<", cmd)){
        ostream(nlhs, plhs, nrhs, prhs);
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

    if(!strcmp("evaluate", cmd)){
        evaluate(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("approxEllipsoidTMatrix", cmd)){
        approxEllipsoidTMatrix(nlhs, plhs, nrhs, prhs);
        return;
    }

 
    mexErrMsgTxt("HyProMHyProEllipsoid - Command not recognized.");
}
