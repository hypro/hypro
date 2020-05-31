/*
 * Class that describes one location of a hybrid automaton.
 * File:   location.h
 * Author: stefan & ckugler
 * Created on April 30, 2014, 9:06 AM
 */

#pragma once

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
using flowVariant = std::variant<linearFlow<Number>, affineFlow<Number>, rectangularFlow<Number>>;

/**
 * @brief      Class for location.
 * @tparam     Number  The used number type.
 */
template <typename Number>
class Location {
  public:
	using transitionVector = std::vector<std::unique_ptr<Transition<Number>>>;

  private:
	mutable std::vector<linearFlow<Number>> mLinearFlows;
	mutable std::vector<rectangularFlow<Number>> mRectangularFlows;
	std::vector<carl::Interval<Number>> mExternalInput;
	bool mHasExternalInput = false;
	transitionVector mTransitions;
	Condition<Number> mInvariant;
	std::string mName = "";
	unsigned mId;
	mutable std::size_t mHash = 0;

  public:
	Location();
	Location( const std::string& name );
	Location( const Location& loc );
	explicit Location( const matrix_t<Number>& mat );
	Location( const matrix_t<Number>& mat, transitionVector&& trans, const Condition<Number>& inv );
	~Location() {}

	Location<Number>& operator=( const Location<Number>& in );

	std::size_t getNumberFlow() const { return mLinearFlows.size(); }
	linearFlow<Number> getLinearFlow( std::size_t I = 0 ) const { return mLinearFlows.at( I ); }
	linearFlow<Number>& rGetLinearFlow( std::size_t I = 0 ) { return mLinearFlows[I]; }
	rectangularFlow<Number> getRectangularFlow( std::size_t I = 0 ) const { return mRectangularFlows.at( I ); }
	rectangularFlow<Number>& rGetRectangularFlow( std::size_t I = 0 ) { return mRectangularFlows[I]; }

	const std::vector<linearFlow<Number>>& getLinearFlows() const { return mLinearFlows; }
	const std::vector<rectangularFlow<Number>>& getRectangularFlows() const { return mRectangularFlows; }

	const Condition<Number>& getInvariant() const { return mInvariant; }
	const transitionVector& getTransitions() const { return mTransitions; }
	transitionVector& rGetTransitions() { return mTransitions; }
	const std::vector<carl::Interval<Number>>& getExternalInput() const { return mExternalInput; }
	bool hasExternalInput() const { return mHasExternalInput; }
	[[deprecated( "use hash() instead" )]] unsigned getId() const { return mId; }
	std::string getName() const { return mName; }
	std::size_t dimension() const;
	std::size_t dimension( std::size_t i ) const;

	void setName( const std::string& name ) {
		mName = name;
		mHash = 0;
	}
	void setFlow( const matrix_t<Number>& f, std::size_t I = 0 ) { this->setLinearFlow( linearFlow<Number>( f ), I ); }
	void setFlow( const linearFlow<Number>& f, std::size_t I = 0 ) { this->setLinearFlow( f, I ); }
	void setFlow( const rectangularFlow<Number>& f, std::size_t I = 0 ) { this->setRectangularFlow( f, I ); }
	void setLinearFlow( const linearFlow<Number>& f, std::size_t I = 0 );
	void setRectangularFlow( const rectangularFlow<Number>& f, std::size_t I = 0 );
	void setLinearFlow( const std::vector<linearFlow<Number>>& flows ) {
		mLinearFlows = flows;
		mHash = 0;
	};
	void setRectangularFlow( const std::vector<rectangularFlow<Number>>& flows ) {
		mRectangularFlows = flows;
		mHash = 0;
	};
	void setInvariant( const Condition<Number>& inv ) {
		mInvariant = inv;
		mHash = 0;
	}
	void setTransitions( transitionVector&& trans );
	void addTransition( std::unique_ptr<Transition<Number>>&& trans );
	//void updateTransition(Transition<Number>* original, Transition<Number>* newT);
	void setExtInput( const std::vector<carl::Interval<Number>>& b );

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
	bool isComposedOf( const Location<Number>& rhs, const std::vector<std::string>& rhsVars, const std::vector<std::string>& thisVars ) const;

	std::string getDotRepresentation( const std::vector<std::string>& vars ) const;

	/*
    * decomposes flow and invariant of this location.
    */
	void decompose( const Decomposition& decomposition );

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

