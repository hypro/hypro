#pragma once
#pragma once

#include "algorithms/reachability/FlowpipeConstructionConvenience.h"
#include "algorithms/reachability/util.h"
#include "datastructures/HybridAutomaton/Transition.h"
#include "datastructures/HybridAutomaton/flow/linear.h"
#include "representations/GeometricObjectBase.h"
#include "types.h"
#include "util/typetraits.h"

#include <carl/interval/Interval.h>

namespace hypro {

template <class Number>
struct ErrorBoxes {
	Box<Number> X0Box{};
	Box<Number> ExternalInputBox{};
	Box<Number> DifferenceBox{};
};

template <class Number>
matrix_t<Number> computeTimeTransformation( linearFlow<Number> const& flow, tNumber timeStep );

template <class Representation, class Number>
Representation constructFirstSegment( Representation const& initialSet,
									  linearFlow<Number> const& flow,
									  matrix_t<Number> const& rawTransformation,
									  tNumber timeStep );

template <class Representation, class Number>
ErrorBoxes<Number> constructErrorBoxes( Number const& delta, matrix_t<Number> const& flowMatrix, Representation const& initialSet, matrix_t<Number> const& trafoMatrix, Box<Number> const& externalInput );

template <class Representation>
std::vector<Representation> aggregate( int segmentsPerBlock, std::vector<Representation>& valuationSets )

// template <class Representation, class Number, class OutputIterator>
// REACHABILITY_RESULT constructFlowpipe( Representation& initialSet,
// 									   Location<Number> const& location,
// 									   matrix_t<Number> const& rawTransformation,
// 									   HybridAutomaton<Number> const& automaton,
// 									   OutputIterator out,
// 									   int segments,
// 									   tNumber timeStep );

// template <class Representation, class Number, class OutputIterator>
// REACHABILITY_RESULT extendFlowpipe( Representation const& tailSegment,
// 									Location<Number> const& location,
// 									AffineTransformationMatrix<Number> const& transformation,
// 									HybridAutomaton<Number> const& automaton,
// 									OutputIterator out,
// 									int segments );

// template <class Representation, class Number>
// REACHABILITY_RESULT intersectBadStates( Representation const& valuationSet, HybridAutomaton<Number> const& automaton, Location<Number> const& loc );

// template <class Representation, class Number>
// JumpCandidates<Representation> getJumpCandidates( Transition<Number> const& transition, FlowpipeView<Representation> const& pipeView );

}  // namespace hypro

#include "LTIFlowpipeConstruction.tpp" a