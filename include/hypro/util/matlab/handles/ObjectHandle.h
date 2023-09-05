/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *  Class that converts various HyPro datastructures from HyPro
 *  to Matlab and vice versa.
 */

#pragma once

#include "../../../datastructures/Halfspace.h"
#include "../../../datastructures/HybridAutomaton/Condition.h"
#include "../../../datastructures/HybridAutomaton/HybridAutomatonComp.h"
#include "../../../datastructures/HybridAutomaton/Location.h"
#include "../../../datastructures/HybridAutomaton/State.h"
#include "../../../datastructures/HybridAutomaton/Transition.h"
#include "../../../datastructures/Point.h"
#include "../../../representations/GeometricObject.h"
#include "../../../types.h"
#include "../../linearOptimization/EvaluationResult.h"

#include <carl/core/MultivariatePolynomial.h>
#include <carl/core/VariablePool.h>
#include <carl/interval/Interval.h>
#include <carl/interval/set_theory.h>
#include <cstring>
#include <mex.h>
#include <stdint.h>
#include <string>
#include <typeinfo>

class ObjectHandle {
public:
    using flowpipe = std::vector<hypro::State_t<double>>;

    template<typename T>
    static void pair2Matlab(const std::pair<T, T> &, mxArray *, const int, const int);

    template<typename T>
    static std::vector<T> objArray2Hypro(const mxArray *, const int);

    template<typename T>
    static void objArray2Matlab(const std::vector<T> &, mxArray *, const int);

    template<typename T>
    static void vector2Matlab(const std::vector<T> &, mxArray *);

    template<typename T>
    static void vector2Matlab(const std::vector<T> &, mxArray *, mxArray *);

    static void flowpipes2Matlab(const std::vector<std::pair<unsigned, flowpipe>> &, mxArray *, const int);

    static void convert2Matlab(const carl::Interval<double> &, mxArray *, const int, const int, const int = 0);

    static void convert2Matlab(const hypro::matrix_t<double> &, mxArray *, const int, const int, const int = 0);

    static void convert2Matlab(const hypro::vector_t<double> &, mxArray *, const int, const int, const int = 0);

    static void convert2Matlab(const hypro::Point<double> &, mxArray *, const int, const int, const int = 0);

    static void convert2Matlab(const hypro::EvaluationResult<double> &, mxArray *, const int, const int, const int = 0);

    static void convert2Matlab(const hypro::Halfspace<double> &, mxArray *, mxArray *, const int, const int,
                               const int = 0);

    static void convert2Matlab(const hypro::CONTAINMENT &, std::string &);

    static void convert2Matlab(const hypro::SOLUTION &, std::string &);

    static void convert2Matlab(const hypro::representation_name &, std::string &);

    static void convert2Matlab(const std::vector<std::string> &, mxArray *, const mwSize *);

    static void convert2Matlab(const std::map<const hypro::Location<double> *, hypro::Condition<double>> &, mxArray *);

    static void convert2Matlab(const std::vector<hypro::Point<double>> &, mxArray *);

    static hypro::SOLUTION mSolution2Hypro(char *);

    static hypro::representation_name mRepresentationName2Hypro(int type);

    static carl::Interval<double> mInterval2Hypro(const mxArray *);

    static carl::Interval <hypro::tNumber> mMPQInterval2Hypro(const mxArray *);

    static hypro::matrix_t<double> mMatrix2Hypro(const mxArray *, const int, const int);

    static hypro::vector_t<double> mVector2Hypro(const mxArray *, const int);

    static hypro::Point<double> mPoint2Hypro(const mxArray *, const int);

    static hypro::Halfspace<double> mHalfspace2Hypro(const mxArray *, const int, double);

    static std::map<hypro::Location<double>, hypro::Condition<double>> mlocationConditionMap2Hypro(mxArray *,
                                                                                                   const int);

    static std::vector<std::size_t> mSizeVector2Hypro(const mxArray *, const int);

    static std::vector<carl::Interval < double>> mIntervals2Hypro( const mxArray*, const int = 1, const int = 2 );
    static std::vector<carl::Interval < double>> mPoints2Hypro( const mxArray* );

