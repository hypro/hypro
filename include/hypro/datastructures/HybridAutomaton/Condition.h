#pragma once
#include "../../representations/ConstraintSet/ConstraintSet.h"
#include "../../representations/types.h"
#include "../../types.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "decomposition/Decomposition.h"

#include <carl/interval/Interval.h>
#include <iosfwd>
#include <numeric>
#include <variant>

namespace hypro {

/**
 * @brief Class representing a collection of conditions (in possibly several subspaces)
 * @tparam Number
 */
template <typename Number>
class Condition {
  private:
	std::vector<ConstraintSetT<Number>> mConstraints;  ///< holds the constraints specifying the condition
	mutable std::vector<TRIBOOL> mConditionIsBox;	   ///< cache to check whether constraints are axis-aligned
	mutable std::vector<SETSTATE> mConditionSetState;  ///< cache to hold whether the set defined is empty or universal
	mutable std::size_t mHash = 0;					   ///< cache for the hash value
  public:
	/// default constructor
	Condition() = default;
	/// constructor from matrix and vector. Creates constraints describing Ax = b.
	Condition( const matrix_t<Number>& mat, const vector_t<Number>& vec )
		: mConstraints()
		, mConditionIsBox( { TRIBOOL::NSET } )
		, mConditionSetState( { SETSTATE::UNKNOWN } )
		, mHash( 0 ) {
		assert( mat.rows() == vec.rows() );
		mConstraints.emplace_back( mat, vec );
	}
	/// constructor from constraint set (which encapsulates a matrix and a vector)
	explicit Condition( const ConstraintSetT<Number>& constraints )
		: mConstraints( { constraints } )
		, mConditionIsBox( { TRIBOOL::NSET } )
		, mConditionSetState( { SETSTATE::UNKNOWN } )
		, mHash( 0 ) {}
	/// constructor from a set of constraint sets.
	explicit Condition( const std::vector<std::variant<ConstraintSetT<Number>>>& sets );
	/// constructor from a vector of intervals
	explicit Condition( const std::vector<carl::Interval<Number>>& intervals );
	/// copy constructor
	Condition( const Condition& orig ) = default;
	/// move constructor
	Condition( Condition&& orig ) = default;
	/// copy assignment
	Condition& operator=( const Condition& orig ) = default;
	/// move assignment
	Condition& operator=( Condition&& orig ) = default;
	/// destructor
	~Condition() = default;
	/// static construction methods
	static Condition True() {
		return Condition();
	}

	/// returns number of subspaces
	std::size_t size() const { return mConstraints.size(); }
	/// checks for emptiness
	bool empty() const { return mConstraints.empty(); }
	/// checks, whether the condition is unbounded
	bool isTrue() const {
		assert( cacheIsSane() );
		updateSetState();
		return this->empty() || std::all_of( mConditionSetState.begin(), mConditionSetState.end(), []( const auto s ) { return s == SETSTATE::UNIVERSAL; } );
	}
	/// checks, whether the condition is unsatisfiable by its own
	bool isFalse() const {
		assert( cacheIsSane() );
		updateSetState();
		return std::any_of( mConditionSetState.begin(), mConditionSetState.end(), []( const auto s ) { return s == SETSTATE::EMPTY; } );
	}
	/// returns state space dimension
	std::size_t dimension() const {
		return std::accumulate( mConstraints.begin(), mConstraints.end(), 0, []( std::size_t cur, const auto& cSet ) { return cur + cSet.dimension(); } );
	}
	/// returns matrix representing constraints for a subspace (default 0)
	const matrix_t<Number>& getMatrix( std::size_t I = 0 ) const {
		assert( mConstraints.size() > I );
		return mConstraints.at( I ).matrix();
	}
	/// returns vector representing constants for a subspace (default 0)
	const vector_t<Number>& getVector( std::size_t I = 0 ) const {
		assert( mConstraints.size() > I );
		return mConstraints.at( I ).vector();
	}
	/// add further constraints
	void addConstraints( const Condition<Number>& other );
	/// true, if all constraints in all subspaces are axis-aligned (box-shaped)
	bool isAxisAligned() const;
	/// true, if all constraints in a particular subspaces are axis-aligned (box-shaped)
	bool isAxisAligned( std::size_t i ) const;
	/// setter for constraint matrix in a subspace (default 0)
	void setMatrix( const matrix_t<Number>& m, std::size_t I = 0 );
	/// setter for constant vector in a subspace (default 0)
	void setVector( const vector_t<Number>& v, std::size_t I = 0 );
	/// getter for constraint sets for all subspaces
	const std::vector<ConstraintSetT<Number>>& constraints() const { return mConstraints; }
	/// computes hash
	std::size_t hash() const;
	/// computes string with dot-representation
	std::string getDotRepresentation( const std::vector<std::string>& vars ) const;
	/// decomposes constraints according to passed decomposition
	void decompose( const Decomposition& decomposition );
	/// compare equal
	friend bool operator==( const Condition& lhs, const Condition& rhs ) {
		if ( lhs.hash() != rhs.hash() || lhs.size() != rhs.size() ) {
			TRACE( "hypro.datastructures", "Hash or size are not equal, hashes: " << lhs.hash() << ", " << rhs.hash() << "; sizes: " << lhs.size() << ", " << rhs.size() );
			return false;
		}

		for ( std::size_t i = 0; i < lhs.size(); ++i ) {
			if ( ( lhs.getVector( i ) != rhs.getVector( i ) ) || ( lhs.getMatrix( i ) != rhs.getMatrix( i ) ) ) {
				TRACE( "hypro.datastructures", "Matrix or vector are not equal." );
				return false;
			}
		}
		return true;
	}
	/// compare not equal
	friend bool operator!=( const Condition& lhs, const Condition& rhs ) {
		return !( lhs == rhs );
	}
	/// outstream operator
	friend std::ostream& operator<<( std::ostream& out, const Condition& in ) {
		if ( in.constraints().size() == 1 ) {
			out << in.constraints().front();
		} else {
			std::size_t i = 0;
			for ( const auto& pair : in.constraints() ) {
				out << "ConstraintSet " << i << ": \n"
					<< pair;
				++i;
			}
		}
		return out;
	}

  private:
	void checkAxisAligned( std::size_t i ) const;
	void updateSetState() const;
#ifndef NDEBUG
	bool cacheIsSane() const;
#endif
};

template <typename Number>
Condition<Number> combine(
	  const Condition<Number>& lhs, const Condition<Number>& rhs,
	  const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar );

template <typename Number>
Condition<Number> conditionFromIntervals( const std::vector<carl::Interval<Number>>& intervals );

}  // namespace hypro

namespace std {

template <typename Number>
struct hash<hypro::Condition<Number>> {
	std::size_t operator()( const hypro::Condition<Number>& cond ) const {
		std::size_t seed = 0;
		for ( auto conSet : cond.constraints() ) {
			carl::hash_add( seed, std::hash<hypro::matrix_t<Number>>()( conSet.matrix() ) );
			carl::hash_add( seed, std::hash<hypro::vector_t<Number>>()( conSet.vector() ) );
		}
		return seed;
	}
};

}  // namespace std

#include "Condition.tpp"
