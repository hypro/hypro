/*
 * Class that describes a hybrid automaton with components.
 * @file   HybridAutomatonComp.cpp
 * @author Tobias Vogel <tobias.vogel@rwth-aachen.de>
 *
 * @since 	2017-12-03
 */

#pragma once

#include "HybridAutomaton.h"
#include "../../types.h"


namespace hypro {

  template <typename Number, typename State>
  class HybridAutomaton;

  /**
    * @brief      Class for linear hybrid automata with components.
    * @tparam     Number  Number type.
  */
  template <typename Number, typename State = State_t<Number,Number>>
  class HybridAutomatonComp {
    private:
      std::set<HybridAutomaton<Number, State>*> mAutomatas;

    public:
      HybridAutomatonComp() {};

      ~HybridAutomatonComp() {};

      void addAutomata(HybridAutomaton<Number, State>* automata) { mAutomatas.insert(automata); }
  };
}

#include "HybridAutomatonComp.tpp"