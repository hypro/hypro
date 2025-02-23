/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Reset.h"

namespace hypro {

    template<typename Number>
    Reset<Number>::Reset(const matrix_t<Number> &mat, const vector_t<Number> &vec) {
        assert(mat.rows() == vec.rows());
        mAffineResets.emplace_back(mat, vec);
        mIntervalResets.emplace_back(std::vector<carl::Interval<Number>>(mat.rows(), createEmptyInterval<Number>()));
    }

    template<typename Number>
    Reset<Number>::Reset(const std::vector<carl::Interval<Number>> &intervals) {
        mAffineResets.emplace_back(matrix_t<Number>::Identity(intervals.size(), intervals.size()),
                                   vector_t<Number>::Zero(intervals.size()));
        mIntervalResets.emplace_back(intervals);
    }

    template<typename Number>
    const vector_t<Number> &Reset<Number>::getVector(std::size_t I) const {
        return mAffineResets[I].mTransformation.vector();
    }

    template<typename Number>
    const matrix_t<Number> &Reset<Number>::getMatrix(std::size_t I) const {
        return mAffineResets[I].mTransformation.matrix();
    }

    template<typename Number>
    matrix_t<Number> &Reset<Number>::rGetMatrix(std::size_t I) {
        return mAffineResets[I].mTransformation.rMatrix();
    }

    template<typename Number>
    vector_t<Number> &Reset<Number>::rGetVector(std::size_t I) {
        return mAffineResets[I].mTransformation.rVector();
    }

    template<typename Number>
    const std::vector<carl::Interval<Number>> &Reset<Number>::getIntervals(std::size_t I) const {
        return mIntervalResets[I].mIntervals;
    }

    template<typename Number>
    std::vector<carl::Interval<Number>> &Reset<Number>::rGetIntervals(std::size_t I) {
        return mIntervalResets[I].mIntervals;
    }

    template<typename Number>
    void Reset<Number>::setVector(const vector_t<Number> &in, std::size_t I) {
        assert(mAffineResets.size() == mIntervalResets.size());
        while (mAffineResets.size() < I + 1) {
            mAffineResets.emplace_back(AffineTransformation<Number>());
            mIntervalResets.emplace_back(IntervalAssignment<Number>());
        }
        assert(mAffineResets.size() == mIntervalResets.size());
        mAffineResets[I].mTransformation.rVector() = in;
        mHash = 0;
    }

    template<typename Number>
    void Reset<Number>::setMatrix(const matrix_t<Number> &in, std::size_t I) {
        assert(mAffineResets.size() == mIntervalResets.size());
        assert(in.rows() == in.cols());
        while (mAffineResets.size() < I + 1) {
            mAffineResets.emplace_back(AffineTransformation<Number>());
            mIntervalResets.emplace_back(IntervalAssignment<Number>());
        }
        assert(mAffineResets.size() == mIntervalResets.size());
        mAffineResets[I].mTransformation.setMatrix(in);
        mHash = 0;
    }

    template<typename Number>
    void Reset<Number>::setIntervals(const std::vector<carl::Interval<Number>> &intervals, std::size_t I) {
        assert(mAffineResets.size() == mIntervalResets.size());
        while (mIntervalResets.size() < I + 1) {
            mAffineResets.emplace_back(AffineTransformation<Number>());
            mIntervalResets.emplace_back(IntervalAssignment<Number>());
        }
        assert(mAffineResets.size() == mIntervalResets.size());
        mIntervalResets[I].mIntervals = intervals;
        mHash = 0;
    }

    template<typename Number>
    void Reset<Number>::addResetTransformation(const AffineTransformation<Number> trafo) {
        mAffineResets.push_back(trafo);
        mIntervalResets.emplace_back(IntervalAssignment<Number>());
    }

    template<typename Number>
    bool Reset<Number>::isAffineIdentity() const {
        return mAffineResets.empty() || std::all_of(mAffineResets.begin(), mAffineResets.end(),
                                                    [](const auto &affineReset) { return affineReset.isIdentity(); });
    }

    template<typename Number>
    bool Reset<Number>::isIntervalIdentity() const {
        return mIntervalResets.empty() || std::all_of(mIntervalResets.begin(), mIntervalResets.end(),
                                                      [](const auto &intervals) { return intervals.isIdentity(); });
    }

