
#pragma once

//#include "../../representations/GeometricObjectBase.h"
#include "../../representations/types.h"
#include "../../util/tuple_expansion/nth_element.h"
#include "Condition.h"
#include "Visitors.h"

#include <carl/interval/Interval.h>
#include <carl/util/tuple_util.h>
#include <variant>

namespace hypro {
template <typename Number>
class HybridAutomaton;

template <typename Number>
class Location;

/**
 * @brief      Class for state.
 * @details    A state can be used in the classical sense, i.e. as a combination of location and state set. Furthermore we allow to
 * to hold more than one set, aiming at providing datastructures for decoupled systems where state sets inside one state can be handled
 * independently.
 * @tparam     Number          The used number type.
 * @tparam     Representation  The type of the primary state set.
 * @tparam     Rargs           The type of the additional state sets.
 */
template <typename Number, typename Representation, typename... Rargs>
class State {
  public:
	template <std::size_t I>
	using nth_representation = nth_element<I, Representation, Rargs...>;

	using repVariant = std::variant<Representation, Rargs...>;	/// variant type for all possible state set representations.
	typedef Number NumberType;

  protected:
	const Location<Number>* mLoc = nullptr;												/// Location of the state.
	std::vector<repVariant> mSets;														/// The state sets wrapped in variant (repVariant).
	std::vector<representation_name> mTypes;											/// A vector holding the actual types corresponding to the state sets.
	carl::Interval<tNumber> mTimestamp = carl::Interval<tNumber>::unboundedInterval();	/// A timestamp.
	mutable std::vector<TRIBOOL> mIsEmpty;												/// A flag for each set which can be set to allow for a quick check for emptiness.

  private:
	/**
	 * @brief       Checks whether the type of all elements in mSets matches the type stored in mTypes.
	 */
	bool checkConsistency() const;

  public:
	/**
	 * @brief      Default constructor.
	 */
	State() = default;

	/**
	 * @brief      Copy constructor.
	 * @param[in]  orig  The original.
	 */
	State( const State<Number, Representation, Rargs...>& orig )
		: mLoc( orig.getLocation() )
		, mSets( orig.getSets() )
		, mTypes( orig.getTypes() )
		, mTimestamp( orig.getTimestamp() )
		, mIsEmpty( orig.getEmptyStates() ) {
		assert( checkConsistency() );
	}

	/**
	 * @brief Move constructor.
	 * @param orig The original.
	 */
	State( State<Number, Representation, Rargs...>&& orig )
		: mLoc( orig.getLocation() )
		, mSets( orig.getSets() )
		, mTypes( orig.getTypes() )
		, mTimestamp( orig.getTimestamp() )
		, mIsEmpty( orig.getEmptyStates() ) {
		assert( checkConsistency() );
	}

	/**
	 * @brief      Copy assignment operator.
	 * @param[in]  orig  The original
	 * @return     A copy of the original state.
	 */
	State<Number, Representation, Rargs...>& operator=( const State<Number, Representation, Rargs...>& orig ) {
		TRACE( "hypro.datastructures", "Assignment operator for state with " << orig.getNumberSets() << " sets." );
		// prevent self-assignment
		if ( &orig == this ) {
			return *this;
		}

		mLoc = orig.getLocation();
		mSets = orig.getSets();
		mTypes = orig.getTypes();
		assert( mSets.size() == mTypes.size() );
		assert( mSets.size() == orig.getNumberSets() );
		mTimestamp = orig.getTimestamp();
		mIsEmpty = orig.getEmptyStates();
		TRACE( "hypro.datastructures", "Assignment operator created state with " << mSets.size() << " sets." );
		assert( checkConsistency() );
		return *this;
	}

