/*
 * Class that describes a hybrid automaton with components.
 * @file   HybridAutomatonComp.cpp
 * @author Tobias Vogel <tobias.vogel@rwth-aachen.de>
 *
 * @since 	2017-12-03
 */

#pragma once

#include "../../types.h"
#include "HybridAutomaton.h"

namespace hypro {

template <typename Number>
class HybridAutomaton;

/**
 * @brief      Class for linear hybrid automata with components.
 * @tparam     Number  Number type.
 */
template <typename Number>
class HybridAutomatonComp {
  private:
	std::set<HybridAutomaton<Number>*> mAutomatas;

  public:
	HybridAutomatonComp(){};

	~HybridAutomatonComp(){};

	void addAutomata( HybridAutomaton<Number>* automata ) { mAutomatas.insert( automata ); }
};
}  // namespace hypro

#include "HybridAutomatonComp.tpp"