    static std::pair<hypro::Point<double>, hypro::Point<double>> mPointPair2Hypro(const mxArray *);

    static std::vector<hypro::Point<double>> mPointsVector2Hypro(const mxArray *, const int, const int);

    static std::vector<hypro::Halfspace<double>> mHalfspaces2Hypro(mxArray *, mxArray *, const int, const int,
                                                                   const int);

    static std::vector<carl::Term < double>> mMultivariatePoly2Hypro( const mxArray* );

    static std::vector<std::vector<std::size_t>> mVectorOfVectors2Hypro(const mxArray *, const int, const int);

    static std::vector<std::string> mStringVector2Hypro(const mxArray *);

    static std::map<const hypro::Location<double> *, hypro::Condition<double>> mLocCondMap2Hypro(const mxArray *);

    static std::vector<std::unique_ptr<hypro::Location<double>>> mLocsVector2Hypro(const mxArray *);
};

/*
 * @brief Converts a std vector into a Matlab vector.
 * @param vec The vector
 * @parma out Pointer to the matlab vector
 */
template<typename T>
void vector2Matlab(const std::vector<T> &vec, mxArray *m_out) {
    const mwSize *dims = mxGetDimensions(m_out);
    const int cols = (int) dims[1];
    const int rows = (int) dims[0];
    double *out = mxGetPr(m_out);
    for (int i = 0; i < rows; i++) {
        ObjectHandle::convert2Matlab(vec[i], m_out, rows, cols, i);
    }
}

/*
 * @brief Converts a std vector into a Matlab vector.
 * @param vec The vector
 * @param m_out_1 Pointer to output matlab vector
 * @param m_out_2 Pointer to output matlab vector
 *
 */
template<typename T>
void vector2Matlab(const std::vector<T> &vec, mxArray *m_out_1, mxArray *m_out_2) {
    const mwSize *dims = mxGetDimensions(m_out_1);
    const int cols = (int) dims[1];
    const int rows = (int) dims[0];
    double *out_1 = mxGetPr(m_out_1);
    double *out_2 = mxGetPr(m_out_2);
    for (int i = 0; i < rows; i++) {
        ObjectHandle::convert2Matlab(vec[i], m_out_1, m_out_2, rows, cols, i);
    }
}

/*
 * @brief Converts an std pair into Matlab vector.
 * @param p The pair
 * @param out Pointer to the Matlab vector
 */
template<typename T>
void pair2Matlab(const std::pair<T, T> p, mxArray *m_out, const int rows, const int cols) {
    ObjectHandle::convert2Matlab(p.first, m_out, rows, cols);
    ObjectHandle::convert2Matlab(p.second, m_out, rows, cols, 1);
}

/*
 * @brief Converts a cell of MHyPro objects into a vector of HyPro objects.
 * @param array_ptr Pointer to the cell array of MHyPro objects
 * @param len Number of the objects in the cell array
 */
template<typename T>
std::vector<T> ObjectHandle::objArray2Hypro(const mxArray *array_ptr, const int len) {
    std::vector<T> vec;
    mxArray *cellElement;
    for (int i = 0; i < len; i++) {
        cellElement = mxGetCell(array_ptr, i);
        T *obj = convertMat2Ptr<T>(cellElement);
        vec.emplace_back(*obj);
    }
    return vec;
}

/*
 * @brief Converts a vector of HyPro objects into a cell array of MHyPro       * objects.
 * @param vec Vector of HyPro objects
 * @param m_array Pointer to output cell
 * @param len Length of the vector
 */
template<typename T>
void objArray2Matlab(const std::vector<T> &vec, mxArray *m_array, const int len) {
    for (int i = 0; i < len; i++) {
        auto item = vec[i];
        mxSetCell(m_array, i, convertPtr2Mat<T>(new T(item)));
    }
}

/*
 * @brief Converts a vector of HyPro points into a n x 2 Matlab matrix.
 * @param points Vector of HyPro points
 * @param m_out Pointer to the output Matlab matrix
 */
