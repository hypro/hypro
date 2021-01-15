#include "Location.h"

namespace hypro {

template <typename Number>
Location<Number>::Location()
	: mFlows()
	, mFlowTypes()
	, mExternalInput()
	, mTransitions()
	, mInvariant()
	, mId()
	, mHash( 0 ) {}

template <typename Number>
Location<Number>::Location( const std::string& name )
	: mFlows()
	, mFlowTypes()
	, mExternalInput()
	, mTransitions()
	, mInvariant()
	, mName( name )
	, mId()
	, mHash( 0 ) {}

template <typename Number>
Location<Number>::Location( const Location<Number>& _loc )
	: mFlows( _loc.getFlows() )
	, mFlowTypes( _loc.getFlowTypes() )
	, mExternalInput( _loc.getExternalInput() )
	, mTransitions()
	, mInvariant( _loc.getInvariant() )
	, mName( _loc.getName() )
	, mId()
	, mHash( 0 ) {
	// update copied transitions
	for ( const auto& t : _loc.getTransitions() ) {
		mTransitions.emplace_back( std::make_unique<Transition<Number>>( Transition<Number>( *( t.get() ) ) ) );
		mTransitions.back()->setSource( this );
	}

	assert( this->hash() == _loc.hash() );
}

template <typename Number>
Location<Number>::Location( const matrix_t<Number>& _mat )
	: mFlows()
	, mFlowTypes()
	, mExternalInput()
	, mTransitions()
	, mId() {
	mFlows.emplace_back( linearFlow<Number>( _mat ) );
	mFlowTypes.emplace_back( DynamicType::linear );
	mHasExternalInput = false;
	mHash = 0;
}

template <typename Number>
Location<Number>::Location( const matrix_t<Number>& _mat, typename Location<Number>::transitionVector&& _trans, const Condition<Number>& _inv )
	: mFlows()
	, mFlowTypes()
	, mExternalInput()
	, mTransitions( std::move( _trans ) )
	, mInvariant( _inv )
	, mId() {
	for ( auto& t : mTransitions ) {
		t->setSource( this );
	}
	mFlows.push_back( linearFlow<Number>( _mat ) );
	mFlowTypes.push_back( DynamicType::affine );
	mHasExternalInput = false;
	mHash = 0;
}

template <typename Number>
Location<Number>& Location<Number>::operator=( const Location<Number>& in ) {
	if ( this != &in ) {
		mInvariant = in.getInvariant();
		mName = in.getName();
		mExternalInput = in.getExternalInput();
		mHash = 0;
		// update copied transitions
		mTransitions.clear();
		for ( const auto& t : in.getTransitions() ) {
			mTransitions.emplace_back( std::make_unique<Transition<Number>>( Transition<Number>( *( t.get() ) ) ) );
			mTransitions.back()->setSource( this );
		}

		mFlows.clear();
		mFlowTypes.clear();
		mFlows.insert( mFlows.begin(), in.getFlows().begin(), in.getFlows().end() );
		mFlowTypes.insert( mFlowTypes.begin(), in.getFlowTypes().begin(), in.getFlowTypes().end() );

		//TRACE( "hypro.datastructures", "Comparing hashes after assignment of " << in.getName() << " to this." );
		assert( this->hash() == in.hash() );
	}
	return *this;
}

template <typename Number>
std::size_t Location<Number>::getSubspaceIndexForStateSpaceDimension( std::size_t dimension ) const {
	std::size_t clusterpos = 0;
	std::size_t accumulatedDimension = std::visit( flowDimensionVisitor{}, mFlows[clusterpos] );
	while ( dimension > accumulatedDimension && clusterpos < mFlows.size() ) {
		++clusterpos;
		accumulatedDimension += std::visit( flowDimensionVisitor{}, mFlows[clusterpos] );
	}
	return clusterpos;
}

template <typename Number>
std::size_t Location<Number>::dimension() const {
	std::size_t res = 0;
	for ( std::size_t i = 0; i < mFlows.size(); ++i ) {
		if ( mFlowTypes[i] == DynamicType::rectangular ) {
			res += std::get<rectangularFlow<Number>>( mFlows[i] ).dimension();
		} else if ( mFlowTypes[i] == DynamicType::linear ) {
			res += std::get<linearFlow<Number>>( mFlows[i] ).dimension();
		}
	}
	return res;
}

template <typename Number>
std::size_t Location<Number>::dimension( std::size_t i ) const {
	assert( i < mFlows.size() );
	if ( mFlowTypes[i] == DynamicType::rectangular ) {
		return std::get<rectangularFlow<Number>>( mFlows[i] ).dimension();
	} else if ( mFlowTypes[i] == DynamicType::linear ) {
		return std::get<linearFlow<Number>>( mFlows[i] ).dimension();
	}
	return 0;
}

template <typename Number>
void Location<Number>::setLinearFlow( const linearFlow<Number>& f, std::size_t I ) {
	assert( I <= mFlows.size() );
	if ( I < mFlows.size() ) {
		auto flowpos = mFlows.erase( std::next( mFlows.begin(), I ) );
		auto typepos = mFlowTypes.erase( std::next( mFlowTypes.begin(), I ) );
		mFlows.insert( flowpos, f );
		mFlowTypes.insert( typepos, DynamicType::linear );
	} else if ( I == mFlows.size() ) {
		mFlows.push_back( f );
		mFlowTypes.push_back( DynamicType::linear );
	}
	assert( isConsistent() );
	mHash = 0;
}

template <typename Number>
void Location<Number>::setRectangularFlow( const rectangularFlow<Number>& f, std::size_t I ) {
	assert( I <= mFlows.size() );
	if ( I < mFlows.size() ) {
		auto flowpos = mFlows.erase( std::next( mFlows.begin(), I ) );
		auto typepos = mFlowTypes.erase( std::next( mFlowTypes.begin(), I ) );
		mFlows.insert( flowpos, f );
		mFlowTypes.insert( typepos, DynamicType::rectangular );
	} else if ( I == mFlows.size() ) {
		mFlows.push_back( f );
		mFlowTypes.push_back( DynamicType::rectangular );
	}
	mHash = 0;
}

template <typename Number>
void Location<Number>::setTransitions( transitionVector&& trans ) {
#ifndef NDEBUG
	for ( const auto& t : trans ) {
		// lightweight test - hash is not collosion-free
		assert( t->getSource() == this );
	}
#endif
	mTransitions = std::move( trans );
	mHash = 0;
}

template <typename Number>
void Location<Number>::addTransition( std::unique_ptr<Transition<Number>>&& trans ) {
	//std::cout << "add transition from " << trans->getSource() << " to " << trans->getTarget() << ", this is " << this << std::endl;
	assert( trans->getSource() == this );
	mTransitions.emplace_back( std::move( trans ) );
	mHash = 0;
}

template <typename Number>
Transition<Number>* Location<Number>::createTransition( Location<Number>* target ) {
	auto& res = mTransitions.emplace_back( std::make_unique<Transition<Number>>( Transition<Number>{ this, target } ) );
	mHash = 0;
	return res.get();
}

/*
template<typename Number>
void Location<Number>::updateTransition(Transition<Number>* original, Transition<Number>* newT) {
	assert(newT->getSource() == this);
	auto tPos = std::find(mTransitions.begin(), mTransitions.end(), original);
	if( tPos == mTransitions.end()) {
		TRACE("hypro.datastructures.hybridAutomaton","Attempted to update non-existing transition @" << original);
		return;
	}
	assert(newT != nullptr);
	mTransitions.erase(tPos);
	mTransitions.emplace_back(newT);
	mHash = 0;
}
*/

template <typename Number>
void Location<Number>::setExtInput( const std::vector<carl::Interval<Number>>& b ) {
	mExternalInput = b;
	for ( std::size_t i = 0; i < b.size(); ++i ) {
		if ( b[i] != carl::Interval<Number>( 0 ) ) {
			mHasExternalInput = true;
			break;
		}
	}
	mHash = 0;
}

template <typename Number>
std::size_t Location<Number>::hash() const {
	if ( mHash == 0 ) {
		mHash = std::hash<Location<Number>>()( *this );
	}
	return mHash;
}

template <typename Number>
std::string Location<Number>::getDotRepresentation( const std::vector<std::string>& vars ) const {
	std::stringstream o;
	o << this->hash() << " [shape=none, margin=0, label=<";
	o << "<TABLE>";
	o << "<TR><TD>" << this->getName() << " (" << this->hash() << ") </TD></TR>";
	// flow
	for ( std::size_t i = 0; i < mFlows.size(); ++i ) {
		if ( mFlowTypes[i] == DynamicType::linear ) {
			const matrix_t<Number>& flow = std::get<linearFlow<Number>>( mFlows[i] ).getFlowMatrix();
			o << "<TR><TD ROWSPAN=\"" << flow.rows() << "\">";
			for ( unsigned i = 0; i < flow.rows() - 1; ++i ) {
				o << vars[i] << "' = ";
				bool allZero = true;
				for ( unsigned j = 0; j < flow.cols() - 1; ++j ) {
					if ( flow( i, j ) != 0 ) {
						o << flow( i, j ) << "*" << vars[j] << " + ";
						allZero = false;
					}
				}
				if ( flow( i, flow.cols() - 1 ) != 0 || allZero ) o << flow( i, flow.cols() - 1 );
				if ( i < flow.rows() - 1 )
					o << "<BR/>";
			}
			o << "</TD>";
			o << "</TR>";
		}
	}

	// invariant
	o << mInvariant.getDotRepresentation( vars );
	o << "</TABLE>";
	o << ">];\n";

	return o.str();
}

/*
template <typename Number>
bool Location<Number>::isComposedOf( const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars ) const {
	// verify name (future work: we need some stronger criterion, also to speed-up the look-up)
	if ( mName.find( rhs.getName() ) == std::string::npos ) {
		//std::cout << "Name does not match." << std::endl;
		return false;
	}

	// check variable sets (this is checked beforehand, but this function now is also stand-alone).
	for ( const auto& v : rhsVars ) {
		if ( std::find( thisVars.begin(), thisVars.end(), v ) == thisVars.end() ) {
			//std::cout << "Variables do not match." << std::endl;
			return false;
		}
	}

	// verify flow:
	// Note: We assume the last row is zero and do not explicitly check this property here.
	// The check searches for matching variables - the *I indices refer to the rhs-related indices
	// while the *Pos indices refer to this.

	for ( Eigen::Index rowI = 0; rowI != rhs.getLinearFlow().getFlowMatrix().rows() - 1; ++rowI ) {
		// find according row in this.
		Eigen::Index rowPos = 0;
		//std::cout << "Search for: " << rhsVars[rowI] << std::endl;
		while ( thisVars[rowPos] != rhsVars[rowI] ) {
			//std::cout << "Consider: " << thisVars[rowPos] << std::endl;
			++rowPos;
			if ( rowPos == Eigen::Index( thisVars.size() ) ) {
				//std::cout << "Reached end." << std::endl;
			}
		}
		// for the row now search all relevant columns. Note that the last column does not have a matching variable (constants), handle separately.
		for ( Eigen::Index colI = 0; colI != rhs.getFlow().cols(); ++colI ) {
			if ( colI != rhs.getFlow().cols() - 1 ) {
				// find corresponding positions in the current flow matrix
				Eigen::Index colPos = 0;
				while ( thisVars[colPos] != rhsVars[colI] ) ++colPos;
				//std::cout << "rowPos " << rowPos << ", rowI " << rowI << ", colPos " << colPos << ", colI " << colI << std::endl;
				if ( mLinearFlows[0].getFlowMatrix()( rowPos, colPos ) != rhs.getLinearFlow().getFlowMatrix()( rowI, colI ) ) {
					//std::cout << "flows do not match." << std::endl;
					return false;
				}
			} else {
				if ( mLinearFlows[0].getFlowMatrix()( rowPos, mLinearFlows[0].getFlowMatrix().cols() - 1 ) != rhs.getLinearFlow( 0 ).getFlowMatrix()( rowI, colI ) ) {
					//std::cout << "constant parts of flow does not match." << std::endl;
					return false;
				}
			}
		}
	}

	// verify invariant constraints. Note that the invariant can also be empty, so verify sizes first.
	//
	if ( rhs.getInvariant().size() != 0 ) {
		if ( this->getInvariant().size() == 0 ) {
			//std::cout << "invariants do not match." << std::endl;
			return false;
		}
		//std::cout << "Compare invariants " << rhs.getInvariant().getMatrix() << " <= " << rhs.getInvariant().getVector() << " and " << this->getInvariant().getMatrix() << " <= " << this->getInvariant().getVector() << std::endl;

		// As the order of constraints does not matter, try to find matching rows one by one.
		for ( Eigen::Index rowI = 0; rowI != rhs.getInvariant().getMatrix().rows(); ++rowI ) {
			//std::cout << "original row " << rowI << std::endl;
			bool foundConstraint = false;
			// compare invariant constraint in this to the row in rhs.
			for ( Eigen::Index rowPos = 0; rowPos != this->getInvariant().getMatrix().rows(); ++rowPos ) {
				bool allMatched = true;
				// if all entries match we found the correct row - check column-wise.
				for ( Eigen::Index colI = 0; colI != rhs.getInvariant().getMatrix().cols(); ++colI ) {
					//std::cout << "original col " << colI << std::endl;
					// find corresponding positions in the current invariant matrix
					Eigen::Index colPos = 0;
					while ( thisVars[colPos] != rhsVars[colI] ) ++colPos;
					//std::cout << "matching col " << colPos << std::endl;
					if ( this->getInvariant().getMatrix()( rowPos, colPos ) != rhs.getInvariant().getMatrix()( rowI, colI ) ) {
						allMatched = false;
						break;
					}
				}
				// if the assumed correct row has been found, also check the constant part.
				if ( allMatched &&
					 this->getInvariant().getVector()( rowPos ) == rhs.getInvariant().getVector()( rowI ) ) {
					//std::cout << "matched row " << rowPos << std::endl;
					foundConstraint = true;
					break;
				}
			}
			if ( !foundConstraint ) {
				//std::cout << "Cound not find invariant constraint." << std::endl;
				return false;
			}
		}
	}

	// check transitions:
	// try to find a matching transition.
	for ( const auto& transPtr : this->mTransitions ) {
		bool foundOne = false;

		for ( const auto& rhsTransPtr : rhs.getTransitions() ) {
			if ( transPtr.get()->isComposedOf( *( rhsTransPtr.get() ), rhs.getVariables(), this->getVariables() ) ) {
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
*/

/*
template<typename Number>
//std::unique_ptr<Location<Number>> parallelCompose(const std::unique_ptr<Location<Number>>& lhs
//                                , const std::unique_ptr<Location<Number>>& rhs
std::unique_ptr<Location<Number>> parallelCompose(const Location<Number>* lhs
                                                , const Location<Number>* rhs
                                                , const std::vector<std::string>& lhsVar
                                                , const std::vector<std::string>& rhsVar
                                                , const std::vector<std::string>& haVar)
{
	//compute flow
	matrix_t<Number> haFlow = matrix_t<Number>::Zero(haVar.size()+1, haVar.size()+1);

	//std::cout << "combine Locations " << lhs->getName() << " and " << rhs->getName() << std::endl;
	//std::cout << "With flows " << lhs->getFlow() << " and " << rhs->getFlow() << std::endl;

	std::size_t lhsIR = 0, lhsIC = 0, rhsIR = 0, rhsIC = 0;
	bool admissible = true; // flag used to denote a non-admissible flow, i.e. shared variables with different flow.
	// iterate over all rows
	for( std::size_t rowI = 0; rowI != haVar.size(); ++rowI ) {
		//std::cout << "Consider composed row " << rowI << " for var " << haVar[rowI] << std::endl;
		//std::cout << "lhsIR: " << lhsIR << std::endl;
		//std::cout << "rhsIR: " << rhsIR << std::endl;
		//std::cout << "Now left hand side." << std::endl;
		if(lhsIR < lhsVar.size() && lhsVar[lhsIR] == haVar[rowI]) {
			// iterate over all columns
			lhsIC = 0;
			for( std::size_t colI = 0; colI != haVar.size(); ++colI) {
				//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
				//std::cout << "lhsIC: " << lhsIC << std::endl;
				//std::cout << "rhsIC: " << rhsIC << std::endl;
				if(lhsVar[lhsIC] == haVar[colI]) {
					haFlow(rowI,colI) = lhs->getFlow()(lhsIR,lhsIC);
					++lhsIC;
					if(lhsIC == lhsVar.size()) {
						break;
					}
				}
			}
			++lhsIR;
		}
		//std::cout << "lhsIR: " << lhsIR << std::endl;
		//std::cout << "intermediate result: " << haFlow << std::endl;
		//std::cout << "Now right hand side." << std::endl;
		if(rhsIR < rhsVar.size() && rhsVar[rhsIR] == haVar[rowI]) {
			// iterate over all columns
			rhsIC = 0;
			for( std::size_t colI = 0; colI != haVar.size(); ++colI) {
				//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
				//std::cout << "lhsIC: " << lhsIC << std::endl;
				//std::cout << "rhsIC: " << rhsIC << std::endl;
				if(rhsVar[rhsIC] == haVar[colI]) {
					// TODO: the check is not entirely correct, since the flow can be non-admissible but set to 0 in lhs and something != 0 in rhs.
					if(haFlow(rowI,colI) != 0 && rhs->getFlow()(rhsIR,rhsIC) != haFlow(rowI,colI)) {
						admissible = false;
						break;
					}

					//std::cout << "haFlow sizes: " << haFlow.rows() << "x" << haFlow.cols() << std::endl;
					//std::cout << "rhs->getFlow() sizes: " << rhs->getFlow().rows() << "x" << rhs->getFlow().cols() << std::endl;
					//std::cout << "rowI: " << rowI << " colI " << colI << " rhsIR " << rhsIR << " rhsIC " << rhsIC << std::endl;
					//assert(rowI < haFlow.rows());
					//assert(colI < haFlow.cols());
					//assert(rhsIR <= rhs->getFlow().rows());
					//assert(rhsIC <= rhs->getFlow().cols());
					haFlow(rowI,colI) = rhs->getFlow()(rhsIR,rhsIC);
					++rhsIC;
					if(rhsIC == rhsVar.size()) {
						break;
					}
				}
			}
			++rhsIR;
		}
		//std::cout << "rhsIR: " << rhsIR << std::endl;
		if(!admissible)
			break;
	}

	// constant parts - TODO: integrate into loop above?
	for(unsigned rowI = 0; rowI < haFlow.rows()-1; ++rowI) {
		//std::cout << "Constant part for var " << haVar[rowI] << std::endl;
		unsigned lhsPos = 0;
		unsigned rhsPos = 0;
		bool leftFound = false;
		bool rightFound = false;
		while(lhsPos != lhsVar.size()) {
			if(lhsVar[lhsPos] == haVar[rowI]) {
				leftFound = true;
				//std::cout << "Found in lhs at pos " << lhsPos << std::endl;
				break;
			}
			++lhsPos;
		}

		while(rhsPos != rhsVar.size()) {
			if(rhsVar[rhsPos] == haVar[rowI]) {
				//std::cout << "Found in rhs at pos " << lhsPos << std::endl;
				rightFound = true;
				break;
			}
			++rhsPos;
		}
		if(leftFound) {
			// if is shared variable
			if(rightFound) {
				if(lhs->getFlow()(lhsPos, lhs->getFlow().cols()-1) != rhs->getFlow()(rhsPos, rhs->getFlow().cols()-1)) {
					admissible = false;
					break;
				} else {
					haFlow(rowI,haFlow.cols()-1) = lhs->getFlow()(lhsPos, lhs->getFlow().cols()-1);
					//std::cout << "Set to " << haFlow(rowI,haFlow.cols()-1) << std::endl;
				}
			} else {
				haFlow(rowI,haFlow.cols()-1) = lhs->getFlow()(lhsPos, lhs->getFlow().cols()-1);
				//std::cout << "Set to " << haFlow(rowI,haFlow.cols()-1) << std::endl;
			}
		} else {
			if(rightFound) {
				haFlow(rowI,haFlow.cols()-1) = rhs->getFlow()(rhsPos, rhs->getFlow().cols()-1);
				//std::cout << "Set to " << haFlow(rowI,haFlow.cols()-1) << std::endl;
			} else {
				//std::cout << "Variable is neither part of lhs or rhs!" << std::endl;
				assert(false);
				admissible = false;
			}
		}
	}

	if(!admissible) {
		FATAL("hypro.datastructures","Failed to create parallel composition of locations.");
		return nullptr;
	}

	//Location<Number>* res = LocationManager<Number>::getInstance().create();
	std::unique_ptr<Location<Number>> res = std::make_unique<Location<Number>>();

	//set name
	res->setName(lhs->getName()+"_"+rhs->getName());

	//std::cout << "Created flow: " << haFlow << " for location " << res->getName();

	res->setFlow(haFlow);

	//set invariant
	Condition<Number> inv = combine(lhs->getInvariant(), rhs->getInvariant(), haVar, lhsVar, rhsVar);
	res->setInvariant(inv);

	//std::cout << "Created invariant: " << inv << " for location " << res->getName();


	//std::cout << "setExtInput" << std::endl;
	//set extinput
	//loc->setExtInput(flowAndExtInput.second);
	//return std::unique_ptr<Location<Number>>(res);
	return res;
}
*/


template <typename Number>
void Location<Number>::decompose( const std::vector<std::vector<std::size_t>>& partition ) {
	// assumption: this function is only called on locations that are not yet decomposed (i.e have exactly one flow)
	if ( mFlows.size() != 1 ) {
		// Already decomposed or empty flow
		return;
	}
	std::vector<flowVariant<Number>> newFlows;
	std::vector<DynamicType> newFlowTypes;

	auto& vpool = VariablePool::getInstance();


	for ( auto& subspace : partition ) {
		if ( mFlowTypes[0] == DynamicType::discrete || mFlowTypes[0] == DynamicType::timed || mFlowTypes[0] == DynamicType::singular || mFlowTypes[0] == DynamicType::affine || mFlowTypes[0] == DynamicType::linear ) {
			std::vector selectedIndices = subspace;
			// Keep last row (affine)
			selectedIndices.emplace_back( this->dimension() );
			auto newFlowMatrix = selectCols( selectRows( this->getLinearFlow().getFlowMatrix(), selectedIndices ), selectedIndices );
			newFlows.emplace_back( newFlowMatrix );
			newFlowTypes.emplace_back( DynamicType::linear );
		} else if ( mFlowTypes[0] == DynamicType::rectangular ) {
			std::map<carl::Variable, carl::Interval<Number>> newIntervals;
			// iterate over selected dimensions and find corresponding rectangular flows in the existing flow definition
			for ( std::size_t dimension : subspace ) {
				auto variable = vpool.carlVarByIndex( dimension );
				newIntervals.insert( std::make_pair( variable, this->getRectangularFlow().getFlowIntervalForDimension( variable ) ) );
			}
			newFlows.emplace_back( rectangularFlow<Number>( newIntervals ) );
			newFlowTypes.emplace_back( DynamicType::rectangular );
		} else {
			assert( false && "Mixed analysis not implemented" );
		}
	}
	assert( newFlows.size() == newFlowTypes.size() );
	assert( newFlows.size() == partition.size() );
	mFlows = std::move( newFlows );
	mFlowTypes = std::move( newFlowTypes );

	// decompose invariant
	mInvariant.decompose( partition );
	// decompose transitions
	for ( auto& transition : mTransitions ) {
		transition->decompose( partition );
	}
	mHash = 0;
}


}  // namespace hypro
