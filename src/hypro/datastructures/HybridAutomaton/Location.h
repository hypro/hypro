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

/**
 * @brief      Class for location.
 * @tparam     Number  The used number type.
 */
template<typename Number>
class Location
{
    friend LocationManager<Number>;

protected:
    using transitionSet = std::set<Transition<Number>*>;

    /**
     * @brief      Constructor
     * @details    Note that locations should only be constructed from the LocationManager.
     * @param[in]  id    The identifier given by the LocationManager.
     */
    ///@{
    Location(unsigned id);
    /**
     * @param[in]  id    The identifier given by the LocationManager.
     * @param[loc] The original location which is copied.
     *
     */
    Location(unsigned id, const Location& loc);
    Location(unsigned id, const matrix_t<Number>& mat);
    Location(unsigned id, const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv);
    Location(unsigned id, const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv,
             const matrix_t<Number>& extInputMat);
    ///@}

private:
    mutable std::vector<matrix_t<Number>> mFlows;
    matrix_t<Number> mExternalInput;
    transitionSet mTransitions;
    Condition<Number> mInvariant;
    unsigned mId;
    std::string mName;

public:
  	Location() = delete;
    ~Location() {}

    matrix_t<Number> getFlow(std::size_t I = 0) const { return mFlows.at(I); }
    matrix_t<Number>& rGetFlow(std::size_t I = 0) { return mFlows[I]; }
    const Condition<Number>& getInvariant() const { return mInvariant; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const matrix_t<Number>& getExternalInput() const { return mExternalInput; }
    unsigned getId() const { return mId; }
	std::string getName() const { return mName; }

    void setName(const std::string& name) { mName = name; }
    void setFlow(const matrix_t<Number>& mat, std::size_t I = 0);
    void setInvariant(const Condition<Number>& inv) { mInvariant = inv; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void addTransition(Transition<Number>* trans) { mTransitions.insert(trans); }
    void setExtInputMat(const matrix_t<Number>& mat) { mExternalInput = mat; }

    inline bool operator<(const Location<Number>& rhs) const { return (mId < rhs.getId()); }
    inline bool operator==(const Location<Number>& rhs) const { return (mId == rhs.getId()); }
    inline bool operator!=(const Location<Number>& rhs) const { return (mId != rhs.getId()); }

    friend std::ostream& operator<<(std::ostream& ostr, const Location<Number>& l) {
    	#ifdef HYPRO_LOGGING
	    matrix_t<Number> tmp = matrix_t<Number>(l.getInvariant().getMatrix().rows(), l.getInvariant().getMatrix().cols() + 1);
	    tmp << l.getInvariant().getMatrix(), l.getInvariant().getVector();
	    ostr << "location " << l.getName() << " (id: " << l.getId() << ")"<< std::endl << "\t Flow: " << std::endl << l.getFlow() << std::endl << "\t Inv: " << std::endl << tmp;
	    //ostr << l.getInvariant().getDiscreteCondition() << std::endl;
	    ostr << "Transitions: " << std::endl;
	    for (auto transitionPtr : l.getTransitions()) {
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