void ObjectHandle::convert2Matlab(const std::vector<hypro::Point<double>> &points, mxArray *m_out) {
    const mwSize *dims = mxGetDimensions(m_out);
    const int cols = (int) dims[1];
    const int rows = (int) dims[0];
    double *out = mxGetPr(m_out);

    for (int j = 0; j < cols; j++) {
        hypro::Point<double> p = points[j];
        for (int i = 0; i < rows; i++) {
            out[i + rows * j] = p[i];
        }
    }
}

/*
 * @brief Converts a vector of flowpipes into a cell array of MStates.
 * @param flowpipes Vector of HyPro flowpipes
 * @param m_out Pointer to the output cell array
 * @param rows Length of the flowpipes vector
 */
void ObjectHandle::flowpipes2Matlab(const std::vector<std::pair<unsigned, ObjectHandle::flowpipe>> &flowpipes,
                                    mxArray *m_out, const int rows) {
    for (int i = 0; i < rows; i++) {
        std::pair<unsigned, ObjectHandle::flowpipe> currentPair = flowpipes[i];
        mxArray *num = mxCreateDoubleScalar((double) currentPair.first);
        std::vector<hypro::State_t<double>> f = currentPair.second;
        int len = f.size();
        const mwSize dims[2] = {1, (mwSize) len};
        mxArray *states = mxCreateCellArray(2, dims);
        for (int j = 0; j < len; j++) {
            auto item = f[j];
            mxSetCell(states, j, convertPtr2Mat<hypro::State_t<double>>(new hypro::State_t<double>(item)));
        }
        mxSetFieldByNumber(m_out, i, 0, num);
        mxSetFieldByNumber(m_out, i, 1, states);
    }
}

/*
 * @brief Converts a location-condition map into an Matlab struct array.
 * @param locConmap Map of locations and conditions
 * @param m_array Pointer to the output struct array
 */
void ObjectHandle::convert2Matlab(const std::map<const hypro::Location<double> *, hypro::Condition<double>> &locConmap,
                                  mxArray *m_array) {
    int i = 0;
    for (auto &entry: locConmap) {
        mxArray *loc = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*(entry.first)));
        mxArray *cond = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>(entry.second));
        mxSetFieldByNumber(m_array, i, 0, loc);
        mxSetFieldByNumber(m_array, i, 1, cond);
        i++;
    }
}

/*
 * @brief Converts a single HyPro interval into Matlab matrix.
 * @param inter The hypro interval
 * @param out Pointer to the Matlab output matrix
 * @parma rows, cols Dimensions
 */
void ObjectHandle::convert2Matlab(const carl::Interval<double> &inter, mxArray *m_out, const int rows, const int cols,
                                  const int index) {
    double *out = mxGetPr(m_out);
    out[index] = inter.lower();
    out[index + rows] = inter.upper();
}

/*
 * @brief Converts a HyPro matrix into Matalb matrix.
 * @param matrix HyPro matrix
 * @param out Pointer to the output matlab matrix
 * @param rows, cols The dimensions of the matrix
 */
void ObjectHandle::convert2Matlab(const hypro::matrix_t<double> &matrix, mxArray *m_out, const int rows,
                                  const int cols, const int index) {
    double *out = mxGetPr(m_out);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            out[i + j * rows] = matrix.coeff(i, j);
        }
    }
}

/*
 * @brief Converts a Matlab matrix into HyPro matrix.
 * @param m_matrix Pointer to the Matlab matrix
 * @param rows, cols Dimensions of the matrix
 */
hypro::matrix_t<double> ObjectHandle::mMatrix2Hypro(const mxArray *m_matrix, const int rows, const int cols) {
    double *matrix = mxGetPr(m_matrix);
    hypro::matrix_t<double> *hypro_matrix = new hypro::matrix_t<double>(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            (*hypro_matrix)(i, j) = matrix[i + j * rows];
        }
    }
    return *hypro_matrix;
}

/*
 * @brief Converts a HyPro vector into Matlab vector.
 * @param vect The HyPro vector
 * @param out Pointer to the output Matlab vector
 * @param rows,cols The dimensions
 */
