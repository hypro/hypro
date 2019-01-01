// // #include "HyProBox.h"
// // #include "ClassHandle.h"
// // #include "ObjectHandle.h"

// /**
//  * @brief Creates an empty box
//  **/
// void HyProBox::emptyBox(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
//     if(nlhs != 1){
//         mexErrMsgTxt("Box - new_empty: One output expected.");
//     }
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>);
// }

// /**
//  * @brief Makes a copy of existing box
//  **/
// void HyProBox::copyBox(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
//     if(nlhs != 1){
//         mexErrMsgTxt("Box - copy: One output expected.");
//     }
//     hypro::Box<double> *origin = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(new hypro::Box<double>(*origin));
// }

// /**
//  * @brief Creates a box from a single interval
//  **/
// void HyProBox::boxFromSingleInterval(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
// if(nlhs != 1){
//         mexErrMsgTxt("Box - new_interval: One output expected."); 
// }
//     mxArray *m_in_interval;
//     const mwSize *dims;
//     double *in;
//     int dimx, dimy;

//     m_in_interval = mxDuplicateArray(prhs[1]);

//     dims = mxGetDimensions(prhs[1]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];
//     if(dimy != 1 || dimx > 2){
//         mexErrMsgTxt("Box - new_interval: You have to input a 1x2-matrix!");
//     }

//     in = mxGetPr(m_in_interval);
//     carl::Interval<double> inter = ObjectHandle::mInterval2Hypro(in);
//     hypro::Box<double>* box = new hypro::Box<double>(inter);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
// }

// /**
//  * @brief Creates a box from a list of intervals
//  **/
// void HyProBox::boxFromIntervals(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
//     if(nlhs != 1){
//         mexErrMsgTxt("Box - new_intervals: One output expected.");
//     }
//     mxArray *m_in_intervals;
//     const mwSize *dims;
//     double *in;
//     int dimx, dimy;

//     m_in_intervals = mxDuplicateArray(prhs[1]);

//     dims = mxGetDimensions(prhs[1]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];
//     // Ensure that the user entered a list of intervals
//     if(dimx != 2){
//         mexErrMsgTxt("Box - new_intervals: You have to enter a nx2-matrix! (e.g.:[lower_1 upper_1; lower_2 upper_2])");
//     }

//     in = mxGetPr(m_in_intervals);
    
//     std::vector<carl::Interval<double>> intervals = ObjectHandle::mIntervals2Hypro(in, dimx, dimy);
//     hypro::Box<double>* box = new hypro::Box<double>(intervals);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(box);
// }

// /**
//  * @brief Creates a box from a minimal and maximal point limiting the box
//  **/
// void HyProBox::boxFromPoints(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
//     if(nlhs != 1){
//         mexErrMsgTxt("Box - new_points: One output expected.");
//     }
//     mxArray *m_in_points;
//     const mwSize *dims;
//     double *in;
//     int dimy, dimx, numdims;

//     m_in_points = mxDuplicateArray(prhs[1]);

//     dims = mxGetDimensions(prhs[1]);
//     numdims = mxGetNumberOfDimensions(prhs[1]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];
//     if(numdims > 2 || dimy != 2 || dimx != 2){
//         mexErrMsgTxt("Box - new_points: You have to input a 2x2-matrix containing the min. and max. point!");
//     }

//     in = mxGetPr(m_in_points);
    
//     std::pair<hypro::Point<double>, hypro::Point<double>> pair = ObjectHandle::mPointPair2Hypro(in);
//     hypro::Box<double>* box = new hypro::Box<double>(pair);
//     plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
//     return;
// }

// /**
//  * @brief Creates a box from a matrix and a vector
//  **/
// void HyProBox::boxFromMatrix(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs != 1){
//         mexErrMsgTxt("Box - new_matrix: Expecting an output!");
//     }
//     if(nrhs != 3){
//         mexErrMsgTxt("Box - new_matrix: One or more arguments are missing!");
//     }
//     mxArray *m_in_matrix, *m_in_vector;
//     double *in_matrix, *in_vector;
//     const mwSize *mat_dims, *vec_dims;
//     int mat_dimx, mat_dimy, vec_dimy;

//     m_in_matrix = mxDuplicateArray(prhs[1]);
//     m_in_vector = mxDuplicateArray(prhs[2]);