	/**
	 * @brief      Move assignment operator.
	 * @param[in]  orig  The original.
	 * @return     A state corresponding to the original.
	 */
	State<Number, Representation, Rargs...>& operator=( State<Number, Representation, Rargs...>&& orig ) {
		mLoc = orig.getLocation();
		mSets = orig.getSets();
		mTypes = orig.getTypes();
		mTimestamp = orig.getTimestamp();
		mIsEmpty = orig.getEmptyStates();
		assert( checkConsistency() );
		return *this;
	}

	/**
	 * @brief      Constructor from a location pointer.
	 * @param[in]  _loc  The location.
	 */
	State( const Location<Number>* _loc )
		: mLoc( _loc )
		, mSets()
		, mTypes()
		, mTimestamp( carl::Interval<tNumber>::unboundedInterval() )
		, mIsEmpty() {
		assert( mLoc != nullptr );
		assert( checkConsistency() );
	}

	/**
	 * @brief      Constructor.
	 * @param[in]  _loc        The location.
	 * @param[in]  _rep        The primary state set.
	 * @param[in]  sets        The additional state sets.
	 * @param[in]  _timestamp  The timestamp.
	 */
	State( const Location<Number>* _loc,
		   const Representation& _rep,
		   const Rargs... sets,
		   const carl::Interval<tNumber>& _timestamp = carl::Interval<tNumber>::unboundedInterval() )
		: mLoc( _loc )
		, mTimestamp( _timestamp ) {
		assert( mLoc != nullptr );
		mSets.push_back( _rep );
		mTypes.push_back( Representation::type() );
// parameter pack expansion
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
		int dummy[sizeof...( Rargs )] = { ( mSets.push_back( sets ), 0 )... };
		int dummy2[sizeof...( Rargs )] = { ( mTypes.push_back( sets.type() ), 0 )... };
#pragma GCC diagnostic pop
		(void)dummy;
		(void)dummy2;
		mIsEmpty = std::vector<TRIBOOL>{ mSets.size(), TRIBOOL::NSET };
		assert( checkConsistency() );
	}

	/**
	 * @brief Construct a new State object with just the state set.
	 *
	 * @param _rep  The state set.
	 * @param _timestamp
	 */
	State( const Representation& _rep,
		   const carl::Interval<tNumber>& _timestamp = carl::Interval<tNumber>::unboundedInterval() )
		: mLoc()
		, mTimestamp( _timestamp ) {
		mSets.push_back( _rep );
		mTypes.push_back( Representation::type() );
		mIsEmpty = std::vector<TRIBOOL>{ mSets.size(), TRIBOOL::NSET };
	}

	/**
	 * @brief Construct a new State object with just the state set.
	 *
	 * @param sets The state set.
	 * @param _timestamp
	 */
	//	State( const Rargs... sets,
	//		   const carl::Interval<tNumber>& _timestamp = carl::Interval<tNumber>::unboundedInterval() )
	//		: mLoc( nullptr )
	//		, mTimestamp( _timestamp ) {
	//// parameter pack expansion
	//#pragma GCC diagnostic push
	//#pragma GCC diagnostic ignored "-Wpedantic"
	//		int dummy[sizeof...( Rargs )] = { ( mSets.push_back( sets ), 0 )... };
	//		int dummy2[sizeof...( Rargs )] = { ( mTypes.push_back( sets.type() ), 0 )... };
	//#pragma GCC diagnostic pop
	//		(void)dummy;
	//		(void)dummy2;
	//		mIsEmpty = std::vector<TRIBOOL>{ mSets.size(), TRIBOOL::NSET };
	//		assert( checkConsistency() );
	//	}

	/**
	 * @brief      Gets the location.
	 * @return     The location.
	 */
	const Location<Number>* getLocation() const { return mLoc; }

	/**
	 * @brief      Gets the location.
	 * @return     The location.
	 */
	Location<Number>* rGetLocation() { return const_cast<Location<Number>*>( mLoc ); }

	/**
	 * @brief      Gets the number of contained sets.
	 * @return     The number of sets.
	 */
	std::size_t getNumberSets() const {
		assert( mSets.size() == mTypes.size() );
		return mSets.size();
	}

