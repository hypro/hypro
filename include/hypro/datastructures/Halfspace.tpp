/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *  Class that holds the implementation of a Halfspace.
 *  @file Halfspace.tpp
 *
 *  @author Stefan Schupp 	<stefan.schupp@cs.rwth-aachen.de>
 *
 *  @since 	2015-03-16
 *  @version 	2015-03-16
 */

#include "Halfspace.h"

namespace hypro {

    template<typename Number>
    Halfspace<Number>::Halfspace(const Point<Number> &_vector, const Number &_off)
            : mNormal(_vector.rawCoordinates()), mScalar(_off) {}

    template<typename Number>
    Halfspace<Number>::Halfspace(std::initializer_list<Number> _coordinates, const Number &_off) {
        mNormal = vector_t<Number>(_coordinates.size());
        unsigned pos = 0;
        for (auto &coordinate: _coordinates) {
            mNormal(pos) = coordinate;
            ++pos;
        }
        mScalar = _off;
    }

    template<typename Number>
    template<typename Normal, typename Offset,
            enable_if<convertible<Normal, vector_t<Number>> && convertible<Offset, Number>>>
    Halfspace<Number>::Halfspace(Normal &&normal, Offset &&offset)
            : mNormal(std::forward<Normal>(normal)), mScalar(std::forward<Offset>(offset)) {}

    template<typename Number>
    Halfspace<Number>::Halfspace(const vector_t<Number> &_vec, const std::vector<vector_t<Number>> &_vectorSet) {
        // here: Halfspace given in parameterform is converted to normalform
        // the normal vector of the Halfspace is computed by solving a system of
        // equations
        mNormal = computePlaneNormal(_vectorSet);

        // the scalar is just the scalar product of the normal vector & a point in the
        // Halfspace
        mScalar = mNormal.dot(_vec);
    }

    template<typename Number>
    Halfspace<Number>::Halfspace(const std::vector<Point<Number>> &points) {
        assert(!points.empty());
        std::vector<vector_t<Number>> rawCoordinates;
        std::transform(points.begin(), points.end(), std::back_inserter(rawCoordinates),
                       [](const Point<Number> &refpoint) { return refpoint.rawCoordinates(); });
        mNormal = Halfspace<Number>::computePlaneNormal(rawCoordinates);
        mScalar = Halfspace<Number>::computePlaneOffset(mNormal, points[0]);
        TRACE("hypro.datastructures", "Constructed hsp from " << mNormal << " and " << mScalar);
    }

    template<typename Number>
    Halfspace<Number>::Halfspace(const std::vector<vector_t<Number>> &points) {
        assert(!points.empty());
        mNormal = Halfspace<Number>::computePlaneNormal(points);
        mScalar = Halfspace<Number>::computePlaneOffset(mNormal, Point(points[0]));
    }

    template<typename Number>
    unsigned Halfspace<Number>::dimension() const {
        return unsigned(mNormal.nonZeros());
    }

    template<typename Number>
    const vector_t<Number> &Halfspace<Number>::normal() const &{
        return mNormal;
    }

    template<typename Number>
    vector_t<Number> &&Halfspace<Number>::normal() &&{
        return std::move(mNormal);
    }

    template<typename Number>
    void Halfspace<Number>::setNormal(const vector_t<Number> &_normal) {
        mNormal = _normal;
    }

    template<typename Number>
    Halfspace<Number> &Halfspace<Number>::invert() {
        mNormal = -mNormal;
        mScalar = -mScalar;
        return *this;
    }

    template<typename Number>
    Number Halfspace<Number>::offset() const &{
        return mScalar;
    }

    template<typename Number>
    Number &&Halfspace<Number>::offset() &&{
        return std::move(mScalar);
    }

    template<typename Number>
    void Halfspace<Number>::setOffset(Number _offset) {
        mScalar = _offset;
    }

