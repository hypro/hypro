/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "HybridAutomatonComp.h"

#include <Eigen/src/Core/DenseBase.h>

namespace hypro {

template <typename Number>
void ComposedLocation<Number>::validate() const {
	TRACE( "hypro.datastructures.hybridAutomatonComp", "Validate" );
	// perform actual composition, if not already done
	if ( isValid() ) return;
	//  set name
	validateName();
	// make sure caches in the composition are up to date
	mAutomaton.setVariableMapping();
	assert( mCompositionals.size() == mAutomaton.mAutomata.size() );
	// collect all locations taking part in the composition
	std::vector<Location<Number>*> locs;
	for ( std::size_t idx = 0; idx < mCompositionals.size(); ++idx ) {
		locs.push_back( mAutomaton.mAutomata[idx].getLocationByIndex( mCompositionals[idx] ) );
	}
	// establish masters for this combination of locations
	std::map<std::string, Location<Number>*> localMasters = getMasterLocations( locs );
	// incremental parallel composition to build the location
	// handle flow and invariant conditions at the same time
	composeLocationContent( locs, localMasters );

	std::size_t dim = this->mAutomaton.getVariables().size();

	// build stumps of transitions, idea: for non-synchronizing jumps, only one component changes its location,
	// for synchronizing jumps, all components change their location. Thus, separate synchronizing and non-synchronizing jumps,
	// handle separately
	using TransitionT = Transition<Location<Number>>;
	std::multimap<std::size_t, TransitionT*> nonSynchronizedJumps;
	std::map<std::vector<Label>, std::vector<std::vector<TransitionT*>>> synchronizedJumps;
	// collect synchronized and non-synchronized jumps
	collectJumpComponents( locs, nonSynchronizedJumps, synchronizedJumps );

	// handle non-synchronizing jumps first
	for ( const auto& [componentIdx, tPtr] : nonSynchronizedJumps ) {
		transitionStub stub{ dim };
		for ( std::size_t automatonIdx = 0; automatonIdx < locs.size(); ++automatonIdx ) {
			// if the component does not change location, use the same local location as target, do nothing apart from that
			if ( automatonIdx != componentIdx ) {
				stub.targetLocationIndices.push_back( mCompositionals[automatonIdx] );
			} else {
				auto* lPtr = locs[automatonIdx];
				// once one transition is urgent, the compose will be as well
				if ( tPtr->isUrgent() ) {
					stub.urgent = true;
				}
				// assemble target location indices, required later to identify possible duplicate composed target locations
				stub.targetLocationIndices.push_back(
					  getIndex( mAutomaton.mAutomata[automatonIdx].getLocations(), tPtr->getTarget() ) );
				// cannot be undefined, otherwise the target location would not be in the location set of the automaton holding the source location
				assert( stub.targetLocationIndices.back() >= 0 );
				// handling of the guard condition
				composeGuard( dim, tPtr, stub, automatonIdx );
				// handling of the reset
				composeResets( localMasters, tPtr, stub, automatonIdx, lPtr );
			}
		}

		// at this point we have all guards, all resets, urgency
		// create stub for a new target location, if it does not yet exist
		auto targetPosition = std::end( mAutomaton.mLocations );
		{
			auto entryPairIt = mAutomaton.mComposedLocs.find( stub.targetLocationIndices );
			if ( entryPairIt != std::end( mAutomaton.mComposedLocs ) ) {
				targetPosition = entryPairIt->second;
			} else {
				mAutomaton.mLocations.emplace_back( mAutomaton );
				auto& newLoc = mAutomaton.mLocations.back();
				newLoc.mCompositionals = stub.targetLocationIndices;
				targetPosition = std::prev( std::end( mAutomaton.mLocations ) );
				mAutomaton.mComposedLocs[stub.targetLocationIndices] = targetPosition;
			}
		}
		// create new transition
		std::unique_ptr<CompTransition> newTransition = std::make_unique<CompTransition>();
		//  fill properties
		newTransition->setGuard( { stub.guardConstraints, stub.guardConstants } );
		newTransition->setReset( { stub.resetMatrix, stub.resetVector } );
		newTransition->setUrgent( stub.urgent );
		newTransition->setSource( const_cast<ComposedLocation<Number>*>( this ) );
		newTransition->setTarget( &( *targetPosition ) );
		TRACE( "hypro.datastructures.hybridAutomatonComp",
			   "Create new non-synchronizing transition " << ( *newTransition.get() ) );
		mTransitions.emplace_back( std::move( newTransition ) );
	}

	// handle synchronizing jumps
	for ( auto labelIt = std::begin( synchronizedJumps ); labelIt != std::end( synchronizedJumps ); ++labelIt ) {
#ifdef HYPRO_LOGGING
		std::stringstream labels;
		for ( const auto& lab : labelIt->first ) {
			labels << lab << ", ";
		}
		TRACE( "hypro.datastructures.hybridAutomatonComp", "Consider label(s) " << labels.str() );
#endif
		std::vector<transitionStub> targets;
		// iterate over all components
		for ( std::size_t automatonIdx = 0; automatonIdx < labelIt->second.size(); ++automatonIdx ) {
			std::size_t oldNumberTargets = targets.size();
			std::size_t numAddedTransitions = labelIt->second[automatonIdx].size();
			assert( numAddedTransitions > 0 );
			// set up copies of targets to create all combinations of synchronizing transitions
			if ( targets.empty() ) {
				targets = std::vector<transitionStub>( numAddedTransitions, transitionStub( dim ) );
				oldNumberTargets = 1;
			} else {
				for ( std::size_t i = 0; i < numAddedTransitions - 1; ++i ) {
					for ( std::size_t j = 0; j < oldNumberTargets; ++j ) {
						targets.push_back( targets[j] );
					}
				}
				assert( targets.size() == oldNumberTargets * numAddedTransitions );
			}
			TRACE( "hypro.datastructures.hybridAutomatonComp",
				   "Have " << oldNumberTargets << " already existing transitions." );
			// iterate over all outgoing jumps of a single location (of the current component) that synchronize on the selected label
			TRACE( "hypro.datastructures.hybridAutomatonComp",
				   "Component " << automatonIdx << " has " << numAddedTransitions << " transitions synchronizing." );
			for ( std::size_t pos = 0; pos < targets.size(); ++pos ) {
				TRACE( "hypro.datastructures.hybridAutomatonComp",
					   "Write target at position " << pos << " resulting from adding transition no. "
												   << ( pos / oldNumberTargets ) );
				auto* tPtr = labelIt->second[automatonIdx][pos / oldNumberTargets];
				auto* lPtr = locs[automatonIdx];
				// once one transition is urgent, the compose will be as well
				if ( tPtr->isUrgent() ) {
					targets[pos].urgent = true;
				}
				// assemble target location indices, required later to identify possible duplicate composed target locations
				targets[pos].targetLocationIndices.push_back(
					  getIndex( mAutomaton.mAutomata[automatonIdx].getLocations(), tPtr->getTarget() ) );

				TRACE( "hypro.datastructures.hybridAutomatonComp",
					   "Added target location index " << targets[pos].targetLocationIndices.back() );
				// cannot be undefined, otherwise the target location would not be in the location set of the automaton holding the source location
				assert( targets[pos].targetLocationIndices.back() >= 0 );
				// handling of the guard condition
				composeSynchronizedGuard( dim, targets, automatonIdx, pos, tPtr );
				// handling of the reset
				// TODO extend to interval resets
				composeSynchronizedReset( localMasters, targets, automatonIdx, pos, tPtr, lPtr );
			}  // loop over created stubs
		}	   // loop over components

		TRACE( "hypro.datastructures.hybridAutomatonComp", "Have " << targets.size() << " transition-stubs" );
		// at this point we have all guards, all resets, urgency
		// create stub for a new target location, if it does not yet exist
		for ( const auto& target : targets ) {
			auto targetPosition = std::end( mAutomaton.mLocations );
			{
				auto entryPairIt = mAutomaton.mComposedLocs.find( target.targetLocationIndices );
				if ( entryPairIt != std::end( mAutomaton.mComposedLocs ) ) {
					targetPosition = entryPairIt->second;
				} else {
					mAutomaton.mLocations.emplace_back( mAutomaton );
					auto& newLoc = mAutomaton.mLocations.back();
					newLoc.mCompositionals = target.targetLocationIndices;
					targetPosition = std::prev( std::end( mAutomaton.mLocations ) );
					mAutomaton.mComposedLocs[target.targetLocationIndices] = targetPosition;
				}
			}
			// create new transition
			std::unique_ptr<CompTransition> newTransition = std::make_unique<CompTransition>();
			//  fill properties
			newTransition->setGuard( { target.guardConstraints, target.guardConstants } );
			newTransition->setReset( { target.resetMatrix, target.resetVector } );
			newTransition->setLabels( labelIt->first );
			newTransition->setUrgent( target.urgent );
			newTransition->setSource( const_cast<ComposedLocation<Number>*>( this ) );
			newTransition->setTarget( &( *targetPosition ) );
			TRACE( "hypro.datastructures.hybridAutomatonComp",
				   "Create new synchronizing transition " << ( *newTransition.get() ) );
			mTransitions.emplace_back( std::move( newTransition ) );
		}
	}

	// update bad-states mapping during validation
	mAutomaton.setLocalBadStateMapping();
	for ( const auto& [key, condition] : mAutomaton.mLocalBadStateMapping ) {
		if ( mCompositionals[key.first] == key.second ) {
			mAutomaton.mLocalBadStates[this] = condition;
		}
	}
	mIsValid[VALIDITY::REST] = true;
}

template <typename Number>
void ComposedLocation<Number>::collectJumpComponents( const std::vector<Location<Number>*> locs,
													  std::multimap<std::size_t, Transition<Location<Number>>*>& nonSynchronizedJumps,
													  std::map<std::vector<Label>, std::vector<std::vector<Transition<Location<Number>>*>>>& synchronizedJumps ) const {
	for ( std::size_t locationIdx = 0; locationIdx < locs.size(); ++locationIdx ) {
		for ( const auto& t : locs[locationIdx]->getTransitions() ) {
			auto* tPtr = t.get();
			// synchronizing jump
			if ( !tPtr->getLabels().empty() ) {
				if ( synchronizedJumps.count( tPtr->getLabels() ) == 0 ) {
					synchronizedJumps.emplace(
						  std::make_pair( tPtr->getLabels(), std::vector<std::vector<TransitionT*>>() ) );
				}
				while ( synchronizedJumps[tPtr->getLabels()].size() <= locationIdx ) {
					synchronizedJumps[tPtr->getLabels()].push_back( std::vector<TransitionT*>{} );
				}
				synchronizedJumps[tPtr->getLabels()][locationIdx].push_back( tPtr );
				TRACE( "hypro.datastructures.hybridAutomatonComp", "Detect synchronized jump:\n"
																		 << *tPtr );
			} else {
				TRACE( "hypro.datastructures.hybridAutomatonComp", "Detect non-synchronized jump:\n"
																		 << *tPtr );
				nonSynchronizedJumps.insert( std::make_pair( locationIdx, tPtr ) );
			}
		}
	}
	// remove all synchronizing jumps where not all components can participate
	for ( auto jumpIt = std::begin( synchronizedJumps ); jumpIt != std::end( synchronizedJumps ); ) {
		if ( jumpIt->second.size() != locs.size() ||
			 std::any_of( std::begin( jumpIt->second ), std::end( jumpIt->second ),
						  []( const auto& b ) { return b.empty(); } ) ) {
#ifdef HYPRO_LOGGING
			std::stringstream labels;
			for ( const auto& lab : jumpIt->first ) {
				labels << lab << ", ";
			}
			std::stringstream jumps;
			for ( const auto& bucket : jumpIt->second ) {
				for ( const auto* tPtr : bucket ) {
					jumps << tPtr->getSource()->getName() << " -> " << tPtr->getTarget()->getName() << ", ";
				}
			}
			TRACE( "hypro.datastructures.hybridAutomatonComp", "Remove jumps\n"
																	 << jumps.str() << "\nsynchronizing on " << labels.str()
																	 << " as there are not enough partners to synchronize (have: " << jumpIt->second.size()
																	 << ", require: " << locs.size() << ")." );
#endif
			jumpIt = synchronizedJumps.erase( jumpIt );
		} else {
			++jumpIt;
		}
	}
}

template <typename Number>
void ComposedLocation<Number>::composeLocationContent( const std::vector<Location<Number>*> locs,
													   const std::map<std::string, Location<Number>*>& localMasters ) const {
	using Matrix = matrix_t<Number>;
	using Vector = vector_t<Number>;
	Matrix haFlow = Matrix::Zero( this->mAutomaton.getVariables().size() + 1,
								  this->mAutomaton.getVariables().size() + 1 );
	Matrix invariantConstraints = Matrix::Zero( 0, this->mAutomaton.getVariables().size() );
	Vector invariantConstants = Vector::Zero( 0 );
	for ( std::size_t automatonIdx = 0; automatonIdx != this->mAutomaton.mAutomata.size(); ++automatonIdx ) {
		auto* lPtr = locs[automatonIdx];
		// handling of the flow - iterate over globally available variables
		for ( std::size_t globalVIdx = 0; globalVIdx != this->mAutomaton.getVariables().size(); ++globalVIdx ) {
			auto globalVName = this->mAutomaton.getVariables()[globalVIdx];
			// if the variable is mastered
			if ( localMasters.count( globalVName ) > 0 ) {
				// if the current location is the master, simply write flow row indicated by globalVIdx, else do nothing
				if ( localMasters.at( globalVName ) == lPtr ) {
					for ( std::size_t localCol = 0;
						  localCol < lPtr->getLinearFlow().getFlowMatrix().cols(); ++localCol ) {
						if ( localCol != lPtr->getLinearFlow().getFlowMatrix().cols() - 1 ) {
							haFlow( globalVIdx, this->mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																									localCol )] ) = Number( lPtr->getLinearFlow().getFlowMatrix()( this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx],
																																								   localCol ) );
						} else {
							haFlow( globalVIdx, haFlow.cols() - 1 ) = Number( lPtr->getLinearFlow().getFlowMatrix()(
								  this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol ) );
						}
					}
				}
			} else {
				// the variable is not mastered
				// check if the current automaton has information for this variable, if not (value is -1), skip
				if ( this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] >= 0 ) {
					// the global variable is also in the local variable set, import flow, if admissible
					// maps the global var index to the row in the local flow
					auto localRow = this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
					// try to import local flow
					for ( std::size_t localCol = 0;
						  localCol < lPtr->getLinearFlow().getFlowMatrix().cols(); ++localCol ) {
						bool isConst = ( localCol == lPtr->getLinearFlow().getFlowMatrix().cols() - 1 );
						// check admissibility by checking against all other automata
						for ( std::size_t otherAutomatonIdx = 0;
							  otherAutomatonIdx != this->mAutomaton.mAutomata.size(); ++otherAutomatonIdx ) {
							// column of the same variable in the other automaton, can be -1 if the other automaton does not have this variable
							long int otherCol;
							if ( isConst ) {
								otherCol = locs[otherAutomatonIdx]->getLinearFlow().getFlowMatrix().cols() - 1;
							} else {
								otherCol = this->mAutomaton.mGlobalToLocalVars[this->mAutomaton.mLocalToGlobalVars[std::make_pair(
									  automatonIdx, localCol )]][otherAutomatonIdx];
							}
							// do not compare to one self and skip, if the other automaton does not have the variable (localCol) in its set
							// or if it does not have information about the main variable (globalIdx)
							if ( otherAutomatonIdx == automatonIdx || otherCol < 0 ||
								 this->mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx] < 0 ) {
								continue;
							}
							// the other automaton has information on this (local col) variable
							auto otherFlow = locs[otherAutomatonIdx]->getLinearFlow().getFlowMatrix();
							if ( otherFlow( this->mAutomaton.mGlobalToLocalVars[globalVIdx][otherAutomatonIdx],
											otherCol ) != lPtr->getLinearFlow().getFlowMatrix()( localRow, localCol ) ) {
								throw std::logic_error( "Flows of shared variables are not admissible" );
							}
						}
						// if we reach here, the flow is admissible for the current col
						if ( isConst ) {
							haFlow( globalVIdx, haFlow.cols() - 1 ) = Number(
								  lPtr->getLinearFlow().getFlowMatrix()( localRow, localCol ) );
						} else {
							haFlow( globalVIdx, this->mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																									localCol )] ) = Number( lPtr->getLinearFlow().getFlowMatrix()( localRow, localCol ) );
						}
					}  // loop over local variable idx
				}
			}		   // if variable is not mastered
		}			   // loop over all globally available variables

		// handling of the invariant condition
		const auto& localInvariant = locs[automatonIdx]->getInvariant();
		// only proceed, if the invariant is not trivially true (in which case it does not have a matrix and the following will fail)
		if ( !localInvariant.isTrue() ) {
			for ( std::size_t constraintIdx = 0;
				  constraintIdx < localInvariant.getMatrix().rows(); ++constraintIdx ) {
				Vector newRow = Vector::Zero( this->mAutomaton.getVariables().size() );
				for ( std::size_t localCol = 0; localCol != localInvariant.getMatrix().cols(); ++localCol ) {
					newRow( this->mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																				localCol )] ) = localInvariant.getMatrix()( constraintIdx, localCol );
				}
				appendRow( invariantConstraints, newRow );
				appendRow( invariantConstants, localInvariant.getVector()( constraintIdx ) );
			}
		}
	}  // loop over all automata in the composition

	// set the flow as composed before
	this->castawayConst().setFlow( haFlow );
	// set the invariant as composed before
	this->castawayConst().setInvariant( Condition<Number>( invariantConstraints, invariantConstants ) );
}

