#include <stdint.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <carl/interval/Interval.h>
#include <mex.h>
#include "../../types.h"
#include "../../datastructures/Point.h"
#include "../../datastructures/Halfspace.h"
#include "../linearOptimization/EvaluationResult.h"


class ObjectHandle{
    public:
        template<typename T>
        static void vector2matlab(const std::vector<T>&, double*, const int, const int);

        template<typename T>
        static void pair2matlab(const std::pair<T,T>&, double*, const int, const int);
        
        static void convert2matlab(const carl::Interval<double>&, double*, const int, const int, const int = 0);
        static void convert2matlab(const hypro::matrix_t<double>&, double*, const int, const int, const int = 0);
        static void convert2matlab(const hypro::vector_t<double>&, double*, const int, const int, const int = 0);
        static void convert2matlab(const hypro::Point<double>&, double*, const int, const int, const int = 0);
        static void convert2matlab(const hypro::Halfspace<double>&, double*, const int, const int, const int = 0);
        static void convert2matlab(const hypro::EvaluationResult<double>&, double*, const int, const int, const int = 0 );

        static carl::Interval<double> mInterval2Hypro(double*);
        static hypro::matrix_t<double> mMatrix2Hypro(double*, const int, const int);
        static hypro::vector_t<double> mVector2Hypro(double*, const int);
        static hypro::Point<double> mPoint2Hypro(double*, const int);
        static hypro::Halfspace<double> mHalfspace2Hypro(double*, const int, const int);
        static hypro::EvaluationResult<double> mEvaluationResult2Hypro(double*);

        static std::vector<carl::Interval<double>> mIntervals2HyProIntervals(double*, int, int);
        static std::vector<carl::Interval<double>>& mPoints2HyProIntervals(double*);
        static carl::Interval<double>& mInterval2HyproInterval(double*);
        static hypro::matrix_t<double>& mMatrix2HyProMatrix(double*, int, int);
        static hypro::vector_t<double>& mVector2HyProVector(double*, int);
        static hypro::Point<double>& mPoint2HyProPoint(double*, int);
        static std::pair<hypro::Point<double>, hypro::Point<double>> mPointPair2HyProPointPair(double*);
        static std::vector<hypro::Point<double>> mPointsVector2HyProPointsVector(double*, int&);
        static hypro::Halfspace<double> mHalfspace2hyProHalfspace(double*, int, double&);
        static std::vector<hypro::Halfspace<double>> mHalfspaceVector2hyProHalfspaceVector(double*);
        static hypro::EvaluationResult<double> mEvaluationStruct2hyProEvaluationResult(double*);
        static std::vector<hypro::EvaluationResult<double>> mMultiEvaluationStruct2hyProMultiEvaluation(double*);
    private:
};

struct matlabHalfspace{
    hypro::vector_t<double> normal;
    double offset;
};

/********************************************************************************************************
 *  HyPro Objects to Matlab
 *******************************************************************************************************/

/**
 * @brief Converts a std vector into a Matlab vector
 * @param vec The vector
 * @parma out Pointer to the matlab vector
 **/ 
template<typename T>
void vector2mVector(const std::vector<T>& vec, double* out, const int dimx, const int dimy){
    for(int i = 0; i < dimy; i++){
        ObjectHandle::convert2matlab(vec[i], out, dimx, dimy, i);
    }
}

/**
 * @brief Converts a std pair into Matlab vecotr
 * @param p The pair
 * @param out Pointer to the Matlab vector
 **/
template<typename T>
void pair2matlab(const std::pair<T,T> p, double* out, const int dimx, const int dimy){
    ObjectHandle::convert2matlab(p.first, out, dimx, dimy);
    ObjectHandle::convert2matlab(p.second, out, dimx, dimy,1);
}

/**
 * @brief Converts a single HyPro interval into Matlab interval (matrix)
 * @param inter The hypro interval
 * @param out Pointer to the Matlab output matrix
 * @parma dimx, dimy Dimensions
 **/
void ObjectHandle::convert2matlab(const carl::Interval<double>& inter, double *out, const int dimx, const int dimy, const int index){
    out[index] = inter.lower();
    out[index + dimy] = inter.upper();
}

