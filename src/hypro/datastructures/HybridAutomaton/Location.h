/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#include "Condition.h"
#include "LocationManager.h"
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
 * @brief       A enum used to determine which values have been changed after the last operation.
 */
//enum LocationChange { NOCHANGE = 0, FLOWS, EXTINPUT, TRANSITIONS, INVARIANT, ID, NAME };

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
    //[[deprecated]]
    Location(unsigned id);
    ///@{
    /**
     * @param[in]  id    The identifier given by the LocationManager.
     * @param[loc] The original location which is copied.
     */
    //[[deprecated]]
    Location(unsigned id, const Location& loc);
    //[[deprecated]]
    Location(unsigned id, const matrix_t<Number>& mat);
    //[[deprecated]]
    Location(unsigned id, const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv);
    ///@}

private:
    mutable std::vector<matrix_t<Number>> mFlows;
    Box<Number> mExternalInput = Box<Number>::Empty();
    bool mHasExternalInput = false;
    transitionSet mTransitions;
    Condition<Number> mInvariant;
    std::string mName;
    //std::vector<LocationChange> mChanges;
    //[[deprecated]]
    unsigned mId;
    std::size_t mHash;

    std::size_t computeHash();

public:
  	//Location() = delete;
    Location();
    Location(const Location& loc);
    Location(const matrix_t<Number>& mat);
    Location(const matrix_t<Number>& mat, const transitionSet& trans, const Condition<Number>& inv);

    ~Location(){
        std::cout << "loc " << mName << " with id " << mId << " sagt tschau!\n";
    }

    std::size_t getNumberFlow() const { return mFlows.size(); }
    matrix_t<Number> getFlow(std::size_t I = 0) const { return mFlows.at(I); }
    matrix_t<Number>& rGetFlow(std::size_t I = 0) { return mFlows[I]; }
    const std::vector<matrix_t<Number>>& getFlows() const { return mFlows; }
    const Condition<Number>& getInvariant() const { return mInvariant; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const Box<Number>& getExternalInput() const { return mExternalInput; }
    bool hasExternalInput() const { return mHasExternalInput; }
    unsigned getId() const { return mId; }
	std::string getName() const { return mName; }

    void setName(const std::string& name) { mName = name; }
    void setFlow(const matrix_t<Number>& mat, std::size_t I = 0);
    void setInvariant(const Condition<Number>& inv) { mInvariant = inv; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void addTransition(Transition<Number>* trans) { mTransitions.insert(trans); }
    void setExtInput(const Box<Number>& b);

    std::size_t getHash() const { return mHash; }

    /**
     * @brief      Determines if this composed of rhs and some potential rest.
     * @details    Checks whether this location can be the result of a parallel composition where rhs is involved as a composite.
     *
     * @param[in]  rhs       The right hand side
     * @param[in]  rhsVars   The right hand side variables
     * @param[in]  thisVars  The variables of this location
     *
     * @return     True if composed of, False otherwise.
     */
    bool isComposedOf(const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars) const;
    std::string getDotRepresentation(const std::vector<std::string>& vars) const;

    //inline bool operator<(const Location<Number>& rhs) const { return (mId < rhs.getId()); }
    //inline bool operator==(const Location<Number>& rhs) const { return (mId == rhs.getId()); }
    //inline bool operator!=(const Location<Number>& rhs) const { return (mId != rhs.getId()); }

    inline bool operator<(const Location<Number>& rhs) const { return (mHash < rhs.getHash()); }
    inline bool operator==(const Location<Number>& rhs) const { return (mHash == rhs.getHash()); }
    inline bool operator!=(const Location<Number>& rhs) const { return (mHash != rhs.getHash()); }

    friend std::ostream& operator<<(std::ostream& ostr, const Location<Number>& l) {

    #ifdef HYPRO_LOGGING
	    //matrix_t<Number> tmp = matrix_t<Number>(l.getInvariant().getMatrix().rows(), l.getInvariant().getMatrix().cols() + 1);
	    //tmp << l.getInvariant().getMatrix(), l.getInvariant().getVector();
	    ostr << "location " << l.getName() << " ptr "<< &l  << " (id: " << l.getId() << ")"<< std::endl << "\t Flow: " << std::endl << l.getFlow() << std::endl << "\t Inv: " << std::endl << l.getInvariant();
	    //ostr << l.getInvariant().getDiscreteCondition() << std::endl;
        ostr << "ExternalInput:\n" << l.getExternalInput() << std::endl;
	    ostr << "Transitions: " << std::endl;
	    for (auto transitionPtr : l.getTransitions()) {
	        ostr << *transitionPtr << std::endl;
	    }
      ostr << "and transitions.size() is: " << l.getTransitions().size() << std::endl;
	    ostr << std::endl << ")";
	#endif
	    return ostr;
    }
};

template<typename Number>
struct locPtrComp {
    bool operator()(const Location<Number>* lhs, const Location<Number>* rhs) const { return (*lhs < *rhs); }
    bool operator()(const std::unique_ptr<Location<Number>>& lhs, const std::unique_ptr<Location<Number>>& rhs) const { return (*lhs < *rhs); }
};

//template<typename Number>
//std::size_t LocationHashValue(const Location<Number>* loc);

template<typename Number>
//Location<Number>* parallelCompose(const Location<Number>* lhs
//								, const Location<Number>* rhs
//								, const std::vector<std::string>& lhsVar
//								, const std::vector<std::string>& rhsVar
//								, const std::vector<std::string>& haVar);

std::unique_ptr<Location<Number>> parallelCompose(const std::unique_ptr<Location<Number>>& lhs
                                , const std::unique_ptr<Location<Number>>& rhs
                                , const std::vector<std::string>& lhsVar
                                , const std::vector<std::string>& rhsVar
                                , const std::vector<std::string>& haVar);


}  // namespace hypro

namespace std {

    template<typename Number>
    struct hash<hypro::Location<Number>*> {
        std::size_t operator()(const hypro::Location<Number>* locPtr) const
        {
            //return hypro::LocationHashValue(locPtr);
            return locPtr->computeHash();
        }
    };

}  // namespace std

#include "Location.tpp"
