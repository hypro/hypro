/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * @file HPolytope.h
 * \example example_HPolytope.cpp
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../../algorithms/quantifierElimination/qe.h"
#include "../../../algorithms/quickhull/Quickhull.h"
#include "../../../types.h"
#include "../../../util/convexHull.h"
#include "../../../util/linearOptimization/Optimizer.h"
#include "../../../util/sequenceGeneration/SequenceGenerator.h"
#include "../../../util/templateDirections.h"
#include "../../../util/typetraits.h"
#include "HPolytopeSetting.h"
#include "delegates.h"

#ifdef HYPRO_USE_SERIALIZATION

#include <cereal/archives/json.hpp>

#endif

#ifdef HYPRO_USE_DD_METHOD

#include "../../../algorithms/doubledescription/doubleDescription.h"

#endif

#include <algorithm>
#include <cassert>
#include <optional>

namespace hypro {

    template<typename Number>
    class Location;

/**
 * @brief      Class for a H-polytope.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 * \ingroup geoState @{
 */
    template<typename Number, typename Converter, class Setting>
    class HPolytopeT : private GeometricObjectBase {
    public:
        enum REDUCTION_STRATEGY {
            DROP = 0,
            DROP_SMOOTH,
            UNITE,
            UNITE_SMOOTH,
            UNITE_CUT,
            UNITE_NORM,
            DIRECTED_SMALL,
            DIRECTED_BIG,
            DIRECTED_TEMPLATE
        };

        using HalfspaceVector = std::vector<Halfspace<Number>>;

        typedef Setting Settings;
        typedef Number NumberType;
        static constexpr auto type_enum = representation_name::polytope_h;

    private:
        mutable HalfspaceVector mHPlanes;                                                 ///< halfspaces defining the polytope
        std::size_t mDimension;                                                             ///< cache for the state space dimension
        mutable bool mNonRedundant;                                                         ///< cache for redundancy information
        mutable std::optional<Optimizer<Number>> mOptimizer = std::nullopt;                 ///< optional cache (settings-dependent) for an LP instance
        mutable bool mUpdated = false;                                                     ///< cache flag to mark a required update of the optional LP instance
        mutable std::optional<std::vector<carl::Interval<Number>>> mBox = std::nullopt;     ///< cache of the bounding box

    public:
        /**
         * @brief Constructor for the universal H-polytope.
         */
        HPolytopeT();

        /**
         * @brief Copy constructor.
         * @param orig Original H-polytope.
         */
        // HPolytopeT( const HPolytopeT& orig ) = default;
        HPolytopeT(const HPolytopeT &orig);

        template<typename M, typename C, typename S, carl::DisableIf<std::is_same<M, Number>> = carl::dummy>
        HPolytopeT(const HPolytopeT<M, C, S> &in) {
            HalfspaceVector convertedSpaces;
            std::transform(in.constraints().begin(), in.constraints().end(), std::back_inserter(convertedSpaces),
                           [&](const auto &constraint) {
                               return Halfspace<Number>(convert<M, Number>(constraint.normal()),
                                                        carl::convert<M, Number>(constraint.offset()));
                           });
            *this = HPolytopeT(convertedSpaces);
        }

        /**
         * @brief Constructor from a vector of halfspaces.
         * @details The resulting object is the intersection of the given halfspaces, i.e. the conjunction of the linear
         * constraints representing the halfspaces.
         * @param planes A vector of halfspaces.
         */
        HPolytopeT(const HalfspaceVector &planes);

        /**
         * @brief Constructor from a matrix and a vector.
         * @details Each row in the matrix is considered to represent a constraint, i.e. a normal to a bounding hyperplane.
         * Each corresponding entry in the passed vector is the offset of that plane, i.e. the constant part of the linear
         * constraint.
         * @param A A matrix.
         * @param b A vector.
         */
        HPolytopeT(const matrix_t<Number> &A, const vector_t<Number> &b);

        /**
         * @brief Constructor from a matrix.
         * @details Each row in the matrix is considered to represent a constraint, i.e. a normal to a bounding hyperplane.
         * The offset of each plane is considered to be 0, i.e. if the number of affinely independent constraints
         * is larger or equal to d+1, the resulting polytope represents the origin point.
         * @param A A matrix.
         */
        HPolytopeT(const matrix_t<Number> &A);

