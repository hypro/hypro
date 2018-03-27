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

}  // namespace hydra
