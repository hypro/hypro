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
	for(unsigned i = 0; i < flow.rows(); ++i) {
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

}  // namespace hydra
