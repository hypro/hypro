/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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

	LTIWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mLocalTimeHorizon( localTimeHorizon )
		, mTrafoCache( trafoCache ) {}

	template <typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out ) const;

	std::vector<JumpSuccessor<Representation>> computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const;
	JumpSuccessorGen getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<Number> const* transition ) const;
    SegmentInd maxNumberSegments() const { return mNumSegments; }

  protected:
	const HybridAutomaton<Number>& mHybridAutomaton;  ///< hybrid automaton to analyze
	const AnalysisParameters& mSettings;			  ///< analysis settings
	tNumber mLocalTimeHorizon;						  ///< local time horizon
	TimeTransformationCache<Number>& mTrafoCache;	  ///< cache for matrix exponential
	size_t const mNumSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "LTIWorker.tpp"