template <typename Number>
void ComposedLocation<Number>::composeSynchronizedGuard( unsigned long dim, std::vector<transitionStub>& targets,
														 size_t automatonIdx, size_t pos,
														 Transition<Location<Number>>* tPtr ) const {
	auto localGuard = tPtr->getGuard();
	if ( !localGuard.isTrue() ) {
		for ( std::size_t constraintIdx = 0; constraintIdx < localGuard.getMatrix().rows(); ++constraintIdx ) {
			vector_t<Number> newRow = vector_t<Number>::Zero( dim );
			for ( std::size_t localCol = 0; localCol != localGuard.getMatrix().cols(); ++localCol ) {
				newRow( mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																	  localCol )] ) = localGuard.getMatrix()( constraintIdx, localCol );
			}
			appendRow( targets[pos].guardConstraints, newRow );
			appendRow( targets[pos].guardConstants, localGuard.getVector()( constraintIdx ) );
		}
	}
}

template <typename Number>
void ComposedLocation<Number>::composeSynchronizedReset( const std::map<std::string, Location<Number>*>& localMasters,
														 std::vector<transitionStub>& targets, size_t automatonIdx,
														 size_t pos, Transition<Location<Number>>* tPtr,
														 Location<Number>* lPtr ) const {
	for ( std::size_t globalVIdx = 0; globalVIdx != mAutomaton.getVariables().size(); ++globalVIdx ) {
		auto globalVName = mAutomaton.getVariables()[globalVIdx];
		// if the variable is mastered
		if ( localMasters.count( globalVName ) > 0 ) {
			// if the current location is the master, simply write reset indicated by globalVIdx, else do nothing
			if ( localMasters.at( globalVName ) == lPtr ) {
				const auto& localReset = tPtr->getReset();
				if ( !localReset.isIdentity() ) {
					for ( std::size_t localCol = 0; localCol != localReset.getMatrix().cols(); ++localCol ) {
						targets[pos].resetMatrix( globalVIdx,
												  mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																								localCol )] ) = localReset.getMatrix()( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol );
					}
					targets[pos].resetVector( globalVIdx ) = localReset.getVector()(
						  mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] );
				}
			}
		} else {
			// the variable is not mastered
			// check if the current automaton has information for this variable, if not (value is -1), skip
			if ( mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] >= 0 ) {
				// the global variable is also in the local variable set, import reset, if admissible
				// distinguish between identity resets (which might have an empty matrix) and others
				if ( !tPtr->getReset().isIdentity() ) {
					// is not identity, i.e., does definitely have a matrix
					const auto& localResetMatrix = tPtr->getReset().getMatrix();
					const auto& localResetVector = tPtr->getReset().getVector();
					// maps the global var index to the row in the local reset
					std::size_t localRow = mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
					// import local reset
					for ( std::size_t localCol = 0; localCol != localResetMatrix.cols(); ++localCol ) {
						targets[pos].resetMatrix( globalVIdx,
												  mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																								localCol )] ) = localResetMatrix( localRow, localCol );
					}  // loop over local variable idx
					targets[pos].resetVector( globalVIdx ) = localResetVector( localRow );
				}	   // if is not identity
			}		   // if automaton does have information on this variable
		}			   // if variable is not mastered
	}				   // loop over all globally available variables for resets
}

