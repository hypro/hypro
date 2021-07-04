#pragma once
#include "../../types.h"
#include "../../util/type_handling/representation_enums.h"
#include "../../util/type_handling/settings_enums.h"

#include <carl/numbers/numbers.h>
#include <iosfwd>
#include <string>

namespace hypro {

class Settings;

struct AnalysisParameters {
	tNumber timeStep = 0;												   ///< time step size for time-successor computation
	AGG_SETTING aggregation = AGG_SETTING::NO_AGG;						   ///< the forced aggregation settings
	int clustering = -1;												   ///< if clustering is used: number of clusters
	representation_name representation_type = representation_name::UNDEF;  ///< type of representation
	int representation_setting = 0;										   ///< used settings for the representation
	bool uniformBloating = false;
	REACH_SETTING reachability_analysis_method = REACH_SETTING::FORWARD;  ///< method of reachability analysis
	int timeStepFactor = 1;												  ///< the factor between the fixed time step and this time step, i.e. fixedTimeStep * timeStepFactor = timeStep. Can be negative.
};

struct FixedAnalysisParameters {
	size_t jumpDepth{ std::numeric_limits<int>::max() };  ///< bound for maximal number of executed jumps
	tNumber localTimeHorizon = 0;						  ///< bound for maximal duration of time elapse per flowpipe, use negative value for unbounded time (not always supported)
	tNumber fixedTimeStep = 0;							  ///< a time step that all timesteps of the analysis parameters are multiples of, i.e. fixedTimeStep * timeStepFactor = timeStep.
	/// computed on construction of the setting as the (fractional) gcd of the time steps
	bool detectFixedPoints = false;	 ///< true if an analyzer should try to detect a fixed point
#if HYPRO_USE_PPL
	unsigned long pplDenominator{ defaultPPLDenominator };
#endif
};

struct PlottingSettings {
	std::vector<std::vector<size_t>> plotDimensions{};
	std::vector<std::string> plotFileNames{};
	PLOTTYPE plottingFileType = PLOTTYPE::nset;
};

class Settings {
	PlottingSettings mPlotting{};
	FixedAnalysisParameters mFixedParameters{};
	std::vector<AnalysisParameters> mStrategy{ 1 };

  public:
	/// default constructor
	Settings() = default;
	/// full constructor
	Settings( PlottingSettings plotting, FixedAnalysisParameters fixedParameters, std::vector<AnalysisParameters> strategy )
		: mPlotting( plotting )
		, mFixedParameters( fixedParameters )
		, mStrategy( strategy ) {
		if ( strategy.empty() ) return;
		// calculate gcd of the strategies timesteps
		mpz_class numerator_gcd = mStrategy.front().timeStep.get_num();
		mpz_class denominator_lcm = mStrategy.front().timeStep.get_den();

		for ( AnalysisParameters const& params : mStrategy ) {
			numerator_gcd = gcd( numerator_gcd, params.timeStep.get_num() );
			denominator_lcm = lcm( denominator_lcm, params.timeStep.get_den() );
		}

		mFixedParameters.fixedTimeStep = mpq_class( numerator_gcd, denominator_lcm );

		for ( AnalysisParameters& params : mStrategy ) {
			mpq_class timeStepFactor = params.timeStep / mFixedParameters.fixedTimeStep;
			assert( timeStepFactor.get_den() == 1 );
			assert( timeStepFactor.get_num().fits_sint_p() );
			params.timeStepFactor = int( timeStepFactor.get_num().get_si() );
		}
	}

	PlottingSettings const& plotting() const {
		return mPlotting;
	}

	FixedAnalysisParameters const& fixedParameters() const {
		return mFixedParameters;
	}

	std::vector<AnalysisParameters> const& strategy() const {
		return mStrategy;
	}

	void setStrategy( const std::vector<AnalysisParameters> strategy ) { mStrategy = strategy; }
};

/**
 * @brief      Struct for reachability analysis algorithm settings.
 */
struct ReachabilitySettings {
	tNumber timeBound = 0;											   /// The local time horizon.
	int jumpDepth = 0;												   /// The maximal number of jumps, i.e. the depth of the search tree.
	tNumber timeStep = 0;											   /// Time step size.
	std::string fileName = "out";									   /// Name for the output file (plotting).
	unsigned long pplDenomimator = 0;								   /// Common denominator for ppl-numbers (only relevant if ppl is used).
	std::vector<std::vector<std::size_t>> plotDimensions{ { 0, 1 } };  /// A set of dimension pairs to plot.
	bool uniformBloating = false;									   /// Bloating settings.
	int clustering = -1;											   /// -1 = off, 0 = all (aggregation), i = maximal number of segments to unify
	bool useInvariantTimingInformation = true;
	bool useGuardTimingInformation = true;
	bool useBadStateTimingInformation = true;

	/**
     * @brief      Default constructor.
     */
	ReachabilitySettings() = default;

	ReachabilitySettings( const ReachabilitySettings& orig ) = default;

	/**
     * @brief      Assignment operator.
     * @param[in]  _rhs  The right hand side.
     * @return     A reference to this object.
     */
	ReachabilitySettings& operator=( const ReachabilitySettings& _rhs ) = default;

	/**
     * @brief      Equality comparison operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True if both settings are equal, false otherwise.
     */
	friend bool operator==( const ReachabilitySettings& lhs, const ReachabilitySettings& rhs ) {
		return (
			  lhs.timeBound == rhs.timeBound &&
			  lhs.jumpDepth == rhs.jumpDepth &&
			  lhs.timeStep == rhs.timeStep &&
			  lhs.fileName == rhs.fileName &&
			  lhs.pplDenomimator == rhs.pplDenomimator &&
			  lhs.plotDimensions == rhs.plotDimensions &&
			  lhs.uniformBloating == rhs.uniformBloating &&
			  lhs.clustering == rhs.clustering &&
			  lhs.useBadStateTimingInformation == rhs.useBadStateTimingInformation &&
			  lhs.useGuardTimingInformation == rhs.useGuardTimingInformation &&
			  lhs.useInvariantTimingInformation == rhs.useInvariantTimingInformation );
	}

	/**
     * @brief      Outstream operator.
     * @param      ostr  The outstream.
     * @param[in]  rhs   The right hand side.
     * @return     Reference to the outstream.
     */
	friend std::ostream& operator<<( std::ostream& ostr, const ReachabilitySettings& rhs ) {
		ostr << "Local time-horizon: " << carl::toDouble( rhs.timeBound ) << std::endl;
		ostr << "Time-step size: " << carl::toDouble( rhs.timeStep ) << std::endl;
		ostr << "Jump-depth: " << rhs.jumpDepth << std::endl;
		ostr << "Clustering: " << rhs.clustering << std::endl;
		return ostr;
	}
};

}  // namespace hypro
