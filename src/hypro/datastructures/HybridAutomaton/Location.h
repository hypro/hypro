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
    Box<Number> mExternalInput;
    transitionSet mTransitions;
    Condition<Number> mInvariant;
    unsigned mId;
    std::string mName;

public:
  	Location() = delete;
    ~Location() {}

    std::size_t getNumberFlow() const { return mFlows.size(); }
    matrix_t<Number> getFlow(std::size_t I = 0) const { return mFlows.at(I); }
    matrix_t<Number>& rGetFlow(std::size_t I = 0) { return mFlows[I]; }
    const Condition<Number>& getInvariant() const { return mInvariant; }
    const transitionSet& getTransitions() const { return mTransitions; }
    const Box<Number>& getExternalInput() const { return mExternalInput; }
    unsigned getId() const { return mId; }
	std::string getName() const { return mName; }

    void setName(const std::string& name) { mName = name; }
    void setFlow(const matrix_t<Number>& mat, std::size_t I = 0);
    void setInvariant(const Condition<Number>& inv) { mInvariant = inv; }
    void setTransitions(const transitionSet& trans) { mTransitions = trans; }
    void addTransition(Transition<Number>* trans) { mTransitions.insert(trans); }
    void setExtInput(const Box<Number>& b) { mExternalInput = b; }

    /**
<<<<<<< 4dda3818d9d4266312171298c4e8fc2cbcd08d45
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
	/*
    * decomposes flow and invariant of this location.
    */
    void decompose(std::vector<std::vector<size_t>> decomposition);

    inline bool operator<(const Location<Number>& rhs) const { return (mId < rhs.getId()); }
    inline bool operator==(const Location<Number>& rhs) const { return (mId == rhs.getId()); }
    inline bool operator!=(const Location<Number>& rhs) const { return (mId != rhs.getId()); }

    friend std::ostream& operator<<(std::ostream& ostr, const Location<Number>& l) {
//<<<<<<< HEAD
//	    matrix_t<Number> tmp = matrix_t<Number>(l.getInvariant().getMatrix().rows(), l.getInvariant().getMatrix().cols() + 1);
//	    tmp << l.getInvariant().getMatrix(), l.getInvariant().getVector();
//	    ostr << "location " << l.getName() << " ptr "<< &l  << " (id: " << l.getId() << ")"<< std::endl << "\t Flow: " << std::endl << l.getFlow() << std::endl << "\t Invariant: " << std::endl << tmp;
//=======
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
};

