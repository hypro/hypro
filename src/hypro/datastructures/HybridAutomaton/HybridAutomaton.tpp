#include "HybridAutomaton.h"

#include <algorithm>

namespace hypro {

//Copy constructor
template <typename Number>
HybridAutomaton<Number>::HybridAutomaton( const HybridAutomaton<Number>& hybrid )
	: mLocations()
	, mInitialStates()
	, mLocalBadStates()
	, mGlobalBadStates( hybrid.getGlobalBadStates() )
	, mVariables( hybrid.getVariables() ) {
	// mappings to update nested datastructures (transitions sets of locations and source/target locations of transitions).
	std::map<const Location<Number>*, Location<Number>*> locationMapping;  // maps old locations to position in new vector.

	// create real copies of the locations
	for ( Location<Number>* l : hybrid.getLocations() ) {
		Location<Number>* tmp = this->createLocation( l );
		TRACE( "hypro.datastructures", "Add location-Mapping entry " << l << " -> " << tmp );
		locationMapping[l] = tmp;
		assert( tmp->getTransitions().size() == l->getTransitions().size() );
		assert( std::all_of( tmp->getTransitions().begin(), tmp->getTransitions().end(), [tmp]( const auto& t ) { return t.get()->getSource() == tmp; } ) );
		assert( *tmp == *mLocations.back().get() );
		TRACE( "hypro.datastructures", "Location after copy: " << *tmp << " VS original: " << *l );
	}

	//update locations of transitions and transitions of locations
	for ( auto& l : mLocations ) {
		for ( auto& t : l.get()->rGetTransitions() ) {
			// verify that the source of the location already corresponds to the new location.
			assert( t.get()->getSource() == l.get() );
			// the target is updated to the new location.
			assert( t.get()->getTarget() != nullptr );
			TRACE( "hypro.datastructures", "Check if target @" << t.get()->getTarget() << ", which is \n"
															   << *t.get()->getTarget() << "\ncan be found in location mapping." );
			assert( locationMapping.find( t.get()->getTarget() ) != locationMapping.end() );
			t.get()->setTarget( locationMapping[t.get()->getTarget()] );
		}
		TRACE( "hypro.datastructures", "Location after transition update: " << *l.get() );
	}
	assert( std::all_of( locationMapping.begin(), locationMapping.end(), []( const auto& p ) {
		TRACE( "hypro.datastructures", "Compare " << *p.second << "\nand\n"
												  << *p.first );
		return p.second->getTransitions().size() == p.first->getTransitions().size();
	} ) );
	assert( is_equal( this->getLocations(), hybrid.getLocations() ) );

	// get correct location pointer for initial states.
	for ( auto& otherInitial : hybrid.getInitialStates() ) {
		auto copy = otherInitial.second;
		// update location
		TRACE( "hypro.datastructures", "Other initial state with loc @" << otherInitial.first << " is at index " << locationMapping[otherInitial.first] );
		assert( locationMapping.find( otherInitial.first ) != locationMapping.end() );
		mInitialStates[locationMapping[otherInitial.first]] = copy;
	}

	for ( auto& otherBad : hybrid.getLocalBadStates() ) {
		auto copy = otherBad.second;
		// update location
		this->addLocalBadState( locationMapping[otherBad.first], copy );
	}
	TRACE( "hypro.datastructures", "After copy, original: \n"
										 << hybrid << "\n copy: \n"
										 << *this );
	assert( *this == hybrid );
}

//Copy assignment
template <typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=( const HybridAutomaton<Number>& rhs ) {
	if ( this != &rhs ) {
		auto copy{ rhs };
		*this = std::move( copy );
	}
	assert( *this == rhs );
	return *this;
}

//Move Assignment
template <typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=( HybridAutomaton<Number>&& rhs ) {
	if ( this != &rhs ) {
		mLocations = std::move( rhs.mLocations );
		//Copy the rest
		mInitialStates = rhs.getInitialStates();
		mLocalBadStates = rhs.getLocalBadStates();
		mGlobalBadStates = rhs.getGlobalBadStates();
		mVariables = rhs.getVariables();
	}
	return *this;
}

template <typename Number>
std::vector<Location<Number>*> HybridAutomaton<Number>::getLocations() const {
	std::vector<Location<Number>*> res;
	for ( const auto& l : mLocations ) {
		res.emplace_back( l.get() );
	}
	return res;
}

template <typename Number>
Location<Number>* HybridAutomaton<Number>::getLocation( const std::size_t hash ) const {
	for ( const auto& loc : mLocations ) {
		assert( loc != nullptr );
		if ( loc->hash() == hash ) {
			return loc.get();
		}
	}
	return nullptr;
}

template <typename Number>
Location<Number>* HybridAutomaton<Number>::getLocation( const std::string& name ) const {
	for ( const auto& loc : mLocations ) {
		assert( loc != nullptr );
		if ( loc->getName() == name ) {
			return loc.get();
		}
	}
	return nullptr;
}

template <typename Number>
std::vector<Transition<Number>*> HybridAutomaton<Number>::getTransitions() const {
	std::vector<Transition<Number>*> res;
	for ( const auto& loc : mLocations ) {
		for ( const auto& tPtr : loc->getTransitions() ) {
			res.emplace_back( tPtr.get() );
		}
	}
	return res;
}

template <typename Number>
unsigned HybridAutomaton<Number>::dimension() const {
	if ( mInitialStates.empty() ) return 0;

	return ( mInitialStates.begin()->first->dimension() );
}

template <typename Number>
const std::set<Label> HybridAutomaton<Number>::getLabels() const {
	std::set<Label> labels;
	for ( const auto& loc : mLocations ) {
		for ( auto& tra : loc->getTransitions() ) {
			std::for_each( tra->getLabels().begin(), tra->getLabels().end(), [&labels]( auto l ) { labels.emplace( l ); } );
		}
	}
	return labels;
}

template <typename Number>
const std::unique_ptr<Location<Number>>& HybridAutomaton<Number>::addLocation( const Location<Number>& location ) {
	return this->addLocation( std::move( std::make_unique<Location<Number>>( location ) ) );
}

template <typename Number>
const std::unique_ptr<Location<Number>>& HybridAutomaton<Number>::addLocation( std::unique_ptr<Location<Number>>&& location ) {
	assert( location != nullptr );
	return mLocations.emplace_back( std::move( location ) );
}

template <typename Number>
void HybridAutomaton<Number>::addTransition( std::unique_ptr<Transition<Number>>&& transition ) {
	assert( transition != nullptr );
	for ( auto& l : mLocations ) {
		if ( l.get() == transition->getSource() ) {
			l.addTransition( std::move( transition ) );
			break;
		}
	}
}

template <typename Number>
Location<Number>* HybridAutomaton<Number>::createLocation() {
	return mLocations.emplace_back( std::make_unique<Location<Number>>( Location<Number>{} ) ).get();
}

template <typename Number>
Location<Number>* HybridAutomaton<Number>::createLocation( Location<Number>* original ) {
	return mLocations.emplace_back( std::make_unique<Location<Number>>( Location<Number>{ *original } ) ).get();
}

template <typename Number>
void HybridAutomaton<Number>::reduce() {
	std::set<Location<Number> const*> locations_found{};
	std::vector<Location<Number> const*> stack{};

	for ( auto& [loc_ptr, _] : getInitialStates() ) {
		stack.push_back( loc_ptr );
		locations_found.insert( loc_ptr );
	}

	while ( !stack.empty() ) {
		auto const* current_loc = stack.back();
		stack.pop_back();
		for ( auto& transition : current_loc->getTransitions() ) {
			if(locations_found.count( transition->getTarget() ) == 0){
				stack.push_back( transition->getTarget() );
				locations_found.insert( transition->getTarget() );
			}
		}
	}

	mLocations.erase( std::remove_if( mLocations.begin(), mLocations.end(), [&]( auto& loc ) {
						  return locations_found.count( loc.get() ) == 0;
					  } ),
					  mLocations.end() );
}

template <typename Number>
bool HybridAutomaton<Number>::isComposedOf( const HybridAutomaton<Number>& rhs ) const {
	// trivial case.
	if ( *this == rhs ) return true;

	// check variable sets
	for ( const auto& v : rhs.getVariables() ) {
		if ( std::find( mVariables.begin(), mVariables.end(), v ) == mVariables.end() ) {
			//std::cout << "Variable " << v << " not contained in this, return false" << std::endl;
			return false;
		}
	}

	// check locations:
	// try to find *exactly* one location, which matches - matching is defined by name, flow and invariant.
	for ( auto& locPtr : this->mLocations ) {
		bool foundOne = false;
		for ( auto& rhsLocPtr : rhs.getLocations() ) {
			if ( locPtr->isComposedOf( *rhsLocPtr, rhs.getVariables(), this->getVariables() ) ) {
				if ( foundOne ) {
					return false;
				}
				foundOne = true;
			}
		}
		if ( !foundOne ) {
			return false;
		}
	}

	return true;
}

template <typename Number>
std::string HybridAutomaton<Number>::getDotRepresentation() const {
	std::string res = "digraph {\n";

	for ( const auto& loc : mLocations ) {
		res += loc->getDotRepresentation( mVariables );
	}

	res += "}\n";

	return res;
}

template <typename Number>
void HybridAutomaton<Number>::decompose( const Decomposition& decomposition ) {
	// decompose locations (flow (affine trafo) and invariant(condition))
	for ( auto& location : mLocations ) {
		location->decompose( decomposition );
	}

	// decompose local bad states (condition)
	for ( auto it = mLocalBadStates.begin(); it != mLocalBadStates.end(); ++it ) {
		it->second.decompose( decomposition );
	}

	// decompose global bad states (conditions)
	for ( auto it = mGlobalBadStates.begin(); it != mGlobalBadStates.end(); ++it ) {
		it->decompose( decomposition );
	}
	// decompose intial states (state sets)
	DEBUG( "hypro.datastructures", "Decompose initial states." );
	for ( auto it = mInitialStates.begin(); it != mInitialStates.end(); ++it ) {
		it->second.decompose( decomposition );
	}
	DEBUG( "hypro.datastructures", "Decompose initial states done. Having " << mInitialStates.size() << " initial states." );
}

template <typename Number>
std::string HybridAutomaton<Number>::getStatistics() const {
	using namespace std::literals;

	size_t t_count = 0;
	for ( Location<Number>* loc : getLocations() ) {
		t_count += loc->getTransitions().size();
	}

	std::string result = "#Locations: "s + std::to_string( mLocations.size() ) + "\n"s + "#Transitions "s + std::to_string( t_count ) + "\n"s;
	return result;
}

template <typename Number>
HybridAutomaton<Number> operator||( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs ) {
	TRACE( "hypro.datastructures", "Parallel composition of " << lhs << "\n\n and \n\n"
															  << rhs );
	HybridAutomaton<Number> ha;
	using variableVector = std::vector<std::string>;  /// Vector of variables
	const variableVector& lhsVar = lhs.getVariables();
	const variableVector& rhsVar = rhs.getVariables();
	std::map<unsigned, std::pair<unsigned, unsigned>> sharedVars;

	variableVector haVar;
	variableVector::size_type i = 0;
	variableVector::size_type j = 0;
	TRACE( "hypro.datastructures", "Combine variable sets" );
	while ( i < lhsVar.size() && j < rhsVar.size() ) {
		if ( lhsVar.at( i ) == rhsVar.at( j ) ) {
			haVar.push_back( lhsVar[i] );
			i++;
			j++;
			continue;
		}
		if ( lhsVar.at( i ) < rhsVar.at( j ) ) {
			haVar.push_back( lhsVar[i] );
			i++;
			continue;
		}
		if ( lhsVar.at( i ) > rhsVar.at( j ) ) {
			haVar.push_back( rhsVar[j] );
			j++;
			continue;
		}
	}
	for ( ; i < lhsVar.size(); i++ ) {
		haVar.push_back( lhsVar[i] );
	}
	for ( ; j < rhsVar.size(); j++ ) {
		haVar.push_back( rhsVar[j] );
	}
	ha.setVariables( haVar );

	// find shared variables
	TRACE( "hypro.datastructures", "Find shared variables" );
	for ( std::size_t i = 0; i != haVar.size(); ++i ) {
		bool left = false;
		bool right = false;
		std::size_t l = 0;
		std::size_t r = 0;
		while ( l != lhsVar.size() ) {
			if ( lhsVar[l] == haVar[i] ) {
				left = true;
				break;
			}
			++l;
		}
		while ( r != rhsVar.size() ) {
			if ( rhsVar[r] == haVar[i] ) {
				right = true;
				break;
			}
			++r;
		}
		if ( left && right ) {
			//std::cout << "Shared var at " << i << " corresponds to (" << l << "," << r << ")" << std::endl;
			sharedVars[i] = std::make_pair( l, r );
		}
	}

	TRACE( "hypro.datastructures", "Combine locations" );
	for ( const auto& locLhs : lhs.getLocations() ) {
		for ( const auto& locRhs : rhs.getLocations() ) {
			std::unique_ptr<Location<Number>> loc = parallelCompose( locLhs, locRhs, lhsVar, rhsVar, haVar );
			TRACE( "hypro.datastructures", "Add combined location " << *loc );
			ha.addLocation( std::move( loc ) );
		}
	}

	TRACE( "hypro.datastructures", "Combine synchronized transitions" );
	std::set<Label> lhsLabels = lhs.getLabels();
	std::set<Label> rhsLabels = rhs.getLabels();
	for ( const auto& lhsT : lhs.getTransitions() ) {
		for ( const auto& rhsT : rhs.getTransitions() ) {
			std::unique_ptr<Transition<Number>> t = parallelCompose( lhsT, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
			if ( t ) {
				//ha.addTransition( std::move( t ) );
				( t->getSource() )->addTransition( std::move( t ) );
			}
		}
	}

	// non-synchronizing transitions in each component
	// fix rhs first
	TRACE( "hypro.datastructures", "Build non-synchronizing transitions for lhs, fix rhs" );
	for ( const auto& lhsT : lhs.getTransitions() ) {
		if ( lhsT->getLabels().empty() ) {
			for ( const auto& loc : rhs.getLocations() ) {
				std::unique_ptr<Transition<Number>> tmp = std::make_unique<Transition<Number>>( Transition<Number>( loc, loc ) );
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>( matrix_t<Number>::Identity( rhsVar.size(), rhsVar.size() ), vector_t<Number>::Zero( rhsVar.size() ) );
				if ( !sharedVars.empty() ) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					// Todo: iterate over rows, then over cols (only the ones which correspond to shared vars) and set the resets accordingly.

					for ( auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt ) {
						//std::cout << "update row " << shdIt->second.second << std::endl;
						for ( auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt ) {
							tmpReset.rGetMatrix()( shdIt->second.second, colIt->second.second ) = lhsT->getReset().getMatrix()( shdIt->second.first, colIt->second.first );
						}
						tmpReset.rGetVector()( shdIt->second.second ) = lhsT->getReset().getVector()( shdIt->second.first );
					}
				}

				tmp->setReset( tmpReset );
				tmp->setAggregation( lhsT->getAggregation() );

				std::unique_ptr<Transition<Number>> t = parallelCompose( lhsT, tmp.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					//ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( std::move( t ) );
				}
			}
		}
	}
	// fix lhs
	TRACE( "hypro.datastructures", "Build non-synchronizing transitions for rhs, fix lhs" );
	for ( const auto& rhsT : rhs.getTransitions() ) {
		if ( rhsT->getLabels().empty() ) {
			for ( const auto& loc : lhs.getLocations() ) {
				std::unique_ptr<Transition<Number>> tmp = std::make_unique<Transition<Number>>( Transition<Number>( loc, loc ) );
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>( matrix_t<Number>::Identity( lhsVar.size(), lhsVar.size() ), vector_t<Number>::Zero( lhsVar.size() ) );
				if ( !sharedVars.empty() ) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					for ( auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt ) {
						for ( auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt ) {
							tmpReset.rGetMatrix()( shdIt->second.first, colIt->second.first ) = rhsT->getReset().getMatrix()( shdIt->second.second, colIt->second.second );
						}
						tmpReset.rGetVector()( shdIt->second.first ) = rhsT->getReset().getVector()( shdIt->second.second );
					}
				}

				tmp->setReset( tmpReset );
				tmp->setAggregation( rhsT->getAggregation() );

				std::unique_ptr<Transition<Number>> t = parallelCompose( tmp.get(), rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					//ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( std::move( t ) );
				}
			}
		}
	}

