/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../representations/ConstraintSet/ConstraintSet.h"
#include "../../representations/types.h"
#include "../../types.h"
#include "../../util/linearOptimization/Optimizer.h"
#include "decomposition/Decomposition.h"

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
	Condition( Condition&& orig ) noexcept = default;
	/// copy assignment
	Condition& operator=( const Condition& orig ) = default;
	/// move assignment
	Condition& operator=( Condition&& orig ) noexcept = default;
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
	/// checks if a point is contained in a subspace
	bool contains( const Point<Number>& point, std::size_t I = 0 ) const {
		auto opt = Optimizer<Number>( mConstraints[I].matrix(), mConstraints[I].vector() );
		return opt.checkPoint( point );
	}
	/// returns some point which satisfies the condition
	std::optional<hypro::Point<Number>> getInternalPoint( std::size_t I = 0 ) const {
		auto opt = Optimizer<Number>( mConstraints[I].matrix(), mConstraints[I].vector() );
		auto res = opt.getInternalPoint();
		return res.errorCode == SOLUTION::FEAS ? std::optional<hypro::Point<Number>>{ res.optimumValue } : std::nullopt;
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
	void decompose( const std::vector<std::vector<std::size_t>>& partition );
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

	/// Serialization function required by cereal
	template <typename Archive>
	void serialize( Archive& ar ) {
		ar( mConstraints, mConditionIsBox, mConditionSetState );
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
