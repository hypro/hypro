#pragma once

#include "algorithms/reachability/FlowpipeConstructionConvenience.h"
#include "algorithms/reachability/handlers/badStateHandlers/ltiBadStateHandler.h"
#include "algorithms/reachability/workers/LTIFlowpipeConstruction.h"
#include "datastructures/reachability/Settings.h"
#include "datastructures/reachability/TimeTransformationCache.h"
#include "datastructures/reachability/timing/HierarchicalIntervalVector.h"
#include "util/logging/Logger.h"
#include "util/plotting/PlotData.h"

#include <optional>
#include <vector>

namespace hypro {

template <typename Representation>
class LTIWorker {
  private:
	using Number = typename Representation::NumberType;

	struct EnabledSegmentsGen;
	struct AggregatedGen;

  public:
	struct JumpSuccessorGen;

	LTIWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mLocalTimeHorizon( localTimeHorizon )
		, mTrafoCache( trafoCache ) {}

	template <typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out ) const;

	std::vector<JumpSuccessor<Representation>> computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const;
	JumpSuccessorGen getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<Number> const* transition ) const;

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  ///< hybrid automaton to analyze
	const AnalysisParameters& mSettings;			  ///< analysis settings
	tNumber mLocalTimeHorizon;						  ///< local time horizon
	TimeTransformationCache<Number>& mTrafoCache;	  ///< cache for matrix exponential

	size_t const mNumSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "LTIWorker.tpp"
