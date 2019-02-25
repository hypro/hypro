#include "MHyProGeometricObject.h"

/**
 * @brief Constructs a HyPro geometric object using a matrix
 **/
template<typename T>
void MHyProGeometricObject<T>::new_matrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - new_matrix: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - new_matrix: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - new_matrix: One or more input arguments were ignored.");

    const mwSize *mat_dims;
    int mat_dimx, mat_dimy;

    mat_dims = mxGetDimensions(prhs[2]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_dimx, mat_dimy);
    plhs[0] = convertPtr2Mat<T>(new T(matrix));
}

/**
 * @brief Constructs a HyPro geometric object using a vector
 **/
template<typename T>
void MHyProGeometricObject<T>::new_vector(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - new_vector: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - new_vector: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - new_vector: One or more input arguments were ignored.");

    double *in_vector;
    const mwSize *vec_dims;
    int mat_dimx, mat_dimy, vec_dimy;
    vec_dims = mxGetDimensions(prhs[3]);
    vec_dimy = (int) vec_dims[0];

    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], vec_dimy);

    T* temp = new T(vector);
    plhs[0] = convertPtr2Mat<T>(temp);
}

/**
 * @brief Copy constructor
 **/
template<typename T>
void MHyProGeometricObject<T>::copyObj(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - copyObj: One output expected.");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - copyObj: One argument is missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - copyObj: One or more input arguments were ignored.");

    T *origin = convertMat2Ptr<T>(prhs[2]);
    plhs[0] = convertPtr2Mat<T>(new T(*origin));
}

/**
 * @brief Constructs a HyPro geometric object using a matrix and a vector
 **/
template<typename T>
void MHyProGeometricObject<T>::new_mat_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - new_mat_vec: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - new_mat_vec: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - new_mat_vec: One or more input arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, vec_dimy;

    mat_dims = mxGetDimensions(prhs[2]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_dims = mxGetDimensions(prhs[3]);
    vec_dimy = (int) vec_dims[0];

    hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(prhs[2], mat_dimx, mat_dimy);
    hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(prhs[3], vec_dimy);
    plhs[0] =  convertPtr2Mat<T>(new T(matrix, vector));
}


/**
 * @brief Destructor
 **/
