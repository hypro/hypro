/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
	AGG_SETTING aggregation = AGG_SETTING::MODEL;						   ///< the forced aggregation settings
	int clustering = -1;												   ///< if clustering is used: number of clusters
	representation_name representation_type = representation_name::UNDEF;  ///< type of representation
	int representation_setting = 0;										   ///< used settings for the representation
	bool uniformBloating = false;
	REACH_SETTING reachability_analysis_method = REACH_SETTING::FORWARD;  ///< method of reachability analysis
	int timeStepFactor = 1;												  ///< the factor between the fixed time step and this time step, i.e. fixedTimeStep * timeStepFactor = timeStep. Can be negative.
	bool detectJumpFixedPoints = false;									  ///< true if an analyzer should try to detect a fixed point by analyzing initial sets of other flowpipes
	bool detectFixedPointsByCoverage = false;							  ///< if true, fixed points for jumps are also detected if multiple sets achieve coverage of the current set (more expensive)
	std::size_t numberSetsForContinuousCoverage = 0;					  ///< number of sets at the beginning of a flowpipe that are used for coverage tests to detect fixed points within other nodes
	bool detectContinuousFixedPointsLocally = false;					  ///< true if an analyzer should try to find fixed points within the current flowpipe (set-containment)
	bool detectZenoBehavior = true;										  ///< if true, a lightweight check for Zeno cycles is preformed during analysis
};

struct FixedAnalysisParameters {
	size_t jumpDepth{ std::numeric_limits<int>::max() };  ///< bound for maximal number of executed jumps
	tNumber localTimeHorizon = 0;						  ///< bound for maximal duration of time elapse per flowpipe, use negative value for unbounded time (not always supported)
	tNumber fixedTimeStep = 0;							  ///< a time step that all timesteps of the analysis parameters are multiples of, i.e. fixedTimeStep * timeStepFactor = timeStep.
	tNumber globalTimeHorizon = -1;						  ///< bound for maximal time duration (globally) - computation should stop, when each trace covers this duration (but not exactly then), negative if not used (default)
	bool silent = false;								  ///< if true, no output for stdout is generated
#if HYPRO_USE_PPL
	unsigned long pplDenominator{ defaultPPLDenominator };
#endif
};

struct PlottingSettings {
	std::vector<std::vector<size_t>> plotDimensions{};
	std::vector<std::string> plotFileNames{};
	PLOTTYPE plottingFileType = PLOTTYPE::nset;
};

struct UrgencyCEGARSettings {
	std::vector<UrgencyRefinementLevel> refinementLevels{ UrgencyRefinementLevel::FULL,
														  UrgencyRefinementLevel::CUTOFF,
														  UrgencyRefinementLevel::SETDIFF };
	bool refineHalfspaces = true;
	bool pruneUrgentSegments = true;
	UrgencyRefinementHeuristic heuristic = UrgencyRefinementHeuristic::NONE;
	bool aggregatedRefine = true;
};

class Settings {
	PlottingSettings mPlotting{};
	FixedAnalysisParameters mFixedParameters{};
	std::vector<AnalysisParameters> mStrategy{ 1 };
	UrgencyCEGARSettings mUrgencySettings{};

  public:
	/// default constructor
	Settings() = default;
	/// full constructor
	Settings( PlottingSettings plotting, FixedAnalysisParameters fixedParameters, std::vector<AnalysisParameters> strategy, UrgencyCEGARSettings urgencySettings = UrgencyCEGARSettings{} )
		: mPlotting( plotting )
		, mFixedParameters( fixedParameters )
		, mStrategy( strategy )
		, mUrgencySettings( urgencySettings ) {
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
			mpq_class timeStepFactor = (int)1;
			if ( mFixedParameters.fixedTimeStep != 0 ) {
				mpq_class timeStepFactor = params.timeStep / mFixedParameters.fixedTimeStep;
			}
			assert( timeStepFactor.get_den() == 1 );
			assert( timeStepFactor.get_num().fits_sint_p() );
			params.timeStepFactor = int( timeStepFactor.get_num().get_si() );
		}
	}

	PlottingSettings const& plotting() const {
		return mPlotting;
	}

	PlottingSettings& rPlotting() {
		return mPlotting;
	}

	FixedAnalysisParameters const& fixedParameters() const {
		return mFixedParameters;
	}

	FixedAnalysisParameters& rFixedParameters() {
		return mFixedParameters;
	}

	std::vector<AnalysisParameters> const& strategy() const {
		return mStrategy;
	}

	std::vector<AnalysisParameters>& rStrategy() {
		return mStrategy;
	}

	UrgencyCEGARSettings const& urgencySettings() const {
		return mUrgencySettings;
	}

	UrgencyCEGARSettings& rUrgencySettings() {
		return mUrgencySettings;
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

/**
 * Converts the old ReachabilitySettings type to the new Settings-type
 * @param r_settings old settings type
 * @return new settings type
 */
Settings convert( const ReachabilitySettings& r_settings );

}  // namespace hypro
