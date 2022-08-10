/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
					for ( std::size_t localCol = 0; localCol < localFlow.cols(); ++localCol ) {
						if ( localCol != localFlow.cols() - 1 ) {
							haFlow( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localFlow( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol );
						} else {
							haFlow( globalVIdx, haFlow.cols() - 1 ) = localFlow( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol );
						}
					}
				}
			} else {
				// the variable is not mastered
				// check if the current automaton has information for this variable, if not (value is -1), skip
				if ( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] >= 0 ) {
					// the global variable is also in the local variable set, import flow, if admissible
					auto localFlow = lPtr->getLinearFlow().getFlowMatrix();
					// maps the global var index to the row in the local flow
					auto localRow = mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
					// try to import local flow
					for ( std::size_t localCol = 0; localCol < localFlow.cols(); ++localCol ) {
						bool isConst = ( localCol == localFlow.cols() - 1 );
						// check admissibility by checking against all other automata
						for ( std::size_t otherAutomatonIdx = 0; otherAutomatonIdx != mAutomaton.mAutomata.size(); ++otherAutomatonIdx ) {
							// column of the same variable in the other automaton, can be -1 if the other automaton does not have this variable
							long int otherCol;
							if ( isConst ) {
								otherCol = locs[otherAutomatonIdx]->getLinearFlow().getFlowMatrix().cols() - 1;
							} else {
								otherCol = mAutomaton.mGlobalToLocalVars[mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )]][otherAutomatonIdx];
							}
							// do not compare to one self and skip, if the other automaton does not have the variable (localCol) in its set
							// or if it does not have information about the main variable (globalIdx)
							if ( otherAutomatonIdx == automatonIdx || otherCol < 0 || mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx] < 0 ) {
								continue;
							}
							// the other automaton has information on this (local col) variable
							auto otherFlow = locs[otherAutomatonIdx]->getLinearFlow().getFlowMatrix();
							if ( otherFlow( mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx], otherCol ) != localFlow( localRow, localCol ) ) {
								throw std::logic_error( "Flows of shared variables are not admissible" );
							}
						}
						// if we reach here, the flow is admissible for the current col
						if ( isConst ) {
							haFlow( globalVIdx, haFlow.cols() - 1 ) = localFlow( localRow, localCol );
						} else {
							haFlow( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localFlow( localRow, localCol );
						}
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

	// build stumps of transitions, idea: for non-synchronizing jumps, only one component changes its location,
	// for synchronizing jumps, all components change their location. Thus, separate synchronizing and non-synchronizing jumps,
	// handle separately
	using TransitionT = Transition<Number, Location<Number>>;
	std::multimap<std::size_t, TransitionT*> nonSynchronizedJumps;
	std::map<std::vector<Label>, std::vector<TransitionT*>> synchronizedJumps;
	// collect synchronized and non-synchronized jumps
	for ( std::size_t locationIdx = 0; locationIdx < locs.size(); ++locationIdx ) {
		for ( const auto& t : locs[locationIdx]->getTransitions() ) {
			auto* tPtr = t.get();
			// synchronizing jump
			if ( !tPtr->getLabels().empty() ) {
				if ( synchronizedJumps.count( tPtr->getLabels() ) == 0 ) {
					synchronizedJumps.emplace( std::make_pair( tPtr->getLabels(), std::vector<TransitionT*>{} ) );
				}
				synchronizedJumps[tPtr->getLabels()].push_back( tPtr );
			} else {
				nonSynchronizedJumps.insert( std::make_pair( locationIdx, tPtr ) );
			}
		}
	}
	// remove all synchronizing jumps where not all components can participate
	for ( auto jumpIt = std::begin( synchronizedJumps ); jumpIt != std::end( synchronizedJumps ); ) {
		if ( jumpIt->second.size() != locs.size() ) {
			jumpIt = synchronizedJumps.erase( jumpIt );
		} else {
			++jumpIt;
		}
	}

	// handle non-synchronizing jumps first
	for ( const auto& [componentIdx, tPtr] : nonSynchronizedJumps ) {
		matrix_t<Number> guardConstraints = matrix_t<Number>::Zero( 0, haVars.size() );
		vector_t<Number> guardConstants = vector_t<Number>::Zero( 0 );
		matrix_t<Number> resetMatrix = matrix_t<Number>::Identity( haVars.size(), haVars.size() );
		vector_t<Number> resetVector = vector_t<Number>::Zero( haVars.size() );
		bool urgent = false;
		std::vector<std::size_t> targetLocationIndices;
		for ( std::size_t automatonIdx = 0; automatonIdx < locs.size(); ++automatonIdx ) {
			// if the component does not change location, use the same local location as target, do nothing apart from that
			if ( automatonIdx != componentIdx ) {
				targetLocationIndices.push_back( mCompositionals[automatonIdx] );
			} else {
				auto* lPtr = locs[automatonIdx];
				// once one transition is urgent, the compose will be as well
				if ( tPtr->isUrgent() ) {
					urgent = true;
				}
				// assemble target location indices, required later to identify possible duplicate composed target locations
				targetLocationIndices.push_back( getIndex( mAutomaton.mAutomata[automatonIdx].getLocations(), tPtr->getTarget() ) );
				// cannot be undefined, otherwise the target location would not be in the location set of the automaton holding the source location
				assert( targetLocationIndices.back() >= 0 );
				// handling of the guard condition
				std::cout << "Transition: " << *tPtr << std::endl;
				const auto& localGuard = tPtr->getGuard();
				if ( !localGuard.isTrue() ) {
					std::cout << "consider matrix " << localGuard.getMatrix() << " and vector " << localGuard.getVector() << std::endl;
					for ( std::size_t constraintIdx = 0; constraintIdx < localGuard.getMatrix().rows(); ++constraintIdx ) {
						vector_t<Number> newRow = vector_t<Number>::Zero( haVars.size() );
						for ( std::size_t localCol = 0; localCol != localGuard.getMatrix().cols(); ++localCol ) {
							auto coeff = localGuard.getMatrix()( constraintIdx, localCol );
							auto pos = mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )];
							newRow( pos ) = coeff;
						}
						appendRow( guardConstraints, newRow );
						appendRow( guardConstants, localGuard.getVector()( constraintIdx ) );
						std::cout << "after adding constraints: " << guardConstraints << " and vector " << guardConstants << std::endl;
					}
				}
				std::cout << "Final guard matrix: " << guardConstraints << " and vector " << guardConstants << std::endl;

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
						if ( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] >= 0 ) {
							// the global variable is also in the local variable set, import reset, if admissible
							// distinguish between identity resets (which might have an empty matrix) and others
							if ( tPtr->getReset().isIdentity() ) {
								// do nothing
							} else {
								// is not identity, i.e., does definitely have a matrix
								const auto& localResetMatrix = tPtr->getReset().getMatrix();
								const auto& localResetVector = tPtr->getReset().getVector();
								// maps the global var index to the row in the local reset
								std::size_t localRow = mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
								// import local reset
								for ( std::size_t localCol = 0; localCol != localResetMatrix.cols(); ++localCol ) {
									resetMatrix( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localResetMatrix( localRow, localCol );
								}  // loop over local variable idx
							}	   // if is identity - else
						}		   // if automaton does have information on this variable
					}			   // if variable is not mastered
				}				   // loop over all globally available variables for resets
			}
		}

		// at this point we have all guards, all resets, urgency
		// create stub for a new target location, if it does not yet exist
		auto targetPosition = std::end( mAutomaton.mLocations );
		{
			auto entryPairIt = mAutomaton.mComposedLocs.find( targetLocationIndices );
			if ( entryPairIt != std::end( mAutomaton.mComposedLocs ) ) {
				targetPosition = entryPairIt->second;
			} else {
				mAutomaton.mLocations.emplace_back( mAutomaton );
				auto& newLoc = mAutomaton.mLocations.back();
				newLoc.mCompositionals = targetLocationIndices;
				newLoc.mIsValid = false;
				targetPosition = std::prev( std::end( mAutomaton.mLocations ) );
				mAutomaton.mComposedLocs[targetLocationIndices] = targetPosition;
			}
		}
		// create new transition
		std::unique_ptr<CompTransition> newTransition = std::make_unique<CompTransition>();
		//  fill properties
		newTransition->setGuard( { guardConstraints, guardConstants } );
		newTransition->setReset( { resetMatrix, resetVector } );
		newTransition->setUrgent( urgent );
		newTransition->setSource( const_cast<ComposedLocation<Number>*>( this ) );
		newTransition->setTarget( &( *targetPosition ) );
		mTransitions.emplace_back( std::move( newTransition ) );
	}

	// handle synchronizing jumps
	for ( auto transitionIt = std::begin( synchronizedJumps ); transitionIt != std::end( synchronizedJumps ); ++transitionIt ) {
		matrix_t<Number> guardConstraints = matrix_t<Number>::Zero( 0, haVars.size() );
		vector_t<Number> guardConstants = vector_t<Number>::Zero( 0 );
		matrix_t<Number> resetMatrix = matrix_t<Number>::Identity( haVars.size(), haVars.size() );
		vector_t<Number> resetVector = vector_t<Number>::Zero( haVars.size() );
		bool urgent = false;
		std::vector<std::size_t> targetLocationIndices;
		for ( std::size_t automatonIdx = 0; automatonIdx < locs.size(); ++automatonIdx ) {
			auto* tPtr = transitionIt->second[automatonIdx];
			auto* lPtr = locs[automatonIdx];
			std::cout << "Transition: " << *tPtr << std::endl;
			// once one transition is urgent, the compose will be as well
			if ( tPtr->isUrgent() ) {
				urgent = true;
			}
			// assemble target location indices, required later to identify possible duplicate composed target locations
			targetLocationIndices.push_back( getIndex( mAutomaton.mAutomata[automatonIdx].getLocations(), tPtr->getTarget() ) );
			// cannot be undefined, otherwise the target location would not be in the location set of the automaton holding the source location
			assert( targetLocationIndices.back() >= 0 );
			// handling of the guard condition
			auto localGuard = tPtr->getGuard();
			if ( !localGuard.isTrue() ) {
				std::cout << "consider matrix " << localGuard.getMatrix() << " and vector " << localGuard.getVector() << std::endl;
				for ( std::size_t constraintIdx = 0; constraintIdx < localGuard.getMatrix().rows(); ++constraintIdx ) {
					vector_t<Number> newRow = vector_t<Number>::Zero( haVars.size() );
					for ( std::size_t localCol = 0; localCol != localGuard.getMatrix().cols(); ++localCol ) {
						newRow( mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localGuard.getMatrix()( constraintIdx, localCol );
					}
					appendRow( guardConstraints, newRow );
					appendRow( guardConstants, localGuard.getVector()( constraintIdx ) );
					std::cout << "after adding constraints: " << guardConstraints << " and vector " << guardConstants << std::endl;
				}
			}
			std::cout << "Final guard matrix: " << guardConstraints << " and vector " << guardConstants << std::endl;

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
					// TODO currently there are no sanity checks here!
					// check if the current automaton has information for this variable, if not (value is -1), skip
					if ( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] >= 0 ) {
						// the global variable is also in the local variable set, import reset, if admissible
						// distinguish between identity resets (which might have an empty matrix) and others
						if ( tPtr->getReset().isIdentity() ) {
							// do nothing
						} else {
							// is not identity, i.e., does definitely have a matrix
							const auto& localResetMatrix = tPtr->getReset().getMatrix();
							const auto& localResetVector = tPtr->getReset().getVector();
							// maps the global var index to the row in the local reset
							std::size_t localRow = mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
							// import local reset
							for ( std::size_t localCol = 0; localCol != localResetMatrix.cols(); ++localCol ) {
								resetMatrix( globalVIdx, mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )] ) = localResetMatrix( localRow, localCol );
							}  // loop over local variable idx
						}	   // if is identity - else
					}		   // if automaton does have information on this variable
				}			   // if variable is not mastered
			}				   // loop over all globally available variables for resets
		}

		// at this point we have all guards, all resets, urgency
		// create stub for a new target location, if it does not yet exist
		auto targetPosition = std::end( mAutomaton.mLocations );
		{
			auto entryPairIt = mAutomaton.mComposedLocs.find( targetLocationIndices );
			if ( entryPairIt != std::end( mAutomaton.mComposedLocs ) ) {
				targetPosition = entryPairIt->second;
			} else {
				mAutomaton.mLocations.emplace_back( mAutomaton );
				auto& newLoc = mAutomaton.mLocations.back();
				newLoc.mCompositionals = targetLocationIndices;
				newLoc.mIsValid = false;
				targetPosition = std::prev( std::end( mAutomaton.mLocations ) );
				mAutomaton.mComposedLocs[targetLocationIndices] = targetPosition;
			}
		}
		// create new transition
		std::unique_ptr<CompTransition> newTransition = std::make_unique<CompTransition>();
		//  fill properties
		newTransition->setGuard( { guardConstraints, guardConstants } );
		newTransition->setReset( { resetMatrix, resetVector } );
		newTransition->setLabels( transitionIt->first );
		newTransition->setUrgent( urgent );
		newTransition->setSource( const_cast<ComposedLocation<Number>*>( this ) );
		newTransition->setTarget( &( *targetPosition ) );
		mTransitions.emplace_back( std::move( newTransition ) );
	}

	mIsValid = true;
}