    template<typename Number>
    Number Halfspace<Number>::signedDistance(const vector_t<Number> &_point) const {
        return (_point.dot(mNormal) - mScalar);
    }

    template<typename Number>
    Number Halfspace<Number>::evaluate(const vector_t<Number> &_direction) const {
        return (_direction.dot(mNormal));
    }

    template<typename Number>
    Point<Number> Halfspace<Number>::projectPointOnPlane(const Point<Number> point) const {
        return Point<Number>(point.rawCoordinates() +
                             ((mScalar - point.rawCoordinates().dot(mNormal)) / mNormal.dot(mNormal)) * mNormal);
    }

    template<typename Number>
    bool Halfspace<Number>::intersection(Number &_result, const vector_t<Number> &_vector) const {
        bool intersect = false;
        Number factor = 0;
        Number dotProduct = (mNormal.dot(_vector));
        if (dotProduct != 0) {
            intersect = true;
            factor = mScalar / dotProduct;
        }
        _result = factor;
        // note: to get the intersection point -> _vector *= factor;
        return intersect;
    }

    template<typename Number>
    bool Halfspace<Number>::intersection(Number &_result, const Point<Number> &_vector) const {
        return intersection(_result, _vector.rawCoordinates());
    }

    template<typename Number>
    Halfspace<Number> Halfspace<Number>::projectOn(const std::vector<size_t> &dimensions) const {
        if (dimensions.empty()) {
            return Halfspace<Number>();
        }

        vector_t<Number> projectedNormal = hypro::projectOn(mNormal, dimensions);
        return Halfspace<Number>(projectedNormal, mScalar);
    }

    template<typename Number>
    Halfspace<Number> Halfspace<Number>::linearTransformation(const matrix_t<Number> &A) const {
        Eigen::FullPivLU<matrix_t<Number>> lu(A);
        // if A has full rank, we can simply retransform
        if (lu.rank() == A.rows()) {
            // Todo: Verify this.
            return Halfspace<Number>(mNormal.transpose() * A.inverse(), mScalar);
        } else {
            // we cannot invert A - chose points on the plane surface and create new plane
            assert(false);
            // TODO
            return Halfspace<Number>();
        }
    }

    template<typename Number>
    Halfspace<Number> Halfspace<Number>::affineTransformation(const matrix_t<Number> &A,
                                                              const vector_t<Number> &b) const {
        Eigen::FullPivLU<matrix_t<Number>> lu(A);
        // if A has full rank, we can simply retransform
        if (lu.rank() == A.rows()) {
            Number newOffset = mNormal.transpose() * A.inverse() * b;
            return Halfspace<Number>(mNormal.transpose() * A.inverse(), newOffset + mScalar);
        } else {
            // we cannot invert A - chose points on the plane surface and create new plane
            assert(false);
            // TODO
            return Halfspace<Number>();
        }
    }

    template<typename Number>
    vector_t<Number> Halfspace<Number>::intersectionVector(const Halfspace<Number> &_rhs) const {
        matrix_t<Number> A = matrix_t<Number>(3, mNormal.rows());
        A.row(0) = mNormal.transpose();
        A.row(1) = _rhs.normal().transpose();
        A.row(2) = vector_t<Number>::Ones(A.cols()).transpose();

        vector_t<Number> b = vector_t<Number>(3);
        b << mScalar, _rhs.offset(), Number(1);

        vector_t<Number> result = A.fullPivLu().solve(b);
        // vector_t<Number> result = gauss( A, b );

        return result;
    }