void ObjectHandle::convert2Matlab(const hypro::vector_t<double> &vec, mxArray *m_out, const int rows, const int cols,
                                  const int index) {
    double *out = mxGetPr(m_out);
    for (int i = 0; i < rows; i++) {
        out[i] = vec(i);
    }
}

/*
 * @brief Converts a HyPro Point into Matlab vector.
 * @param p HyPro point
 * @param out Pointer to the output matlab vector
 * @param rows,cols The dimensions
 * @index index Points to the first element of the matlab vector
 */
void ObjectHandle::convert2Matlab(const hypro::Point<double> &p, mxArray *m_out, const int rows, const int cols,
                                  const int index) {
    double *out = mxGetPr(m_out);
    for (int i = 0; i < rows; i++) {
        out[index * rows + i] = p[i];
    }
}

/*
 * @brief Converts a HyPro halfspace into Matlab representation.
 * @param h The HyPro halfspace
 * @param out Pointer to Matlab struct representing the halfspace
 * @param rows,cols Dimensions
 * @param index Offset
 */
void ObjectHandle::convert2Matlab(const hypro::Halfspace<double> &h, mxArray *m_normal_out, mxArray *m_offset_out,
                                  const int rows, const int cols, const int index) {
    double *normal_out = mxGetPr(m_normal_out);
    double *offset_out = mxGetPr(m_offset_out);
    hypro::vector_t<double> nVector = h.normal();
    double offset = h.offset();

    for (int i = 0; i < cols; i++) {
        int at = i * rows + index;
        normal_out[at] = nVector[i];
    }
    offset_out[index] = offset;
}

/*
 * @brief Converts the HyPro containment enum into Matlab.
 * @param cont Containment value
 * @param out Pointer to the Matlab output
 */
void ObjectHandle::convert2Matlab(const hypro::CONTAINMENT &cont, std::string &out) {
    if (cont == hypro::CONTAINMENT::NO) {
        out = "NO";
    } else if (cont == hypro::CONTAINMENT::FULL) {
        out = "FULL";
    } else if (cont == hypro::CONTAINMENT::BOT) {
        out = "BOT";
    } else if (cont == hypro::CONTAINMENT::PARTIAL) {
        out = "PARTIAL";
    } else if (cont == hypro::CONTAINMENT::YES) {
        out = "YES";
    }
}

/*
 * @brief Converts the HyPro solution enum into Matlab
 * @param cont Solution value
 * @param out Pointer to the Matlab output
 */
void ObjectHandle::convert2Matlab(const hypro::SOLUTION &sol, std::string &out) {
    if (sol == hypro::SOLUTION::FEAS) {
        out = "FEAS";
    } else if (sol == hypro::SOLUTION::INFEAS) {
        out = "INFEAS";
    } else if (sol == hypro::SOLUTION::INFTY) {
        out = "INFTY";
    } else if (sol == hypro::SOLUTION::UNKNOWN) {
        out = "UNKNOWN";
    }
}

/*
 * @brief Converts representation_name into Matlab string.
 * @param name Name of the representation
 * @param out Pointer to the output Matlab string
 */
void ObjectHandle::convert2Matlab(const hypro::representation_name &name, std::string &out) {
    if (name == hypro::representation_name::box) {
        out = "box";
        return;
    } else if (name == hypro::representation_name::carl_polytope) {
        out = "carl polytope";
        return;
    } else if (name == hypro::representation_name::constraint_set) {
        out = "constraint set";
        return;
    } else if (name == hypro::representation_name::difference_bounds) {
        out = "difference bounds";
        return;
    } else if (name == hypro::representation_name::polytope_h) {
        out = "polytope_h";
        return;
    } else if (name == hypro::representation_name::polytope_v) {
        out = "polytope_v";
        return;
    } else if (name == hypro::representation_name::ppl_polytope) {
        out = "ppl polytope";
        return;
    } else if (name == hypro::representation_name::support_function) {
        out = "support function";
        return;
    } else if (name == hypro::representation_name::taylor_model) {
        out = "taylor model";
        return;
    } else if (name == hypro::representation_name::zonotope) {
        out = "zonotope";
        return;
    } else {
        out = "undef";
    }
}

