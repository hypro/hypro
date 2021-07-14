#pragma once

#include "../../../datastructures/reachability/Settings.h"
#include "../../../datastructures/reachability/TimeTransformationCache.h"
#include "../../../datastructures/reachability/timing/HierarchicalIntervalVector.h"
#include "../../../util/logging/Logger.h"
#include "../../../util/plotting/PlotData.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../handlers/badStateHandlers/ltiBadStateHandler.h"
#include "../workers/LTIFlowpipeConstruction.h"

#include <optional>
#include <vector>

namespace hypro {

template <typename Representation>
class DiscreteWorker {
  private:
    using Number = typename Representation::NumberType;


  public:
    struct JumpSuccessorGen;

    DiscreteWorker( const HybridAutomaton<Number>& ha, const AnalysisParameters& settings, std::size_t subspace = 0 )
        : mHybridAutomaton( ha )
        , mSettings( settings )
        , mSubspace( subspace ) {}

    template <typename OutputIt>
    REACHABILITY_RESULT computeTimeSuccessors( const Representation& initialSet, Location<Number> const* loc, OutputIt out, bool checkSafety = true ) const;

    std::vector<JumpSuccessor<Representation>> computeJumpSuccessors( std::vector<Representation> const& flowpipe, Location<Number> const* loc ) const;
    JumpSuccessorGen getJumpSuccessors( std::vector<Representation> const& flowpipe, Transition<Number> const* transition ) const;
    // Compute jump successors for guard enabling sets
    std::vector<TimedValuationSet<Representation>> computeJumpSuccessorsForGuardEnabled( std::vector<IndexedValuationSet<Representation>>& predecessors, Transition<Number> const* trans ) const;

  protected:
    const HybridAutomaton<Number>& mHybridAutomaton;  ///< hybrid automaton to analyze
    const AnalysisParameters& mSettings;              ///< analysis settings
    std::size_t mSubspace;

};

}  // namespace hypro

#include "DiscreteWorker.tpp"
