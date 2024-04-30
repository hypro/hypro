/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../../algorithms/convexHull/ConvexHull.h"
#include "../../../algorithms/quickhull/Quickhull.h"
#include "../../../datastructures/Facet.h"
#include "../../../util/adaptions_eigen/adaptions_eigen.h"
#include "../../../util/convexHull.h"
#include "../../../util/linearOptimization/Optimizer.h"
#include "../../../util/pca.h"
#include "../../../util/sequenceGeneration/SequenceGenerator.h"
#include "../../../util/statistics/statistics.h"
#include "../../../util/typetraits.h"
#include "../Cone.h"
#include "../redundantPoints.h"
#include "VPolytopeSetting.h"
#include "util.h"

#include <cassert>
#include <set>
#include <vector>

namespace hypro {

/**
 * @brief      The class implementing the vertex representation of a convex polytope.
 *
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * \ingroup geoState @{
 */
    template<typename Number, typename Converter, typename S>
    class VPolytopeT : private GeometricObjectBase {
    public:
        using pointVector = std::vector<Point<Number>>;
        using Rays = std::set<vector_t<Number>>;
        typedef S Settings;
        typedef Number NumberType;

        static constexpr auto type_enum = representation_name::polytope_v;

    private:
        mutable pointVector mVertices = {};     ///< set of generating vertices
        Rays mRays = {};                     ///< set of generating rays
        bool mReduced = false;                 ///< caches if the polyhedron is reduced

        std::vector<std::set<unsigned>> mNeighbors;

    public:

        /**
        * @brief      Calculates the set difference of two polytopes.
        * @param[in]  polytope  The VPolytope G.
        */
        std::vector<VPolytopeT<Number, Converter, S>> setMinus2(const VPolytopeT<Number, Converter, S> &minus) const;

        /**
        * @brief      Computation of the set minus operator using crossing points.
        * @param[in]  polytope  The VPolytope G.
        */
        VPolytopeT<Number, Converter, S> setMinusCrossingV(const VPolytopeT<Number, Converter, S> &polytopeG) const;

        /**
        * @brief      Computation of the set minus operator using crossing points.
        * @param[in]  polytope  The HPolytope G.
        */
        template<typename HConverter, typename HSetting> 
        VPolytopeT<Number, Converter, S> setMinusCrossingH(const HPolytopeT<Number, HConverter, HSetting> &polytopeG) const;

        /**
        * @brief      Returns the extreme points of the polytope.
        */ 
        std::vector<Point<Number>> getExtremePoints() const;

        /**
        * @brief      Returns true if the point is extreme
        * @param[in]  point  The point.
        */
        bool isExtremePoint(Point<Number> point) const;

        /**
        * @brief      Returns the one dimensional faces of a polytope as a pair of convex vertices
        * @param[in]  extremePoints  The extreme points.
        */
        std::vector<std::pair<Point<Number>, Point<Number>>> getConvexEdges(std::vector<Point<Number>> extremePoints) const;

        /**
        * @brief      Returns true if the pair of points is a convex edge of a polytope. 
        *             Requires that points p1,p2 are extreme points.
        * @param[in]  p1  The point.
        * @param[in]  p2  The point.
        * @param[in]  extremePoints  The extreme points.
        */
        bool isPairConvexEdge(Point<Number> p1, Point<Number> p2, std::vector<Point<Number>> extremePoints) const;


        /**
        * @brief      Rertuns the crossing point of an edge (pair of points).
        * @param[in]  fromPoint  The starting point.
        * @param[in]  toPoint  The ending point.
        */
       Point<Number> getCrossingPoint(Point<Number> fromPoint, Point<Number> toPoint) const; 

       
       std::vector<Point<Number>> getBorderVertices(Point<Number> point, std::vector<std::pair<Point<Number>, Point<Number>>> edgesP, std::vector<Point<Number>> PnG) const;



        /**
         * @brief      Default constructor.
         */
        VPolytopeT();

        /**
         * @brief      Constructor from a single point.
         * @param[in]  point  The point.
         */
        VPolytopeT(const Point<Number> &point);

        /**
         * @brief      Constructor from a vector of points.
         * @param[in]  points  The points.
         */
        VPolytopeT(const pointVector &points);

        /**
         * @brief      Constructor from a vector of coordinates.
         * @param[in]  rawPoints  The raw coordinates.
         */
        VPolytopeT(const std::vector<vector_t<Number>> &rawPoints);