//     mat_dims = mxGetDimensions(prhs[1]);
//     mat_dimy = (int) mat_dims[0];
//     mat_dimx = (int) mat_dims[1];
//     vec_dims = mxGetDimensions(prhs[2]);
//     vec_dimy = (int) vec_dims[0];
    
//     in_matrix = mxGetPr(m_in_matrix);
//     in_vector = mxGetPr(m_in_vector);

//     hypro::matrix_t<double> matrix = ObjectHandle::mMatrix2Hypro(in_matrix, mat_dimx, mat_dimy);
//     hypro::vector_t<double> vector = ObjectHandle::mVector2Hypro(in_vector, vec_dimy);

//     hypro::Box<double>* box = new hypro::Box<double>(matrix, vector);
//     plhs[0] =  convertPtr2Mat<hypro::Box<double>>(box);
// }

// /**
//  * @brief Deletes a box
//  **/
// void HyProBox::deleteBox(int nlhs, int nrhs, const mxArray *prhs[]){
//     // Destroy the Box object
//     destroyObject<hypro::Box<double>>(prhs[1]);
//     // Warn if other commands were ignored
//     if (nlhs != 0 || nrhs != 2)
//         mexWarnMsgTxt("Box - delete: Unexpected arguments ignored.");
// }

// /**
//  * @brief Returns setting of a box
//  **/
// void HyProBox::getSettings(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
//     mexPrintf("getSettings: Not finished yet!");
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     if(nlhs != 1)
//         mexErrMsgTxt("Box - getSettings: Expecting an output!");
//     box->getSettings();
// }

// /**
//  * @brief Method for the construction of an empty box of required dimension.
//  **/
// void HyProBox::empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - empty: Expecting one output!");
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - empty: One or more arguments are missing!");

//     mxArray *m_in_dim, *m_out_box;
//     double *out;
//     const mwSize *dims;
//     int dimy, dimx;

//     size_t in = (size_t) mxGetScalar(prhs[2]);

//     hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[1]);

//     hypro::Box<double> temp = box->Empty(in);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Returns the intervals from which the box is constructed
//  **/
// void HyProBox::intervals(int nlhs, mxArray *plhs[], const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - intervals: Expecting an output!");
//     }   
//     mxArray* m_out_intervals;
//     double* out;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

//     std::vector<carl::Interval<double>> intervals = box->intervals();

//     const int dimy = intervals.size();
//     const int dimx = 2;
//     m_out_intervals = plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
//     out = mxGetPr(m_out_intervals);
//     vector2mVector(intervals, out, dimx, dimy);
// }

// /**
//  * @brief Extends a box by a further interval
//  **/
// void HyProBox::insert(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nrhs < 3){
//         mexErrMsgTxt("Box - insert: One argument is missing!");
//     }
//     mxArray *m_in_box, *m_in_interval;
//     const mwSize *dims;
//     double *in_box, *in_interval, *out;
//     int dimy, dimx, numdims;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

//     m_in_box = mxDuplicateArray(prhs[1]);
//     m_in_interval = mxDuplicateArray(prhs[2]);

//     dims = mxGetDimensions(prhs[2]);
//     numdims = mxGetNumberOfDimensions(prhs[2]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];
//     if(numdims > 2 || dimy != 1 || dimx != 2){
//         mexErrMsgTxt("Box - insert: You have to input a 1x2-matrix!");
//     }

//     in_box = mxGetPr(m_in_box);
//     in_interval = mxGetPr(m_in_interval);
//     carl::Interval<double> interval = ObjectHandle::mInterval2Hypro(in_interval);
//     box->insert(interval);
// }

// /**
//  * @brief Getter for the limiting points.
//  **/
// void HyProBox::limits(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - limits: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - limits: One argument is missing!");
//     }
//     mxArray* m_out;
//     double* out;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     std::pair<hypro::Point<double>, hypro::Point<double>> p = box->limits();
    
//     m_out = plhs[0] = mxCreateDoubleMatrix(2, 2, mxREAL);
//     out = mxGetPr(m_out);
//     pair2matlab(p, out, 1, 2);
// }

// /**
//  * @brief Getter for the hyperplanar representation of the current box.
//  **/
// void HyProBox::constraints(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 2)
//         mexErrMsgTxt("Box - constraints: Expecting two output values!");
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - constraints: One argument is missing!");

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     std::vector<hypro::Halfspace<double>> hSpaces = box->constraints();

//     const int dimx = hSpaces[0].dimension();
//     const int dimy = hSpaces.size();

