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

}  // namespace hydra
