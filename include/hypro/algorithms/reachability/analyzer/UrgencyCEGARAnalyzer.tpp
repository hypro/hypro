/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "UrgencyCEGARAnalyzer.h"

namespace hypro {

template <typename Representation, typename Automaton>
auto UrgencyCEGARAnalyzer<Representation, Automaton>::run() -> UrgencyCEGARResult {
	TimeTransformationCache<Number> transformationCache;
	UrgencyCEGARWorker<Representation, Automaton> worker{
		  *mHybridAutomaton,
		  mParameters,
		  mFixedParameters.localTimeHorizon,
		  transformationCache };
	UrgencyRefinementAnalyzer<Representation, Automaton> refinementAnalyzer( mHybridAutomaton, mFixedParameters, mParameters, mRefinementSettings, mRoots );

	while ( !mWorkQueue.empty() ) {
		COUNT( "Computed flowpipes" );
		auto currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();
		// std::cout << "Node at depth " << currentNode->getDepth() << "\n";

		START_BENCHMARK_OPERATION( "Unrefined time successors" );
		worker.reset();	 // delete cached jump predecessors and computed flowpipe
		auto safetyResult = worker.computeTimeSuccessors( *currentNode, mRefinementSettings.pruneUrgentSegments );
		worker.insertFlowpipe( *currentNode );
		currentNode->setSafety( safetyResult );
		STOP_BENCHMARK_OPERATION( "Unrefined time successors" );

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			refinementAnalyzer.setRefinement( currentNode );
			START_BENCHMARK_OPERATION( "Refinement" );
			auto refineResult = refinementAnalyzer.run();
			STOP_BENCHMARK_OPERATION( "Refinement" );
			if ( refineResult.isSuccess() ) {
				for ( auto successor : refineResult.success().pathSuccessors ) {
					mWorkQueue.push_front( successor );
				}
			} else {
				return { Failure{ refineResult.failure().conflictNode } };
			}
		} else {
			// Do not perform discrete jump if jump depth was reached
			if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;
			// create jump successor tasks
			for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( *currentNode ) ) {
				for ( const auto jsucc : timedValuationSets ) {
					// create Task
					auto childNode = createChildNode( jsucc, transition, currentNode );
					mWorkQueue.push_front( childNode );
				}
			}
		}
	}
	return { UrgencyCEGARSuccess{} };
}

template <typename Representation, typename Automaton>
ReachTreeNode<Representation, typename UrgencyCEGARAnalyzer<Representation, Automaton>::LocationT>* UrgencyCEGARAnalyzer<Representation, Automaton>::createChildNode(
	  const TimedValuationSet<Representation>& jsucc, const Transition<Number, LocationT>* transition, ReachTreeNode<Representation, LocationT>* parent ) {
	carl::Interval<SegmentInd> const& initialSetDuration = parent->getTimings();
	// add one to upper to convert from segment indices to time points
	// multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
	carl::Interval<SegmentInd> enabledDuration{
		  jsucc.time.lower() * mParameters.timeStepFactor,
		  ( jsucc.time.upper() + 1 ) * mParameters.timeStepFactor };
	carl::Interval<TimePoint> globalDuration{
		  initialSetDuration.lower() + enabledDuration.lower(),
		  initialSetDuration.upper() + enabledDuration.upper() };

	auto& childNode = parent->addChild( jsucc.valuationSet, globalDuration, transition );

	for ( auto const& trans : childNode.getLocation()->getTransitions() ) {
		if ( trans->isUrgent() ) {
			childNode.getUrgencyRefinementLevels()[trans.get()] = detail::getInitialRefinementLevel( trans.get(), mRefinementSettings );
		}
	}
	return &childNode;
}

}  // namespace hypro