//     mxArray* m_normal = plhs[0] = mxCreateDoubleMatrix(dimy,dimx, mxREAL);
//     mxArray *m_offset = plhs[1] = mxCreateDoubleMatrix(dimy,1,mxREAL);

//     double *out_normal, *out_offset;
//     out_normal = mxGetPr(m_normal);
//     out_offset = mxGetPr(m_offset);

//     vector2mVector(hSpaces, out_normal, out_offset, dimx, dimy);
// }

// /**
//  * @brief Getter for an interval representation of one specific dimension.
//  **/
// void HyProBox::interval(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - interval: Expecting an output!");
//     }
//     if(nrhs < 3){
//         mexErrMsgTxt("Box - interval: One or more arguments are missing!");
//     }

//     mxArray *m_in_dim, *m_out;
//     double *in, *out;

//     size_t dim = (size_t) mxGetScalar(prhs[2]);

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     const carl::Interval<double> inter = box->interval(dim);
//     m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
//     out = mxGetPr(m_out);
//     ObjectHandle::convert2matlab(inter, out, 2, 1);
// }

// /**
//  * @brief Getter for an interval representation of one specific dimension.
//  **/
// void HyProBox::at(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - at: Expecting an output!");
//     }
//     if(nrhs < 3){
//         mexErrMsgTxt("Box - at: One or more arguments are missing!");
//     }

//     mxArray *m_in_dim, *m_out;
//     double* out;

//     size_t dim = (size_t) mxGetScalar(prhs[2]);
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     const carl::Interval<double> inter = box->at(dim);

//     m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
//     out = mxGetPr(m_out);
//     ObjectHandle::convert2matlab(inter, out, 2, 1);
// }

// /**
//  * @brief Determines if the current box is empty.
//  **/
// void HyProBox::is_empty_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - isEmpty: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - isEmpty: One argument missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     const bool empty = box->empty();
//     mxLogical a = empty;
//     plhs[0] = mxCreateLogicalScalar(empty);
// }

// /**
//  * @brief Determines if the current box is symmetric.
//  **/
// void HyProBox::is_symmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - isSymmetric: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - isSymmetric: One argument missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     const bool empty = box->isSymmetric();
//     mxLogical a = empty;
//     plhs[0] = mxCreateLogicalScalar(empty);
// }

// /**
//  * @brief Getter for the maximal point.
//  **/
// void HyProBox::max(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - max: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - max: One argument missing!");
//     }
//     mxArray *m_out;
//     double* out;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::Point<double> m = box->max();
//     int dim = m.rawCoordinates().size();
//     m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
//     out = mxGetPr(m_out);
//     ObjectHandle::convert2matlab(m, out, 1, dim);
// }

// /**
//  * @brief Getter for the minimal point.
//  **/
// void HyProBox::min(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
// if(nlhs < 1){
//         mexErrMsgTxt("Box - min: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - min: One argument missing!");
//     }
//     mxArray *m_out;
//     double* out;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::Point<double> m = box->min();
//     int dim = m.rawCoordinates().size();
//     m_out = plhs[0] = mxCreateDoubleMatrix(1, 2, mxREAL);
//     out = mxGetPr(m_out);
//     ObjectHandle::convert2matlab(m, out, 1, dim);
// }

// /**
//  * @brief Method returning the supremum point of the box, i.e. the maximal point.
//  **/
// void HyProBox::supremum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - supremum: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - supremum: One argument missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     double supremum = box->supremum();
//     plhs[0] = mxCreateDoubleScalar(supremum);
// }

// /**
//  * @brief Getter for a vertex-representation of the current box.
//  **/
// void HyProBox::vertices(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - vertices: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - vertices: One argument is missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     std::vector<hypro::Point<double>> vertices = box->vertices();

//     mxArray* m_out_vertices;
//     double* out;
//     int dimy = vertices.size();
//     int dimx = vertices[0].dimension();
//     m_out_vertices = plhs[0] = mxCreateDoubleMatrix(dimy, dimx, mxREAL);
//     out = mxGetPr(m_out_vertices);
//     vector2mVector<hypro::Point<double>>(vertices, out, dimx, dimy);
// }

// /**
//  * @brief Evaluation function (convex linear optimization).
//  **/
// void HyProBox::evaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - evaluate: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - evaluate: One or more arguments are missing!");
//     mxArray *m_in_vector;
//     double *in_vector;
//     const mwSize *dims_vec;
//     int vec_len;
//     bool ans;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