/*
 * @brief Converts a vector of strings into a Matlab cell array of strings.
 * @param strings Vector of strings
 * @param str_array Pointer to the output cell array
 * @param dim Dimensions
 */
void ObjectHandle::convert2Matlab(const std::vector<std::string> &strings, mxArray *str_arr, const mwSize *dims) {
    mxArray *element;
    for (int i = 0; i < 3; i++) {
        element = mxCreateString(strings[i].c_str());
        mxSetCell(str_arr, i, element);
    }
}

/*
 * @brief Converts a Matlab vector of ints into standard vector.
 * @param sizes Pointer to the Matlab vector
 * @param v_len Length of the vector
 */
std::vector<std::size_t> ObjectHandle::mSizeVector2Hypro(const mxArray *m_sizes, const int v_len) {
    double *sizes = mxGetPr(m_sizes);
    std::vector<std::size_t> vec;
    for (int i = 0; i < v_len; i++) {
        vec.emplace_back(sizes[i]);
    }
    return vec;
}

/*
 * @brief Converts Matlab array of matrices into a vector of HyPro intervals.
 * @param m_interval_list A list of Matlab matrices
 * @param rows, cols Dimensions
 */
std::vector<carl::Interval < double>>

ObjectHandle::mIntervals2Hypro(const mxArray *m_intervals, int rows, int cols) {
    double *intervals = mxGetPr(m_intervals);
    std::vector<carl::Interval < double>>
    hyPro_intervals;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            hyPro_intervals.emplace_back(
                    carl::Interval<double>(intervals[i * cols + j], intervals[(i + 1) * cols + j]));
        }
        i++;
    }
    return hyPro_intervals;
}

/*
 *  @brief Converts a single Matlab matrix into a HyPro interval.
 *  @param Pointer to the Matlab input matrix
 */
carl::Interval<double> ObjectHandle::mInterval2Hypro(const mxArray *m_interval) {
    double *interval = mxGetPr(m_interval);
    carl::Interval<double> *hyPro_interval = new carl::Interval<double>(interval[0], interval[1]);
    return *hyPro_interval;
}

/*
 *  @brief Converts a pair of points defined in Matlab into HyPro intervals.
 *  @param points A pointer to the input Matlab matrix
 */
std::vector<carl::Interval < double>>

ObjectHandle::mPoints2Hypro(const mxArray *m_points) {
    double *points = mxGetPr(m_points);
    std::vector<carl::Interval < double>>
    *hyPro_intervals = new std::vector<carl::Interval < double>>;
    hyPro_intervals->emplace_back(carl::Interval<double>(points[0], points[2]));
    hyPro_intervals->emplace_back(carl::Interval<double>(points[1], points[3]));
    return *hyPro_intervals;
}

/*
 * @brief Converts a Matlab vector into HyPro vector.
 * @param m_vector Pointer to the Matlab vector
 * @parma v_len Length of the vector
 */
hypro::vector_t<double> ObjectHandle::mVector2Hypro(const mxArray *m_vector, const int v_len) {
    double *vector = mxGetPr(m_vector);
    hypro::vector_t<double> *hypro_vector = new hypro::vector_t<double>(v_len);
    for (int i = 0; i < v_len; i++) {
        (*hypro_vector)(i) = vector[i];
    }
    return *hypro_vector;
}

/*
 * @brief Converts a Matlab vector into HyPro point
 * @param vec Pointer to the vector of coordinates
 * @param cols Lenght of the vector
 */
hypro::Point<double> ObjectHandle::mPoint2Hypro(const mxArray *m_vec, int cols) {
    double *vec = mxGetPr(m_vec);
    std::vector<double> temp;
    for (int i = 0; i < cols; i++) {
        temp.emplace_back(vec[i]);
    }
    hypro::Point<double> *point = new hypro::Point<double>(temp);
    return *point;
}

/*
 * @brief Converts a n x 2 Matlab matrix into pair of HyPro points.
 * @param mat Pointer to the matrix
 */
