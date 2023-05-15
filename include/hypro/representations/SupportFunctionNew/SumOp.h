/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * SumOp.h
 *
 * A RootGrowNode that represents a Minkowski Sum operation in the tree of operations representing a SupportFunction.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "RootGrowNode.h"

namespace hypro {

// Forward Declaration
    template<typename Number, typename Converter, typename Setting>
    class SupportFunctionNewT;

// Specialized subclass for sums as example of a binary operator
    template<typename Number, typename Converter, typename Setting>
    class SumOp : public RootGrowNode<Number, Converter, Setting> {
    private:
        ////// General Interface

        SFNEW_TYPE type = SFNEW_TYPE::SUMOP;
        unsigned originCount = 2;
        std::size_t mDimension;
        std::vector<std::shared_ptr<RootGrowNode<Number, Converter, Setting>>> mChildren;

        ////// Special members of this class

    public:
        ////// Constructors & Destructors

        SumOp() = delete;

        SumOp(const SupportFunctionNewT<Number, Converter, Setting> &lhs,
              const SupportFunctionNewT<Number, Converter, Setting> &rhs)
                : mDimension(lhs.dimension()) {
            assert(lhs.dimension() == rhs.dimension() || lhs.empty() || rhs.empty());
            lhs.addOperation(this, std::vector<SupportFunctionNewT<Number, Converter, Setting>>{rhs});
            // update and set empty-cache
            if (lhs.empty() || rhs.empty()) {
                RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
            }
        }

        SumOp(const SupportFunctionNewT<Number, Converter, Setting> &lhs,
              const std::vector<SupportFunctionNewT<Number, Converter, Setting>> &rhs)
                : mDimension(lhs.dimension()) {
#ifndef NDEBUG
            for (const auto &sf: rhs) {
                assert(lhs.dimension() == sf.dimension() || lhs.empty() || sf.empty());
            }
#endif
            lhs.addOperation(this, rhs);
            // check for rhs is too expensive at the moment -> update usage of cache everywhere, then this is fine.
            if (lhs.empty()) {
                RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
            }
        }

        SumOp(const RGNData &) {}

        ~SumOp() {}

        ////// Getters and Setters

        SFNEW_TYPE getType() const override { return type; }

        unsigned getOriginCount() const override { return originCount; }

        std::size_t getDimension() const override { return mDimension; }

        RGNData *getData() const override { return new RGNData(); }

        void setDimension(const std::size_t d) override { mDimension = d; }

        ////// RootGrowNode Interface

        // Does nothing
        matrix_t<Number> transform(const matrix_t<Number> &param) const override {
            return param;
        }

        // Should not be reached
        std::vector<EvaluationResult<Number>> compute(const matrix_t<Number> &, bool) const override {
            assert("ERROR. USED COMPUTE FROM SUMOP SUBCLASS." && false);
            return std::vector<EvaluationResult<Number>>();
        }

        // Given two or more result vecs, sum them coefficientwise
        std::vector<EvaluationResult<Number>>
        aggregate(std::vector<std::vector<EvaluationResult<Number>>> &resultStackBack,
                  const matrix_t<Number> & /*currentParam*/ ) const override {
            assert(resultStackBack.size() >= 2);
            assert(resultStackBack.at(0).size() == resultStackBack.at(1).size());

            std::vector<EvaluationResult<Number>> accumulatedResult;
            for (unsigned index = 0; index < resultStackBack.front().size(); ++index) {
                EvaluationResult<Number> r;
                // r.optimumValue = vector_t<Number>::Zero( resultStackBack.front().front().optimumValue.rows() );
                for (const auto &res: resultStackBack) {
                    if (res[index].errorCode == SOLUTION::INFEAS) return res;
                    if (res[index].errorCode == SOLUTION::INFTY) {
                        r.errorCode = SOLUTION::INFTY;
                        r.supportValue = 1;
                        // std::cout << "SumOp::aggregate, entry was infty" << std::endl;
                        break;
                    } else {
                        r.errorCode = SOLUTION::FEAS;
                        r.supportValue += res[index].supportValue;
                        // std::cout << "SumOp::aggregate, r after adding is:" << r.supportValue << std::endl;
                        // if(res[index].optimumValue != vector_t<Number>::Zero(0)){
                        // if(res[index].errorCode != SOLUTION::INFTY){
                        //	r.optimumValue += res[index].optimumValue;
                        // }
                    }
                }
                accumulatedResult.emplace_back(r);
            }
            return accumulatedResult;
        }

        // Minkowski Sum empty when all operands (children) are empty
        // Minkowski Sum of an nonempty object with an empty object equals the nonempty object
        bool empty(const std::vector<bool> &childrenEmpty) const override {
            for (const auto &childEmpty: childrenEmpty) {
                if (!childEmpty) return false;
            }
            return true;
        }

        // Sum all suprema together
        Point<Number> supremumPoint(std::vector<Point<Number>> &points) const override {
            Point<Number> res = Point<Number>::Zero(points.front().dimension());
            for (const auto &p: points) {
                if (p.dimension() == 0) return p;
                res += p;
            }
            return res;
        }

        // Only return true if all children contained the point before
        bool contains(const std::vector<bool> &v, const vector_t<Number> & /*point*/ ) const override {
            for (auto containedInChild: v) {
                if (containedInChild) return true;
            }
            return false;
        }

        // Erases all dimensions from a copy of dimensions that are denoted in dims
        std::vector<std::size_t> intersectDims(const std::vector<std::vector<std::size_t>> &dims) const override {
            // we create the intersection of all results. Therefore we iterate over the first vector and check the other
            // result vectors, if the respective element is contained. Iterating over the first is sufficient, as elements
            // not in the first vector will not be in the intersection anyways.
            std::vector<std::size_t> accumulatedResult;
            for (unsigned pos = 0; pos < dims.begin()->size(); ++pos) {
                std::size_t element = dims.begin()->at(pos);
                bool elementInAllVectors = true;
                for (unsigned resIndex = 1; resIndex < dims.size(); ++resIndex) {
                    if (std::find(dims.at(resIndex).begin(), dims.at(resIndex).end(), element) ==
                        dims.at(resIndex).end()) {
                        elementInAllVectors = false;
                        break;
                    }
                }
                if (elementInAllVectors) {
                    // if this is a projection, we need to remove non-projected dimensions -> we could not have been in a projection since
                    // since this part of the function was only executed if a node had more than 2 children
                    accumulatedResult.emplace_back(element);
                }
            }
            return accumulatedResult;
        }
    };

}  // namespace hypro
