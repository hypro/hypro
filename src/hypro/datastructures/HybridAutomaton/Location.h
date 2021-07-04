/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

#ifndef INCL_FROM_HAHEADER
static_assert( false, "This file may only be included indirectly by HybridAutomaton.h" );
#endif

#include "../../types.h"
#include "Condition.h"
#include "decomposition/Decomposition.h"
#include "flow/operations.h"
#include "flow/typetraits.h"
#include "flow/visitors.h"

#include <iosfwd>
#include <string>
#include <variant>

namespace hypro {
template <typename Number>
class Transition;

template <typename Number>
class StochasticTransition;

template <typename Number>
using flowVariant = std::variant<linearFlow<Number>, affineFlow<Number>, rectangularFlow<Number>>;

/**
 * @brief      Class for a location of a hybrid automaton.
 * @details    The dynamics can be linear or rectangular, the class also provides ways to combine both. Furthermore, subspaces are supported.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class Location {
  public:
	using transitionVector = std::vector<std::unique_ptr<Transition<Number>>>;

  private:
	std::vector<flowVariant<Number>> mFlows;			 ///< Dynamics
	std::vector<DynamicType> mFlowTypes;				 ///< Types of dynamics
	std::vector<carl::Interval<Number>> mExternalInput;	 ///< External input/disturbance
	bool mHasExternalInput = false;						 ///< Cache-flag
	transitionVector mTransitions;						 ///< Outgoing transitions
	Condition<Number> mInvariant;						 ///< Invariant condition
	std::string mName = "";								 ///< Name of the location
	unsigned mId;										 ///< ID - was used for comparison (deprecated)
	mutable std::size_t mHash = 0;						 ///< Hash of the location
	bool mIsUrgent = false;								 ///< Flag indicating that a location is urgent

  public:
	/// default constructor
	Location();
	/// construction by name
	Location( const std::string& name );
	/// copy constructor
	Location( const Location& loc );
	/// construction from flow matrix
	explicit Location( const matrix_t<Number>& mat );
	/// construction from matrix, vector and invariant condition
	Location( const matrix_t<Number>& mat, transitionVector&& trans, const Condition<Number>& inv );
	/// destructor
	virtual ~Location() {}
	/// assignment operator
	Location<Number>& operator=( const Location<Number>& in );

	/// returns the number of subspaces
	std::size_t getNumberSubspaces() const {
		assert( isConsistent() );
		return mFlows.size();
	}
	/// returns a linear flow for a subspace. The type of subspace needs to be linear, otherwise this operation fails.
	linearFlow<Number> getLinearFlow( std::size_t I = 0 ) const {
		assert( isConsistent() );
		return std::get<linearFlow<Number>>( mFlows[I] );
	}
	/// returns a rectangular flow for a subspace. The type of subspace needs to be rectangular, otherwise this operation fails.
	rectangularFlow<Number> getRectangularFlow( std::size_t I = 0 ) const {
		assert( isConsistent() );
		return std::get<rectangularFlow<Number>>( mFlows[I] );
	}
	/// getter for vector of flow-variants
	const std::vector<flowVariant<Number>>& getFlows() const {
		assert( isConsistent() );
		return mFlows;
	}
	/// getter for vector of flow types
	const std::vector<DynamicType>& getFlowTypes() const {
		assert( isConsistent() );
		return mFlowTypes;
	}
	/// returns index of the subspace the requested state space dimension is contained in (assuming linear, ascending order of subspaces and variables)
	std::size_t getSubspaceIndexForStateSpaceDimension( std::size_t dimension ) const;
	/// getter for invariant condition
	const Condition<Number>& getInvariant() const { return mInvariant; }
	/// getter for outgoing transitions
	const transitionVector& getTransitions() const { return mTransitions; }
	/// getter to non-const reference of transitions (allows in-place modifications)
	transitionVector& rGetTransitions() { return mTransitions; }
	const std::vector<carl::Interval<Number>>& getExternalInput() const { return mExternalInput; }
	/// returns whether the locations' dynamics is influenced by external input/disturbances
	bool hasExternalInput() const { return mHasExternalInput; }
	/// getter for the locations' id (deprecated)
	[[deprecated( "use hash() instead" )]] unsigned getId() const { return mId; }
	/// getter for the name of the location
	std::string getName() const { return mName; }
	/// getter for the urgency-flag
	bool isUrgent() const { return mIsUrgent; }
	/// getter for the state space dimension
	std::size_t dimension() const;
	/// getter for the state space dimension of a specific subspace
	std::size_t dimension( std::size_t i ) const;
	/// setter for the name
	void setName( const std::string& name ) {
		mName = name;
		mHash = 0;
	}
	/// setter for linear flow of a subspace (optional, default 0) via passing a matrix
	void setFlow( const matrix_t<Number>& f, std::size_t I = 0 ) { this->setLinearFlow( linearFlow<Number>( f ), I ); }
	/// setter for linear flow of a subspace (optional, default 0)
	void setFlow( const linearFlow<Number>& f, std::size_t I = 0 ) { this->setLinearFlow( f, I ); }
	/// setter for rectangular flow of a subspace (optional, default 0)
	void setFlow( const rectangularFlow<Number>& f, std::size_t I = 0 ) { this->setRectangularFlow( f, I ); }
	/// explicit setter of linear flow for a subspace (optional, default 0)
	void setLinearFlow( const linearFlow<Number>& f, std::size_t I = 0 );
	/// explicit setter of rectangular flow for a subspace (optional, default 0)
	void setRectangularFlow( const rectangularFlow<Number>& f, std::size_t I = 0 );
	/// setter for invariant condition
	void setInvariant( const Condition<Number>& inv ) {
		mInvariant = inv;
		mHash = 0;
	}
	/// allows setting the location to being urgent
	void setUrgent( bool urgent = true ) { mIsUrgent = urgent; }
	/// setter for vector of outgoing transitions (move)
	void setTransitions( transitionVector&& trans );
	/// adds outgoing transitions
	void addTransition( std::unique_ptr<Transition<Number>>&& trans );
	void removeTransition( Transition<Number>* transitionPtr ) {
	    mTransitions.erase(std::find_if(std::begin(mTransitions), std::end(mTransitions), [&](auto& uPtr){
			  return uPtr.get() == transitionPtr;
		  }));
	}
	/// creates a transition from this location to the target
	Transition<Number>* createTransition( Location<Number>* target );
	/// adds a copy of the passed transition with the source being this location
	Transition<Number>* createTransition( Transition<Number>* target );
	/// setter for external input/disturbance
	void setExtInput( const std::vector<carl::Interval<Number>>& b );
	/// returns hash value of the location
	std::size_t hash() const;

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
	//bool isComposedOf( const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars ) const;

	/// returns dot-representation of the location
	std::string getDotRepresentation( const std::vector<std::string>& vars ) const;
	/// decomposes location into subspaces defined in the passed decomposition
	void decompose( const Decomposition& decomposition );
	/// hash-based less operator
	inline bool operator<( const Location<Number>& rhs ) const {
		if ( this->hash() != rhs.hash() ) {
			return this->hash() < rhs.hash();
		} else {
			//Case where we have to compare members, as same hashes do not necessarily mean equality between the locations.
			//As order does not mean anything here semantically, we are free to choose anything that gives us an ordering between locations.
			//Here, we choose the lexicographical order between the names.
			return mName < rhs.getName();
		}
	}
	/// equal comparison
	inline bool operator==( const Location<Number>& rhs ) const {
		TRACE( "hypro.datastructures", "Comparison of " << *this << " and " << rhs );
		if ( mName != rhs.getName() ) {
			TRACE( "hypro.datastructures", "Name not equal." );
			return false;
		}
		if ( mInvariant != rhs.getInvariant() ) {
			TRACE( "hypro.datastructures", "Invariants not equal." );
			return false;
		}
		if ( mFlows.size() != rhs.getFlows().size() ) {
			TRACE( "hypro.datastructures", "Number of flows not equal." );
			return false;
		}
		if ( mFlowTypes.size() != rhs.getFlowTypes().size() ) {
			TRACE( "hypro.datastructures", "Number of flows not equal." );
			return false;
		}
		for ( std::size_t i = 0; i < mFlows.size(); ++i ) {
			if ( mFlowTypes[i] != rhs.getFlowTypes()[i] ) {
				return false;
			}
			switch ( mFlowTypes[i] ) {
				case DynamicType::linear:
					if ( std::get<linearFlow<Number>>( mFlows[i] ) != std::get<linearFlow<Number>>( rhs.getFlows()[i] ) ) {
						TRACE( "hypro.datastructures", "Dynamics not equal" );
						return false;
					}
					break;
				case DynamicType::rectangular:
					if ( std::get<rectangularFlow<Number>>( mFlows[i] ) != std::get<rectangularFlow<Number>>( rhs.getFlows()[i] ) ) {
						TRACE( "hypro.datastructures", "Dynamics not equal" );
						return false;
					}
					break;
				default:
					assert( false );
					return false;
					break;
			}
		}
		/*
		if ( mExternalInput != rhs.getExternalInput() ) {
			//TRACE("hypro.datastructures","External input not equal.");
			std::cout << "ExtIn not equal" << std::endl;
			return false;
		}
		*/