	/**
	 * @brief      Gets the i-th set.
	 * @param[in]  i     Set index.
	 * @return     The set.
	 */
	const std::variant<Representation, Rargs...>& getSet( std::size_t i = 0 ) const;

	/**
	 * @brief      Gets a reference to the i-th set.
	 * @param[in]  i     Set index.
	 * @return     The set.
	 */
	std::variant<Representation, Rargs...>& rGetSet( std::size_t i = 0 );

	/**
	 * @brief      Gets the type of the i-th set.
	 * @param[in]  i     Set index.
	 * @return     The set type.
	 */
	representation_name getSetType( std::size_t i = 0 ) const {
		TRACE( "hypro.datastructures", "Attempt to get set type at pos " << i << ", mTypes.size() = " << mTypes.size() );
		assert( i < mTypes.size() );
		TRACE( "hypro.datastructures", "Type is " << mTypes.at( i ) );
		assert( mSets.size() == mTypes.size() );
		assert( checkConsistency() );
		return mTypes.at( i );
	}

	/**
	 * @brief      Gets all contained sets.
	 * @return     The sets.
	 */
	const std::vector<repVariant>& getSets() const { return mSets; }

	/**
	 * @brief      Gets all contained types.
	 * @return     The types.
	 */
	const std::vector<representation_name>& getTypes() const { return mTypes; }

	/**
	 * @brief      Gets the timestamp.
	 * @return     The timestamp.
	 */
	const carl::Interval<tNumber>& getTimestamp() const { return mTimestamp; }

	/**
	 * @brief      Returns empty-flag value.
	 * @return     True if empty, False otherwise.
	 */
	bool isEmpty() const;

	/**
	 * @brief      Returns empty-flag values.
	 * @return     Vector of tribools.
	 */
	const std::vector<TRIBOOL>& getEmptyStates() const { return mIsEmpty; }

	/**
	 * @brief      Returns empty-flag values.
	 * @return     Vector of tribools.
	 */
	std::vector<TRIBOOL>& rGetEmptyStates() { return mIsEmpty; }

	/**
	 * @brief      Sets the location.
	 * @param[in]  l     The location.
	 */
	void setLocation( const Location<Number>* l ) { mLoc = l; }

	/**
	 * @brief      Sets the set at position i.
	 * @param[in]  s     The set.
	 * @param[in]  i     The position.
	 * @tparam     R     The type of s.
	 */
	template <typename R>
	void setSet( const R& s, std::size_t i = 0 );

	/**
	 * @brief     Sets the set at position i.
	 * @param[in]  s     The set.
	 * @param[in]  i     The position.
	 */
	void setSet( const repVariant& s, std::size_t i = 0 );

	/**
	 * @brief      Sets the set type for the set at position i.
	 * @param[in]  type  The type
	 * @param[in]  I     The position.
	 */
	void setSetType( representation_name type, std::size_t I = 0 ) {
		TRACE( "hypro.datastructures", "Attempt to set set type at pos " << I << " to type " << type << ", mSets.size() = " << mSets.size() << ", mTypes.size() = " << mTypes.size() );
		assert( mSets.size() == mTypes.size() );
		// if not enough sets, fill with default values.
		while ( I >= mSets.size() ) {
			mSets.emplace_back( Representation() );		 // some default set.
			mTypes.push_back( Representation::type() );	 // some default set type.
			mIsEmpty.push_back( TRIBOOL::NSET );
		}
		TRACE( "hypro.datastructures", "Set set type at pos " << I << " to type " << type );
		mTypes[I] = type;
		// assert(checkConsistency());
	}

	/**
	 * @brief      Sets the timestamp.
	 * @param[in]  t     The timestamp.
	 */
	void setTimestamp( const carl::Interval<tNumber>& t ) { mTimestamp = t; }

