#include "Location.h"

namespace hypro
{

template<typename Number>    
Location<Number>::Location(unsigned _id) : mFlow(), mExternalInput(), mTransitions(), mInvariant(), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const hydra::Location<Number>& _loc)
    : mFlow(_loc.getFlow()), mExternalInput(_loc.getExternalInput()), mTransitions(_loc.getTransitions()), mInvariant(_loc.getInvariant()), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const hypro::matrix_t<Number>& _mat) : mFlow(_mat), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const hypro::matrix_t<Number>& _mat, const hydra::Location<Number>::transitionSet& _trans, const Condition<Number>& _inv)
    : mFlow(_mat), mExternalInput(), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
}

template<typename Number>
Location<Number>::Location(unsigned _id, const hypro::matrix_t<Number>& _mat, const hydra::Location::transitionSet& _trans, const Condition<Number>& _inv,
                   const hypro::matrix_t<Number>& _extInputMat)
    : mFlow(_mat), mExternalInput(_extInputMat), mTransitions(_trans), mInvariant(_inv), mId(_id)
{
}

template<typename Number>
std::ostream& operator<<(std::ostream& _ostr, const Location<Number>& _l)
{
#ifdef HYDRA_USE_LOGGING
    hypro::matrix_t<Number> tmp = hypro::matrix_t<Number>(_l.getInvariant().getMatrix().rows(), _l.getInvariant().getMatrix().cols() + 1);
    tmp << _l.getInvariant().getMatrix(), _l.getInvariant().getVector();
    _ostr << "location " << _l.getName() << " (id: " << _l.getId() << ")"<< std::endl << "\t Flow: " << std::endl << _l.getFlow() << std::endl << "\t Inv: " << std::endl << tmp;
    //_ostr << _l.getInvariant().getDiscreteCondition() << std::endl;
    _ostr << "Transitions: " << std::endl;
    for (auto transitionPtr : _l.getTransitions()) {
        _ostr << transitionPtr << std::endl;
    }
    _ostr << std::endl << ")";
#endif
    return _ostr;
}

}  // namespace hydra
