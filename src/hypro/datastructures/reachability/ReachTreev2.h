#pragma once

#include "../HybridAutomaton/Location.h"
#include "../HybridAutomaton/Path.h"
#include "../HybridAutomaton/Transition.h"
#include "TreeNodev2.h"
#include "util/typetraits.h"

#include <carl/interval/Interval.h>
#include <vector>

template <class Representation>
class ReachTreeNodev2 : TreeNodev2<ReachTreeNodev2<Representation>> {
  private:
	using Number = rep_number<Representation>;
	using Base = TreeNodev2<ReachTreeNodev2<Representation>>;

	Location<Number> const* mLocation;									  ///< location in which the flowpipe was computed
	std::vector<std::vector<carl::Interval<SegmentInd>>> mTransitions{};  ///< contains enabled timings for transitions, relies on FIXED order of transitions in the HA.
	std::vector<Representation>* mFlowpipe{};							  ///< contains computed flowpipe

  public:
	ReachTreeNodev2( ReachTreeNodev2* parent, Location<Number> const* loc, std::vector<Representation>* flowpipe )
		: Base( parent )
		, mLocation( loc )
		, mFlowpipe( flowpipe ) {
	}

	ReachTreeNodev2( Location<Number> const* loc, std::vector<Representation>* flowpipe )
		: mLocation( loc )
		, mFlowpipe( flowpipe ) {
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
     * @brief Get the time intervals the passed transition was enabled
     * @param transition
     * @return std::vector<carl::Interval<SegmentInd>>
     */
	std::vector<carl::Interval<SegmentInd>> getEnabledTimings( Transition<Number> const* const transition ) const;
};