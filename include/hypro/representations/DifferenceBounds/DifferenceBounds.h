/*
 * Copyright (c) 2023.
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

#include "../../datastructures/Point.h"
#include "DifferenceBoundsSetting.h"

namespace hypro {
    template<typename Number>
    class Point;

/**
 * @brief      Class wrapping the difference bounds content.
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 *
 * \ingroup geoState@{
 */
    template<typename Number, typename Converter, class Setting>
    class DifferenceBoundsT : private GeometricObjectBase {
    public:
        enum BOUND_TYPE {
            SMALLER,
            SMALLER_EQ,
            INFTY,
        };

        typedef Setting Settings;
        typedef Number NumberType;

        class DBMEntry : public std::pair<Number, BOUND_TYPE> {
        public:
            using std::pair<Number, BOUND_TYPE>::first;
            using std::pair<Number, BOUND_TYPE>::second;

            DBMEntry();

            DBMEntry(Number number, BOUND_TYPE boundType);

            DBMEntry(const DBMEntry &other) = default;

            ~DBMEntry() = default;

            DBMEntry &operator=(const DBMEntry &other) {
                if (this != &other) {
                    this->first = other.first;
                    this->second = other.second;
                }
                return *this;
            }

            static DBMEntry max(const DBMEntry &lhs, const DBMEntry &rhs) { return lhs < rhs ? rhs : lhs; }

            static DBMEntry min(const DBMEntry &lhs, const DBMEntry &rhs) { return lhs < rhs ? lhs : rhs; }

            bool operator<(const DBMEntry rhs) {
                if (this->second == BOUND_TYPE::INFTY) {
                    // TODO correct?
                    return false;
                }
                // (n, </<=) < infty
                if (rhs.second == BOUND_TYPE::INFTY) {
                    return true;
                }
                // (n_1, </<=) < (n_2, </<=) if n_1 < n_2
                if (this->first < rhs.first) {
                    return true;
                }
                // (n, <) < (n,<=)
                if (this->first == rhs.first && this->second == BOUND_TYPE::SMALLER &&
                    rhs.second == BOUND_TYPE::SMALLER_EQ) {
                    return true;
                }
                return false;
            }

            bool operator<(const DBMEntry rhs) const {
                if (this->second == BOUND_TYPE::INFTY) {
                    // TODO correct?
                    return false;
                }
                // (n, </<=) < infty
                if (rhs.second == BOUND_TYPE::INFTY) {
                    return true;
                }
                // (n_1, </<=) < (n_2, </<=) if n_1 < n_2
                if (this->first < rhs.first) {
                    return true;
                }
                // (n, <) < (n,<=)
                if (this->first == rhs.first && this->second == BOUND_TYPE::SMALLER &&
                    rhs.second == BOUND_TYPE::SMALLER_EQ) {
                    return true;
                }
                return false;
            }

            bool operator==(const DBMEntry rhs) {
                if (this->second == BOUND_TYPE::INFTY && rhs.second == BOUND_TYPE::INFTY) {
                    return true;
                }
                // (n_1, </<=) == (n_2, </<=) if n_1 == n_2 and </<=_1 == </<=_2
                if (this->first == rhs.first && this->second == rhs.second) {
                    return true;
                }
                return false;
            }

            bool operator<=(const DBMEntry rhs) {
                return (*this < rhs) || (*this == rhs);
            }

            DBMEntry operator+(const DBMEntry rhs) {
                // adding infinity yields infinity;
                if (this->second == BOUND_TYPE::INFTY || rhs.second == BOUND_TYPE::INFTY) {
                    return DBMEntry(0.0, BOUND_TYPE::INFTY);
                }
                // (m,<=)+(n,<=) = (m+n,<=)
                if (this->second == BOUND_TYPE::SMALLER_EQ && rhs.second == BOUND_TYPE::SMALLER_EQ) {
                    return DBMEntry(this->first + rhs.first, BOUND_TYPE::SMALLER_EQ);
                }
                // (m,<)+(n,</<=) = (m+n,<)
                return DBMEntry(this->first + rhs.first, BOUND_TYPE::SMALLER);
            }

            friend std::ostream &operator<<(std::ostream &ostr, const DBMEntry entry) {
                ostr << "( ";
                ostr << entry.first;
                ostr << ", ";
                ostr << entry.second;
                ostr << " )";
                return ostr;
            }
        };

    private:
        mutable matrix_t<DBMEntry> m_dbm;
        Number m_timeHorizon;

    public:
        DifferenceBoundsT();

        DifferenceBoundsT(const DifferenceBoundsT &orig) = default;

        DifferenceBoundsT(matrix_t<Number> matrix, vector_t<Number> vector);

        /* TODO: not implemented */
        matrix_t<Number> matrix() const {
            assert("Not implemented." && false);
            return matrix_t<Number>::Zero(0, 0);
        }

        /* TODO: not implemented */
        vector_t<Number> vector() const {
            assert("Not implemented." && false);
            return vector_t<Number>::Zero(0);
        }

        matrix_t<DBMEntry> getDBM() const;

        void setDBM(matrix_t<DBMEntry> dbm);

        Number getTimeHorizon() const;

        void setTimeHorizon(Number horizon);

        carl::Interval<tNumber> getCoveredTimeInterval() const;

        // geometric object
        std::size_t dimension() const;

        std::size_t size() const;

        static representation_name type() { return representation_name::difference_bounds; }

        bool empty() const;

        static DifferenceBoundsT Empty() {
            assert(DifferenceBoundsT().empty());
            return DifferenceBoundsT();
        }

        /* TODO: not implemented */
        EvaluationResult<Number> evaluate(const vector_t<Number> &direction, bool useExact = true) const;

        /* TODO: not implemented */
        std::vector<EvaluationResult<Number>>
        multiEvaluate(const matrix_t<Number> &directions, bool useExact = true) const;

        std::vector<Point<Number>> vertices(const matrix_t<Number> & = matrix_t<Number>::Zero(0, 0)) const;

        std::pair<CONTAINMENT, DifferenceBoundsT> satisfiesHalfspace(const Halfspace<Number> &rhs) const;

        std::pair<CONTAINMENT, DifferenceBoundsT>
        satisfiesHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        DifferenceBoundsT projectOn(const std::vector<std::size_t> &dimensions) const;

        DifferenceBoundsT assignIntervals(const std::map<std::size_t, carl::Interval<Number>> &) const {
            WARN("hypro", "Not implemented.");
            return *this;
        }

        DifferenceBoundsT linearTransformation(const matrix_t<Number> &A) const;

        DifferenceBoundsT affineTransformation(const matrix_t<Number> &A, const vector_t<Number> &b) const;

        DifferenceBoundsT minkowskiSum(const DifferenceBoundsT &_rhs) const;

        DifferenceBoundsT intersect(const DifferenceBoundsT &_rhs) const;

        DifferenceBoundsT intersectHalfspace(const Halfspace<Number> &hs) const;

        DifferenceBoundsT intersectHalfspaces(const matrix_t<Number> &_mat, const vector_t<Number> &_vec) const;

        bool contains(const Point<Number> &_point) const;

        DifferenceBoundsT unite(const DifferenceBoundsT &_rhs) const;

        void reduceRepresentation() { *this = this->removeRedundancy(); }

        const DifferenceBoundsT &removeRedundancy();
        // difference bounds specific

        /**
         * Elapses time for all clocks, i.e. d_i0 (that is x_i-0<=d_i0) is set to infinity
         * @return a DBM where the smaller(_eq) constraints for each clock is moved to infinity.
         */
        DifferenceBoundsT elapse() const;

        /**
         * Computes the set of clock assignments that can reach the current DBMs Zone when time
         * is elapsed. It is computed by setting all lower clock bound to 0.
         *
         * I.e. d_0i (that is 0-x_i <= d_0i <=> x_i >= -d_01) is set to 0
         * @return a DBM where the greater_(eq) constraints for each clock is moved to 0.
         */
        DifferenceBoundsT rewind() const;

        /**
         * Frees a clock x, i.e. removes all bounding constraints for that clock
         * @param x index of the clock
         * @return DBM with clock x freed
         */
        DifferenceBoundsT free(int x) const;

        /**
         * Resets clock x to given Number value.
         * @param x index of the clock
         * @param value reset value of the clock
         * @return DBM with clock x reset to value
         */
        DifferenceBoundsT reset(int x, Number value) const;

        /**
         * Copies a the value of clock src to clock dest, i.e. resets the value of
         * dest to the value of src.
         * @param src index of src clock
         * @param dest index of dest clock
         * @return DBM with clock dest set to clock src
         */
        DifferenceBoundsT copy(int src, int dest) const;

        /**
         * Shifts the valuation of clock x by the given offset
         * @param x index of the clock
         * @param offset offset to be applied
         * @return DBM with clock x shifted by offset
         */
        DifferenceBoundsT shift(int x, Number offset) const;

        /**
         * Shifts the valuation of all clocks by the given offset
         * @param offset offset to be applied
         * @return DBM with clocks shifted by offset
         */
        DifferenceBoundsT shift(Number offset) const;

        /**
         * checks whether _rhs is contained in the left hand side
         *
         * A DBM X contains a DBM Y if the lower bounds of Y are greater or equal than the lower bounds of X
         * and the upper bounds of Y are smaller or equal than the upper bounds of X.
         *
         * This is the case if for every entry i,j in Y d_ij is lower or equal than the corresponding d_ij in X
         * @param _rhs
         * @return true is lhs contains rhs
         */
        bool contains(const DifferenceBoundsT &_rhs) const;

        /**
         * intersects the DBM with the bound given by index x, y and bound value bound
         * i.e. x-y <= bound
         * @param x
         * @param y
         * @param bound
         * @return the intersection of the DBM with constraint x-y bound
         */
        DifferenceBoundsT intersectConstraint(const int x, const int y, const DBMEntry &bound) const;

        /**
         * intersects the DBM with the bound given set of constraints
         * i.e. x-y <= bound
         * @param x
         * @param y
         * @param bound
         * @return the intersection of the DBM with constraint x-y bound
         */
        std::pair<CONTAINMENT, DifferenceBoundsT>
        intersectConstraints(const matrix_t<Number> constraints, const vector_t<Number> constants,
                             const CONTAINMENT defaultOnEmptyConstraints) const;

        /**
         * extrapolates the current DBM by using the ExtraM Method. A description
         * can be found in: Behrman, Bouyer "Lower and Upper Bounds in Zone Based Abstractions of Timed Automata"
         * @param MBounds List of DBMEntries describing the maximal Bounds for each variable i.e. the largest constant the variable is compared against. Note that the BOUND_TYPE has no effect unless it is infinity which denotes that the variable is not compared against any constant (i.e. is interpreted as -INFTY). The Bound for the 0 clock is 0.
         * @return The extrapolated DBM
         */
        DifferenceBoundsT extraM(const vector_t<DBMEntry> &MBounds) const;

        /**
         * extrapolates the current DBM by using the ExtraM+ Method. A description
         * can be found in: Behrman, Bouyer "Lower and Upper Bounds in Zone Based Abstractions of Timed Automata"
         * @param MBounds List of DBMEntries describing the maximal Bounds for each variable i.e. the largest constant the variable is compared against. Note that the BOUND_TYPE has no effect unless it is infinity which denotes that the variable is not compared against any constant (i.e. is interpreted as -INFTY) The Bound for the 0 clock is 0.
         * @return The extrapolated DBM
         */
        DifferenceBoundsT extraMPlus(const vector_t<DBMEntry> &MBounds) const;

        /**
         * extrapolates the current DBM by using the ExtraLU Method. A description
         * can be found in: Behrman, Bouyer "Lower and Upper Bounds in Zone Based Abstractions of Timed Automata"
         *
         * Lower and upper bounds are defined as follows:
         * The maximal lower bound denoted L(x) (resp. maximal upper bound U(x)) of clock x is the maximal
         * constant k such that there exists a constraint x>k or x>=k (resp x<k or x<=k) in a guard
         * of some transition or in an invariant of some location of the automaton. If such a constant
         * does not exist we set L(x) (resp. U(x)) to -INFTY. (Here: DBMEntry with BOUNDTYPE::INFTY)
         *
         * @param LBounds List of DBMEntries describing the maximal lower Bound for each variable i.e. the largest constant the variable is compared against. Note that the BOUND_TYPE has no effect unless it is infinity which denotes that the variable is not compared against any constant (i.e. is interpreted as -INFTY) The Bound for the 0 clock is 0.
         * @param UBounds List of DBMEntries describing the maximal upper Bound for each variable i.e. the largest constant the variable is compared against. Note that the BOUND_TYPE has no effect unless it is infinity which denotes that the variable is not compared against any constant (i.e. is interpreted as -INFTY) The Bound for the 0 clock is 0.
         * @return The extrapolated DBM
         */
        DifferenceBoundsT extraLU(const vector_t<DBMEntry> &LBounds, const vector_t<DBMEntry> &UBounds) const;

        /**
         * extrapolates the current DBM by using the ExtraLU+ Method. A description
         * can be found in: Behrman, Bouyer "Lower and Upper Bounds in Zone Based Abstractions of Timed Automata"
         *
         * see extraLU(LBounds,UBounds) for a definition of lower and upper bounds in this context.
         *
         * @param LBounds List of DBMEntries describing the maximal lower Bound for each variable i.e. the largest constant the variable is compared against. Note that the BOUND_TYPE has no effect unless it is infinity which denotes that the variable is not compared against any constant (i.e. is interpreted as -INFTY) The Bound for the 0 clock is 0.
         * @param UBounds List of DBMEntries describing the maximal upper Bound for each variable i.e. the largest constant the variable is compared against. Note that the BOUND_TYPE has no effect unless it is infinity which denotes that the variable is not compared against any constant (i.e. is interpreted as -INFTY) The Bound for the 0 clock is 0.
         * @return The extrapolated DBM
         */
        DifferenceBoundsT extraLUPlus(const vector_t<DBMEntry> &LBounds, const vector_t<DBMEntry> &UBounds) const;

        friend std::ostream &operator<<(std::ostream &ostr, const DifferenceBoundsT<Number, Converter, Setting> &db) {
            long rows = db.getDBM().rows();
            long cols = db.getDBM().cols();
            if (rows > 0 && cols > 0) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        ostr << db.getDBM()(i, j);
                    }
                    ostr << "\n";
                }
            }
            return ostr;
        }

        friend std::ostream &operator<<(std::ostream &ostr, const BOUND_TYPE value) {
            switch (value) {
                case SMALLER:
                    ostr << "<";
                    break;
                case SMALLER_EQ:
                    ostr << "<=";
                    break;
                case INFTY:
                    ostr << "inf";
                    break;
                default:
                    ostr << "undef";
                    break;
            }
            return ostr;
        }

        friend bool operator==(const DifferenceBoundsT<Number, Converter, Setting> &lhs,
                               const DifferenceBoundsT<Number, Converter, Setting> &rhs) {
            if (lhs.getDBM().cols() != rhs.getDBM().cols() || lhs.getDBM().rows() != rhs.getDBM().rows()) {
                return false;
            }
            for (int i = 0; i < lhs.getDBM().rows(); i++) {
                for (int j = 0; j < lhs.getDBM().rows(); j++) {
                    if (lhs.getDBM()(i, j) != rhs.getDBM()(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        }
    };

/** @} */

}  // namespace hypro
#include "DifferenceBounds.tpp"