    template<typename Number>
    vector_t<Number> Halfspace<Number>::fastIntersect(const std::vector<Halfspace<Number>> &_planes) {
        assert(_planes.size() ==
               _planes.begin()->dimension());     // TODO: Make function more general to cope with arbitrary input.

        matrix_t<Number> A(_planes.size(), _planes.begin()->dimension());
        vector_t<Number> b(_planes.size());
        std::size_t pos = 0;
        for (auto planeIt = _planes.begin(); planeIt != _planes.end(); ++planeIt) {
            A.row(pos) = planeIt->normal().transpose();
            b(pos) = planeIt->offset();
            ++pos;
        }

        Eigen::FullPivLU<matrix_t<Number>> lu_decomp(A);
        if (lu_decomp.rank() < A.rows()) {
            // TODO: Cope with intersection plane.
        }

        vector_t<Number> res = lu_decomp.solve(b);

        /*
        // check for infinity
        bool infty = false;
        for ( unsigned i = 0; i < res.rows(); ++i ) {
            if ( std::numeric_limits<Number>::infinity() == ( Number( res( i ) ) ) ) {
                //std::cout << ( Number( res( i ) ) ) << " is infty." << std::endl;
                infty = true;
                break;
            }
        }
        */
        return res;
    }

    template<typename Number>
    vector_t<Number> Halfspace<Number>::saveIntersect(const std::vector<Halfspace<Number>> &_planes, Number threshold) {
        assert(_planes.size() ==
               _planes.begin()->dimension());     // TODO: Make function more general to cope with arbitrary input.

        matrix_t<Number> A(_planes.size(), _planes.begin()->dimension());
        vector_t<Number> b(_planes.size());
        std::size_t pos = 0;
        for (auto planeIt = _planes.begin(); planeIt != _planes.end(); ++planeIt) {
            A.row(pos) = planeIt->normal().transpose();
            b(pos) = planeIt->offset();
            ++pos;
        }

        Eigen::FullPivLU<matrix_t<Number>> lu_decomp(A);
        if (lu_decomp.rank() < A.rows()) {
            // TODO: Cope with intersection plane.
        }

        vector_t<Number> res = lu_decomp.solve(b);

        std::vector<std::size_t> belowIndices;
        for (std::size_t index = 0; index < _planes.size(); ++index) {
            Number dist = _planes.at(index).offset() - _planes.at(index).normal().dot(res);
            if (dist > 0) {
                belowIndices.push_back(index);
            }
        }
        Number eps = std::numeric_limits<Number>::epsilon();
        std::size_t iterationCount = 0;
        while (!belowIndices.empty()) {
            // enlarge as long as point lies below one of the planes.
            if (eps < threshold) {
                eps = eps * 2;
            } else {
                eps += std::numeric_limits<Number>::epsilon();
            }

            for (std::size_t index = 0; index < _planes.size(); ++index) {
                A.row(index) = _planes.at(index).normal().transpose();
                // if(belowIndices.front() == index) {
                // std::cout << "Shift plane  + " << eps << ", dist: ";
                b(index) = _planes.at(index).offset() + eps;
                //	belowIndices.erase(belowIndices.begin());
                //} else {
                //	b(index) = _planes.at(index).offset();
                //}
            }
            belowIndices.clear();
            assert(belowIndices.empty());
            vector_t<Number> tmp = Eigen::FullPivLU<matrix_t<Number>>(A).solve(b);

            for (std::size_t i = 0; i < _planes.size(); ++i) {
                Number dist = _planes.at(i).offset() - _planes.at(i).normal().dot(tmp);
                if (dist > 0) {
                    belowIndices.push_back(i);
                }
            }
            ++iterationCount;
            if (belowIndices.empty()) {
                res = tmp;
            }
        }
        return res;
    }

    template<typename Number>
    bool Halfspace<Number>::contains(const vector_t<Number> _vector) const {
        return satisfiesIneqation(mNormal, mScalar, _vector);
    }

    template<typename Number>
    bool Halfspace<Number>::contains(const Point<Number> _vector) const {
        return this->contains(_vector.rawCoordinates());
    }

    template<typename Number>
    bool Halfspace<Number>::contains(const std::vector<Point<Number>> &_points) const {
        for (const auto &point: _points) {
            if (!this->contains(point.rawCoordinates())) {
                return false;
            }
        }
        return true;
    }