template<typename Number>
Location<Number>* parallelCompose(const Location<Number>* lhs
								, const Location<Number>* rhs
								, const std::vector<std::string>& lhsVar
								, const std::vector<std::string>& rhsVar
								, const std::vector<std::string>& haVar)
{
	//compute flow
	matrix_t<Number> haFlow = matrix_t<Number>::Zero(haVar.size()+1, haVar.size()+1);

	//std::cout << "combine Locations " << lhs->getName() << " and " << rhs->getName() << std::endl;
	//std::cout << "With flows " << lhs->getFlow() << " and " << rhs->getFlow() << std::endl;

	std::size_t lhsIR = 0, lhsIC = 0, rhsIR = 0, rhsIC = 0;
	bool admissible = true; // flag used to denote a non-admissible flow, i.e. shared variables with different flow.
	// iterate over all rows
	for( std::size_t rowI = 0; rowI != haVar.size(); ++rowI ) {
		//std::cout << "Consider composed row " << rowI << " for var " << haVar[rowI] << std::endl;
		//std::cout << "lhsIR: " << lhsIR << std::endl;
		//std::cout << "rhsIR: " << rhsIR << std::endl;
		//std::cout << "Now left hand side." << std::endl;
		if(lhsIR < lhsVar.size() && lhsVar[lhsIR] == haVar[rowI]) {
			// iterate over all columns
			lhsIC = 0;
			for( std::size_t colI = 0; colI != haVar.size(); ++colI) {
				//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
				//std::cout << "lhsIC: " << lhsIC << std::endl;
				//std::cout << "rhsIC: " << rhsIC << std::endl;
				if(lhsVar[lhsIC] == haVar[colI]) {
					haFlow(rowI,colI) = lhs->getFlow()(lhsIR,lhsIC);
					++lhsIC;
					if(lhsIC == lhsVar.size()) {
						break;
					}
				}
			}
			++lhsIR;
		}
		//std::cout << "lhsIR: " << lhsIR << std::endl;
		//std::cout << "intermediate result: " << haFlow << std::endl;
		//std::cout << "Now right hand side." << std::endl;
		if(rhsIR < rhsVar.size() && rhsVar[rhsIR] == haVar[rowI]) {
			// iterate over all columns
			rhsIC = 0;
			for( std::size_t colI = 0; colI != haVar.size(); ++colI) {
				//std::cout << "Consider composed col " << colI << " for var " << haVar[colI] << std::endl;
				//std::cout << "lhsIC: " << lhsIC << std::endl;
				//std::cout << "rhsIC: " << rhsIC << std::endl;
				if(rhsVar[rhsIC] == haVar[colI]) {
					// TODO: the check is not entirely correct, since the flow can be non-admissible but set to 0 in lhs and something != 0 in rhs.
					if(haFlow(rowI,colI) != 0 && rhs->getFlow()(rhsIR,rhsIC) != haFlow(rowI,colI)) {
						admissible = false;
						break;
					}
					haFlow(rowI,colI) = rhs->getFlow()(rhsIR,rhsIC);
					++rhsIC;
					if(rhsIC == rhsVar.size()) {
						break;
					}
				}
			}
			++rhsIR;
		}
		//std::cout << "rhsIR: " << rhsIR << std::endl;
		if(!admissible)
			break;
	}

	// constant parts - TODO: integrate into loop above?
	for(unsigned rowI = 0; rowI < haFlow.rows()-1; ++rowI) {
		//std::cout << "Constant part for var " << haVar[rowI] << std::endl;
		unsigned lhsPos = 0;
		unsigned rhsPos = 0;
		bool leftFound = false;
		bool rightFound = false;
		while(lhsPos != lhsVar.size()) {
			if(lhsVar[lhsPos] == haVar[rowI]) {
				leftFound = true;
				//std::cout << "Found in lhs at pos " << lhsPos << std::endl;
				break;
			}
			++lhsPos;
		}

		while(rhsPos != rhsVar.size()) {
			if(rhsVar[rhsPos] == haVar[rowI]) {
				//std::cout << "Found in rhs at pos " << lhsPos << std::endl;
				rightFound = true;
				break;
			}
			++rhsPos;
		}
		if(leftFound) {
			// if is shared variable
			if(rightFound) {
				if(lhs->getFlow()(lhsPos, lhs->getFlow().cols()-1) != rhs->getFlow()(rhsPos, rhs->getFlow().cols()-1)) {
					admissible = false;
					break;
				} else {
					haFlow(rowI,haFlow.cols()-1) = lhs->getFlow()(lhsPos, lhs->getFlow().cols()-1);
					//std::cout << "Set to " << haFlow(rowI,haFlow.cols()-1) << std::endl;
				}
			} else {
				haFlow(rowI,haFlow.cols()-1) = lhs->getFlow()(lhsPos, lhs->getFlow().cols()-1);
				//std::cout << "Set to " << haFlow(rowI,haFlow.cols()-1) << std::endl;
			}
		} else {
			if(rightFound) {
				haFlow(rowI,haFlow.cols()-1) = rhs->getFlow()(rhsPos, rhs->getFlow().cols()-1);
				//std::cout << "Set to " << haFlow(rowI,haFlow.cols()-1) << std::endl;
			} else {
				//std::cout << "Variable is neither part of lhs or rhs!" << std::endl;
				assert(false);
				admissible = false;
			}
		}
	}

	if(!admissible) {
		FATAL("hypro.datastructures","Failed to create parallel composition of locations.");
		return nullptr;
	}

	Location<Number>* res = LocationManager<Number>::getInstance().create();

	//set name
	res->setName(lhs->getName()+"_"+rhs->getName());

	//std::cout << "Created flow: " << haFlow << " for location " << res->getName();

	res->setFlow(haFlow);

	//set invariant
	Condition<Number> inv = combine(lhs->getInvariant(), rhs->getInvariant(), haVar, lhsVar, rhsVar);
	res->setInvariant(inv);

	//std::cout << "Created invariant: " << inv << " for location " << res->getName();


	//std::cout << "setExtInput" << std::endl;
	//set extinput
	//loc->setExtInput(flowAndExtInput.second);
	return res;
}

}  // namespace hypro

#include "Location.tpp"