template<class T>
void MHyProGeometricObject<T>::deleteObject(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - deleteObject: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - deleteObject: One or more arguments were ignored.");
    
    destroyObject<T>(prhs[2]);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::matrix(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - matrix: One output expected!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - matrix: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - matrix: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    hypro::matrix_t<double> mat = temp->matrix();
    plhs[0] = mxCreateDoubleMatrix(mat.rows(), mat.cols(), mxREAL);
    ObjectHandle::convert2Matlab(mat, plhs[0], mat.cols(), mat.rows());
    /* TEST */
    // hypro::matrix_t<double> m(3,2);
    // m << 1,2,3,4,5,6;
    // mexPrintf("Matrix:\nrows: %d cols: %d\n", m.rows(), m.cols());
    // plhs[0] = mxCreateDoubleMatrix(m.rows(), m.cols(), mxREAL);
    // ObjectHandle::convert2Matlab(m, plhs[0], m.cols(), m.rows());
    
}

/**
 * @brief Scaling operator.
 **/
template<class T>
void MHyProGeometricObject<T>::scale(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - scale: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - scale: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - scale: One or more input arguments were ignored.");
        
    T* obj = convertMat2Ptr<T>(prhs[2]);
    const double factor = (double) mxGetScalar(prhs[3]);
    T temp = obj->operator*(factor);
    T* b = new T(temp);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::vector(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - vector: One output expected!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - vector: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - vector: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    hypro::vector_t<double> vec = temp->vector();
    // mexPrintf("Vector:\nrows: %d\n",vec.size());
    plhs[0] = mxCreateDoubleMatrix(vec.size(), 1, mxREAL);
    ObjectHandle::convert2Matlab(vec, plhs[0], 1, vec.size());
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::is_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - isEmpty: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - isEmpty: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - isEmpty: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    const bool empty = temp->empty();
    plhs[0] = mxCreateLogicalScalar(empty);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::vertices(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - vertices: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - vertices: One argument is missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - vertices: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    std::vector<hypro::Point<double>> vertices = temp->vertices();
    int dimy = vertices.size();
    int dimx = vertices[0].dimension();
    plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
    vector2Matlab<hypro::Point<double>>(vertices, plhs[0]);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::equal(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - ==: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - ==: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - ==: One or more input arguments were ignored.");

    T* set_1 = convertMat2Ptr<T>(prhs[2]);
    T* set_2 = convertMat2Ptr<T>(prhs[3]);
    mxLogical ans = false;
    if(*set_1 == *set_2){
        ans = true;
    }
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::unequal(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - !=: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - !=: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - !=: One or more input arguments were ignored.");

    T* set_1 = convertMat2Ptr<T>(prhs[2]);
    T* set_2 = convertMat2Ptr<T>(prhs[3]);
    mxLogical ans = false;
    if(*set_1 != *set_2){
        ans = true;
    }      
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief Method returning the supremum point of the box, i.e. the maximal point.
 **/
template<class T>
void MHyProGeometricObject<T>::supremum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - supremum: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - supremum: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - supremum: One or more input arguments were ignored.");

    T* obj = convertMat2Ptr<T>(prhs[2]);
    double supremum = obj->supremum();
    plhs[0] = mxCreateDoubleScalar(supremum);
}



/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::dimension(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - dimension: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - dimension: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - dimension: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    std::size_t dim = temp->dimension();
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::removeRedundancy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - removeRedundancy: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - removeRedundancy: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - removeRedundancy: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    temp->removeRedundancy();
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::size(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - size: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - size: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - size: One or more input arguments were ignored.");

    T* temp = convertMat2Ptr<T>(prhs[2]);
    std::size_t dim = temp->size();
    
    plhs[0] = mxCreateDoubleScalar(dim);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::reduceNumberRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - reduceNumberRepresentation: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - reduceNumberRepresentation: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - reduceNumberRepresentation: One or more input arguments were ignored.");
    
    T* temp = convertMat2Ptr<T>(prhs[2]);
    T obj = temp->reduceNumberRepresentation();
    T* b = new T(obj);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::satisfiesHalfspace(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 2)
        mexErrMsgTxt("MHyProGeometricObject - satisfiesHalfspace: Expecting two output values!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProGeometricObject - satisfiesHalfspace: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProGeometricObject - satisfiesHalfspace: One or more input arguments were ignored.");

    mxArray* *out_box, *out_cont;
    const mwSize *dims;
    double *in_normal, *cont;
    int dimx, dimy;

    T* temp = convertMat2Ptr<T>(prhs[2]);
    const int offset = (const int) mxGetScalar(prhs[4]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro(prhs[3], dimy);
    const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(hy_normal,offset);

    std::pair<hypro::CONTAINMENT, T> p = temp->satisfiesHalfspace(hSpace);

    std::string ans = "";
    ObjectHandle::convert2Matlab(p.first, ans);
    out_cont = plhs[0] = mxCreateString(ans.c_str());
    T* b = new T(p.second);
    plhs[1] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::satisfiesHalfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs < 2)
        mexErrMsgTxt("MHyProGeometricObject - satisfiesHalfspaces: Expecting two output values!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProGeometricObject - satisfiesHalfspaces: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProGeometricObject - satisfiesHalfspaces: One or more input arguments were ignored.");

    mxArray *out_box, *out_cont;
    const mwSize *mat_dims, *vec_dims;
    int mat_dimx, mat_dimy, vec_len;

    T* temp = convertMat2Ptr<T>(prhs[2]);
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_len = (int) vec_dims[0];

    const hypro::matrix_t<double> hy_matrix = ObjectHandle::mMatrix2Hypro(prhs[3], mat_dimx, mat_dimy);
    const hypro::vector_t<double> hy_vector = ObjectHandle::mVector2Hypro(prhs[4], vec_len);
    std::pair<hypro::CONTAINMENT, T> p = temp->satisfiesHalfspaces(hy_matrix, hy_vector);

    std::string ans = "";
    ObjectHandle::convert2Matlab(p.first, ans);
    out_cont = plhs[0] = mxCreateString(ans.c_str());
    T* b = new T(p.second);
    plhs[1] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::project(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - project: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - project: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - project: One or more input arguments were ignored.");
    
    mxArray *m_in_dimensions;
    const mwSize *dims;
    double *in_dimensions;
    int dimy;

    T* box = convertMat2Ptr<T>(prhs[2]);
    m_in_dimensions = mxDuplicateArray(prhs[3]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];

    // in_dimensions = mxGetPr(m_in_dimensions);

    std::vector<std::size_t> hy_dimensions = ObjectHandle::mSizeVector2Hypro(m_in_dimensions,dimy);

    T temp = box->project(hy_dimensions);
    T* b = new T(temp);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::linearTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - linearTransformation: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - linearTransformation: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - lineaTransformation: One or more input arguments were ignored.");
    
    const mwSize *dims;
    double *in_matrix;
    int dimx, dimy;

    T* obj = convertMat2Ptr<T>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];
    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], dimx, dimy);

    T temp = obj->linearTransformation(mat);
    T* b = new T(temp);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::affineTransformation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - affineTransformation: Expecting one output value!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProGeometricObject - affineTransformation: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProGeometricObject - affineTransformation: One or more input arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    double *in_matrix, *in_vector;
    int mat_dimx, mat_dimy, vec_len;

    T* obj = convertMat2Ptr<T>(prhs[2]);
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_len = (int) vec_dims[0];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], mat_dimx, mat_dimy);
    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[4], vec_len);

    T temp = obj->affineTransformation(mat, vec);
    T* b = new T(temp);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::minkowskiSum(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - minkowskiSum: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - minkowskiSum: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - minkowskiSum: One or more input arguments were ignored.");
    
    T* obj = convertMat2Ptr<T>(prhs[2]);
    T* obj_rhs = convertMat2Ptr<T>(prhs[3]);

    T sum = obj->minkowskiSum(*obj_rhs);
    T* b = new T(sum);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::intersect(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - intersect: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - intersect: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - intersect: One or more input arguments were ignored.");
    
    T* box = convertMat2Ptr<T>(prhs[2]);
    T* box_rhs = convertMat2Ptr<T>(prhs[3]);
    //hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box_rhs = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[3]);

    T sum = box->intersect(*box_rhs);
    T* b = new T(sum);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::intersectHalfspace(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - intersectHalfspace: Expecting two output values!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProGeometricObject - intersectHalfspace: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProGeometricObject - intersectHalfspace: One or more input arguments were ignored.");

    mxArray *out_box, *out_cont;
    const mwSize *dims;
    double *in_normal, *cont;
    int dimx, dimy;

    T* obj = convertMat2Ptr<T>(prhs[2]);
    const int offset = (const int) mxGetScalar(prhs[4]);
    dims = mxGetDimensions(prhs[3]);
    dimy = (int) dims[0];
    dimx = (int) dims[1];

    const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro(prhs[3], dimy);
    const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(hy_normal,offset);

    T temp = obj->intersectHalfspace(hSpace);
    T* inter = new T(temp);
    plhs[0] = convertPtr2Mat<T>(inter);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::intersectHalfspaces(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - intersectHalfspaces: Expecting one output value!");
    if(nrhs < 5)
        mexErrMsgTxt("MHyProGeometricObject - intersectHalfspaces: One or more arguments are missing!");
    if(nrhs > 5)
        mexWarnMsgTxt("MHyProGeometricObject - intersectHalfspaces: One or more input arguments were ignored.");

    const mwSize *mat_dims, *vec_dims;
    double *in_matrix, *in_vector;
    int mat_dimx, mat_dimy, vec_len;

    T* obj = convertMat2Ptr<T>(prhs[2]);
    mat_dims = mxGetDimensions(prhs[3]);
    vec_dims = mxGetDimensions(prhs[4]);
    mat_dimy = (int) mat_dims[0];
    mat_dimx = (int) mat_dims[1];
    vec_len = (int) vec_dims[0];

    hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(prhs[3], mat_dimx, mat_dimy);
    hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(prhs[4], vec_len);

    T temp = obj->intersectHalfspaces(mat, vec);
    T* b = new T(temp);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::contains_point(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - contains_point: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - contains_point: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - contains_point: One or more input arguments were ignored.");

    const mwSize *dims;
    int point_len;
    T* obj = convertMat2Ptr<T>(prhs[2]);
    dims = mxGetDimensions(prhs[3]);
    point_len = (int) dims[0];
    hypro::Point<double> hy_point = ObjectHandle::mPoint2Hypro(prhs[3], point_len);
    const bool ans = obj->contains(hy_point);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::contains_object(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - contains_box: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - contains_box: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - contains_box: One or more input arguments were ignored.");

    T* obj = convertMat2Ptr<T>(prhs[2]);
    T* obj_arg = convertMat2Ptr<T>(prhs[3]);

    const bool ans = obj->contains(*obj_arg);
    plhs[0] = mxCreateLogicalScalar(ans);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::unite_single(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MHyProGeometricObject - unite_single: Expecting one output value!");
    if(nrhs < 4)
        mexErrMsgTxt("MHyProGeometricObject - unite_single: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MHyProGeometricObject - unite_single: One or more input arguments were ignored.");
    
    T* obj = convertMat2Ptr<T>(prhs[3]);
    T* obj_rhs = convertMat2Ptr<T>(prhs[3]);

    T temp = obj->unite(*obj_rhs);
    T* b = new T(temp);
    plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::unite_vec(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // if(nlhs != 1)
    //     mexErrMsgTxt("MHyProGeometricObject - unite_vec: Expecting one output value!");
    // if(nrhs < 4)
    //     mexErrMsgTxt("MHyProGeometricObject - unite_vec: One or more arguments are missing!");
    
    // const mwSize *dims;
    // int dimy;
    // std::vector<T> hy_objs;

    // T* obj = convertMat2Ptr<T>(prhs[2]);
    // in_objs = mxGetPr(m_in_objs);
    // dims = mxGetDimensions(prhs[3]);
    // dimy = dims[0];

    // for(int i = 3; i < nrhs; i++){
    //     T* b = convertMat2Ptr<T>(prhs[i]);
    //     hy_objs.emplace_back(*b);
    // }

    // T united = obj->unite(hy_objs); HERE IS SOMETHING WRONG
    // T* b = new T(united);
    // plhs[0] = convertPtr2Mat<T>(b);
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::reduceRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - reduceRepresentation: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - reduceRepresentation: One or more input arguments were ignored.");

    T* obj = convertMat2Ptr<T>(prhs[2]);
    obj->reduceRepresentation();
}

/**
 * @brief
 **/
template<class T>
void MHyProGeometricObject<T>::clear(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MHyProGeometricObject - clear: One or more arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - clear: One or more input arguments were ignored.");

    T* obj = convertMat2Ptr<T>(prhs[2]);
    obj->clear();
}


/**
 * @brief
 **/
 template<class T>
 void MHyProGeometricObject<T>::ostream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
     if(nrhs < 3)
        mexErrMsgTxt("HyProEllipsoid - ostream: One or more input arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MHyProGeometricObject - ostream: One or more input arguments were ignored.");

    T* obj = convertMat2Ptr<T>(prhs[2]);
    hypro::matrix_t<double> mat = obj->matrix();
    hypro::vector_t<double> vec = obj->vector();

    int rows = mat.rows();
    int cols = mat.cols();

    int len = vec.size();

    mexPrintf("Matrix: [");
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            mexPrintf("%f ", mat(i,j));
        }
        mexPrintf("\n");
    }
    mexPrintf("]\n");

    mexPrintf("Vector: [");
    for(int i = 0; i < len; i++){
        mexPrintf("%f ", vec(i));
    }
    mexPrintf("]\n\n");
 }