std::pair<hypro::Point<double>, hypro::Point<double>> ObjectHandle::mPointPair2Hypro(const mxArray *m_mat) {
    double *mat = mxGetPr(m_mat);
    const mwSize *dims;
    dims = mxGetDimensions(m_mat);
    const int rows = dims[0];
    std::vector<double> temp_one;
    std::vector<double> temp_two;

    for (int i = 0; i < rows; i++) {
        temp_one.emplace_back(mat[i]);
        temp_two.emplace_back(mat[i + rows]);
    }
    hypro::Point<double> *point_one = new hypro::Point<double>(temp_one);
    hypro::Point<double> *point_two = new hypro::Point<double>(temp_two);

    std::pair<hypro::Point<double>, hypro::Point<double>> pair = {*point_one, *point_two};
    return pair;
}

/*
 * @brief Converts a Matlab matrix into vector of HyPro points.
 * @param vec Pointer to the Matlab matrix
 * @parma dim Length of the vector
 */
std::vector<hypro::Point<double>> ObjectHandle::mPointsVector2Hypro(const mxArray *m_vec, const int rows,
                                                                    const int cols) {
    double *points = mxGetPr(m_vec);
    std::vector<hypro::Point<double>> hypro_vec(rows);

    for (int i = 0; i < rows; i++) {
        std::vector<double> pnt(cols);
        for (int j = 0; j < cols; j++) {
            pnt[j] = points[i * cols + j];
        }
        hypro_vec[i] = hypro::Point<double>(pnt);
    }
    return hypro_vec;
}

/*
 * @brief Converts a Maltab normal vector and offset into HyPro halfspace.
 * @param mNormal The normal vector
 * @param offset The offset
 */
hypro::Halfspace<double> ObjectHandle::mHalfspace2Hypro(const mxArray *m_normal, const int len, double offset) {
    hypro::vector_t<double> normalVec = ObjectHandle::mVector2Hypro(m_normal, len);
    hypro::Halfspace<double> hSpace = hypro::Halfspace<double>(normalVec, offset);
    return hSpace;
}

/*
 * @brief Converts a Maltab solution into HyPro SOLUTION enum value.
 * @param mSol The solution
 */
hypro::SOLUTION ObjectHandle::mSolution2Hypro(char *mSol) {
    if (!strcmp(mSol, "FEAS") || !strcmp(mSol, "feas")) {
        return hypro::SOLUTION::FEAS;
    } else if (!strcmp(mSol, "INFEAS") || !strcmp(mSol, "infeas")) {
        return hypro::SOLUTION::INFEAS;
    } else if (!strcmp(mSol, "INFTY") || !strcmp(mSol, "infty")) {
        return hypro::SOLUTION::INFTY;
    } else if (!strcmp(mSol, "UNKNOWN") || !strcmp(mSol, "unknown")) {
        return hypro::SOLUTION::UNKNOWN;
    }
}

/*
 * @brief Converts a Matlab string containing a representation name.
 * into Hypro enum
 */
hypro::representation_name ObjectHandle::mRepresentationName2Hypro(int type) {
    // 0 = box, 1 = carl_polytope, 2 = constraint_set
    //  3 = polytope_h, 4 = polytope_v
    //  5 = ppl_polytope, 6 = support_function, 7 = taylor_model
    //  8 = zonotope, 9 = difference_bounds,
    if (type == 0) {
        return hypro::representation_name::box;
    } else if (type == 1) {
        return hypro::representation_name::carl_polytope;
    } else if (type == 2) {
        return hypro::representation_name::constraint_set;
    } else if (type == 3) {
        return hypro::representation_name::polytope_h;
    } else if (type == 4) {
        return hypro::representation_name::polytope_v;
    } else if (type == 5) {
        return hypro::representation_name::ppl_polytope;
    } else if (type == 6) {
        return hypro::representation_name::support_function;
    } else if (type == 7) {
        return hypro::representation_name::taylor_model;
    } else if (type == 8) {
        return hypro::representation_name::zonotope;
    } else if (type == 9) {
        return hypro::representation_name::difference_bounds;
    } else {
        return hypro::representation_name::UNDEF;
    }
}

/*
 * @brief Converts a Matlab matrix and vector into a vector of halfspaces.
 * Each column of the matrix is a normal vector. The corresponding offset
 * is saved in the vector.
 * @param m_matrix Pointer to the input matrix
 * @param m_offsets Pointer to the input vector
 * @param rows, cols, len Dimensions
 */
