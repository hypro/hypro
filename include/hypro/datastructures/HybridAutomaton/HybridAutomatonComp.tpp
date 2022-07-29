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
	if ( mIsValid ) return;
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
			bool found = false;
			for ( auto* l : locs ) {
				for ( auto* m : it->second ) {
					if ( *l == *m ) {
						if ( !found ) {
							localMasters[var] = {};
							localMasters[var].push_back( l );
							found = true;
						} else {
							throw std::logic_error( "Two locations are mastering the same variable" );
						}
					}
				}
			}
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
						for ( std::size_t otherAutomatonIdx = 0; otherAutomatonIdx != mAutomaton.mAutomata.size(); ++otherAutomatonIdx ) {
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
		// only proceed, if the invariant is not trivially true (in which case it does not have a matrix and the following will fail)
		if ( !localInvariant.isTrue() ) {
			for ( std::size_t constraintIdx = 0; constraintIdx < localInvariant.getMatrix().rows(); ++constraintIdx ) {
				vector_t<Number> newRow = vector_t<Number>::Zero( haVars.size() );
				for ( std::size_t localCol = 0; localCol != localInvariant.getMatrix().cols(); ++localCol ) {
					newRow( mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localInvariant.getMatrix()( constraintIdx, localCol );
				}
				appendRow( invariantConstraints, newRow );
				appendRow( invariantConstants, localInvariant.getVector()( constraintIdx ) );
			}
		}
	}  // loop over all automata in the composition

	// set the flow as composed before
	castawayConst().setFlow( haFlow );
	// Location<Number>::setFlow( haFlow );
	//  set name
	{
		std::stringstream ss;
		ss << ( *std::begin( locs ) )->getName();
		for ( auto it = std::next( std::begin( locs ) ); it != std::end( locs ); ++it ) {
			ss << "_" << ( *it )->getName();
		}
		castawayConst().setName( ss.str() );
		// Location<Number>::setName( ss.str() );
	}

	// set the invariant as composed before
	castawayConst().setInvariant( Condition<Number>( invariantConstraints, invariantConstants ) );
	// Location<Number>::setInvariant( Condition<Number>( invariantConstraints, invariantConstants ) );

	// build stumps of transitions, idea: use permutations of indices to identify all possible combinations
	std::vector<std::size_t> bounds;
	for ( const auto* l : locs ) {
		bounds.push_back( l->getTransitions().size() );
	}
	hypro::Combinator perm{ bounds, locs.size() };
	// loop over all permutations and create according transitions
	while ( !perm.end() ) {
		auto selection = perm();
		// quick check: if the transitions synchronize, all of them should
		const std::vector<Label>& syncLabels = locs.front()->getTransitions()[selection.front()]->getLabels();
		bool skip = false;
		for ( std::size_t automatonIdx = 1; automatonIdx < locs.size(); ++automatonIdx ) {
			if ( locs[automatonIdx]->getTransitions()[selection[automatonIdx]]->getLabels() != syncLabels ) {
				skip = true;
				break;
			}
		}
		if ( skip ) {
			continue;
		}

		matrix_t<Number> guardConstraints = matrix_t<Number>::Zero( 0, haVars.size() );
		vector_t<Number> guardConstants = vector_t<Number>::Zero( 0 );
		matrix_t<Number> resetMatrix = matrix_t<Number>::Identity( haVars.size(), haVars.size() );
		vector_t<Number> resetVector = vector_t<Number>::Zero( haVars.size() );
		bool urgent = false;
		std::vector<std::size_t> targetLocationIndices;
		for ( std::size_t automatonIdx = 0; automatonIdx < selection.size(); ++automatonIdx ) {
			auto* lPtr = locs[automatonIdx];
			auto* tPtr = locs[automatonIdx]->getTransitions()[selection[automatonIdx]].get();
			// once one transition is urgent, the compose will be as well
			if ( tPtr->isUrgent() ) {
				urgent = true;
			}
			// assemble target location indices, required later to identify possible duplicate composed target locations
			targetLocationIndices.push_back( getIndex( mAutomaton.mAutomata[automatonIdx].getLocations(), tPtr->getTarget() ) );
			// cannot be undefined, otherwise the target location would not be in the location set of the automaton holding the source location
			assert( targetLocationIndices.back() >= 0 );
			// handling of the guard condition
			const auto& localGuard = tPtr->getGuard();
			if ( !localGuard.isTrue() ) {
				for ( std::size_t constraintIdx = 0; constraintIdx < localGuard.getMatrix().rows(); ++constraintIdx ) {
					vector_t<Number> newRow = vector_t<Number>::Zero( haVars.size() );
					for ( std::size_t localCol = 0; localCol != localGuard.getMatrix().cols(); ++localCol ) {
						newRow( mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localGuard.getMatrix()( constraintIdx, localCol );
					}
					appendRow( guardConstraints, newRow );
					appendRow( guardConstants, localGuard.getVector()( constraintIdx ) );
				}
			}

			// handling of the reset
			// TODO extend to interval resets
			for ( std::size_t globalVIdx = 0; globalVIdx != mAutomaton.getVariables().size(); ++globalVIdx ) {
				auto globalVName = mAutomaton.getVariables()[globalVIdx];
				// if the variable is mastered
				// TODO check for the right variable
				if ( localMasters.count( globalVName ) > 0 ) {
					// if the current location is the master, simply write reset indicated by globalVIdx, else do nothing
					if ( localMasters[globalVName].front() == lPtr ) {
						const auto& localReset = tPtr->getReset();
						if ( !localReset.isIdentity() ) {
							for ( std::size_t localCol = 0; localCol != localReset.getMatrix().cols(); ++localCol ) {
								resetMatrix( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localReset.getMatrix()( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol );
							}
							resetVector( globalVIdx ) = localReset.getVector()( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] );
						}
					}
				} else {
					// the variable is not mastered
					// check if the current automaton has information for this variable, if not (value is -1), skip
					if ( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] > 0 ) {
						// the global variable is also in the local variable set, import reset, if admissible
						// distinguish between identity resets (which might have an empty matrix) and others
						if ( tPtr->getReset().isIdentity() ) {
							// is identity - check with all other automata, if okay, do nothing, since the matrix is initialized as an identity reset
							for ( std::size_t otherAutomatonIdx = 0; otherAutomatonIdx != mAutomaton.mAutomata.size(); ++otherAutomatonIdx ) {
								auto* otherTPtr = locs[otherAutomatonIdx]->getTransitions()[selection[otherAutomatonIdx]].get();
								if ( !otherTPtr->getReset().isIdentity() ) {
									throw std::logic_error( "Resets of shared variables are not admissible" );
								}
							}
						} else {
							// is not identity, i.e., does definitely have a matrix
							const auto& localResetMatrix = tPtr->getReset().getMatrix();
							const auto& localResetVector = tPtr->getReset().getVector();
							// maps the global var index to the row in the local reset
							std::size_t localRow = mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
							// try to import local reset
							for ( std::size_t localCol = 0; localCol != localResetMatrix.cols(); ++localCol ) {
								// check admissibility by checking against all other automata
								for ( std::size_t otherAutomatonIdx = 0; otherAutomatonIdx != mAutomaton.mAutomata.size(); ++otherAutomatonIdx ) {
									auto* otherTPtr = locs[otherAutomatonIdx]->getTransitions()[selection[otherAutomatonIdx]].get();
									// column of the same variable in the other automaton, can be -1 if the other automaton does not have this variable
									std::size_t otherCol = mAutomaton.mGlobalToLocalVars[mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )]][otherAutomatonIdx];
									// do not compare to one self and skip, if the other automaton does not have the variable (localCol) in its set
									// or if it does not have information about the main variable (globalIdx)
									if ( otherAutomatonIdx == automatonIdx || otherCol < 0 || mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx] < 0 ) {
										continue;
									}
									// the other automaton has information on this (local col) variable
									const auto& otherReset = otherTPtr->getReset();
									if ( otherReset.isIdentity() || otherReset.getMatrix()( mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx], otherCol ) != localResetMatrix( localRow, localCol ) || otherReset.getVector()( mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx] ) != resetVector( localRow ) ) {
										throw std::logic_error( "Resets of shared variables are not admissible" );
									}
								}
								// if we reach here, the flow is admissible for the current col
								resetMatrix( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localResetMatrix( localRow, localCol );
							}  // loop over local variable idx
						}	   // if is identity - else
					}		   // if automaton does have information on this variable
				}			   // if variable is not mastered
			}				   // loop over all globally available variables
		}

		// at this point we have all single transitions, all guards, all resets, urgency
		// create stub for a new target location, if it does not yet exist
		std::size_t targetIndex = mAutomaton.mLocations.size();
		{
			auto entryPairIt = mAutomaton.mComposedLocs.find( targetLocationIndices );
			if ( entryPairIt != std::end( mAutomaton.mComposedLocs ) ) {
				targetIndex = entryPairIt->second;
			} else {
				mAutomaton.mLocations.emplace_back( mAutomaton );
				auto& newLoc = mAutomaton.mLocations.back();
				newLoc.mCompositionals = targetLocationIndices;
				newLoc.mIsValid = false;
			}
		}
		// create new transition
		std::unique_ptr<CompTransition> newTransition = std::make_unique<CompTransition>();
		//  fill properties
		newTransition->setGuard( { guardConstraints, guardConstants } );
		newTransition->setReset( { resetMatrix, resetVector } );
		newTransition->setUrgent( urgent );
		newTransition->setLabels( syncLabels );
		newTransition->setSource( const_cast<ComposedLocation<Number>*>( this ) );
		newTransition->setTarget( &mAutomaton.mLocations[targetIndex] );
		mTransitions.emplace_back( std::move( newTransition ) );
	}

	mIsValid = true;
}

