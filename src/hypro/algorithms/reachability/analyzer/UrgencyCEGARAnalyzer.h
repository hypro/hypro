#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/UrgencyWorker.h"
#include "./ReturnTypes.h"
#include "./impl/UrgencyRefinementAnalyzer.h"

#include <queue>

namespace hypro {

/**
 * @brief Structure to indicate that analysis was successful, i.e. safety could be verified.
 */
struct UrgencyCEGARSuccess {};

/**
 * @brief Analyzer for automata with LTI dynamics and urgent transitions.
 * @detail Uses a CEGAR approach where urgent transitions are treated differently
 * depending on their refinement level. The coarsest level ignores urgency and the finest
 * level involves computing the set difference with jump enabling sets which may cause
 * splitting in the reach tree. Refinement uses the UrgencyRefinementAnalyzer
 * which is called whenever an unsafe node is encountered.
 */
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

	/**
	 * @brief Main method to start analysis.
	 * @return Indicate either success if safety can be verified or failure otherwise.
	 */
	UrgencyCEGARResult run();
	/**
	 * @brief Get the roots of the computed reach tree.
	 * @return A vector containing pointers to the roots.
	 */
	std::vector<ReachTreeNode<Representation>*> getRoots() {
		std::vector<ReachTreeNode<Representation>*> res;
		std::transform( mRoots.begin(), mRoots.end(), std::back_inserter( res ), []( auto& root ) {
			return &root;
		} );
		return res;
	}

  protected:
	std::deque<ReachTreeNode<Representation>*> mWorkQueue;	///< Holds unprocessed reach tree nodes.
	HybridAutomaton<Number> const* mHybridAutomaton;		///< Hybrid automaton.
	FixedAnalysisParameters mFixedParameters;				///< Analysis paramteters.
	AnalysisParameters mParameters;							///< Analysis paramteters.
	UrgencyCEGARSettings mRefinementSettings;				///< Settings that contain information about refinement.
	// use list instead of vector because pointers to the roots (stored in children as mParent)
	// must not be invalidated when pushing new (refined) roots later on.
	std::list<ReachTreeNode<Representation>> mRoots;  ///< Contains the roots of the computed reach tree.

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
