#pragma once

#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/TimeTransformationCache.h"
#include "../../../datastructures/reachability/timing/HierarchicalIntervalVector.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../workers/LTIFlowpipeConstruction.h"

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

	LTIWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache, std::size_t subspace = 0 )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mLocalTimeHorizon( localTimeHorizon )
		, mTrafoCache( trafoCache )
		, mSubspace( subspace ) {}

	template <typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out, int segmentsToCompute, bool checkSafety = true ) const;

	template <typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out, bool checkSafety = true ) const {
		return computeTimeSuccessors( initialSet, loc, out, mNumSegments, checkSafety );
	}

	std::vector<JumpSuccessor<Representation>> computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const;
	JumpSuccessorGen getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<Number> const* transition ) const;
	// Compute jump successors for guard enabling sets
	std::vector<TimedValuationSet<Representation>> computeJumpSuccessorsForGuardEnabled( std::vector<IndexedValuationSet<Representation>>& predecessors, Transition<Number> const* trans ) const;

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  ///< hybrid automaton to analyze
	const AnalysisParameters& mSettings;			  ///< analysis settings
	tNumber mLocalTimeHorizon;						  ///< local time horizon
	TimeTransformationCache<Number>& mTrafoCache;	  ///< cache for matrix exponential
	std::size_t mSubspace;

	size_t const mNumSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "LTIWorker.tpp"
