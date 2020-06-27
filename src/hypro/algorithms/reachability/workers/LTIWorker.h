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

	REACHABILITY_RESULT computeForwardReachability( Location<Number> const* loc, const Representation& initialSet );

	REACHABILITY_RESULT computeTimeSuccessors( Location<Number> const* loc, const Representation& initialSet );

	std::vector<JumpSuccessor<Representation>> computeJumpSuccessors( Location<Number> const* loc );

	const std::vector<JumpSuccessor<Representation>>& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const std::vector<Representation>& getFlowpipe() const { return mFlowpipe; }

  private:
	bool requireTimeSuccessorComputation( std::size_t segmentCount ) const { return segmentCount <= mNumSegments; }

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  /// TODO add documentation
	const AnalysisParameters& mSettings;
	tNumber mLocalTimeHorizon;
	std::vector<JumpSuccessor<Representation>> mJumpSuccessorSets;
	std::vector<Representation> mFlowpipe;
	TimeTransformationCache<Number>& mTrafoCache;

	size_t const mNumSegments = std::size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "LTIWorker.tpp"