//     m_in_vector = mxDuplicateArray(prhs[2]);
//     const double dir = (double) mxGetScalar(prhs[3]);
//     in_vector = mxGetPr(m_in_vector);

//     dims_vec = mxGetDimensions(prhs[2]);
//     vec_len = (int) dims_vec[0];

//     hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(in_vector, vec_len);

//     if(dir == 0){
//         ans = false;
//     }else if (dir == 1){
//         ans = true;
//     }else{
//         mexErrMsgTxt("Box - evaluate: The direction must be either 0 or 1!");
//     }
    
//     hypro::EvaluationResult<double> eval = box->evaluate(vec, ans);
//     plhs[0] = convertPtr2Mat<hypro::EvaluationResult<double>>(&eval);
// }

// /**
//  * @brief Multi-evaluation function (convex linear optimization).
//  **/
// void HyProBox::multiEvaluate(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - multiEvaluate: Expecting an output!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - multiEvaluate: One or more arguments are missing!");
//     mxArray *m_in_vector;
//     double *in_vector;
//     const mwSize *dims;
//     int dimx, dimy;
//     bool ans;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);

//     m_in_vector = mxDuplicateArray(prhs[2]);
//     const double dir = (double) mxGetScalar(prhs[3]);
//     in_vector = mxGetPr(m_in_vector);

//     dims = mxGetDimensions(prhs[2]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];

//     hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_vector, dimx, dimy);

//     if(dir == 0){
//         ans = false;
//     }else if (dir == 1){
//         ans = true;
//     }else{
//         mexErrMsgTxt("Box - evaluate: The direction must be either 0 or 1!");
//     }
    
//     //Does this make sense?
//     // std::vector<hypro::EvaluationResult<double>> eval = box->multiEvaluate(mat,ans);
//     // plhs[0] = convertPtr2Mat<std::vector<hypro::EvaluationResult<double>>>(&eval);
// }

// /**
//  * @brief Checks if two boxes are equal.
//  **/
// void HyProBox::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - ==: Expecting an output!");
//     }
//     if(nrhs < 3){
//         mexErrMsgTxt("Box - ==: One or more arguments are missing!");
//     }
//     hypro::Box<double>* box_1 = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::Box<double>* box_2 = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
//     mxLogical ans = false;
//     if(*box_1 == *box_2){
//         ans = true;
//     }
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief Determines inequality of two boxes.
//  **/
// void HyProBox::unequal(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - !=: Expecting an output!");
//     }
//     if(nrhs < 3){
//         mexErrMsgTxt("Box - !=: One or more arguments are missing!");
//     }
//     hypro::Box<double>* box_1 = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::Box<double>* box_2 = convertMat2Ptr<hypro::Box<double>>(prhs[2]);
//     mxLogical ans = false;
//     if(*box_1 != *box_2){
//         ans = true;
//     }      
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief Scaling operator.
//  **/
// void HyProBox::multiply(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - *: Expecting an output!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - *: One or more arguments are missing!");
//     hypro::Box<double>* box_1 = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     const double factor = (double) mxGetScalar(prhs[2]);
    