template <typename Number>
void ComposedLocation<Number>::composeGuard( unsigned long dim, Transition<Location<Number>>* tPtr,
											 ComposedLocation<Number>::transitionStub& stub,
											 size_t automatonIdx ) const {
	const auto& localGuard = tPtr->getGuard();
	if ( !localGuard.isTrue() ) {
		for ( std::size_t constraintIdx = 0; constraintIdx < localGuard.getMatrix().rows(); ++constraintIdx ) {
			vector_t<Number> newRow = vector_t<Number>::Zero( dim );
			for ( std::size_t localCol = 0; localCol != localGuard.getMatrix().cols(); ++localCol ) {
				auto pos = mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx, localCol )];
				newRow( pos ) = localGuard.getMatrix()( constraintIdx, localCol );
			}
			appendRow( stub.guardConstraints, newRow );
			appendRow( stub.guardConstants, localGuard.getVector()( constraintIdx ) );
		}
	}
}

template <typename Number>
void ComposedLocation<Number>::composeResets( const std::map<std::string, Location<Number>*>& localMasters,
											  Transition<Location<Number>>* tPtr, transitionStub& stub,
											  std::size_t automatonIdx, Location<Number>* lPtr ) const {
	// TODO extend to interval resets
	for ( std::size_t globalVIdx = 0; globalVIdx != this->mAutomaton.getVariables().size(); ++globalVIdx ) {
		auto globalVName = this->mAutomaton.getVariables()[globalVIdx];
		// if the variable is mastered
		// TODO check for the right variable
		if ( localMasters.count( globalVName ) > 0 ) {
			// if the current location is the master, simply write reset indicated by globalVIdx, else do nothing
			if ( localMasters.at( globalVName ) == lPtr ) {
				const auto& localReset = tPtr->getReset();
				if ( !localReset.isIdentity() ) {
					for ( std::size_t localCol = 0; localCol != localReset.getMatrix().cols(); ++localCol ) {
						stub.resetMatrix( globalVIdx,
										  this->mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																							  localCol )] ) = localReset.getMatrix()( this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx], localCol );
					}
					stub.resetVector( globalVIdx ) = localReset.getVector()(
						  this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] );
				}
			}
		} else {
			// the variable is not mastered
			// check if the current automaton has information for this variable, if not (value is -1), skip
			if ( this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx] >= 0 ) {
				// the global variable is also in the local variable set, import reset, if admissible
				// distinguish between identity resets (which might have an empty matrix) and others
				if ( tPtr->getReset().isIdentity() ) {
					// do nothing
				} else {
					// is not identity, i.e., does definitely have a matrix
					const auto& localResetMatrix = tPtr->getReset().getMatrix();
					const auto& localResetVector = tPtr->getReset().getVector();
					// maps the global var index to the row in the local reset
					std::size_t localRow = this->mAutomaton.mGlobalToLocalVars[globalVIdx][automatonIdx];
					// import local reset
					for ( std::size_t localCol = 0; localCol != localResetMatrix.cols(); ++localCol ) {
						stub.resetMatrix( globalVIdx,
										  this->mAutomaton.mLocalToGlobalVars[std::make_pair( automatonIdx,
																							  localCol )] ) = localResetMatrix( localRow, localCol );
					}  // loop over local variable idx
					stub.resetVector( globalVIdx ) = localResetVector( localRow );
				}	   // if is identity - else
			}		   // if automaton does have information on this variable
		}			   // if variable is not mastered
	}				   // loop over all globally available variables for resets
}

