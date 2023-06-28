/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file Box.h
 * \example example_box.cpp
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "../../types.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "../../util/logging/Logger.h"
#include "../../util/sequenceGeneration/SequenceGenerator.h"
#include "../../util/templateDirections.h"
#include "../helperMethods/isBox.h"
#include "BoxSetting.h"
#include "intervalMethods.h"

#include <cassert>
#include <map>
#include <queue>
#include <set>
#include <vector>

namespace hypro {

/**
 * @brief Forward declaration of class Vertex
 * @tparam Number
 */
    template<typename Number>
    class Vertex;

/**
 * @brief Forward declaration of class Location *
 * @tparam Number
 */
    template<typename Number>
    class Location;

/**
 * @brief      The class which represents a box.
 * @details    A box is represented by an ordered sequence of intervals. Details can be found [here](@ref boxDetails).
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 *
 * \ingroup geoState@{
 */
    template<typename Number, typename Converter, class Setting>
    class BoxT : private GeometricObjectBase {
    private:
    public:
        /***************************************************************************
         * Members
         **************************************************************************/

        typedef Setting Settings;
        typedef Number NumberType;
        static constexpr auto type_enum = representation_name::box;

    protected:
        std::vector<carl::Interval<Number>> mLimits; /*!< Box as a vector of intervals. */

    public:
        /***************************************************************************
         * Constructors
         **************************************************************************/

        /**
         * @brief      Creates an empty box.
         * @details   The empty box is represented by a zero-dimensional point pair.
         */
        BoxT()
                : GeometricObjectBase(SETSTATE::EMPTY), mLimits() {
            assert(this->dimension() == 0);
            assert(this->empty());
        }

        /**
         * @brief      Copy constructor.
         * @param[in]  orig  The original.
         */
        BoxT(const BoxT &orig) = default;

        /**
         * @brief      Copy constructor. NOTE: it is not an actual copy constructor as it is templated.
         * @param[in]  orig  The original.
         */
        template<typename SettingRhs, carl::DisableIf<std::is_same<Setting, SettingRhs>> = carl::dummy>
        BoxT(const BoxT<Number, Converter, SettingRhs> &orig)
                : GeometricObjectBase(), mLimits(orig.intervals()) {}

        /**
         * @brief      Move constructor.
         * @param[in]  orig  The original.
         */
        BoxT(BoxT &&orig) noexcept = default;

        /**
         * @brief      Box constructor from one interval, results in a one-dimensional box.
         * @param[in]  val   An interval.
         */
        explicit BoxT(const carl::Interval<Number> &val) {
            mLimits.push_back(val);
            if (isEmpty(val))
                mEmptyState = SETSTATE::EMPTY;
            else if (isUnbounded(val))
                mEmptyState = SETSTATE::UNIVERSAL;
            else
                mEmptyState = SETSTATE::NONEMPTY;
        }

        /**
         * @brief Box constructor from a pair of points.
         * @details The given parameters are considered as the maximal and minimal point.
         * The constructor does not check the order of points.
         * @param limits Pair of points.
         */
        explicit BoxT(const std::pair<Point<Number>, Point<Number>> &limits) {
            assert(limits.first.dimension() == limits.second.dimension());
            mEmptyState = limits.first.dimension() > 0 ? SETSTATE::NONEMPTY : SETSTATE::EMPTY;
            for (std::size_t i = 0; i < limits.first.dimension(); ++i) {
                mLimits.emplace_back(carl::Interval<Number>(limits.first[i], limits.second[i]));
                mEmptyState = isEmpty(mLimits.back()) ? SETSTATE::EMPTY : mEmptyState;
            }
        }

        /**
         * @brief Constructor from a vector of intervals.
         * @details The vector is required to be sorted, i.e. the first interval maps to the first dimension etc..
         * @param _intervals A vector of intervals.
         */
        explicit BoxT(const std::vector<carl::Interval<Number>> &_intervals)
                : GeometricObjectBase(_intervals.size() > 0 ? SETSTATE::NONEMPTY : SETSTATE::EMPTY),
                  mLimits(_intervals) {
            for (const auto &i: mLimits) {
                TRACE("hypro.representations", "Add interval: " << i);
                if (isEmpty(i)) {
                    mEmptyState = SETSTATE::EMPTY;
                    break;
                }
            }
        }

