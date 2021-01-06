#pragma once
#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangular.h"
#include "../../../../datastructures/HybridAutomaton/flow/rectangularOperations.h"
#include "../../../../representations/GeometricObjectBase.h"
#include "../../../../representations/conversion/conversionHelper.h"
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

template <template <typename, typename, typename> class PolyhedralRepresentation, typename Number, typename Converter, typename Setting>
PolyhedralRepresentation<Number, Converter, Setting> rectangularApplyReverseTimeEvolution( const PolyhedralRepresentation<Number, Converter, Setting>& badSet, const rectangularFlow<Number>& flow );

template <typename Number>
CarlPolytope<Number> rectangularApplyTimeEvolution( const CarlPolytope<Number>& initialSet, const rectangularFlow<Number>& flow );

template <typename Number>
CarlPolytope<Number> rectangularApplyReverseTimeEvolution( const CarlPolytope<Number>& badSet, const rectangularFlow<Number>& flow );

}  // namespace hypro

#include "rectangularTimeEvolutionHandler.tpp"