		if ( mTransitions.size() != rhs.getTransitions().size() ) {
			TRACE( "hypro.datastructures", "Number of transitions not equal: " << mTransitions.size() << " (lhs) vs. " << rhs.getTransitions().size() << " (rhs)." );
			return false;
		}
		/*
        for(auto lhsIt = mTransitions.begin(); lhsIt != mTransitions.end(); ++lhsIt) {
            bool found = false;
            for(auto rhsIt = rhs.getTransitions().begin(); rhsIt != rhs.getTransitions().end(); ++rhsIt) {
                if(**lhsIt == **rhsIt) {
                    found = true;
                    break;
                }
            }
            if(!found){
                TRACE("hypro.datastructures","Transition not equal.");
                return false;
            }
        }
        */
		TRACE( "hypro.datastructures", "Equal." );
		return true;
	}
	/// not equal comparison
	inline bool operator!=( const Location<Number>& rhs ) const { return !( *this == rhs ); }
	/// outstream operator
	friend std::ostream& operator<<( std::ostream& ostr, const Location<Number>& l ) {
		ostr << l.getName() << " @" << &l << " {\n"
			 << "Flow.: "
			 << "\n";
		for ( size_t i = 0; i < l.getNumberSubspaces(); i++ ) {
			switch ( l.getFlowTypes()[i] ) {
				case DynamicType::linear:
					ostr << std::get<linearFlow<Number>>( l.getFlows()[i] ) << std::endl;
					break;
				case DynamicType::rectangular:
					ostr << std::get<rectangularFlow<Number>>( l.getFlows()[i] ) << std::endl;
					break;
				default:
					break;
			}
		}
		ostr << "Inv.:\n"
			 << l.getInvariant();
		//ostr << l.getInvariant().getDiscreteCondition() << std::endl;
		//ostr << "ExternalInput:\n" << l.getExternalInput() << std::endl;
		ostr << "Transitions: " << std::endl;
		for ( const auto& transitionPtr : l.getTransitions() ) {
			ostr << *( transitionPtr.get() ) << std::endl;
		}
		ostr << "\n}";
		return ostr;
	}

  private:
	bool isConsistent() const {
		return mFlows.size() == mFlowTypes.size();
	}
};

