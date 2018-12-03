#include "Location.h"

namespace hypro
{

////// Deprecated Versions //////

template<typename Number>
Location<Number>::Location(unsigned _id) : mFlows(), mExternalInput(), mTransitions(), mInvariant(), mId(_id), mHash(0)
{}

template<typename Number>
Location<Number>::Location(unsigned _id, const Location<Number>& _loc)
	: mFlows(_loc.getFlows()), mExternalInput(_loc.getExternalInput()), mTransitions(_loc.getTransitions()), mInvariant(_loc.getInvariant()), mId(_id), mHash(0)
{}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat) : mFlows(), mId(_id), mExternalInput()
{
	mFlows.push_back(linearFlow<Number>(_mat));
	mHasExternalInput = false;
	mHash = 0;
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlows(), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
	mFlows.push_back(linearFlow<Number>(_mat));
	mHasExternalInput = false;
	mHash = 0;
}

/////// New Versions ///////

template<typename Number>
Location<Number>::Location() : mFlows(), mExternalInput(), mTransitions(), mInvariant(), mId(), mHash(0)
{}

template<typename Number>
Location<Number>::Location(const Location<Number>& _loc)
	: mFlows(_loc.getFlows()), mExternalInput(_loc.getExternalInput()), mTransitions(_loc.getTransitions()), mInvariant(_loc.getInvariant()), mName(_loc.getName()), mId(), mHash(0)
{}

template<typename Number>
Location<Number>::Location(const matrix_t<Number>& _mat) : mFlows(), mId(), mExternalInput()
{
	mFlows.push_back(linearFlow<Number>(_mat));
	mHasExternalInput = false;
	mHash = 0;
}

