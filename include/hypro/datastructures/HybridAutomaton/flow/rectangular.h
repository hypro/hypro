/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../types.h"
#include "../../../util/sequenceGeneration/SequenceGenerator.h"

#include <iosfwd>
#include <map>

namespace hypro {

    template<typename Number>
    class rectangularFlow {
    public:
        using flowMap = typename std::map<carl::Variable, carl::Interval<Number>>;

    private:
        flowMap mFlowIntervals;

    public:
        rectangularFlow() = default;

        rectangularFlow(const rectangularFlow<Number> &in) = default;

        explicit rectangularFlow(const flowMap &intervals)
                : mFlowIntervals(intervals) {}

        virtual ~rectangularFlow() {}

        [[nodiscard]]
        static DynamicType type() { return DynamicType::rectangular; }

        void setFlowIntervals(const flowMap &in) { mFlowIntervals = in; }

        void setFlowIntervalForDimension(const carl::Interval<Number> &intv, carl::Variable dim) {
            mFlowIntervals[dim] = intv;
        }

        [[nodiscard]]
        const flowMap &getFlowIntervals() const { return mFlowIntervals; }

        /**
         * Creates a vector of intervals from the current flow.
         * @details Attention: For this to work correctly, the VariablePool has to be initialized properly, i.e., for all
         * used dimensions, a carl::Variable needs to be registered, such that for each i=0,...,d a corresponding carl
         * variable exists. Furthermore, the flow defined by a variable-interval mapping needs to be aligned to this, which
         * can be checked with the isConsistent() method.
         * @return A vector of intervals, ordered according to the ordering defined in the VariablePool
         */
        [[nodiscard]]
        std::vector<carl::Interval<Number>> getOrderedIntervals() const {
            std::vector<carl::Interval<Number>> result;
            result.reserve(mFlowIntervals.size());
            for (std::size_t dim = 0; dim < mFlowIntervals.size(); ++dim) {
                result.push_back(mFlowIntervals.at(VariablePool::getInstance().carlVarByIndex(dim)));
            }
            return result;
        }

        [[nodiscard]]
        const carl::Interval<Number> &getFlowIntervalForDimension(carl::Variable dim) const {
//			for(auto& flow : mFlowIntervals) {
//				std::cout << "flow: " << flow << std::endl;
//			}

//			std::cout << "to find: " << dim << std::endl;
//			std::cout << "found?: " << mFlowIntervals.at(dim) << std::endl;
			assert(mFlowIntervals.find(dim) != mFlowIntervals.end());
            return mFlowIntervals.at(dim);
        }

        [[nodiscard]]
        std::size_t dimension() const { return mFlowIntervals.size(); }

        [[nodiscard]]
        std::size_t size() const { return mFlowIntervals.size(); }

        [[nodiscard]]
        bool empty() const { return mFlowIntervals.empty(); }

        [[nodiscard]]
        DynamicType getDynamicsType() const {
            if (isTimed()) {
                return DynamicType::timed;
            }
            if (isDiscrete()) {
                return DynamicType::discrete;
            }
            if (isSingular()) {
                return DynamicType::singular;
            }
            return DynamicType::rectangular;
        }

        [[nodiscard]]
        DynamicType getDynamicsType(std::size_t varIndex) const {
            if (isTimed(varIndex)) {
                return DynamicType::timed;
            }
            if (isDiscrete(varIndex)) {
                return DynamicType::discrete;
            }
            if (isSingular(varIndex)) {
                return DynamicType::singular;
            }
            return DynamicType::rectangular;
        }

        [[nodiscard]]
        bool isTimed() const {
            for (const auto &keyVal: mFlowIntervals) {
                if (keyVal.second != carl::Interval<Number>(1)) {
                    return false;
                }
            }
            return true;
        }

        [[nodiscard]]
        bool isTimed(std::size_t varIndex) const {
            return mFlowIntervals.at(VariablePool::getInstance().carlVarByIndex(varIndex)) == carl::Interval<Number>(1);
        }

        [[nodiscard]]
        bool isDiscrete() const {
            for (const auto &keyVal: mFlowIntervals) {
                if (keyVal.second != carl::Interval<Number>(0)) {
                    return false;
                }
            }
            return true;
        }

