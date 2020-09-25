#include "HybridAutomaton.h"

namespace hypro {

//Copy constructor
template <typename Number>
HybridAutomaton<Number>::HybridAutomaton( const HybridAutomaton<Number>& hybrid )
	: mLocations()
	, mGlobalBadStates( hybrid.getGlobalBadStates() )
	, mVariables( hybrid.getVariables() ) {
	// mappings to update nested datastructures (transitions sets of locations and source/target locations of transitions).
	std::map<const Location<Number>*, std::size_t> locationMapping;  // maps to position in new vector.
	std::map<Transition<Number>*, std::size_t> transitionMapping;	// maps to position in new vector.

	// create real copies of the locations
	for ( const auto l : hybrid.getLocations() ) {
		Location<Number> tmp = Location<Number>( *l );
		StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( l );
		if ( !stoLoc ) {
			mLocations.emplace_back( std::make_unique<Location<Number>>( tmp ) );
		} else {
			mLocations.emplace_back( std::make_unique<StochasticLocation<Number>>( StochasticLocation<Number>( *( stoLoc ) ) ) );
		}
		locationMapping[l] = mLocations.size() - 1;
		assert( tmp.hash() == l->hash() );
	}

	//update locations of transitions and transitions of locations
	for ( auto& l : mLocations ) {
		for ( auto& t : l->rGetTransitions() ) {
			// verify that the source of the location already corresponds to the new location.
			assert( t->getSource() == l.get() );

			// the target is updated to the new location.
			for ( auto& target : mLocations ) {
				if ( target->hash() == t->getTarget()->hash() ) {
					t->setTarget( target.get() );
				}
			}
		}
	}

	// get correct location pointer for initial states.
	for ( auto& otherInitial : hybrid.getInitialStates() ) {
		auto copy = otherInitial.second;
		// update location
		this->addInitialState( mLocations[locationMapping[otherInitial.first]].get(), copy );
	}

	for ( auto& otherBad : hybrid.getLocalBadStates() ) {
		auto copy = otherBad.second;
		// update location
		this->addLocalBadState( mLocations[locationMapping[otherBad.first]].get(), copy );
	}

#ifdef HYPRO_LOGGING
	DEBUG( "hypro.datastructures", "Hybrid automaton initial states after COPY construction." );
	for ( const auto& iPair : mInitialStates ) {
		DEBUG( "hypro.datastructures", "Initial state in loc " << iPair.first->getName() );
	}
#endif
}

/*
//Move constructor
template<typename Number>
HybridAutomaton<Number>::HybridAutomaton(HybridAutomaton<Number>&& hybrid)
	:
	mLocations(),
	mTransitions(),
	mGlobalBadStates(hybrid.getGlobalBadStates()),
	mVariables(hybrid.getVariables())
 {
	 std::cout << "Move construct hybrid automaton" << std::endl;
// mappings to update nested datastructures (transitions sets of locations and source/target locations of transitions).
	std::map<const Location<Number>*, std::size_t> locationMapping; // maps to position in new vector.
	std::map<Transition<Number>*, std::size_t> transitionMapping; // maps to position in new vector.

	// create real copies of the locations
	for(auto l : hybrid.getLocations()){
		Location<Number> tmp = Location<Number>(*l);
		tmp.setTransitions(std::vector<Transition<Number>*>());
    	mLocations.emplace_back(std::make_unique<Location<Number>>(tmp));
		locationMapping[l] = mLocations.size() - 1;
		assert(tmp.hash() == l->hash());
   	}
	// create copies of transitions
	for(auto& t : hybrid.getTransitions()){
		mTransitions.emplace_back(std::make_unique<Transition<Number>>(Transition<Number>(*t)));
		transitionMapping[t] = mTransitions.size() - 1;
	}

	//update locations of transitions and transitions of locations
	for(auto l : hybrid.getLocations()) {
		// only update transitions which are assigned to locations.
		for(auto t : l->getTransitions()) {

			// update transitions inside location
			mLocations[locationMapping[l]]->addTransition(mTransitions[transitionMapping[t]].get());

			// update source location.
			assert(t->getSource() == l);
			mTransitions[transitionMapping[t]]->setSource(mLocations[locationMapping[l]].get());

			// update correct target.
			mTransitions[transitionMapping[t]]->setTarget(mLocations[locationMapping[t->getTarget()]].get());
		}
	}

	// get correct location pointer for initial states.
	for(auto& otherInitial : hybrid.getInitialStates()) {
		auto copy = otherInitial.second;
		// update location
		this->addInitialState(mLocations[locationMapping[otherInitial.first]].get(), copy);
	}

	for(auto& otherBad : hybrid.getLocalBadStates()) {
		auto copy = otherBad.second;
		// update location
		this->addLocalBadState(mLocations[locationMapping[otherBad.first]].get(), copy);
	}

	DEBUG("hypro.datastructures","Hybrid automaton initial states after MOVE construction.");
	for(const auto& iPair : mInitialStates) {
		DEBUG("hypro.datastructures","Initial state in loc " << iPair.first->getName());
	}
}
*/

//Copy assignment
template <typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=( const HybridAutomaton<Number>& rhs ) {
	if ( this != &rhs ) {
		auto copy{rhs};
		*this = std::move( copy );
	}
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
		for ( auto tra : loc->getTransitions() ) {
			std::for_each( tra->getLabels().begin(), tra->getLabels().end(), [&labels]( auto l ) { labels.emplace( l ); } );
		}
	}
	return labels;
}

