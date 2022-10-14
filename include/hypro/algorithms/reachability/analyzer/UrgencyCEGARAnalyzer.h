/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../../datastructures/HybridAutomaton/HybridAutomaton.h"
#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"
#include "../workers/UrgencyCEGARWorker.h"
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
 * Uses a CEGAR approach where urgent transitions are treated differently
 * depending on their refinement level. The coarsest level ignores urgency and the finest
 * level involves computing the set difference with jump enabling sets which may cause
 * splitting in the reach tree. Refinement uses the UrgencyRefinementAnalyzer
 * which is called whenever an unsafe node is encountered.
 */
template <typename Representation, typename Automaton>
class UrgencyCEGARAnalyzer {
	using Number = typename Representation::NumberType;
	using LocationT = typename Automaton::LocationType;
	using RefinementResult = typename UrgencyRefinementAnalyzer<Representation, Automaton>::RefinementResult;

  public:
	using UrgencyCEGARResult = AnalysisResult<UrgencyCEGARSuccess, Failure<Representation, LocationT>>;

	UrgencyCEGARAnalyzer( Automaton const& ha,
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
					root.getUrgencyRefinementLevels()[trans.get()] = detail::getInitialRefinementLevel( trans.get(), mRefinementSettings );
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
	std::vector<ReachTreeNode<Representation, LocationT>*> getRoots() {
		std::vector<ReachTreeNode<Representation, LocationT>*> res;
		std::transform( mRoots.begin(), mRoots.end(), std::back_inserter( res ), []( auto& root ) {
			return &root;
		} );
		return res;
	}

  protected:
	std::deque<ReachTreeNode<Representation, LocationT>*> mWorkQueue;  ///< Holds unprocessed reach tree nodes.
	Automaton const* mHybridAutomaton;								   ///< Hybrid automaton.
	FixedAnalysisParameters mFixedParameters;						   ///< Analysis parameters.
	AnalysisParameters mParameters;									   ///< Analysis parameters.
	UrgencyCEGARSettings mRefinementSettings;						   ///< Settings that contain information about refinement.
	// use list instead of vector because pointers to the roots (stored in children as mParent)
	// must not be invalidated when pushing new (refined) roots later on:
	std::list<ReachTreeNode<Representation, LocationT>> mRoots;	 ///< Contains the roots of the computed reach tree.

  private:
	/**
	 * @brief Creates a new child node of parent with the given initial set.
	 * @param jsucc Contains the initial set and the jump timing offset.
	 * @param transition The taken discrete jump from the parent.
	 * @param parent The parent node of the new node.
	 * @return The newly created node.
	 */
	auto createChildNode( const TimedValuationSet<Representation>& jsucc, const Transition<LocationT>* transition, ReachTreeNode<Representation, LocationT>* parent )
		  -> ReachTreeNode<Representation, LocationT>*;
};

}  // namespace hypro

#include "UrgencyCEGARAnalyzer.tpp"