template <typename Number>
std::vector<typename HybridAutomatonComp<Number>::LocationType*> HybridAutomatonComp<Number>::getLocations() const {
	std::vector<LocationType*> res;
	// collect all currently discovered and validated locations, make sure not to validate further ones, as this will unroll the whole automaton
	for ( auto locIt = std::begin( mLocations ); locIt != std::end( mLocations ); ++locIt ) {
		if ( locIt->isValid() ) {
			res.push_back( &( *locIt ) );
		}
	}
	return res;
}

template <typename Number>
typename HybridAutomatonComp<Number>::LocationType* HybridAutomatonComp<Number>::getLocation( const std::size_t hash ) const {
	for ( const auto& l : mLocations ) {
		if ( l->hash() == hash ) {
			return &l;
		}
	}
	return nullptr;
}

template <typename Number>
typename HybridAutomatonComp<Number>::LocationType* HybridAutomatonComp<Number>::getLocation( const std::string& name ) const {
	for ( const auto& l : mLocations ) {
		if ( l->getName() == name ) {
			return &l;
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
					tmp.mCompositionals = locationIndices;
					tmp.mIsValid = false;
					mLocations.emplace_back( std::move( tmp ) );
					std::cout << "adress of loc " << &mLocations.back() << std::endl;
					mComposedLocs[locationIndices] = std::prev( std::end( mLocations ) );
				}
			}
			assert( mComposedLocs.count( locationIndices ) > 0 );
			// write initial states
			ComposedLocation<Number>* lPtr = &( *mComposedLocs[locationIndices] );
			std::cout << "Lptr: " << lPtr << std::endl;
			mInitialStates[lPtr] = Condition<Number>( initialMatrix, initialVector );
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
const std::set<Label>& HybridAutomatonComp<Number>::getLabels() const {
	if ( !mCachesValid[CACHE::LABELS] ) {
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			auto labels = mAutomata[automatonIdx].getLabels();
			mLabels.insert( std::begin( labels ), std::end( labels ) );
		}
	}
	return mLabels;
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
			mGlobalToLocalVars[globalIdx] = std::vector<long int>( mAutomata.size() );
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
