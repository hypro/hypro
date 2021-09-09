#pragma once
#include "../../../util/logging/Logger.h"
#include "../../HybridAutomaton/Transition.h"

#include <map>

namespace hypro {

// forward declaration
template <typename Number>
class EventTimingNode;

template <typename N>
struct ChildTimingInformation {
	std::map<EventTimingNode<N>*, bool> timingInformation;
};

/**
 * @brief A class storing information about timing information. The idea is to keep track of timing nodes which are the result of a non-aggregated discete jump.
 *
 * @tparam Number
 */
template <typename Number>
class TimingAggregate {
  private:
	std::map<const Transition<Number>*, ChildTimingInformation<Number>> mChildTimings;

  public:
	TimingAggregate() = default;

	TimingAggregate( const Transition<Number>* t, const std::vector<EventTimingNode<Number>*>& nodes ) {
		mChildTimings[t] = ChildTimingInformation<Number>();
		for ( const auto p : nodes ) {
			// assert(mChildTimings[t].empty() || mChildTimings[t].begin()->first->getParent() == p->getParent());
			mChildTimings[t].timingInformation[p] = false;
		}
	}

	/**
	 * @brief Add a transition along with the resuling timing nodes, which are responsible for handling this transition.
	 *
	 * @param t
	 * @param nodes
	 */
	void addTransition( const Transition<Number>* t, const std::vector<EventTimingNode<Number>*>& nodes ) {
		TRACE( "hypro.datastructures.timing", "Add " << nodes.size() << " for transition " << t );
		mChildTimings[t] = ChildTimingInformation<Number>();
		for ( const auto p : nodes ) {
			// assert(mChildTimings[t].timingInformation.empty() || mChildTimings[t].timingInformation.begin()->first->getParent() == p->getParent());
			mChildTimings[t].timingInformation[p] = false;
		}
	}

	/**
	 * @brief Mark the computation as being completed (i.e. timing information is complete) for a specific successor of a transition t.
	 *
	 * @param t
	 * @param node
	 */
	void markCompleted( const Transition<Number>* t, EventTimingNode<Number>* node ) {
		TRACE( "hypro.datastructures.timing", "Mark node " << node << " as complete for transition " << t );
		if ( mChildTimings.find( t ) != mChildTimings.end() ) {
			if ( mChildTimings[t].timingInformation.find( node ) != mChildTimings[t].timingInformation.end() ) {
				mChildTimings[t].timingInformation[node] = true;
			}
		}
	}

	/**
	 * @brief Get the discrete successor count for a given transition.
	 *
	 * @param t
	 * @return std::size_t
	 */
	std::size_t getSuccessorCount( const Transition<Number>* t ) const {
		if ( mChildTimings.find( t ) == mChildTimings.end() ) {
			return 0;
		} else {
			return mChildTimings[t].timingInformation.size();
		}
	}

	/**
	 * @brief Get the number of discrete successors which still require computation.
	 *
	 * @param t
	 * @return std::size_t
	 */
	std::size_t getOpenSuccessorCount( const Transition<Number>* t ) const {
		if ( mChildTimings.find( t ) == mChildTimings.end() ) {
			return 0;
		} else {
			std::size_t res = 0;
			std::for_each( mChildTimings.at( t ).timingInformation.begin(), mChildTimings.at( t ).timingInformation.end(), [&res]( const auto& pair ) {if(!pair.second) { ++res; } } );
			TRACE( "hypro.datastructures.timing", "Transition " << t << " has " << res << " open successors." );
			return res;
		}
	}

	/**
	 * @brief Get the Successor Nodes for a specific transition. May be used to merge those nodes.
	 *
	 * @param t
	 * @return std::vector<EventTimingNode<Number>*>
	 */
	std::vector<EventTimingNode<Number>*> getSuccessorNodes( const Transition<Number>* t ) {
		std::vector<EventTimingNode<Number>*> res;
		if ( mChildTimings.find( t ) != mChildTimings.end() ) {
			for ( auto& pair : mChildTimings[t].timingInformation ) {
				res.emplace_back( pair.first );
			}
		}
		return res;
	}
};

}  // namespace hypro