template<typename Number>
Location<Number>::Location(const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlows(), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId()
{
	mFlows.push_back(linearFlow<Number>(_mat));
	mHasExternalInput = false;
	mHash = 0;
}

template<typename Number>
std::size_t Location<Number>::dimension() const {
	std::size_t res = 0;
	for(const auto& f : mFlows) {
		res += boost::apply_visitor(flowDimensionVisitor(), f);
	}
	return res;
}

template<typename Number>
std::size_t Location<Number>::dimension(std::size_t i) const {
	return boost::apply_visitor(flowDimensionVisitor(), mFlows.at(i));
}

template<typename Number>
void Location<Number>::setFlow(const flowVariant& f, std::size_t I) {
	matrix_t<Number> dummy = matrix_t<Number>::Identity(getFlowDimension(f), getFlowDimension(f));
	while(mFlows.size() <= I) {
		mFlows.push_back(linearFlow<Number>(dummy));
	}
	mFlows[I] = f;
	mHash = 0;
}

template<typename Number>
void Location<Number>::updateTransition(Transition<Number>* original, Transition<Number>* newT) {
	auto tPos = std::find(mTransitions.begin(), mTransitions.end(), original);
	if( tPos == mTransitions.end()) {
		TRACE("hypro.datastructures.hybridAutomaton","Attempted to update non-existing transition @" << original);
		return;
	}
	assert(newT != nullptr);
	mTransitions.erase(tPos);
	mTransitions.insert(newT);
	mHash = 0;
}

template<typename Number>
void Location<Number>::setExtInput(const std::vector<carl::Interval<Number>>& b) {
	mExternalInput = b;
	for(std::size_t i = 0; i < b.size(); ++i) {
		if(b[i] != carl::Interval<Number>(0)) {
			mHasExternalInput = true;
			break;
		}
	}
	mHash = 0;
}

template<typename Number>
std::size_t Location<Number>::hash() const {
	if(mHash == 0){
		mHash = std::hash<Location<Number>>()(*this);
	}
	return mHash;
}

template<typename Number>
std::string Location<Number>::getDotRepresentation(const std::vector<std::string>& vars) const {
	std::stringstream o;
	o << this->hash() << " [shape=none, margin=0, label=<";
	o << "<TABLE>";
	o << "<TR><TD>" << this->getName() << " (" << this->hash() << ") </TD></TR>";
	// flow
	matrix_t<Number>& flow = *mFlows.begin();
	o << "<TR><TD ROWSPAN=\"" << flow.rows() << "\">";
	for(unsigned i = 0; i < flow.rows()-1; ++i) {
		o << vars[i] << "' = ";
		bool allZero = true;
		for(unsigned j = 0; j < flow.cols() -1; ++j) {
			if(flow(i,j) != 0) {
				o << flow(i,j) << "*" << vars[j] << " + ";
				allZero = false;
			}
		}
		if(flow(i,flow.cols()-1) != 0 || allZero) o << flow(i,flow.cols()-1);
		if(i < flow.rows() -1)
			o << "<BR/>";
	}
	o << "</TD>";
	o << "</TR>";
	// invariant
	o << mInvariant.getDotRepresentation(vars);
	o << "</TABLE>";
	o << ">];\n";

	return o.str();
}

template<typename Number>
bool Location<Number>::isComposedOf(const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars) const {
	// verify name (future work: we need some stronger criterion, also to speed-up the look-up)
	if(mName.find(rhs.getName()) == std::string::npos) {
		//std::cout << "Name does not match." << std::endl;
		return false;
	}

	// check variable sets (this is checked beforehand, but this function now is also stand-alone).
	for(const auto& v : rhsVars) {
		if(std::find(thisVars.begin(), thisVars.end(), v) == thisVars.end() ) {
			//std::cout << "Variables do not match." << std::endl;
			return false;
		}
	}

	// verify flow:
	// Note: We assume the last row is zero and do not explicitly check this property here.
	// The check searches for matching variables - the *I indices refer to the rhs-related indices
	// while the *Pos indices refer to this.

	//std::cout << "compare flows " << mFlows[0] << " and " << rhs.getFlow() << std::endl;
	for(Eigen::Index rowI = 0; rowI != rhs.getFlow().rows()-1; ++rowI) {
		// find according row in this.
		Eigen::Index rowPos = 0;
		//std::cout << "Search for: " << rhsVars[rowI] << std::endl;
		while(thisVars[rowPos] != rhsVars[rowI]) {
			//std::cout << "Consider: " << thisVars[rowPos] << std::endl;
			++rowPos;
			if(rowPos == Eigen::Index(thisVars.size())) {
				//std::cout << "Reached end." << std::endl;
			}
		}
		// for the row now search all relevant columns. Note that the last column does not have a matching variable (constants), handle separately.
		for(Eigen::Index colI = 0; colI != rhs.getFlow().cols(); ++colI) {
			if(colI != rhs.getFlow().cols()-1) {
				// find corresponding positions in the current flow matrix
				Eigen::Index colPos = 0;
				while(thisVars[colPos] != rhsVars[colI]) ++colPos;
				//std::cout << "rowPos " << rowPos << ", rowI " << rowI << ", colPos " << colPos << ", colI " << colI << std::endl;
				if(mFlows[0](rowPos,colPos) != rhs.getFlow()(rowI,colI)) {
					//std::cout << "flows do not match." << std::endl;
					return false;
				}
			} else {
				if(mFlows[0](rowPos, mFlows[0].cols()-1) != rhs.getFlow()(rowI,colI)) {
					//std::cout << "constant parts of flow does not match." << std::endl;
					return false;
				}
			}

		}
	}

	// verify invariant constraints. Note that the invariant can also be empty, so verify sizes first.
	//
	if(rhs.getInvariant().size() != 0 ) {
		if(this->getInvariant().size() == 0 ) {
			//std::cout << "invariants do not match." << std::endl;
			return false;
		}
		//std::cout << "Compare invariants " << rhs.getInvariant().getMatrix() << " <= " << rhs.getInvariant().getVector() << " and " << this->getInvariant().getMatrix() << " <= " << this->getInvariant().getVector() << std::endl;

		// As the order of constraints does not matter, try to find matching rows one by one.
		for(Eigen::Index rowI = 0; rowI != rhs.getInvariant().getMatrix().rows(); ++rowI) {
			//std::cout << "original row " << rowI << std::endl;
			bool foundConstraint = false;
			// compare invariant constraint in this to the row in rhs.
			for(Eigen::Index rowPos = 0; rowPos != this->getInvariant().getMatrix().rows(); ++rowPos) {
				bool allMatched = true;
				// if all entries match we found the correct row - check column-wise.
				for(Eigen::Index colI = 0; colI != rhs.getInvariant().getMatrix().cols(); ++colI) {
					//std::cout << "original col " << colI << std::endl;
					// find corresponding positions in the current invariant matrix
					Eigen::Index colPos = 0;
					while(thisVars[colPos] != rhsVars[colI]) ++colPos;
					//std::cout << "matching col " << colPos << std::endl;
					if(this->getInvariant().getMatrix()(rowPos,colPos) != rhs.getInvariant().getMatrix()(rowI,colI)) {
						allMatched = false;
						break;
					}
				}
				// if the assumed correct row has been found, also check the constant part.
				if(allMatched &&
					this->getInvariant().getVector()(rowPos) == rhs.getInvariant().getVector()(rowI)) {
					//std::cout << "matched row " << rowPos << std::endl;
					foundConstraint = true;
					break;
				}
			}
			if(!foundConstraint) {
				//std::cout << "Cound not find invariant constraint." << std::endl;
				return false;
 			}
		}
	}

	return true;
}

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

template<typename Number>
void Location<Number>::decompose(std::vector<std::vector<size_t>> decomposition){
	if(mFlows.size() > 1 || mInvariant.size() > 1){
		//already decomposed
		return;
	}
	DEBUG("hypro.datastructures","Flow Matrix before: \n " << mFlows.at(0));
	// decompose flow
	matrix_t<Number> oldFlow(mFlows.at(0));
	std::vector<matrix_t<Number>> newFlows;
	// for each set {i,j,..., k} select the i-th,j-th,...,k-th vector into a new square matrix
	for(auto set : decomposition){
		#ifdef HYPRO_LOGGING
		DEBUG("hypro.datastructures","decompose flow for set: {");
		for(auto entry : set){
			DEBUG("hypro.datastructures", "" << entry << ", ");
		}
		DEBUG("hypro.datastructures","}");
		#endif
		// +1 row for last-row of affine transformation
		matrix_t<Number> rowMat = matrix_t<Number>::Zero(set.size()+1, oldFlow.cols());
		// -1 because of last-row
		for(Eigen::Index index = 0; index < rowMat.rows()-1; index++){
			// select the specific rows into rowMat
			rowMat.row(index) = oldFlow.row(set[index]);
		}
		//copy last row over
		rowMat.row(rowMat.rows()-1) = oldFlow.row(oldFlow.rows()-1);

		// +1 for constant column
		matrix_t<Number> finMat = matrix_t<Number>::Zero(rowMat.rows(), set.size()+1);
		// -1 for constant column
		for(Eigen::Index index = 0; index < finMat.cols()-1; index++){
			finMat.col(index) = rowMat.col(set[index]);
		}
		finMat.col(finMat.cols()-1) = rowMat.col(rowMat.cols()-1);
		DEBUG("hypro.datastructures", "Final decomposed Flow: \n" << finMat );
		newFlows.push_back(finMat);
	}

	mFlows = newFlows;
	// decompose invariant
	mInvariant.decompose(decomposition);
}

}  // namespace hypro
