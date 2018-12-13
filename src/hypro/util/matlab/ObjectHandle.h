#include <stdint.h>
#include <string>
#include <cstring>
#include <typeinfo>
#include <carl/interval/Interval.h>
#include <mex.h>
#include "../../types.h"
#include "../../datastructures/Point.h"


class ObjectHandle{
    public:
        static std::vector<carl::Interval<double>>& mIntervals2HyProIntervals(double*, int, int);
        static void hyProIntervals2mIntervals(const std::vector<carl::Interval<double>>, double*, int, int);
        static std::vector<carl::Interval<double>>& mPoints2HyProIntervals(double*);
        static carl::Interval<double>& mInterval2HyproInterval(double*);
        static hypro::matrix_t<double>& mMatrix2HyProMatrix(double*, int, int);
        static void hyProMatrix2mMatrix(hypro::matrix_t<double>&, double*, int, int);
        static hypro::vector_t<double>& mVector2HyProVector(double*, int);
        static void hyProVector2mVector(hypro::vector_t<double>&, double*, int);
        // static hypro::Point<double>& mPoint2HyProPoint(double*, int);
        // static std::pair<hypro::Point<double>, hypro::Point<double>>& mPointPair2HyProPointPair(double*);
    private:
};

/**
 * @brief Converts Matlab intervals (in form of a matrix) into a vector of HyPro intervals
 * @param m_interval_list A list of Matlab intervals (represented as arrays)
 **/
 std::vector<carl::Interval<double>>& ObjectHandle::mIntervals2HyProIntervals(double* intervals, int dimx, int dimy){
    std::vector<carl::Interval<double>> *hyPro_intervals = new std::vector<carl::Interval<double>>;
    int counter = 0;
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            hyPro_intervals->emplace_back(carl::Interval<double>(intervals[i*dimy+j], intervals[(i + 1)*dimy+j]));
        }
        i++;
    }
    return *hyPro_intervals;
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
 *  @brief Converts a HyPro interval into a Matlab interval
 *  @param interval_list A list of HyPro intervals
 *  @param out Pointer to the output Matlab matrix
 *  @param dimx Number of rows
 *  @parma dimy Number of columns
 **/
void ObjectHandle::hyProIntervals2mIntervals(std::vector<carl::Interval<double>> interval_list, double *out, int dimx, int dimy){
    for(int i = 0; i < interval_list.size(); i++){
        out[i] = interval_list[i].lower();
        out[i + dimy] = interval_list[i].upper();
    }
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
 * @brief Converts a HyPro matrix into Matalb  matrix
 * @param matrix HyPro matrix
 * @param out Pointer to the output matlab matrix
 * @param dimx, dimy The dimensions of the matrix
 **/
void ObjectHandle::hyProMatrix2mMatrix(hypro::matrix_t<double>& matrix, double *out, int dimx, int dimy){
    for(int i = 0; i < dimx; i++){
        for(int j = 0; j < dimy; j++){
            out[i*dimy+j] = matrix(j,i);
        }
    }
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
 * @brief Converts a HyPro vector into Matlab vector
 * @param vect The HyPro vector
 * @param out Pointer to the output Matlab vector
 * @param v_len Length of the vector
 **/
void ObjectHandle::hyProVector2mVector(hypro::vector_t<double>& vec, double *out, int v_len){
    for(int i = 0; i < v_len; i++){
        out[i] = vec(i);
    }
}

// /**
//  * @brief Converts a Matlab vector into HyPro Point
//  * @param vec Pointer to the vector of coordinates
//  * @param dimy Lenght of the vector
//  **/
// hypro::Point<double>& mPoint2HyProPoint(double* vec, int dimy){
//     std::vector<double> temp;
//     for(int i = 0; i < dimy; i++){
//         temp.emplace_back(vec[i]);
//     }
//     hypro::Point<double> *point = new hypro::Point<double>(temp);
//     return *point;
// }

// /**
//  * @brief Converts a 2x2 Matlab matrix into pair of HyPro points
//  * @param mat Pointer to the matrix
//  **/
// std::pair<hypro::Point<double>, hypro::Point<double>>& mPointPair2HyProPointPair(double* mat){
//     std::vector<double> temp_one;
//     std::vector<double> temp_two;
//     temp_one.emplace_back(mat[0]);
//     temp_one.emplace_back(mat[2]);
//     temp_two.emplace_back(mat[1]);
//     temp_two.emplace_back(mat[3]);

//     hypro::Point<double> *point_one = new hypro::Point<double>(temp_one);
//     hypro::Point<double> *point_two = new hypro::Point<double>(temp_one);

//     std::pair<hypro::Point<double>,hypro::Point<double>> pair = std::make_pair(*point_one,*point_two);
//     return pair;
// }


 
 