template <typename Number>
std::map<std::string, Location<Number>*>
ComposedLocation<Number>::getMasterLocations( const std::vector<Location<Number>*>& locs ) const {
	std::map<std::string, Location<Number>*> localMasters;
	for ( const auto& var : this->mAutomaton.getVariables() ) {
		auto it = this->mAutomaton.mMasters.find( var );
		if ( it != std::end( this->mAutomaton.mMasters ) ) {
			// check, if one of the locations is also contained in the selected masters (it) for this variable
			bool found = false;
			for ( const auto& [componentIdx, locationIdx] : it->second ) {
				if ( this->mCompositionals[componentIdx] == locationIdx ) {
					if ( found ) {
						throw std::logic_error( "Two locations are mastering the same variable" );
					}
					found = true;
					localMasters[it->first] = locs[componentIdx];
				}
			}
		}
	}
	return localMasters;
}

template <typename Number>
void ComposedLocation<Number>::validateName() const {
	if ( !mIsValid[VALIDITY::NAME] ) {
		std::stringstream ss;
		bool first = true;
		for ( std::size_t componentIdx = 0; componentIdx < mCompositionals.size(); ++componentIdx ) {
			if ( first ) {
				first = false;
			} else {
				ss << mAutomaton.nameDelimiter;
			}
			ss << ( mAutomaton.mAutomata[componentIdx].getLocationByIndex( mCompositionals[componentIdx] ) )->getName();
			castawayConst().setName( ss.str() );
		}
		// register location name in lookup-table
		mAutomaton.mLocationNames[Location<Number>::mName] = const_cast<typename HybridAutomatonComp<Number>::LocationType*>( this );
		mIsValid[VALIDITY::NAME] = true;
	}
}