    template<typename Number>
    bool Reset<Number>::isIdentity() const {
        return isAffineIdentity() && isIntervalIdentity();
    }

    template<typename Number>
    bool Reset<Number>::isIdentity(std::size_t I) const {
        if (mAffineResets.empty() && mIntervalResets.empty()) {
            return true;
        }
        // compute offset
        std::size_t offset = I;
        std::size_t subspace = 0;
        // TODO write a test for this, there might be an off-by-one error here and there
        while (I > mAffineResets.at(subspace).size()) {
            ++subspace;
            I -= mAffineResets.at(subspace).size();
            offset -= mAffineResets.at(subspace).size();
        }
        matrix_t<Number> testRow = matrix_t<Number>::Zero(1, mAffineResets.at(subspace).mTransformation.dimension());
        testRow(0, offset) = 1;
        return mAffineResets.at(subspace).mTransformation.matrix().row(offset) == testRow &&
               mAffineResets.at(subspace).mTransformation.vector()(offset) == 0;
    }

    template<typename Number>
    std::size_t Reset<Number>::hash() const {
        if (mHash == 0) {
            mHash = std::hash<Reset<Number>>()(*this);
        }
        return mHash;
    }

    template<typename Number>
    Reset<Number> combine(
            const Reset<Number> &lhs, const Reset<Number> &rhs,
            const std::vector<std::string> haVar, const std::vector<std::string> lhsVar,
            const std::vector<std::string> rhsVar) {
        matrix_t<Number> newMat;
        vector_t<Number> newVec;

        if (lhs.isIdentity() && !rhs.isIdentity()) {
            newMat = combine(matrix_t<Number>(0, 0), rhs.getMatrix(), haVar, lhsVar, rhsVar);
            newVec = combine(vector_t<Number>(0), rhs.getVector());
        } else if (!lhs.isIdentity() && rhs.isIdentity()) {
            newMat = combine(lhs.getMatrix(), matrix_t<Number>(0, 0), haVar, lhsVar, rhsVar);
            newVec = combine(lhs.getVector(), vector_t<Number>(0));
        } else if (lhs.isIdentity() && rhs.isIdentity()) {
            return Reset<Number>();
        } else {
            assert(lhs.size() != 0);
            assert(rhs.size() != 0);
            assert(!lhs.isIdentity());
            assert(!rhs.isIdentity());

            // Todo: This is a corrected, yet ineffective method. Improve!
            newMat = matrix_t<Number>::Zero(haVar.size(), haVar.size());
            newVec = vector_t<Number>::Zero(haVar.size());
            std::size_t lhsIR = 0;
            std::size_t lhsIC = 0;
            std::size_t rhsIR = 0;
            std::size_t rhsIC = 0;
            bool admissible = true;     // flag used to denote a non-admissible reset, i.e. shared variables with different reset.
            // iterate over all rows
            for (std::size_t rowI = 0; rowI != haVar.size(); ++rowI) {
                if (lhsIR < lhsVar.size() && lhsVar[lhsIR] == haVar[rowI]) {
                    newVec(rowI) = lhs.getVector()(lhsIR);
                    // iterate over all columns
                    lhsIC = 0;
                    for (std::size_t colI = 0; colI != haVar.size(); ++colI) {
                        assert(lhsIC < lhsVar.size());
                        if (lhsVar[lhsIC] == haVar[colI]) {
                            newMat(rowI, colI) = lhs.getMatrix()(lhsIR, lhsIC);
                            ++lhsIC;
                            if (lhsIC == lhsVar.size()) {
                                break;
                            }
                        }
                    }
                    ++lhsIR;
                }
                if (rhsIR < rhsVar.size() && rhsVar[rhsIR] == haVar[rowI]) {
                    newVec(rowI) = rhs.getVector()(rhsIR);
                    // iterate over all columns
                    rhsIC = 0;
                    for (std::size_t colI = 0; colI != haVar.size(); ++colI) {
                        if (rhsVar[rhsIC] == haVar[colI]) {
                            // TODO: the check is not entirely correct, since the flow can be non-admissible but set to 0 in lhs and something != 0 in rhs.
                            if (newMat(rowI, colI) != 0 && rhs.getMatrix()(rhsIR, rhsIC) != newMat(rowI, colI)) {
                                admissible = false;
                                break;
                            }
                            newMat(rowI, colI) = rhs.getMatrix()(rhsIR, rhsIC);
                            ++rhsIC;
                            if (rhsIC == rhsVar.size()) {
                                break;
                            }
                        }
                    }
                    ++rhsIR;
                }
                if (!admissible)
                    break;
            }
            assert(admissible);
            // newMat = combine(lhs.getMatrix(), rhs.getMatrix(), haVar, lhsVar, rhsVar);
            // newVec = combine(lhs.getVector(), rhs.getVector());
        }
        return Reset<Number>{newMat, newVec};
    }

