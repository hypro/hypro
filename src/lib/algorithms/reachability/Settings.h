
#pragma once

namespace hypro{

template<typename Number>
struct ReachabilitySettings {
	Number timeBound;
	std::size_t jumpDepth;
	Number timeStep;
	std::string fileName;
	unsigned long pplDenomimator;

	ReachabilitySettings<Number>()
		: timeBound(carl::rationalize<Number>(fReach_TIMEBOUND))
		, jumpDepth(fReach_JUMPDEPTH)
		, timeStep(carl::rationalize<Number>(fReach_TIMESTEP))
		, fileName("out")
		, pplDenomimator(fReach_DENOMINATOR)
	{}

	ReachabilitySettings<Number>& operator=(const ReachabilitySettings<Number>& _rhs){
		timeBound = _rhs.timeBound;
		jumpDepth = _rhs.jumpDepth;
		timeStep = _rhs.timeStep;
		fileName = _rhs.fileName;
		pplDenomimator = _rhs.pplDenomimator;
		return *this;
	}

	friend std::ostream& operator<<( std::ostream& lhs, const ReachabilitySettings<Number>& rhs ) {
		lhs << "Local time-horizon: " << carl::toDouble(rhs.timeBound) << std::endl;
		lhs << "Time-step size: " << carl::toDouble(rhs.timeStep) << std::endl;
		lhs << "Jump-depth: " << rhs.jumpDepth << std::endl;
		return lhs;
	}
};

} // namespace hypro

