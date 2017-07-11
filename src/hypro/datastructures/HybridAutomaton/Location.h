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
    friend LocationManager;

protected:
    using transitionSet = std::set<hydra::Transition<Number>*>;

    Location(unsigned id);
    Location(unsigned id, const Location& loc);
    Location(unsigned id, const hypro::matrix_t<Number>& mat);
    Location(unsigned id, const hypro::matrix_t<Number>& mat, const transitionSet& trans, const Condition& inv);
    Location(unsigned id, const hypro::matrix_t<Number>& mat, const transitionSet& trans, const Condition& inv,
             const hypro::matrix_t<Number>& extInputMat);

private:
    mutable hypro::matrix_t<Number> mFlow;
    hypro::matrix_t<Number> mExternalInput;
    transitionSet mTransitions;
    Condition mInvariant;
    unsigned mId;
    std::string mName;

public:
  	Location() = delete;
    ~Location() {}

    const hypro::matrix_t<Number>& getFlow() const { return mFlow; }
    const Condition& getInvariant() const { return mInvariant; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const hypro::matrix_t<Number>& getExternalInput() const { return mExternalInput; }
    unsigned getId() const { return mId; }
	std::string getName() const { return mName; }
    void setName(const std::string& name) { mName = name; }
    void setFlow(const hypro::matrix_t<Number>& mat) { mFlow = mat; }
    void setInvariant(const hydra::Condition& inv) { mInvariant = inv; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void addTransition(Transition<Number>* trans) { mTransitions.insert(trans); }
    void setExtInputMat(const hypro::matrix_t<Number>& mat) { mExternalInput = mat; }

    inline bool operator<(const Location<Number>& rhs) const { return (mId < rhs.getId()); }
    inline bool operator==(const Location<Number>& rhs) const { return (mId == rhs.getId()); }
    inline bool operator!=(const Location<Number>& rhs) const { return (mId != rhs.getId()); }
    friend std::ostream& operator<<(std::ostream& ostr, const Location<Number>& l);
};

template<typename Number>
struct locPtrComp {
    bool operator()(const Location<Number>* lhs, const Location<Number>* rhs) const { return (*lhs < *rhs); }
};

}  // namespace hypro

#include "Location.tpp"