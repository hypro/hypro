/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Dictionary.h"

namespace hypro {

    template<typename Number>
    Dictionary<Number>::Dictionary(const Dictionary &rhs)
            : mDictionary(rhs.tableau()), mB(rhs.basis()), mN(rhs.cobasis()) {}

    template<typename Number>
    Dictionary<Number>::Dictionary(const matrix_t<Number> &rhs, std::vector<Eigen::Index> basis,
                                   std::vector<Eigen::Index> cobasis)
            : mDictionary(rhs), mB(basis), mN(cobasis) {}

    template<typename Number>
    Dictionary<Number>::Dictionary(const matrix_t<Number> &rhs, std::vector<Eigen::Index> basis,
                                   std::vector<Eigen::Index> cobasis, ConstrainSet<Number> constrains)
            : mDictionary(rhs), mB(basis), mN(cobasis), mConstrains(constrains) {}

    template<typename Number>
    Dictionary<Number>::Dictionary(const std::vector<Halfspace<Number>> &hsv) {
        int d = hsv[0].dimension();                                         // get dimension (number of cols)
        int n0 = int(hsv.size());                                         // get number of rows
        Eigen::Index i, j;                                                 // some indices.
        matrix_t<Number> Ab = matrix_t<Number>::Zero(n0 + 1, n0 +
                                                             1);     // create square matrix Ab, has one more row than constraints exist.

        for (i = 0; i < n0; ++i) {
            Ab(i, i + 1) = -1;
        }
        Ab(n0, 0) = -1;
        // Ab (is square) contains all -1's one right to the diagonal and lower left ist also -1.

        matrix_t<Number> An = matrix_t<Number>::Zero(n0 + 1, d + 1);    // An has dimensions as the final dictionary.

        // make first row (f in the paper) all ones except g-col, which is the last col.
        for (i = 0; i < d; ++i) {
            An(0, i) = 1;
        }
        An(0, d) = 0;

        // An contains all 1's in the first row (except the last col)
        for (i = 1; i < n0 + 1; ++i) {
            // last col holds negative offsets -> form n*x <= c to n*x -c <= 0
            An(i, d) = -1 * hsv[i - 1].offset();
            // write normals.
            for (j = 0; j < d; ++j) {
                An(i, j) = hsv[i - 1].normal()[j];
            }
        }

        // create actual dictionary -> negate rows and constants and move f-row (which was top) to the bottom, now containing all -1's
        mDictionary = Ab * An;
        // std::cout << "MDictionary: " << std::endl << mDictionary << std::endl;

        // initially the basis constraints are the n0 row indices. Note that the indices start from 1.
        for (i = 1; i < n0 + 1; ++i) {
            mB.push_back(i);
        }
        mB.push_back(Eigen::Index(n0 + d + 1));
        // the col indices are the cobasis initially.
        for (i = n0 + 1; i < n0 + d + 1; ++i) {
            mN.push_back(i);
        }
        mN.push_back(Eigen::Index(n0 + d + 2));
        // f=n0+d+1 ; g= n0+d+2

        // add variable bounds and assignments.
        for (i = 0; i < n0; ++i) {
            // initially all basic variables have the constant part as a lower bound (all vars are set to zero, 1st phase of simplex) and assigned the value 0.
            mConstrains.add(std::tuple<std::pair<bool, Number>, std::pair<bool, Number>, Number>(
                    // note: take negated -mDictionary(i,d), as it is on the LHS now. Assignment is 0, upper bound is infty.
                    std::pair<bool, Number>(false, -mDictionary(i, d)), std::pair<bool, Number>(true, Number(0)),
                    Number(0)));
        }
        for (i = 0; i < d; ++i) {
            // initially all non-basic variables are unbounded and assigned 0
            mConstrains.add(std::tuple<std::pair<bool, Number>, std::pair<bool, Number>, Number>(
                    // variables from co-basis (cols) are initially unbounded.
                    std::pair<bool, Number>(true, Number(0)), std::pair<bool, Number>(true, Number(0)), Number(0)));
        }
    }

    template<typename Number>
    std::vector<Eigen::Index> Dictionary<Number>::basis() const {
        return mB;
    }