	/**
	 * @brief       Sets the sets.
	 * @details     Note that this method directly sets the sets while ignoring the consistency of the previously stored types
	 * @param[in]   sets  The sets.
	 */
	void setSets( const std::vector<std::variant<Representation, Rargs...>>& sets );

	/**
	 * @brief       Sets the sets.
	 * @details     A slower but safer version of setSets as it ensures that mTypes and mSets must be consistent
	 *              in terms of length and content when being set.
	 * @param[in]   sets    The sets to set.
	 */
	void setSetsSave( const std::vector<std::variant<Representation, Rargs...>>& sets );

	/**
	 * @brief      Sets the set.
	 * @details    Does not update the type for the respective position - can be used if type does not change to avoid unpacking.
	 *
	 * @param[in]  in    The set as a std::variant.
	 * @param[in]  I     The position in the sets vector.
	 */
	void setSetDirect( const repVariant& in, std::size_t I = 0 ) {
		TRACE( "hypro.datastructures", "Attempt to set set direct at pos " << I << ", mSets.size() = " << mSets.size() << ", mTypes.size() = " << mTypes.size() );
		assert( mSets.size() == mTypes.size() );
		assert( checkConsistency() );
		while ( I >= mSets.size() ) {
			mSets.emplace_back( Representation() );		 // some default set.
			mTypes.push_back( Representation::type() );	 // some default set type.
			mIsEmpty.push_back( TRIBOOL::NSET );
		}
		assert( checkConsistency() );
		mSets[I] = in;
	}

	template <typename To>
	void setAndConvertType( std::size_t I = 0 );

	/**
	 * @brief      Adds time to clocks.
	 * @details    This is a meta-function which allows to change multiple sets. Currently it only affects the timestamp.
	 * @param[in]  t     The time.
	 */
	void addTimeToClocks( tNumber t );

	template <typename Callable, typename... Args>
	auto visit( std::size_t setIndex, Callable c, Args&&... args ) {
		return std::visit( [&]( auto r ) { return c( r, std::forward<Args>( args )... ); }, mSets[setIndex] );
	}

	template <typename Callable, typename... Args>
	auto visit( std::size_t setIndex, Callable c, Args&&... args ) const {
		return std::visit( [&]( auto r ) { return c( r, std::forward<Args>( args )... ); }, mSets[setIndex] );
	}

	/**
	 * @brief      Meta-function to aggregate two states.
	 * @details    Each contained set is aggregated with its corresponding set in the passed state.
	 * @param[in]  in    The passed second state.
	 * @return     A state which represents the closure of the union of both states.
	 */
	State<Number, Representation, Rargs...> unite( const State<Number, Representation, Rargs...>& in ) const;

	/**
	 * @brief Meta function to compute the intersection of two state sets.
	 * @param in
	 * @return State<Number, Representation, Rargs...>
	 */
	State<Number, Representation, Rargs...> intersect( const State<Number, Representation, Rargs...>& in ) const;

	/**
	 * @brief      Meta-function to verify a state against a condition.
	 * @details    Each contained set is verified separately. Note that once one verification fails the whole function directly returns.
	 * This function is the equivalent to satisfiesHalfspaces in GeometricObject.
	 * @param[in]  in    The passed condition.
	 * @return     A pair of a Boolean and the resulting state. The Boolean is set to True, if the resulting state is not empty.
	 */
	std::pair<CONTAINMENT, State<Number, Representation, Rargs...>> satisfies( const Condition<Number>& in ) const;
	std::pair<CONTAINMENT, State<Number, Representation, Rargs...>> satisfiesHalfspaces( const matrix_t<Number>& constraints, const vector_t<Number>& constants ) const;

	/**
	 * @brief      Meta-function to verify the i-th set of a state against the i-th component of a condition.
	 * @param[in]  in    The passed condition.
	 * @param[in]  I	 The set index.
	 * @return     A pair of a Boolean and the resulting state. The Boolean is set to True, if the resulting state is not empty.
	 */
	std::pair<CONTAINMENT, State<Number, Representation, Rargs...>> partiallySatisfies( const Condition<Number>& in, std::size_t I ) const;

