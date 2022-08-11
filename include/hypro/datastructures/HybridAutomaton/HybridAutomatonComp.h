/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Class that describes a hybrid automaton with components.
 * @file   HybridAutomatonComp.cpp
 * @author Stefan Schupp <stefan.schupp@tuwien.ac.at>
 */

#pragma once

#include "HybridAutomaton.h"
#include "Location.h"
#include "hypro/util/convenienceSTLFunctions.h"
#include "hypro/util/exceptions.h"

namespace hypro {

template <typename Number>
class HybridAutomatonComp;

template <typename Number>
class ComposedLocation : public Location<Number> {
	friend class HybridAutomatonComp<Number>;

  public:
	using CompTransition = Transition<Number, ComposedLocation<Number>>;
	using transitionVector = std::vector<std::unique_ptr<CompTransition>>;

  private:
	mutable bool mIsValid = false;					///< Flag indicating whether the location has been initialized
	mutable transitionVector mTransitions;			///< Outgoing transitions
	std::vector<std::size_t> mCompositionals;		///< Indices of the locations in the single automata
	const HybridAutomatonComp<Number>& mAutomaton;	///< Reference to the original automaton this location is part of

  public:
	/// Helper function which converts a location-stub to a fully composed location
	void validate() const;
	/// constructor
	ComposedLocation( const HybridAutomatonComp<Number>& automaton )
		: mAutomaton( automaton ) {}

	ComposedLocation( ComposedLocation<Number>&& other )
		: mIsValid( false )
		, mTransitions()
		, mCompositionals( std::move( other.mCompositionals ) )
		, mAutomaton( std::move( other.mAutomaton ) ) {
	}

	ComposedLocation( const ComposedLocation<Number>& other )
		: mIsValid( false )
		, mTransitions()
		, mCompositionals( other.mCompositionals )
		, mAutomaton( other.mAutomaton ) {
	}
	/// getter of indices of locations combined in this location
	const std::vector<std::size_t>& getComponentLocationIndices() const {
		return mCompositionals;
	}
	/// returns the number of subspaces
	std::size_t getNumberSubspaces() const {
		validate();
		return Location<Number>::getNumberSubspaces();
	}
	/// returns a linear flow for a subspace. The type of subspace needs to be linear, otherwise this operation fails.
	linearFlow<Number> getLinearFlow( std::size_t I = 0 ) const {
		validate();
		return Location<Number>::getLinearFlow( I );
	}
	/// returns a rectangular flow for a subspace. The type of subspace needs to be rectangular, otherwise this operation fails.
	rectangularFlow<Number> getRectangularFlow( std::size_t I = 0 ) const {
		validate();
		return Location<Number>::getRectangularFlow( I );
	}
	/// getter for vector of flow-variants
	const std::vector<flowVariant<Number>>& getFlows() const {
		validate();
		return Location<Number>::getFlows();
	}
	/// getter for vector of flow types
	const std::vector<DynamicType>& getFlowTypes() const {
		validate();
		return Location<Number>::getFlowTypes();
	}
	/// returns index of the subspace the requested state space dimension is contained in (assuming linear, ascending order of subspaces and variables)
	std::size_t getSubspaceIndexForStateSpaceDimension( std::size_t dimension ) const {
		validate();
		return Location<Number>::getSubspaceIndexForStateSpaceDimension( dimension );
	}
	/// getter for invariant condition
	const Condition<Number>& getInvariant() const {
		validate();
		return Location<Number>::getInvariant();
	}
	/// getter for outgoing transitions
	const transitionVector& getTransitions() const {
		validate();
		return mTransitions;
	}
	/// getter to non-const reference of transitions (allows in-place modifications)
	transitionVector& rGetTransitions() {
		validate();
		return Location<Number>::rGetTransitions();
	}
	/// getter for the name of the location
	std::string getName() const {
		validate();
		return Location<Number>::getName();
	}
	/// getter for the urgency-flag
	bool isUrgent() const {
		validate();
		return Location<Number>::isUrgent();
	}
	/// getter to query whether the location is a stub or whether it is fully composed
	inline bool isValid() const {
		return mIsValid;
	}
	/// getter for the state space dimension
	std::size_t dimension() const {
		validate();
		return Location<Number>::dimension();
	};
	/// getter for the state space dimension of a specific subspace
	std::size_t dimension( std::size_t i ) const {
		validate();
		return Location<Number>::dimension( i );
	}
	/// returns hash value of the location
	std::size_t hash() const {
		validate();
		return Location<Number>::hash();
	}
	/// returns dot-representation of the location
	std::string getDotRepresentation( const std::vector<std::string>& vars ) const { throw NotImplemented(); }
	/// decomposes location into subspaces defined in the passed decomposition
	void decompose( const std::vector<std::vector<std::size_t>>& partition ) { throw NotImplemented(); }
	/// hash-based less operator
	inline bool operator<( const ComposedLocation<Number>& rhs ) const {
		validate();
		rhs.validate();
		return Location<Number>::operator<( rhs );
	}
	/// equal comparison
	inline bool operator==( const ComposedLocation<Number>& rhs ) const {
		validate();
		rhs.validate();
		return Location<Number>::operator==( rhs );
	}
	/// not equal comparison
	inline bool operator!=( const Location<Number>& rhs ) const { return !( *this == rhs ); }
	/// outstream operator
	friend std::ostream& operator<<( std::ostream& ostr, const ComposedLocation<Number>& l ) {
		l.validate();
		return Location<Number>::printContent();
	}
	/// only prints the content without the transitions, i.e., only the name, dynamics, and invariant constraints
	std::string printContent() const {
		validate();
		return Location<Number>::printContent();
	}

