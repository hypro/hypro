#pragma once
#include <carl/numbers/numbers.h>

namespace hypro{

template<typename Number>
struct ReachabilitySettings {
	Number timeBound;
	std::size_t jumpDepth;
	Number timeStep;
	std::string fileName;
	unsigned long pplDenomimator;
	std::vector<unsigned> plotDimensions;
	bool uniformBloating = false;

	ReachabilitySettings<Number>()
		: timeBound(0)
		, jumpDepth(0)
		, timeStep(0)
		, fileName("out")
		, pplDenomimator(1)
		, plotDimensions()
	{}

	ReachabilitySettings<Number>(const ReachabilitySettings<Number>& _orig) = default;
	ReachabilitySettings<Number>& operator=(const ReachabilitySettings<Number>& _rhs) = default;

	friend std::ostream& operator<<( std::ostream& lhs, const ReachabilitySettings<Number>& rhs ) {
		lhs << "Local time-horizon: " << carl::toDouble(rhs.timeBound) << std::endl;
		lhs << "Time-step size: " << carl::toDouble(rhs.timeStep) << std::endl;
		lhs << "Jump-depth: " << rhs.jumpDepth << std::endl;
		return lhs;
	}
};

} // namespace hypro

