#pragma once

#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/TimeTransformationCache.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../workers/LTIFlowpipeConstruction.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../handlers/urgencyHandlers/ltiUrgencyHandler.h"

#include <optional>

namespace hypro {

/**
 * @brief   Class implementing a worker for automata with urgent transitions.
 * @details Implements methods for computing time elapse and discrete transitions.
 *          Repeated calling of these methods allows implementation of reachability analysis.
 *          The UrgencyWorker considers urgent transitions by computing the set difference
 *          of the reachable set and urgent guards.
 * @tparam Representation   The used state set representation.
 */
template <typename Representation>
class UrgencyWorker {
  private:
    using Number = typename Representation::NumberType;
    using Flowpipe = std::vector<IndexedValuationSet<Representation>>;
    using JumpSuccessors = std::vector<JumpSuccessor<Representation>>;

  public:

    UrgencyWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache )
        : mHybridAutomaton( ha )
        , mSettings( settings )
        , mLocalTimeHorizon( localTimeHorizon )
        , mTrafoCache( trafoCache ) {}

    /**
     * @brief Computes the states reachable by letting time elapse.
     * @param task Used to access the the location, initial set and urgent transitions.
     * @return Safety after time elapse.
     */
    REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<Representation>& task );
    /**
     * @brief Getter function for the computed flowpipe.
     * @details The flowpipe is stored as pairs of valuation set and segment index,
     *          since set difference computation can split segments.
     * @return Pairs of flowpipe segments and their timing index.
     */
    const Flowpipe& getFlowpipe() const { return mFlowpipe; }

    /**
     * @brief Computes the states reachable by taking a discrete transition.
     * @details Performs aggregation and applies the reset.
     * @param task Used to access the location.
     */
    void computeJumpSuccessors( const ReachTreeNode<Representation>& task );
    /**
     * @brief Getter function for the computed jump successors.
     */
    const JumpSuccessors& getJumpSuccessors() const { return mJumpSuccessors; }

    void reset() {
        mJumpSuccessors.clear();
        mFlowpipe.clear();
    }

  private:
    /**
     * @brief Performs operations on the segment obtained by letting time elapse.
     * @details Applies intersection with the invariant, set difference with urgent guards
     *          and intersection with bad states.
     * @return Safety of the segment.
     */
    REACHABILITY_RESULT handleSegment(
        const ReachTreeNode<Representation>& task, const Representation& segment, SegmentInd timing );
    void addSegment( const Representation& segment, SegmentInd timing );
    void addSegment( const std::vector<Representation>& segment, SegmentInd timing );

  protected:
    const HybridAutomaton<Number>& mHybridAutomaton;  ///< hybrid automaton to analyze
    const AnalysisParameters& mSettings;              ///< analysis settings
    tNumber mLocalTimeHorizon;                        ///< local time horizon
    TimeTransformationCache<Number>& mTrafoCache;     ///< cache for matrix exponential
    Flowpipe mFlowpipe;                               ///< Storage of computed time successors
    JumpSuccessors mJumpSuccessors;                   ///< Storage of computed jump successors


    size_t const mNumSegments = size_t( std::ceil( std::nextafter( carl::convert<tNumber, double>( mLocalTimeHorizon / mSettings.timeStep ), std::numeric_limits<double>::max() ) ) );
};

}  // namespace hypro

#include "UrgencyWorker.tpp"