	State<Number, Representation, Rargs...> intersectHalfspaces( const matrix_t<Number>& constraints, const vector_t<Number>& constants, std::size_t I = 0 ) const;

	/**
	 * @brief      Meta-function which can be used to transform all contained sets at once with the passed parameters and adjust the
	 * timestamp as well.
	 * @param[in]  matrixExponentials   The solution to the differential equation system.
	 * @param[in]  timeStepSize         The time step size.
	 * @return     A state where each set has been transformed by the passed parameters and the timestamp has been increased by timeStepSize.
	 */
	State<Number, Representation, Rargs...> applyTimeStep( const std::vector<std::pair<const matrix_t<Number>&, const vector_t<Number>&>>& matrixExponentials, tNumber timeStepSize ) const;

	/**
	 * @brief      Meta-function which applies a transformation by the passed parameters and increases the timestamp for the i-th set.
	 * @param[in]  flow          The solution to the differential equation system (a matrix exponential).
	 * @param[in]  timeStepSize  The time step size.
	 * @param[in]  I             The set index.
	 * @return     A state where the i-th set has been transformed by the passed parameters and the timestamp has been increased by timeStepSize.
	 */
	State<Number, Representation, Rargs...> partiallyApplyTimeStep( const ConstraintSet<Number>& flow, tNumber timeStepSize, std::size_t I = 0 ) const;

	State<Number, Representation, Rargs...> computeAndApplyLinearTimeStep( const std::vector<const matrix_t<Number>&>& flows, tNumber timeStepSize ) const;

	State<Number, Representation, Rargs...> partiallyComputeAndApplyLinearTimeStep( const matrix_t<Number>& flow, tNumber timeStepSize, std::size_t I = 0 ) const;

	State<Number, Representation, Rargs...> computeAndApplyAffineTimeStep( const std::vector<const matrix_t<Number>&>& flows, tNumber timeStepSize ) const;

	State<Number, Representation, Rargs...> partiallyComputeAndApplyAffineTimeStep( const matrix_t<Number>& flow, tNumber timeStepSize, std::size_t I = 0 ) const;

	/**
	 * @brief      Meta-function, which applies an affine transformation to each set contained.
	 * @param[in]  trafos  The trafos represented as a vector of ConstraintSet.
	 * @return     A state where each set has been transformed by the corresponding ConstraintSet.
	 */
	State<Number, Representation, Rargs...> applyTransformation( const std::vector<ConstraintSet<Number>>& trafos ) const;
	State<Number, Representation, Rargs...> applyTransformation( const ConstraintSet<Number>& trafo, std::size_t I = 0 ) const;
	State<Number, Representation, Rargs...> linearTransformation( const matrix_t<Number>& matrix ) const;
	State<Number, Representation, Rargs...> affineTransformation( const matrix_t<Number>& matrix, const vector_t<Number>& vector ) const;
	State<Number, Representation, Rargs...> partialIntervalAssignment( const std::vector<carl::Interval<Number>>& assignments, std::size_t I ) const;

	State<Number, Representation, Rargs...> applyTransformation( const ConstraintSet<Number>& trafo ) const;

	/**
	 * @brief      Meta-function, which applies an affine transformation to each set contained in the state and whose index is contained
	 * in the second parameter.
	 * @param[in]  trafos  The trafos represented as a vector of ConstraintSet.
	 * @param[in]  sets    The indices of the sets to transform.
	 * @return     A state where each indexed set has been transformed by the corresponding ConstraintSet.
	 */
	State<Number, Representation, Rargs...> partiallyApplyTransformation( const std::vector<ConstraintSet<Number>>& trafos, const std::vector<std::size_t>& sets ) const;

