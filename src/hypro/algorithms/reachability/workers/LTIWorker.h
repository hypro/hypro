#pragma once

#include "algorithms/reachability/workers/LTIFlowpipeConstruction.h"
#include "algorithms/reachability/FlowpipeConstructionConvenience.h"
#include "datastructures/reachability/Settings.h"
#include "datastructures/reachability/TimeTransformationCache.h"
#include "datastructures/reachability/timing/HierarchicalIntervalVector.h"
#include "util/logging/Logger.h"
#include "util/plotting/PlotData.h"
#include "algorithms/reachability/handlers/badStateHandlers/ltiBadStateHandler.h"

#include <vector>

namespace hypro {

template <typename Representation>
class LTIWorker {
  private:
	using Number = typename Representation::NumberType;

  public:
	LTIWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mLocalTimeHorizon( localTimeHorizon )
		, mTrafoCache( trafoCache ) {}

	template<typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out ) const;

	std::vector<JumpSuccessor<Representation>> computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const;

  private:

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  /// TODO add documentation
	const AnalysisParameters& mSettings;
	tNumber mLocalTimeHorizon;
	TimeTransformationCache<Number>& mTrafoCache;

	size_t const mNumSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "LTIWorker.tpp"
