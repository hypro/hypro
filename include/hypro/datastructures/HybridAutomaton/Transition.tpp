/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Transition.h"

namespace hypro {

template <typename LocationType>
std::size_t Transition<LocationType>::hash() const {
	if ( mHash == 0 ) {
		mHash = std::hash<Transition<LocationType>>()( *this );
	}
	return mHash;
}

template <typename LocationType>
std::string Transition<LocationType>::getDotRepresentation( const std::vector<std::string>& vars ) const {
	std::stringstream o;
	o << this->getSource()->hash() << " -> " << this->getTarget()->hash();
	if ( getLabels().size() != 0 || ( mReset.size() > 0 && !mReset.isIdentity() ) || mGuard.size() != 0 ) {
		o << "[label=< <TABLE>";
		// sync labels
		for ( const auto& l : getLabels() ) {
			o << "<TR><TD>" << l << "</TD></TR>";
		}
		// guard
		o << mGuard.getDotRepresentation( vars );
		// reset
		if ( mReset.size() > 0 && !mReset.isIdentity() ) {
			const matrix_t<Number>& reset = mReset.getMatrix();
			o << "<TR><TD ROWSPAN=\"" << reset.rows() << "\">";
			for ( unsigned i = 0; i < reset.rows(); ++i ) {
				o << vars[i] << "' = ";
				bool allZero = true;
				for ( unsigned j = 0; j < reset.cols(); ++j ) {
					if ( reset( i, j ) != 0 ) {
						o << reset( i, j ) << "*" << vars[j] << " + ";
						allZero = false;
					}
				}
				if ( mReset.getVector()( i ) != 0 || allZero ) o << " + " << mReset.getVector()( i );
				if ( i < reset.rows() - 1 )
					o << "<BR/>";
			}
			o << "</TD>";
			o << "</TR>";
		}
		o << "</TABLE>>];";
	}
	o << "\n";
	return o.str();
}

template <typename LocationType>
bool Transition<LocationType>::isComposedOf( const Transition<LocationType>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars ) const {
	// compare source and target location
	if ( this->getSource()->getName().find( rhs.getSource()->getName() ) == std::string::npos ||
		 this->getTarget()->getName().find( rhs.getTarget()->getName() ) == std::string::npos ) {
		// std::cout << "source or target did not match." << std::endl;
		return false;
	}

	// check labels
	for ( const auto& l1 : rhs.getLabels() ) {
		bool found = false;
		for ( const auto l2 : this->getLabels() ) {
			if ( l2 == l1 ) {
				found = true;
				break;
			}
		}
		if ( !found ) {
			// std::cout << "Labels did not match." << std::endl;
			return false;
		}
	}

	// compare guard constraints. As the order is not fixed, we consider each row, one by one and try to match rows (outer two loops).
	// This is similar to the invariant comparison in Location.tpp
	if ( rhs.getGuard().size() != 0 ) {
		if ( this->getGuard().size() == 0 ) {
			// std::cout << "guards do not match." << std::endl;
			return false;
		}
		// std::cout << "Compare guards " << rhs.getGuard().getMatrix() << " <= " << rhs.getGuard().getVector() << " and " << this->getGuard().getMatrix() << " <= " << this->getInvariant().getVector() << std::endl;

		// try to find matching rows.
		for ( Eigen::Index rowI = 0; rowI != rhs.getGuard().getMatrix().rows(); ++rowI ) {
			// std::cout << "original row " << rowI << std::endl;
			bool foundConstraint = false;
			for ( Eigen::Index rowPos = 0; rowPos != this->getGuard().getMatrix().rows(); ++rowPos ) {
				bool allMatched = true;
				for ( Eigen::Index colI = 0; colI != rhs.getGuard().getMatrix().cols(); ++colI ) {
					// std::cout << "original col " << colI << std::endl;
					//  find corresponding positions in the current flow matrix
					Eigen::Index colPos = 0;
					while ( thisVars[colPos] != rhsVars[colI] ) ++colPos;
					// std::cout << "matching col " << colPos << std::endl;
					if ( this->getGuard().getMatrix()( rowPos, colPos ) != rhs.getGuard().getMatrix()( rowI, colI ) ) {
						allMatched = false;
						break;
					}
				}
				// also compare constants.
				if ( allMatched ) {
					if ( this->getGuard().getVector()( rowPos ) == rhs.getGuard().getVector()( rowI ) ) {
						// std::cout << "matched row " << rowPos << std::endl;
						foundConstraint = true;
						break;
					}
				}
			}
			if ( !foundConstraint ) {
				// std::cout << "Cound not find invariant constraint." << std::endl;
				return false;
			}
		}
	}

	// compare reset function:
	// Find corresponding rows, then compare relevant entries.
	for ( Eigen::Index rowI = 0; rowI != rhs.getReset().getMatrix().rows(); ++rowI ) {
		Eigen::Index rowPos = 0;
		// std::cout << "Search for: " << rhsVars[rowI] << std::endl;
		while ( thisVars[rowPos] != rhsVars[rowI] ) ++rowPos;
		for ( Eigen::Index colI = 0; colI != rhs.getReset().getMatrix().cols(); ++colI ) {
			// find corresponding positions in the current reset matrix
			Eigen::Index colPos = 0;
			while ( thisVars[colPos] != rhsVars[colI] ) ++colPos;
			// std::cout << "rowPos " << rowPos << ", rowI " << rowI << ", colPos " << colPos << ", colI " << colI << std::endl;
			if ( this->getReset().getMatrix()( rowPos, colPos ) != rhs.getReset().getMatrix()( rowI, colI ) ) {
				// std::cout << "reset matrix entries do not match." << std::endl;
				return false;
			}
		}

		// compare constant part (b)
		if ( this->getReset().getVector()( rowPos ) != rhs.getReset().getVector()( rowI ) ) {
			// std::cout << "constant parts do not match." << std::endl;
			return false;
		}
	}

	return true;
}

template <typename LocationType>
Condition<typename Transition<LocationType>::Number> Transition<LocationType>::getJumpEnablingSet() {
	if ( mJumpEnablingSet ) {
		return mJumpEnablingSet.value();
	}
	const auto& guard = this->getGuard();
	const auto& targetInvariant = this->getTarget()->getInvariant();
	if ( guard.isFalse() ) {
		return guard;
	} else if ( targetInvariant.isFalse() ) {
		return targetInvariant;
	}

	if ( guard.isTrue() && targetInvariant.isTrue() ) {
		return guard;
	}

	matrix_t<Number> guardMatrix;
	vector_t<Number> guardVector;
	if ( !guard.isTrue() ) {
		guardMatrix = guard.getMatrix();
		guardVector = guard.getVector();
	}
	matrix_t<Number> invMatrix;
	vector_t<Number> invVector;
	if ( !targetInvariant.isTrue() ) {
		if ( this->getReset().isIdentity() ) {
			invMatrix = targetInvariant.getMatrix();
			invVector = targetInvariant.getVector();
		} else {
			invMatrix = targetInvariant.getMatrix() * this->getReset().getMatrix();
			invVector = targetInvariant.getVector() - targetInvariant.getMatrix() * this->getReset().getVector();
		}
	}

	if ( guard.isTrue() && !targetInvariant.isTrue() ) {
		mJumpEnablingSet = Condition<Number>( invMatrix, invVector );
	} else if ( !guard.isTrue() && targetInvariant.isTrue() ) {
		mJumpEnablingSet = Condition<Number>( guardMatrix, guardVector );
	} else {
		assert( guardMatrix.cols() == invMatrix.cols() );
		matrix_t<Number> resMatrix( guardMatrix.rows() + invMatrix.rows(), guardMatrix.cols() );
		vector_t<Number> resVector( guardMatrix.rows() + invMatrix.rows() );
		resMatrix.topRows( guardMatrix.rows() ) = guardMatrix;
		resMatrix.bottomRows( invMatrix.rows() ) = invMatrix;
		resVector.head( guardVector.rows() ) = guardVector;
		resVector.tail( invVector.rows() ) = invVector;

		// remove redundancy
		Optimizer<Number> opt( resMatrix, resVector );
		auto redundantRows = opt.redundantConstraints();
		resMatrix = removeRows( resMatrix, redundantRows );
		resVector = removeRows( resVector, redundantRows );
		Condition<Number> res( resMatrix, resVector );
		mJumpEnablingSet = res;
	}
	return mJumpEnablingSet.value();
}

template <typename Number, typename LocationType>
std::unique_ptr<Transition<LocationType>> parallelCompose( const Transition<LocationType>* lhsT, const Transition<LocationType>* rhsT, const std::vector<std::string>& lhsVar, const std::vector<std::string>& rhsVar, const std::vector<std::string>& haVar, const HybridAutomaton<Number>& ha, const std::set<Label> lhsLabels, const std::set<Label> rhsLabels, const std::map<std::string, std::vector<LocationType*>>& masters ) {
	assert( haVar.size() >= lhsVar.size() );
	assert( haVar.size() >= rhsVar.size() );

	TRACE( "hypro.datastructures", "Parallel composition of " << *lhsT << "\n\n and \n\n"
															  << *rhsT );

	// Transition<LocationType>* t = new Transition<LocationType>();
	// std::unique_ptr<Transition<LocationType>> t = new Transition<LocationType>()
	std::unique_ptr<Transition<LocationType>> t = std::make_unique<Transition<LocationType>>();

	// set target and source. If they do not exist, this means that the combined location was not admissible for some reason and thus, the transition also cannot be added.
	// TODO: returning nullptr in case the locations do not exist seems like a hotfix for now, as it indicates that something went wrong elsewhere.
	auto* source = ha.getLocation( lhsT->getSource()->getName() + '_' + rhsT->getSource()->getName() );
	auto* target = ha.getLocation( lhsT->getTarget()->getName() + '_' + rhsT->getTarget()->getName() );
	if ( source != nullptr && target != nullptr ) {
		t->setTarget( target );
		t->setSource( source );
	} else {
		return nullptr;
	}

	// set labels
	if ( lhsT->getLabels() == rhsT->getLabels() ) {
		// transitions agree on their synchronization labels
		t->setLabels( lhsT->getLabels() );
	}
	// TODO Stefan: Why did we come up with these cases? If you can find a reason, include them again, but add detailed documentation, because I cannot understand this right now
	// TODO Stefan, update: This might be, if we have 3 or more automata to synchronize. Idea: Argue only about labels that both automata agree on, keep the rest (unsynchronized).
	// TODO Stefan, update: The set of labels of an automaton should be a superset of the set of labels it uses on its transitions.
	/*else if ( !( lhsT->getLabels().empty() ) and rhsLabels.set::count( *( lhsT->getLabels().begin() ) ) == 0 and rhsT->getLabels().empty() ) {
		//
		t->setLabels( lhsT->getLabels() );
	} else if ( !( rhsT->getLabels().empty() ) and lhsLabels.set::count( *( rhsT->getLabels().begin() ) ) == 0 and lhsT->getLabels().empty() ) {
		// std::cout << "c" << std::endl;
		t->setLabels( rhsT->getLabels() );
	}*/
	else {
		// the label sets do not agree, i.e., they are not both empty or not both the same, delete the transition candidate t
		return nullptr;
	}

	// quick test for shared resets - should be equal, otherwise do not parallel compose.
	// mapping from resultIndex to pair lhsIndex, rhsIndex of the shared variables.
	std::map<unsigned, std::pair<unsigned, unsigned>> sharedVars;
	unsigned idx = 0;
	for ( const auto& var : haVar ) {
		// identify a shared variable dimension.
		if ( std::find( lhsVar.begin(), lhsVar.end(), var ) != lhsVar.end() && std::find( rhsVar.begin(), rhsVar.end(), var ) != rhsVar.end() ) {
			unsigned lhsIdx = 0;
			unsigned rhsIdx = 0;
			while ( lhsVar[lhsIdx] != var ) ++lhsIdx;
			while ( rhsVar[rhsIdx] != var ) ++rhsIdx;
			sharedVars[idx] = std::make_pair( lhsIdx, rhsIdx );
			// std::cout << "Shared variable " << var << " at pos " << idx << " with original positions " << lhsIdx << ", " << rhsIdx << std::endl;
		}
		++idx;
	}
	// quick check for incompatible resets on variables that are reset but do not have a master
	for ( const auto& varTuple : sharedVars ) {
		for ( const auto& other : sharedVars ) {
			if ( masters.count( haVar[varTuple.first] ) == 0 && lhsT->getReset().size() != 0 && rhsT->getReset().size() != 0 ) {
				// std::cout << "Compare resets: " << lhsT->getReset().getMatrix() << " and " << rhsT->getReset().getMatrix() << std::endl;
				// std::cout << "Compare resets: " << lhsT->getReset().getVector() << " and " << rhsT->getReset().getVector() << std::endl;
				if ( lhsT->getReset().getMatrix()( varTuple.second.first, other.second.first ) != rhsT->getReset().getMatrix()( varTuple.second.second, other.second.second ) || lhsT->getReset().getVector()( varTuple.second.first ) != rhsT->getReset().getVector()( varTuple.second.second ) ) {
					// std::cout << "Delete." << std::endl;
					// delete t;
					return nullptr;
				}
			}
		}
	}

	// set urgent
	//  Todo: is it not the case that a composed transition is urgent as soon as one of its participating transitions is urgent?
	t->setUrgent( lhsT->isUrgent() || rhsT->isUrgent() );

	auto guard_lhsvars = lhsVar;
	auto guard_rhsvars = rhsVar;
	auto reset_lhsvars = lhsVar;
	auto reset_rhsvars = rhsVar;
	for ( const auto& var : haVar ) {
		if ( masters.count( var ) > 0 ) {
			// guard
			if ( std::find( std::begin( masters.at( var ) ), std::end( masters.at( var ) ), lhsT->getSource() ) != std::end( masters.at( var ) ) ) {
				auto it = std::find( std::begin( guard_rhsvars ), std::end( guard_rhsvars ), var );
				if ( it != std::end( guard_rhsvars ) ) {
					guard_rhsvars.erase( it );
				}
			} else if ( std::find( std::begin( masters.at( var ) ), std::end( masters.at( var ) ), rhsT->getSource() ) != std::end( masters.at( var ) ) ) {
				auto it = std::find( std::begin( guard_lhsvars ), std::end( guard_lhsvars ), var );
				if ( it != std::end( guard_lhsvars ) ) {
					guard_lhsvars.erase( it );
				}
			}
			// reset
			if ( std::find( std::begin( masters.at( var ) ), std::end( masters.at( var ) ), lhsT->getTarget() ) != std::end( masters.at( var ) ) ) {
				auto it = std::find( std::begin( reset_rhsvars ), std::end( reset_rhsvars ), var );
				if ( it != std::end( reset_rhsvars ) ) {
					reset_rhsvars.erase( it );
				}
			} else if ( std::find( std::begin( masters.at( var ) ), std::end( masters.at( var ) ), rhsT->getTarget() ) != std::end( masters.at( var ) ) ) {
				auto it = std::find( std::begin( reset_lhsvars ), std::end( reset_lhsvars ), var );
				if ( it != std::end( reset_lhsvars ) ) {
					reset_lhsvars.erase( it );
				}
			}
		}
	}

	// set guard
	auto haGuard = combine( lhsT->getGuard(), rhsT->getGuard(), haVar, lhsVar, rhsVar );
	t->setGuard( haGuard );

	// set reset
	// std::cout << "Reset, combine matrices: " << std::endl;
	auto haReset = combine( lhsT->getReset(), rhsT->getReset(), haVar, reset_lhsvars, reset_rhsvars );
	// std::cout << "New reset function: " << haReset << std::endl;

	t->setReset( haReset );

	// set aggregation
	t->setAggregation( lhsT->getAggregation() );

	return t;
}

}  // namespace hypro