	/**
	 * @brief      Meta-function, which applies an affine transformation to the i-th set contained in the state
	 * @param[in]  trafo  The trafo
	 * @param[in]  I      The set index.
	 * @return     A state where the i-th set has been transformed by the passed parameters.
	 */
	State<Number, Representation, Rargs...> partiallyApplyTransformation( const ConstraintSet<Number>& trafo, std::size_t I ) const;

	// TODO: Documentation from here on

	State<Number, Representation, Rargs...> minkowskiSum( const State<Number, Representation, Rargs...>& rhs ) const;

	State<Number, Representation, Rargs...> partiallyMinkowskiSum( const State<Number, Representation, Rargs...>& rhs, std::size_t I ) const;

	/**
	 * @brief      Checks whether a state is fully contained in caller-state.
	 * @details    This calls "contains" for all stored state sets iteratively and returns "false" first time it can be detected.
	 * @param[in]  rhs   The right hand side state.
	 * @return     True, if every subset of rhs is fully contained in the respective subset of the caller-state.
	 */
	bool contains( const State<Number, Representation, Rargs...>& rhs ) const;

	std::vector<Point<Number>> vertices( std::size_t I = 0 ) const;

	State<Number, Representation, Rargs...> projectOn( const std::vector<std::size_t>& dimensions, std::size_t I = 0 ) const;
	State<Number, Representation, Rargs...> projectOn( const std::pair<std::size_t, std::size_t>& dimensions, std::size_t I = 0 ) const;

	State<Number, Representation, Rargs...> assignIntervals( const std::map<std::size_t, carl::Interval<Number>>&, std::size_t I = 0 ) const;

	std::size_t getDimension( std::size_t I = 0 ) const;
	std::size_t getDimensionOffset( std::size_t I ) const;

	Number getSupremum( std::size_t I ) const;

	void removeRedundancy();

	void partiallyRemoveRedundancy( std::size_t I );

	void reduceRepresentation();

	void partiallyReduceRepresentation( std::size_t I );

	/**
	 * decomposes state set by projection
	 */
	void decompose( const Decomposition& decomposition );

	/**
	 * @brief      Outstream operator.
	 * @param      out    The outstream.
	 * @param[in]  state  The state.
	 * @return     A reference to the outstream.
	 */

	friend std::ostream& operator<<( std::ostream& out, const State<Number, Representation, Rargs...>& state ) {
		if ( state.getLocation() != nullptr ) {
			out << "location @" << state.getLocation();
		} else {
			out << "location: NULL";
		}
		// out << " at timestamp " << carl::convert<tNumber, double>( state.getTimestamp() ) << std::endl;

		// out << "Set: " << convert<Number,double>(Converter<Number>::toBox(state.getSet())) << std::endl;
		// out << "Set: " << std::visit(genericConversionVisitor<repVariant,Number>(representation_name::box), state.getSet()) << std::endl;
		if ( state.getNumberSets() > 0 ) {
			out << "Set: " << std::visit( genericToStringVisitor(), state.getSet( 0 ) ) << std::endl;
		}
		if ( state.getNumberSets() > 1 ) {
			out << "Other sets: " << std::endl;
			for ( std::size_t i = 1; i < state.getNumberSets(); ++i )
				out << std::visit( genericToStringVisitor(), state.getSet( i ) ) << std::endl;
		}
		return out;
	}

