#pragma once

#include "../HybridAutomaton/Location.h"
#include "../HybridAutomaton/Path.h"
#include "../HybridAutomaton/Transition.h"
#include "TreeNodev2.h"
#include "util/typetraits.h"

#include <carl/interval/Interval.h>
#include <vector>

namespace hypro {

template <class Representation>
class ReachTreeNode : private TreeNode<ReachTreeNode<Representation>> {
  private:
	using Number = rep_number<Representation>;
	using Base = TreeNode<ReachTreeNode<Representation>>;

	Location<Number> const* mLocation;						///< location in which the flowpipe was computed
	std::vector<Transition<Number> const*> mTransitions{};	///< contains the corresponding transition for each child
	std::vector<Representation>* mFlowpipe{};				///< contains computed flowpipe
	Representation mInitialSet;								///< contains initial set for the flowpipe
	carl::Interval<SegmentInd> mTimings{};					///< global time covered by inital set the flowpipe (used as offset)

  public:
	//Forwarding from base
	using Base::getChildren;
	using Base::getDepth;

	ReachTreeNode( ReachTreeNode* parent, Location<Number> const* loc, std::vector<Representation>* flowpipe, Representation initialSet, carl::Interval<SegmentInd> timings )
		: Base( parent )
		, mLocation( loc )
		, mFlowpipe( flowpipe )
		, mInitialSet( initialSet )
		, mTimings( timings ) {
	}

	ReachTreeNode( Location<Number> const* loc, std::vector<Representation>* flowpipe, Representation initialSet, carl::Interval<SegmentInd> timings )
		: mLocation( loc )
		, mFlowpipe( flowpipe )
		, mInitialSet( initialSet )
		, mTimings( timings ) {
	}

	/**
	 * @brief Add a child that was reached by a discrete jump
	 * @param flowpipe The flowpipe in the new location
	 * @param initialSet The initial set in the location after the jump
	 * @param timings The time slots which the initial set covers, i.e. during which the transition was enabled
	 * @param transition The transition taken to the new location
	 * @return A reference to the new child
	 */
	ReachTreeNode& addChild( std::vector<Representation>* flowpipe, Representation initialSet, carl::Interval<SegmentInd> timings, Transition<Number> const* transition );

	/**
     * @brief Get the path to the current node (computed)
     * @return Path<Number, SegmentInd>
     */
	Path<Number, SegmentInd> getPath() const;

	/**
     * @brief Get access to the flowpipe
     * @return std::vector<Representation>*
     */
	std::vector<Representation>* getFlowpipe() const { return mFlowpipe; }

	/**
	 * @brief Get the initial set
	 * @return const Representation&
	 */
	const Representation& getInitialSet() const { return mInitialSet; }

	const Location<Number>* getLocation() const { return mLocation; }

	const carl::Interval<SegmentInd>& getTimings() const { return mTimings; }

	/**
     * @brief Get the time intervals the passed transition was enabled
     * @param transition
     * @return std::vector<carl::Interval<SegmentInd>>
     */
	std::vector<carl::Interval<SegmentInd>> getEnabledTimings( Transition<Number> const* const transition ) const;
};

}  // namespace hypro

#include "ReachTreev2.tpp"