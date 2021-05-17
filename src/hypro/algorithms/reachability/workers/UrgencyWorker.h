#pragma once

#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/TimeTransformationCache.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../workers/LTIFlowpipeConstruction.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../handlers/urgencyHandlers/ltiUrgencyHandler.h"

#include <optional>

namespace hypro {

template <typename Representation>
class UrgencyWorker {
  private:
    using Number = typename Representation::NumberType;
    using Flowpipe = std::vector<IndexedValuationSet<Representation>>;
    using JumpSuccessors = std::vector<JumpSuccessor<Representation>>;

    struct PreviousSegmentGen;

  public:

    UrgencyWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, tNumber localTimeHorizon, TimeTransformationCache<Number>& trafoCache )
        : mHybridAutomaton( ha )
        , mSettings( settings )
        , mLocalTimeHorizon( localTimeHorizon )
        , mTrafoCache( trafoCache ) {}

    REACHABILITY_RESULT computeTimeSuccessors( const ReachTreeNode<Representation>& task ) const;

    void computeJumpSuccessors( const ReachTreeNode<Representation>& task ) const;
    const JumpSuccessors& getJumpSuccessors() const { return mJumpSuccessors; }

  private:
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
