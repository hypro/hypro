/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Condition.h"
//#include "lib/utils/types.h"
//#include <hypro/types.h>
#include "../../types.h"
#include <iostream>
#include <string>

namespace hypro
{
template<typename Number>
class Transition;

template<typename Number>
class LocationManager;

template<typename Number>
class Location
{
    friend LocationManager<Number>;

protected:
    using transitionSet = std::set<Transition<Number>*>;

    Location(unsigned id);
    Location(unsigned id, const Location& loc);
    Location(unsigned id, const matrix_t<Number>& mat);
    Location(unsigned id, const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv);
    Location(unsigned id, const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv,
             const matrix_t<Number>& extInputMat);

private:
    mutable matrix_t<Number> mFlow;
    matrix_t<Number> mExternalInput;
    transitionSet mTransitions;
    Condition<Number> mInvariant;
    unsigned mId;
    std::string mName;

public:
  	Location() = delete;
    ~Location() {}

    const matrix_t<Number>& getFlow() const { return mFlow; }
    const Condition<Number>& getInvariant() const { return mInvariant; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const matrix_t<Number>& getExternalInput() const { return mExternalInput; }
    unsigned getId() const { return mId; }
	std::string getName() const { return mName; }
    void setName(const std::string& name) { mName = name; }
    void setFlow(const matrix_t<Number>& mat) { mFlow = mat; }
    void setInvariant(const Condition<Number>& inv) { mInvariant = inv; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void addTransition(Transition<Number>* trans) { mTransitions.insert(trans); }
    void setExtInputMat(const matrix_t<Number>& mat) { mExternalInput = mat; }

    inline bool operator<(const Location<Number>& rhs) const { return (mId < rhs.getId()); }
    inline bool operator==(const Location<Number>& rhs) const { return (mId == rhs.getId()); }
    inline bool operator!=(const Location<Number>& rhs) const { return (mId != rhs.getId()); }

    friend std::ostream& operator<<(std::ostream& ostr, const Location<Number>& l) {
    	#ifdef HYDRA_USE_LOGGING
	    matrix_t<Number> tmp = matrix_t<Number>(_l.getInvariant().getMatrix().rows(), _l.getInvariant().getMatrix().cols() + 1);
	    tmp << _l.getInvariant().getMatrix(), _l.getInvariant().getVector();
	    ostr << "location " << _l.getName() << " (id: " << _l.getId() << ")"<< std::endl << "\t Flow: " << std::endl << _l.getFlow() << std::endl << "\t Inv: " << std::endl << tmp;
	    //ostr << _l.getInvariant().getDiscreteCondition() << std::endl;
	    ostr << "Transitions: " << std::endl;
	    for (auto transitionPtr : _l.getTransitions()) {
	        ostr << transitionPtr << std::endl;
	    }
	    ostr << std::endl << ")";
	#endif
	    return ostr;
    }
};

template<typename Number>
struct locPtrComp {
    bool operator()(const Location<Number>* lhs, const Location<Number>* rhs) const { return (*lhs < *rhs); }
};

}  // namespace hypro

#include "Location.tpp"
