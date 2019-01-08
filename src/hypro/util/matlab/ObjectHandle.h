#ifndef OBJECT_HANDLE_H
#define OBJECT_HANDLE_H

#include <stdint.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <carl/interval/Interval.h>
#include <carl/interval/set_theory.h>
#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/VariablePool.h>
#include <mex.h>
#include "../../types.h"
#include "../../datastructures/Point.h"
#include "../../datastructures/Halfspace.h"
#include "../linearOptimization/EvaluationResult.h"
#include "../../representations/GeometricObject.h"


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
        static void convert2matlab(const hypro::EvaluationResult<double>&, double*, const int, const int, const int = 0 );
        static void convert2matlab(const hypro::Halfspace<double>&, double*, double*, const int, const int, const int = 0 );
        static void convert2matlab(const hypro::CONTAINMENT&, std::string&);
        static void convert2matlab(const hypro::SOLUTION&, std::string&);
        static void convert2matlab(const carl::Term<double>&, double*, const int, const int);

        static hypro::SOLUTION mSolution2Hypro(char*);
        static carl::Interval<double> mInterval2Hypro(double*);
        static hypro::matrix_t<double> mMatrix2Hypro(double*, const int, const int);
        static hypro::vector_t<double> mVector2Hypro(double*, const int);
        static hypro::Point<double> mPoint2Hypro(double*, const int);
        static hypro::Halfspace<double> mHalfspace2Hypro(double*, const int, double&);
        static hypro::EvaluationResult<double> mEvaluationResult2Hypro(double*);

        static std::vector<std::size_t> mSizeVector2Hypro(double*, const int);
        static std::vector<carl::Interval<double>> mIntervals2Hypro(double*, const int, const int);
        static std::vector<carl::Interval<double>> mPoints2Hypro(double*);
        static std::pair<hypro::Point<double>, hypro::Point<double>> mPointPair2Hypro(double*);
        static std::vector<hypro::Point<double>> mPointsVector2Hypro(double*, int);
        static std::vector<hypro::Halfspace<double>> mHalfspaces2Hypro(double*, double*, const int, const int, const int);
        static std::vector<hypro::EvaluationResult<double>> mMultiEvaluationStruct2Hypro(double*);
        static std::vector<carl::Term<double>> mMultivariatePoly2Hypro(double*);

    private:
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