        /**
         * @brief Constructor from a matrix and a vector.
         * @details Constructs a box assuming each row of the matrix is the normal to a hyperplane and its corresponding
         * entry in the given vector is the offset.
         * @param _constraints A matrix representing the constraint normals.
         * @param _constants A vector representing the offsets of the corresponting hyperplane.
         */
        BoxT(const matrix_t<Number> &_constraints, const vector_t<Number> &_constants);

        /**
         * @brief Constructor from a set of points.
         * @details The constructor does not rely on the operator < of the point class, thus each point is considered
         * for the construction of the maximal and minimal point.
         * @param _points A set of points.
         */
        explicit BoxT(const std::set<Point<Number>> &_points);

        /**
         * @brief A constructor from a vector of points.
         * @details Creates the maximal and minimal point by collecting all coordinates from all given points.
         * @param _points A vector of points.
         */
        explicit BoxT(const std::vector<Point<Number>> &_points);

        /**
         * @brief Destructor.
         */
        ~BoxT() {}

        /***************************************************************************
         * Getters & setters
         **************************************************************************/

        Setting getSettings() const { return Setting{}; }

        /**
         * @brief Static method for the construction of an empty box of required dimension.
         * @return Empty box.
         */
        static BoxT Empty() {
            auto tmp = BoxT();
            assert(tmp.empty());
            return tmp;
        }

        /**
         * @brief Getter for interval representation of the current box.
         * @details Converts the two-points representation of the current box into a sorted vector of intervals.
         * @return A vector of intervals.
         */
        const std::vector<carl::Interval<Number>> &intervals() const {
            return mLimits;
        }

        std::vector<carl::Interval<Number>> &rIntervals() {
            return mLimits;
        }

        /**
         * @brief Getter for the limiting points.
         * @return A pair of points.
         */
        std::pair<Point<Number>, Point<Number>> limits() const {
            if (mEmptyState == SETSTATE::EMPTY) {
                return std::pair<Point<Number>, Point<Number>>{Point<Number>(vector_t<Number>::Ones(this->dimension())),
                                                               Point<Number>(
                                                                       vector_t<Number>::Zero(this->dimension()))};
            }
            std::pair<Point<Number>, Point<Number>> res{Point<Number>(vector_t<Number>(this->dimension())),
                                                        Point<Number>(vector_t<Number>(this->dimension()))};
            std::size_t p = 0;
            for (const auto &i: mLimits) {
                res.first[p] = i.lower();
                res.second[p] = i.upper();
                ++p;
            }
            return res;
        }

        matrix_t<Number> matrix() const;

        vector_t<Number> vector() const;

        /**
         * @brief Getter for the hyperplanar representation of the current box.
         * @details Converts the two-points representation into a hyperplanar representation, i.e. a H-polytope.
         * @return A vector of hyperplanes.
         */
        std::vector<Halfspace<Number>> constraints() const;

        /**
         * @brief Extends the dimension of the current box by the given interval.
         * @details Effectively extends the dimension of the current box.
         * @param val An interval.
         */
        void insert(const carl::Interval<Number> &val) {
            mLimits.push_back(val);
            if (isEmpty(mLimits.back())) {
                mEmptyState = SETSTATE::EMPTY;
            } else if (mLimits.size() == 1) {     // the new interval was the first and it is not empty.
                mEmptyState = isUnbounded(mLimits.front()) ? SETSTATE::UNIVERSAL : SETSTATE::NONEMPTY;
            } else if (isUnbounded(val)) {
                mEmptyState = SETSTATE::UNIVERSAL;
            }
            // otherise do not modify mEmptyState - if it was true before it stays true, otherwise nothing happens.
        }

        /**
         * @brief Getter for an interval representation of one specific dimension.
         * @details Converts the d-th entries in the maximal and minimal point to an interval.
         * @param d The queried dimension.
         * @return An interval.
         */
        const carl::Interval<Number> &interval(std::size_t d) const {
            assert(d < mLimits.size());
            return mLimits[d];
        }

        carl::Interval<Number> &rInterval(std::size_t d) {
            assert(d < mLimits.size());
            return mLimits[d];
        }

        /**
         * @brief Getter for an interval representation of one specific dimension.
         * @details Converts the d-th entries in the maximal and minimal point to an interval.
         * @param d The queried dimension.
         * @return An interval.
         */
        carl::Interval<Number> at(std::size_t _index) const {
            return mLimits.at(_index);
        }

