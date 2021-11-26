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
class ReachTreeNode : private TreeNode<ReachTreeNode<Representation>> {
  private:
	using Number = rep_number<Representation>;
	using Base = TreeNode<ReachTreeNode<Representation>>;

	Location<Number> const* mLocation;										   ///< location in which the flowpipe was computed
	Transition<Number> const* mTransition{};								   ///< the transition which lead here. nullptr for roots
	std::vector<Representation> mFlowpipe{};								   ///< contains computed flowpipe
	Representation mInitialSet;												   ///< contains initial set for the flowpipe
	carl::Interval<SegmentInd> mTimings{};									   ///< global time covered by inital set (used as offset)
	std::optional<std::vector<carl::Interval<Number>>> mInitialBoundingBox{};  ///< optional bounding box of the initial set

  public:
	//Exposition types
	using Rep = Representation;

	//Forwarding from base
	using Base::getChildren;
	using Base::getDepth;

	ReachTreeNode( ReachTreeNode* parent, Transition<Number> const* transition, Location<Number> const* loc, Representation initialSet, carl::Interval<SegmentInd> timings )
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

	auto getParent() const { return this->mParent; }

	Transition<Number> const* getTransition() const { return mTransition; }

	/**
     * @brief Get access to the flowpipe
     * @return std::vector<Representation>*
     */
	std::vector<Representation>& getFlowpipe() { return mFlowpipe; }
	std::vector<Representation> const& getFlowpipe() const { return mFlowpipe; }
	void setFlowpipe( std::vector<Representation>&& fp ) { mFlowpipe = std::move( fp ); }
	void setFlowpipe( const std::vector<Representation>& fp ) { mFlowpipe = fp; }

	/**
	 * @brief Get the initial set
	 * @return const Representation&
	 */
	const Representation& getInitialSet() const { return mInitialSet; }

	[[deprecated( "Use getInitialSet() instead." )]] const Representation& getState() const { return mInitialSet; }

	const Location<Number>* getLocation() const { return mLocation; }

	const carl::Interval<SegmentInd>& getTimings() const { return mTimings; }

	/**
     * @brief Get the time intervals the passed transition was enabled
     * @param transition
     * @return std::vector<carl::Interval<SegmentInd>>
	 * TODO Implement
     */
	std::vector<carl::Interval<SegmentInd>> getEnabledTimings( Transition<Number> const* const transition ) const;

	void setBoundingBox( const std::vector<carl::Interval<Number>>& intervals ) { mInitialBoundingBox = intervals; }
	const std::optional<std::vector<carl::Interval<Number>>>& getInitialBoundingBox() const { return mInitialBoundingBox; };
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