template <typename Number>
std::vector<typename HybridAutomatonComp<Number>::LocationType*>
HybridAutomatonComp<Number>::getLocations() const {
	if ( !fullLazy ) {
		createAllLocations();
	}
	std::vector<LocationType*> res;
	// collect all currently discovered and validated locations, make sure not to validate further ones, as this will unroll the whole automaton
	for ( auto locIt = std::begin( mLocations ); locIt != std::end( mLocations ); ++locIt ) {
		// if ( locIt->isValid() ) {
		res.push_back( &( *locIt ) );
		//}
	}
	return res;
}

template <typename Number>
typename HybridAutomatonComp<Number>::LocationType*
HybridAutomatonComp<Number>::getLocation( const std::size_t hash ) const {
	for ( const auto& l : mLocations ) {
		if ( l->hash() == hash ) {
			return &l;
		}
	}
	return nullptr;
}

template <typename Number>
typename HybridAutomatonComp<Number>::LocationType*
HybridAutomatonComp<Number>::getLocation( const std::string& name ) const {
	auto res = mLocationNames.find( name );
	if ( res != std::end( mLocationNames ) ) {
		return res->second;
	} else {
		if ( fullLazy ) {
			return nullptr;
		} else {
			// create the missing location
			std::vector<std::size_t> compositeIndices = getIndicesByName( name );
			auto locationIt = addLocationStubByIndices( compositeIndices );
			locationIt->validate();
			assert( mLocationNames.find( name ) != mLocationNames.end() );
			return mLocationNames.find( name )->second;
		}
	}
}