        /**
         * @brief Construct a new HPolytopeT object from a single point
         * @param point
         */
        HPolytopeT(const Point<Number> &point);

        /**
         * @brief Constructor from a vector of points.
         * @details Converts a vertex-representation into a hyperplanar representation, i.e. solving the plane enumeration
         * problem.
         * @param points A vector of points.
         */
        HPolytopeT(const std::vector<Point<Number>> &points);

        /// Settings conversion constructor
        template<typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
        HPolytopeT(const HPolytopeT<Number, Converter, SettingRhs> &orig);

        /**
         * @brief Destructor.
         */
        ~HPolytopeT();

        /**
         * @brief Approximates the storage usage of the current polytope.
         * @details [long description]
         * @return The size.
         */
        double sizeOfHPolytopeT() const {
            return sizeof(*this) + this->mHPlanes.size() * this->mHPlanes.at(0).sizeOfHalfspace();
        }

        /**
         * @brief Determines, if the polytope is empty.
         * @details Checks for satisfiability of the given constraints.
         * @return True if the polytope is empty, false otherwise.
         */
        bool empty() const;

        /**
         * @brief Static method for construction of an empty H-polytope.
         * @details An empty H-polytope is constructed by creating two hyperplanes which falsify each other.
         * @return An empty polytope.
         */
        static HPolytopeT<Number, Converter, Setting> Empty();

        /**
         * @brief Getter for the dimension of the polytope.
         * @details Note that this only returns the space dimension and not the effective dimension of the polytope.
         * @return The space dimension.
         */
        std::size_t dimension() const;

        /**
         * @brief Getter for the number of constraints.
         * @return The number of constraints.
         */
        std::size_t size() const;

        static representation_name type() { return representation_name::polytope_h; }

        /**
         * @brief Resets the information if the current polytope contains redundant constraints.
         * @details This function may be used to allow a manual call to the redundancy removal method.
         */
        void unreduce() const { mNonRedundant = false; }

        /**
         * @brief Manually sets the polytope to behave as if it did not contain redundant constraints.
         * @details This function can avoid an expensive redundancy removal call in case the user already knows that this property holds.
         */
        void setReduced() const { mNonRedundant = true; }

        /**
         * @brief Returns, whether the current polytope contains redundant constraints.
         * @details Only reads the stored flag without.
         * @return True, if there are no redundant constraints, false otherwise.
         */
        bool isNonRedundant() const { return mNonRedundant; }

        /**
         * @brief Getter for the matrix representation of the constraints.
         * @return A matrix.
         */
        matrix_t<Number> matrix() const;

        /**
         * @brief Getter for the vector of offsets of the bounding hyperplanes.
         * @return A vector.
         */
        vector_t<Number> vector() const;

        /**
         * @brief Getter for the full description of the polytope as a pair of a matrix and a vector.
         * @return A pair of a matrix and a vector.
         */
        std::pair<matrix_t<Number>, vector_t<Number>> inequalities() const;

        /**
         * @brief Getter for the vertices of the current polytope
         * @details Solves the vertex enumeration problem, i.e. converts the hyperplanar description into a vertex description.
         * @return A vector of points.
         */
        std::vector<Point<Number>> vertices(const matrix_t<Number> & = matrix_t<Number>::Zero(0, 0)) const;

        /**
         * @brief Getter for a number representing the supremum according to the infinity norm of the polytope.
         * @return A number.
         */
        Number supremum() const;

        /**
         * @brief Inserts an additional bounding halfspace into the polytope.
         * @param plane The plane to add.
         * @return True, if a plane was added, false, if it was already part of the polytope
         */
        bool insert(const Halfspace<Number> &plane);

        /**
         * @brief Inserts a range of halfspaces into the current polytope.
         * @param iterator Iterator pointing to the start of the range.
         * @param iterator Iterator pointing to the end of the range.
         * @return True, if a plane was added, false, if it was already part of the polytope
         */
        bool insert(const typename HalfspaceVector::iterator begin, const typename HalfspaceVector::iterator end);

        /**
         * @brief Removes the constraint at position index.
         * @param index An index.
         */
        void erase(const unsigned index);

        const HalfspaceVector &constraints() const;

        bool hasConstraint(const Halfspace<Number> &hplane) const;

        const HPolytopeT &removeRedundancy();

        HPolytopeT heuristic() const;

