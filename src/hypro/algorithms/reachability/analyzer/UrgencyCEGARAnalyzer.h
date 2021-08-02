#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/UrgencyWorker.h"
#include "./ReturnTypes.h"
#include "./impl/UrgencyRefinementAnalyzer.h"

#include <queue>

namespace hypro {

struct UrgencyCEGARSuccess {};

template <typename Representation>
class UrgencyCEGARAnalyzer {
	using Number = typename Representation::NumberType;
	using RefinementResult = typename UrgencyRefinementAnalyzer<Representation>::RefinementResult;

  public:
	using UrgencyCEGARResult = AnalysisResult<UrgencyCEGARSuccess, Failure<Representation>>;

	UrgencyCEGARAnalyzer( HybridAutomaton<Number> const& ha,
						  FixedAnalysisParameters const& fixedParameters,
						  AnalysisParameters const& parameters,
						  UrgencyCEGARSettings const& refinementSettings )
		: mHybridAutomaton( &ha )
		, mFixedParameters( fixedParameters )
		, mParameters( parameters )
		, mRefinementSettings( refinementSettings ) {
		for ( auto& root : makeRoots<Representation>( ha ) ) {
			mRoots.push_back( std::move( root ) );
		}
		for ( auto& root : mRoots ) {
			for ( auto const& trans : root.getLocation()->getTransitions() ) {
				if ( trans->isUrgent() ) {
					root.getUrgent()[trans.get()] = detail::getInitialRefinementLevel( trans.get(), mRefinementSettings );
				}
			}
			mWorkQueue.push_front( &root );
		}
	}

	UrgencyCEGARResult run();
	std::vector<ReachTreeNode<Representation>*> getRoots() {
		std::vector<ReachTreeNode<Representation>*> res;
		std::transform( mRoots.begin(), mRoots.end(), std::back_inserter( res ), []( auto& root ) {
			return &root;
		} );
		return res;
	}

  protected:
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;
	HybridAutomaton<Number> const* mHybridAutomaton;
	FixedAnalysisParameters mFixedParameters;
	AnalysisParameters mParameters;
	UrgencyCEGARSettings mRefinementSettings;
	// use list instead of vector because pointers to the roots (stored in children as mParent)
	// must not be invalidated when pushing new (refined) roots later on.
	std::list<ReachTreeNode<Representation>> mRoots;

  private:
	/**
     * @brief Creates a new child node of parent with the given initial set.
     * @param jsucc Contains the initial set and the jump timing offset.
     * @param transition The taken discrete jump from the parent.
     * @param parent The parent node of the new node.
     * @return The newly created node.
     */
	auto createChildNode( const TimedValuationSet<Representation>& jsucc, const Transition<Number>* transition, ReachTreeNode<Representation>* parent )
		  -> ReachTreeNode<Representation>*;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
