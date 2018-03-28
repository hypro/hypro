#include "Location.h"

namespace hypro
{

template<typename Number>
Location<Number>::Location(unsigned _id) : mFlows(), mExternalInput(), mTransitions(), mInvariant(), mId(_id)
{}

template<typename Number>
Location<Number>::Location(unsigned _id, const Location<Number>& _loc)
    : mFlows(_loc.getFlows()), mExternalInput(_loc.getExternalInput()), mTransitions(_loc.getTransitions()), mInvariant(_loc.getInvariant()), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat) : mFlows(), mId(_id)
{
	mFlows.push_back(_mat);
	std::vector<Point<Number>> point;
	point.push_back(Point<Number>(vector_t<Number>::Zero(_mat.cols() -1 )));
	mExternalInput = Box<Number>(point);
	mHasExternalInput = false;
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlows(), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
	mFlows.push_back(_mat);
	std::vector<Point<Number>> point;
	point.push_back(Point<Number>(vector_t<Number>::Zero(_mat.cols() -1 )));
	mExternalInput = Box<Number>(point);
	mHasExternalInput = false;
}

template<typename Number>
void Location<Number>::setFlow(const matrix_t<Number>& mat, std::size_t I) {
	while(I < mFlows.size()) {
		mFlows.push_back(matrix_t<Number>::Identity(mat.rows(),mat.cols()));
	}
	mFlows.push_back(mat);
	if(!mHasExternalInput) {
		std::vector<Point<Number>> point;
		point.push_back(Point<Number>(vector_t<Number>::Zero(mat.cols() -1 )));
		mExternalInput = Box<Number>(point);
	}
}

template<typename Number>
void Location<Number>::setExtInput(const Box<Number>& b) {
	mExternalInput = b;
	for(std::size_t i = 0; i < b.dimension(); ++i) {
		if(b.min()[i] != 0 || b.max()[i] != 0) {
			mHasExternalInput = true;
			break;
		}
	}
}

template<typename Number>
std::string Location<Number>::getDotRepresentation(const std::vector<std::string>& vars) const {
	std::stringstream o;
	o << this->getId() << " [shape=none, margin=0, label=<";
	o << "<TABLE>";
	o << "<TR><TD>" << this->getName() << " (" << this->getId() << ") </TD></TR>";
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

template<typename Number>
Location<Number>* parallelCompose(const Location<Number>* lhs
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

	Location<Number>* res = LocationManager<Number>::getInstance().create();

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
	return res;
}


}  // namespace hypro