/**
 * @brief Converts a HyPro matrix into Matalb  matrix
 * @param matrix HyPro matrix
 * @param out Pointer to the output matlab matrix
 * @param dimx, dimy The dimensions of the matrix
 **/
void ObjectHandle::convert2matlab(const hypro::matrix_t<double>& matrix, double *out, const int dimx, const int dimy, const int index){
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            out[i*dimy+j] = matrix(j,i);
        }
    }
}

/**
 * @brief Converts a HyPro vector into Matlab vector
 * @param vect The HyPro vector
 * @param out Pointer to the output Matlab vector
 * @param dimx,dimy The dimensions
 **/
void ObjectHandle::convert2matlab(const hypro::vector_t<double>& vec, double *out, const int dimx, const int dimy, const int index){
    for(int i = 0; i < dimy; i++){
        out[i] = vec(i);
    }
}

/**
 * @brief Converts a HyPro Point into Matlab vector
 * @param p HyPro point
 * @param out Pointer to the output matlab vector
 * @param dimx,dimy The dimensions
 * @index index Points to the first element of the matlab vector
 **/
void ObjectHandle::convert2matlab(const hypro::Point<double>& p, double *out, const int dimx, const int dimy, const int index){
    hypro::vector_t<double> vec_one =  p.rawCoordinates();
    for(int i = 0; i < vec_one.size(); i++){
        out[i*dimy + index] = vec_one[i];
    }
}

/**
 * @brief Converts a HyPro halfspace into Matlab representation
 * @param h The HyPro halfspace
 * @param out Pointer to Matlab struct representing the halfspace
 * @param dimx,dimy
 * @param index
 **/
void ObjectHandle::convert2matlab(const hypro::Halfspace<double>& h, double *out, const int dimx, const int dimy, const int index){
    hypro::vector_t<double> nVector = h.normal();
    double offset = h.offset();

    const char *field_names[] = {"normal", "offset"};
    struct matlabHalfspace hSpace = {nVector, offset};
    mwSize dims[2] = {1,1};


    mxArray *m_normal = mxCreateDoubleMatrix(nVector.size(), 1, mxREAL);
    double *normal_out = mxGetPr(m_normal);

    for(int i = 0; i < nVector.size(); i++){
        normal_out[i] = nVector[i];
    }

    mxArray *m_offset = mxCreateDoubleScalar(offset);

    mxArray *entry = mxCreateStructArray(2,2,2,field_names);
    mxSetFieldByNumber(entry, 0, 0, m_normal);
    mxSetFieldByNumber(entry, 0, 1, m_offset);

    double* p = mxGetPr(entry);
    out[index] = p;

    // hypro::vector_t<double> temp(1,1);
    // nVector.conservativeResize(nVector.rows() + 1, nVector.cols());
    // nVector(nVector.rows()-1,1) = offset;
}

/**
 * @brief Converts a HyPros evaluation results into Matlab representation
 * @param h The HyPro halfspace
 * @param out Pointer to the Matlab vector - THE LAST ENTRY IS THE OFFSET!
 * @param dimx,dimy
 * @param index
 **/
void ObjectHandle::convert2matlab(const hypro::EvaluationResult<double>& h, double *out, const int dimx, const int dimy, const int index){
 
}

/********************************************************************************************************
 *  Matlab Objects to HyPro
 *******************************************************************************************************/


/**
 * @brief Converts Matlab intervals (in form of a matrix) into a vector of HyPro intervals
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 **/
 std::vector<carl::Interval<double>> ObjectHandle::mIntervals2HyProIntervals(double* intervals, int dimx, int dimy){
    std::vector<carl::Interval<double>> hyPro_intervals;
    int counter = 0;
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            hyPro_intervals.emplace_back(carl::Interval<double>(intervals[i*dimy+j], intervals[(i + 1)*dimy+j]));
        }
        i++;
    }
    return hyPro_intervals;
 }

/**
 *  @brief Converts a single Matlab interval into a HyPro interval
 *  @param Pointer to the matlab input interval
 **/
carl::Interval<double>& ObjectHandle::mInterval2HyproInterval(double* interval){
    carl::Interval<double> *hyPro_interval = new carl::Interval<double>(interval[0], interval[1]);
    return *hyPro_interval;
}