	inline bool operator==( const Location<Number>& rhs ) const {
		//TRACE("hypro.datastructures","Comparison of " << *this << " and " << rhs);
		if ( this->hash() != rhs.hash() ) {
			//TRACE("hypro.datastructures","Hash " << this->hash() << " and " << rhs.hash() << " not equal.");
			return false;
		}
		if ( mName != rhs.getName() ) {
			//TRACE("hypro.datastructures","Name not equal.");
			return false;
		}
		if ( mInvariant != rhs.getInvariant() ) {
			//TRACE("hypro.datastructures","Invariants not equal.");
			return false;
		}
		if ( mLinearFlows.size() != rhs.getLinearFlows().size() ) {
			//TRACE("hypro.datastructures","Number of flows not equal.");
			return false;
		}
		for ( std::size_t i = 0; i < mLinearFlows.size(); ++i ) {
			if ( mLinearFlows[i] != rhs.getLinearFlow( i ) ) {
				//TRACE("hypro.datastructures","Flows not equal.");
				return false;
			}
			if ( mRectangularFlows[i] != rhs.getRectangularFlow( i ) ) {
				//TRACE("hypro.datastructures","Flows not equal.");
				return false;
			}
		}
		if ( mExternalInput != rhs.getExternalInput() ) {
			//TRACE("hypro.datastructures","External input not equal.");
			return false;
		}
		/*
        if(mTransitions.size() != rhs.getTransitions().size()) {
            TRACE("hypro.datastructures","Number of transitions not equal.");
            return false;
        }
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
		//TRACE("hypro.datastructures","Equal.");
		return true;
	}

	inline bool operator!=( const Location<Number>& rhs ) const { return !( *this == rhs ); }

	friend std::ostream& operator<<( std::ostream& ostr, const Location<Number>& l ) {
#ifdef HYPRO_LOGGING
		ostr << "location " << l.getName() << " ptr " << &l << " (id: " << l.hash() << ")" << std::endl
			 << "\t Flow: " << std::endl;
		for ( size_t i = 0; i < l.getNumberFlow(); i++ ) {
			ostr << i << ": " << l.getLinearFlow( i ) << ", rect.: " << l.getRectangularFlow( i ) << std::endl;
		}
		ostr << "\t Inv: " << std::endl
			 << l.getInvariant();
		//ostr << l.getInvariant().getDiscreteCondition() << std::endl;
		//ostr << "ExternalInput:\n" << l.getExternalInput() << std::endl;
		ostr << "Transitions: " << std::endl;
		for ( const auto& transitionPtr : l.getTransitions() ) {
			ostr << *( transitionPtr.get() ) << std::endl;
		}
		ostr << "and transitions.size() is: " << l.getTransitions().size() << std::endl;
		ostr << std::endl
			 << ")";
#endif
		return ostr;
	}
};

template <typename Number>
struct locPtrComp {
	bool operator()( const Location<Number>* lhs, const Location<Number>* rhs ) const { return ( *lhs < *rhs ); }
	bool operator()( const std::unique_ptr<Location<Number>>& lhs, const std::unique_ptr<Location<Number>>& rhs ) const { return ( *lhs < *rhs ); }
};

/*
template<typename Number>
//std::unique_ptr<Location<Number>> parallelCompose(const std::unique_ptr<Location<Number>>& lhs
//                                , const std::unique_ptr<Location<Number>>& rhs
std::unique_ptr<Location<Number>> parallelCompose(const Location<Number>* lhs
                                                , const Location<Number>* rhs
                                                , const std::vector<std::string>& lhsVar
                                                , const std::vector<std::string>& rhsVar
                                                , const std::vector<std::string>& haVar);
*/

}  // namespace hypro

namespace std {

template <typename Number>
struct hash<hypro::Location<Number>> {
	std::size_t operator()( const hypro::Location<Number>& loc ) const {
		//TRACE( "hypro.datastructures", "Hash for location " << loc.getName() );
		//Flows
		std::size_t seed = 0;
		for ( const auto& f : loc.getLinearFlows() ) {
			//TRACE( "hypro.datastructures", "Add flow hash " << std::hash<hypro::linearFlow<Number>>()( f ) );
			carl::hash_add( seed, std::hash<hypro::linearFlow<Number>>()( f ) );
		}
		for ( const auto& f : loc.getRectangularFlows() ) {
			//TRACE( "hypro.datastructures", "Add flow hash " << std::hash<hypro::rectangularFlow<Number>>()( f ) );
			carl::hash_add( seed, std::hash<hypro::rectangularFlow<Number>>()( f ) );
		}

		//Name
		//TRACE( "hypro.datastructures", "Add name hash " << std::hash<std::string>()( loc.getName() ) );
		carl::hash_add( seed, std::hash<std::string>()( loc.getName() ) );

		////Transitions
		//std::size_t transitionHash = 0;
		//for(auto& t : mTransitions){
		//  seed += std::hash<Transition<Number>*>()(t);
		//}
		////Extinput
		//if(mHasExternalInput){
		//  seed += std::hash<Box<Number>>()(mExternalInput);
		//}

		// Invariant
		//TRACE( "hypro.datastructures", "Add invariant hash " << loc.getInvariant().hash() );
		carl::hash_add( seed, loc.getInvariant().hash() );

		//TRACE( "hypro.datastructures", "Resulting hash " << seed );
		return seed;
	}
};

}  // namespace std

#include "Location.tpp"