/**
 * @brief Pointer-comparison functor
 * @tparam Number
 */
template <typename Number>
struct locPtrComp {
	bool operator()( const Location<Number>* lhs, const Location<Number>* rhs ) const { return ( *lhs < *rhs ); }
	bool operator()( const std::unique_ptr<Location<Number>>& lhs, const std::unique_ptr<Location<Number>>& rhs ) const { return ( *lhs < *rhs ); }
};

template<typename Number>
//std::unique_ptr<Location<Number>> parallelCompose(const std::unique_ptr<Location<Number>>& lhs
//                                , const std::unique_ptr<Location<Number>>& rhs
std::unique_ptr<Location<Number>> parallelCompose(const Location<Number>* lhs
                                                , const Location<Number>* rhs
                                                , const std::vector<std::string>& lhsVar
                                                , const std::vector<std::string>& rhsVar
                                                , const std::vector<std::string>& haVar);

}  // namespace hypro

namespace std {

/**
 * @brief override of std::hash for locations.
 * @tparam Number
 */
template <typename Number>
struct hash<hypro::Location<Number>> {
	std::size_t operator()( const hypro::Location<Number>& loc ) const {
		//Flows
		std::size_t seed = 0;
		for ( const auto& f : loc.getFlows() ) {
			carl::hash_add( seed, std::visit( hypro::flowHashVisitor{}, f ) );
		}
		//Name
		carl::hash_add( seed, std::hash<std::string>()( loc.getName() ) );
		//Transitions
		for ( const auto& t : loc.getTransitions() ) {
			seed += std::hash<hypro::Transition<Number>*>()( t.get() );
		}
		// Invariant
		carl::hash_add( seed, loc.getInvariant().hash() );
		return seed;
	}
};

}  // namespace std

// clang-format off
#define INCL_FROM_LOCHEADER true

#include "Transition.h"
#include "Location.tpp"
// clang-format on
