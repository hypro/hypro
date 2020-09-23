/*
 * Class that describes a location of a stochastic hybrid automaton.
 */

#pragma once

#include "Location.h"

namespace hypro {

template <typename Number>
class StochasticTransition;

/**
 * @brief      Class for a location in a stochastic automaton.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class StochasticLocation : public Location<Number> {
  public:
	using stochasticTransitionVector = std::vector<std::unique_ptr<StochasticTransition<Number>>>;

  private:
	// Number mProbability = 1;
	matrix_t<Number> mLocationDistribution;

  public:
	StochasticLocation()
		: Location<Number>()
		, mLocationDistribution() {}

	StochasticLocation( const std::string& name )
		: Location<Number>( name )
		, mLocationDistribution() {}

	StochasticLocation( const StochasticLocation& _loc )
		: Location<Number>( _loc )
		, mLocationDistribution( _loc.getLocationDistribution() ) {
	}

	explicit StochasticLocation( const matrix_t<Number>& _mat )
		: Location<Number>( _mat )
		, mLocationDistribution() {}

	StochasticLocation( const matrix_t<Number>& _mat, stochasticTransitionVector&& _trans, const Condition<Number>& _inv, const matrix_t<Number>& _dist, stochasticTransitionVector&& _stotrans )
		: Location<Number>( _mat, _trans, _inv )
		, mLocationDistribution( _dist ) {}

	~StochasticLocation() {}

	void setLocationDistribution( const matrix_t<Number> locationDistribution ) {
		mLocationDistribution = locationDistribution;
	}
	const matrix_t<Number>& getLocationDistribution() const {
		return mLocationDistribution;
	}
};

}  // namespace hypro