/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HybridAutomatonComp.h"

namespace hypro {

template <typename Number>
void ComposedLocation<Number>::validate() const {
	// perform actual composition, if not already done
	if ( isValid ) return;
	// make sure caches in the composition are up to date
	mAutomaton.setVariableMapping();
	assert( mCompositionals.size() == mAutomaton.mAutomata.size() );
	// collect all locations taking part in the composition
	std::vector<Location<Number>*> locs;
	for ( std::size_t idx = 0; idx < mCompositionals.size(); ++idx ) {
		locs.push_back( mAutomaton.mAutomata[idx].getLocationByIndex( mCompositionals[idx] ) );
	}
	// establish masters for this combination of locations
	decltype( mMasters ) localMasters;
	for ( const auto& var : mAutomaton.getVariables() ) {
		auto it = mMasters.find( var );
		if ( it != std::end( mMasters ) ) {
			// check, if one of the locations is also contained in the selected masters (it) for this variable
			auto master = std::find_if( std::begin( locs ), std::end( locs ), [&it]( auto* l ) { return std::find_if( std::begin( *it ), std::end( *it ), l ) != std::end( *it ); } );
			if ( master != std::end( locs ) ) {
				localMasters[var] = { *master };
			}
			// TODO add check that the current combination of locations does not declare two master locations for the same variable
		}
	}
	// incremental parallel composition to build the location
	// handle flow and invariant conditions at the same time
	matrix_t<Number> haFlow = matrix_t<Number>::Zero( mAutomaton.getVariables().size() + 1, mAutomaton.getVariables().size() + 1 );
	matrix_t<Number> invariantConstraints = matrix_t<Number>::Zero( 0, mAutomaton.getVariables().size() );
	vector_t<Number> invariantConstants = vector_t<Number>::Zero( 0 );
	const auto& haVars = mAutomaton.getVariables();
	for ( std::size_t automatonIdx = 0; automatonIdx != mAutomaton.mAutomata.size(); ++automatonIdx ) {
		auto* lPtr = locs[automatonIdx];
		// handling of the flow - iterate over globally available variables
		for ( std::size_t globalVIdx = 0; globalVIdx != mAutomaton.getVariables().size(); ++globalVIdx ) {
			auto globalVName = mAutomaton.getVariables()[globalVIdx];
			// if the variable is mastered
			if ( localMasters.count( globalVName ) > 0 ) {
				// if the current location is the master, simply write flow row indicated by globalVIdx, else do nothing
				if ( localMasters[globalVName].front() == lPtr ) {
					const auto& localFlow = lPtr->getLinearFlow().getFlowMatrix();
					for ( std::size_t localCol = 0; localCol != localFlow.cols(); ++localCol ) {
						haFlow( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localFlow( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol );
					}
				}
			} else {
				// the variable is not mastered
				// check if the current automaton has information for this variable, if not (value is -1), skip
				if ( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] > 0 ) {
					// the global variable is also in the local variable set, import flow, if admissible
					const auto& localFlow = lPtr->getLinearFlow().getFlowMatrix();
					// maps the global var index to the row in the local flow
					std::size_t localRow = mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
					// try to import local flow
					for ( std::size_t localCol = 0; localCol != localFlow.cols(); ++localCol ) {
						// check admissibility by checking agains all other automata
						for ( std::size_t otherAutomatonIdx = 0; otherAutomatonIdx != mAutomaton.size(); ++otherAutomatonIdx ) {
							// column of the same variable in the other automaton, can be -1 if the other automaton does not have this variable
							std::size_t otherCol = mAutomaton.mGlobalToLocalVars[mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )]][otherAutomatonIdx];
							// do not compare to one self and skip, if the other automaton does not have the variable (localCol) in its set
							// or if it does not have information about the main variable (globalIdx)
							if ( otherAutomatonIdx == automatonIdx || otherCol < 0 || mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx] < 0 ) {
								continue;
							}
							// the other automaton has information on this (local col) variable
							const auto& otherFlow = locs[otherAutomatonIdx]->getLinearFlow().getFlowMatrix();
							if ( otherFlow( mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx], otherCol ) != localFlow( localRow, localCol ) ) {
								throw std::logic_error( "Flows of shared variables are not admissible" );
							}
						}
						// if we reach here, the flow is admissible for the current col
						haFlow( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localFlow( localRow, localCol );
					}  // loop over local variable idx
				}
			}  // if variable is not mastered
		}	   // loop over all globally available variables

		// handling of the invariant condition
		const auto& localInvariant = locs[automatonIdx]->getInvariant();
		for ( std::size_t constraintIdx = 0; constraintIdx < localInvariant.getMatrix().rows(); ++constraintIdx ) {
			vector_t<Number> newRow = vector_t<Number>::Zero( haVars.size() );
			for ( std::size_t localCol = 0; localCol != localInvariant.getMatrix().cols(); ++localCol ) {
				newRow( mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localInvariant.getMatrix()( constraintIdx, localCol );
			}
			appendRow( invariantConstraints, newRow );
			appendRow( invariantConstants, localInvariant.getVector()( constraintIdx ) );
		}
	}  // loop over all automata in the composition

	// set the flow as composed before
	Location<Number>::setFlow( haFlow );
	// set name
	{
		std::stringstream ss;
		ss << ( *std::begin( locs ) )->getName();
		for ( auto it = std::next( std::begin( locs ) ); it != std::end( locs ); ++it ) {
			ss << "_" << ( *it )->getName();
		}
		Location<Number>::setName( ss.str() );
	}

	// set the invariant as composed before
	Location<Number>::setInvariant( Condition<Number>( invariantConstraints, invariantConstants ) );

	// build stumps of transitions

	isValid = true;
}

