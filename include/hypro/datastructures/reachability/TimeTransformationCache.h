#pragma once
#include "../../algorithms/reachability/workers/LTIFlowpipeConstruction.h"
#include "../HybridAutomaton/Location.h"

#include <unordered_map>

namespace hypro {
template <class Number>
class TimeTransformationCache {
	std::unordered_map<Location<Number> const*, matrix_t<Number>> mMatrices{};

  public:
	matrix_t<Number> const& transformationMatrix( Location<Number> const* loc, tNumber timeStep, std::size_t I = 0 ) {
		auto search = mMatrices.find( loc );

		if ( search == mMatrices.end() ) {
			std::tie( search, std::ignore ) = mMatrices.emplace( loc, computeTimeTransformation( loc->getLinearFlow( I ), timeStep ) );
		}
		return search->second;
	}
};

}  // namespace hypro