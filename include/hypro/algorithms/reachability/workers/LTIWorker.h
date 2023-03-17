/*
 * Copyright (c) 2022-2023.
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

template <typename Representation, typename HybridAutomaton>
class LTIWorker {
  private:
	using Number = typename Representation::NumberType;
	using LocationT = typename HybridAutomaton::LocationType;

	struct EnabledSegmentsGen;
	struct AggregatedGen;

  public:
	struct JumpSuccessorGen;

	LTIWorker( const HybridAutomaton& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<LocationT>& trafoCache, std::size_t subspace = 0 )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mLocalTimeHorizon( localTimeHorizon )
		, mTrafoCache( trafoCache )
		, mSubspace( subspace ) {}

	template <typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, LocationT const* loc, OutputIt out, long segmentsToCompute, bool checkSafety = true ) const;

	template <typename OutputIt>
	REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, LocationT const* loc, OutputIt out, bool checkSafety = true ) const {
		return computeTimeSuccessors( initialSet, loc, out, mNumSegments, checkSafety );
	}

	std::vector<JumpSuccessor<Representation, LocationT>> computeJumpSuccessors( std::vector<Representation> const& flowpipe, LocationT const* loc ) const;
	JumpSuccessorGen getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<LocationT> const* transition ) const;
	SegmentInd maxNumberSegments() const { return mNumSegments; }
	// Compute jump successors for guard enabling sets
	std::vector<TimedValuationSet<Representation>> computeJumpSuccessorsForGuardEnabled( std::vector<IndexedValuationSet<Representation>>& predecessors, Transition<LocationT> const* trans ) const;

  protected:
	const HybridAutomaton& mHybridAutomaton;		  ///< hybrid automaton to analyze
	const AnalysisParameters& mSettings;			  ///< analysis settings
	tNumber mLocalTimeHorizon;						  ///< local time horizon
	TimeTransformationCache<LocationT>& mTrafoCache;  ///< cache for matrix exponential
	std::size_t mSubspace;

	long const mNumSegments = long( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "LTIWorker.tpp"
