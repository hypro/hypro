/*
 * Class that describes a hybrid automaton with components.
 * @file   HybridAutomatonComp.cpp
 * @author Tobias Vogel <tobias.vogel@rwth-aachen.de>
 *
 * @since 	2017-12-03
 */

#pragma once

#include "HybridAutomaton.h"

namespace hypro {

  /**
    * @brief      Class for linear hybrid automata with components.
    * @tparam     Number  Number type.
  */
  template <typename Number, typename State = State_t<Number,Number>>
  class HybridAutomatonComp {
    public:
      using automataSet = std::set<HybridAutomaton<Number, State_t<Number, Number>>*>;
    private:
      automataSet mAutomatas;

    public:
      HybridAutomatonComp() {};

      ~HybridAutomatonComp() {};

      void addAutomata(HybridAutomaton<Number, State_t<Number, Number>>* automata) { mAutomatas.insert(automata); }
  };
}

#include "HybridAutomatonComp.tpp"