	/**
	 * @brief      Comparison for equality operator.
	 * @details    Note that this operator is very expensive in case both states are equal.
	 * @param[in]  lhs   The left hand side.
	 * @param[in]  rhs   The right hand side.
	 * @return     True, if both states are equal, false otherwise.
	 */
	friend bool operator==( const State<Number, Representation, Rargs...>& lhs, const State<Number, Representation, Rargs...>& rhs ) {
		// quick checks first
		if ( lhs.getNumberSets() != rhs.getNumberSets() || lhs.mTimestamp != rhs.mTimestamp ) {
			return false;
		}

		// light-weight check on mIsEmpty
		for ( const auto b1 : lhs.getEmptyStates() ) {
			for ( const auto b2 : rhs.getEmptyStates() ) {
				if ( ( b1 == TRIBOOL::TRUE && b2 == TRIBOOL::FALSE ) || ( b2 == TRIBOOL::TRUE && b1 == TRIBOOL::FALSE ) ) {
					return false;
				}
			}
		}

		// location-based checks
		if ( lhs.mLoc != nullptr ) {
			if ( rhs.mLoc != nullptr ) {
				if ( *( lhs.mLoc ) != *( rhs.mLoc ) ) {
					return false;
				}
			} else {
				return false;
			}
		} else {
			if ( rhs.mLoc != nullptr ) {
				return false;
			}
		}

		// set-based checks
		for ( std::size_t i = 0; i < lhs.getNumberSets(); ++i ) {
			if ( lhs.getSetType( i ) != rhs.getSetType( i ) ) {
				return false;
			}
			if ( !std::visit( genericCompareVisitor(), lhs.getSet( i ), rhs.getSet( i ) ) ) {
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief      Operator for unequal.
	 * @param[in]  lhs   The left hand side.
	 * @param[in]  rhs   The right hand side.
	 * @return     True, if both states are not equal, false otherwise.
	 */
	friend bool operator!=( const State<Number, Representation, Rargs...>& lhs, const State<Number, Representation, Rargs...>& rhs ) {
		return !( lhs == rhs );
	}
};

/*
template<typename Number, typename State>
State parallelCompose(
	const State& lhsInitState, const State& rhsInitState,
	const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar, const std::vector<std::string> haVar,
	const HybridAutomaton<Number, State> ha) {

	State haInitState;

	// set location
	std::string name = lhsInitState.getLocation()->getName()+"_"+rhsInitState.getLocation()->getName();
	auto location = ha.getLocation(name);
	assert(location != NULL);
	haInitState.setLocation(location);

	// set constraint
	// TODO: Move this.
	ConstraintSet<Number> lhsConstraintSet = std::get<ConstraintSet<Number>>(lhsInitState.getSet(0));
	ConstraintSet<Number> rhsConstraintSet = std::get<ConstraintSet<Number>>(rhsInitState.getSet(0));
	matrix_t<Number> lhsMatrix = lhsConstraintSet.matrix();
	matrix_t<Number> rhsMatrix = rhsConstraintSet.matrix();
	vector_t<Number> lhsVector = lhsConstraintSet.vector();
	vector_t<Number> rhsVector = rhsConstraintSet.vector();
	matrix_t<Number> newMatrix = combine(lhsMatrix, rhsMatrix, haVar, lhsVar, rhsVar);
	matrix_t<Number> newVector = combine(lhsVector, rhsVector);
	ConstraintSet<Number> haConstraintSet = ConstraintSet<Number>(newMatrix, newVector);

	//ConstraintSet<Number> haConstraintSet = combine(lhsConstraintSet, rhsConstraintSet, lhsVar, rhsVar, haVar);
	haInitState.setSet(haConstraintSet ,0);

	// set timestamp
	haInitState.setTimestamp(carl::Interval<Number>(0));

	// return state
	return haInitState;
}
*/

#ifdef HYPRO_USE_PPL
template <typename Number>
using State_t = State<Number, Box<Number>, CarlPolytope<Number>, ConstraintSet<Number>, SupportFunction<Number>, Zonotope<Number>, HPolytope<Number>, VPolytope<Number>, DifferenceBounds<Number>, SupportFunctionNew<Number>, TemplatePolyhedron<Number>, Polytope<Number>>;
#else
template <typename Number>
using State_t = State<Number, Box<Number>, CarlPolytope<Number>, ConstraintSet<Number>, SupportFunction<Number>, Zonotope<Number>, HPolytope<Number>, VPolytope<Number>, DifferenceBounds<Number>, SupportFunctionNew<Number>, TemplatePolyhedron<Number>>;
#endif

}  // namespace hypro

#include "State.tpp"
#include "StateUtil.h"
