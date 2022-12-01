/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HybridAutomaton.h"

#include <algorithm>

namespace hypro {

// Copy constructor
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
		locationMapping[l] = tmp;
		assert( tmp->getTransitions().size() == l->getTransitions().size() );
		assert( std::all_of( tmp->getTransitions().begin(), tmp->getTransitions().end(), [tmp]( const auto& t ) { return t.get()->getSource() == tmp; } ) );
		assert( *tmp == *mLocations.back().get() );
		TRACE( "hypro.datastructures.hybridAutomaton", "Location after copy: " << *tmp << " VS original: " << *l );
	}

	// update locations of transitions and transitions of locations
	for ( auto& l : mLocations ) {
		for ( auto& t : l.get()->rGetTransitions() ) {
			// verify that the source of the location already corresponds to the new location.
			assert( t.get()->getSource() == l.get() );
			// the target is updated to the new location.
			assert( t.get()->getTarget() != nullptr );
			TRACE( "hypro.datastructures.hybridAutomaton", "Check if target @" << t.get()->getTarget() << ", which is \n"
																			   << *t.get()->getTarget() << "\ncan be found in location mapping." );
			assert( locationMapping.find( t.get()->getTarget() ) != locationMapping.end() );
			t.get()->setTarget( locationMapping[t.get()->getTarget()] );
		}
		TRACE( "hypro.datastructures.hybridAutomaton", "Location after transition update: " << *l.get() );
	}
	assert( std::all_of( locationMapping.begin(), locationMapping.end(), []( const auto& p ) {
		TRACE( "hypro.datastructures.hybridAutomaton", "Compare " << *p.second << "\nand\n"
																  << *p.first );
		return p.second->getTransitions().size() == p.first->getTransitions().size();
	} ) );
	assert( is_equal( this->getLocations(), hybrid.getLocations() ) );

	// get correct location pointer for initial states.
	for ( auto& otherInitial : hybrid.getInitialStates() ) {
		auto copy = otherInitial.second;
		// update location
		TRACE( "hypro.datastructures.hybridAutomaton", "Other initial state with loc @" << otherInitial.first << " is at index " << locationMapping[otherInitial.first] );
		assert( locationMapping.find( otherInitial.first ) != locationMapping.end() );
		mInitialStates[locationMapping[otherInitial.first]] = copy;
	}

	for ( auto& otherBad : hybrid.getLocalBadStates() ) {
		auto copy = otherBad.second;
		// update location
		this->addLocalBadStates( locationMapping[otherBad.first], copy );
	}
	TRACE( "hypro.datastructures.hybridAutomaton", "After copy, original: \n"
														 << hybrid << "\n copy: \n"
														 << *this );
	assert( *this == hybrid );
}

// Copy assignment
template <typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=( const HybridAutomaton<Number>& rhs ) {
	if ( this != &rhs ) {
		auto copy{ rhs };
		*this = std::move( copy );
	}
	assert( *this == rhs );
	return *this;
}