template<typename T>
void vector2mVector(const std::vector<T>& vec, double* out_1, double* out_2, const int dimx, const int dimy){
    for(int i = 0; i < dimy; i++){
        ObjectHandle::convert2matlab(vec[i], out_1, out_2, dimx, dimy, i);
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
void ObjectHandle::convert2matlab(const hypro::Halfspace<double>& h, double *normal_out, double *offset_out, const int dimx, const int dimy, const int index){
    hypro::vector_t<double> nVector = h.normal();
    double offset = h.offset();

    for(int i = 0; i < nVector.size(); i++){
        normal_out[i] = nVector[i];
    }
    offset_out = &offset;

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

/**
 * @brief Converts the HyPro containment enum into matlab
 * @param cont Containment value
 * @param out Pointer to the Matlab output
 **/
void ObjectHandle::convert2matlab(const hypro::CONTAINMENT& cont, std::string& out){
    if (cont == hypro::CONTAINMENT::NO){
        out = "NO";
    }else if (cont == hypro::CONTAINMENT::FULL){
        out = "FULL";
    }else if (cont == hypro::CONTAINMENT::BOT){
        out = "BOT";
    }else if (cont == hypro::CONTAINMENT::PARTIAL){
        out = "PARTIAL";
    }else if (cont == hypro::CONTAINMENT::YES){
        out = "YES";
    }
}

/**
 * @brief Converts the HyPro solution enum into matlab
 * @param cont Solution value
 * @param out Pointer to the Matlab output
 **/
void ObjectHandle::convert2matlab(const hypro::SOLUTION& sol, std::string& out){
    if (sol == hypro::SOLUTION::FEAS){
        out = "FEAS";
    }else if (sol == hypro::SOLUTION::INFEAS){
        out = "INFEAS";
    }else if (sol == hypro::SOLUTION::INFTY){
        out = "INFTY";
    }else if (sol == hypro::SOLUTION::UNKNOWN){
        out = "UNKNOWN";
    }
}


/**
 * @breif
 * 
 **/
void ObjectHandle::convert2matlab(const carl::Term<double>& term, double* out, const int dimx, const int dimy){

}

/********************************************************************************************************
 *  Matlab Objects to HyPro
 *******************************************************************************************************/

/**
 * @brief Converts a Matlab vector of ints into standard vector
 * @param sizes Pointer to the Matlab vector
 * @param v_len Length of the vector
 **/
std::vector<std::size_t> ObjectHandle::mSizeVector2Hypro(double* sizes, const int v_len){
    std::vector<std::size_t> vec;
    for(int i = 0; i < v_len; i++){
        vec.emplace_back(sizes[i]);
    }
    return vec;
}


/**
 * @brief Converts Matlab intervals (in form of a matrix) into a vector of HyPro intervals
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 **/
std::vector<carl::Interval<double>> ObjectHandle::mIntervals2Hypro(double* intervals, int dimx, int dimy){
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
carl::Interval<double> ObjectHandle::mInterval2Hypro(double* interval){
    carl::Interval<double> *hyPro_interval = new carl::Interval<double>(interval[0], interval[1]);
    return *hyPro_interval;
}

/**
 *  @brief Converts a pair of points defined in matlab into hyPro intervals
 *  @param points A pointer to the input Matlab matrix
 **/
std::vector<carl::Interval<double>> ObjectHandle::mPoints2Hypro(double* points){
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
hypro::matrix_t<double> ObjectHandle::mMatrix2Hypro(double* m_matrix, const int dimx, const int dimy){
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
hypro::vector_t<double> ObjectHandle::mVector2Hypro(double* m_vector, const int v_len){
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
hypro::Point<double> ObjectHandle::mPoint2Hypro(double* vec, int dimy){
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
std::pair<hypro::Point<double>, hypro::Point<double>> ObjectHandle::mPointPair2Hypro(double* mat){
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
std::vector<hypro::Point<double>> ObjectHandle::mPointsVector2Hypro(double* vec, int dim){
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
hypro::Halfspace<double> ObjectHandle::mHalfspace2Hypro(double* mNormal, const int len, double& offset){
    hypro::vector_t<double> normalVec = ObjectHandle::mVector2Hypro(mNormal, len);
    hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(normalVec, offset);
    return hSpace;
}

/**
* @brief Converts a Maltab solution into HyPro SOLUTION enum value 
* @param mSol The solution
**/
hypro::SOLUTION ObjectHandle::mSolution2Hypro(char* mSol){
    if(!strcmp(mSol, "FEAS") || !strcmp(mSol, "feas")){
        return hypro::SOLUTION::FEAS;
    }else if(!strcmp(mSol,"INFEAS") || !strcmp(mSol,"infeas")){
        return hypro::SOLUTION::INFEAS;
    }else if(!strcmp(mSol, "INFTY") || !strcmp(mSol, "infty")){
        return hypro::SOLUTION::INFTY;
    }else if(!strcmp(mSol, "UNKNOWN") || !strcmp(mSol, "unknown")){
        return hypro::SOLUTION::UNKNOWN;
    }
}

/**
 * @brief
 *
 **/
std::vector<carl::Term<double>> ObjectHandle::mMultivariatePoly2Hypro(double*){
    
}

/**
 * @brief Converts a Matlab matrix and vector into a vector of halfspaces.
 * Each column of the matrix is a normal vector. The corresponding offset
 * is saved in the vector
 * 
 **/
std::vector<hypro::Halfspace<double>> ObjectHandle::mHalfspaces2Hypro(double* matrix, double* offsets, const int dimx, const int dimy, const int len){
    std::vector<hypro::Halfspace<double>> hypro_vec(len);
    
    hypro::matrix_t<double> mat = mMatrix2Hypro(matrix, dimx, dimy);
    hypro::vector_t<double> vec = mVector2Hypro(offsets, len);

    for(int i = 0; i < dimx; i++){
        const hypro::vector_t<double> normal = mat.col(i);
        const double offset = vec(0,i);
        hypro::Halfspace<double>* h = new hypro::Halfspace<double>(normal, offset);
        hypro_vec.emplace_back(*h);
    }

    return hypro_vec;
}

#endif