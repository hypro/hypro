#include "Condition.h"

namespace hypro {

template <typename Number>
Condition<Number>::Condition( const std::vector<std::variant<ConstraintSetT<Number>>>& sets ) {
	for ( const auto& item : sets ) {
		mConstraints.push_back( std::get<ConstraintSetT<Number>>( item ) );
	}
	mConditionIsBox = std::vector<TRIBOOL>{ mConstraints.size(), TRIBOOL::NSET };
	mHash = 0;
}

template <typename Number>
bool Condition<Number>::isAxisAligned() const {
	for ( std::size_t i = 0; i < mConstraints.size(); ++i ) {
		if ( !isAxisAligned( i ) ) {
			return false;
		}
	}
	return true;
}

template <typename Number>
bool Condition<Number>::isAxisAligned( std::size_t i ) const {
	checkAxisAligned( i );
	if ( mConditionIsBox[i] == TRIBOOL::FALSE ) {
		return false;
	}
	return true;
}

template <typename Number>
void Condition<Number>::setMatrix( const matrix_t<Number>& m, std::size_t I ) {
	while ( I >= mConstraints.size() ) {
		mConstraints.push_back( ConstraintSetT<Number>() );
	}
	mConstraints[I].rMatrix() = m;
	DEBUG( "hypro.datastructures", "Set matrix at pos " << I << ", mConstraints.size() = " << mConstraints.size() );
	mConditionIsBox = std::vector<TRIBOOL>{ mConstraints.size(), TRIBOOL::NSET };
	mHash = 0;
}

template <typename Number>
void Condition<Number>::setVector( const vector_t<Number>& v, std::size_t I ) {
	while ( I > mConstraints.size() ) {
		mConstraints.push_back( ConstraintSetT<Number>() );
	}
	mConstraints[I].rVector() = v;
	DEBUG( "hypro.datastructures", "Set vector at pos " << I << ", mConstraints.size() = " << mConstraints.size() );
	mConditionIsBox = std::vector<TRIBOOL>{ mConstraints.size(), TRIBOOL::NSET };
	mHash = 0;
}

template <typename Number>
std::size_t Condition<Number>::hash() const {
	if ( mHash == 0 ) {
		mHash = std::hash<Condition<Number>>()( *this );
	}
	return mHash;
}

template <typename Number>
std::string Condition<Number>::getDotRepresentation( const std::vector<std::string>& vars ) const {
	std::stringstream o;
	if ( mConstraints.size() > 0 ) {
		const matrix_t<Number>& constraints = mConstraints.begin()->matrix();
		o << "<TR><TD ROWSPAN=\"" << constraints.rows() << "\">";
		for ( unsigned i = 0; i < constraints.rows(); ++i ) {
			for ( unsigned j = 0; j < constraints.cols(); ++j ) {
				if ( constraints( i, j ) != 0 ) {
					o << constraints( i, j ) << "*" << vars[j] << " + ";
				}
			}
			o << " &lt;= " << mConstraints.begin()->vector()( i );
			if ( i < constraints.rows() - 1 )
				o << "<BR/>";
		}
		o << "</TD>";
		o << "</TR>";
	}
	return o.str();
}

template <typename Number>
Condition<Number> combine(
	  const Condition<Number>& lhs, const Condition<Number>& rhs,
	  const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar ) {
	if ( lhs.size() == 0 && rhs.size() == 0 ) {
		return Condition<Number>();
	}

	matrix_t<Number> lhsMatrix = matrix_t<Number>::Zero( 0, lhsVar.size() );
	matrix_t<Number> rhsMatrix = matrix_t<Number>::Zero( 0, rhsVar.size() );
	;
	vector_t<Number> lhsVector = vector_t<Number>::Zero( 0 );
	vector_t<Number> rhsVector = vector_t<Number>::Zero( 0 );
	;

	if ( lhs.size() != 0 ) {
		lhsMatrix = lhs.getMatrix();
		lhsVector = lhs.getVector();
	}
	if ( rhs.size() != 0 ) {
		rhsMatrix = rhs.getMatrix();
		rhsVector = rhs.getVector();
	}

	matrix_t<Number> newMat = combine( lhsMatrix, rhsMatrix, haVar, lhsVar, rhsVar );
	vector_t<Number> newVec = combine( lhsVector, rhsVector );

	/*vector_t<Number>::Zero(lhsInv.getVector().size()+rhsInv.getVector().size());
	newVec.head(lhsInv.getVector().size()) = lhsInv.getVector();
	newVec.tail(rhsInv.getVector().size()) = rhsInv.getVector();*/

	return Condition<Number>( newMat, newVec );
}

template <typename Number>
void Condition<Number>::decompose( const std::vector<std::vector<std::size_t>>& partition ) {
	if ( mConstraints.size() > 1 ) {
		//already decomposed/empty constraints
		return;
	} else if ( mConstraints.size() == 0 && partition.size() > 0 ) {
		//fill mConstaints with empty constraint sets
		std::vector<ConstraintSetT<Number>> newCset;
		for ( std::size_t i = 0; i < partition.size(); i++ ) {
			ConstraintSetT<Number> res = ConstraintSetT<Number>();
			newCset.push_back( res );
		}
		mConstraints = newCset;
		mConditionIsBox = std::vector<TRIBOOL>{ mConstraints.size(), TRIBOOL::NSET };
		mHash = 0;
		return;
	}

	ConstraintSetT<Number> cset = mConstraints.at( 0 );
	DEBUG( "hypro.datastructures", "Constraint Set before: \n " << cset );

	matrix_t<Number> constraintsOld( cset.matrix() );
	vector_t<Number> constantsOld( cset.vector() );

	std::vector<ConstraintSetT<Number>> newCset;
	// for each set {i,j,..., k} select each constraint that defines over {i,j,k etc.}
	for ( auto set : partition ) {
#ifdef HYPRO_LOGGING
		DEBUG( "hypro.datastructures", "decompose constraint for set: {" );
		for ( auto entry : set ) {
			DEBUG( "hypro.datastructures", "" << entry << ", " );
		}
		DEBUG( "hypro.datastructures", "}" );
#endif

		// for each row of the constraints check if it contains an entry for one of the variables of the set
		// and add the corresponding rows to a list of indices that are later added to a matrix
		std::vector<Eigen::Index> indicesToAdd;
		for ( Eigen::Index i = 0; i < constraintsOld.rows(); i++ ) {
			bool containsVar = false;
			for ( Eigen::Index j = 0; j < constraintsOld.cols(); j++ ) {
				if ( constraintsOld( i, j ) != 0 && std::find( set.begin(), set.end(), j ) != set.end() ) {
					//set contains variable j, which is also contained in this constraint
					containsVar = true;
					break;
				}
			}
			if ( containsVar ) {
				TRACE( "hypro.datastructures", "Row " << i << " is used in constraint " << constraintsOld.row( i ) << " for the current set." );
				indicesToAdd.push_back( i );
			}
		}

		if ( indicesToAdd.size() > 0 ) {
			// create a row matrix with numIndicesToAdd many rows
			matrix_t<Number> newMatrix = selectRows( constraintsOld, indicesToAdd );
			newMatrix = selectCols( newMatrix, set );

			// create final constant vector
			vector_t<Number> newVec = selectRows( constantsOld, indicesToAdd );

			ConstraintSetT<Number> res( newMatrix, newVec );
			DEBUG( "hypro.datastructures", "Final decomposed ConstraintSet: \n"
												 << res );
			newCset.push_back( res );
		} else {
			DEBUG( "hypro.datastructures", "No constraints for set found." );
			ConstraintSetT<Number> res = ConstraintSetT<Number>();
			newCset.push_back( res );
		}
	}

	mConstraints = newCset;
	mConditionIsBox = std::vector<TRIBOOL>{ mConstraints.size(), TRIBOOL::NSET };
	mHash = 0;
	DEBUG( "hypro.datastructures", "Decomposed Condition, created " << mConstraints.size() << " new constraint sets." );
}

template <typename Number>
void Condition<Number>::checkAxisAligned( std::size_t i ) const {
	if ( mConditionIsBox[i] == TRIBOOL::NSET ) {
		mConditionIsBox[i] = mConstraints[i].isAxisAligned() == true ? TRIBOOL::TRUE : TRIBOOL::FALSE;
	}
}

//template<typename Number>
//template<typename Representation, typename ...Rargs>
//std::pair<bool,State<Number,Representation, Rargs...>> Condition<Number>::isSatisfiedBy(const State<Number,Representation, Rargs...>& inState) const {
//#ifdef HYDRA_USE_LOGGING
//	DEBUG("hydra.datastructures","Checking condition.");
//	DEBUG("hydra.datastructures","State: " << inState);
//#endif
//
//	// TODO: Overthink order here - it would be nice to test clocks first, then discrete assignments and continuous sets last.
//	State<Number,Representation> res(inState);
//	bool empty = false;
//	for(std::size_t i = 0; i < this->size(); ++i) {
//		if(mConstraints.at(i).first.rows() == 0) {
//			assert(mConstraints.at(i).second.rows() == 0);
//		} else {
//			//TRACE("hydra.datastructures","Check continuous condition, mat: " << mat << " and vector " << vec << " of state " << inState);
//			std::tuple_element<i, std::tuple<Representation, Rargs...>>::type> contSet = res.getSet<i>().satisfiesHalfspaces(mConstraints.at(i).first, mConstraints.at(i).second);
//			if(contSet.first) {
//				//TRACE("hydra.datastructures","Not empty, resulting set: ");
//				empty = false;
//				res.setSet<i>(contSet.second);
//				//TRACE("hydra.datastructures",res);
//			} else {
//				empty = true;
//				break;
//			}
//		}
//	}
//
//	//DEBUG("hydra.datastructures","Condition is satisfied: " << !empty);
//	return std::make_pair(!empty, res);
//}

}  // namespace hypro
