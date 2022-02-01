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

/**
 * Heuristics which priorizes a high depth of a node, i.e., implements a depth-first approach
 * @tparam R
 */
template <typename R>
struct DepthFirst {
	constexpr bool operator()( const ReachTreeNode<R>* lhs, const ReachTreeNode<R>* rhs ) {
		auto lhsDepth = lhs->getDepth();
		auto rhsDepth = rhs->getDepth();
		if ( lhsDepth > rhsDepth ) {
			return true;
		}
		if ( lhsDepth < rhsDepth ) {
			return false;
		}
		// use pointer comparison if nothing works
		return lhs < rhs;
	}
};

/**
 * Heuristics which priorizes a low depth of a node, i.e., implements a breadth-first approach
 * @tparam R
 */
template <typename R>
struct BreadthFirst {
	constexpr bool operator()( const ReachTreeNode<R>* lhs, const ReachTreeNode<R>* rhs ) {
		auto lhsDepth = lhs->getDepth();
		auto rhsDepth = rhs->getDepth();
		if ( lhsDepth < rhsDepth ) {
			return true;
		}
		if ( lhsDepth > rhsDepth ) {
			return false;
		}
		// use pointer comparison if nothing works
		return lhs < rhs;
	}
};

/**
 * Heuristics functor which takes the maximum number of repeated locations (excluding the last one) on the path to the node as a metric. The idea is to rate nodes with a lower cycle-count as better to enforce progress instead of looping.
 * @tparam R
 */
template <typename R>
struct LeastLocationCycleCount {
	/**
	 * Function to compute the largest number of repeated locations on a path to the passed node.
	 * @details Note that the last location on the path is not considered.
	 * @param in The node
	 * @return The count of the occurrences of the location which appears the most on the path to the node.
	 */
	std::size_t largestLocationCycle( const ReachTreeNode<R>* in ) {
		std::map<Location<typename R::NumberType>*, std::size_t> counts;
		for ( const auto& intervalTransitionPair : in->getPath().elements ) {
			counts[intervalTransitionPair.second->getSource()] += 1;
		}
		return std::max_element( std::begin( counts ), std::end( counts ), []( const auto& aPair, const auto& bPair ) { return aPair.second < bPair.second; } )->second;
	}

	constexpr bool operator()( const ReachTreeNode<R>* lhs, const ReachTreeNode<R>* rhs ) {
		auto lhsCycles = largestLocationCycle( lhs );
		auto rhsCycles = largestLocationCycle( rhs );
		if ( lhsCycles < rhsCycles ) {
			return true;
		}
		if ( lhsCycles > rhsCycles ) {
			return false;
		}
		// use pointer comparison if nothing works
		return lhs < rhs;
	}
};

}  // namespace hypro
