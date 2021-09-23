#include "LTIAnalyzer.h"

#include <algorithm>
#include <vector>

namespace hypro {

template <typename State>
auto LTIAnalyzer<State>::run() -> LTIResult {
	// Setup settings for flowpipe construction in worker
	TimeTransformationCache<Number> transformationCache;
	LTIWorker<State> worker{
		  *mHybridAutomaton,
		  mParameters,
		  mFixedParameters.localTimeHorizon,
		  transformationCache };

	while ( !mWorkQueue.empty() ) {
		ReachTreeNode<State>* currentNode = mWorkQueue.back();
		mWorkQueue.pop_back();
		REACHABILITY_RESULT safetyResult;

		if ( mParameters.detectJumpFixedPoints && !currentNode->getInitialBoundingBox() ) {
			currentNode->setBoundingBox( Converter<Number>::toBox( currentNode->getInitialSet() ).intervals() );
		}

		// bounded time evolution
		safetyResult = worker.computeTimeSuccessors( currentNode->getInitialSet(), currentNode->getLocation(), std::back_inserter( currentNode->getFlowpipe() ) );

		// TODO Do not hardcode this!
		// test containment of the first 10 segments against all other nodes' first 10 segments (with the same location)
		std::size_t set_index = 0;
		while ( set_index < 10 && set_index < currentNode->getFlowpipe().size() ) {
			for ( auto& other_node : preorder( mRoots ) ) {
				if ( &other_node != currentNode && other_node.getLocation() == currentNode->getLocation() ) {
					// fill coverer
					std::vector<State> coverer;
					for ( std::size_t i = 0; i < 12; ++i ) {
						if ( other_node.getFlowpipe().size() > i ) {
							coverer.push_back( other_node.getFlowpipe()[i] );
						}
					}
					if ( is_covered( currentNode->getFlowpipe()[set_index], coverer ) ) {
						std::cout << "Found fixed point in the first 10 segments of some other node via coverage." << std::endl;
						currentNode->setFixedPoint();
						break;
					}

					std::size_t other_set_index = 0;
					while ( other_set_index < 10 && other_set_index < other_node.getFlowpipe().size() ) {
						if ( other_node.getFlowpipe()[other_set_index].contains( currentNode->getFlowpipe()[set_index] ) ) {
							std::cout << "Found fixed point in the first 10 segments of some other node via containment." << std::endl;
							currentNode->setFixedPoint();
							break;
						}
						++other_set_index;
					}
				}
				if ( currentNode->hasFixedPoint() == TRIBOOL::TRUE ) {
					break;
				}
			}
			++set_index;
			if ( currentNode->hasFixedPoint() == TRIBOOL::TRUE ) {
				break;
			}
		}
		// TODO temporary, check!
		if ( currentNode->hasFixedPoint() == TRIBOOL::TRUE ) {
			continue;
		}

		if ( safetyResult == REACHABILITY_RESULT::UNKNOWN ) {
			return { Failure{ currentNode } };
		}

		// Do not perform discrete jump if jump depth was reached
		if ( currentNode->getDepth() == mFixedParameters.jumpDepth ) {
			COUNT( "Unfinished branches" );
			continue;
		}

		// create jump successor tasks
		for ( const auto& [transition, timedValuationSets] : worker.computeJumpSuccessors( currentNode->getFlowpipe(), currentNode->getLocation() ) ) {
			for ( const auto [valuationSet, segmentsInterval] : timedValuationSets ) {
				// update reachTree

				// convert local time to global time
				carl::Interval<SegmentInd> const& initialSetDuration = currentNode->getTimings();
				// add one to upper to convert from segment indices to time points
				// multiply by timeStepFactor to convert from analyzer specific timeStep to fixedTimeStep
				carl::Interval<SegmentInd> enabledDuration{ segmentsInterval.lower() * mParameters.timeStepFactor, ( segmentsInterval.upper() + 1 ) * mParameters.timeStepFactor };
				carl::Interval<TimePoint> globalDuration{ initialSetDuration.lower() + enabledDuration.lower(), initialSetDuration.upper() + enabledDuration.upper() };

				// in any case add node to the search tree
				ReachTreeNode<State>& childNode = currentNode->addChild( valuationSet, globalDuration, transition );
				// if desired, try to detect fixed-point
				bool fixedPointReached = mParameters.detectJumpFixedPoints;
				auto boundingBox = std::vector<carl::Interval<Number>>{};
				if ( mParameters.detectJumpFixedPoints ) {
					boundingBox = Converter<Number>::toBox( childNode.getInitialSet() ).intervals();
					fixedPointReached = detectJumpFixedPoint( childNode, mRoots, mParameters.detectFixedPointsByCoverage );
				}

				// set bounding box to speed up search in case the option is enabled.
				// IMPORTANT: This has to be done *after* fp-detection to ensure that the node does not consider itself during fp-detection
				if ( mParameters.detectJumpFixedPoints ) {
					childNode.setBoundingBox( boundingBox );
				}
				// create Task, push only to queue, in case no fixed-point has been detected or detection is disabled
				if ( !fixedPointReached ) {
					mWorkQueue.push_front( &childNode );
				} else {
					COUNT( "Finished branches (fixed-point)" );
				}
			}
		}

		// detect fixed points in continuous behavior (locally), only if the node does not have any child nodes. Otherwise, the detected fixed point can be evaded by taking a discrete jump.
		if ( mParameters.detectContinuousFixedPointsLocally && currentNode->getChildren().empty() ) {
			for ( auto cur = std::begin( currentNode->getFlowpipe() ); cur != std::end( currentNode->getFlowpipe() ); ++cur ) {
				for ( auto succ = std::begin( currentNode->getFlowpipe() ); succ != std::end( currentNode->getFlowpipe() ); ++succ ) {
					if ( succ->contains( *cur ) ) {
						currentNode->setFixedPoint();
					}
				}
			}
		}
	}

	return { LTISuccess{} };
}

}  // namespace hypro
