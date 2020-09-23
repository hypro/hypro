/*
 * Class that describes a hybrid automaton.
 * @file   hybridAutomaton.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since 	2014-04-30
 * @version	2015-03-07
 */

#pragma once

#define INCL_FROM_HAHEADER true

#include "../../types.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"
#include "Condition.h"
#include "HybridAutomatonComp.h"
#include "Label.h"
#include "Location.h"
#include "Reset.h"
#include "decomposition/Decomposition.h"
#include "decomposition/decomposeConstraintSet.h"

#include <map>

namespace hypro {

/**
 * @brief      Class for linear hybrid automata.
 * @tparam     Number  Number type.
 * @details	   The automaton owns all the locations and transitions. Newly created locations and transitions
 			   can only be added as unique pointers. If another class/object requests a location/transition,
 			   then only normal pointers are returned.
 */
//template <typename Number, typename State = State_t<Number>>
template <typename Number>
class HybridAutomaton {
  public:
	using locationVector = std::vector<std::unique_ptr<Location<Number>>>;
	using locationConditionMap = std::map<const Location<Number>*, Condition<Number>>;
	using conditionVector = std::vector<Condition<Number>>;
	using variableVector = std::vector<std::string>;

  private:
	locationVector mLocations;			   /// The locations of the hybrid automaton.
	locationConditionMap mInitialStates;   /// The set of initial states.
	locationConditionMap mLocalBadStates;  /// The set of bad states which are bound to locations.
	conditionVector mGlobalBadStates;	   /// The set of bad states which are not bound to any location.
	variableVector mVariables;

  public:
	/**
  	 * @brief      	Default constructor.
  	 */
	HybridAutomaton() {}

	/**
     * @brief      	Copy constructor.
     *
     * @param[in]  	hybrid  The original hybrid automaton.
     * @details 	This operation is costly as it performs deep copies
     */
	HybridAutomaton( const HybridAutomaton<Number>& hybrid );

	/**
     * @brief      	Move constructor.
     *
     * @param[in]  	hybrid  The original hybrid automaton.
     */
	//HybridAutomaton(HybridAutomaton<Number>&& hybrid);

	/**
     * @brief 		Constructor from locations, transitions and initial states
     * @param[in]	locs 			Set of locations
     * @param[in]	trans 			Set of transitions
     * @param[in] 	initialStates 	Map of initial states
     */
	//HybridAutomaton(const locationVector& locs, const transitionVector& trans, const locationConditionMap& initialStates);
	//TOOOOOODOOOOOOO: This is missing
	HybridAutomaton( const locationVector& locs, const locationConditionMap& initialStates );

	/**
     * @brief 		Destructor
     */
	virtual ~HybridAutomaton() {}

	/**
     * @brief 		Copy Assignment
     *
     * @param[in]	rhs 	The original hybrid automaton
     * @details 	This operation is costly as it performs deep copies
     */
	HybridAutomaton& operator=( const HybridAutomaton<Number>& rhs );

	/**
     * @brief 		Move Assignment
     *
     * @param[in]	rhs 	The original hybrid automaton
     */
	HybridAutomaton& operator=( HybridAutomaton<Number>&& rhs );

	/**
     * @brief      Getter function.
     */
	///@{
	//* @return The set of locations. */
	std::vector<Location<Number>*> getLocations() const;
	Location<Number>* getLocation( const std::size_t hash ) const;
	Location<Number>* getLocation( const std::string& name ) const;
	//* @return The set of transitions. */
	std::vector<Transition<Number>*> getTransitions() const;
	//* @return The set of initial states. */
	const locationConditionMap& getInitialStates() const { return mInitialStates; }
	//* @return The set of bad states bound to locations. */
	const locationConditionMap& getLocalBadStates() const { return mLocalBadStates; }
	//* @return The set of bad states which are not bound to locations. */
	const conditionVector& getGlobalBadStates() const { return mGlobalBadStates; }
	//* @return The state space dimension. */
	unsigned dimension() const;
	//* @return The vector of variables. */
	const variableVector& getVariables() const { return mVariables; }
	//* @return The set of all labels. */
	const std::set<Label> getLabels() const;
	///@}

