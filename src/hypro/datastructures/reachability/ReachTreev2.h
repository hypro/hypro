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
class ReachTreeNode : public TreeNode<ReachTreeNode<Representation>> {
  private:
	using Number = rep_number<Representation>;
	using Base = TreeNode<ReachTreeNode<Representation>>;

	Location<Number> const* mLocation;						///< location in which the flowpipe was computed
	std::vector<Transition<Number> const*> mTransitions{};	///< contains the corresponding transition for each child
	carl::Interval<SegmentInd> mTimings{};					///< global time covered by inital set the flowpipe (used as offset)
	std::vector<Representation>* mFlowpipe{};				///< contains computed flowpipe
	Representation mInitialSet;								///< contains initial set for the flowpipe

  public:
	ReachTreeNode( ReachTreeNode* parent, Location<Number> const* loc, std::vector<Representation>* flowpipe, Representation initialSet )
		: Base( parent )
		, mLocation( loc )
		, mFlowpipe( flowpipe )
		, mInitialSet( initialSet ) {
	}

	ReachTreeNode( Location<Number> const* loc, std::vector<Representation>* flowpipe, Representation initialSet )
		: mLocation( loc )
		, mFlowpipe( flowpipe )
		, mInitialSet( initialSet ) {
	}

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

	/**
     * @brief Get the time intervals the passed transition was enabled
     * @param transition
     * @return std::vector<carl::Interval<SegmentInd>>
     */
	std::vector<carl::Interval<SegmentInd>> getEnabledTimings( Transition<Number> const* const transition ) const;
};

}  // namespace hypro