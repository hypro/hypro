#include "Transition.h"

namespace hypro {

template <typename Number>
std::size_t Transition<Number>::hash() const {
	if ( mHash == 0 ) {
		mHash = std::hash<Transition<Number>>()( *this );
	}
	return mHash;
}

template <typename Number>
std::string Transition<Number>::getDotRepresentation( const std::vector<std::string>& vars ) const {
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

template <typename Number>
bool Transition<Number>::isComposedOf( const Transition<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars ) const {
	// compare source and target location
	if ( this->getSource()->getName().find( rhs.getSource()->getName() ) == std::string::npos ||
		 this->getTarget()->getName().find( rhs.getTarget()->getName() ) == std::string::npos ) {
		//std::cout << "source or target did not match." << std::endl;
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
			//std::cout << "Labels did not match." << std::endl;
			return false;
		}
	}

	// compare guard constraints. As the order is not fixed, we consider each row, one by one and try to match rows (outer two loops).
	// This is similar to the invariant comparison in Location.tpp
	if ( rhs.getGuard().size() != 0 ) {
		if ( this->getGuard().size() == 0 ) {
			//std::cout << "guards do not match." << std::endl;
			return false;
		}
		//std::cout << "Compare guards " << rhs.getGuard().getMatrix() << " <= " << rhs.getGuard().getVector() << " and " << this->getGuard().getMatrix() << " <= " << this->getInvariant().getVector() << std::endl;

		// try to find matching rows.
		for ( Eigen::Index rowI = 0; rowI != rhs.getGuard().getMatrix().rows(); ++rowI ) {
			//std::cout << "original row " << rowI << std::endl;
			bool foundConstraint = false;
			for ( Eigen::Index rowPos = 0; rowPos != this->getGuard().getMatrix().rows(); ++rowPos ) {
				bool allMatched = true;
				for ( Eigen::Index colI = 0; colI != rhs.getGuard().getMatrix().cols(); ++colI ) {
					//std::cout << "original col " << colI << std::endl;
					// find corresponding positions in the current flow matrix
					Eigen::Index colPos = 0;
					while ( thisVars[colPos] != rhsVars[colI] ) ++colPos;
					//std::cout << "matching col " << colPos << std::endl;
					if ( this->getGuard().getMatrix()( rowPos, colPos ) != rhs.getGuard().getMatrix()( rowI, colI ) ) {
						allMatched = false;
						break;
					}
				}
				// also compare constants.
				if ( allMatched ) {
					if ( this->getGuard().getVector()( rowPos ) == rhs.getGuard().getVector()( rowI ) ) {
						//std::cout << "matched row " << rowPos << std::endl;
						foundConstraint = true;
						break;
					}
				}
			}
			if ( !foundConstraint ) {
				//std::cout << "Cound not find invariant constraint." << std::endl;
				return false;
			}
		}
	}

	// compare reset function:
	// Find corresponding rows, then compare relevant entries.
	for ( Eigen::Index rowI = 0; rowI != rhs.getReset().getMatrix().rows(); ++rowI ) {
		Eigen::Index rowPos = 0;
		//std::cout << "Search for: " << rhsVars[rowI] << std::endl;
		while ( thisVars[rowPos] != rhsVars[rowI] ) ++rowPos;
		for ( Eigen::Index colI = 0; colI != rhs.getReset().getMatrix().cols(); ++colI ) {
			// find corresponding positions in the current reset matrix
			Eigen::Index colPos = 0;
			while ( thisVars[colPos] != rhsVars[colI] ) ++colPos;
			//std::cout << "rowPos " << rowPos << ", rowI " << rowI << ", colPos " << colPos << ", colI " << colI << std::endl;
			if ( this->getReset().getMatrix()( rowPos, colPos ) != rhs.getReset().getMatrix()( rowI, colI ) ) {
				//std::cout << "reset matrix entries do not match." << std::endl;
				return false;
			}
		}

		// compare constant part (b)
		if ( this->getReset().getVector()( rowPos ) != rhs.getReset().getVector()( rowI ) ) {
			//std::cout << "constant parts do not match." << std::endl;
			return false;
		}
	}

	return true;
}

template<typename Number>
std::unique_ptr<Transition<Number>> parallelCompose(const Transition<Number>* lhsT
                                                    , const Transition<Number>* rhsT
                                                    , const std::vector<std::string>& lhsVar
                                                    , const std::vector<std::string>& rhsVar
                                                    , const std::vector<std::string>& haVar
                                                    , const HybridAutomaton<Number>& ha
                                                    , const std::set<Label> lhsLabels
                                                    , const std::set<Label> rhsLabels)
{
    assert(haVar.size() >= lhsVar.size());
    assert(haVar.size() >= rhsVar.size());

    //std::cout << "Parallel composition of transitions " << lhsT->getSource()->getName() << " -> " << lhsT->getTarget()->getName() << " and " << rhsT->getSource()->getName() << " -> " << rhsT->getTarget()->getName() << std::endl;

    //Transition<Number>* t = new Transition<Number>();
    //std::unique_ptr<Transition<Number>> t = new Transition<Number>()
    std::unique_ptr<Transition<Number>> t = std::make_unique<Transition<Number>>();

    //set label
    if (lhsT->getLabels() == rhsT->getLabels()) {
        //std::cout << "a" << std::endl;
        t->setLabels(lhsT->getLabels());
    } else if(!(lhsT->getLabels().empty()) and rhsLabels.set::count(*(lhsT->getLabels().begin()))==0 and rhsT->getLabels().empty()) {
        //std::cout << "b" << std::endl;
        t->setLabels(lhsT->getLabels());
    } else if(!(rhsT->getLabels().empty()) and lhsLabels.set::count(*(rhsT->getLabels().begin()))==0 and lhsT->getLabels().empty()) {
        //std::cout << "c" << std::endl;
        t->setLabels(rhsT->getLabels());
    } else {
        //std::cout << "d" << std::endl;
        //delete t;
        return nullptr;
    }

    // quick test for shared resets - should be equal, otherwise do not parallel compose.
    // mapping from resultIndex to pair lhsIndex, rhsIndex of the shared variables.
    std::map<unsigned, std::pair<unsigned,unsigned>> sharedVars;
    unsigned idx = 0;
    for(const auto& var : haVar) {
    	// identify a shared variable dimension.
    	if(std::find(lhsVar.begin(), lhsVar.end(), var) != lhsVar.end() && std::find(rhsVar.begin(), rhsVar.end(), var) != rhsVar.end()) {
    		unsigned lhsIdx = 0;
    		unsigned rhsIdx = 0;
    		while(lhsVar[lhsIdx] != var) ++ lhsIdx;
    		while(rhsVar[rhsIdx] != var) ++ rhsIdx;
    		sharedVars[idx] = std::make_pair(lhsIdx,rhsIdx);
    		//std::cout << "Shared variable " << var << " at pos " << idx << " with original positions " << lhsIdx << ", " << rhsIdx << std::endl;
    	}
    	++idx;
    }
    for(const auto& varTuple : sharedVars) {
    	for(const auto& other : sharedVars) {
    		assert(lhsT->getReset().size() != 0);
    		assert(rhsT->getReset().size() != 0);
    		//std::cout << "Compare resets: " << lhsT->getReset().getMatrix() << " and " << rhsT->getReset().getMatrix() << std::endl;
    		//std::cout << "Compare resets: " << lhsT->getReset().getVector() << " and " << rhsT->getReset().getVector() << std::endl;
    		if(lhsT->getReset().getMatrix()(varTuple.second.first,other.second.first) != rhsT->getReset().getMatrix()(varTuple.second.second,other.second.second)
    			|| lhsT->getReset().getVector()(varTuple.second.first) != rhsT->getReset().getVector()(varTuple.second.second) ) {
    			//std::cout << "Delete." << std::endl;
    			//delete t;
    			return nullptr;
    		}
    	}
    }

    //set target and source
    Location<Number>* source = ha.getLocation(lhsT->getSource()->getName()+'_'+rhsT->getSource()->getName());
    Location<Number>* target = ha.getLocation(lhsT->getTarget()->getName()+'_'+rhsT->getTarget()->getName());
    assert(source != nullptr);
    assert(target != nullptr);
    t->setTarget(target);
    t->setSource(source);

    //set urgent
    // Todo: is it not the case that a composed transition is urgent as soon as one of its participating transitions is urgent?
    t->setUrgent(lhsT->isUrgent() || rhsT->isUrgent());

    //set guard
    Condition<Number> haGuard = combine(lhsT->getGuard(), rhsT->getGuard(), haVar, lhsVar, rhsVar);
    t->setGuard(haGuard);

    //set reset
    //std::cout << "Reset, combine matrices: " << std::endl;
    Reset<Number> haReset = combine(lhsT->getReset(), rhsT->getReset(), haVar, lhsVar, rhsVar);
    //std::cout << "New reset function: " << haReset << std::endl;

    t->setReset(haReset);

    //set aggregation
    t->setAggregation(lhsT->getAggregation());

    return t;
}

}  //namespace hypro
