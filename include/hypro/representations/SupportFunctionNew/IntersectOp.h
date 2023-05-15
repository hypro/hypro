/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * IntersectOp.h
 *
 * A RootGrowNode that represents a intersection operation in the tree of operations representing a SupportFunction.
 *
 * @author Stefan Schupp
 * @author Phillip Tse
 */

#pragma once

#include "../../datastructures/Halfspace.h"
#include "RootGrowNode.h"

namespace hypro {

// Forward Declaration
    template<typename Number, typename Converter, typename Setting>
    class SupportFunctionNewT;

    template<typename Number, typename Converter, typename Setting>
    class RootGrowNode;

// Specialized subclass for sums as example of a binary operator
    template<typename Number, typename Converter, typename Setting>
    class IntersectOp : public RootGrowNode<Number, Converter, Setting> {
    private:
        ////// General Interface

        SFNEW_TYPE type = SFNEW_TYPE::INTERSECTOP;
        unsigned originCount = 2;
        std::size_t mDimension = 0;
        std::vector<std::shared_ptr<RootGrowNode<Number, Converter, Setting>>> mChildren;

        ////// Special members of this class

    public:
        ////// Constructors & Destructors

        IntersectOp() = delete;

        // Single sibling constructor
        IntersectOp(const SupportFunctionNewT<Number, Converter, Setting> &lhs,
                    const SupportFunctionNewT<Number, Converter, Setting> &rhs)
                : mDimension(lhs.dimension()) {
            assert(lhs.dimension() == rhs.dimension() || lhs.empty() || rhs.empty());
            lhs.addOperation(this, std::vector<SupportFunctionNewT<Number, Converter, Setting>>{rhs});
            // update and set empty-cache
            if (lhs.empty() || rhs.empty()) {
                RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
            }
        }

        // Multiple siblings constructor
        IntersectOp(const SupportFunctionNewT<Number, Converter, Setting> &lhs,
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

        // Data constructor
        IntersectOp(const RGNData &) {}

        ~IntersectOp() {}

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
            assert(false && "IntersectOp::compute should never be called");
            return std::vector<EvaluationResult<Number>>();
        }

        // Given evaluation result vecs, take the smallest supportValues coefficientwise
        std::vector<EvaluationResult<Number>>
        aggregate(std::vector<std::vector<EvaluationResult<Number>>> &resultStackBack,
                  const matrix_t<Number> &) const override {
            TRACE("hypro.representations.supportFunction", ": INTERSECT, accumulate results.")
            assert(resultStackBack.size() >= 2);
            // For all evaluation results in each direction in resultStackBack, iteratively look for the smallest evaluation result
            std::vector<EvaluationResult<Number>> accumulatedResult = resultStackBack.front();
            for (unsigned operand = 1; operand < resultStackBack.size(); ++operand) {
                for (unsigned index = 0; index < resultStackBack.front().size(); ++index) {
                    EvaluationResult<Number> r = resultStackBack.at(operand).at(index);
                    if (r.errorCode == SOLUTION::INFEAS)
                        return resultStackBack.at(operand);
                    if (r.errorCode == SOLUTION::INFTY) {
                        continue;
                    } else {
                        assert(r.errorCode == SOLUTION::FEAS);
                        if (accumulatedResult.at(index).errorCode == SOLUTION::INFTY) {
                            accumulatedResult.at(index) = r;
                            assert(accumulatedResult.at(index).errorCode != SOLUTION::INFTY);
                        } else {
                            assert(accumulatedResult.at(index).errorCode == SOLUTION::FEAS);
                            accumulatedResult.at(index).supportValue =
                                    r.supportValue < accumulatedResult.at(index).supportValue ? r.supportValue
                                                                                              : accumulatedResult.at(
                                            index).supportValue;
                            // accumulatedResult.at(index).optimumValue = r.optimumValue < accumulatedResult.at(index).optimumValue ? r.optimumValue : accumulatedResult.at(index).optimumValue;
                        }
                    }
                }
            }
            return accumulatedResult;
            /*
                    //For all evaluation results in each direction in resultStackBack, iteratively look for the smallest evaluation result
                    std::vector<EvaluationResult<Number>> accumulatedResult;
                    for ( unsigned i = 0; i < resultStackBack.front().size(); ++i ) {
                        EvaluationResult<Number> r = resultStackBack.front().at( i );
                        for ( const auto& res : resultStackBack ) {
                            if ( res[i].errorCode == SOLUTION::INFEAS ) return res;
                            if ( res[i].errorCode == SOLUTION::FEAS ) {
                                //Since the first result we compare with can still be infty
                                if ( r.errorCode == SOLUTION::INFTY ) {
                                    r.errorCode = SOLUTION::FEAS;
                                    r.supportValue = res[i].supportValue;
                                    std::cout << "IntersectOp::aggregate, entry was infty" << std::endl;
                                    //r.optimumValue = res[i].optimumValue;
                                } else {
                                    r.errorCode = SOLUTION::FEAS;
                                    r.supportValue = res[i].supportValue < r.supportValue ? res[i].supportValue : r.supportValue;
                                    std::cout << "IntersectOp::aggregate, after choosing min between " << r.supportValue << " and  " << res[i].supportValue << " r is:" << r.supportValue << std::endl;
                                    //r.optimumValue = res[i].optimumValue < r.optimumValue ? res[i].optimumValue : r.optimumValue;
                                }
                            }
                        }
                        accumulatedResult.emplace_back( r );
                    }
                    return accumulatedResult;
            */
        }

