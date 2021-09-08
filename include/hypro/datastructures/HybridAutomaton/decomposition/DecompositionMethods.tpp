#include "DecompositionMethods.h"

namespace hypro {
template <typename Number>
representation_name getRepresentationForSubspace( const Location<Number>& loc, size_t index ) {
	// in the beginning we assume it is a timed automaton
	bool isTimed = isTimedSubspace( loc, index );

	TRACE( "hypro.decisionEntity", "Is Timed subspace? " << isTimed );
	if ( isTimed ) {
		return representation_name::difference_bounds;
	}
	return representation_name::UNDEF;
}

template <typename Number>
representation_name getRepresentationForAutomaton( const HybridAutomaton<Number>& ha ) {
	// in the beginning we assume it is a timed automaton
	bool isTimed = isTimedAutomaton( ha );

	TRACE( "hypro.decisionEntity", "Is Timed automaton? " << isTimed );
	if ( isTimed ) {
		return representation_name::difference_bounds;
	}
	return representation_name::UNDEF;
}

template <typename Number>
representation_name getRepresentationForLocation( const Location<Number>& loc ) {
	// in the beginning we assume it is a timed automaton
	bool isTimed = isTimedLocation( loc );

	TRACE( "hypro.decisionEntity", "Is Timed location? " << isTimed );
	if ( isTimed ) {
		return representation_name::difference_bounds;
	}
	return representation_name::UNDEF;
}

template <typename Number>
bool isDiscreteSubspace( const Location<Number>& loc, size_t index ) {
	return loc.getLinearFlow( index ).isDiscrete() && loc.getRectangularFlow( index ).isDiscrete();
}

template <typename Number>
bool isTimedSubspace( const Location<Number>& loc, size_t index ) {
	TRACE( "hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index );
	// check if flow is of the form
	//	0 ... 0 1
	//  .........
	//	0 ... 0 1
	//  0 ....0 0

	if ( !( loc.getLinearFlow( index ) ).isTimed() ) {
		TRACE( "hypro.decisionEntity", "Flow is not timed." );
		return false;
	}

	// check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
	if ( loc.getInvariant().size() > 0 ) {
		if ( !loc.getInvariant().isAxisAligned( index ) ) {
			TRACE( "hypro.decisionEntity", "Invariant is not axis-aligned." );
			return false;
		}
	}

	for ( const auto& transition : loc.getTransitions() ) {
		TRACE( "hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() );

		// for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most

		if ( transition->getGuard().size() > 0 ) {
			if ( !transition->getGuard().isAxisAligned( index ) ) {
				TRACE( "hypro.decisionEntity", "Guard is not axis-aligned." );
				return false;
			}
		}

		// check if for each transition the reset function is of the form
		//
		//	0/1	 0  ...  0 | 0
		//	0  0/1 0 ... 0 | 0
		//	..................
		//  0 ...... 0 0/1 | 0
		if ( transition->getReset().size() > 0 ) {
			matrix_t<Number> reset = transition->getReset().getMatrix( index );
			for ( int i = 0; i < reset.rows(); i++ ) {
				matrix_t<Number> expected0 = matrix_t<Number>::Zero( 1, reset.cols() );
				matrix_t<Number> expected1 = matrix_t<Number>::Zero( 1, reset.cols() );
				expected1( 0, i ) = Number( 1.0 );
				if ( !( reset.row( i ) == expected0 || reset.row( i ) == expected1 ) ) {
					TRACE( "hypro.decisionEntitiy", "Reset matrix rows do not match." );
					return false;
				}
			}
		}

		if ( transition->getReset().size() > 0 ) {
			matrix_t<Number> reset = transition->getReset().getVector( index );
			if ( reset != matrix_t<Number>::Zero( reset.rows(), 1 ) ) {
				TRACE( "hypro.decisionEntitiy", "Reset vector rows do not reset to zero." );
				return false;
			}
		}
	}
	TRACE( "hypro.decisionEntitiy", "Is timed." );
	return true;
}

template <typename Number>
bool isRectangularSubspace( const Location<Number>& loc, size_t index ) {
	TRACE( "hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index );

	if ( !( loc.getLinearFlow( index ).hasNoFlow() && !loc.getRectangularFlow( index ).empty() ) ) {
		TRACE( "hypro.decisionEntity", "Flow is not rectangular." );
		return false;
	}

	// check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
	if ( loc.getInvariant().size() > 0 ) {
		if ( !loc.getInvariant().isAxisAligned( index ) ) {
			TRACE( "hypro.decisionEntity", "Invariant is not axis-aligned." );
			return false;
		}
	}

	for ( const auto& transition : loc.getTransitions() ) {
		TRACE( "hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() );

		// for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most

		if ( transition->getGuard().size() > 0 ) {
			if ( !transition->getGuard().isAxisAligned( index ) ) {
				TRACE( "hypro.decisionEntity", "Guard is not axis-aligned." );
				return false;
			}
		}

		// check if for each transition the reset function is of the form
		//
		//	0/1	 0  ...  0 | 0
		//	0  0/1 0 ... 0 | 0
		//	..................
		//  0 ...... 0 0/1 | 0
		if ( transition->getReset().size() > 0 ) {
			if ( !transition->getReset().getAffineReset( index ).isIdentity() ) {
				TRACE( "hypro.decisionEntity", "Reset is not interval-based." );
				return false;
			}
		}
	}
	TRACE( "hypro.decisionEntitiy", "Is rectangular." );
	return true;
}

template <typename Number>
bool isTimedLocation( const Location<Number>& loc ) {
	TRACE( "hypro.decisionEntity", "Investigating " << loc.getName() );
	// check if flow is of the form
	//	0 ... 0 1
	//  .........
	//	0 ... 0 1
	//  0 ....0 0
	for ( size_t i = 0; i < loc.getNumberFlow(); i++ ) {
		if ( !loc.getLinearFlow( i ).isTimed() ) {
			TRACE( "hypro.decisionEntity", "Flow is not timed." );
			return false;
		}
	}

	// check if the constraints of the invariant set only contain 0s and one entry 1/-1 at most
	if ( !loc.getInvariant().isAxisAligned() ) {
		TRACE( "hypro.decisionEntity", "Invariant is not axis-aligned." );
		return false;
	}

	for ( const auto& transition : loc.getTransitions() ) {
		TRACE( "hypro.decisionEntity", "Investigating " << transition->getSource()->getName() << " -> " << transition->getTarget()->getName() );

		// for each transitions check if the constraints of the guard set only only contain 0s and one entry 1/-1 at most
		if ( !transition->getGuard().isAxisAligned() ) {
			TRACE( "hypro.decisionEntity", "Guard is not axis-aligned." );
			return false;
		}

		// check if for each transition the reset function is of the form
		//
		//	0/1	 0  ...  0 | 0
		//	0  0/1 0 ... 0 | 0
		//	..................
		//  0 ...... 0 0/1 | 0
		for ( size_t i = 0; i < transition->getReset().size(); i++ ) {
			matrix_t<Number> reset = transition->getReset().getMatrix( i );
			for ( int i = 0; i < reset.rows(); i++ ) {
				matrix_t<Number> expected0 = matrix_t<Number>::Zero( 1, reset.cols() );
				matrix_t<Number> expected1 = matrix_t<Number>::Zero( 1, reset.cols() );
				expected1( 0, i ) = Number( 1.0 );
				if ( !( reset.row( i ) == expected0 || reset.row( i ) == expected1 ) ) {
					TRACE( "hypro.decisionEntity", "Reset is not timed." );
					return false;
				}
			}
		}

		for ( size_t i = 0; i < transition->getReset().size(); i++ ) {
			matrix_t<Number> reset = transition->getReset().getVector( i );
			if ( reset != matrix_t<Number>::Zero( reset.rows(), 1 ) ) {
				TRACE( "hypro.decisionEntity", "Reset is not timed." );
				return false;
			}
		}
	}

	return true;
}

template <typename Number>
bool isRectangularLocation( const Location<Number>& loc ) {
	for ( size_t i = 0; i < loc.getNumberFlow(); i++ ) {
		if ( !isRectangularSubspace( loc, i ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number>
bool isTimedAutomaton( const HybridAutomaton<Number>& ha ) {
	return std::all_of( ha.getLocations().begin(), ha.getLocations().end(), []( auto locPtr ) { return isTimedLocation( *locPtr ); } );
}

template <typename Number>
bool isRectangularAutomaton( const HybridAutomaton<Number>& ha ) {
	return std::all_of( ha.getLocations().begin(), ha.getLocations().end(), []( auto locPtr ) { return isRectangularLocation( *locPtr ); } );
}

template <typename Number>
bool checkDecomposed( const HybridAutomaton<Number>& automaton ) {
	for ( const auto& [locPtr, condition] : automaton.getInitialStates() ) {
		if ( condition.size() > 1 ) {
			return true;
		}
	}
	return false;
}

namespace detail {

template <typename Number>
void addEdgesForAffineTrafo( matrix_t<Number> affineTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph ) {
	matrix_t<Number> tmp( affineTrafo );
	// we do not consider the constant part of the trafo
	tmp.conservativeResize( tmp.rows() - 1, tmp.cols() - 1 );

	addEdgesForLinTrafo( tmp, graph );
}

template <typename Number>
void addEdgesForLinTrafo( matrix_t<Number> linTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph ) {
	for ( Eigen::Index i = 0; i < linTrafo.rows(); i++ ) {
		for ( Eigen::Index j = 0; j < linTrafo.cols(); j++ ) {
			if ( linTrafo( i, j ) != 0 ) {
				boost::add_edge( i, j, graph );
			}
		}
	}
}

template <typename Number>
void addEdgesForRectTrafo( const std::vector<carl::Interval<Number>>& intervals, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph ) {
	for ( size_t i = 0; i < intervals.size(); i++ ) {
		for ( size_t j = 0; j < intervals.size(); j++ ) {
			if ( i != j && intervals[i] != carl::Interval<Number>::emptyInterval() && intervals[j] != carl::Interval<Number>::emptyInterval() ) {
				boost::add_edge( i, j, graph );
			}
		}
	}
}

template <typename Number>
void addEdgesForRectMap( const std::map<carl::Variable, carl::Interval<Number>>& map, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph ) {
	auto& vpool = VariablePool::getInstance();
	for ( const auto& keyValPair1 : map ) {
		for ( const auto& keyValPair2 : map ) {
			if ( keyValPair1.first != keyValPair2.first ) {
				boost::add_edge( vpool.id( keyValPair1.first ), vpool.id( keyValPair2.first ), graph );
			}
		}
	}
}

template <typename Number>
void addEdgesForCondition( const Condition<Number>& condition, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>& graph ) {
	if ( !( condition.size() > 0 ) ) {
		// empty condition (e.g. location with no invariant) --> do nothing
		return;
	}
	matrix_t<Number> tmp( condition.getMatrix() );

	for ( Eigen::Index i = 0; i < tmp.rows(); i++ ) {
		// pairwise comparison of the row entries
		for ( Eigen::Index j = 0; j < tmp.cols(); j++ ) {
			for ( Eigen::Index k = 0; k < tmp.cols(); k++ ) {
				// Example:
				//  row i: 0,0,2,0,0,-4
				//             j      k
				//  => j and k are dependent
				if ( tmp( i, j ) != 0 && tmp( i, k ) != 0 ) {
					boost::add_edge( j, k, graph );
				}
			}
		}
	}
}

}  // namespace detail

template <typename Number>
Decomposition getSubspaceDecomposition( const HybridAutomaton<Number>& automaton ) {
	if ( checkDecomposed( automaton ) ) {
		// return empty decomposition
		return Decomposition();
	}
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
	Graph G( automaton.dimension() - 1 );

	// check flow and invariant of locations
	for ( auto locPtr : automaton.getLocations() ) {
		for ( std::size_t i = 0; i < locPtr->getNumberFlow(); ++i ) {
			detail::addEdgesForAffineTrafo( locPtr->getLinearFlow( i ).getFlowMatrix(), G );
			detail::addEdgesForRectMap( locPtr->getRectangularFlow( i ).getFlowIntervals(), G );
		}
		// TODO: add further flow types
		detail::addEdgesForCondition( locPtr->getInvariant(), G );
	}

	// check reset and guards of transitions
	for ( const auto& transition : automaton.getTransitions() ) {
		detail::addEdgesForLinTrafo( transition->getReset().getMatrix(), G );
		detail::addEdgesForRectTrafo( transition->getReset().getIntervals(), G );
		detail::addEdgesForCondition( transition->getGuard(), G );
	}

	// check local bad states
	for ( const auto& [locPtr, condition] : automaton.getLocalBadStates() ) {
		detail::addEdgesForCondition( condition, G );
	}
	// check global bad states
	for ( const auto& condition : automaton.getGlobalBadStates() ) {
		detail::addEdgesForCondition( condition, G );
	}

	std::vector<int> component( num_vertices( G ) );
	int num = boost::connected_components( G, &component[0] );
	// components now holds an array. It has one entry for each variable specifying its component
	// we parse this to a vector of vectors. each vector contains the variable indices for one component
	// and can consequently can be given to project.
	Decomposition res;
	res.subspaces = std::vector<std::vector<size_t>>( num );
	res.subspaceTypes = std::vector<DynamicType>( num, DynamicType::undefined );
	std::vector<size_t>::size_type i;
	for ( i = 0; i != component.size(); i++ ) {
		res.subspaces[component[i]].push_back( i );
	}
	return res;
}

template <typename Number>
std::pair<HybridAutomaton<Number>, Decomposition> decomposeAutomaton( const HybridAutomaton<Number>& automaton ) {
	// compute decomposition
	Decomposition decomposition = getSubspaceDecomposition( automaton );

	if ( decomposition.subspaces.size() <= 1 ) {
		// decomposing failed/was already done(0-case) or decomposition is all variables (1 case)
		return std::make_pair( automaton, decomposition );
	}
	TRACE( "hypro.decisionEntity", "Automaton before decomposition: " << automaton );
	auto automatonCopy = automaton;
	automatonCopy.decompose( decomposition );
	TRACE( "hypro.decisionEntity", "Automaton after decomposition: " << automatonCopy );
	return std::make_pair( automatonCopy, decomposition );
}

}  // namespace hypro