        /**
         * @brief Determines if the current box is empty.
         * @details The method checks the dimension of the limit points and afterwards each interval for emptiness.
         * @return True, if one interval is empty. False if the dimension is 0 or no interval is empty.
         */
        bool empty() const {
            return mEmptyState == SETSTATE::EMPTY;
        }

        /**
         * @brief      Determines if the current box is symmetric.
         * @details    A box is symmetric, if its centroid is the origin in the respective space, i.e. if the center of each interval in each
         * dimension is zero.
         * @return     True if symmetric, False otherwise.
         */
        bool isSymmetric() const {
            if (mEmptyState == SETSTATE::EMPTY) {
                return true;
            }
            for (std::size_t d = 0; d < mLimits.size(); ++d) {
                if (!(-mLimits[d].lower() == mLimits[d].upper() &&
                      lowerBoundType(mLimits[d]) == upperBoundType(mLimits[d]))) {
                    return false;
                }
            }
            return true;
        }

        /**
         * @brief Getter for the maximal point.
         * @return A point.
         */
        Point<Number> max() const {
            Point<Number> res{vector_t<Number>(this->dimension())};
            for (std::size_t d = 0; d < mLimits.size(); ++d) {
                res[d] = mLimits[d].upper();
            }
            return res;
        }

        /**
         * @brief Getter for the minimal point.
         * @return A point.
         */
        Point<Number> min() const {
            Point<Number> res{vector_t<Number>(this->dimension())};
            for (std::size_t d = 0; d < mLimits.size(); ++d) {
                res[d] = mLimits[d].lower();
            }
            return res;
        }

        /**
         * @brief Method returning the supremum point of the box, i.e. the maximal point.
         * @return A point representing the supremum of the current box.
         */
        Number supremum() const;

        /**
         * @brief Getter for a vertex-representation of the current box.
         * @details Converts the current box from its two-point representation into a vertex representation, i.e. a V-polytope.
         * The representation is generated by creating all possible combinations of upper and lower bounds of the box.
         * @return A vector of points.
         */
        std::vector<Point<Number>> vertices(const matrix_t<Number> & = matrix_t<Number>::Zero(0, 0)) const;

        /**
         * @brief      Evaluation function (convex linear optimization).
         * @details    Linear optimization for boxes can be done more efficiently that for general convey polytopes as the state space dimensions are  independent. Consequently it suffices to consider the coefficient of the cost function for each dimension and either use the upper, respectively lower bound depending on its sign (positive, respectively negative) to get the vertex of the box representing the optimum.
         * @param[in]  _direction  The direction/cost function.
         * @return     Maximum towards _direction.
         */
        EvaluationResult<Number> evaluate(const vector_t<Number> &_direction, bool = true) const;

        /**
         * @brief      Multi-evaluation function (convex linear optimization).
         * @details    Can be done similar to basic linear optimization in one direction.
         * @param[in]  _directions  The directions/cost functions.
         * @return     A set of maxima towards the respective directions.
         */
        std::vector<EvaluationResult<Number>>
        multiEvaluate(const matrix_t<Number> &_directions, bool useExact = true) const;

        /**
         * @brief Checks if two boxes are equal.
         * @param b1 Contains the first box.
         * @param b2 Contains the second box.
         * @return True, if they are equal.
         */
        template<class SettingRhs>
        friend bool operator==(const BoxT &b1, const BoxT<Number, Converter, SettingRhs> &b2) {
            if (b1.dimension() != b2.dimension()) {
                return false;
            }
            for (std::size_t i = 0; i < b1.dimension(); ++i) {
                if (b1.interval(i) != b2.interval(i)) {
                    return false;
                }
            }
            return true;
        }

        /**
         * @brief Determines inequality of two boxes.
         * @param b1 A box.
         * @param b2 A box.
         * @return False, if both boxes are equal.
         */
        friend bool operator!=(const BoxT &b1, const BoxT &b2) { return !(b1 == b2); }
        /*
        template<typename SettingRhs, carl::DisableIf< std::is_same<Setting, SettingRhs> > = carl::dummy>
        friend bool operator!=( const BoxT<Number,Converter,Setting>& b1, const BoxT<Number,Converter,SettingRhs>& b2 ) { return !( b1 == b2 ); }
    */
        /**
         * @brief Assignment operator.
         * @param rhs A box.
         */
        BoxT &operator=(const BoxT &rhs) = default;

        /**
         * @brief Move assignment operator.
         * @param rhs A box.
         */
        BoxT &operator=(BoxT &&rhs) noexcept = default;