  private:
	/// hack to be able to modify the base class
	Location<Number>& castawayConst() const { return const_cast<ComposedLocation<Number>&>( *this ); }
};

/**
 * @brief      Class for linear hybrid automata with components.
 * @tparam     Number  Number type.
 */
template <typename Number>
class HybridAutomatonComp {
	friend class ComposedLocation<Number>;
	enum CACHE { INITIALSTATES = 0,
				 LOCALBADSTATES = 1,
				 GLOBALBADSTATES = 2,
				 VARIABLES = 3,
				 LABELS = 4,
				 Count };

  public:
	using LocationType = ComposedLocation<Number>;
	using Locations = std::list<LocationType>;
	using TransitionType = Transition<Number, LocationType>;
	using locationConditionMap = std::map<LocationType*, Condition<Number>>;
	using conditionVector = std::vector<Condition<Number>>;
	using variableVector = std::vector<std::string>;

  private:
	std::vector<HybridAutomaton<Number>> mAutomata;	 /// The set of hybrid automata that is composed.
	mutable Locations mLocations;					 /// Cache for the locations of the hybrid automaton already discovered.
	mutable locationConditionMap mInitialStates;	 /// The set of initial states.
	mutable locationConditionMap mLocalBadStates;	 /// The set of bad states which are bound to locations.
	mutable conditionVector mGlobalBadStates;		 /// The set of bad states which are not bound to any location.
	mutable std::vector<std::string> mVariables;	 /// Cache for the variables of the composed automata.
	mutable std::map<unsigned, std::vector<unsigned>> mSharedVars;
	mutable std::vector<bool> mCachesValid = std::vector<bool>( CACHE::Count, false );		 ///< Set of flags used to indicate cache validity
	mutable std::map<std::size_t, std::vector<long int>> mGlobalToLocalVars;				 ///< Mapping from global var idx to local ones
	mutable std::map<std::pair<std::size_t, long int>, std::size_t> mLocalToGlobalVars;		 ///< Mapping from automaton and var idx (pair) to global var idx
	mutable std::map<std::vector<std::size_t>, typename Locations::iterator> mComposedLocs;	 ///< Mapping from indices of components to the index in the location vector
	mutable std::set<Label> mLabels;														 ///< Jump-synchronizationLabels
	std::map<std::string, std::vector<std::pair<std::size_t, std::size_t>>> mMasters;		 ///< Maps Variables to sets of locations in which the dynamics of this variable is overriding dynamics in other components

  public:
	HybridAutomatonComp(){};

	~HybridAutomatonComp(){};

	void addAutomaton( HybridAutomaton<Number>&& automaton ) {
		// invalidate caches
		invalidateCaches();
		mAutomata.emplace_back( std::move( automaton ) );
	}

	void addMasterLocations( std::size_t componentIndex, const std::map<std::string, std::vector<std::size_t>>& masters ) {
		invalidateCaches();
		for ( const auto& [var, locationIndices] : masters ) {
			if ( mMasters.count( var ) == 0 ) {
				mMasters[var] = std::vector<std::pair<std::size_t, std::size_t>>();
			}
			for ( auto locIndex : locationIndices ) {
				mMasters[var].emplace_back( componentIndex, locIndex );
			}
		}
	}

