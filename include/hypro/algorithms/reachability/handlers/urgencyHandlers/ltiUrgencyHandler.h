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
	std::vector<Representation> urgentSetDifference( const std::vector<Representation>& segment, Transition<Number>* trans );
	/**
	 * @brief Compute the convex hull of the set difference with the segment and the jump enabling set of the transition.
	 * @param segment The current (unconstrained) segment.
	 * @param trans The urgent transition.
	 * @return Convex hull of the set difference result.
	 */
	Representation cutoff( Representation const& segment, Transition<Number>* trans );
};

}  // namespace hypro

#include "ltiUrgencyHandler.tpp"
