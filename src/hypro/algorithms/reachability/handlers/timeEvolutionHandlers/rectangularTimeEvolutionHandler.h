#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangular.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangularOperations.h"
#include "../../../../representations/GeometricObjectBase.h"
#include "../../../../representations/conversion/conversionHelper.h"
#include "../../../../util/typetraits.h"
#include "../IHandler.h"

#include <sstream>
#include <string>

namespace hypro {

template <typename Number, class... Reps>
State<Number, Reps...> rectangularApplyTimeEvolution( const State<Number, Reps...>& initialSet, const rectangularFlow<Number>& flow );

template <typename Number, class... Reps>
State<Number, Reps...> rectangularApplyReverseTimeEvolution( const State<Number, Reps...>& badSet, const rectangularFlow<Number>& flow );

template <template <typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& initialSet, const rectangularFlow<Number>& flow );

template <template <typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyBoundedTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& initialSet, const rectangularFlow<Number>& flow, tNumber timeBound );

template <typename Number>
CarlPolytope<Number> rectangularApplyReverseTimeEvolution( const CarlPolytope<Number>& badSet, const rectangularFlow<Number>& flow );

template <typename Number>
CarlPolytope<Number> rectangularUnderapproximateReverseTimeEvolution( const CarlPolytope<Number>& badSet, const rectangularFlow<Number>& flow );

template <template <typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyReverseTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& badSet, const rectangularFlow<Number>& flow ) {
	auto convertedSet = Converter::toCarlPolytope( badSet );
	auto convertedResult = rectangularApplyReverseTimeEvolution( convertedSet, flow );
	PolyhedralRepresentation<Number, Converter, Setting> res;
	convert( convertedResult, res );
	return res;
}

template <template <typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting, enable_if<!std::is_same_v<CarlPolytope<Number>, PolyhedralRepresentation<Number, Converter, Setting>>> = 0>
PolyhedralRepresentation<Number, Converter, Setting> rectangularUnderapproximateReverseTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& badSet, const rectangularFlow<Number>& flow ) {
	auto convertedSet = Converter::toCarlPolytope( badSet );
	auto convertedResult = rectangularUnderapproximateReverseTimeEvolution( convertedSet, flow );
	PolyhedralRepresentation<Number, Converter, Setting> res;
	convert( convertedResult, res );
	return res;
}

template <typename Number>
CarlPolytope<Number> rectangularApplyTimeEvolution( const CarlPolytope<Number>& initialSet, const rectangularFlow<Number>& flow );

}  // namespace hypro

#include "rectangularTimeEvolutionHandler.tpp"