        HPolytopeT
        reduce(unsigned facet = 1, unsigned facet2 = 0, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP) const;

        HPolytopeT reduce_directed(std::vector<vector_t<Number>> directions,
                                   REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DIRECTED_SMALL) const;

        void reduceAssign(unsigned _steps = 1, REDUCTION_STRATEGY strat = REDUCTION_STRATEGY::DROP);

        bool isBounded(std::vector<vector_t<Number>>) const;
        // static std::vector<vector_t<Number>> computeTemplate(unsigned dimension, unsigned polytope);

        bool isExtremePoint(const vector_t<Number> &point) const;

        bool isExtremePoint(const Point<Number> &point) const;

        EvaluationResult<Number> evaluate(const vector_t<Number> &_direction) const;

        std::vector<EvaluationResult<Number>> multiEvaluate(const matrix_t<Number> &_direction) const;

        std::vector<EvaluationResult<Number>> multiEvaluate(const matrix_t<Number> &_directions, bool useExact) const;

        std::vector<Point<Number>> vertexEnumeration() const;

        // function which offsets all the halfspaces with the same number
        void offsetAllToNegative(Number offset); 

        // function to normalize all halfspaces
        void normalize();

        /*
         * General interface
         */

        std::pair<CONTAINMENT, HPolytopeT> satisfiesHalfspace(const Halfspace<Number> &rhs) const;

        std::pair<CONTAINMENT, HPolytopeT>
        satisfiesHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        HPolytopeT projectOut(const std::vector<std::size_t> &dimensions, bool viaLinearTransformation = false) const;

        HPolytopeT
        projectOutConservative(const std::vector<std::size_t> &dimensions, bool viaLinearTransformation = false) const;

        HPolytopeT projectOn(const std::vector<std::size_t> &dimensions) const;

        HPolytopeT assignIntervals(const std::map<std::size_t, carl::Interval<Number>> &) const {
            WARN("hypro", "Not implemented.");
            return *this;
        }

        HPolytopeT linearTransformation(const matrix_t<Number> &A) const;

        HPolytopeT affineTransformation(const matrix_t<Number> &A, const vector_t<Number> &b) const;

        HPolytopeT minkowskiSum(const HPolytopeT &rhs) const;

        HPolytopeT intersect(const HPolytopeT &rhs) const;

        HPolytopeT intersectHalfspace(const Halfspace<Number> &rhs) const;

        HPolytopeT intersectHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        bool contains(const Point<Number> &point) const;

        bool contains(const vector_t<Number> &vec) const;

        bool contains(const HPolytopeT &rhs) const;

        HPolytopeT unite(const HPolytopeT &rhs) const;

        static HPolytopeT unite(const std::vector<HPolytopeT> &rhs);

        void reduceRepresentation() {
            reduceNumberRepresentation();
            removeRedundancy();
        }

        void clear();

        void print() const;

        std::string printWithGenericVarIdents() {
            std::stringstream result;
            if (this->constraints().size() > 0) {
                result << "[ ";
                for (unsigned i = 0; i < this->constraints().size() - 1; ++i) {
                    result << convert<Number, double>(this->constraints()[i]).printWithGenericVarIdents()
                        << ",\n";
                }
                result << convert<Number, double>(this->constraints()[this->constraints().size() - 1]).printWithGenericVarIdents() 
                    << " ]";
            }
            result << " isEmpty: " << this->mEmptyState;
            return result.str();
        }

        /*
         * Operators
         */
        HPolytopeT &operator=(const HPolytopeT<Number, Converter, Setting> &rhs) {
            GeometricObjectBase::operator=(rhs);
            mHPlanes = rhs.constraints();
            mDimension = rhs.dimension();
            mNonRedundant = rhs.isNonRedundant();

            if (Setting::OPTIMIZER_CACHING && rhs.getOptimizer().has_value()) {
                mOptimizer->cleanContexts();
                setOptimizer(rhs.matrix(), rhs.vector());
            }
            assert(mEmptyState == rhs.getEmptyState());
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &lhs, const HPolytopeT<Number, Converter, Setting> &rhs) {
            if (rhs.constraints().size() > 0) {
                lhs << "[ ";
                for (unsigned i = 0; i < rhs.constraints().size() - 1; ++i) {
                    lhs << convert<Number, double>(rhs.constraints()[i]) << "," << std::endl;
                }
                lhs << convert<Number, double>(rhs.constraints()[rhs.constraints().size() - 1]) << " ]";
            }
            lhs << " isEmpty: " << rhs.mEmptyState;
            return lhs;
        }

