
namespace hypro{

template<typename Number>
struct ReachabilitySettings {
	Number timebound = carl::rationalize<Number>(fReach_TIMEBOUND);
	std::size_t jumpDepth = fReach_JUMPDEPTH;
	Number timestep = carl::rationalize<Number>(fReach_TIMESTEP);
	std::string fileName = "out";
	unsigned long pplDenomimator = fReach_DENOMINATOR;

	friend std::ostream& operator<<( std::ostream& lhs, const ReachabilitySettings<Number>& rhs ) {
		lhs << "Local time-horizon: " << carl::toDouble(rhs.timebound) << std::endl;
		lhs << "Time-step size: " << carl::toDouble(rhs.timestep) << std::endl;
		lhs << "Jump-depth: " << rhs.jumpDepth << std::endl;
		return lhs;
	}
};

} // namespace hypro

