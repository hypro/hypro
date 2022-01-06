#pragma once

#include "../../../representations/types.h"
#include "../../../types.h"
#include "../../../util/logging/Logger.h"
#include "../HybridAutomaton.h"
#include "../Location.h"
#include "../flow/operations.h"
#include "Decomposition.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <carl/util/Singleton.h>

namespace hypro {
/**
 * DecisionEntity is a Singleton class providing decision procedures for choosing a suitable represenation
 */
template <typename Number>
class DecisionEntity : public carl::Singleton<DecisionEntity<Number>> {
	friend carl::Singleton<DecisionEntity<Number>>;

  public:
	representation_name getRepresentationForAutomaton( const HybridAutomaton<Number>& ha );
	representation_name getRepresentationForLocation( const Location<Number>& loc );
	representation_name getRepresentationForSubspace( const Location<Number>& loc, size_t index );
	/**
	 * decomposed the given space into a set of set of variables. Each of the variable sets indicate
	 * dependent variables
	 */
	Decomposition getSubspaceDecomposition( const HybridAutomaton<Number>& automaton );
	bool checkDecomposed( const HybridAutomaton<Number>& automaton );
	std::pair<HybridAutomaton<Number>, Decomposition> decomposeAutomaton( const HybridAutomaton<Number>& automaton );

	void addEdgesForLinTrafo( matrix_t<Number> linTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph );
	void addEdgesForAffineTrafo( matrix_t<Number> affineTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph );
	void addEdgesForCondition( Condition<Number> condition, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph );
	void addEdgesForRectTrafo( const std::vector<carl::Interval<Number>>& intervals, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph );
	void addEdgesForRectMap( const std::map<carl::Variable, carl::Interval<Number>>& map, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph );

	void printDecomposition( const Decomposition& decomposition );

	bool isTimedAutomaton( const HybridAutomaton<Number>& ha );
	bool isRectangularAutomaton( const HybridAutomaton<Number>& ha );

	bool isTimedLocation( const Location<Number>& loc );
	bool isRectangularLocation( const Location<Number>& loc );

	bool isTimedSubspace( const Location<Number>& loc, size_t index );
	bool isRectangularSubspace( const Location<Number>& loc, size_t index );
	bool isDiscreteSubspace( const Location<Number>& loc, size_t index );
};
}  // namespace hypro

#include "DecisionEntity.tpp"