        /**
         * @brief      Constructor from a constraint system represented by a matrix and a  vector.
         * @param[in]  _constraints  The constraints.
         * @param[in]  _constants    The constants.
         */
        VPolytopeT(const matrix_t<Number> &_constraints, const vector_t<Number> _constants);

        /**
         * @brief      Copy constructor.
         * @param[in]  orig  The original.
         */
        VPolytopeT(const VPolytopeT &orig) = default;

        /**
         * @brief      Move constructor.
         * @param[in]  <unnamed>  The original.
         */
        VPolytopeT(VPolytopeT &&_orig) = default;

        /**
         * @brief      Destroys the object.
         */
        ~VPolytopeT() {
        }

        /***************************************************************************
         * General interface
         **************************************************************************/

        matrix_t<Number> matrix() const {
            assert(false && "NOT IMPLEMENTED YET");
            return matrix_t<Number>::Zero(1, 1);
        }

        vector_t<Number> vector() const {
            assert(false && "NOT IMPLEMENTED YET");
            return vector_t<Number>::Zero(1);
        }

        /**
         * @brief Computes a projection where the passed dimensions are projected out.
         * @details Note that this effectively reduces the state space dimension of the object in contrast to other representations.
         * @param dimensions
         * @return VPolytopeT
         */
        VPolytopeT projectOut(const std::vector<std::size_t> &dimensions) const;

        VPolytopeT projectOn(const std::vector<std::size_t> &dimensions) const;

        VPolytopeT assignIntervals(const std::map<std::size_t, carl::Interval<Number>> &) const {
            WARN("hypro", "Not implemented.");
            return *this;
        }

        VPolytopeT linearTransformation(const matrix_t<Number> &A) const;

        VPolytopeT affineTransformation(const matrix_t<Number> &A, const vector_t<Number> &b) const;

        VPolytopeT minkowskiSum(const VPolytopeT &rhs) const;

        /**
         * @brief      Intersects the polytope with a second polytope.
         * @param[in]  rhs   The right hand side.
         * @return     The resulting object.
         */
        VPolytopeT intersect(const VPolytopeT &rhs) const;

        VPolytopeT intersectHalfspace(const Halfspace<Number> &rhs) const;

        VPolytopeT intersectHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        std::pair<CONTAINMENT, VPolytopeT> satisfiesHalfspace(const Halfspace<Number> &rhs) const;

        std::pair<CONTAINMENT, VPolytopeT>
        satisfiesHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        bool contains(const Point<Number> &point) const;

        /**
         * @brief      Checks if a point represented by its coordinates is contained in the polytope.
         * @param[in]  vec  The point vector.
         * @return     True, if the point lies inside the polytope.
         */
        bool contains(const vector_t<Number> &vec) const;

        /**
         * @brief      Checks if the other polytope is fully contained in this polytope.
         * @param[in]  _other  The other polytope.
         * @return     True, if the other polytope is contained.
         */
        bool contains(const VPolytopeT &_other) const;

        VPolytopeT unite(const VPolytopeT &rhs) const;

        /**
         * @brief      Computes the convex hull of this and a set of polytopes.
         * @param[in]  rhs   The set of polytopes.
         * @return     The resulting object.
         */
        static VPolytopeT unite(const std::vector<VPolytopeT> &rhs);

        /**
         * @brief      Reduces the box - only in case rational types are used, the number representation is optimized.
         */
        void reduceRepresentation() {
            reduceNumberRepresentation();
            removeRedundancy();
        }

        /**
         * @brief      Clears the polytope.
         */
        void clear();

        EvaluationResult<Number> evaluate(const vector_t<Number> &direction) const;

        std::vector<EvaluationResult<Number>>
        multiEvaluate(const matrix_t<Number> &directions, bool useExact = true) const;

        /**
         * @brief      Checks if the polytope represents the empty set.
         * @return     True if there are no vertices.
         */
        bool empty() const { return mVertices.empty(); }

        /**
         * @brief      Constructs the empty polytope.
         * @return     The polytope.
         */
        static VPolytopeT Empty() { return VPolytopeT(); }

        /**
         * @brief      Returns the space dimension.
         * @return     The space dimension.
         */
        std::size_t dimension() const {
            if (mVertices.empty()) return 0;
            return mVertices[0].dimension();
        }

        /**
         * @brief      Returns the number of vertices.
         * @return     The number of vertices.
         */
        std::size_t size() const { return mVertices.size(); }