template <typename Number>
typename HybridAutomatonComp<Number>::LocationType*
HybridAutomatonComp<Number>::getLocationByIndex( std::size_t index ) const {
	// find the correct composite, we assume the given ordering induced by the order of addition of components
	// initialize to zero
	std::vector<std::size_t> locationIndices{ mAutomata.size(), 0 };
	int componentIndex = mAutomata.size() - 1;
	while ( index != 0 ) {
		if ( index > mAutomata[componentIndex].getLocations().size() ) {
			locationIndices[componentIndex] = index % mAutomata[componentIndex].getLocations().size();
			index -= index / mAutomata[componentIndex].getLocations().size();
			--componentIndex;
		} else {
			locationIndices[componentIndex] = index;
			break;
		}
		if ( index > 0 && componentIndex < 0 ) {
			throw std::logic_error( "Passed index is too large." );
		}
	}
	auto it = addLocationStubByIndicesSafe( locationIndices );
	return &( *it );
}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap&
HybridAutomatonComp<Number>::getInitialStates() const {
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
				while ( idx < mAutomata[automatonIdx].getLocations().size() &&
						( *mAutomata[automatonIdx].getLocations()[idx] ) !=
							  *std::next( initialStateIt, combination[automatonIdx] )->first ) {
					++idx;
				}
				// locationIndices.push_back( getIndex( mAutomata[automatonIdx].getLocations(), std::next( initialStateIt, combination[automatonIdx] )->first ) );
				locationIndices.push_back( idx );
				assert( locationIndices.back() >= 0 );
				const auto& localInitialCondition = std::next( initialStateIt, combination[automatonIdx] )->second;
				if ( !localInitialCondition.isTrue() ) {
					// iterate over local constraints, convert to global ones
					for ( std::size_t constraintIdx = 0;
						  constraintIdx < localInitialCondition.getMatrix().rows(); ++constraintIdx ) {
						vector_t<Number> newRow = vector_t<Number>::Zero( getVariables().size() );
						for ( std::size_t localCol = 0;
							  localCol != localInitialCondition.getMatrix().cols(); ++localCol ) {
							newRow( mLocalToGlobalVars[std::make_pair( automatonIdx,
																	   localCol )] ) = localInitialCondition.getMatrix()( constraintIdx, localCol );
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
					mLocations.emplace_back( std::move( tmp ) );
					mComposedLocs[locationIndices] = std::prev( std::end( mLocations ) );
				}
			}
			assert( mComposedLocs.count( locationIndices ) > 0 );
			// write initial states
			ComposedLocation<Number>* lPtr = &( *mComposedLocs[locationIndices] );
			mInitialStates[lPtr] = Condition<Number>( initialMatrix, initialVector );
		}
		mCachesValid[CACHE::INITIALSTATES] = true;
	}
	return mInitialStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::locationConditionMap&