        /**
         * @brief      Scaling operator.
         * @param[in]  factor  The scaling factor.
         * @return     The scaled box.
         */
        BoxT operator*(const Number &factor) const {
            BoxT<Number, Converter, Setting> copy{*this};
            for (auto &i: copy.rIntervals()) {
                i *= factor;
            }
            return copy;
        }

        /**
         * @brief Outstream operator.
         * @param ostr Outstream.
         * @param b A box.
         */
        friend std::ostream &operator<<(std::ostream &ostr, const BoxT<Number, Converter, Setting> &b) {
            ostr << "{ ";
            if (!b.empty()) {
                for (const auto &i: b.intervals()) {
                    ostr << i << " ";
                }
            }
            ostr << " }";
            return ostr;
        }

        /**
         * @brief Access operator (const).
         * @param i Dimension to access.
         * @return An interval.
         */
        const carl::Interval<Number> &operator[](unsigned i) const { return mLimits[i]; }

        carl::Interval<Number> &operator[](unsigned i) { return mLimits[i]; }

        /***************************************************************************
         * General interface
         **************************************************************************/

        /**
         * @brief      Getter for the state space dimension.
         * @return     The dimension of the space.
         */
        std::size_t dimension() const { return mLimits.size(); }

        /**
         * @brief      Removes redundancy (part of the general interface. Does nothing for boxes.)
         */
        void removeRedundancy() {}

        /**
         * @brief      Storage size determination.
         * @return     Size of the required memory.
         */
        std::size_t size() const;

        static representation_name type() { return representation_name::box; }

        /**
         * @brief      Function to reduce the number representation (over-approximate).
         * @details    The function tries to reduce the size of each interval boundary in case it is larger than some specified limit.
         * This is done by outward rounding. Note that this function is only relevant, if the number representation may affect running times (here: rational number implementations).
         *
         * @param[in]  limit      The limit
         */
        const BoxT &reduceNumberRepresentation(unsigned limit = fReach_DENOMINATOR);

        /**
         * @brief      Makes a symmetric box from the current box.
         * @details    The symmetry is obtained by dimension-wise extension of the boundaries. The resulting boundaries for each dimension
         * are the maximal absolute values of the original boundaries mirrored positive and negative.
         * @return     The resulting symmetric box.
         */
        BoxT makeSymmetric() const;

        /**
         * @brief Meta-function, which allows to compute the intersection of a box with a half-space and return the resulting box as well as the information, whether the resulting box is empty.
         * @details The computation is done by exploiting interval arithmetic similar to contraction operations in interval constraint propagation on linear constraints.
         *
         * @param rhs
         * @return std::pair<CONTAINMENT, BoxT>
         */
        std::pair<CONTAINMENT, BoxT> satisfiesHalfspace(const Halfspace<Number> &rhs) const;

        std::pair<CONTAINMENT, BoxT>
        satisfiesHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        BoxT projectOn(const std::vector<std::size_t> &dimensions) const;

        BoxT assignIntervals(const std::map<std::size_t, carl::Interval<Number>> &assignments) const;

        /**
         * @brief Computes the linear transformation of a box by a matrix A.
         * @details We employ interval-arithmetic to compute the result instead of a naive approach in which a conversion to a V-polytope would be used.
         *
         * @param A Matrix used for the transformation.
         * @return BoxT<Number,Converter,Setting>
         */
        BoxT linearTransformation(const matrix_t<Number> &A) const;

        /**
         * @brief Computes the affine transformation of a box by a matrix A and an offset vector b.
         * @details The computation is performed via interval arithmetic using a linear transformation operation and afterwards accounting for the translation invoked by b.
         * @param A
         * @param b
         * @return BoxT<Number,Converter,Setting>
         */
        BoxT affineTransformation(const matrix_t<Number> &A, const vector_t<Number> &b) const;

        BoxT minkowskiSum(const BoxT &rhs) const;

        /**
         * @brief      Computes the Minkowski decomposition of the current box by the given box.
         * @details    This operation can be seen as the set-theoretic equivalent of subtraction. Note that this is not entirely true, as the operation is performed on sets which adds over-approximation errors (similarly to using addition and subtraction in interval-arithmetic).
         * @param[in]  rhs   The right hand side box.
         * @return     The resulting box.
         */
        BoxT minkowskiDecomposition(const BoxT &rhs) const;