        /**
         * @brief      Returns the type.
         * @return     The type.
         */
        static representation_name type() { return representation_name::polytope_v; }

        /**
         * @brief      Returns whether the polytope has been reduced (i.e. the set of vertices is minimal).
         * @return     True, if the set of vertices is minimal.
         */
        bool reduced() const { return mReduced; }

        /**
         * @brief      Returns the supremum of the set according to the infty norm.
         * @return     The supremum.
         */
        Number supremum() const;

        /// getter for generating rays
        const Rays &rays() const { return mRays; }

        /// setter for generating rays
        void setRays(const Rays &rays) { mRays = rays; }

        void setNeighbors(const Point<Number> &_point, const std::set<Point<Number>> &_neighbors) {
            unsigned pos = 0;
            while (pos < mVertices.size() && (mVertices[pos] != _point)) ++pos;

            if (mVertices[pos] == _point) {
                for (const auto &neighbor: _neighbors) {
                    unsigned nPos = 0;
                    while (nPos < mVertices.size() && (mVertices[nPos] != neighbor)) ++nPos;

                    if (mVertices[nPos] == neighbor) {
                        mNeighbors[pos].insert(nPos);
                        mNeighbors[nPos].insert(pos);
                    }
                }
            }
        }

        void unsafeSetNeighbors(const std::vector<std::set<unsigned>> &_neighbors) { mNeighbors = _neighbors; }

        std::vector<Point<Number>> neighbors(const Point<Number> &_point) const {
            std::vector<Point<Number>> result;
            unsigned pos = 0;
            while (pos < mVertices.size() && (mVertices[pos] != _point)) ++pos;

            if (mVertices[pos] == _point) {
                for (unsigned nPos: mNeighbors[pos]) result.emplace_back(mVertices[nPos]);
            }
            return result;
        }

        typename pointVector::iterator insert(const Point<Number> &i) {
            assert(dimension() == 0 || dimension() == i.dimension());
            mReduced = false;
            auto res = mVertices.insert(mVertices.end(), i);
            mNeighbors.push_back(std::set<unsigned>());
            return res;
        }

        Point<Number> &emplace_back(Point<Number> &&i) {
            assert(dimension() == 0 || dimension() == i.dimension());
            mReduced = false;
            mVertices.emplace_back(std::move(i));
            mNeighbors.push_back(std::set<unsigned>());
            return mVertices.back();
        }

        typename pointVector::iterator insert(const vector_t<Number> &_coord) {
            assert(dimension() == 0 || dimension() == _coord.rows());
            mReduced = false;
            mNeighbors.push_back(std::set<unsigned>());
            return mVertices.insert(mVertices.end(), Point<Number>(_coord));
        }

        typename pointVector::iterator insert(const typename pointVector::const_iterator begin,
                                              const typename pointVector::const_iterator end) {
            assert(dimension() == 0 || dimension() == begin->dimension());
            mReduced = false;
            mNeighbors.push_back(std::set<unsigned>());
            return mVertices.insert(mVertices.end(), begin, end);
        }

        /// getter to the vertices defining this object
        const std::vector<Point<Number>> &
        vertices(const matrix_t<Number> & = matrix_t<Number>::Zero(0, 0)) const { return mVertices; };

        /// getter for a non-const reference to the vertices. Use only if you know what you are doing.
        std::vector<Point<Number>> &rVertices() {
            return mVertices;
        }

        bool hasVertex(const Point<Number> &vertex) const {
            for (const auto point: mVertices) {
                if (point == vertex) return true;
            }
            return false;
        }

        bool hasVertex(const vector_t<Number> &vertex) const { return (mVertices.find(vertex) != mVertices.end()); }

        typename pointVector::iterator begin() { return mVertices.begin(); }

        typename pointVector::const_iterator begin() const { return mVertices.begin(); }

        typename pointVector::iterator end() { return mVertices.end(); }

        typename pointVector::const_iterator end() const { return mVertices.end(); }

        void removeRedundancy();

