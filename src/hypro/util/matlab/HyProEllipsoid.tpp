#include "HyProEllipsoid.h"

/**
 * @brief
 **/
 void HyProEllipsoid::ellipsoid_rad(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - ellipsoid: One output expected.");
    double radius = (double) mxGetScalar(prhs[2]);
    size_t dim = (size_t) mxGetScalar(prhs[3]);

    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(new hypro::Ellipsoid<double>(radius, dim));
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::ellipsoid_mat(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - ellipsoid_mat: One output expected.");
    mxArray *m_in_matrix;
    double *in_matrix;
    const mwSize *dims;
    int dimx, dimy;

    m_in_matrix = mxDuplicateArray(prhs[2]);
    dims = mxGetDimensions(prhs[2]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    in_matrix = mxGetPr(m_in_matrix);
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, dimx, dimy);
    
    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(new hypro::Ellipsoid<double>(mat));
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - copy: One output expected.");
    if(nrhs < 1)
        mexErrMsgTxt("HyProEllipsoid - copy: One input is missing.");
    
    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(new hypro::Ellipsoid<double>(*ellipse));
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::deleteEllipsoid(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     destroyObject<hypro::Ellipsoid<double>>(prhs[2]);
     if(nlhs != 0 || nrhs != 3)
        mexWarnMsgTxt("HyProEllipsoid - delete: Unexpected arguments ignored.");
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::matrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - matrix: One output expected.");
    
    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    hypro::matrix_t<double> mat = ellipse->matrix();

    mxArray *m_out;
    double *out;
    m_out = plhs[0] = mxCreateDoubleMatrix(mat.rows(), mat.cols(), mxREAL);
    out = mxGetPr(m_out);

    ObjectHandle::convert2matlab(mat, out, mat.cols(), mat.rows());
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::dimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - dimension: One output expected.");
    if(nrhs < 1)
        mexErrMsgTxt("HyProEllipsoid - dimension: One input is missing.");
    
    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    std::size_t dim = ellipse->dimension();
    plhs[0] = mxCreateDoubleScalar(dim);
    
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::is_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - isEmpty: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("HyProEllipsoid - isEmpty: One input is missing.");

    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    const bool empty = ellipse->empty();
    plhs[0] = mxCreateLogicalScalar(empty);
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::equal(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - equal: One output expected.");
    if(nrhs < 4)
        mexErrMsgTxt("HyProEllipsoid - equal: One or more input arguments are missing.");

    hypro::Ellipsoid<double>* ellipse_1 = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    hypro::Ellipsoid<double>* ellipse_2 = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[3]);

    mxLogical ans = false;
    if(*ellipse_1 == *ellipse_2)
        ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);
 }

 /**
  * @brief
  **/
 void HyProEllipsoid::unequal(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - unequal: One output expected.");
    if(nrhs < 4)
        mexErrMsgTxt("HyProEllipsoid - unequal: One or more input arguments are missing.");

    hypro::Ellipsoid<double>* ellipse_1 = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    hypro::Ellipsoid<double>* ellipse_2 = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[3]);

    mxLogical ans = false;
    if(*ellipse_1 != *ellipse_2)
        ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);
 }
 /**
  * @brief
  **/
 void HyProEllipsoid::ostream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     mexErrMsgTxt("NOT IMPLEMENTED");
 }
 /**
  * @brief
  **/
 void HyProEllipsoid::linearTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("HyProEllipsoid - linearTransformation: One output expected.");
    if(nrhs < 4)
        mexErrMsgTxt("HyProEllipsoid - linearTransformation: One or more input arguments are missing.");

    mxArray *m_in_matrix;
    const mwSize *dims;
    double *in_matrix;
    int dimx, dimy;

    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    m_in_matrix = mxDuplicateArray(prhs[3]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    in_matrix = mxGetPr(m_in_matrix);
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, dimx, dimy);

    hypro::Ellipsoid<double> temp = ellipse->linearTransformation(mat);
    hypro::Ellipsoid<double>* b = new hypro::Ellipsoid<double>(temp);
    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(b);

 }
 /**
  * @brief
  **/
 void HyProEllipsoid::affineTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs < 1)
        mexErrMsgTxt("HyProEllipse - affineTransformation: Expecting one output value!");
    if(nrhs < 5)
        mexErrMsgTxt("HyProEllipse - affineTransformation: One or more arguments are missing!");
    
    mxArray *m_in_matrix, *m_in_vector;
    const mwSize *mat_dims, *vec_dims;
    double *in_matrix, *in_vector;
    int mat_dimx, mat_dimy, vec_len;

    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    m_in_matrix = mxDuplicateArray(prhs[3]);
    m_in_vector = mxDuplicateArray(prhs[4]);
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_len = (int) vec_dims[0];

    in_matrix = mxGetPr(m_in_matrix);
    in_vector = mxGetPr(m_in_vector);

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, mat_dimx, mat_dimy);
    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(in_vector, vec_len);


    hypro::Ellipsoid<double> temp = ellipse->affineTransformation(mat, vec);
    hypro::Ellipsoid<double>* b = new hypro::Ellipsoid<double>(temp);
    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(b);
 }
 /**
  * @brief
  **/
 void HyProEllipsoid::minkowskiSum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs < 1)
        mexErrMsgTxt("HyProEllipsoid - minkowskiSum: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("HyProEllipsoid - minkowskiSum: One or more arguments are missing!");
    
    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);
    hypro::EllipsoidT<double, hypro::Converter<double>>* Ellipsoid_rhs = convertMat2Ptr<hypro::EllipsoidT<double, hypro::Converter<double>>>(prhs[3]);

    hypro::Ellipsoid<double> sum = ellipse->minkowskiSum(*Ellipsoid_rhs);
    hypro::Ellipsoid<double>* b = new hypro::Ellipsoid<double>(sum);
    plhs[0] = convertPtr2Mat<hypro::Ellipsoid<double>>(b);
 }
 /**
  * @brief
  **/
 void HyProEllipsoid::evaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     if(nlhs < 1)
        mexErrMsgTxt("HyProEllipsoid - evaluate: Expecting an output!");
    if(nrhs < 5)
        mexErrMsgTxt("HyProEllipsoid - evaluate: One or more arguments are missing!");
    mxArray *m_in_vector;
    double *in_vector;
    const mwSize *dims_vec;
    int vec_len;
    bool ans;

    hypro::Ellipsoid<double>* ellipse = convertMat2Ptr<hypro::Ellipsoid<double>>(prhs[2]);

    m_in_vector = mxDuplicateArray(prhs[3]);
    const double dir = (double) mxGetScalar(prhs[4]);
    in_vector = mxGetPr(m_in_vector);

    dims_vec = mxGetDimensions(prhs[3]);
    vec_len = (int) dims_vec[0];

    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(in_vector, vec_len);

    if(dir == 0){
        ans = false;
    }else if (dir == 1){
        ans = true;
    }else{
        mexErrMsgTxt("HyProEllipsoid - evaluate: The direction must be either 0 or 1!");
    }
    
    hypro::vector_t<double> vect = ellipse->evaluate(vec);
    mxArray *m_out;
    double *out;
    m_out = plhs[0] = mxCreateDoubleMatrix(vect.rows(), 1, mxREAL);
    out = mxGetPr(m_out);

    ObjectHandle::convert2matlab(vect, out, 1, vect.rows());
 }
 /**
  * @brief
  **/
 void HyProEllipsoid::approxEllipsoidTMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
     mexErrMsgTxt("NOT IMPLEMENTED");
 }


