/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../types.h"
#include "linear.h"

#include <iosfwd>

namespace hypro {

    template<typename Number>
    class affineFlow : public linearFlow<Number> {
    public:
    protected:
        vector_t<Number> mTranslation;
        mutable TRIBOOL mIsNoTranslation = TRIBOOL::NSET;

    public:
        affineFlow() = default;

        affineFlow(const affineFlow<Number> &in) = default;

        affineFlow(const matrix_t<Number> &A, const vector_t<Number> &b)
                : linearFlow<Number>(A), mTranslation(b) {}

        virtual ~affineFlow() {}

        static DynamicType type() { return DynamicType::affine; }

        std::size_t dimension() const { return linearFlow<Number>::dimension(); }

        void setTranslation(const vector_t<Number> &newB) {
            mTranslation = newB;
            mIsNoTranslation = TRIBOOL::NSET;
        }

        const vector_t<Number> &getTranslation() const { return mTranslation; }

        DynamicType getDynamicsType() const {
            if (dimension() == 0 || mTranslation == vector_t<Number>::Zero(dimension())) {
                return linearFlow<Number>::getDynamicsType();
            }
            return DynamicType::affine;
        }

        bool hasTranslation() const {
            if (mIsNoTranslation == TRIBOOL::NSET) {
                if (mTranslation.rows() == 0) {
                    mIsNoTranslation = TRIBOOL::FALSE;
                    return false;
                } else {
                    mIsNoTranslation = mTranslation == vector_t<Number>::Zero(mTranslation.rows()) ? TRIBOOL::TRUE
                                                                                                   : TRIBOOL::FALSE;
                }
            }
            return mIsNoTranslation == TRIBOOL::FALSE;
        }

        bool isTimed() const {
            TRACE("hypro.decisionEntity", "Flowmatrix: " << linearFlow<Number>::getFlowMatrix());
            if (linearFlow<Number>::isTimed()) {
                // TODO: we need to remove distinguishing of linear and affine flow.
                return true;
            }
            return linearFlow<Number>::hasNoFlow() && mTranslation == vector_t<Number>::Ones(mTranslation.rows());
        }

        bool isTimed(std::size_t varIndex) const {
            if (linearFlow<Number>::isTimed()) {
                // TODO: we need to remove distinguishing of linear and affine flow.
                return true;
            }
            return linearFlow<Number>::hasNoFlow(varIndex) && mTranslation(varIndex) == 1;
        }

        bool isDiscrete() const {
            return linearFlow<Number>::hasNoFlow() && !hasTranslation();
        }

        bool isDiscrete(std::size_t i) const {
            return linearFlow<Number>::hasNoFlow(i) && mTranslation(i) == 0;
        }

        std::vector<std::size_t> getNonDiscreteDimensions() const {
            std::vector<std::size_t> result;
            for (std::size_t d = 0; d < this->dimension(); ++d) {
                if (!isDiscrete(d)) {
                    result.push_back(d);
                }
            }
            return result;
        }

        friend bool operator==(const affineFlow<Number> &lhs, const affineFlow<Number> &rhs) {
            return (lhs.getFlowMatrix() == rhs.getFlowMatrix() && lhs.getTranslation() == rhs.getTranslation());
        }

        friend bool operator!=(const affineFlow<Number> &lhs, const affineFlow<Number> &rhs) {
            return !(lhs == rhs);
        }

        friend std::ostream &operator<<(std::ostream &out, const affineFlow<Number> &in) {
            bool firstRow = true;
            // assemble flow matrix
            matrix_t<Number> fMat = matrix_t<Number>(in.mFlowMatrix.rows(), in.mFlowMatrix.cols() + 1);
            fMat.block(0, 0, in.mFlowMatrix.rows(), in.mFlowMatrix.cols()) = in.mFlowMatrix;
            fMat.col(fMat.cols() - 1) = in.mTranslation;
            if (fMat.rows() > 0) {
                for (Eigen::Index row = 0; row < fMat.rows(); ++row) {
                    if (!firstRow) {
                        out << "\n";
                    } else {
                        firstRow = false;
                    }
                    out << "x" << row << "' = " << to_string<Number>(fMat.row(row));
                }
            }
            return out;
        }
    };

}  // namespace hypro

namespace std {

    template<typename Number>
    struct hash<hypro::affineFlow<Number>> {
        std::size_t operator()(const hypro::affineFlow<Number> &f) const {
            std::size_t seed = 0;
            carl::hash_add(seed, std::hash<hypro::linearFlow<Number>>()(hypro::linearFlow<Number>(f)));
            carl::hash_add(seed, std::hash<hypro::vector_t<Number>>()(f.getTranslation()));
            return seed;
        }
    };

}  // namespace std
