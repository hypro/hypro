#include "Location.h"

namespace hypro
{

template<typename Number>
Location<Number>::Location(unsigned _id) : mFlow(), mExternalInput(), mTransitions(), mInvariant(), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const Location<Number>& _loc)
    : mFlow(_loc.getFlow()), mExternalInput(_loc.getExternalInput()), mTransitions(_loc.getTransitions()), mInvariant(_loc.getInvariant()), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat) : mFlow(_mat), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlow(_mat), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const matrix_t<Number>& _mat, const typename Location<Number>::transitionSet& _trans, const Condition<Number>& _inv,
                   const matrix_t<Number>& _extInputMat)
    : mFlow(_mat), mExternalInput(_extInputMat), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
}

}  // namespace hydra
