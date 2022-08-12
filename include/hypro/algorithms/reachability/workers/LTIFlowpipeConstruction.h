#pragma once
#pragma once

#include "../../../datastructures/HybridAutomaton/Transition.h"
#include "../../../datastructures/HybridAutomaton/flow/linear.h"
#include "../../../representations/GeometricObjectBase.h"
#include "../../../types.h"
#include "../../../util/typetraits.h"
#include "../FlowpipeConstructionConvenience.h"
#include "../types.h"
#include "../util.h"

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
std::vector<Representation> aggregate( int segmentsPerBlock, std::vector<Representation>& valuationSets );


}  // namespace hypro

#include "LTIFlowpipeConstruction.tpp"