        bool operator==(const HPolytopeT<Number, Converter, Setting> &rhs) const {
            if (this->dimension() != rhs.dimension()) {
                return false;
            }

            return this->constraints() == rhs.constraints();
        }

        friend void swap(HPolytopeT &a, HPolytopeT &b) {
            std::size_t tmpDim = a.mDimension;
            a.mDimension = b.mDimension;
            b.mDimension = tmpDim;
            swap(a.mHPlanes, b.mHPlanes);
            a.setUpdated(false);
            b.setUpdated(false);
        }

        template<typename N = Number, carl::DisableIf<std::is_same<N, double>> = carl::dummy>
        void reduceNumberRepresentation(const std::vector<Point<Number>> &_vertices = std::vector<Point<Number>>(),
                                        unsigned limit = fReach_DENOMINATOR) const {
            constexpr bool GET_VERTICES_AFTER_CHECK = false;
			// #ifdef REDUCE_NUMBERS
            if (Setting::REDUCE_NUMBERS == true) {
				std::vector<Point<Number>> originalVertices;
				if(!GET_VERTICES_AFTER_CHECK) {
					TRACE("hypro.hPolytope", "Attempt to reduce numbers.");
					if (_vertices.empty()) {
						TRACE("hypro.hPolytope", "No passed vertices, computed vertices.");
						originalVertices = this->vertices();
					} else {
						TRACE("hypro.hPolytope", "Use passed vertices.");
						originalVertices = _vertices;
					}
					TRACE("hypro.hPolytope", "Vertices empty: " << originalVertices.empty());
				}

                if (!this->empty()) {
                    // normal reduction
                    for (unsigned planeIndex = 0; planeIndex < mHPlanes.size(); ++planeIndex) {
                        // find maximal value
                        Number largest = Number(0);
                        mHPlanes.at(planeIndex).makeInteger();
                        largest = carl::abs(mHPlanes.at(planeIndex).offset());
                        for (unsigned i = 0; i < mDimension; ++i) {
                            if (carl::abs(mHPlanes.at(planeIndex).normal()(i)) > largest) {
                                largest = carl::abs(mHPlanes.at(planeIndex).normal()(i));
                            }
                        }

                        // reduce, if reduction is required
                        if (largest > (limit * limit)) {
							if(GET_VERTICES_AFTER_CHECK) {
								TRACE("hypro.hPolytope", "Attempt to reduce numbers.");
								if (_vertices.empty()) {
									TRACE("hypro.hPolytope", "No passed vertices, computed vertices.");
									originalVertices = this->vertices();
								} else {
									TRACE("hypro.hPolytope", "Use passed vertices.");
									originalVertices = _vertices;
								}
								TRACE("hypro.hPolytope", "Vertices empty: " << originalVertices.empty());
							}

                            vector_t<Number> newNormal(mDimension);
                            for (unsigned i = 0; i < mDimension; ++i) {
                                newNormal(i) = carl::floor(
                                        Number((mHPlanes.at(planeIndex).normal()(i) / largest) * Number(limit)));
                                assert(carl::abs(Number(mHPlanes.at(planeIndex).normal()(i) / largest)) <= Number(1));
                                assert(isInteger(newNormal(i)));
                                assert(newNormal(i) <= Number(limit));
                            }
                            mHPlanes.at(planeIndex).setNormal(newNormal);
                            Number newOffset = mHPlanes.at(planeIndex).offset();
                            newOffset = carl::ceil(Number((newOffset / largest) * Number(limit)));
                            for (const auto &vertex: originalVertices) {
                                Number tmp = newNormal.dot(vertex.rawCoordinates());
                                if (tmp > newOffset) {
                                    newOffset = newOffset + (tmp - newOffset);
                                    assert(newNormal.dot(vertex.rawCoordinates()) <= newOffset);
                                }
                                assert(Halfspace<Number>(newNormal, newOffset).contains(vertex));
                            }
                            newOffset = carl::ceil(newOffset);
                            mHPlanes.at(planeIndex).setOffset(newOffset);
                        }
                    }
                }
            }
            // #endif
        }

