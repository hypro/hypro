/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace hypro {

template <typename Representation>
class ltiUrgencyHandler {
	using Number = typename Representation::NumberType;

  public:
	/**
	 * @brief Compute the set difference with the segment and the jump enabling set of the transition.
	 * Takes segment as vector to allow repeated application with multiple urgent jumps.
	 * @param segment Vector of sets that cover the segment.
	 * @param trans The urgent transition.
	 * @return Vector of sets that cover the set difference result.
	 */
	template <typename Location>
	std::vector<Representation> urgentSetDifference( const std::vector<Representation>& segment, Transition<Location>* trans );
	/**
	 * @brief Compute the convex hull of the set difference with the segment and the jump enabling set of the transition.
	 * @param segment The current (unconstrained) segment.
	 * @param trans The urgent transition.
	 * @return Convex hull of the set difference result.
	 */
	template <typename Location>
	Representation cutoff( Representation const& segment, Transition<Location>* trans );
};

}  // namespace hypro

#include "ltiUrgencyHandler.tpp"