HybridAutomatonComp<Number>::getLocalBadStates() const {
	if ( !mCachesValid[CACHE::LOCALBADSTATES] ) {
		// collect all local bad states from all automata. Each existing (valid) location, check if one of its components
		// is a local bad state - if so, update the list
		setLocalBadStateMapping();

		for ( const auto& location : mLocations ) {
			// detect potentially relevant locations that require testing
			if ( location.isValid() && mLocalBadStates.count( &location ) < 0 ) {
				for ( const auto& [key, condition] : mLocalBadStateMapping ) {
					if ( location.mCompositionals[key.first] == key.second ) {
						mLocalBadStates[&location] = condition;
					}
				}
			}
		}

		mCachesValid[CACHE::LOCALBADSTATES] = true;
	}
	return mLocalBadStates;
}

template <typename Number>
const typename HybridAutomatonComp<Number>::conditionVector&
HybridAutomatonComp<Number>::getGlobalBadStates() const {
	if ( !mCachesValid[CACHE::VARIABLES] ) {
		setVariableMapping();
	}
	if ( !mCachesValid[CACHE::GLOBALBADSTATES] ) {
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			for ( const auto& badStateCondition : mAutomata[automatonIdx].getGlobalBadStates() ) {
				matrix_t<Number> constraints = matrix_t<Number>::Zero( badStateCondition.getMatrix().rows(),
																	   this->dimension() );
				vector_t<Number> constants = vector_t<Number>::Zero( badStateCondition.getMatrix().rows() );
				for ( Eigen::Index row = 0; row < badStateCondition.getMatrix().rows(); ++row ) {
					for ( Eigen::Index col = 0; col < badStateCondition.getMatrix().cols(); ++col ) {
						// if the automaton does not have these variables, we assume it knows the global indices already
						bool hasVariable = mLocalToGlobalVars.find( std::make_pair( automatonIdx, col ) ) !=
										   mLocalToGlobalVars.end();
						if ( hasVariable ) {
							constraints( row, mLocalToGlobalVars.at(
													std::make_pair( automatonIdx, col ) ) ) = badStateCondition.getMatrix()( row, col );
						} else {
							constraints( row, col ) = badStateCondition.getMatrix()( row, col );
						}
					}
					constants( row ) = badStateCondition.getVector()( row );
				}
				mGlobalBadStates.emplace_back( constraints, constants );
			}
		}
		mCachesValid[CACHE::GLOBALBADSTATES] = true;
	}
	return mGlobalBadStates;
}

template <typename Number>
std::size_t HybridAutomatonComp<Number>::dimension() const {
	return getVariables().size();
}