        bool isDiscrete(std::size_t varIndex) const {
            return mFlowIntervals.at(VariablePool::getInstance().carlVarByIndex(varIndex)) == carl::Interval<Number>(0);
        }

        [[nodiscard]]
        bool isSingular() const {
            for (const auto &[_, interval]: mFlowIntervals) {
#ifdef CARL_OLD_STRUCTURE
                if ( !interval.isPointInterval() ) {
#else
                if (!interval.is_point_interval()) {
#endif
                    return false;
                }
            }
            return true;
        }

        [[nodiscard]]
        bool isSingular(std::size_t varIndex) const {
#ifdef CARL_OLD_STRUCTURE
            return mFlowIntervals.at( VariablePool::getInstance().carlVarByIndex( varIndex ) ).isPointInterval();
#else
            return mFlowIntervals.at(VariablePool::getInstance().carlVarByIndex(varIndex)).is_point_interval();
#endif
        }

        friend bool operator==(const rectangularFlow<Number> &lhs, const rectangularFlow<Number> &rhs) {
            if (lhs.getFlowIntervals().size() != rhs.getFlowIntervals().size()) {
                return false;
            }

            for (const auto &keyVal: lhs.getFlowIntervals()) {
                if (rhs.getFlowIntervals().find(keyVal.first) == rhs.getFlowIntervals().end()) {
                    return false;
                } else {
                    if (keyVal.second != rhs.getFlowIntervalForDimension(keyVal.first)) {
                        return false;
                    }
                }
            }
            return true;
        }

        friend bool operator!=(const rectangularFlow<Number> &lhs, const rectangularFlow<Number> &rhs) {
            return !(lhs == rhs);
        }

        friend std::ostream &operator<<(std::ostream &out, const rectangularFlow<Number> &in) {
            for (const auto &i: in.getFlowIntervals()) {
                out << i.first << ": " << i.second << ", ";
            }
            return out;
        }

        [[nodiscard]]
        std::vector<Point<Number>> vertices() const {
            // enumerate all 2^d combinations of interval bounds to obtain all vertices.
            std::size_t dim = this->size();
            Combinator sequencer{2, dim};
            std::vector<Point<Number>> flowVertices;
            while (!sequencer.end()) {
                std::vector<std::size_t> selection = sequencer();
                Point<Number> vertex{vector_t<Number>::Zero(dim)};
                for (std::size_t i = 0; i < selection.size(); ++i) {
                    assert(selection[i] == 1 || selection[i] == 0);
                    if (selection[i] == 0) {
                        vertex[i] = this->getFlowIntervals().at(VariablePool::getInstance().carlVarByIndex(i)).lower();
                    } else {
                        vertex[i] = this->getFlowIntervals().at(VariablePool::getInstance().carlVarByIndex(i)).upper();
                    }
                }
                flowVertices.emplace_back(std::move(vertex));
            }
            return flowVertices;
        }

        /**
         * Checks, whether the stored variables are initialized in the VariablePool and whether their sequence of
         * associated indices (dimension indices) is without missing elements.
         * @return True, if the flow is consistent and complete with respect to the VariablePool
         */
        [[nodiscard]]
        bool isConsistent() const {
            for (std::size_t i = 0; i < mFlowIntervals.size(); ++i) {
                if (!VariablePool::getInstance().hasDimension(i) ||
                    mFlowIntervals.count(VariablePool::getInstance().carlVarByIndex(i)) == 0) {
                    return false;
                }
            }
            return true;
        }
    };

}  // namespace hypro

namespace std {

    template<typename Number>
    struct hash<hypro::rectangularFlow<Number>> {
        std::size_t operator()(const hypro::rectangularFlow<Number> &f) const {
            std::size_t seed = 0;
            for (const auto &i: f.getFlowIntervals()) {
                carl::hash_add(seed, std::hash<carl::Variable>()(i.first));
                carl::hash_add(seed, std::hash<carl::Interval<Number>>()(i.second));
            }
            return seed;
        }
    };

}  // namespace std