//     hypro::Box<double> temp = box_1->operator*(factor);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Outstream operator.
//  **/
// void HyProBox::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - <<: One or more arguments are missing!");

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     if(!box->empty()){
//         hypro::Point<double> min_p = box->min();
//         hypro::Point<double> max_p = box->max();
//         hypro::vector_t<double> vec_min =  min_p.rawCoordinates();
//         hypro::vector_t<double> vec_max =  max_p.rawCoordinates();
//         mexPrintf("Min: [");
//         for(int i = 0; i < vec_min.size(); i++){
//             mexPrintf("%f ", vec_min[i]);
//         }
//         mexPrintf("] Max: [");
//         for(int i = 0; i < vec_max.size(); i++){
//             mexPrintf("%f ", vec_max[i]);
//         }
//         mexPrintf("]\n");
//     }
// }

// /**
//  * @brief Getter for the space dimension.
//  **/
// void HyProBox::dimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - dimension: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - dimension: One or more arguments are missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     std::size_t dim = box->dimension();
//     plhs[0] = mxCreateDoubleScalar(dim);
// }

// /**
//  * @brief Removes redundancy (part of the general interface. Does nothing for boxes.)
//  **/
// void HyProBox::removeRedundancy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1){
//         mexErrMsgTxt("Box - removeRedundancy: Expecting an output!");
//     }
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - removeRedundancy: One or more arguments are missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     box->removeRedundancy();
// }

// /**
//  * @brief Storage size determination.
//  **/
// void HyProBox::box_size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - size: Expecting an output!");
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - size: One or more arguments are missing!");

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     std::size_t dim = box->size();
    
//     plhs[0] = mxCreateDoubleScalar(dim);
// }

// /**
//  * @brief Returns type of representation.
//  **/
// void HyProBox::type(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     mexPrintf("Box");
// }

// /**
//  * @brief Function to reduce the number representation (over-approximate).
//  **/
// void HyProBox::reduceNumberRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - reduceNumberRepresentation: Expecting an output!");
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - reduceNumberRepresentation: One or more arguments are missing!");
    
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::Box<double> temp = box->reduceNumberRepresentation();
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Makes a symmetric box from the current box.
//  **/
// void HyProBox::makeSymmetric(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nrhs < 2){
//         mexErrMsgTxt("Box - makeSymmetric: One or more arguments are missing!");
//     }
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     box->makeSymmetric();
// }

// /**
//  * @brief Checks if a box lies in the specified halfspace.
//  **/
// void HyProBox::satisfiesHalfspace(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 2)
//         mexErrMsgTxt("Box - satisfiesHalfspace: Expecting two output values!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - satisfiesHalfspace: One or more arguments are missing!");

//     mxArray* m_in_normal, *out_box, *out_cont;
//     const mwSize *dims;
//     double *in_normal, *cont;
//     int dimx, dimy;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_normal = mxDuplicateArray(prhs[2]);
//     const int offset = (const int) mxGetScalar(prhs[3]);
//     dims = mxGetDimensions(prhs[2]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];

//     in_normal = mxGetPr(m_in_normal);

//     const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro(in_normal, dimy);
//     const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(hy_normal,offset);

//     std::pair<hypro::CONTAINMENT, hypro::Box<double>> p = box->satisfiesHalfspace(hSpace);

//     std::string ans = "";
//     ObjectHandle::convert2matlab(p.first, ans);
//     out_cont = plhs[0] = mxCreateString(ans.c_str());
//     hypro::Box<double>* b = new hypro::Box<double>(p.second);
//     plhs[1] = convertPtr2Mat<hypro::Box<double>>(b);
    
// }

// /**
//  * @brief Checks if a box lies in the specified halfspaces.
//  **/
// void HyProBox::satisfiesHalfspaces(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 2)
//         mexErrMsgTxt("Box - satisfiesHalfspaces: Expecting two output values!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - satisfiesHalfspaces: One or more arguments are missing!");

//     mxArray *m_in_matrix, *m_in_vector, *out_box, *out_cont;
//     const mwSize *mat_dims, *vec_dims;
//     double *in_matrix, *in_vector, *cont;
//     int mat_dimx, mat_dimy, vec_len;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_matrix = mxDuplicateArray(prhs[2]);
//     m_in_vector = mxDuplicateArray(prhs[3]);
//     mat_dims = mxGetDimensions(prhs[2]);
//     vec_dims = mxGetDimensions(prhs[3]);
//     mat_dimy = (int) mat_dims[0];
//     mat_dimx = (int) mat_dims[1];
//     vec_len = (int) vec_dims[0];

//     in_matrix = mxGetPr(m_in_matrix);
//     in_vector = mxGetPr(m_in_vector);

//     const hypro::matrix_t<double> hy_matrix = ObjectHandle::mMatrix2Hypro(in_matrix, mat_dimx, mat_dimy);
//     const hypro::vector_t<double> hy_vector = ObjectHandle::mVector2Hypro(in_vector, vec_len);
//     std::pair<hypro::CONTAINMENT, hypro::Box<double>> p = box->satisfiesHalfspaces(hy_matrix, hy_vector);

//     std::string ans = "";
//     ObjectHandle::convert2matlab(p.first, ans);
//     out_cont = plhs[0] = mxCreateString(ans.c_str());
//     hypro::Box<double>* b = new hypro::Box<double>(p.second);
//     plhs[1] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Projects a box on a specified dimension.
//  **/
// void HyProBox::project(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - project: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - project: One or more arguments are missing!");
    
//     mxArray *m_in_dimensions;
//     const mwSize *dims;
//     double *in_dimensions;
//     int dimy;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_dimensions = mxDuplicateArray(prhs[2]);
//     dims = mxGetDimensions(prhs[2]);
//     dimy = (int) dims[0];

//     in_dimensions = mxGetPr(m_in_dimensions);

//     std::vector<std::size_t> hy_dimensions = ObjectHandle::mSizeVector2Hypro(in_dimensions,dimy);

//     hypro::Box<double> temp = box->project(hy_dimensions);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Makes a linear transformation of a box.
//  **/
// void HyProBox::linearTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - linearTransformation: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - linearTransformation: One or more arguments are missing!");
    
//     mxArray *m_in_matrix;
//     const mwSize *dims;
//     double *in_matrix;
//     int dimx, dimy;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_matrix = mxDuplicateArray(prhs[2]);
//     dims = mxGetDimensions(prhs[2]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];

//     in_matrix = mxGetPr(m_in_matrix);
//     hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, dimx, dimy);

//     hypro::Box<double> temp = box->linearTransformation(mat);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Makes an affine transformation of a box.
//  **/
// void HyProBox::affineTransformation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - affineTransformation: Expecting one output value!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - affineTransformation: One or more arguments are missing!");
    
//     mxArray *m_in_matrix, *m_in_vector;
//     const mwSize *mat_dims, *vec_dims;
//     double *in_matrix, *in_vector;
//     int mat_dimx, mat_dimy, vec_len;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_matrix = mxDuplicateArray(prhs[2]);
//     m_in_vector = mxDuplicateArray(prhs[3]);
//     mat_dims = mxGetDimensions(prhs[2]);
//     vec_dims = mxGetDimensions(prhs[3]);
//     mat_dimy = (int) mat_dims[0];
//     mat_dimx = (int) mat_dims[1];
//     vec_len = (int) vec_dims[0];

//     in_matrix = mxGetPr(m_in_matrix);
//     in_vector = mxGetPr(m_in_vector);

//     hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, mat_dimx, mat_dimy);
//     hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(in_vector, vec_len);


//     hypro::Box<double> temp = box->affineTransformation(mat, vec);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Performs Minkowski sum of two boxes.
//  **/
// void HyProBox::minkowskiSum(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - minkowskiSum: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - minkowskiSum: One or more arguments are missing!");
    
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box_rhs = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[2]);