/**
 *  @brief Converts a pair of points defined in matlab into hyPro intervals
 *  @param points A pointer to the input Matlab matrix
 **/
std::vector<carl::Interval<double>>& ObjectHandle::mPoints2HyProIntervals(double* points){
    std::vector<carl::Interval<double>> *hyPro_intervals = new std::vector<carl::Interval<double>>;
    hyPro_intervals->emplace_back(carl::Interval<double>(points[0], points[2]));
    hyPro_intervals->emplace_back(carl::Interval<double>(points[1], points[3]));
    return *hyPro_intervals;
}

/**
 * @brief Converts a Matlab matrix into HyPro matrix_t<double>
 * @param m_matrix Pointer to the Matlab matrix
 * @param dimx, dimy The dimensions of the matrix
 **/
hypro::matrix_t<double>& ObjectHandle::mMatrix2HyProMatrix(double* m_matrix, int dimx, int dimy){
    hypro::matrix_t<double> *hypro_matrix = new hypro::matrix_t<double>(dimx,dimy);
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            (*hypro_matrix)(j,i) = m_matrix[i*dimy+j];
        }
    }
    return *hypro_matrix;
}

/**
 * @brief Converts a Matlab vector into HyPro vector
 * @param m_vector Pointer to the Matlab vector
 * @parma v_len Length of the vector
 **/
hypro::vector_t<double>& ObjectHandle::mVector2HyProVector(double* m_vector, int v_len){
    hypro::vector_t<double> *vector = new hypro::vector_t<double>(v_len);
    for(int i = 0; i < v_len; i++){
        (*vector)(i) = m_vector[i];
    }
    return *vector;
}

/**
 * @brief Converts a Matlab vector into HyPro Point
 * @param vec Pointer to the vector of coordinates
 * @param dimy Lenght of the vector
 **/
hypro::Point<double>& ObjectHandle::mPoint2HyProPoint(double* vec, int dimy){
    std::vector<double> temp;
    for(int i = 0; i < dimy; i++){
        temp.emplace_back(vec[i]);
    }
    hypro::Point<double> *point = new hypro::Point<double>(temp);
    return *point;
}

/**
 * @brief Converts a 2x2 Matlab matrix into pair of HyPro points
 * @param mat Pointer to the matrix
 **/
std::pair<hypro::Point<double>, hypro::Point<double>> ObjectHandle::mPointPair2HyProPointPair(double* mat){
    std::vector<double> temp_one{mat[0],mat[1]};
    std::vector<double> temp_two{mat[2],mat[3]};

    hypro::Point<double> *point_one = new hypro::Point<double>(temp_one);
    hypro::Point<double> *point_two = new hypro::Point<double>(temp_two);

    std::pair<hypro::Point<double>,hypro::Point<double>> pair = {*point_one,*point_two};
    return pair;
}

/**
 * @brief Converts a Matlab matrix into vector of HyPro Points
 * @param vec Pointer to the Matlab matrix
 * @parma dim Length of the vector
 **/
std::vector<hypro::Point<double>> ObjectHandle::mPointsVector2HyProPointsVector(double* vec, int& dim){
    std::vector<hypro::Point<double>> hypro_vec(dim);

    for(int i = 0; i < dim; i++){
        hypro::Point<double> p = hypro::Point<double>(vec[i]);
        hypro_vec[i] = p;
    }
    return hypro_vec;
}

/**
 * @brief Converts a Maltab normal vector and offset into HyPro halfspace
 * @param mNormal The normal vector 
 * @param offset The offset
 **/
hypro::Halfspace<double> ObjectHandle::mHalfspace2hyProHalfspace(double* mNormal, int len, double& offset){
    hypro::vector_t<double> normalVec = ObjectHandle::mVector2HyProVector(mNormal, len);
    hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(normalVec, offset);
    return hSpace;
}

// /**
//  * @brief
//  * @param
//  **/
hypro::EvaluationResult<double> mEvaluationStruct2hyProEvaluationResult(double*){}

// /**
//  * @brief
//  * @param
//  **/
std::vector<hypro::EvaluationResult<double>> mMultiEvaluationStruct2hyProMultiEvaluation(double*){

}
  


 
 

