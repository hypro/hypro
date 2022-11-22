/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "RefinementAnalyzer.h"

namespace hypro {

template <typename Representation>
struct ChildNodeGen {
	typename LTIWorker<Representation>::JumpSuccessorGen* successors;
	ReachTreeNode<Representation>* parentNode;
	int timeStepFactor;

	ReachTreeNode<Representation>* next() {
		auto succ = successors->next();
		if ( !succ ) return nullptr;
		auto& [valuationSet, segmentsInterval] = *succ;

		// convert local time to global time

		carl::Interval<TimePoint> const& initialSetDuration = parentNode->getTimings();
		// add one to upper to convert from segment indices to time points
		// multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
		carl::Interval<TimePoint> enabledDuration{ segmentsInterval.lower() * timeStepFactor, ( segmentsInterval.upper() + 1 ) * timeStepFactor };
		carl::Interval<TimePoint> globalDuration{ initialSetDuration.lower() + enabledDuration.lower(), initialSetDuration.upper() + enabledDuration.upper() };

		return &parentNode->addChild( valuationSet, globalDuration, successors->mTransition );
	}
};
template <class Gen, class Rep>
ChildNodeGen( Gen*, ReachTreeNode<Rep>*, int ) -> ChildNodeGen<Rep>;

template <typename Representation>
bool RefinementAnalyzer<Representation>::matchesPathTiming( ReachTreeNode<Representation>* node ) {
	auto& timing = mPath.elements.at( node->getDepth() - 1 ).first;
	return node->getTimings().upper() >= timing.lower() && node->getTimings().lower() <= timing.upper();
}

template <typename Representation>
bool RefinementAnalyzer<Representation>::matchesPathTransition( ReachTreeNode<Representation>* node ) {
	auto const* transition = mPath.elements.at( node->getDepth() - 1 ).second;
	return ( transition == node->getTransition() );
}

template <typename Representation>
auto RefinementAnalyzer<Representation>::run() -> RefinementResult {
	// Setup settings for flowpipe construction in worker
	TimeTransformationCache<LocationT> transformationCache;
	LTIWorker<Representation> worker{
		  mHybridAutomaton,
		  mParameters,
		  mFixedParameters.localTimeHorizon,
		  transformationCache };

	std::vector<ReachTreeNode<Representation>*> pathSuccessors{};

	while ( !mWorkQueue.empty() ) {
		// pop node
		ReachTreeNode<Representation>* currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();

		// if node is child of last node in path, collect it in return value
		if ( currentNode->getDepth() == mPath.elements.size() + 1 ) {
			pathSuccessors.push_back( currentNode );
			continue;
		}

		REACHABILITY_RESULT safetyResult;

		// compute flowpipe
		if ( currentNode->getFlowpipe().empty() ) {
			safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

			// fail if bad state was hit
			if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
				return { Failure{ currentNode } };
			}
		}

		// do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) continue;

		// currentNode is last node in path, create and collect all children
		if ( currentNode->getDepth() == mPath.elements.size() ) {
			for ( auto const& transition : currentNode->getLocation()->getTransitions() ) {
				auto jumpSuccGen = worker.getJumpSuccessors( currentNode->getFlowpipe(), transition.get() );
				auto childGen = ChildNodeGen{ &jumpSuccGen, currentNode, mParameters.timeStepFactor };

				while ( auto* child = childGen.next() ) {
					pathSuccessors.push_back( child );
				}
			}
		} else {
			// continue along path

			// check if children already exist
			bool matchedOne = false;
			for ( auto* child : currentNode->getChildren() ) {
				if ( matchesPathTransition( child ) ) {
					matchedOne = true;
					// check against path
					if ( matchesPathTiming( child ) ) {
						mWorkQueue.push_front( child );
					}
				}
			}

			if ( !matchedOne ) {
				auto jumpSuccGen = worker.getJumpSuccessors( currentNode->getFlowpipe(), mPath.elements.at( currentNode->getDepth() ).second );
				auto childGen = ChildNodeGen{ &jumpSuccGen, currentNode, mParameters.timeStepFactor };

				while ( auto* child = childGen.next() ) {
					if ( matchesPathTiming( child ) ) {
						mWorkQueue.push_front( child );
					}
				}
			}
		}
	}

	return { RefinementSuccess{ pathSuccessors } };
}

}  // namespace hypro