//     hypro::Box<double> sum = box->minkowskiSum(*box_rhs);
//     hypro::Box<double>* b = new hypro::Box<double>(sum);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Performs a Minkowski decomposition of two boxes.
//  **/
// void HyProBox::minkowskiDecomposition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - minkowskiDecomposition: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - minkowskiDecomposition: One or more arguments are missing!");
    
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box_rhs = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[2]);

//     hypro::Box<double> sum = box->minkowskiDecomposition(*box_rhs);
//     hypro::Box<double>* b = new hypro::Box<double>(sum);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Computes the Minkowski decomposition of the current box by the given box.
//  **/
// void HyProBox::intersect(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - intersect: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - intersect: One or more arguments are missing!");
    
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box_rhs = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[2]);

//     hypro::Box<double> sum = box->intersect(*box_rhs);
//     hypro::Box<double>* b = new hypro::Box<double>(sum);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Checks if a box intersects a given halfspace.
//  **/
// void HyProBox::intersectHalfspace(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - intersectHalfspace: Expecting two output values!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - intersectHalfspace: One or more arguments are missing!");

//     mxArray* m_in_normal, *out_box, *out_cont;
//     const mwSize *dims;
//     double *in_normal, *cont;
//     int dimx, dimy;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_normal = mxDuplicateArray(prhs[2]);
//     const int offset = (const int) mxGetScalar(prhs[3]);
//     dims = mxGetDimensions(prhs[2]);
//     dimy = (int) dims[0];
//     dimx = (int) dims[1];

//     in_normal = mxGetPr(m_in_normal);

//     const hypro::vector_t<double> hy_normal = ObjectHandle::mVector2Hypro(in_normal, dimy);
//     const hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(hy_normal,offset);

//     hypro::Box<double> temp = box->intersectHalfspace(hSpace);
//     hypro::Box<double>* inter = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(inter);
// }

// /**
//  * @brief Checks if a box intersects given halfspaces.
//  **/
// void HyProBox::intersectHalfspaces(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - intersectHalfspaces: Expecting one output value!");
//     if(nrhs < 4)
//         mexErrMsgTxt("Box - intersectHalfspaces: One or more arguments are missing!");
    
