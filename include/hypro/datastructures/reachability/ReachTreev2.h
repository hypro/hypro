/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../util/typetraits.h"
#include "../HybridAutomaton/HybridAutomaton.h"
#include "../HybridAutomaton/Pathv2.h"
#include "TreeNodev2.h"

#include <carl/interval/Interval.h>
#include <ostream>
#include <vector>

namespace hypro {

template <class Representation>
class ReachTreeNode : public TreeNode<ReachTreeNode<Representation>> {
  private:
	using Number = rep_number<Representation>;
	using Base = TreeNode<ReachTreeNode<Representation>>;

    Location<Number> const *mLocation = nullptr;                               ///< location in which the flowpipe was computed
    Transition<Number> const *mTransition{};                                   ///< the transition which lead here. nullptr for roots
    std::vector<Representation> mFlowpipe{};                                   ///< contains computed flowpipe
    Representation mInitialSet;                                                   ///< contains initial set for the flowpipe
    carl::Interval<SegmentInd> mTimings{};                                       ///< global time covered by inital set (used as offset)
    std::optional<std::vector<carl::Interval<Number>>> mInitialBoundingBox{};  ///< optional bounding box of the initial set
    TRIBOOL mHasFixedPoint = TRIBOOL::NSET;                                       ///< true, if the initial set of this node is strictly contained in the initial set of another node in the current tree
    ReachTreeNode<Representation> *mFixedPointReason = nullptr;                   ///< points to the node which is the reason for fixed-point detection
    bool mIsOnZenoCycle = false;                                               ///< true, if the node is the end of a Zeno-Cycle
    bool mFinishesWithTimelock = false;                                        ///< true, if the node exhibits a timelock
    bool mPotentiallyUnsafe = false;                                            ///< true, if the analysis has found a non-empty intersection with the set of bad states
	std::map<Transition<Number>*, UrgencyRefinementLevel> mUrgRefinementLevels{};  ///< refinement level for outgoing urgent transitions
	std::vector<SegmentInd> mFpTimings{};										   ///< timing information for simultaneous segments (urgency)
	REACHABILITY_RESULT mSafetyResult;											   ///< safety of flowpipe segments

public:
    // Exposition types
    using Rep = Representation;

    // Forwarding from base
    using Base::getChildren;
    using Base::getDepth;

    ReachTreeNode(ReachTreeNode *parent, Transition<Number> const *transition, Location<Number> const *loc, Representation initialSet, carl::Interval<SegmentInd> timings)
		: Base( parent )
		, mLocation( loc )
		, mTransition( transition )
		, mInitialSet( initialSet )
		, mTimings( timings ) {
	}

	ReachTreeNode( Location<Number> const* loc, Representation initialSet, carl::Interval<SegmentInd> timings )
		: mLocation( loc )
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
	ReachTreeNode& addChild( Representation initialSet, carl::Interval<SegmentInd> timings, Transition<Number> const* transition );

	/**
	 * @brief Get the path to the current node (computed)
	 * @return Path<Number, SegmentInd>
	 */
	Path<Number> getPath() const;

	// auto getParent() const { return this->mParent; }

	Transition<Number> const* getTransition() const { return mTransition; }

	/**
	 * @brief Get access to the flowpipe
	 * @return std::vector<Representation>*
	 */
	std::vector<Representation>& getFlowpipe() { return mFlowpipe; }
	std::vector<Representation> const& getFlowpipe() const { return mFlowpipe; }
	void setFlowpipe( std::vector<Representation>&& fp ) { mFlowpipe = std::move( fp ); }
	void setFlowpipe( const std::vector<Representation>& fp ) { mFlowpipe = fp; }

	const REACHABILITY_RESULT& getSafety() const { return mSafetyResult; }
	void setSafety( REACHABILITY_RESULT result ) { mSafetyResult = result; }

	/**
   * @brief Get access to the urgent Transitions
   * @return Map of urgent transitions to refinement level
   */
	std::map<Transition<Number>*, UrgencyRefinementLevel>& getUrgencyRefinementLevels() { return mUrgRefinementLevels; }
	std::map<Transition<Number>*, UrgencyRefinementLevel> const& getUrgencyRefinementLevels() const { return mUrgRefinementLevels; }

	/**
	 * @brief Get the initial set
	 * @return const Representation&
	 */
	const Representation& getInitialSet() const { return mInitialSet; }