// Move Assignment
template <typename Number>
HybridAutomaton<Number>& HybridAutomaton<Number>::operator=( HybridAutomaton<Number>&& rhs ) {
	if ( this != &rhs ) {
#ifndef NDEBUG
		std::size_t oldLocationSize = rhs.getLocations().size();
#endif
		mLocations = std::move( rhs.mLocations );
		assert( mLocations.size() == oldLocationSize );
		// Copy the rest
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
Location<Number>* HybridAutomaton<Number>::getLocationByIndex( const std::size_t index ) const {
	return mLocations.at( index ).get();
}

template <typename Number>
long int HybridAutomaton<Number>::getLocationIndex( const Location<Number>* location ) const {
	long int res = -1;
	for ( long int idx = 0; idx < mLocations.size(); ++idx ) {
		if ( mLocations[idx].get() == location ) {
			return idx;
		}
	}
	return res;
}

template <typename Number>
std::vector<Transition<Location<Number>>*> HybridAutomaton<Number>::getTransitions() const {
	std::vector<Transition<Location<Number>>*> res;
	for ( const auto& loc : mLocations ) {
		for ( const auto& tPtr : loc->getTransitions() ) {
			res.emplace_back( tPtr.get() );
		}
	}
	return res;
}

template <typename Number>
unsigned HybridAutomaton<Number>::dimension() const {
	if ( !mInitialStates.empty() ) return mInitialStates.begin()->first->dimension();
	if ( !mLocations.empty() ) return mLocations.front()->dimension();
	return 0;
}

template <typename Number>
const typename HybridAutomaton<Number>::variableVector& HybridAutomaton<Number>::getVariables() const {
	if ( !mVariablesSet && mVariables.size() == 0 ) {
		auto dim = this->dimension();
		if ( this->dimension() > 0 ) {
			for ( int i = 0; i < dim; ++i ) {
				mVariables.push_back( "x" + std::to_string( i ) );
			}
		}
	}
	return mVariables;
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
	try {
		auto stoLoc = dynamic_cast<const StochasticLocation<Number>&>( location );
		return this->addLocation( std::move( std::make_unique<StochasticLocation<Number>>( stoLoc ) ) );
	} catch ( const std::bad_cast& re ) {
		std::cout << "wrong with message: " << re.what() << std::endl;
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
void HybridAutomaton<Number>::addTransition( std::unique_ptr<Transition<Location<Number>>>&& transition ) {
	assert( transition != nullptr );
	for ( auto& l : mLocations ) {
		if ( l.get() == transition->getSource() ) {
			l.addTransition( std::move( transition ) );
			break;
		}
	}
}

template <typename Number>
Location<Number>* HybridAutomaton<Number>::createLocation( const std::string& name ) {
	return mLocations.emplace_back( std::make_unique<Location<Number>>( Location<Number>{ name } ) ).get();
}

template <typename Number>
Location<Number>* HybridAutomaton<Number>::createLocation( Location<Number>* original ) {
	StochasticLocation<Number>* stoLoc = dynamic_cast<StochasticLocation<Number>*>( original );
	if ( !stoLoc ) {
		return mLocations.emplace_back( std::make_unique<Location<Number>>( Location<Number>{ *original } ) ).get();
	} else {
		return mLocations.emplace_back( std::make_unique<StochasticLocation<Number>>( StochasticLocation<Number>( *( stoLoc ) ) ) ).get();
	}
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
			if ( locations_found.count( transition->getTarget() ) == 0 ) {
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
void HybridAutomaton<Number>::decompose( const std::vector<std::vector<std::size_t>>& partition ) {
	// decompose locations (flow (affine trafo) and invariant(condition))
	for ( auto& location : mLocations ) {
		location->decompose( partition );
	}

	// decompose local bad states (condition)
	for ( auto it = mLocalBadStates.begin(); it != mLocalBadStates.end(); ++it ) {
		it->second.decompose( partition );
	}

	// decompose global bad states (conditions)
	for ( auto it = mGlobalBadStates.begin(); it != mGlobalBadStates.end(); ++it ) {
		it->decompose( partition );
	}
	// decompose intial states (state sets)
	DEBUG( "hypro.datastructures.hybridAutomaton", "Decompose initial states." );
	for ( auto it = mInitialStates.begin(); it != mInitialStates.end(); ++it ) {
		it->second.decompose( partition );
	}
	DEBUG( "hypro.datastructures.hybridAutomaton", "Decompose initial states done. Having " << mInitialStates.size() << " initial states." );
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
	TRACE( "hypro.datastructures.hybridAutomaton", "Parallel composition of " << lhs << "\n\n and \n\n"
																			  << rhs );
	HybridAutomaton<Number> ha;
	using variableVector = std::vector<std::string>;  /// Vector of variables
	const variableVector& lhsVar = lhs.getVariables();
	const variableVector& rhsVar = rhs.getVariables();
	std::map<unsigned, std::pair<unsigned, unsigned>> sharedVars;

	variableVector haVar;
	variableVector::size_type i = 0;
	variableVector::size_type j = 0;
	TRACE( "hypro.datastructures.hybridAutomaton", "Combine variable sets" );
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
	{
		std::stringstream ss;
		for ( const auto& v : haVar ) {
			ss << v << ", ";
		}
		TRACE( "hypro.datastructures.hybridAutomaton", "Resulting set of variables: " << ss.str() );
	}
	ha.setVariables( haVar );

	// find shared variables
	TRACE( "hypro.datastructures.hybridAutomaton", "Find shared variables" );
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
			TRACE( "hypro.datastructures.hybridAutomaton", "Shared var at " << i << " corresponds to original indices (" << l << "," << r << ")" );
			sharedVars[i] = std::make_pair( l, r );
		}
	}

	TRACE( "hypro.datastructures.hybridAutomaton", "Combine locations" );
	for ( const auto& locLhs : lhs.getLocations() ) {
		for ( const auto& locRhs : rhs.getLocations() ) {
			std::unique_ptr<Location<Number>> loc = parallelCompose( locLhs, locRhs, lhsVar, rhsVar, haVar );
			if ( loc != nullptr ) {
				TRACE( "hypro.datastructures.hybridAutomaton", "Add combined location " << *loc );
				ha.addLocation( std::move( loc ) );
			}
		}
	}
	TRACE( "hypro.datastructures.hybridAutomaton", "Created " << ha.getLocations().size() << " locations" );

	TRACE( "hypro.datastructures.hybridAutomaton", "Combine synchronized transitions" );
	std::set<Label> lhsLabels = lhs.getLabels();
	std::set<Label> rhsLabels = rhs.getLabels();
	for ( const auto& lhsT : lhs.getTransitions() ) {
		for ( const auto& rhsT : rhs.getTransitions() ) {
			std::unique_ptr<Transition<Location<Number>>> t = parallelCompose( lhsT, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
			if ( t ) {
				// ha.addTransition( std::move( t ) );
				( t->getSource() )->addTransition( std::move( t ) );
			}
		}
	}

	// non-synchronizing transitions in each component
	// fix rhs first
	TRACE( "hypro.datastructures.hybridAutomaton", "Build non-synchronizing transitions for lhs, fix rhs" );
	for ( const auto& lhsT : lhs.getTransitions() ) {
		if ( lhsT->getLabels().empty() ) {
			for ( const auto& loc : rhs.getLocations() ) {
				std::unique_ptr<Transition<Location<Number>>> tmp = std::make_unique<Transition<Location<Number>>>( Transition<Location<Number>>( loc, loc ) );
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>( matrix_t<Number>::Identity( rhsVar.size(), rhsVar.size() ), vector_t<Number>::Zero( rhsVar.size() ) );
				if ( !sharedVars.empty() ) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					// Todo: iterate over rows, then over cols (only the ones which correspond to shared vars) and set the resets accordingly.

					for ( auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt ) {
						for ( auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt ) {
							tmpReset.rGetMatrix()( shdIt->second.second, colIt->second.second ) = lhsT->getReset().getMatrix()( shdIt->second.first, colIt->second.first );
						}
						tmpReset.rGetVector()( shdIt->second.second ) = lhsT->getReset().getVector()( shdIt->second.first );
					}
				}

				tmp->setReset( tmpReset );
				tmp->setAggregation( lhsT->getAggregation() );

				std::unique_ptr<Transition<Location<Number>>> t = parallelCompose( lhsT, tmp.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					// ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( std::move( t ) );
				}
			}
		}
	}
	// fix lhs
	TRACE( "hypro.datastructures.hybridAutomaton", "Build non-synchronizing transitions for rhs, fix lhs" );
	for ( const auto& rhsT : rhs.getTransitions() ) {
		if ( rhsT->getLabels().empty() ) {
			for ( const auto& loc : lhs.getLocations() ) {
				std::unique_ptr<Transition<Location<Number>>> tmp = std::make_unique<Transition<Location<Number>>>( Transition<Location<Number>>( loc, loc ) );
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

				std::unique_ptr<Transition<Location<Number>>> t = parallelCompose( tmp.get(), rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					// ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( std::move( t ) );
				}
			}
		}
	}

	// set initial states
	TRACE( "hypro.datastructures.hybridAutomaton", "Combine initial states (not yet implemented)" );
	for ( auto const& [loc_lhs, condition_lhs] : lhs.getInitialStates() ) {
		for ( auto const& [loc_rhs, condition_rhs] : rhs.getInitialStates() ) {
			// simply put constraints (rows) below each other, but reorder variables (columns) of both lhs and rhs to fit new order

			auto num_constraints_lhs = condition_lhs.getMatrix().rows();
			auto num_constraints_rhs = condition_rhs.getMatrix().rows();

			auto total_constraints = num_constraints_lhs + num_constraints_rhs;
			matrix_t<Number> constraints{ total_constraints, haVar.size() };

			Eigen::Index col = 0;
			for ( std::string const& variable : haVar ) {
				auto index_lhs = std::distance( lhsVar.begin(), std::find( lhsVar.begin(), lhsVar.end(), variable ) );
				auto index_rhs = std::distance( rhsVar.begin(), std::find( rhsVar.begin(), rhsVar.end(), variable ) );

				// put lhs part of column in at the top
				if ( size_t( index_lhs ) < lhsVar.size() ) {
					constraints.col( col ).head( num_constraints_lhs ) = condition_lhs.getMatrix().col( index_lhs );
				}

				if ( size_t( index_rhs ) < rhsVar.size() ) {
					constraints.col( col ).tail( num_constraints_rhs ) = condition_rhs.getMatrix().col( index_rhs );
				}
				col += 1;
			}

			vector_t<Number> constants{ num_constraints_lhs + num_constraints_rhs };
			constants.head( num_constraints_lhs ) = condition_lhs.getVector();
			constants.tail( num_constraints_rhs ) = condition_rhs.getVector();

			std::string loc_name = loc_lhs->getName() + "_" + loc_rhs->getName();
			Location<Number> const* init_loc = ha.getLocation( loc_name );
			ha.addInitialState( init_loc, Condition{ constraints, constants } );
		}
	}

	// localBadstates
	// globalBAdstates

	// remove non-reachable locations and transitions.
	ha.reduce();

	return ha;
}

template <typename Number>
HybridAutomaton<Number> parallelCompose( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs, const std::map<std::string, std::vector<Location<Number>*>>& masters, bool reduce ) {
	TRACE( "hypro.datastructures.hybridAutomaton", "Parallel composition of " << lhs << "\n\n and \n\n"
																			  << rhs );
	HybridAutomaton<Number> ha;
	using variableVector = std::vector<std::string>;  /// Vector of variables
	const variableVector& lhsVar = lhs.getVariables();
	const variableVector& rhsVar = rhs.getVariables();
	std::map<unsigned, std::pair<unsigned, unsigned>> sharedVars;

	variableVector haVar;
	variableVector::size_type i = 0;
	variableVector::size_type j = 0;
	TRACE( "hypro.datastructures.hybridAutomaton", "Combine variable sets" );
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
	{
		std::stringstream ss;
		for ( const auto& v : haVar ) {
			ss << v << ", ";
		}
		TRACE( "hypro.datastructures.hybridAutomaton", "Resulting set of variables: " << ss.str() );
	}
	ha.setVariables( haVar );

	// find shared variables
	TRACE( "hypro.datastructures.hybridAutomaton", "Find shared variables" );
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
			TRACE( "hypro.datastructures.hybridAutomaton", "Shared var at " << i << " corresponds to original indices (" << l << "," << r << ")" );
			sharedVars[i] = std::make_pair( l, r );
		}
	}

	TRACE( "hypro.datastructures.hybridAutomaton", "Combine locations" );
	for ( const auto& locLhs : lhs.getLocations() ) {
		for ( const auto& locRhs : rhs.getLocations() ) {
			std::unique_ptr<Location<Number>> loc = parallelCompose( locLhs, locRhs, lhsVar, rhsVar, haVar, masters );
			if ( loc != nullptr ) {
				TRACE( "hypro.datastructures.hybridAutomaton", "Add combined location " << *loc );
				ha.addLocation( std::move( loc ) );
			}
		}
	}
	TRACE( "hypro.datastructures.hybridAutomaton", "Created " << ha.getLocations().size() << " locations" );

	TRACE( "hypro.datastructures.hybridAutomaton", "Combine synchronized transitions" );
	std::set<Label> lhsLabels = lhs.getLabels();
	std::set<Label> rhsLabels = rhs.getLabels();
	for ( const auto& lhsT : lhs.getTransitions() ) {
		for ( const auto& rhsT : rhs.getTransitions() ) {
			std::unique_ptr<Transition<Location<Number>>> t = parallelCompose( lhsT, rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels, masters );
			if ( t ) {
				// ha.addTransition( std::move( t ) );
				( t->getSource() )->addTransition( std::move( t ) );
			}
		}
	}

	// non-synchronizing transitions in each component
	// fix rhs first
	TRACE( "hypro.datastructures.hybridAutomaton", "Build non-synchronizing transitions for lhs, fix rhs" );
	for ( const auto& lhsT : lhs.getTransitions() ) {
		if ( lhsT->getLabels().empty() ) {
			for ( const auto& loc : rhs.getLocations() ) {
				std::unique_ptr<Transition<Location<Number>>> tmp = std::make_unique<Transition<Location<Number>>>( Transition<Location<Number>>( loc, loc ) );
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>( matrix_t<Number>::Identity( rhsVar.size(), rhsVar.size() ), vector_t<Number>::Zero( rhsVar.size() ) );
				auto lhsReset = lhsT->getReset();
				if ( !sharedVars.empty() && !lhsReset.empty() ) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					// Todo: iterate over rows, then over cols (only the ones which correspond to shared vars) and set the resets accordingly.

					for ( auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt ) {
						for ( auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt ) {
							tmpReset.rGetMatrix()( shdIt->second.second, colIt->second.second ) = lhsReset.getMatrix()( shdIt->second.first, colIt->second.first );
						}
						tmpReset.rGetVector()( shdIt->second.second ) = lhsReset.getVector()( shdIt->second.first );
					}
				}

				tmp->setReset( tmpReset );
				tmp->setAggregation( lhsT->getAggregation() );

				std::unique_ptr<Transition<Location<Number>>> t = parallelCompose( lhsT, tmp.get(), lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					// ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( std::move( t ) );
				}
			}
		}
	}
	// fix lhs
	TRACE( "hypro.datastructures.hybridAutomaton", "Build non-synchronizing transitions for rhs, fix lhs" );
	for ( const auto& rhsT : rhs.getTransitions() ) {
		if ( rhsT->getLabels().empty() ) {
			for ( const auto& loc : lhs.getLocations() ) {
				std::unique_ptr<Transition<Location<Number>>> tmp = std::make_unique<Transition<Location<Number>>>( Transition<Location<Number>>( loc, loc ) );
				// TODO: temporary test -> fix!
				Reset<Number> tmpReset = Reset<Number>( matrix_t<Number>::Identity( lhsVar.size(), lhsVar.size() ), vector_t<Number>::Zero( lhsVar.size() ) );
				auto rhsReset = rhsT->getReset();
				if ( !sharedVars.empty() && !rhsReset.empty() ) {
					// Attention: This is a temporary solution. Naturally, we would need to replicate the reset on the shared variables to create
					// an admissible combined reset.
					for ( auto shdIt = sharedVars.begin(); shdIt != sharedVars.end(); ++shdIt ) {
						for ( auto colIt = sharedVars.begin(); colIt != sharedVars.end(); ++colIt ) {
							tmpReset.rGetMatrix()( shdIt->second.first, colIt->second.first ) = rhsReset.getMatrix()( shdIt->second.second, colIt->second.second );
						}
						tmpReset.rGetVector()( shdIt->second.first ) = rhsReset.getVector()( shdIt->second.second );
					}
				}

				tmp->setReset( tmpReset );
				tmp->setAggregation( rhsT->getAggregation() );

				std::unique_ptr<Transition<Location<Number>>> t = parallelCompose( tmp.get(), rhsT, lhsVar, rhsVar, haVar, ha, lhsLabels, rhsLabels );
				if ( t ) {
					// ha.addTransition( std::move( t ) );
					( t->getSource() )->addTransition( std::move( t ) );
				}
			}
		}
	}

	// set initial states
	TRACE( "hypro.datastructures.hybridAutomaton", "Combine initial states (not yet implemented)" );
	for ( auto const& [loc_lhs, condition_lhs] : lhs.getInitialStates() ) {
		for ( auto const& [loc_rhs, condition_rhs] : rhs.getInitialStates() ) {
			// simply put constraints (rows) below each other, but reorder variables (columns) of both lhs and rhs to fit new order

			auto num_constraints_lhs = condition_lhs.isTrue() ? 0 : condition_lhs.getMatrix().rows();
			auto num_constraints_rhs = condition_rhs.isTrue() ? 0 : condition_rhs.getMatrix().rows();

			auto total_constraints = num_constraints_lhs + num_constraints_rhs;
			matrix_t<Number> constraints{ total_constraints, haVar.size() };

			Eigen::Index col = 0;
			for ( std::string const& variable : haVar ) {
				auto index_lhs = std::distance( lhsVar.begin(), std::find( lhsVar.begin(), lhsVar.end(), variable ) );
				auto index_rhs = std::distance( rhsVar.begin(), std::find( rhsVar.begin(), rhsVar.end(), variable ) );

				// put lhs part of column in at the top
				if ( size_t( index_lhs ) < lhsVar.size() ) {
					constraints.col( col ).head( num_constraints_lhs ) = condition_lhs.getMatrix().col( index_lhs );
				}

				if ( size_t( index_rhs ) < rhsVar.size() ) {
					constraints.col( col ).tail( num_constraints_rhs ) = condition_rhs.getMatrix().col( index_rhs );
				}
				col += 1;
			}

			vector_t<Number> constants{ num_constraints_lhs + num_constraints_rhs };
			if ( num_constraints_lhs > 0 ) {
				constants.head( num_constraints_lhs ) = condition_lhs.getVector();
			}
			if ( num_constraints_rhs > 0 ) {
				constants.tail( num_constraints_rhs ) = condition_rhs.getVector();
			}

			std::string loc_name = loc_lhs->getName() + "_" + loc_rhs->getName();
			Location<Number> const* init_loc = ha.getLocation( loc_name );
			ha.addInitialState( init_loc, Condition{ constraints, constants } );
		}
	}

	// localBadstates
	// globalBAdstates
	typename HybridAutomaton<Number>::conditionVector globalSpec;
	for ( const auto& condition : lhs.getGlobalBadStates() ) {
		globalSpec.push_back( combine( condition, hypro::Condition<Number>::True(), haVar, lhsVar, rhsVar ) );
	}
	for ( const auto& condition : rhs.getGlobalBadStates() ) {
		globalSpec.push_back( combine( condition, hypro::Condition<Number>::True(), haVar, lhsVar, rhsVar ) );
	}
	ha.setGlobalBadStates( globalSpec );

	// remove non-reachable locations and transitions.
	if ( reduce ) {
		ha.reduce();
	}

	return ha;
}

}  // namespace hypro