        template<typename N = Number, carl::DisableIf<is_float<N>> = carl::dummy>
        void reduceNumberRepresentation(std::size_t limit = fReach_DENOMINATOR) const {
            if (!mVertices.empty()) {
                // determine barycenter to set rounding directions
                std::size_t dimension = std::size_t(mVertices.begin()->rawCoordinates().rows());
                vector_t<Number> barycenter = vector_t<Number>::Zero(dimension);
                for (const auto &vertex: mVertices) {
                    barycenter = barycenter + (vertex.rawCoordinates() / Number(mVertices.size()));
                }
                for (auto &vertex: mVertices) {
                    // distance vector to the barycenter - each component now determines its own rounding direction.
                    vector_t<Number> roundingDirections = vertex.rawCoordinates() - barycenter;
                    for (std::size_t d = 0; d < dimension; ++d) {
                        assert(d < vertex.dimension());
                        // determine, which is larger: numerator or denominator
                        Number denom = getDenominator(vertex.at(d));
                        Number num = getNumerator(vertex.at(d));
                        if (denom > limit && carl::abs(num) > limit) {
                            if (denom > num) {
                                Number newNum = num / denom * limit;
                                if (roundingDirections(d) >= 0) {  // round up
                                    newNum = carl::ceil(newNum);
                                    assert(newNum / limit >= vertex.at(d));
                                } else {  // round down
                                    newNum = carl::floor(newNum);
                                    assert(newNum / limit <= vertex.at(d));
                                }
                                vertex[d] = newNum / limit;
                            } else {  // num >= denom
                                Number newDenom = denom / num * limit;
                                if (roundingDirections(d) >= 0) {  // round up
                                    newDenom = carl::floor(newDenom);
                                    assert(limit / newDenom >= vertex.at(d));
                                } else {  // round down
                                    newDenom = carl::ceil(newDenom);
                                    assert(limit / newDenom <= vertex.at(d));
                                }
                                vertex[d] = limit / newDenom;
                            }
                        }
                    }
                }
            }
        }

        template<typename N = Number, carl::EnableIf<is_float<N>> = carl::dummy>
        void reduceNumberRepresentation(unsigned = fReach_DENOMINATOR) const {}

        void updateNeighbors();

        friend std::ostream &operator<<(std::ostream &out, const hypro::VPolytopeT<Number, Converter, S> &lhs) {
            out << "{ ";
            for (const auto &vector: lhs) {
                out << vector << " ";
            }
            out << "} isEmpty: " << lhs.mEmptyState;;
            return out;
        }

    private:
        static bool
        belowPlanes(const vector_t<Number> &vertex, const matrix_t<Number> &normals, const vector_t<Number> &offsets);

        static bool
        abovePlanes(const vector_t<Number> &vertex, const matrix_t<Number> &normals, const vector_t<Number> &offsets);

        template<typename N = Number, carl::DisableIf<std::is_same<N, double>> = carl::dummy>
        static bool
        insidePlanes(const vector_t<Number> &vertex, const matrix_t<Number> &normals, const vector_t<Number> &offsets) {
            for (unsigned rowIndex = 0; rowIndex < normals.rows(); ++rowIndex) {
                if (vertex.dot(normals.row(rowIndex)) != offsets(rowIndex)) {
                    return false;
                }
            }
            return true;
        }

        template<typename N = Number, carl::EnableIf<std::is_same<N, double>> = carl::dummy>
        static bool
        insidePlanes(const vector_t<double> &vertex, const matrix_t<double> &normals, const vector_t<double> &offsets) {
            for (unsigned rowIndex = 0; rowIndex < normals.rows(); ++rowIndex) {
                // compare with tolerance of 128 ULPs.
                if (!carl::AlmostEqual2sComplement(vertex.dot(normals.row(rowIndex)), offsets(rowIndex),
                                                   default_double_comparison_ulps)) {
                    DEBUG("hypro.representations.vpolytope",
                          "Values " << vertex.dot(normals.row(rowIndex)) << " and " << offsets(rowIndex)
                                    << " are not equal.");
                    return false;
                }
            }
            return true;
        }

    public:
        VPolytopeT<Number, Converter, S> &operator=(const VPolytopeT<Number, Converter, S> &rhs) = default;

        VPolytopeT<Number, Converter, S> &operator=(VPolytopeT<Number, Converter, S> &&rhs) = default;

        bool operator==(const VPolytopeT<Number, Converter, S> &rhs) const;
    };

/** @} */

    template<typename From, typename To, typename Converter, typename S>
    VPolytopeT<To, Converter, S> convert(const VPolytopeT<From, Converter, S> &in) {
        std::vector<Point<To>> convertedVertices;
        for (const auto &vertex: in.vertices()) {
            convertedVertices.push_back(Point<To>(convert<From, To>(vertex.rawCoordinates())));
        }
        return VPolytopeT<To, Converter, S>(convertedVertices);
    }

}  // namespace hypro

#include "VPolytope.tpp"