    template<typename Number>
    void Reset<Number>::decompose(const std::vector<std::vector<std::size_t>> &partition) {
        if (mAffineResets.size() == 0) {
            // empty constraints
            return;
        }
        if (mAffineResets.size() > 1 || mDecomposed) {
            // Already decomposed
            mDecomposed = true;
            return;
        }
        assert(mAffineResets.size() == 1);

        INFO("hypro.datastructures",
             "In the current state we assume that rectangular subspaces will not be decomposed.");

        // traverse reset variants to collect all assignments per proposed subspace
        ConstraintSetT<Number> cset = mAffineResets[0].mTransformation;
        DEBUG("hypro.datastructures", "Constraint Set before: \n " << cset);

        matrix_t<Number> constraintsOld(cset.matrix());
        vector_t<Number> constantsOld(cset.vector());
        auto oldIntervalAssignments = mIntervalResets[0].mIntervals;

        mAffineResets.clear();
        mIntervalResets.clear();

        // select constrains i,j,k into new constraint vector
        for (auto set: partition) {
#ifdef HYPRO_LOGGING
            DEBUG("hypro.datastructures", "decompose constraint for set: {");
            for (auto entry: set) {
                DEBUG("hypro.datastructures", "" << entry << ", ");
            }
            DEBUG("hypro.datastructures", "}");
#endif

            // new interval assignments are just copied, as we do not store the variable
            std::vector<carl::Interval<Number>> newIntervals;
            // std::vector<carl::Interval<Number>> newIntervals = oldIntervalAssignments;

            // for each row of the constraints check if it contains an entry for one of the variables of the set
            // and add the corresponding rows to a list of indices that are later added to a matrix
            std::vector<Eigen::Index> indicesToAdd;
            for (auto entry: set) {
                indicesToAdd.emplace_back(Eigen::Index(entry));
                newIntervals.emplace_back(oldIntervalAssignments[entry]);
            }

            // create a row matrix with numIndicesToAdd many rows
            matrix_t<Number> newMatrix = selectRows(constraintsOld, indicesToAdd);
            newMatrix = selectCols(newMatrix, set);

            // create final constant vector
            vector_t<Number> newVec = selectRows(constantsOld, indicesToAdd);

            ConstraintSetT<Number> newConstraintSet(newMatrix, newVec);
            mAffineResets.emplace_back(std::move(newConstraintSet));
            mIntervalResets.emplace_back(std::move(newIntervals));
        }

        mDecomposed = true;
        mHash = 0;
    }

    template<typename Number>
    void Reset<Number>::extendDimension() {
        for (auto &IntervalReset : mIntervalResets) {
            IntervalReset.mIntervals.emplace_back(createEmptyInterval<Number>());
        }
    }
    
    template<typename Number>
    Reset<Number> operator+(const Reset<Number> &lhs, const Reset<Number> &rhs) {
        if (!lhs.isIntervalIdentity() || !rhs.isIntervalIdentity()) {
            throw std::logic_error("Operator + is not yet implemented for interval resets.");
        }

        // since no reset also indicates identity, add shortcuts here
        if (lhs.getAffineResets().size() == 0) {
            return rhs;
        }
        if (rhs.getAffineResets().size() == 0) {
            return lhs;
        }
        // if both have defined some resets over subspaces, those need to be of similar size
        assert(lhs.getAffineResets().size() == rhs.getAffineResets().size());

        Reset<Number> res;
        for (std::size_t i = 0; i < lhs.getAffineResets().size(); ++i) {
            res.addResetTransformation(lhs.getAffineReset(i) + rhs.getAffineReset(i));
        }
        return res;
    }

}  // namespace hypro