    template<typename Number>
    bool Halfspace<Number>::exactContains(vector_t<Number> const &point) const {
        hypro::vector_t<mpq_class> normal = mNormal.template cast<mpq_class>();
        hypro::vector_t<mpq_class> mpq_vertex = point.template cast<mpq_class>();
        mpq_class offset = mScalar;

        return normal.dot(mpq_vertex) - offset <= 0;
    }

    template<typename Number>
    bool Halfspace<Number>::holds(const vector_t<Number> _vector) const {
        return (_vector.dot(mNormal) == mScalar);
    }

    template<typename Number>
    vector_t<Number> Halfspace<Number>::computePlaneNormal(const std::vector<vector_t<Number>> &pointSet) {
        assert(!pointSet.empty());
        // case: dimension-many vertices in the plane
        if (pointSet.size() <= unsigned(pointSet.begin()->rows())) {
            // method avoiding glpk and using Eigen instead (higher precision)
            Eigen::Index dim = pointSet.begin()->rows();
            matrix_t<Number> constraints(pointSet.size(), dim + 1);
            for (unsigned pos = 0; pos < pointSet.size(); ++pos) {
                constraints.row(pos).head(dim) = pointSet.at(pos).transpose();
                constraints.row(pos)(dim) = Number(1);
            }

            TRACE("hypro.datastructures", "computing kernel of " << constraints);
            TRACE("hypro.datastructures", "rows: " << constraints.rows() << ", cols: " << constraints.cols());

            matrix_t<Number> kernel = constraints.fullPivLu().kernel();

            vector_t<Number> normal = kernel.col(0).head(dim);

            TRACE("hypro.datastructures", "Computed kernel: " << kernel);

            return normal;
        } else {
            /*
             * Setup LP with GLPK
             */

            // TODO: Re-think this: apparently this only works, if all points lie exactly on the plane, in which case you
            // could have selected only the dim-first ones.

            glp_prob *normal;
            normal = glp_create_prob();
            glp_set_obj_dir(normal, GLP_MAX);

            // we have one row for each edge in our set
            glp_add_rows(normal, int(pointSet.size()));

            // constraints of auxiliary variables (bounds for rows)
            for (int i = 1; i <= int(pointSet.size()); ++i) {
                glp_set_row_bnds(normal, i, GLP_FX, 0.0, 0.0);
            }

            // each column corresponds to one dimension of a vector in our edgeSet
            // TODO consider p1 & p2 of different dimensions? (-> two edge sets)
            glp_add_cols(normal, int(pointSet.at(0).rows()));

            // coefficients of objective function:
            for (int i = 1; i <= pointSet.at(0).rows(); ++i) {
                glp_set_obj_coef(normal, i, 1.0);
            }

            // constraints for structural variables
            for (int i = 1; i <= pointSet.at(0).rows(); ++i) {
                glp_set_col_bnds(normal, i, GLP_DB, -1.0, 1.0);
            }

            // setup matrix coefficients
            std::size_t elements = (pointSet.size()) * (std::size_t(pointSet.at(0).rows()));
            int *ia = new int[elements + 1];
            int *ja = new int[elements + 1];
            double *ar = new double[elements + 1];
            int pos = 1;

            // to prevent bugs
            ia[0] = 0;
            ja[0] = 0;
            ar[0] = 0;

            for (int i = 1; i <= int(pointSet.size()); ++i) {
                for (int j = 1; j <= pointSet.at(0).rows(); ++j) {
                    ia[pos] = i;
                    ja[pos] = j;
                    vector_t<Number> tmpVec = pointSet.at(i - 1);
                    ar[pos] = toDouble(tmpVec(j - 1));
                    ++pos;
                }
            }
            assert(pos - 1 <= int(elements));

            glp_load_matrix(normal, int(elements), ia, ja, ar);
            glp_simplex(normal, NULL);
            glp_exact(normal, NULL);

            vector_t<Number> result = vector_t<Number>(pointSet.at(0).rows(), 1);

            // fill the result vector based on the optimal solution returned by the LP
            for (unsigned i = 1; i <= pointSet.at(0).rows(); ++i) {
                result(i - 1) = carl::rationalize<Number>(glp_get_col_prim(normal, i));
            }

            glp_delete_prob(normal);
            delete[] ja;
            delete[] ia;
            delete[] ar;

            return result;
        }
    }