template <typename Number>
std::vector<Location<Number>*> HybridAutomatonComp<Number>::getLocations() const {
	std::vector<Location<Number>*> res;
	// collect all currently discovered locations, validate those, make sure not to validate further ones, as this will unroll the whole automaton
	for ( std::size_t locationIdx = 0; locationIdx < mLocations.size(); ++locationIdx ) {
		mLocations[locationIdx].validate();
		res.push_back( &( mLocations[locationIdx] ) );
	}
	return res;
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
const typename HybridAutomatonComp<Number>::locationConditionMap& HybridAutomatonComp<Number>::getInitialStates() const {
	if ( !mCachesValid[CACHE::INITIALSTATES] ) {
		// cleanup
		mInitialStates.clear();
		// build product of all possible locations and all possible configurations, maybe reuse code from location composition
		std::vector<std::size_t> numberInitialSets;
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			numberInitialSets.push_back( mAutomata[automatonIdx].getInitialStates().size() );
		}
		hypro::Combinator perm{ numberInitialSets, mAutomata.size() };

		while ( !perm.end() ) {
			// current combination of indices pointing to initial sets
			auto combination = perm();
			// collect constraints
			matrix_t<Number> initialMatrix = matrix_t<Number>::Zero( 0, getVariables().size() );
			vector_t<Number> initialVector = vector_t<Number>::Zero( 0 );
			// translate local initial locations to local location indices
			std::vector<std::size_t> locationIndices;
			for ( std::size_t automatonIdx = 0; automatonIdx < combination.size(); ++automatonIdx ) {
				auto initialStateIt = std::begin( mAutomata[automatonIdx].getInitialStates() );
				// for each automaton consider the i-th initial set (enconded in combination) and get the index of the location
				std::size_t idx = 0;
				// TODO: this is a silly workaround, getLocations returns a vector of Location* while getInitialStates() maps from const Location*
				while ( idx < mAutomata[automatonIdx].getLocations().size() && ( *mAutomata[automatonIdx].getLocations()[idx] ) != *std::next( initialStateIt, combination[automatonIdx] )->first ) {
					++idx;
				}
				// locationIndices.push_back( getIndex( mAutomata[automatonIdx].getLocations(), std::next( initialStateIt, combination[automatonIdx] )->first ) );
				locationIndices.push_back( idx );
				assert( locationIndices.back() >= 0 );
				const auto& localInitialCondition = std::next( initialStateIt, combination[automatonIdx] )->second;
				if ( !localInitialCondition.isTrue() ) {
					// iterate over local constraints, convert to global ones
					for ( std::size_t constraintIdx = 0; constraintIdx < localInitialCondition.getMatrix().rows(); ++constraintIdx ) {
						vector_t<Number> newRow = vector_t<Number>::Zero( getVariables().size() );
						for ( std::size_t localCol = 0; localCol != localInitialCondition.getMatrix().cols(); ++localCol ) {
							newRow( mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localInitialCondition.getMatrix()( constraintIdx, localCol );
						}
						appendRow( initialMatrix, newRow );
						appendRow( initialVector, localInitialCondition.getVector()( constraintIdx ) );
					}
				}
			}
			// create and add location, if it does not yet exist
			{
				auto entryPairIt = mComposedLocs.find( locationIndices );
				if ( entryPairIt == std::end( mComposedLocs ) ) {
					ComposedLocation<Number> tmp{ *this };
					mLocations.emplace_back( std::move( tmp ) );
					auto& newLoc = mLocations.back();
					newLoc.mCompositionals = locationIndices;
					newLoc.mIsValid = false;
					mComposedLocs[locationIndices] = mLocations.size() - 1;
				}
			}
			assert( mComposedLocs.count( locationIndices ) > 0 );
			// write initial states
			mInitialStates[mLocations[mComposedLocs[locationIndices]]] = Condition<Number>( initialMatrix, initialVector );
		}
		mCachesValid[CACHE::INITIALSTATES] = true;
	}
	return mInitialStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap& HybridAutomatonComp<Number>::getLocalBadStates() const {
	if ( !mCachesValid[CACHE::LOCALBADSTATES] ) {
		throw NotImplemented();
		mCachesValid[CACHE::LOCALBADSTATES] = true;
	}
	return mLocalBadStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::conditionVector& HybridAutomatonComp<Number>::getGlobalBadStates() const {
	if ( !mCachesValid[CACHE::GLOBALBADSTATES] ) {
		throw NotImplemented();
		mCachesValid[CACHE::GLOBALBADSTATES] = true;
	}
	return mGlobalBadStates;
}

template <typename Number>
unsigned HybridAutomatonComp<Number>::dimension() const {
	return getVariables().size();
}

template <typename Number>
const std::vector<std::string>& HybridAutomatonComp<Number>::getVariables() const {
	if ( !mCachesValid[CACHE::VARIABLES] ) {
		std::set<std::string> uniqueVariables;
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			uniqueVariables.insert( std::begin( mAutomata[automatonIdx].getVariables() ), std::end( mAutomata[automatonIdx].getVariables() ) );
		}
		mVariables.clear();
		mVariables.insert( std::end( mVariables ), std::begin( uniqueVariables ), std::end( uniqueVariables ) );

		setVariableMapping();

		mCachesValid[CACHE::VARIABLES] = true;
	}
	return mVariables;
}

template <typename Number>
std::set<Label> HybridAutomatonComp<Number>::getLabels() const {
	std::set<Label> res;
	for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
		auto labels = mAutomata[automatonIdx].getLabels();
		res.insert( std::begin( labels ), std::end( labels ) );
	}
	return res;
}

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