	/**
	 * @brief 		Copy Assignment
	 * @param[in]	rhs 	The original hybrid automaton
	 * @details 	This operation is costly as it performs deep copies
	 */
	HybridAutomatonComp& operator=( const HybridAutomatonComp<Number>& rhs );

	/**
	 * @brief 		Move Assignment
	 * @param[in]	rhs 	The original hybrid automaton
	 */
	HybridAutomatonComp& operator=( HybridAutomatonComp<Number>&& rhs );

	/**
	 * @brief      Getter function.
	 */
	///@{
	//* @return The set of locations. */
	std::vector<LocationType*> getLocations() const;
	/// getter for a single location identified by its hash
	LocationType* getLocation( const std::size_t hash ) const;
	/// getter for a single location identified by its name
	LocationType* getLocation( const std::string& name ) const;
	//* @return The set of initial states. */
	const locationConditionMap& getInitialStates() const;
	//* @return The set of bad states bound to locations. */
	const locationConditionMap& getLocalBadStates() const;
	//* @return The set of bad states which are not bound to locations. */
	const conditionVector& getGlobalBadStates() const;
	//* @return The state space dimension. */
	unsigned dimension() const;
	//* @return The vector of variables. */
	const variableVector& getVariables() const;
	//* @return The set of all labels. */
	const std::set<Label>& getLabels() const;
	///@}

	/**
	 * @brief Decomposes an automaton into the components
	 *  defined by decomposition. The vector should contain
	 *  sets of variables that are at least syntactically
	 *  independet to each other.
	 */
	void decompose( const std::vector<std::vector<std::size_t>>& partition ) { throw NotImplemented(); }

	/// Reduction function, currently a no-op for compositional hybrid automata, as the reachable part is built on the fly anyway
	void reduce() {}

	/**
	 * @brief Function which tests whether this can be the result of a parallel composition with rhs.
	 *
	 * @param rhs Automaton which can be a component of this.
	 * @return True, if this is composed of rhs and some (possibly empty) rest.
	 */
	bool isComposedOf( const HybridAutomaton<Number>& rhs ) const {
		return std::any_of( std::begin( mAutomata ), std::end( mAutomata ), [&rhs]( const auto& ha ) { return ha == rhs; } );
	}

	std::string getDotRepresentation() const { throw NotImplemented(); }

	std::string getStatistics() const { throw NotImplemented(); }

	/**
	 * @brief      Comparison for equality operator.
	 * @param[in]  lhs   The left hand side.
	 * @param[in]  rhs   The right hand side.
	 * @return     True, if both automata are equal, false otherwise.
	 */
	friend bool operator==( const HybridAutomatonComp<Number>& lhs, const HybridAutomatonComp<Number>& rhs ) {
		return lhs.mAutomata == rhs.mAutomata;
	}

	friend bool operator!=( const HybridAutomatonComp<Number>& lhs, const HybridAutomatonComp<Number>& rhs ) {
		return !( lhs == rhs );
	}

	/**
	 * @brief      Parallel Composition Operator.
	 * @param[in]  lhs   The left hand side.
	 * @param[in]  rhs   The right hand side.
	 * @return     Return parallel composition of two Automata.
	 */
	// This template is needed or else gcc spits out the warning -Wno-non-template-friend
	// Num represents Number and Stat represents State
	/*
	template <typename Num>
	friend HybridAutomatonComp<Num> operator||( const HybridAutomatonComp<Num>& lhs, const HybridAutomatonComp<Num>& rhs ) {
		HybridAutomatonComp<Num> res;
		res.mAutomata.insert( std::begin( lhs.mAutomata ), std::end( lhs.mAutomata ) );
		res.mAutomata.insert( std::begin( rhs.mAutomata ), std::end( rhs.mAutomata ) );
		res.mCachesValid = false;
		return res;
	}
	 */

	inline friend std::ostream& operator<<( std::ostream& ostr, const HybridAutomatonComp<Number>& a ) {
		throw NotImplemented();
		return ostr;
	}

	inline bool checkConsistency() const {
		for ( const auto& l : mLocations ) {
			if ( !l ) return false;
		}
		return true;
	}

  private:
	void setVariableMapping() const;
	void invalidateCaches() const;
};
}  // namespace hypro

#include "HybridAutomatonComp.tpp"
