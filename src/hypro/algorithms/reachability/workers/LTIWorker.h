#pragma once

#include "algorithms/reachability/workers/LTIFlowpipeConstruction.h"
#include "datastructures/reachability/Settings.h"
#include "datastructures/reachability/TimeTransformationCache.h"
#include "datastructures/reachability/timing/HierarchicalIntervalVector.h"
#include "util/logging/Logger.h"
#include "util/plotting/PlotData.h"

#include <vector>

namespace hypro {

template <typename Representation>
class LTIWorker {
  private:
	using Number = typename Representation::NumberType;
	using JumpSuccessors = std::map<Transition<Number>*, std::vector<Representation>>;

  public:
	LTIWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, TimeTransformationCache<Number>& trafoCache )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mTrafoCache( trafoCache ) {}

	REACHABILITY_RESULT computeForwardReachability( Location<Number> const* loc, const Representation& initialSet, const matrix_t<Number>& transformation );

	REACHABILITY_RESULT computeTimeSuccessors( Location<Number> const* loc, const Representation& initialSet, const matrix_t<Number>& transformation );

	void computeJumpSuccessors( Location<Number> const* loc, AnalysisParameters settings );

	const JumpSuccessors& getJumpSuccessorSets() const { return mJumpSuccessorSets; }
	const std::vector<Representation>& getFlowpipe() const { return mFlowpipe; }

  private:
	void postProcessJumpSuccessors( const JumpSuccessors& guardSatisfyingSets );

	bool requireTimeSuccessorComputation( std::size_t segmentCount ) const { return segmentCount <= mSettings.localTimeHorizon / mSettings.strategy.front().timeStep; }

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;
	const AnalysisParameters& mSettings;
	JumpSuccessors mJumpSuccessorSets;
	std::vector<Representation> mFlowpipe;
	TimeTransformationCache<Number>& mTrafoCache;
};

}  // namespace hypro

#include "LTIWorker.tpp"