    template<typename Number>
    std::vector<Eigen::Index> Dictionary<Number>::cobasis() const {
        return mN;
    }

    template<typename Number>
    ConstrainSet<Number> Dictionary<Number>::constrainSet() const {
        return mConstrains;
    }

    template<typename Number>
    Number Dictionary<Number>::get(Eigen::Index i, Eigen::Index j) const {
        return mDictionary(i, j);
    }

    template<typename Number>
    void Dictionary<Number>::setValue(Eigen::Index i, Eigen::Index j, Number val) {
        mDictionary(i, j) = val;
    }

    template<typename Number>
    matrix_t<Number> Dictionary<Number>::tableau() const {
        return mDictionary;
    }

    template<typename Number>
    void Dictionary<Number>::printDictionary() const {
        uint32_t i, j;
        std::cout << "\n mB size=";
        std::cout << mB.size();
        std::cout << "\n mN size=";
        std::cout << mN.size();
        std::cout << "\n mDictionary size=";
        std::cout << mDictionary.size();
        std::cout << "\n \n";

        std::cout << "mB = ";
        for (i = 0; i < mB.size(); ++i) {
            std::cout << mB[i];
            std::cout << ";  ";
        }
        std::cout << "\nmN = ";
        for (j = 0; j < mN.size(); ++j) {
            std::cout << mN[j];
            std::cout << ";  ";
        }
        std::cout << "\n \n";

        for (i = 0; i < mB.size(); ++i) {
            for (j = 0; j < mN.size(); ++j) {
                std::cout << mDictionary(i, j);
                std::cout << " ; ";
            }
            std::cout << "\n";
        }
        std::cout.flush();
    }

    template<typename Number>
    void Dictionary<Number>::pivotDictionary(Eigen::Index i, Eigen::Index j) {
        // std::cout << "Cols: " << mDictionary.cols() << ", rows: " << mDictionary.rows() << ", i: " << i << ", j: " << j << std::endl;
        //  update other cells
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()); ++colIndex) {
            for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()); ++rowIndex) {
                if (rowIndex != i && colIndex != j)
                    mDictionary(rowIndex, colIndex) = mDictionary(rowIndex, colIndex) -
                                                      (mDictionary(rowIndex, j) * mDictionary(i, colIndex)) /
                                                      mDictionary(i, j);
            }
        }

        // update row
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()); ++colIndex) {
            if (colIndex != j)
                mDictionary(i, colIndex) = -mDictionary(i, colIndex) / mDictionary(i, j);
        }

        // update col
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()); ++rowIndex) {
            if (rowIndex != i)
                mDictionary(rowIndex, j) = mDictionary(rowIndex, j) / mDictionary(i, j);
        }

        // update cell
#ifndef NDEBUG
        Number tmpEntry = mDictionary(i, j);
#endif
        mDictionary(i, j) = Number(1) / mDictionary(i, j);
#ifndef NDEBUG
        assert((tmpEntry < 0 && mDictionary(i, j) < 0) || (tmpEntry >= 0 && mDictionary(i, j) >= 0));