	/**
     * @brief      Setter function.
     */
	///@{
	void setLocations( locationVector&& locs ) {
		assert( checkConsistency() );
		mLocations.clear();
		mLocations = std::move( locs );
		assert( checkConsistency() );
	}
	void setInitialStates( const locationConditionMap& states ) { mInitialStates = states; }
	void setLocalBadStates( const locationConditionMap& states ) { mLocalBadStates = states; }
	void setGlobalBadStates( const conditionVector& states ) { mGlobalBadStates = states; }
	void setVariables( const variableVector& variables ) { mVariables = variables; }
	///@}

	/**
     * @brief      Extension function.
     */
	///@{
	const std::unique_ptr<Location<Number>>& addLocation( const Location<Number>& location );
	const std::unique_ptr<Location<Number>>& addLocation( std::unique_ptr<Location<Number>>&& location );
	void addTransition( std::unique_ptr<Transition<Number>>&& transition );
	void addInitialState( const Location<Number>* loc, const Condition<Number>& state ) { mInitialStates.emplace( std::make_pair( loc, state ) ); }
	void addLocalBadState( const Location<Number>* loc, const Condition<Number>& condition ) { mLocalBadStates.emplace( std::make_pair( loc, condition ) ); }
	void addGlobalBadState( const Condition<Number>& state ) { mGlobalBadStates.push_back( state ); }
	///@}

	Location<Number>* createLocation();

	/**
     * @brief Decomposes an automaton into the components
     *  defined by decomposition. The vector should contain
     *  sets of variables that are at least syntactically
     *  independet to each other.
     */
	void decompose( const Decomposition& decomposition );

	/**
     * @brief      Reduces the automaton, i.e. removes Locations which are not connected to the automaton by transitions.
     */
	void reduce();

	/**
     * @brief Function which tests whether this can be the result of a parallel composition with rhs.
     * @details Used to verify the result of operator|| for hybrid automata. Checks whether this automaton can be the composed of rhs and some
     * (potentially empty) other composite.
     *
     * @param rhs Automaton which can be a component of this.
     * @return True, if this is composed of rhs and some (possibly empty) rest.
     */
	bool isComposedOf( const HybridAutomaton<Number>& rhs ) const;

	std::string getDotRepresentation() const;

	std::string getStatistics() const;

	//TODO: replace this with operator== for sets of pointers to loc (if implemented this way, standard == operator of set is used,
	//which does not compare correctly
	template <typename T>
	bool equals( const std::vector<T*>& lhs, const std::vector<T*>& rhs ) const {
		if ( lhs.size() != rhs.size() ) return false;
		for ( auto lhsIt = lhs.begin(); lhsIt != lhs.end(); ++lhsIt ) {
			bool found = false;
			for ( auto rhsIt = rhs.begin(); rhsIt != rhs.end(); ++rhsIt ) {
				//std::cout << "now comparing " << (*(lhsIt))->hash() << " and " << (*(rhsIt))->hash() << std::endl;
				if ( ( *lhsIt )->hash() == ( *rhsIt )->hash() ) {
					found = true;
					break;
				}
			}
			if ( !found ) {
				return false;
			}
		}

		return true;
	}