std::vector<hypro::Halfspace<double>> ObjectHandle::mHalfspaces2Hypro(mxArray *m_matrix, mxArray *m_offsets,
                                                                      const int rows, const int cols, const int len) {
    std::vector<hypro::Halfspace<double>> hypro_vec(len);
    hypro::matrix_t<double> mat = mMatrix2Hypro(m_matrix, rows, cols);
    hypro::vector_t<double> vec = mVector2Hypro(m_offsets, len);
    for (int i = 0; i < rows; i++) {
        const hypro::vector_t<double> normal = mat.col(i);
        const double offset = vec(i, 0);
        hypro::Halfspace<double> *h = new hypro::Halfspace<double>(normal, offset);
        hypro_vec.emplace_back(*h);
    }
    return hypro_vec;
}

/*
 * @brief Converts a Matlab matrix into a vector of vectors.
 * @param m_matrix Pointer to the input Matlab matrix
 * @parma rows, cols Dimensions
 */
std::vector<std::vector<size_t>> ObjectHandle::mVectorOfVectors2Hypro(const mxArray *m_matrix, const int rows,
                                                                      const int cols) {
    double *matrix = mxGetPr(m_matrix);
    std::vector<std::vector<size_t>> vector(rows);
    for (int i = 0; i < rows; i++) {
        std::vector<size_t> temp(cols);
        for (int j = 0; j < cols; j++) {
            temp[j] = (size_t) matrix[i * cols + j];
        }
        vector[i] = temp;
    }
    return vector;
}

/*
 * @brief Converts a cell array of strings in Matlab into a vector of strings * in HyPro.
 * @param strings Pointer to the cell array
 */
std::vector<std::string> ObjectHandle::mStringVector2Hypro(const mxArray *strings) {
    std::vector<std::string> vec;
    mxArray *cellElement;
    double *p;
    std::size_t nfields = (std::size_t) mxGetNumberOfElements(strings);

    for (int i = 0; i < (int) nfields; i++) {
        cellElement = mxGetCell(strings, i);
        p = mxGetPr(cellElement);
        char *word = reinterpret_cast<char *>( p );
        vec.emplace_back(std::string(word));
    }
    return vec;
}

/*
 * @brief Converts a struct array containg locations conditions mapping into     HyPro map of locations-conditions.
 * @param structArray Pointer to the Matlab struct array
 */
std::map<const hypro::Location<double> *, hypro::Condition<double>> ObjectHandle::mLocCondMap2Hypro(
        const mxArray *structArray) {
    const mwSize *dims = mxGetDimensions(structArray);
    int cols = dims[1];
    std::map<const hypro::Location<double> *, hypro::Condition<double>> mapping;

    for (int i = 0; i < cols; i++) {
        hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(mxGetField(structArray, i, "loc"));
        std::string name = loc->getName();
        hypro::Condition<double> *cond =
                convertMat2Ptr<hypro::Condition<double>>(mxGetField(structArray, i, "cond"));
        mapping[loc] = *cond;
    }
    return mapping;
}

/*
 * @brief Converts a Matlab vector of locations into vector of unique pointers   to the locations.
 * @param locsVector Pointer to the vector of MLocation objects
 */
std::vector<std::unique_ptr<hypro::Location<double>>> ObjectHandle::mLocsVector2Hypro(const mxArray *locsVector) {
    const mwSize *loc_dims;
    int loc_num;
    loc_dims = mxGetDimensions(locsVector);
    loc_num = loc_dims[1];
    const std::vector<hypro::Location<double>> locs = objArray2Hypro<hypro::Location<double>>(locsVector, loc_num);

    std::vector<std::unique_ptr<hypro::Location<double>>> ptr_locs;
    for (const auto &elem: locs) {
        hypro::Location<double> *l = new hypro::Location<double>(elem);
        std::unique_ptr<hypro::Location<double>> loc = std::make_unique<hypro::Location<double>>(*l);
        ptr_locs.emplace_back(std::move(loc));
    }
    return ptr_locs;
}
