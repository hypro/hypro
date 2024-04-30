/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * @file   VPolytope.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-02-25
 * @version 2014-02-25
 */

#include "VPolytope.h"

#include <algorithm>

namespace hypro {
    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>::VPolytopeT()
            : GeometricObjectBase(SETSTATE::EMPTY), mVertices(), mReduced(true), mNeighbors() {
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>::VPolytopeT(const Point<Number> &point)
            : GeometricObjectBase(SETSTATE::NONEMPTY) {
        mVertices.push_back(point);
        mReduced = true;
        mNeighbors.push_back(std::set<unsigned>());
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>::VPolytopeT(const pointVector &points)
            : GeometricObjectBase(SETSTATE::NONEMPTY) {
        for (const auto point: points) {
            if (std::find(mVertices.begin(), mVertices.end(), point) == mVertices.end()) {
                mVertices.push_back(point);
                mNeighbors.push_back(std::set<unsigned>());
            }
        }
        mReduced = false;
        reduceNumberRepresentation();
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>::VPolytopeT(const std::vector<vector_t<Number>> &rawPoints)
            : GeometricObjectBase(SETSTATE::NONEMPTY) {
        for (const auto point: rawPoints) {
            Point<Number> tmpPoint(point);
            if (std::find(mVertices.begin(), mVertices.end(), tmpPoint) == mVertices.end()) {
                mVertices.push_back(tmpPoint);
                mNeighbors.push_back(std::set<unsigned>());
            }
        }
        mReduced = false;
        reduceNumberRepresentation();
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>::VPolytopeT(const matrix_t<Number> &_constraints,
                                                 const vector_t<Number> _constants) {
        if constexpr (is_exact<Number>) {
            // check consistency, i.e., if the polytope potentially is empty
            // TODO ensure that this is robust
            {
                TRACE("hypro.representations.vpolytope", "Check for emptiness.");
#ifdef HYPRO_USE_Z3
                bool isEmpty = !z3CheckConsistency(_constraints, _constants,
                                                   std::vector<carl::Relation>(_constraints.rows(),
                                                                               carl::Relation::LEQ));
                if (isEmpty) {
                    TRACE("hypro.representations.vpolytope",
                          "Construction from matrix and vector produced an empty polytope.");
                    this->mEmptyState = SETSTATE::EMPTY;
                    this->mReduced = true;
                    return;
                }
#else
                auto opt = hypro::Optimizer<Number>(_constraints, _constants);
                if (!opt.checkConsistency()) {
                    TRACE("hypro.representations.vpolytope",
                          "Construction from matrix and vector produced an empty polytope.");
                    this->mEmptyState = SETSTATE::EMPTY;
                    this->mReduced = true;
                    return;
                }
                auto internalPoint = opt.getInternalPoint();
                if (internalPoint.errorCode == SOLUTION::INFEAS) {
                    TRACE("hypro.representations.vpolytope",
                          "Construction from matrix and vector does not contain any point (INFEAS), create empty polytope.");
                    this->mEmptyState = SETSTATE::EMPTY;
                    this->mReduced = true;
                    return;
                }
#endif
            }

            auto dimension = _constraints.cols();
            typename QuickIntersection<Number>::pointVector_t inputHalfspaces;

            for (int i = 0; i < _constraints.rows(); ++i) {
                inputHalfspaces.emplace_back(dimension + 1);
                inputHalfspaces.back().head(dimension) = _constraints.row(i);
                inputHalfspaces.back()[dimension] = -_constants[i];
            }
            TRACE("hypro.representations.vpolytope",
                  "Construct VPolytope from " << _constraints << " <= " << _constants);
            QuickIntersection<Number> qInt{inputHalfspaces, (size_t) dimension};
            qInt.compute();

            for (auto &facet: qInt.getFacets()) {
                if (facet.mOffset == 0) {
                    TRACE("hypro.representations.vpolytope",
                          "The facet normal was zero, as we understand this yields the empty polytope");
                    *this = Empty();
                    return;
                }
                facet.mNormal /= -facet.mOffset;
                mVertices.emplace_back(Point(std::move(facet.mNormal)));
            }
        } else {
            // calculate all possible Halfspace intersections
            TRACE("hypro.representations.vpolytope", "Construct from " << _constraints << " <= " << _constants);
            // std::cout << __func__ << ": matrix: " << _constraints << " and vector: " << _constants << std::endl;
            assert(_constraints.rows() == _constants.rows());
            Permutator permutator = Permutator(_constraints.rows(), _constraints.cols());
            matrix_t<Number> intersection = matrix_t<Number>(_constraints.cols(), _constraints.cols());
            vector_t<Number> intersectionConstants = vector_t<Number>(_constraints.cols());
            std::set<vector_t<Number>> possibleVertices;
            std::vector<std::size_t> permutation;
            while (!permutator.end()) {
                permutation = permutator();
                unsigned rowCount = 0;
                // std::cout << "Intersect :" << std::endl;
                for (const auto &rowIndex: permutation) {
                    // std::cout << _constraints.row(rowIndex) << " <= " <<
                    // _constants(rowIndex) << std::endl;
                    assert(rowCount < _constraints.cols());
                    intersection.row(rowCount) = _constraints.row(rowIndex);
                    intersectionConstants(rowCount) = _constants(rowIndex);
                    ++rowCount;
                }
                // check if rank is full
                if (intersection.fullPivLu().rank() == intersection.cols()) {
                    vector_t<Number> vertex = intersection.fullPivLu().solve(intersectionConstants);
                    assert(vertex.rows() == _constraints.cols());
                    // assert(insidePlanes(vertex, intersection, intersectionConstants));
                    //  avoid duplicate entries
                    if (std::find(possibleVertices.begin(), possibleVertices.end(), vertex) == possibleVertices.end()) {
                        possibleVertices.emplace(std::move(vertex));
                    }
                }
            }
            TRACE("hypro.representations.vpolytope", ": Computed " << possibleVertices.size() << " possible vertices.");

            // check if vertices are true vertices (i.e. they fulfill all constraints)
            for (auto vertex = possibleVertices.begin(); vertex != possibleVertices.end();) {
                // std::cout<<__func__ << " : " <<__LINE__ << " current position : " << i <<
                // std::endl;
                // std::cout<<__func__ << " : " <<__LINE__ << "number of vertices : " <<
                // possibleVertices.size() << std::endl;
                bool deleted = false;
                for (unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
                    Number res = vertex->dot(_constraints.row(rowIndex));
                    if (!carl::AlmostEqual2sComplement(res, _constants(rowIndex), default_double_comparison_ulps) &&
                        res > _constants(rowIndex)) {
                        vertex = possibleVertices.erase(vertex);
                        deleted = true;
                        break;
                    }
                }
                if (!deleted) {
                    ++vertex;
                }
            }

            TRACE("hypro.representations.vpolytope",
                  "Deleted vertices. Remaining " << possibleVertices.size() << " vertices.");

            // std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
            // finish initialization
            for (const auto &point: possibleVertices) {
                mVertices.emplace_back(point);
                mNeighbors.push_back(std::set<unsigned>());
                // std::cout << "Real vertex " << point.transpose() << std::endl;
            }
            // std::cout<<__func__ << " : " <<__LINE__ <<std::endl;
            mReduced = false;

            // reduceNumberRepresentation();
        }
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::projectOut(const std::vector<std::size_t> &dimensions) const {
        if (dimensions.empty()) {
            return *this;
        }

        std::vector<Point<Number>> projectedVertices;
        for (const auto &vertex: mVertices) {
            projectedVertices.emplace_back(vertex.projectOut(dimensions));
        }

        return VPolytopeT<Number, Converter, S>(projectedVertices);
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::projectOn(const std::vector<std::size_t> &dimensions) const {
        if (dimensions.empty()) {
            return Empty();
        }

        std::vector<Point<Number>> projectedVertices;
        for (const auto &vertex: mVertices) {
            projectedVertices.emplace_back(vertex.projectOn(dimensions));
        }

        return VPolytopeT<Number, Converter, S>(projectedVertices);
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::linearTransformation(const matrix_t<Number> &A) const {
        // std::cout << __func__ << " A: " << A << ", b: " << b << std::endl;
        VPolytopeT<Number, Converter, S> result;
        for (const auto &vertex: mVertices) {
            Point<Number> tmp{vertex.linearTransformation(A)};
            if (std::find(result.begin(), result.end(), tmp) == result.end()) {
                result.emplace_back(std::move(tmp));
            }
        }
        result.unsafeSetNeighbors(mNeighbors);
        return result;
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S> VPolytopeT<Number, Converter, S>::affineTransformation(const matrix_t<Number> &A,
                                                                                            const vector_t<Number> &b) const {
        // std::cout << __func__ << " A: " << A << ", b: " << b << std::endl;
        VPolytopeT<Number, Converter, S> result;
        for (const auto &vertex: mVertices) {
            Point<Number> tmp{vertex.affineTransformation(A, b)};
            if (std::find(result.begin(), result.end(), tmp) == result.end()) {
                result.emplace_back(std::move(tmp));
            }
        }
        result.unsafeSetNeighbors(mNeighbors);
        return result;
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::minkowskiSum(const VPolytopeT<Number, Converter, S> &rhs) const {
        if (this->empty() || rhs.empty()) {
            return Empty();
        }
        VPolytopeT<Number, Converter, S> result;
        // add each rhs-vertex to each vertex of this polytope.
        for (auto lhsVertex: mVertices) {
            for (auto rhsVertex: rhs.mVertices) {
                result.insert(lhsVertex + rhsVertex);
            }
        }
        return result;
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::intersect(const VPolytopeT<Number, Converter, S> &rhs) const {
        // create a set of possible points via combination of all coordinates
        if (rhs.size() == 0) {
            return VPolytopeT<Number, Converter, S>();
        } else {
            pointVector possibleVertices;
            for (const auto &lhsVertex: mVertices) {
                possibleVertices.push_back(lhsVertex);
                for (unsigned coordIndex = 0; coordIndex < lhsVertex.rawCoordinates().rows(); ++coordIndex) {
                    for (const auto &rhsVertex: rhs.mVertices) {
                        vector_t<Number> newVertex = rhsVertex.rawCoordinates();
                        newVertex(coordIndex) = lhsVertex.at(coordIndex);
                        possibleVertices.push_back(Point<Number>(newVertex));
                        possibleVertices.push_back(Point<Number>(rhsVertex.rawCoordinates()));
                    }
                }
            }
            // remove all vertices, which are only contained in one of the polytopes
            for (auto vertexIt = possibleVertices.begin(); vertexIt != possibleVertices.end();) {
                if (!(this->contains(*vertexIt) && rhs.contains(*vertexIt))) {
                    vertexIt = possibleVertices.erase(vertexIt);
                } else {
                    ++vertexIt;
                }
            }
            return VPolytopeT<Number, Converter, S>(std::move(possibleVertices));
        }
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::intersectHalfspace(const Halfspace<Number> &rhs) const {
        auto intermediate = Converter::toHPolytope(*this);
        auto intersection = intermediate.intersectHalfspace(rhs);
        // intersection.removeRedundancy();
        VPolytopeT<Number, Converter, S> res(Converter::toVPolytope(intersection));
        return res;
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S> VPolytopeT<Number, Converter, S>::intersectHalfspaces(const matrix_t<Number> &_mat,
                                                                                           const vector_t<Number> &_vec) const {
        auto intermediate = Converter::toHPolytope(*this);
        auto intersection = intermediate.intersectHalfspaces(_mat, _vec);
        // intersection.removeRedundancy();
        VPolytopeT<Number, Converter, S> res(Converter::toVPolytope(intersection));
        return res;
    }

    template<typename Number, typename Converter, typename S>
    std::pair<CONTAINMENT, VPolytopeT<Number, Converter, S>>
    VPolytopeT<Number, Converter, S>::satisfiesHalfspace(const Halfspace<Number> &rhs) const {
        // if we want to have fast pre-checks, this is the time to do them
        if (S::checkVerticesBeforeConversion) {
            // we count the number of vertices satisfying the halfspace to get a first impression about the result type.
            std::size_t numberVerticesInRhs = numberOfPointsInHalfspace(mVertices, rhs);
            // no vertex is contained - the result will be empty.
            if (numberVerticesInRhs == 0) {
                COUNT("VPolyAvoidConversion");
                return std::make_pair(CONTAINMENT::NO, VPolytopeT<Number, Converter, S>::Empty());
            } else if (numberVerticesInRhs == mVertices.size()) {
                // all vertices are contained - the full set is the result.
                COUNT("VPolyAvoidConversion");
                return std::make_pair(CONTAINMENT::FULL, *this);
            }
        }

        auto intermediate = Converter::toHPolytope(*this);
        auto resultPair = intermediate.satisfiesHalfspace(rhs);
        if (resultPair.first != CONTAINMENT::NO) {
            // resultPair.second.removeRedundancy();
            VPolytopeT<Number, Converter, S> res(Converter::toVPolytope(resultPair.second));
            return std::make_pair(resultPair.first, std::move(res));
        }
        return std::make_pair(resultPair.first, std::move(VPolytopeT<Number, Converter, S>::Empty()));
    }

    template<typename Number, typename Converter, typename S>
    std::pair<CONTAINMENT, VPolytopeT<Number, Converter, S>>
    VPolytopeT<Number, Converter, S>::satisfiesHalfspaces(const matrix_t<Number> &_mat,
                                                          const vector_t<Number> &_vec) const {
        // this stores results from pre-checks to reduce the effort of intersections later, if applicable.
        std::vector<Eigen::Index> halfspacesToAvoid;
        if (S::checkVerticesBeforeConversion) {
            // we check for each halfspace individually to allow for premature exiting and reductions.
            for (Eigen::Index rowIndex = 0; rowIndex < _mat.rows(); ++rowIndex) {
                // we count the number of vertices satisfying the halfspace to get a first impression about the result type.
                std::size_t numberVerticesInRhs = numberOfPointsInHalfspace(mVertices,
                                                                            Halfspace<Number>(_mat.row(rowIndex),
                                                                                              _vec(rowIndex)));
                // no vertex is contained - the result will be empty.
                if (numberVerticesInRhs == 0) {
                    COUNT("VPolyAvoidConversion");
                    return std::make_pair(CONTAINMENT::NO, VPolytopeT<Number, Converter, S>::Empty());
                } else if (numberVerticesInRhs == mVertices.size()) {
                    // all vertices are contained - the full set is the result for this halfspace, we can avoid it.
                    halfspacesToAvoid.push_back(rowIndex);
                }
            }
            // none of the halfspaces cuts the set - return full set.
            if (halfspacesToAvoid.size() == std::size_t(_mat.rows())) {
                COUNT("VPolyAvoidConversion");
                return std::make_pair(CONTAINMENT::FULL, *this);
            }
        }

        auto intermediate = Converter::toHPolytope(*this);
        intermediate.reduceNumberRepresentation(mVertices);
        // std::cout << typeid(*this).name() << "::" << __func__ << ": Intermediate hpoly: " << intermediate << std::endl;
        auto resultPair = intermediate.satisfiesHalfspaces(removeRows(_mat, halfspacesToAvoid),
                                                           removeRows(_vec, halfspacesToAvoid));
        if (resultPair.first != CONTAINMENT::NO) {
            // resultPair.second.removeRedundancy();
            assert(!resultPair.second.empty());
            TRACE("hypro.representations.vpolytope", ": Intermediate hpoly convert back: " << resultPair.second);
            VPolytopeT<Number, Converter, S> res(Converter::toVPolytope(resultPair.second));
            TRACE("hypro.representations.vpolytope", "Re-Converted v-poly: " << res);
            assert(!res.empty());
            return std::make_pair(resultPair.first, std::move(res));
        }
        return std::make_pair(resultPair.first, std::move(VPolytopeT<Number, Converter, S>::Empty()));
    }

    template<typename Number, typename Converter, typename S>
    bool VPolytopeT<Number, Converter, S>::contains(const Point<Number> &point) const {
        return this->contains(point.rawCoordinates());
    }

    template<typename Number, typename Converter, typename S>
    bool VPolytopeT<Number, Converter, S>::contains(const vector_t<Number> &vec) const {
        if (this->empty()) {
            return false;
        }
        // quick check for vertices
        if (std::any_of(mVertices.begin(), mVertices.end(),
                        [&vec](const auto &vertex) { return is_approx_equal(vertex.rawCoordinates(), vec); })) {
            return true;
        }
        // check for containment on facets or inside the polytope
        if (S::useLpForPointContainment) {
            // create LP  Ax = b to solve whether vec can be represented as a convex combination of the vertices.
            // 1 create matrix from vertices.
            // 2 use vec as b
            // 3 set bounds for cols to [0,1]
            // 4 add constraint stating that all col-values need to sum up to 1.

            // 1 create matrix
            matrix_t<Number> A = matrix_t<Number>(this->dimension(), mVertices.size());
            for (Eigen::Index i = 0; i < A.cols(); ++i) {
                A.col(i) = mVertices[i].rawCoordinates();
            }

            Optimizer<Number> opt(A, vec);

            // 3 bound cols
            for (Eigen::Index i = 0; i < A.cols(); ++i) {
                vector_t<Number> constraint = vector_t<Number>::Zero(A.cols());
                constraint(i) = 1;
                opt.addConstraint(constraint, 1, carl::Relation::LEQ);
                opt.addConstraint(constraint, 0, carl::Relation::GEQ);
            }

            // 4 add constraint that all coefficients add up to 1
            vector_t<Number> constraint = vector_t<Number>::Ones(A.cols());
            opt.addConstraint(constraint, 1, carl::Relation::EQ);

            // Check that the point can be represented (EQ).
            opt.setRelations(std::vector<carl::Relation>(this->dimension(), carl::Relation::EQ));

            return opt.checkConsistency();

        } else {
            // check via conversion
            auto tmpHPoly = Converter::toHPolytope(*this);
            return tmpHPoly.contains(vec);
        }
    }

    template<typename Number, typename Converter, typename S>
    bool VPolytopeT<Number, Converter, S>::contains(const VPolytopeT<Number, Converter, S> &_other) const {
        for (const auto &vertex: _other.vertices()) {
            if (!this->contains(vertex)) {
                return false;
            }
        }
        return true;
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::unite(const VPolytopeT<Number, Converter, S> &rhs) const {
        if (rhs.dimension() == 0) {
            return VPolytopeT<Number, Converter, S>(mVertices);
        } else {
            VPolytopeT<Number, Converter, S> result;
            // std::cout << __func__ << " : of " << *this << " and " << rhs << std::endl;
            VPolytopeT<Number, Converter, S>::pointVector points;

            std::set<Point<Number>> pointSet;
            pointSet.insert(this->mVertices.begin(), this->mVertices.end());
            pointSet.insert(rhs.mVertices.begin(), rhs.mVertices.end());

            if (pointSet.empty()) {
                return VPolytopeT<Number, Converter, S>();
            }

            unsigned effDim = unsigned(effectiveDimension(pointSet));
            points.insert(points.end(), pointSet.begin(), pointSet.end());
            assert(!points.empty());
            TRACE("hypro.representations.vpolytope",
                  "Effective dimension: " << effDim << ", points dimension: " << points.begin()->dimension());

            if (effDim < points.begin()->dimension()) {
                // TODO: We can optimize this here.
                return VPolytopeT<Number, Converter, S>(points);
            } else if (points.size() > points.begin()->dimension()) {
                TRACE("hypro.representations.vpolytope", "Using convex hull algorithm to reduce point set.");
                std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull(points).first;
                std::set<Point<Number>> preresult;
                for (unsigned i = 0; i < facets.size(); i++) {
                    for (unsigned j = 0; j < facets[i]->vertices().size(); j++) {
                        preresult.insert(facets[i]->vertices().at(j));
                    }
                }
                VPolytopeT<Number, Converter, S>::pointVector res;
                for (const auto &point: preresult) {
                    res.push_back(point);
                }
                result = VPolytopeT<Number, Converter, S>(res);
            } else {
                result = VPolytopeT<Number, Converter, S>(points);
            }

            // assert(result.contains(*this));
            // assert(result.contains(rhs));

            return result;
        }
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S> VPolytopeT<Number, Converter, S>::unite(const std::vector<VPolytopeT> &rhs) {
        if (rhs.size() == 0) {
            return VPolytopeT<Number, Converter, S>::Empty();
        } else {
            VPolytopeT<Number, Converter, S> result;
            // std::cout << __func__ << " : of " << *this << " and " << rhs << std::endl;
            VPolytopeT<Number, Converter, S>::pointVector points;

            std::set<Point<Number>> pointSet;
            for (const auto &poly: rhs) {
                pointSet.insert(rhs.mVertices.begin(), rhs.mVertices.end());
            }

            if (pointSet.empty()) {
                return VPolytopeT<Number, Converter, S>();
            }

            unsigned effDim = unsigned(effectiveDimension(pointSet));
            points.insert(points.end(), pointSet.begin(), pointSet.end());
            assert(!points.empty());

            if (effDim < points.begin()->dimension()) {
                pointSet.clear();
                std::vector<Halfspace<Number>> orientedHalfspaces = computeOrientedBox(points);
                // std::cout << "Box has " << orientedHalfspaces.size() << " halfspaces in dimension " << points.begin()->dimension() << std::endl;
                // assert(orientedHalfspaces.size() == points.begin()->dimension());

                // vertex computation of the oriented box
                unsigned dim = points.begin()->dimension();
                Permutator permutator(orientedHalfspaces.size(), dim);
                std::vector<std::size_t> permutation;
                while (!permutator.end()) {
                    permutation = permutator();

                    matrix_t<Number> A(dim, dim);
                    vector_t<Number> b(dim);
                    unsigned pos = 0;
                    for (auto planeIt = permutation.begin(); planeIt != permutation.end(); ++planeIt) {
                        A.row(pos) = orientedHalfspaces.at(*planeIt).normal().transpose();
                        b(pos) = orientedHalfspaces.at(*planeIt).offset();
                        ++pos;
                    }
                    Eigen::FullPivLU<matrix_t<Number>> lu_decomp(A);
                    if (lu_decomp.rank() < A.rows()) {
                        continue;
                    }

                    vector_t<Number> res = lu_decomp.solve(b);

                    // Check if the computed vertex is a real vertex
                    bool outside = false;
                    for (unsigned planePos = 0; planePos < orientedHalfspaces.size(); ++planePos) {
                        bool skip = false;
                        for (unsigned permPos = 0; permPos < permutation.size(); ++permPos) {
                            if (planePos == permutation.at(permPos)) {
                                skip = true;
                                break;
                            }
                        }

                        if (!skip) {
                            if (orientedHalfspaces.at(planePos).offset() -
                                orientedHalfspaces.at(planePos).normal().dot(res) < 0) {
                                // std::cout << "Drop vertex: " << res << " because of plane " << planePos << std::endl;
                                outside = true;
                                break;
                            }
                        }
                    }
                    if (!outside) {
                        pointSet.emplace(res);
                    }
                }
                for (const auto &point: pointSet) {
                    result.insert(point);
                }
            } else if (points.size() > points.begin()->dimension()) {
                std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull(points).first;
                std::set<Point<Number>> preresult;
                for (unsigned i = 0; i < facets.size(); i++) {
                    for (unsigned j = 0; j < facets[i]->vertices().size(); j++) {
                        preresult.insert(facets[i]->vertices().at(j));
                    }
                }
                VPolytopeT<Number, Converter, S>::pointVector res;
                for (const auto &point: preresult) {
                    res.push_back(point);
                }
                result = VPolytopeT<Number, Converter, S>(res);
            } else {
                result = VPolytopeT<Number, Converter, S>(points);
            }
            // assert(result.contains(*this));
            return result;
        }
    }

    template<typename Number, typename Converter, typename S>
    void VPolytopeT<Number, Converter, S>::clear() {
        mVertices.clear();
        mEmptyState = SETSTATE::EMPTY;
    }

    template<typename Number, typename Converter, typename S>
    EvaluationResult<Number> VPolytopeT<Number, Converter, S>::evaluate(const vector_t<Number> &direction) const {
        if (direction == vector_t<Number>::Zero(direction.rows()))
            return EvaluationResult<Number>();
        Number maxDist = Number(-1e20);
        std::size_t vIndex = 0;
        EvaluationResult<Number> res;
        for (std::size_t i = 0; i < mVertices.size(); ++i) {
            // Point with the furthest distance to the direction vector is the optimal point and is always a corner
            Number dist = direction.dot(mVertices[i].rawCoordinates());
            if (dist > maxDist) {
                maxDist = dist;
                vIndex = i;
            }
        }
        res.optimumValue = mVertices[vIndex].rawCoordinates();
        res.supportValue = Number(maxDist);
        res.errorCode = SOLUTION::FEAS;
        return res;
    }

    template<typename Number, typename Converter, typename S>
    std::vector<EvaluationResult<Number>>
    VPolytopeT<Number, Converter, S>::multiEvaluate(const matrix_t<Number> &directions, bool) const {
        if (directions == matrix_t<Number>::Zero(directions.rows(), directions.cols()))
            return std::vector<EvaluationResult<Number>>();
        std::vector<EvaluationResult<Number>> allRes;
        for (int i = 0; i < directions.rows(); ++i) {
            EvaluationResult<Number> res = evaluate(directions.row(i));
            allRes.emplace_back(res);
        }
        return allRes;
    }

    template<typename Number, typename Converter, typename S>
    Number VPolytopeT<Number, Converter, S>::supremum() const {
        Number max = 0;
        for (auto &point: mVertices) {
            Number inftyNorm = Point<Number>::inftyNorm(point);
            max = max > inftyNorm ? max : inftyNorm;
        }
        return max;
    }

    template<typename Number, typename Converter, typename S>
    void VPolytopeT<Number, Converter, S>::removeRedundancy() {
        if (!mReduced && !this->empty()) {
#ifdef USE_SMTRAT
            std::set<Point<Number>> toDelete;
            smtrat::SimplexSolver simplex;
            simplex.push();

            // create mapping of variables (lambdas') to vertices.
            std::map<Point<Number>, carl::Variable> lambdas;
            for ( const auto& vertex : mVertices ) {
                carl::Variable lambda = freshRealVariable();
                lambdas.insert( std::make_pair( vertex, lambda ) );
                // std::cout << "Assigned " << lambdas.find(vertex)->second << " to " << lambdas.find(vertex)->first << std::endl;
            }

            for ( auto currVertex = mVertices.begin(); currVertex != mVertices.end(); ) {
                // std::cout << currVertex << ": " << std::endl;
                //  create constraint for Sum(lambdas) == 1
                carl::MultivariatePolynomial<smtrat::Rational> sumBound;
                for ( const auto& vertex : mVertices ) {
                    if ( vertex != *currVertex ) {
                        carl::Variable lambda = lambdas.find( vertex )->second;
                        sumBound += lambda;
                        smtrat::FormulaT constr = smtrat::FormulaT( carl::MultivariatePolynomial<smtrat::Rational>( lambda ), carl::Relation::GEQ );
                        simplex.inform( constr );
                        simplex.add( constr );
                    }
                }
                sumBound -= smtrat::Rational( 1 );
                smtrat::FormulaT constr = smtrat::FormulaT( sumBound, carl::Relation::EQ );
                simplex.inform( constr );
                simplex.add( constr );

                for ( unsigned dim = 0; dim < this->dimension(); ++dim ) {
                    carl::MultivariatePolynomial<smtrat::Rational> row;
                    for ( const auto& vertex : mVertices ) {
                        if ( *currVertex != vertex ) {
                            carl::Variable tmp = lambdas.find( vertex )->second;
                            row += tmp * carl::convert<Number, smtrat::Rational>( vertex.at( dim ) );
                        } else {
                            row -= carl::convert<Number, smtrat::Rational>( vertex.at( dim ) );
                        }
                    }
                    smtrat::FormulaT constr = smtrat::FormulaT( row, carl::Relation::EQ );
                    // std::cout << constr << std::endl;
                    simplex.inform( constr );
                    simplex.add( constr );
                }

                // std::cout << "Checking: " << std::endl << simplex.formula().toString() << std::endl;

                smtrat::Answer res = simplex.check();

                if ( res == smtrat::Answer::SAT ) {
                    currVertex = mVertices.erase( currVertex );
                } else {
                    ++currVertex;
                }

                // std::cout << "Is extreme point: " << (res == smtrat::Answer::UNSAT) << std::endl << std::endl << std::endl << std::endl;
                simplex.pop();
                simplex.push();
            }
#else
            mVertices = removeRedundantPoints(mVertices);
#endif
        }
        mReduced = true;
    }

    template<typename Number, typename Converter, typename S>
    void VPolytopeT<Number, Converter, S>::updateNeighbors() {
        // std::map<Point<Number>, std::set<Point<Number>>> neighbors = convexHull( mVertices ).second;
        // mVertices.clear();
        // for ( const auto &pointNeighborsPair : neighbors ) {
        // 	mVertices.push_back( pointNeighborsPair.first );
        // }
        // // we can only set neighbors after all points have been inserted.
        // for ( const auto &pointNeighborsPair : neighbors ) {
        // 	this->setNeighbors( pointNeighborsPair.first, pointNeighborsPair.second );
        // }
        mReduced = true;
    }

    template<typename Number, typename Converter, typename S>
    VPolytopeT<Number, Converter, S>
    VPolytopeT<Number, Converter, S>::getTimeProjection() const {
        // we assume the last dimension is the time, because the time variable is added automatically at the begining of the analysis and not in the model file.
        std::vector<std::size_t> dimensions;
        dimensions.emplace_back(this->dimension()-1);
        assert(dimensions.size() == 1);
        auto result = projectOn(dimensions);
        result.removeRedundancy();
        return result;
    }

/***************************************************************************
 * Auxiliary functions
 **************************************************************************/

    template<typename Number, typename Converter, typename S>
    bool VPolytopeT<Number, Converter, S>::belowPlanes(const vector_t<Number> &vertex, const matrix_t<Number> &normals,
                                                       const vector_t<Number> &offsets) {
        for (unsigned rowIndex = 0; rowIndex < normals.rows(); ++rowIndex) {
            if (vertex.dot(normals.row(rowIndex)) > offsets(rowIndex)) {
                return false;
            }
        }
        return true;
    }

    template<typename Number, typename Converter, typename S>
    bool VPolytopeT<Number, Converter, S>::abovePlanes(const vector_t<Number> &vertex, const matrix_t<Number> &normals,
                                                       const vector_t<Number> &offsets) {
        for (unsigned rowIndex = 0; rowIndex < normals.rows(); ++rowIndex) {
            if (vertex.dot(normals.row(rowIndex)) < offsets(rowIndex)) {
                return false;
            }
        }
        return true;
    }

    template<typename Number, typename Converter, typename S>
    bool VPolytopeT<Number, Converter, S>::operator==(const VPolytopeT<Number, Converter, S> &rhs) const {
        if (this->dimension() != rhs.dimension()) return false;

        // TODO: Highly inefficient!!!
        for (auto &lPoint: this->vertices()) {
            if (!rhs.hasVertex(lPoint)) return false;
        }
        for (auto &rPoint: rhs.vertices()) {
            if (!this->hasVertex(rPoint)) return false;
        }
        return true;
    }

}  // namespace hypro
