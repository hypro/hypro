#pragma once

namespace hypro {

template <typename StateSet>
StateSet linearApplyTimeEvolution( const StateSet& initialSet, const StateSet& flow );

template <typename StateSet>
StateSet linearApplyBoundedTimeEvolution( const StateSet& initialSet, const StateSet& flow, tNumber timeBound );

}  // namespace hypro

#include "linearTimeEvolutionHandler.tpp"