template <typename Number>
const std::unique_ptr<Location<Number>>& HybridAutomaton<Number>::addLocation( const Location<Number>& location ) {
	try{
		// std::cout<<"try transform Location to StochasticLocation!"<<std::endl;
		auto stoLoc = dynamic_cast<const StochasticLocation<Number>&>( location );
		// std::cout<<"nothing wrong!"<<std::endl;
		return this->addLocation( std::move( std::make_unique<StochasticLocation<Number>>( stoLoc ) ) );
	}catch(const std::bad_cast& re){
		std::cout<<"wrong with message: " << re.what()<<std::endl;
		return this->addLocation( std::move( std::make_unique<Location<Number>>( location ) ) );
	}
	// if ( stoLoc != std::bad_cast ) {
	// 	return this->addLocation( std::move( std::make_unique<Location<Number>>( location ) ) );
	// } else {
	// 	return this->addLocation( std::move( std::make_unique<StochasticLocation<Number>>( stoLoc ) ) );
	// }
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
void HybridAutomaton<Number>::reduce() {
	// TODO rewrite
	assert( false && "NOT IMPLEMENTED." );
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
	std::stringstream out;
	out << "#Locations: " << mLocations.size() << std::endl;

	return out.str();
}

template <typename Number>
HybridAutomaton<Number> operator||( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs ) {
	HybridAutomaton<Number> ha;
	using variableVector = std::vector<std::string>;  /// Vector of variables
	const variableVector& lhsVar = lhs.getVariables();
	const variableVector& rhsVar = rhs.getVariables();
	std::map<unsigned, std::pair<unsigned, unsigned>> sharedVars;

	variableVector haVar;
	variableVector::size_type i = 0;
	variableVector::size_type j = 0;
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

	for ( const auto& locLhs : lhs.getLocations() ) {
		for ( const auto& locRhs : rhs.getLocations() ) {
			std::unique_ptr<Location<Number>> loc = parallelCompose( locLhs, locRhs, lhsVar, rhsVar, haVar );
			ha.addLocation( std::move( loc ) );
		}
	}

	//build transisitons
	std::set<Label> lhsLabels = lhs.getLabels();
	std::set<Label> rhsLabels = rhs.getLabels();
	for ( const auto& lhsT : lhs.getTransitions() ) {
		for ( const auto& rhsT : rhs.getTransitions() ) {
			std::unique_ptr<Transition<Number>> t = parallelCompose( lhsT.get(), rhsT.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
			if ( t ) {
				ha.addTransition( std::move( t ) );
				( t->getSource() )->addTransition( t.get() );
			}
		}
	}

	// non-synchronizing transitions in each component
	// fix rhs first
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

				std::unique_ptr<Transition<Number>> t = parallelCompose( lhsT.get(), tmp.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( t.get() );
				}
			}
		}
	}
	// fix lhs
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

				std::unique_ptr<Transition<Number>> t = parallelCompose( tmp.get(), rhsT.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( t.get() );
				}
			}
		}
	}

	// set initial states
	for ( const auto& initialStateLhs : lhs.getInitialStates() ) {
		for ( const auto& initialStateRhs : rhs.getInitialStates() ) {
			FATAL( "hypro", "WARNING: parallel composition of initial states not implemented yet." );
			assert( false );
		}
	}

	//localBadstates
	//globalBAdstates

	// remove non-reachable locations and transitions.
	ha.reduce();

	return ha;
}

}  // namespace hypro
