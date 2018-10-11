#pragma once

#include "Decomposition.h"
#include "../HybridAutomaton.h"
#include "../Location.h"
#include "../../../representations/types.h"
#include "../../../util/logging/Logger.h"
#include <carl/util/Singleton.h>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>


namespace hypro
{
/**
 * DecisionEntity is a Singleton class providing decision procedures for choosing a suitable represenation
 */
template<typename Number>
class DecisionEntity : public carl::Singleton<DecisionEntity<Number>>
{
  friend carl::Singleton<DecisionEntity<Number>>;

  public:
    /**
    * decomposed the given space into a set of set of variables. Each of the variable sets indicate
    * dependent variables
    */
    Decomposition getSubspaceDecomposition(const HybridAutomaton<Number> &automaton);
    bool checkDecomposed(const HybridAutomaton<Number> &automaton);
    std::pair<HybridAutomaton<Number>,Decomposition> decomposeAutomaton(HybridAutomaton<Number> &automaton);

    void addEdgesForLinTrafo(matrix_t<Number> linTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph);
    void addEdgesForAffineTrafo(matrix_t<Number> affineTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph);
    void addEdgesForCondition(Condition<Number> condition, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph);

    void printDecomposition(const Decomposition& decomposition);

  	bool isTimedAutomaton(const HybridAutomaton<Number> &ha);

  	bool isTimedLocation(const Location<Number> &loc);

    bool isTimedSubspace(const Location<Number> &loc, size_t index);
    bool isDiscreteSubspace(const Location<Number> &loc, size_t index);

};
} // hypro

#include "DecisionEntity.tpp"