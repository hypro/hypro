/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/TimeTransformationCache.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../handlers/urgencyHandlers/ltiUrgencyHandler.h"
#include "../workers/LTIFlowpipeConstruction.h"

#include <optional>

namespace hypro {

/**
 * @brief   Class implementing a worker for automata with urgent transitions.
 * @details Implements methods for computing time elapse and discrete transitions.
 *          Repeated calling of these methods allows implementation of reachability analysis.
 *          The worker can optionally deal with urgent transitions by either computing a convex overapproximation
 * 					of the set difference with the jump enabling set or by computing the set difference, which can lead
 * 					to multiple segments for a single point in time. The refinement level for each transition is set
 * 					in the given task.
 * @tparam Representation   The used state set representation.
 */
template <typename Representation, typename Automaton>
class UrgencyCEGARWorker {
  private:
	using Number = typename Representation::NumberType;
	using LocationT = typename Automaton::LocationType;
	using Flowpipe = std::vector<IndexedValuationSet<Representation>>;

  public:
	UrgencyCEGARWorker( const Automaton& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache )
		: mHybridAutomaton( ha )
		, mSettings( settings )
		, mLocalTimeHorizon( localTimeHorizon )
		, mTrafoCache( trafoCache ) {}

	/**
	 * @brief Computes the states reachable by letting time elapse up to the given time horizon.
	 * @param task Used to access the the location, initial set and refinement levels of urgent transitions.
	 * @param timeHorizion Number of segments to compute.
	 * @param pruneUrgentSegments If true, ignore segments that are contained in urgent jump enabling sets,
	 * regardless of their refinement level.
	 * @return Safety after time elapse.
	 */
	REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<Representation, LocationT>& task, std::size_t timeHorizon, bool pruneUrgentSegments = true );
	/**
	 * @brief Computes the states reachable by letting time elapse. Time horizon is given by the settings.
	 * @param task Used to access the the location, initial set and refinement levels of urgent transitions.
	 * @param pruneUrgentSegments If true, ignore segments that are contained in urgent jump enabling sets,
	 * regardless of their refinement level.
	 * @return Safety after time elapse.
	 */
	REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<Representation, LocationT>& task, bool pruneUrgentSegments = true ) {
		return computeTimeSuccessors( task, mNumSegments, pruneUrgentSegments );
	}
	/**
	 * @brief Getter function for the computed flowpipe.
	 * @details The flowpipe is stored as pairs of valuation set and segment index,
	 *          since set difference computation can split segments.
	 * @return Pairs of flowpipe segments and their timing index.
	 */
	const Flowpipe& getFlowpipe() const { return mFlowpipe; }
	/**
	 * @brief Writes the computed flowpipe in a reach tree node.
	 * @details The segments are written to the flowpipe field of the node and the time offsets in the timing field.
	 * @param node The tree node to write the flowpipe to.
	 */
	void insertFlowpipe( ReachTreeNode<Representation, LocationT>& node ) const;

	/**
	 * @brief Computes the states reachable by taking some discrete transition in a time interval.
	 * @details Performs aggregation and applies the reset.
	 * @param task Used to access the location.
	 * @param transition The transition to take.
	 * @param timeOfJump Only jumps taken in this time interval will be considered.
	 */
	std::vector<TimedValuationSet<Representation>> computeJumpSuccessors(
		  const ReachTreeNode<Representation, LocationT>& task,
		  const Transition<Number, LocationT>* transition,
		  const carl::Interval<SegmentInd>& timeOfJump = carl::Interval<SegmentInd>::unboundedInterval() );

	/**
	 * @brief Computes the states reachable by taking any discrete transition.
	 * @details Iterates over all transitions, performs aggregation and applies the reset.
	 * @param task Used to access the location.
	 */
	std::vector<JumpSuccessor<Representation, LocationT>> computeJumpSuccessors( const ReachTreeNode<Representation, LocationT>& task );

	/**
	 * @brief Clears the flowpipe so the worker can be reused for another task
	 */
	void reset() {
		mFlowpipe.clear();
		mJumpPredecessors.clear();
	}

  private:
	/**
	 * @brief Performs operations on the segment obtained by letting time elapse.
	 * @details Applies intersection with the invariant, set difference with urgent guards
	 *          and intersection with bad states and adds the result to the flowpipe.
	 * @param task The current task, used to access the location.
	 * @param segment The current segment computed by letting time elapse.
	 * @param timing The time offset of the segment.
	 * @param pruneUrgentSegments If true, ignore segments that are contained in urgent jump enabling sets,
	 * regardless of their refinement level.
	 * @return Safety of the segment.
	 */
	REACHABILITY_RESULT handleSegment(
		  const ReachTreeNode<Representation, LocationT>& task, const Representation& segment, SegmentInd timing, bool pruneUrgentSegments );
	/**
	 * @brief Adds a single segment to the flowpipe object
	 * @param The computed segment.
	 * @param timing The time offset of the segment.
	 */
	void addSegment( const Representation& segment, SegmentInd timing );
	/**
	 * @brief Adds a list of segments with the same time offset to the flowpipe object.
	 * @param segment Vector of computed segments.
	 * @param timing The time offset of the segments.
	 */
	void addSegment( const std::vector<Representation>& segment, SegmentInd timing );

  protected:
	const Automaton& mHybridAutomaton;																					 ///< hybrid automaton to analyze
	const AnalysisParameters& mSettings;																				 ///< analysis settings
	tNumber mLocalTimeHorizon;																							 ///< local time horizon
	TimeTransformationCache<Number>& mTrafoCache;																		 ///< cache for matrix exponential
	Flowpipe mFlowpipe;																									 ///< Storage of computed time successors
	std::map<const Transition<Number, LocationT>*, std::vector<IndexedValuationSet<Representation>>> mJumpPredecessors;	 ///< Cache jump predecessors

	size_t const mNumSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "UrgencyCEGARWorker.tpp"