	[[deprecated( "Use getInitialSet() instead." )]] const Representation& getState() const { return mInitialSet; }
	/// Getter for the location
	const Location<Number>* getLocation() const { return mLocation; }
	/// Getter for timing-information (global time when the node was active)
	const carl::Interval<SegmentInd>& getTimings() const { return mTimings; }
	std::vector<SegmentInd>& getFpTimings() { return mFpTimings; }
	const std::vector<SegmentInd>& getFpTimings() const { return mFpTimings; }

	/**
	 * @brief Get the time intervals the passed transition was enabled
	 * @param transition
	 * @return std::vector<carl::Interval<SegmentInd>>
	 * TODO Implement
	 */
	std::vector<carl::Interval<SegmentInd>> getEnabledTimings( Transition<Number> const* const transition ) const;
	/// Sets the bounding box of the sets of reachable states for this node (caching)
	void setBoundingBox( const std::vector<carl::Interval<Number>>& intervals ) { mInitialBoundingBox = intervals; }
	/// Returns the bounding box stored for this nodes' sets of reachable states
	const std::optional<std::vector<carl::Interval<Number>>>& getInitialBoundingBox() const { return mInitialBoundingBox; };

	/**
	 * Set the fixed-point state to a Boolean value (once set, cannot be unset), true if the initial set of this node is fully contained in the initial set of another node, false otherwise.
	 * @param hasFixedPoint
	 */
	void setFixedPoint( bool hasFixedPoint = true, ReachTreeNode<Representation>* reason = nullptr );

    /**
     * Returns whether this node represents a fixed point.
     * @return True, if the initial set of this node is fully contained in the initial set of another node of this tree, false otherwise, nset if this property has not been set yet.
     */
    TRIBOOL hasFixedPoint() const { return mHasFixedPoint; }

    /// Returns a pointer to the node in the path leading to this node-object, which is the reason for finding a fixed-point
    ReachTreeNode<Representation> *getFixedPointReason() { return mFixedPointReason; }

    /// Setter of a flag indicating the node is on a Zeno-cycle
    void flagZenoCycle(bool zeno = true) { mIsOnZenoCycle = zeno; }

    /// Getter of the flag, which indicates whether the node is on a Zeno-cycle
    bool isOnZenoCycle() const { return mIsOnZenoCycle; }

    /// Setter for a flag indicating, that the node exhibits a timelock
    void flagTimelock(bool timelock = true) { mFinishesWithTimelock = timelock; }

    /// Getter for the unsafe-status of this node
    bool intersectedUnsafeRegion() const { return mPotentiallyUnsafe; }

    /// Setter for a flag indicating, that the node has intersected the set of bad states
    void flagUnsafe(bool unsafe = true) { mPotentiallyUnsafe = unsafe; }

    /// Getter for the timelock-status of this node, i.e., whether a timelock has been detected during analysis
    bool hasTimelock() const { return mFinishesWithTimelock; }
};

template <typename Representation>
std::ostream& operator<<( std::ostream& out, const ReachTreeNode<Representation>& node ) {
	out << "{ " << node.getLocation()->getName() << ", init " << node.getInitialSet() << " }";
	return out;
}

/**
 * @brief Convenience function to create roots of a search tree from the initial states of the passed hybrid automaton.
 * @tparam Representation
 * @tparam Number
 * @param ha
 * @return std::vector<ReachTreeNode<Representation>>
 */
template <class Representation, class Number>
std::vector<ReachTreeNode<Representation>> makeRoots( HybridAutomaton<Number> const& ha ) {
	std::vector<ReachTreeNode<Representation>> roots{};

	std::transform( ha.getInitialStates().begin(), ha.getInitialStates().end(), std::back_inserter( roots ), []( auto const& locCond ) {
		auto const& [location, condition] = locCond;
		return ReachTreeNode<Representation>{ location, Representation{ condition.getMatrix(), condition.getVector() }, carl::Interval<SegmentInd>{ 0, 0 } };
	} );

	return roots;
}

template <class RTN>
struct RTN_Rep_i;

template <class Representation>
struct RTN_Rep_i<ReachTreeNode<Representation>> {
	using type = Representation;
};

template <class RTN>
using RTN_Rep = typename RTN_Rep_i<std::remove_pointer_t<std::remove_reference_t<std::remove_cv_t<RTN>>>>::type;

}  // namespace hypro

#include "ReachTreev2.tpp"