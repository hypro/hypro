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
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlows(), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
	mFlows.push_back(_mat);
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv,
                   const matrix_t<Number>& _extInputMat)
    : mFlows(), mExternalInput(_extInputMat), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
	mFlows.push_back(_mat);
}

template<typename Number>
void Location<Number>::setFlow(const matrix_t<Number>& mat, std::size_t I) {
	while(I < mFlows.size()) {
		mFlows.push_back(matrix_t<Number>::Identity(mat.rows(),mat.cols()));
	}
	mFlows.push_back(mat);
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
	// verify name (future work: we need some stronger criterion)
	if(mName.find(rhs.getName()) == std::string::npos) {
		//std::cout << "Name does not match." << std::endl;
		return false;
	}

	// check variables
	for(const auto& v : rhsVars) {
		if(std::find(thisVars.begin(), thisVars.end(), v) == thisVars.end() ) {
			//std::cout << "Variables do not match." << std::endl;
			return false;
		}
	}

	// verify flow
	//std::cout << "compare flows " << mFlows[0] << " and " << rhs.getFlow() << std::endl;
	for(Eigen::Index rowI = 0; rowI != rhs.getFlow().rows(); ++rowI) {
		Eigen::Index rowPos = 0;
		while(thisVars[rowPos] != rhsVars[rowI]) ++rowPos;
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

	// verify invariant
	if(rhs.getInvariant().size() != 0 ) {
		if(this->getInvariant().size() == 0 ) {
			//std::cout << "invariants do not match." << std::endl;
			return false;
		}
		//std::cout << "Compare invariants " << rhs.getInvariant().getMatrix() << " <= " << rhs.getInvariant().getVector() << " and " << this->getInvariant().getMatrix() << " <= " << this->getInvariant().getVector() << std::endl;
		for(Eigen::Index rowI = 0; rowI != rhs.getInvariant().getMatrix().rows(); ++rowI) {
			//std::cout << "original row " << rowI << std::endl;
			bool foundConstraint = false;
			for(Eigen::Index rowPos = 0; rowPos != this->getInvariant().getMatrix().rows(); ++rowPos) {
				bool allMatched = true;
				for(Eigen::Index colI = 0; colI != rhs.getInvariant().getMatrix().cols(); ++colI) {
					//std::cout << "original col " << colI << std::endl;
					// find corresponding positions in the current flow matrix
					Eigen::Index colPos = 0;
					while(thisVars[colPos] != rhsVars[colI]) ++colPos;
					//std::cout << "matching col " << colPos << std::endl;
					if(this->getInvariant().getMatrix()(rowPos,colPos) != rhs.getInvariant().getMatrix()(rowI,colI)) {
						allMatched = false;
						break;
					}
				}
				if(allMatched) {
					if(this->getInvariant().getVector()(rowPos) == rhs.getInvariant().getVector()(rowI)) {
						//std::cout << "matched row " << rowPos << std::endl;
						foundConstraint = true;
						break;
					}
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

}  // namespace hydra