#endif
    }

    template<typename Number>
    void Dictionary<Number>::pivot(const Eigen::Index i, const Eigen::Index j) {
        pivotDictionary(i, j);

        Eigen::Index tmp = mB[i];
        mB[i] = mN[j];
        mN[j] = tmp;

#ifndef NDEBUG
        Dictionary tmpDic(*this);
        tmpDic.pivotDictionary(i, j);
        tmpDic.pivotDictionary(i, j);
        assert(this->mDictionary == tmpDic.tableau());
#endif
    }

    template<typename Number>
    bool Dictionary<Number>::fixOutOfBounds() {
        Number diff = 0;
        Eigen::Index index = 0;
        Eigen::Index indexRef = index;
        Eigen::Index pivot = 0;
        Eigen::Index pivotRef = pivot;
        if (!(mConstrains.outside(indexRef, diff, mB))) {     // is there any variable out of its bounds?
#ifdef DICT_DBG
            std::cout << "All variables are in their bounds." << std::endl;
#endif
            return false;
        }
        if (!(mConstrains.getPivot(indexRef, diff, pivotRef, mN, mDictionary))) {
            throw std::string("\n WARNING: empty set. \n");
        }  // is there a suitable pivot
#ifdef DICT_DBG
        std::cout << "Variable " << indexRef << " is out of bounds by " << diff << std::endl;
        std::cout << "suitable pivot: " << pivotRef << std::endl;
#endif
        this->pivot(indexRef, pivotRef);                                      // apply pivot.
        mConstrains.modifyAssignment(pivotRef, diff, mB, mN, mDictionary);  // update bounds.
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::selectBlandPivot(Eigen::Index &i, Eigen::Index &j) const {
        Eigen::Index minIndex = mDictionary.size() + 1;     // holds variable index of some candidate.
        Eigen::Index indexMin = mDictionary.size() + 1;     // holds position index of some candidate.
        std::vector<Eigen::Index> goodIndices;             // holds row indices for candidates for i.

        // determine s.
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {    // select the col
            if (mDictionary(mDictionary.rows() - 1, colIndex) > 0 && mN[colIndex] < minIndex) {
                minIndex = mN[colIndex];
                indexMin = colIndex;
            }
        }
        if (minIndex == mDictionary.size() + 1) {
            return false;
        }

        // determine candidates for r.
        j = indexMin;
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {
            if (mDictionary(rowIndex, j) < 0) {
                goodIndices.push_back(rowIndex);
            }
        }
        if (goodIndices.size() == 0) {
            return false;
        }

        i = goodIndices[0];
        minIndex = mB[goodIndices[0]];
        Number currentLambda = mDictionary(i, mDictionary.cols() - 1) / mDictionary(i, j);
        for (unsigned candidateRowIndex = 1;
             candidateRowIndex < unsigned(goodIndices.size()); ++candidateRowIndex) {  // select the candidate row
            // improving candidate
            if (mDictionary(goodIndices[candidateRowIndex], mDictionary.cols() - 1) /
                mDictionary(goodIndices[candidateRowIndex], j) > currentLambda) {
                i = goodIndices[candidateRowIndex];
                currentLambda = mDictionary(i, mDictionary.cols() - 1) / mDictionary(i, j);
                minIndex = mB[goodIndices[candidateRowIndex]];
            }
            // equals-candidate with better variable index -> follow variable order
            if (mDictionary(goodIndices[candidateRowIndex], mDictionary.cols() - 1) /
                mDictionary(goodIndices[candidateRowIndex], j) == currentLambda &&
                minIndex > mB[goodIndices[candidateRowIndex]]) {
                i = goodIndices[candidateRowIndex];
                currentLambda = mDictionary(i, mDictionary.cols() - 1) / mDictionary(i, j);
                minIndex = mB[goodIndices[candidateRowIndex]];
            }
        }
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::selectDualBlandPivot(Eigen::Index &i, Eigen::Index &j,
                                                  const std::vector<Eigen::Index> availableIndices) {
        Eigen::Index minIndex = mDictionary.size();
        Eigen::Index indexMin = mDictionary.size();
        std::vector<Eigen::Index> goodIndices;
        for (Eigen::Index rowIndex = 0; rowIndex < Eigen::Index(availableIndices.size()); ++rowIndex) {
            if (mDictionary(availableIndices[rowIndex], mDictionary.cols() - 1) < 0 &&
                mB[availableIndices[rowIndex]] < minIndex) {
                minIndex = mB[availableIndices[rowIndex]];
                indexMin = rowIndex;
            }
        }
        if (minIndex == Eigen::Index(mDictionary.size())) {
            return false;
        }
        i = indexMin;
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {
            if (mDictionary(availableIndices[i], colIndex) > 0) {
                goodIndices.push_back(colIndex);
            }
        }
        minIndex = mN[goodIndices[0]];
        j = goodIndices[0];
        Number currentLambda = mDictionary(mDictionary.rows() - 1, j) / mDictionary(availableIndices[i], j);
        for (unsigned colIndex = 1; colIndex < unsigned(goodIndices.size()); ++colIndex) {
            if (mDictionary(mDictionary.rows() - 1, goodIndices[colIndex]) /
                mDictionary(availableIndices[i], goodIndices[colIndex]) > currentLambda) {
                j = goodIndices[colIndex];
                currentLambda = mDictionary(mDictionary.rows() - 1, j) / mDictionary(availableIndices[i], j);
                minIndex = mN[goodIndices[colIndex]];
            }
            if (mDictionary(mDictionary.rows() - 1, goodIndices[colIndex]) /
                mDictionary(availableIndices[i], goodIndices[colIndex]) == currentLambda &&
                minIndex > mN[goodIndices[colIndex]]) {
                minIndex = mN[goodIndices[colIndex]];
                j = goodIndices[colIndex];
                currentLambda = mDictionary(mDictionary.rows() - 1, j) / mDictionary(availableIndices[i], j);
            }
        }
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::selectCrissCrossPivot(Eigen::Index &i, Eigen::Index &j) {
        unsigned minIndex = mDictionary.size();
        unsigned indexMin = mDictionary.size();
        bool b = true;
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {
            if (mDictionary(rowIndex, mDictionary.cols() - 1) < 0 && mB[rowIndex] < minIndex) {
                minIndex = mB[rowIndex];
                indexMin = rowIndex;
            }
        }
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {
            if (mDictionary(mDictionary.rows() - 1, colIndex) > 0 && mN[colIndex] < minIndex) {
                minIndex = mN[colIndex];
                indexMin = colIndex;
                b = false;
            }
        }
        if (minIndex == unsigned(mDictionary.size())) {
            return false;
        }
        if (b) {
            i = indexMin;
            minIndex = mDictionary.size();
            for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols()); ++colIndex) {
                if (mDictionary(i, colIndex) > 0 && mN[colIndex] < minIndex) {
                    minIndex = mN[colIndex];
                    j = colIndex;
                }
            }
        } else {
            j = indexMin;
            minIndex = mDictionary.size();
            for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()); ++rowIndex) {
                if (mDictionary(rowIndex, j) < 0 && mB[rowIndex] < minIndex) {
                    minIndex = mB[rowIndex];
                    i = rowIndex;
                }
            }
        }
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::isPrimalFeasible() const {
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {
            if (mDictionary(rowIndex, mDictionary.cols() - 1) < 0) {
                return false;
            }
        }
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::isDualFeasible() const {
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {
            if (mDictionary(mDictionary.rows() - 1, colIndex) > 0) {
                return false;
            }
        }
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::isOptimal() const {
#ifndef NDEBUG
        if (not(this->isPrimalFeasible() && this->isDualFeasible())) {
            std::cout << "This is not optimal: " << std::endl;
            printDictionary();
        }
#endif

        return this->isPrimalFeasible() && this->isDualFeasible();
    }

    template<typename Number>
    bool Dictionary<Number>::reverse_old(const Eigen::Index i, const Eigen::Index j) {
        Eigen::Index a = Eigen::Index(0);
        Eigen::Index b = Eigen::Index(0);
        Eigen::Index &i3 = a;
        Eigen::Index &j3 = b;
        if (mDictionary(i, j) == 0) {
            return false;
        };
        pivot(i, j);
        bool primal = isPrimalFeasible();
        bool existingPivot = selectBlandPivot(i3, j3);
        pivot(i, j);
        return (i == i3) && (j == j3) && existingPivot && primal;
    }

    template<typename Number>
    bool Dictionary<Number>::reverse(const Eigen::Index i, const Eigen::Index j) {
#ifdef DICT_DBG
        std::cout << __func__ << " i=" << i << ", j=" << j << "? ";
#endif
        if (mDictionary(mDictionary.rows() - 1, j) >= 0 || mDictionary(i, j) >= 0) {
#ifdef DICT_DBG
            std::cout << "False, cell content >= 0: " << (mDictionary(i, j) >= 0) << ", objective coefficient >= 0: "
                      << (mDictionary(mDictionary.rows() - 1, j) >= 0) << std::endl;
#endif
            return false;
        }
        Number maxRatio = mDictionary(i, mDictionary.cols() - 1) / mDictionary(i,
                                                                               j);  // equivalent to the lambda in the paper (almost, it is inverted in the paper)
        // check for minimality (maximality) of the ratio itself.
        for (int rowIndex = 0; rowIndex < mDictionary.rows() - 1; ++rowIndex) {
            if (mDictionary(rowIndex, j) < 0 &&
                maxRatio < mDictionary(rowIndex, mDictionary.cols() - 1) / mDictionary(rowIndex, j)) {
#ifdef DICT_DBG
                std::cout << "False, not minimal ratio. (Condition on lambda)" << std::endl;
#endif
                return false;
            }
        }

        // TODO: What is the purpose of this test? It searches all other rows with variable index of the row being less than the var index of
        // the selected column (some Bland stuff?) and checks, if their constant part is zero and the entry at (i,j) is larger than zero.
        for (int rowIndex = 0; rowIndex < mDictionary.rows() - 1; ++rowIndex) {
            if (rowIndex != int(i) && mB[rowIndex] < mN[j] &&
                (mDictionary(rowIndex, mDictionary.cols() - 1) == 0 && mDictionary(rowIndex, j) > 0)) {
#ifdef DICT_DBG
                std::cout << "False, third check fails." << std::endl;
#endif
                return false;
            }
        }

        // TODO: What is the purpose of this test? It searches all other cols, where the variable index is less than the variable index of the selected
        // row and tests, if the objective coefficient is larger than
        for (int colIndex = 0; colIndex < mDictionary.cols() - 1; ++colIndex) {
            if (mN[colIndex] < mB[i] &&
                colIndex != int(j) &&
                mDictionary(mDictionary.rows() - 1, colIndex) >
                mDictionary(mDictionary.rows() - 1, j) * mDictionary(i, colIndex) / mDictionary(i, j)) {
#ifdef DICT_DBG
                std::cout << "False, fourth check fails." << std::endl;
#endif
                return false;
            }
        }

#ifdef DICT_DBG
        std::cout << "True, manual check: ";
        Dictionary<Number> tmp(*this);
        tmp.pivot(i, j);
        std::cout << "Manual check: After pivot down:" << std::endl;
        tmp.printDictionary();
        std::cout << "Double version: " << std::endl;
        std::cout << convert<Number, double>(tmp.mDictionary) << std::endl;
        Eigen::Index ti, tj;
        tmp.selectBlandPivot(ti, tj);
        std::cout << "Selected pivots: " << ti << ", " << tj << std::endl;
        tmp.pivot(ti, tj);
        std::cout << (tmp == *this) << std::endl;
        assert(tmp == *this);
#endif
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::reverseDual_old(const Eigen::Index i, const Eigen::Index j,
                                             const std::vector<Eigen::Index> availableIndices) {
        Eigen::Index a = Eigen::Index(0);
        Eigen::Index b = Eigen::Index(0);
        Eigen::Index &i3 = a;
        Eigen::Index &j3 = b;
        if (mDictionary(availableIndices[i], j) == 0) {
            return false;
        };
        pivot(availableIndices[i], j);
        bool dual = isDualFeasible();
        bool existingPivot = selectDualBlandPivot(i3, j3, availableIndices);
        pivot(availableIndices[i], j);
        return (i == i3) && (j == j3) && existingPivot && dual;
    }

    template<typename Number>
    bool Dictionary<Number>::reverseDual(const Eigen::Index i, const Eigen::Index j,
                                         const std::vector<Eigen::Index> &availableIndices) {
        if (mDictionary(availableIndices[i], mDictionary.cols() - 1) <= 0 || mDictionary(availableIndices[i], j) <= 0) {
            return false;
        }
        Number maxRatio = mDictionary(mDictionary.rows() - 1, j) / mDictionary(availableIndices[i], j);
        for (Eigen::Index colIndex = 0; colIndex < Eigen::Index(mDictionary.cols() - 1); ++colIndex) {
            if (mDictionary(availableIndices[i], colIndex) > 0 &&
                maxRatio < mDictionary(mDictionary.rows() - 1, colIndex) / mDictionary(availableIndices[i], colIndex)) {
                return false;
            }
        }
        for (Eigen::Index colIndex = 0; colIndex < Eigen::Index(mDictionary.cols() - 1); ++colIndex) {
            if (colIndex != j && mN[colIndex] < mB[i] && (mDictionary(mDictionary.rows() - 1, colIndex) == 0 &&
                                                          mDictionary(availableIndices[i], colIndex) < 0)) {
                return false;
            }
        }
        for (Eigen::Index rowIndex = 0; rowIndex < Eigen::Index(availableIndices.size()); ++rowIndex) {
            if (mB[availableIndices[rowIndex]] < mN[j] && availableIndices[rowIndex] != i &&
                mDictionary(availableIndices[rowIndex], mDictionary.cols() - 1) >
                mDictionary(availableIndices[i], mDictionary.cols() - 1) * mDictionary(availableIndices[rowIndex], j) /
                mDictionary(availableIndices[i], j)) {
                return false;
            }
        }
        return true;
    }

    template<typename Number>
    bool Dictionary<Number>::isLexMin() {
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {
            if (mDictionary(rowIndex, mDictionary.cols() - 1) == 0) {
                for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {
                    if (mDictionary(rowIndex, colIndex) != 0 && mB[rowIndex] > mN[colIndex]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    template<typename Number>
    Point<Number> Dictionary<Number>::toPoint() const {
        std::vector<Number> point = std::vector<Number>(mDictionary.cols() - 1);
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {
            point[colIndex] = 0;
        }
        for (unsigned rowIndex = 0;
             rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {    // to optimize, not looking at every row
            if (mB[rowIndex] >= Eigen::Index(mB.size())) {
                point[mB[rowIndex] - mB.size()] = mDictionary(rowIndex, mDictionary.cols() - 1);
            }
        }
        return Point<Number>(point);
    }

    template<typename Number>
    std::vector<Eigen::Index> Dictionary<Number>::findZeros() {
        std::vector<Eigen::Index> indexList;
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {
            if (mDictionary(rowIndex, mDictionary.cols() - 1) == 0) {
                indexList.push_back(rowIndex);
            }
        }
        return indexList;
    }

    template<typename Number>
    void Dictionary<Number>::setOnes(const std::vector<Eigen::Index> &indices) {
        for (unsigned rowIndex = 0; rowIndex < unsigned(indices.size()); ++rowIndex) {
            mDictionary(indices[rowIndex], mDictionary.cols() - 1) = 1;
        }
    }

    template<typename Number>
    void Dictionary<Number>::setZeros(const std::vector<Eigen::Index> &indices) {
        for (unsigned rowIndex = 0; rowIndex < unsigned(indices.size()); ++rowIndex) {
            mDictionary(indices[rowIndex], mDictionary.cols() - 1) = 0;
        }
    }

    template<typename Number>
    void Dictionary<Number>::nonSlackToBase(std::vector<vector_t<Number>> &linealtySpace) {
        for (unsigned colIndex = 0; colIndex < mN.size() - 1; ++colIndex) {
            if (mN[colIndex] >= Eigen::Index(mB.size())) {    // non slack var in cobase -> pivot to base
                unsigned rowIndex = 0;
                // find suitable pivot
                for (rowIndex = 0; rowIndex < mB.size() - 1; ++rowIndex) {
                    if (mDictionary(rowIndex, colIndex) != 0 &&
                        mB[rowIndex] < Eigen::Index(mB.size())) {     // found pivot - apply.
                        this->pivot(rowIndex, colIndex);
                        break;
                    }
                }
                if (rowIndex == mB.size() - 1) {    // we did not find a suitable pivot
                    vector_t<Number> newLinealty = vector_t<Number>::Zero(mN.size() - 1);
                    newLinealty[mN[colIndex] - mB.size()] = 1;
                    for (rowIndex = 0; rowIndex < mB.size() - 1; ++rowIndex) {
                        if (mDictionary(rowIndex, colIndex) != 0 && mB[rowIndex] >= Eigen::Index(mB.size())) {
                            newLinealty[mB[rowIndex] - mB.size()] += mDictionary(rowIndex, colIndex);
                        }
                    }
                    linealtySpace.push_back(newLinealty);
                }
            }
        }
    }

    template<typename Number>
    void Dictionary<Number>::nonSlackToBase() {
        for (unsigned colIndex = 0; colIndex < mN.size() - 1; ++colIndex) {
            if (mN[colIndex] >= Eigen::Index(mB.size())) {
                unsigned rowIndex = 0;
                for (rowIndex = 0; rowIndex < mB.size() - 1; ++rowIndex) {
                    if (mDictionary(rowIndex, colIndex) != 0 && mB[rowIndex] < Eigen::Index(mB.size())) {
                        this->pivot(rowIndex, colIndex);
                        break;
                    }
                }
                if (rowIndex == mB.size() - 1) {
                    throw (std::string("WARNING: linealty space found"));
                }
            }
        }
    }

    template<typename Number>
    std::set<Eigen::Index> Dictionary<Number>::toCobase(const std::set<Eigen::Index> &saturatedIndices) {
        std::set<Eigen::Index> frozenCols;
        for (Eigen::Index colIndex = 0; colIndex < Eigen::Index(mN.size() - 1); ++colIndex) {
            if (saturatedIndices.end() != saturatedIndices.find(mN[colIndex] - 1)) {
                frozenCols.insert(colIndex);
            }
        }
        for (Eigen::Index rowIndex = 0; rowIndex < Eigen::Index(mB.size() - 1); ++rowIndex) {
            if (saturatedIndices.end() != saturatedIndices.find(mB[rowIndex] - 1)) {
                for (Eigen::Index colIndex = 0; colIndex < Eigen::Index(mN.size() - 1); ++colIndex) {
                    if (frozenCols.end() == frozenCols.find(colIndex) && mDictionary(rowIndex, colIndex) != 0) {
                        this->pivot(rowIndex, colIndex);
                        frozenCols.insert(colIndex);
                        break;
                    }
                }
            }
        }
        return frozenCols;
    }

    template<typename Number>
    void Dictionary<Number>::pushToBounds(Eigen::Index colIndex) {
        Number diff = mConstrains.diffToLowerBound(mN[colIndex] - 1);     // diff<0
        long minDiffIndex = mDictionary.size();
        for (unsigned rowIndex = 0; rowIndex < unsigned(mDictionary.rows()) - 1; ++rowIndex) {
            if (mConstrains.finiteLowerBound(mB[rowIndex] - 1) && mDictionary(rowIndex, colIndex) > 0 &&
                diff < (mConstrains.diffToLowerBound(mB[rowIndex] - 1) / mDictionary(rowIndex, colIndex))) {
                minDiffIndex = rowIndex;
                diff = mConstrains.diffToLowerBound(mB[rowIndex] - 1) / mDictionary(rowIndex, colIndex);
            }
        }
        if (minDiffIndex != mDictionary.size()) {
            this->pivot(minDiffIndex, colIndex);
            mConstrains.modifyAssignment(colIndex, mConstrains.diffToLowerBound(mB[minDiffIndex] - 1), mB, mN,
                                         mDictionary);
        } else {
            mConstrains.modifyAssignment(colIndex, diff, mB, mN, mDictionary);
        }
    }

    template<typename Number>
    std::set<vector_t<Number>> Dictionary<Number>::findCones() {
        std::set<vector_t<Number>> coneList;
        for (unsigned colIndex = 0; colIndex < unsigned(mDictionary.cols() - 1); ++colIndex) {
            if (mDictionary(mDictionary.rows() - 1, colIndex) < 0) {
                unsigned rowIndex = 0;
                while (rowIndex < unsigned(mDictionary.rows() - 1) && mDictionary(rowIndex, colIndex) >= 0) {
                    ++rowIndex;
                }
                if (rowIndex == unsigned(mDictionary.rows() - 1)) {
                    vector_t<Number> cone = vector_t<Number>::Zero(mDictionary.cols() - 1);
                    if (mN[colIndex] >= Eigen::Index(mB.size())) {
                        cone[mN[colIndex] - mB.size()] = Number(1);
                    }
                    for (rowIndex = 0; rowIndex < unsigned(mDictionary.rows() - 1); ++rowIndex) {
                        if (mB[rowIndex] >= Eigen::Index(mB.size())) {
                            cone[mB[rowIndex] - mB.size()] = mDictionary(rowIndex, colIndex);
                        }
                    }
                    for (int index = 0; index < cone.size(); ++index) {
                        if (cone[index] != 0) {
                            cone = cone / carl::abs(cone[index]);
                            break;
                        }
                    }
                    coneList.insert(cone);
                }
            }
        }
        return coneList;
    }

}  // namespace hypro