	/**
     * @brief      Comparison for equality operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     True, if both automata are equal, false otherwise.
     */
	friend bool operator==( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs ) {
		if ( !( lhs.equals( lhs.getLocations(), rhs.getLocations() ) ) ) {
			TRACE( "hypro.datastructures.hybridAutomaton", "no equality of locations." );
			return false;
		}
		//if(!(lhs.equals(lhs.getTransitions(),rhs.getTransitions()))){
		//    TRACE("hypro.datastructures.hybridAutomaton", "no equality of transitions.");
		//    return false;
		//}
		if ( lhs.getInitialStates().size() != rhs.getInitialStates().size() ) {
			TRACE( "hypro.datastructures.hybridAutomaton", "initial set sizes were different." );
			return false;
		}
		if ( lhs.getInitialStates() != rhs.getInitialStates() ) {
			TRACE( "hypro.datastructures.hybridAutomaton", "no equality of initials." );

			TRACE( "hypro.datastructures.hybridAutomaton", "size of lhs initial set: " << lhs.getInitialStates().size() << " size of rhs initial set: " << rhs.getInitialStates().size() );
			auto rhsIt = rhs.getInitialStates().begin();
			for ( auto lhsIt = lhs.getInitialStates().begin(); lhsIt != lhs.getInitialStates().end(); ++lhsIt ) {
				if ( *( ( *lhsIt ).first ) != *( ( *rhsIt ).first ) ) {
					TRACE( "hypro.datastructures.hybridAutomaton", ( *lhsIt ).first->getName() << " with hash " << ( *lhsIt ).first->hash() << " unequal to " << ( *rhsIt ).first->getName() << " with hash " << ( *rhsIt ).first->hash() );
					return false;
				}
				if ( ( *lhsIt ).second != ( *rhsIt ).second ) {
					TRACE( "hypro.datastructures.hybridAutomaton", "states were different." );
					return false;
				}
				rhsIt++;
			}
		}
		if ( lhs.getLocalBadStates() != rhs.getLocalBadStates() ) {
			TRACE( "hypro.datastructures.hybridAutomaton", "no equality of local bads." );
			return false;
		}
		if ( lhs.getGlobalBadStates() != rhs.getGlobalBadStates() ) {
			TRACE( "hypro.datastructures.hybridAutomaton", "no equality of global bads." );
			return false;
		}

		return true;
	}

	friend bool operator!=( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs ) {
		return !( lhs == rhs );
	}

	/**
     * @brief      Parallel Composition Operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     Return parallel composition of two Automata.
     */
	//This template is needed or else gcc spits out the warning -Wno-non-template-friend
	//Num represents Number and Stat represents State
	template <typename Num>
	friend HybridAutomaton<Num> operator||( const HybridAutomaton<Num>& lhs, const HybridAutomaton<Num>& rhs );
	/**
     * @brief      Combination Operator.
     * @param[in]  lhs   The left hand side.
     * @param[in]  rhs   The right hand side.
     * @return     Return compositional Automata of two Automata.
     */
	friend HybridAutomatonComp<Number> operator+( const HybridAutomaton<Number>& lhs, const HybridAutomaton<Number>& rhs ) {
		HybridAutomatonComp<Number> hac;
		hac.addAutomata( lhs );
		hac.addAutomata( rhs );
		return hac;
	}

#ifdef HYPRO_LOGGING
	friend std::ostream& operator<<( std::ostream& ostr, const HybridAutomaton<Number>& a )
#else
	friend std::ostream& operator<<( std::ostream& ostr, const HybridAutomaton<Number>& )
#endif
	{
#ifdef HYPRO_LOGGING
		/*_ostr << "initial states: " << std::endl;
        for ( auto initialIT = a.initialStates().begin(); initialIT != a.initialStates().end(); ++initialIT ) {
            ostr << ( *initialIT ).first->id() << ": " << ( *initialIT ).second.first
                  << " <= " << ( *initialIT ).second.second << std::endl;
        }*/
		// TODO
		ostr << "initial states (" << a.getInitialStates().size() << "): " << std::endl;
		for ( auto initialIt = a.getInitialStates().begin(); initialIt != a.getInitialStates().end(); ++initialIt ) {
			ostr << ( ( *initialIt ).first )->getName() << ": " << ( *initialIt ).second << std::endl;
		}
		ostr << "locations (" << a.getLocations().size() << "): " << std::endl;
		for ( auto l : a.getLocations() ) {
			ostr << *l << std::endl;
		}
		//ostr << "transitions ("<< a.getTransitions().size() << "): " << std::endl;
		//for (const auto& transition : a.getTransitions()) {
		//    ostr << *transition << std::endl;
		//}
		ostr << "local bad states (" << a.getLocalBadStates().size() << "): " << std::endl;
		for ( auto badStateIt = a.getLocalBadStates().begin(); badStateIt != a.getLocalBadStates().end(); ++badStateIt ) {
			ostr << ( ( *badStateIt ).first )->getName() << ": " << ( *badStateIt ).second << std::endl;
		}
#endif
		return ostr;
	}

	bool checkConsistency() const {
		for ( const auto& l : mLocations ) {
			if ( !l ) return false;
		}
		return true;
	}
};

}  // namespace hypro

#include "HybridAutomaton.tpp"