        /**
         * calculates the set difference of two polytopes
         */
        std::vector<HPolytopeT<Number, Converter, Setting>>
        setMinus2(const HPolytopeT<Number, Converter, Setting> &minus) const;

        std::vector<HPolytopeT<Number, Converter, Setting>>
        setMinus(const HPolytopeT<Number, Converter, Setting> &minus) const;

        template<typename N = Number, carl::EnableIf<std::is_same<N, double>> = carl::dummy>
        void reduceNumberRepresentation(const std::vector<Point<double>> & = std::vector<Point<double>>(),
                                        unsigned = fReach_DENOMINATOR) const {}


        /// Serialization function required by cereal
        template<typename Archive>
        void serialize(Archive &ar) {
#ifdef HYPRO_USE_SERIALIZATION
            ar(cereal::make_nvp("isEmpty", mEmptyState), cereal::make_nvp("constraints", mHPlanes),
               cereal::make_nvp("dimension", mDimension), cereal::make_nvp("guaranteedNonRedundant", mNonRedundant));
#else
            ar( mEmptyState, mHPlanes, mDimension, mNonRedundant );
#endif
        }


    private:
        /*
         * Computes a set of constraints that correpsonds to the convex hull of the points
         * @param points The set of points. Note that auxilarry points might be added to this vector.
         * @param degeneratedDimensions the number of dimensions in which the convex hull of the points is degenerated, i.e., spaceDimension - effectiveDimension
         */
        HalfspaceVector computeConstraintsForDegeneratedPolytope(std::vector<Point<Number>> &points,
                                                                 unsigned degeneratedDimensions) const;

        std::vector<std::vector<unsigned>> getMembersOfVertices(std::vector<Point<Number>> vertices) const;

        std::vector<unsigned>
        getNeighborsOfIndex(unsigned facet, std::vector<std::vector<unsigned>> membersOfvertices) const;

        std::vector<Point<Number>> getVerticesOfIndex(unsigned a, std::vector<Point<Number>> vertices,
                                                      std::vector<std::vector<unsigned>> membersOfvertices) const;

        std::vector<Point<Number>> getVerticesOf2Indices(unsigned a, unsigned b, std::vector<Point<Number>> vertices,
                                                         std::vector<std::vector<unsigned>> membersOfvertices) const;

        std::vector<Point<Number>>
        getVerticesOf2IndicesAround(unsigned a, unsigned b, std::vector<Point<Number>> vertices,
                                    std::vector<std::vector<unsigned>> membersOfvertices) const;

        std::vector<std::vector<vector_t<Number>>>
        getVerticesPermutationForFacet(unsigned a, unsigned b, std::vector<Point<Number>> vertices) const;

        vector_t<Number> computeNormal(std::vector<vector_t<Number>> vertices, vector_t<Number> check) const;

        Point<Number>
        getVertexForVector(const vector_t<Number> &vector, const std::vector<Point<Number>> &vertices) const;

        /**
         * @brief      Extends the constraint to a higher dimension. This effectively unbounds the polytope in that direction. The passed set of
         * existing dimensions is used to allow adding dimensions in between. Note that both vectors have to be ordered ascending.
         * @param[in]  existingDimensions  The existing dimensions.
         * @param[in]  newDimensions       The new dimensions.
         */
        void insertEmptyDimensions(const std::vector<std::size_t> &existingDimensions,
                                   const std::vector<std::size_t> &newDimensions);

        void updateBoundingBox() const;

        /// TODO
        void updateCache() const;

        void invalidateCache() const;

    public:
        // If CACHE_OPTIMIZER = true, initialize optimizer
        std::optional<Optimizer<Number>> &getOptimizer() const { return mOptimizer; }

        void setOptimizer(const matrix_t<Number> &mat = matrix_t<Number>::Zero(1, 1),
                          const vector_t<Number> &vec = vector_t<Number>::Zero(1)) const;

        void setUpdated(const bool &b) { mUpdated = b; }

        bool getUpdated() const { return mUpdated; }
    };

/** @} */

    template<typename From, typename To, typename Converter, class Setting>
    HPolytopeT<To, Converter, Setting> convert(const HPolytopeT<From, Converter, Setting> &in) {
        return HPolytopeT<To, Converter, Setting>(convert<From, To>(in.matrix()), convert<From, To>(in.vector()));
    }

}  // namespace hypro

#include "HPolytope.tpp"
#include "reduction.tpp"