    public:
        /* Problem: Check emptiness of intersection of n convex objects
         * Solution 1: Template Evaluation
         *	- For each template direction, evaluate every object except one in that direction and the one into the -direction
         *	- If -direction is bigger in absolute value, then intersection not empty
         *	- Needs n*t*LP worst time, since every evaluate needs to solve a LP
         *	- Can stop early if direction directly found -> best time possible time is n*LP
         *	- Scales bad in dimension
         * Solution 2: Template Evaluation +
         *  - Like Solution 1, but parallel evaluation of 2 directions
         *	- Needs 0.5*n*t*LP time
         * Solution 3: Center of Gravity (COG)
         *  - For each object, generate a point within the object
         *		- Either on a halfspace (needs an LP, how to choose which halfspace?)
         *		- Or the center of gravity ob the object (needs to compute vertices, then averaging -> expensive as hell)
         *	- Compute the COG of all points and determine the direction as the vector from the COG to the points
         *	- Evaluate all directions -> but how to determine emptiness from that?
         *	- Needs n*LP to generate points and n*LPs for evaluation
         *
         * All these solutions were not ideal for dealing with halfspaces. Algorithm now (for only 2 objects):
         * - If both are not halfspaces: Use template evaluation: 2*#dir*LP
         * - If one is a halfspace and the other not: Use satisfiesHalfspace: 2*LP
         * - If none are halfspaces: Check linear dependency of halfspace normals: linear
         */
        bool empty(const std::vector<bool> &childrenEmpty) const override {
            // Current implementation uses Solution 1: template evaluation.

            // Quick check: If emptiness already computed, just return computation result
            if (RootGrowNode<Number, Converter, Setting>::mEmptyState != SETSTATE::UNKNOWN)
                return (RootGrowNode<Number, Converter, Setting>::mEmptyState == SETSTATE::EMPTY);

            // Quick check: If not already computed, check if at least one child is empty
            for (const auto &child: childrenEmpty) {
                if (child) {
                    RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
                    return true;
                }
            }

            // If no quick check worked: Turn children into SFs
            std::vector<SupportFunctionNewT<Number, Converter, Setting>> sfChildren;
            for (std::size_t i = 0; i < this->getChildren().size(); ++i) {
                sfChildren.emplace_back(SupportFunctionNewT<Number, Converter, Setting>(this->getChildren().at(i)));
            }

            // Choose one child for which we will always evaluate in the negative direction
            SupportFunctionNewT<Number, Converter, Setting> chosenOne = sfChildren.back();
            sfChildren.pop_back();
            std::vector<vector_t<Number>> directions = computeTemplate<Number>(mDimension,
                                                                               defaultTemplateDirectionCount);

            for (const auto &direction: directions) {
                // Determine supportValue of direction and reverse direction for chosenOne
                // Check if the supportValues don't overlap -> there is no intersection between at least two -> empty -> return true
                // Check in both directions since directions and children do not have to be symmetrical
                for (const auto &child: sfChildren) {
                    EvaluationResult<Number> chosenNegEval = chosenOne.evaluate(-direction, false);
                    EvaluationResult<Number> childPosEval = child.evaluate(direction, false);
                    if (childPosEval.supportValue < -chosenNegEval.supportValue &&
                        childPosEval.errorCode != SOLUTION::INFTY && chosenNegEval.errorCode != SOLUTION::INFTY) {
                        RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
                        return true;
                    }
                    EvaluationResult<Number> chosenPosEval = chosenOne.evaluate(direction, false);
                    EvaluationResult<Number> childNegEval = child.evaluate(-direction, false);
                    if (-childNegEval.supportValue > chosenPosEval.supportValue &&
                        childNegEval.errorCode != SOLUTION::INFTY && chosenPosEval.errorCode != SOLUTION::INFTY) {
                        RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::EMPTY;
                        return true;
                    }
                }
            }
            RootGrowNode<Number, Converter, Setting>::mEmptyState = SETSTATE::NONEMPTY;
            return false;
        }

        // Select smallest supremum of given suprema
        Point<Number> supremumPoint(std::vector<Point<Number>> &points) const override {
            Point<Number> smallestInftyNorm = points.front();
            for (auto &p: points) {
                if (p.dimension() == 0) return p;
                smallestInftyNorm =
                        Point<Number>::inftyNorm(smallestInftyNorm) < Point<Number>::inftyNorm(p) ? smallestInftyNorm
                                                                                                  : p;
            }
            return smallestInftyNorm;
        }

        // Only return true if all children contained the point before
        bool contains(const std::vector<bool> &v, const vector_t<Number> & /*point*/ ) const override {
            for (const auto &containedInChild: v) {
                if (!containedInChild)
                    return false;
            }
            return true;
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