template <typename Number>
const std::vector<std::string>& HybridAutomatonComp<Number>::getVariables() const {
	if ( !mCachesValid[CACHE::VARIABLES] ) {
		mVariables.clear();
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			for ( const auto& var : mAutomata[automatonIdx].getVariables() ) {
				if ( std::find( std::begin( mVariables ), std::end( mVariables ), var ) == std::end( mVariables ) ) {
					mVariables.push_back( var );
				}
			}
		}

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
				mGlobalToLocalVars[globalIdx][automatonIdx] = getIndex( mAutomata[automatonIdx].getVariables(),
																		mVariables[globalIdx] );
				TRACE( "hypro.datastructures", "Global variable " << mVariables[globalIdx] << " at pos " << globalIdx
																  << " is equal to variable at pos "
																  << mGlobalToLocalVars[globalIdx][automatonIdx]
																  << " of component " << automatonIdx );
			}
		}
		// establish reverse mapping
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			for ( std::size_t localIdx = 0; localIdx < mAutomata[automatonIdx].getVariables().size(); ++localIdx ) {
				mLocalToGlobalVars[std::make_pair( automatonIdx, localIdx )] = getIndex( mVariables,
																						 mAutomata[automatonIdx].getVariables()[localIdx] );
			}
		}
	}
}

template <typename Number>
void HybridAutomatonComp<Number>::invalidateCaches() const {
	mLocations.clear();
	mLocationNames.clear();
	mInitialStates.clear();
	mLocalBadStates.clear();
	mGlobalBadStates.clear();
	mVariables.clear();
	mSharedVars.clear();
	mGlobalToLocalVars.clear();
	mLocalToGlobalVars.clear();
	mComposedLocs.clear();
	mLocalBadStateMapping.clear();
	mLabels.clear();
	mCachesValid = std::vector<bool>( CACHE::Count, false );
}

template <typename Number>
void HybridAutomatonComp<Number>::setLocalBadStateMapping() const {
	if ( !mCachesValid[CACHE::LOCALBADSTATEMAPPING] ) {
		mLocalBadStateMapping.clear();
		for ( std::size_t automatonIdx = 0; automatonIdx < mAutomata.size(); ++automatonIdx ) {
			auto locs = mAutomata[automatonIdx].getLocations();
			for ( const auto& [location, condition] : mAutomata[automatonIdx].getLocalBadStates() ) {
				long int locationIdx = -1;
				for ( locationIdx = 0; locationIdx < locs.size(); ++locationIdx ) {
					if ( locs[locationIdx] == location ) {
						break;
					}
				}
				if ( locationIdx < 0 ) {
					throw std::logic_error( "Index for location " + location->getName() + " could not be found." );
				}
				mLocalBadStateMapping[std::make_pair( automatonIdx, locationIdx )] = condition;
			}
		}
		mCachesValid[CACHE::LOCALBADSTATEMAPPING] = true;
	}
}

template <typename Number>
typename HybridAutomatonComp<Number>::Locations::iterator
HybridAutomatonComp<Number>::addLocationStubByIndicesSafe( const std::vector<std::size_t>& indices ) const {
	auto res = mComposedLocs.find( indices );
	if ( res == std::end( mComposedLocs ) ) {
		return addLocationStubByIndices( indices );
	} else {
		return res->second;
	}
}

template <typename Number>
typename HybridAutomatonComp<Number>::Locations::iterator
HybridAutomatonComp<Number>::addLocationStubByIndices( const std::vector<std::size_t>& indices ) const {
	ComposedLocation<Number> tmp{ *this };
	tmp.mCompositionals = indices;
	mLocations.emplace_back( std::move( tmp ) );
	mComposedLocs[indices] = std::prev( std::end( mLocations ) );
	return std::prev( mLocations.end() );
}

template <typename Number>
void HybridAutomatonComp<Number>::createAllLocations() const {
	std::vector<std::size_t> numberLocations;
	for ( std::size_t componentIdx = 0; componentIdx < mAutomata.size(); ++componentIdx ) {
		numberLocations.push_back( mAutomata[componentIdx].getNumberLocations() );
	}

	auto perm = hypro::Combinator{ numberLocations, mAutomata.size() };
	while ( !perm.end() ) {
		auto indices = perm();
		/*std::cout << "Add location for indices ";
		for ( auto i : indices ) {
			std::cout << i << "  ";
		}
		std::cout << std::endl;*/
		addLocationStubByIndicesSafe( indices );
	}
}

template <typename Number>
std::vector<std::size_t> HybridAutomatonComp<Number>::getIndicesByName( std::string name ) const {
	std::vector<std::size_t> res;
	std::size_t position{ 0 };
	std::size_t automatonIdx{ 0 };
	while ( ( position = name.find( nameDelimiter ) ) != std::string::npos ) {
		if ( automatonIdx >= mAutomata.size() ) {
			throw std::logic_error( "Too many subnames in passed location name " + name + ", may be maximal " + std::to_string( mAutomata.size() ) );
		}
		auto* lPtr = mAutomata[automatonIdx].getLocationByName( name.substr( 0, position ) );
		if ( lPtr == nullptr ) {
			throw std::logic_error( "Location " + name.substr( 0, position ) + " not present in automaton " + std::to_string( automatonIdx ) );
		}
		res.emplace_back( mAutomata[automatonIdx].getLocationIndex( lPtr ) );
		name.erase( 0, position + nameDelimiter.length() );
	}
	return res;
}

}  // namespace hypro