	// set initial states
	TRACE( "hypro.datastructures", "Combine initial states (not yet implemented)" );
	for ( auto const& [loc_lhs, condition_lhs] : lhs.getInitialStates() ) {
		for ( auto const& [loc_rhs, condition_rhs] : rhs.getInitialStates() ) {

			// simply put constraints (rows) below each other, but reorder variables (columns) of both lhs and rhs to fit new order

			auto num_constraints_lhs = condition_lhs.getMatrix().rows();
			auto num_constraints_rhs = condition_rhs.getMatrix().rows();

			auto total_constraints = num_constraints_lhs + num_constraints_rhs;
			matrix_t<Number> constraints{total_constraints, haVar.size() };

			Eigen::Index col = 0;
			for ( std::string const& variable : haVar ) {
				auto index_lhs = std::distance( lhsVar.begin(), std::find( lhsVar.begin(), lhsVar.end(), variable ) );
				auto index_rhs = std::distance( rhsVar.begin(), std::find( rhsVar.begin(), rhsVar.end(), variable ) );

				// put lhs part of column in at the top
				if(size_t(index_lhs) < lhsVar.size()) {
					constraints.col(col).head(num_constraints_lhs) = condition_lhs.getMatrix().col(index_lhs);
				}

				if(size_t(index_rhs) < rhsVar.size()) {
					constraints.col(col).tail(num_constraints_rhs) = condition_rhs.getMatrix().col(index_rhs);
				}
				col += 1;
			}

			vector_t<Number> constants{num_constraints_lhs + num_constraints_rhs};
			constants.head(num_constraints_lhs) = condition_lhs.getVector();
			constants.tail(num_constraints_rhs) = condition_rhs.getVector();

			std::string loc_name = loc_lhs->getName() + "_" + loc_rhs->getName();
			Location<Number> const* init_loc = ha.getLocation(loc_name);
			ha.addInitialState(init_loc, Condition{constraints, constants});
		}
	}

	//localBadstates
	//globalBAdstates

	// remove non-reachable locations and transitions.
	ha.reduce();

	return ha;
}

}  // namespace hypro