/**
* @brief The entry point to the HyPro Ellipsoid class for Matalb.
* @param nlhs Number of items in plhs 
* @param plhs Array of mxArray pointers to the output variables
* @param nrhs Number of items in prhs
* @param prhs Array of mxArray pointers to the input variables
**/
void HyProEllipsoid::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("HyProEllipsoid - First input should be a command string less than 64 characters long.");
    
    /***************************************************************************
     * Constructors
     **************************************************************************/

    if (!strcmp("ellipsoid", cmd) && nrhs == 2){  
        ellipsoid_rad(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("ellipsoid_mat", cmd) && nrhs == 2){  
        ellipsoid_mat(nlhs, plhs, nrhs, prhs);
        return;
    }

    
    // Check if there is a second input, which should be the class instance handle
    if (nrhs < 2){
        mexErrMsgTxt("Second input should be a Ellipsoid instance handle.");
    }
    
    if(!strcmp("copy", cmd)){
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("delete", cmd)) {
        deleteEllipsoid(nlhs, plhs, nrhs, prhs);
        return;
    }
    
    /***************************************************************************
     * Getters & setters
     **************************************************************************/ 

    if(!strcmp("is_empty", cmd)){
        is_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("matrix", cmd)){
        matrix(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("isEqual", cmd)){
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

    if(!strcmp("unequal", cmd)){
        unequal(nlhs, plhs, nrhs, prhs);
        return;
    }

    if(!strcmp("ostream", cmd)){
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

 
    mexErrMsgTxt("HyProHyProEllipsoid - Command not recognized.");
}
