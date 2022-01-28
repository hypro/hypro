/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 27.01.22.
 */

#pragma once
#include "ReachTreev2.h"

namespace hypro {

template<typename R>
struct DepthFirst {
	constexpr bool operator()(const ReachTreeNode<R>* lhs, const ReachTreeNode<R>* rhs) {
		auto lhsDepth = lhs->getDepth();
		auto rhsDepth = rhs->getDepth();
		if(lhsDepth > rhsDepth) {
			return true;
		}
		if(lhsDepth < rhsDepth) {
			return false;
		}
		// use pointer comparison if nothing works
		return lhs < rhs;
	}
};

template<typename R>
struct BreadthFirst {
	constexpr bool operator()(const ReachTreeNode<R>* lhs, const ReachTreeNode<R>* rhs) {
		auto lhsDepth = lhs->getDepth();
		auto rhsDepth = rhs->getDepth();
		if(lhsDepth < rhsDepth) {
			return true;
		}
		if(lhsDepth > rhsDepth) {
			return false;
		}
		// use pointer comparison if nothing works
		return lhs < rhs;
	}
};

template<typename R>
struct LeastLocationCycleCount {
	std::size_t largestLocationCycle(const ReachTreeNode<R>* in) {
		std::map<Location<typename R::NumberType>*, std::size_t> counts;
		for(const auto& intervalTransitionPair : in->getPath()) {
			counts[intervalTransitionPair.second->getSource()] += 1;
		}
		return std::max_element(std::begin(counts), std::end(counts), [](const auto &aPair, const auto &bPair){return aPair.second < bPair.second;}).second;
	}

	constexpr bool operator()(const ReachTreeNode<R>* lhs, const ReachTreeNode<R>* rhs) {
		auto lhsCycles = largestLocationCycle(lhs);
		auto rhsCycles = largestLocationCycle(rhs);
		if(lhsCycles < rhsCycles) {
			return true;
		}
		if(lhsCycles > rhsCycles) {
			return false;
		}
		// use pointer comparison if nothing works
		return lhs < rhs;
	}
};

} // namespace hypro
