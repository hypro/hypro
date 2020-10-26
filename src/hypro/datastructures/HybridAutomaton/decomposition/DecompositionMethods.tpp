#include "DecompositionMethods.h"

namespace hypro {
template <typename Number>
representation_name getRepresentationForSubspace( const Location<Number> &loc, size_t index ) {
	// in the beginning we assume it is a timed automaton
	bool isTimed = isTimedSubspace( loc, index );

	TRACE( "hypro.decisionEntity", "Is Timed subspace? " << isTimed );
	if ( isTimed ) {
		return representation_name::difference_bounds;
	}
	return representation_name::UNDEF;
}

template <typename Number>
representation_name getRepresentationForAutomaton( const HybridAutomaton<Number> &ha ) {
	// in the beginning we assume it is a timed automaton
	bool isTimed = isTimedAutomaton( ha );

	TRACE( "hypro.decisionEntity", "Is Timed automaton? " << isTimed );
	if ( isTimed ) {
		return representation_name::difference_bounds;
	}
	return representation_name::UNDEF;
}

template <typename Number>
representation_name getRepresentationForLocation( const Location<Number> &loc ) {
	// in the beginning we assume it is a timed automaton
	bool isTimed = isTimedLocation( loc );

	TRACE( "hypro.decisionEntity", "Is Timed location? " << isTimed );
	if ( isTimed ) {
		return representation_name::difference_bounds;
	}
	return representation_name::UNDEF;
}

template <typename Number>
bool isDiscreteSubspace( const Location<Number> &loc, size_t index ) {
	assert( index < loc.getNumberSubspaces() );
	if ( loc.getFlowTypes()[ index ] == DynamicType::rectangular ) {
		return false;
	}
	return loc.getLinearFlow( index ).isDiscrete();
}

template <typename Number>
bool isTimedSubspace( const Location<Number> &loc, size_t index ) {
	assert( index < loc.getNumberSubspaces() );
	TRACE( "hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index );
	if ( loc.getFlowTypes()[ index ] == DynamicType::rectangular ) {
		return false;
	}	
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

	for ( const auto &transition : loc.getTransitions() ) {
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
bool isRectangularSubspace( const Location<Number> &loc, size_t index ) {
	assert( index < loc.getNumberSubspaces() );
	TRACE( "hypro.decisionEntity", "Investigating " << loc.getName() << ", subspace " << index );
	if ( loc.getFlowTypes()[ index ] != DynamicType::rectangular ) {
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

	for ( const auto &transition : loc.getTransitions() ) {
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
bool isTimedLocation( const Location<Number> &loc ) {
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

	for ( const auto &transition : loc.getTransitions() ) {
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
bool isRectangularLocation( const Location<Number> &loc ) {
	for ( size_t i = 0; i < loc.getNumberFlow(); i++ ) {
		if ( !isRectangularSubspace( loc, i ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number>
bool isTimedAutomaton( const HybridAutomaton<Number> &ha ) {
	return std::all_of( ha.getLocations().begin(), ha.getLocations().end(), []( auto locPtr ) { return isTimedLocation( *locPtr ); } );
}

template <typename Number>
bool isRectangularAutomaton( const HybridAutomaton<Number> &ha ) {
	return std::all_of( ha.getLocations().begin(), ha.getLocations().end(), []( auto locPtr ) { return isRectangularLocation( *locPtr ); } );
}

template <typename Number>
bool checkDecomposed( const HybridAutomaton<Number> &automaton ) {
	for ( const auto &[locPtr, condition] : automaton.getInitialStates() ) {
		if ( condition.size() > 1 ) {
			return true;
		}
	}
	return false;
}

namespace detail {

template <typename Number>
void addEdgesForAffineTrafo( matrix_t<Number> affineTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph ) {
	matrix_t<Number> tmp( affineTrafo );
	// we do not consider the constant part of the trafo
	tmp.conservativeResize( tmp.rows() - 1, tmp.cols() - 1 );

	addEdgesForLinTrafo( tmp, graph );
}

template <typename Number>
void addEdgesForLinTrafo( matrix_t<Number> linTrafo, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph ) {
	for ( Eigen::Index i = 0; i < linTrafo.rows(); i++ ) {
		for ( Eigen::Index j = 0; j < linTrafo.cols(); j++ ) {
			if ( linTrafo( i, j ) != 0 ) {
				boost::add_edge( i, j, graph );
			}
		}
	}
}

template <typename Number>
void addEdgesForRectTrafo( const std::vector<carl::Interval<Number>> &intervals, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph ) {
	for ( size_t i = 0; i < intervals.size(); i++ ) {
		for ( size_t j = 0; j < intervals.size(); j++ ) {
			if ( i != j && intervals[i] != carl::Interval<Number>::emptyInterval() && intervals[j] != carl::Interval<Number>::emptyInterval() ) {
				boost::add_edge( i, j, graph );
			}
		}
	}
}

template <typename Number>
void addEdgesForRectMap( const std::map<carl::Variable, carl::Interval<Number>> &map, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph ) {
	auto &vpool = VariablePool::getInstance();
	for ( const auto &keyValPair1 : map ) {
		for ( const auto &keyValPair2 : map ) {
			if ( keyValPair1.first != keyValPair2.first ) {
				boost::add_edge( vpool.id( keyValPair1.first ), vpool.id( keyValPair2.first ), graph );
			}
		}
	}
}

template <typename Number>
void addEdgesForCondition( const Condition<Number> &condition, boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> &graph ) {
	if ( !( condition.size() > 0 ) ) {
		//empty condition (e.g. location with no invariant) --> do nothing
		return;
	}
	matrix_t<Number> tmp( condition.getMatrix() );

	for ( Eigen::Index i = 0; i < tmp.rows(); i++ ) {
		//pairwise comparison of the row entries
		for ( Eigen::Index j = 0; j < tmp.cols(); j++ ) {
			for ( Eigen::Index k = 0; k < tmp.cols(); k++ ) {
				//Example:
				// row i: 0,0,2,0,0,-4
				//            j      k
				// => j and k are dependent
				if ( tmp( i, j ) != 0 && tmp( i, k ) != 0 ) {
					boost::add_edge( j, k, graph );
				}
			}
		}
	}
}

}  // namespace detail

template <typename Number>
std::vector<std::vector<std::size_t>> getSubspacePartition( const HybridAutomaton<Number> &automaton ) {
	if ( checkDecomposed( automaton ) ) {
		// return empty decomposition
		return std::vector<std::vector<std::size_t>>();
	}
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
	Graph G( automaton.dimension() );

	//check flow and invariant of locations
	for ( auto locPtr : automaton.getLocations() ) {
		// Automaton is not decomposed so every location should have exactly one flow
		assert( locPtr->getNumberSubspaces() == 1 && "Subspace decomposition called on decomposed automaton" );
		switch ( locPtr->getFlowTypes()[ 0 ] ) {
			case DynamicType::discrete:
				[[fallthrough]];
			case DynamicType::timed:
				[[fallthrough]];
			case DynamicType::singular:
				[[fallthrough]];
			case DynamicType::affine:
				[[fallthrough]];
			case DynamicType::linear:
				detail::addEdgesForAffineTrafo( locPtr->getLinearFlow().getFlowMatrix(), G );
				break;
			case DynamicType::rectangular:
				detail::addEdgesForRectMap( locPtr->getRectangularFlow().getFlowIntervals(), G );
				break;
			default:
				assert( false && "Decompososition for flow type " locPtr->getFlowTypes()[ i ] << " not implemented yet." );
				break;
		}
		detail::addEdgesForCondition( locPtr->getInvariant(), G );
	}

	//check reset and guards of transitions
	for ( const auto &transition : automaton.getTransitions() ) {
		detail::addEdgesForLinTrafo( transition->getReset().getMatrix(), G );
		detail::addEdgesForRectTrafo( transition->getReset().getIntervals(), G );
		detail::addEdgesForCondition( transition->getGuard(), G );
	}

	//check local bad states
	for ( const auto &[locPtr, condition] : automaton.getLocalBadStates() ) {
		detail::addEdgesForCondition( condition, G );
	}
	//check global bad states
	for ( const auto &condition : automaton.getGlobalBadStates() ) {
		detail::addEdgesForCondition( condition, G );
	}

	std::vector<int> component( num_vertices( G ) );
	int num = boost::connected_components( G, &component[0] );
	// components now holds an array. It has one entry for each variable specifying its component
	// we parse this to a vector of vectors. each vector contains the variable indices for one component
	// and can consequently can be given to project.
	std::vector<std::vector<size_t>> res( num );
	std::vector<size_t>::size_type i;
	for ( i = 0; i != component.size(); i++ ) {
		res[component[i]].push_back( i );
	}
	return res;
}

template <typename Number>
std::pair<HybridAutomaton<Number>, Decomposition> decomposeAutomaton( const HybridAutomaton<Number> &automaton ) {
	// compute decomposition
	auto partition = getSubspacePartition( automaton );

	// Todo: What if partition.size() == 0? In that case decomposition must have been called twice
	if ( partition.size() == 0 ) {
		// decomposing failed/was already done(0-case)
		return std::make_pair( automaton, Decomposition() );
	}
	TRACE( "hypro.decisionEntity", "Automaton before decomposition: " << automaton );
	auto automatonCopy = automaton;
	automatonCopy.decompose( partition );
	Decomposition res;
	res.subspaces = partition;
	res.subspaceTypes = refineSubspaceDynamicTypes( automatonCopy );

	TRACE( "hypro.decisionEntity", "Automaton after decomposition: " << automatonCopy );
	return std::make_pair( automatonCopy, res );
}

template <typename Number>
std::vector<DynamicType> refineSubspaceDynamicTypes( const HybridAutomaton<Number>& automaton ) {
	std::vector<DynamicType> subspaceTypes( automaton.getLocations()[0]->getNumberSubspaces(), DynamicType::undefined );
	// Check for every location which dynamics it has in the subspace. Combine them

#ifndef NDEBUG
	// Assume that every location is decomposed in the same number of subspaces, as is done by the decomposeAutomaton function
	for( auto& loc : automaton.getLocations() ) {
		assuert( loc->getNumberSubspaces() == subspaceTypes.size() );
	}
#endif
	for ( std::size_t subspaceIndex = 0; subspaceIndex < subspaceTypes.size(); ++subspaceIndex ) {
		for ( auto & loc : automaton.getLocations() ) {
			switch ( subspaceTypes[ subspaceIndex ] ) {
				case DynamicType::undefined:
					if ( isDiscreteSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::discrete;
					} else if ( isTimedSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::timed;
					//} else if ( isSingularSubspace( *loc, subspaceIndex ) ) {
					//	subspaceTypes[ subspaceIndex ] = DynamicType::singular;
					} else if ( isRectangularSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::rectangular;
					} else {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					}
					break;
				case DynamicType::discrete:
					if ( isDiscreteSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::discrete;
					} else if ( isTimedSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::timed;
					//} else if ( isSingularSubspace( *loc, subspaceIndex ) ) {
					//	subspaceTypes[ subspaceIndex ] = DynamicType::singular;
					} else if ( isRectangularSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					} else {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					}
					break;
				case DynamicType::timed:
					if ( isDiscreteSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::timed;
					} else if ( isTimedSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::timed;
					//} else if ( isSingularSubspace( *loc, subspaceIndex ) ) {
					//	subspaceTypes[ subspaceIndex ] = DynamicType::singular;
					} else if ( isRectangularSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					} else {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					}
					break;
				case DynamicType::singular:
					if ( isDiscreteSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::singular;
					} else if ( isTimedSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::singular;
					//} else if ( isSingularSubspace( *loc, subspaceIndex ) ) {
					//	subspaceTypes[ subspaceIndex ] = DynamicType::singular;
					} else if ( isRectangularSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					} else {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					}
					break;
				case DynamicType::rectangular:
					if ( isDiscreteSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					} else if ( isTimedSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					//} else if ( isSingularSubspace( *loc, subspaceIndex ) ) {
					//	subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					} else if ( isRectangularSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::rectangular;
					} else {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					}
					break;
				case DynamicType::affine:
					[[fallthrough]];
				case DynamicType::linear:
					if ( isDiscreteSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					} else if ( isTimedSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					//} else if ( isSingularSubspace( *loc, subspaceIndex ) ) {
					//	subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					} else if ( isRectangularSubspace( *loc, subspaceIndex ) ) {
						subspaceTypes[ subspaceIndex ] = DynamicType::mixed;
					} else {
						subspaceTypes[ subspaceIndex ] = DynamicType::linear;
					}
					break;
				case DynamicType::mixed:
					break;
			}
		}
		assert( subspaceTypes[ subspaceIndex ] != DynamicType::undefined );
	}
	return subspaceTypes;
}



}  // namespace hypro