//     mxArray *m_in_matrix, *m_in_vector;
//     const mwSize *mat_dims, *vec_dims;
//     double *in_matrix, *in_vector;
//     int mat_dimx, mat_dimy, vec_len;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_matrix = mxDuplicateArray(prhs[2]);
//     m_in_vector = mxDuplicateArray(prhs[3]);
//     mat_dims = mxGetDimensions(prhs[2]);
//     vec_dims = mxGetDimensions(prhs[3]);
//     mat_dimy = (int) mat_dims[0];
//     mat_dimx = (int) mat_dims[1];
//     vec_len = (int) vec_dims[0];

//     in_matrix = mxGetPr(m_in_matrix);
//     in_vector = mxGetPr(m_in_vector);

//     hypro::matrix_t<double> mat = ObjectHandle::mMatrix2Hypro(in_matrix, mat_dimx, mat_dimy);
//     hypro::vector_t<double> vec = ObjectHandle::mVector2Hypro(in_vector, vec_len);


//     hypro::Box<double> temp = box->intersectHalfspaces(mat, vec);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
// * @brief Checks if a box contains a given point.
// **/
// void HyProBox::contains_point(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - contains_point: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - contains_point: One or more arguments are missing!");

//     mxArray* m_in_point;
//     double* in_point;
//     const mwSize *dims;
//     int point_len;
    
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_point = mxDuplicateArray(prhs[2]);
//     in_point = mxGetPr(m_in_point);
//     dims = mxGetDimensions(prhs[2]);
//     point_len = (int) dims[0];

//     hypro::Point<double> hy_point = ObjectHandle::mPoint2Hypro(in_point, point_len);

//     const bool ans = box->contains(hy_point);
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief Checks if the current box contains a given box.
//  **/
// void HyProBox::contains_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - contains_box: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - contains_box: One or more arguments are missing!");

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::Box<double>* box_arg = convertMat2Ptr<hypro::Box<double>>(prhs[2]);

//     const bool ans = box->contains(*box_arg);
//     plhs[0] = mxCreateLogicalScalar(ans);
// }

// /**
//  * @brief Computes the union of two boxes.
//  **/
// void HyProBox::unite_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - unite_box: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - unite_box: One or more arguments are missing!");
    
//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>* box_rhs = convertMat2Ptr<hypro::BoxT<double, hypro::Converter<double>, hypro::BoxLinearOptimizationOn>>(prhs[2]);

//     hypro::Box<double> temp = box->unite(*box_rhs);
//     hypro::Box<double>* b = new hypro::Box<double>(temp);
//     plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief Computes the union of the current box with a set of boxes.
//  **/
// void HyProBox::unite_boxes(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     mexErrMsgTxt("Something is wrong here!");
//     if(nlhs < 1)
//         mexErrMsgTxt("Box - unite_boxes: Expecting one output value!");
//     if(nrhs < 3)
//         mexErrMsgTxt("Box - unite_boxes: One or more arguments are missing!");

//     mxArray* m_in_boxes;
//     double* in_boxes;
//     const mwSize *dims;
//     int dimy;
//     std::vector<hypro::Box<double>> hy_boxes;

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     m_in_boxes = mxDuplicateArray(prhs[2]);
//     in_boxes = mxGetPr(m_in_boxes);
//     dims = mxGetDimensions(prhs[2]);
//     dimy = dims[0];

//     for(int i = 2; i < nrhs; i++){
//         hypro::Box<double>* b = convertMat2Ptr<hypro::Box<double>>(prhs[i]);
//         hy_boxes.emplace_back(*b);
//     }

//     // hypro::Box<double> united = box->unite(hy_boxes); HERE IS A PROBLEM
//     // hypro::Box<double>* b = new hypro::Box<double>(united);
//     // plhs[0] = convertPtr2Mat<hypro::Box<double>>(b);
// }

// /**
//  * @brief
//  **/
// void HyProBox::reduceRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - reduceRepresentation: One or more arguments are missing!");

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     box->reduceRepresentation();
// }

// /**
//  * @brief Reduces the box - only in case rational types are used, the number representation is optimized.
//  **/
// void HyProBox::clear_box(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     if(nrhs < 2)
//         mexErrMsgTxt("Box - clear_box: One or more arguments are missing!");