    template<typename Number>
    Number Halfspace<Number>::computePlaneOffset(const vector_t<Number> &normal, const Point<Number> &pointOnPlane) {
        return normal.dot(pointOnPlane.rawCoordinates());
    }

// Return mNormal as a matrix
    template<typename Number>
    matrix_t<Number> Halfspace<Number>::matrix() const {
        matrix_t<Number> mat = matrix_t<Number>::Zero(1, mNormal.rows());
        mat.row(0) = mNormal.transpose();
        return mat;
    }

// Return mScalar as a vector
    template<typename Number>
    vector_t<Number> Halfspace<Number>::vector() const {
        vector_t<Number> vec = vector_t<Number>::Zero(1);
        vec(0) = mScalar;
        return vec;
    }

// A halfspace itself cannot be empty, except its normal is the zero vector and the scalar is smaller than 0
    template<typename Number>
    bool Halfspace<Number>::empty() const {
        if (mNormal != vector_t<Number>::Zero(mNormal.rows()) && mScalar < 0) return true;
        return false;
    }

    template<typename Number>
    EvaluationResult<Number> Halfspace<Number>::evaluate(const vector_t<Number> &direction, bool /*useExact*/) const {
        assert(mNormal.rows() == direction.rows());
        std::pair<bool, Number> dependent = linearDependent(mNormal, direction);
        if (dependent.first) {
            if (dependent.second > 0) {
                // The vectors are dependent -> to find point on plane and to avoid squareroot computations, return vector
                // which contains zeroes except of the position with the first non-zero coeff, which is set to the stored
                // distance.
                vector_t<Number> pointOnPlane = vector_t<Number>::Zero(direction.rows());
                unsigned i = 0;
                while (i < direction.rows() && direction(i) == 0) {
                    ++i;
                }
                pointOnPlane(i) = mScalar;
                return EvaluationResult<Number>(mScalar, pointOnPlane, SOLUTION::FEAS);
            } else {
                return EvaluationResult<Number>(0, SOLUTION::INFTY);
            }
        }
        return EvaluationResult<Number>(0, SOLUTION::INFTY);
    }

    template<typename Number>
    std::vector<EvaluationResult<Number>> Halfspace<Number>::multiEvaluate(const matrix_t<Number> &_directions,
                                                                           bool /*useExact*/) const {
        assert(_directions.cols() == this->dimension());
        std::vector<EvaluationResult<Number>> res;
        vector_t<Number> pointOnPlane = vector_t<Number>::Zero(dimension());
        assert(mNormal.nonZeros() != 0);
        unsigned nonZeroPos = 0;
        while (mNormal(nonZeroPos) == 0) {
            ++nonZeroPos;
        }
        pointOnPlane(nonZeroPos) = mScalar;
        for (unsigned index = 0; index < _directions.rows(); ++index) {
            std::pair<bool, Number> dependent =
                    linearDependent(vector_t<Number>(mNormal), vector_t<Number>(_directions.row(index)));
            if (dependent.first) {
                if (dependent.second > 0) {
                    res.emplace_back(mScalar * dependent.second, pointOnPlane, SOLUTION::FEAS);
                } else {
                    res.emplace_back(1, pointOnPlane, SOLUTION::INFTY);
                }
            } else {
                res.emplace_back(1, pointOnPlane, SOLUTION::INFTY);
            }
        }
        assert(res.size() == std::size_t(_directions.rows()));
        return res;
    }

}  // namespace hypro