template <typename Number>
std::vector<Location<Number>*> HybridAutomatonComp<Number>::getLocations() const {
	return mLocations;
}

template <typename Number>
Location<Number>* HybridAutomatonComp<Number>::getLocation( const std::size_t hash ) const {
	for ( const auto* l : mLocations ) {
		if ( l->hash() == hash ) {
			return l;
		}
	}
	return nullptr;
}

template <typename Number>
Location<Number>* HybridAutomatonComp<Number>::getLocation( const std::string& name ) const {
	for ( const auto* l : mLocations ) {
		if ( l->getName() == name ) {
			return l;
		}
	}
	return nullptr;
}

template <typename Number>
std::vector<Transition<Number>*> HybridAutomatonComp<Number>::getTransitions() const {}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap& HybridAutomatonComp<Number>::getInitialStates() const {
	return mInitialStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap& HybridAutomatonComp<Number>::getLocalBadStates() const {
	return mLocalBadStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::conditionVector& HybridAutomatonComp<Number>::getGlobalBadStates() const {
	return mGlobalBadStates;
}

template <typename Number>
unsigned HybridAutomatonComp<Number>::dimension() const {}

template <typename Number>
const std::vector<std::string>& HybridAutomatonComp<Number>::getVariables() const {
	if ( mCachesValid ) return mVariables;

	/*
	for ( auto haIt = std::begin( mAutomata ); haIt != std::end( mAutomata ); ++haIt ) {
		mVariables.insert(std::begin(haIt->getVariables()); std::end(haIt->getVariables()));
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
	}
	 */

	return mVariables;
}

template <typename Number>
const std::set<Label> HybridAutomatonComp<Number>::getLabels() const {}

template <typename Number>
void HybridAutomatonComp<Number>::setVariableMapping() const {
	// if any cache is invalid
	if ( mGlobalToLocalVars.empty() || mLocalToGlobalVars.empty() ) {
		// clear both to make sure a clean state
		mGlobalToLocalVars.clear();
		mLocalToGlobalVars.clear();
		// for each global variable
		for ( std::size_t globalIdx = 0; globalIdx < mVariables.size(); ++globalIdx ) {
			mGlobalToLocalVars[globalIdx] = std::vector<std::size_t>{ mAutomata.size() };
			// for each component
			for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
				mGlobalToLocalVars[globalIdx][automatonIdx] = getIndex( mAutomata[automatonIdx].getVariables(), mVariables[globalIdx] );
			}
		}
		// establish reverse mapping
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			for ( std::size_t localIdx = 0; localIdx < mAutomata[automatonIdx].getVariables().size(); ++localIdx ) {
				mLocalToGlobalVars[std::make_pair( automatonIdx, localIdx )] = getIndex( mVariables, mAutomata[automatonIdx].getVariables()[localIdx] );
			}
		}
	}
}

}  // namespace hypro