//     hypro::Box<double>* box = convertMat2Ptr<hypro::Box<double>>(prhs[1]);
//     box->clear();
// }

// /**
// * @brief The entry point to the HyPro Box class for Matalb.
// * @param nlhs Number of items in plhs 
// * @param plhs Array of mxArray pointers to the output variables
// * @param nrhs Number of items in prhs
// * @param prhs Array of mxArray pointers to the input variables
// **/
// void HyProBox::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
//     // Get the command string
//     char cmd[64];
//     if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
//         mexErrMsgTxt("Box - First input should be a command string less than 64 characters long.");
    
//     /***************************************************************************
//      * Constructors
//      **************************************************************************/

//     if (!strcmp("new_empty", cmd) && nrhs == 1){  
//         emptyBox(nlhs, plhs, prhs);
//         return;
//     }
    
//     // Check if there is a second input, which should be the class instance handle
//     if (nrhs < 2){
//         mexErrMsgTxt("Second input should be a Box instance handle.");
//     }
    
//     if(!strcmp("copy", cmd)){
//         copyBox(nlhs, plhs, prhs);
//         return;
//     }

//     if(!strcmp("new_interval", cmd)){
//         boxFromSingleInterval(nlhs, plhs, prhs);
//         return;
//     }

//     if(!strcmp("new_intervals", cmd)){
//         boxFromIntervals(nlhs, plhs, prhs);
//         return;
//     }

//     if(!strcmp("new_points",cmd)){
//         boxFromPoints(nlhs, plhs, prhs);
//         return;
//     }

//     if(!strcmp("new_matrix",cmd)){
//         boxFromMatrix(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if (!strcmp("delete", cmd)) {
//         deleteBox(nlhs, nrhs, prhs);
//         return;
//     }
    
//     /***************************************************************************
//      * Getters & setters
//      **************************************************************************/ 

//     if(!strcmp("getSettings", cmd)){
//         getSettings(nlhs, plhs,  prhs);
//         return;
//     }

//     if(!strcmp("empty", cmd)){
//         empty(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("intervals", cmd)){
//         intervals(nlhs, plhs, prhs);
//         return;
//     }

//     if(!strcmp("insert", cmd)){
//         insert(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("limits", cmd)){
//         limits(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("constraints", cmd)){
//         constraints(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("interval", cmd)){
//         interval(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("at", cmd)){
//         at(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("isEmpty", cmd)){
//         is_empty_box(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("isSymmetric", cmd)){
//         is_symmetric(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("max", cmd)){
//         max(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("min", cmd)){
//         min(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("supremum", cmd)){
//         supremum(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("vertices", cmd)){
//         vertices(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("evaluate", cmd)){
//         evaluate(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("multiEvaluate", cmd)){
//         multiEvaluate(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("==", cmd)){
//         equals(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("!=", cmd)){
//         unequal(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("*", cmd)){
//         multiply(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("<<", cmd)){
//         outstream(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     /**************************************************************************
//      * General interface
//     **************************************************************************/
    
//     if(!strcmp("dimension", cmd)){
//         dimension(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("removeRedundancy", cmd)){
//         removeRedundancy(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("size", cmd)){
//         box_size(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("type", cmd)){
//         type(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("reduceNumberRepresentation", cmd)){
//         reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("makeSymmetric", cmd)){
//         makeSymmetric(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("satisfiesHalfspace", cmd)){
//         satisfiesHalfspace(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("satisfiesHalfspaces", cmd)){
//         satisfiesHalfspaces(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("project", cmd)){
//         project(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("linearTransformation", cmd)){
//         linearTransformation(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("affineTransformation", cmd)){
//         affineTransformation(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("minkowskiSum", cmd)){
//         minkowskiSum(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("minkowskiDecomposition", cmd)){
//         minkowskiDecomposition(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("intersect", cmd)){
//         intersect(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("intersectHalfspace", cmd)){
//         intersectHalfspace(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("intersectHalfspaces", cmd)){
//         reduceNumberRepresentation(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("contains_point", cmd)){
//         contains_point(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("contains_box", cmd)){
//         contains_box(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("unite_box", cmd)){
//         unite_box(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("unite_boxes", cmd)){
//         unite_boxes(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("reduceRepresentation", cmd)){
//         reduceRepresentation(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     if(!strcmp("clear", cmd)){
//         clear_box(nlhs, plhs, nrhs, prhs);
//         return;
//     }

//     mexErrMsgTxt("Command not recognized");
// }