        /**
         * @brief      Computes the intersection of two boxes.
         * @param[in]  rhs   The right hand side box.
         * @return     The resulting box.
         */
        BoxT intersect(const BoxT &rhs) const;

        /**
         * @brief Allows to compute the intersection of a box with a half-space and return the resulting box.
         * @details The computation is done by exploiting interval arithmetic similar to contraction operations in interval constraint propagation on linear constraints.
         *
         * @param hspace
         * @return BoxT<Number,Converter,Setting>
         */

        BoxT intersectHalfspace(const Halfspace<Number> &hspace) const;

        BoxT intersectHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        bool contains(const Point<Number> &point) const;

        /**
         * @brief Allows to compute the set-difference of a box with another box and returns the resulting vector of boxes.
         * @details follow soon
         *
         * @param minusbox
         * @return std::vector<BoxT<Number,Converter,Setting>>
         */
        std::vector<BoxT<Number, Converter, Setting>> setMinus(const BoxT<Number, Converter, Setting> &minusbox) const;

        /**
         * @brief Allows to compute the set-difference of a box with another box and returns the resulting vector of boxes.

         *
         * @param minusbox
         * @return std::vector<BoxT<Number,Converter, Setting>>
         */
        std::vector<BoxT<Number, Converter, Setting>> setMinus2(const BoxT<Number, Converter, Setting> &minusbox) const;

        /**
         * @brief      Containment check for a box.
         * @param[in]  box   The box.
         * @return     True, if the given box is contained in the current box, false otherwise.
         */
        bool contains(const BoxT &box) const;

        /**
         * Checks, whether the passed box is contained and returns the part of the passed box that is contained.
         * @param other box that is passed
         * @return a pair of containment information and the reduction of the other box
         */
        std::pair<CONTAINMENT, BoxT> containmentReduce(const BoxT &other) const;

        /**
         * Checks whether the two boxes have a non-empty intersection
         * @param box The other box.
         * @return True, if both boxes have a non-empty intersection, false otherwise.
         */
        bool intersects(const BoxT &box) const;

        /**
         * @brief      Computes the union of two boxes.
         * @param[in]  rhs   The right hand side box.
         * @return     The resulting box.
         */
        BoxT unite(const BoxT &rhs) const;

        /**
         * @brief      Computes the union of the current box with a set of boxes.
         * @param[in]  boxes  The boxes.
         * @return     The resulting box.
         */
        static BoxT unite(const std::vector<BoxT> &boxes);

        /**
         * @brief      Reduces the box - only in case rational types are used, the number representation is optimized.
         */
        void reduceRepresentation() {
            *this = std::move(this->reduceNumberRepresentation());
            removeRedundancy();
        }

        /**
         * @brief      Makes this box equal to the empty box.
         */
        void clear();

        /**
         * @brief      A deprecated print method. Use the outstream operator.
         */
        [[deprecated( "Use the outstream-operator instead." )]] void print() const;

        /// Serialization function required by cereal
        template<typename Archive>
        void serialize(Archive &ar) {
            // ar( cereal::base_class<GeometricObjectBase>( this ), mLimits );
            ar(mEmptyState, mLimits);
        }
    };

/** @} */

/**
 * @brief      Operator for scaling a box.
 * @param[in]  factor     The scaling factor.
 * @param[in]  in         The box which is to be scaled.
 * @tparam     Number     The number type.
 * @tparam     Converter  The passed representation converter.
 * @return     The resulting box.
 */
    template<typename Number, typename Converter, class Setting>
    BoxT<Number, Converter, Setting> operator*(Number factor, const BoxT<Number, Converter, Setting> &in) {
        if (in.empty()) {
            return in;
        }
        return in * factor;
    }

/**
 * @brief      Conversion function for different number types.
 * @param[in]  in         The input box.
 * @tparam     From       The current number type.
 * @tparam     To         The number type the box is to be converted to.
 * @tparam     Converter  The passed representation converter.
 * @return     The resulting box.
 */
    template<typename From, typename To, typename Converter, class Setting>
    BoxT<To, Converter, Setting> convert(const BoxT<From, Converter, Setting> &in) {
        std::pair<Point<From>, Point<From>> limits = in.limits();
        return BoxT<To, Converter, Setting>(std::make_pair(Point<To>(convert<From, To>(limits.first.rawCoordinates())),
                                                           Point<To>(
                                                                   convert<From, To>(limits.second.rawCoordinates()))));
    }

}  // namespace hypro

#include "Box.tpp"
