/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../representations/ConstraintSet/ConstraintSet.h"
#include "../../types.h"
#include "ResetTypes.h"
#include "decomposition/Decomposition.h"

#include <functional>

namespace hypro {

namespace detail {

template <typename ReturnType, typename Function>
struct ResetVisitor {
	Function function;

	ResetVisitor() = delete;
	ResetVisitor( const Function& c )
		: function( c ) {}

	template <typename In>
	ReturnType operator()( In&& reset ) {
		return function( std::forward<In>( reset ) );
	}
};

template <class Result, class Func>
ResetVisitor<Result, std::decay_t<Func>> make_reset_visitor( Func&& func ) {
	return { std::forward<Func>( func ) };
}

}  // namespace detail

template <typename Number>
class Reset {
  protected:
	std::vector<AffineTransformation<Number>> mAffineResets;
	std::vector<IntervalAssignment<Number>> mIntervalResets;
	mutable std::size_t mHash = 0;
	bool mDecomposed = false;

  public:
	Reset(){};
	Reset( const Reset& orig )
		: mAffineResets( orig.getAffineResets() )
		, mIntervalResets( orig.getIntervalResets() ) {}

	Reset( Reset&& orig ) = default;
	Reset& operator=( const Reset<Number>& orig ) = default;
	Reset& operator=( Reset<Number>&& orig ) = default;
	Reset( const matrix_t<Number>& mat, const vector_t<Number>& vec );
	Reset( const std::vector<carl::Interval<Number>>& intervals );
	~Reset() {}

	// bool empty() const { return mAffineResets.empty(); }
	bool empty() const { return mAffineResets.empty() && mIntervalResets.empty(); }
	std::size_t size() const { return mAffineResets.size(); }

	const vector_t<Number>& getVector( std::size_t I = 0 ) const;
	const matrix_t<Number>& getMatrix( std::size_t I = 0 ) const;
	matrix_t<Number>& rGetMatrix( std::size_t I = 0 );
	vector_t<Number>& rGetVector( std::size_t I = 0 );
	const std::vector<carl::Interval<Number>>& getIntervals( std::size_t I = 0 ) const;
	std::vector<carl::Interval<Number>>& rGetIntervals( std::size_t I = 0 );

	const AffineTransformation<Number>& getAffineReset( std::size_t I = 0 ) const {
		assert( I < mAffineResets.size() );
		return mAffineResets[I];
	}
	const std::vector<AffineTransformation<Number>>& getAffineResets() const { return mAffineResets; }
	const IntervalAssignment<Number>& getIntervalReset( std::size_t I = 0 ) const {
		assert( I < mIntervalResets.size() );
		return mIntervalResets[I];
	}
	const std::vector<IntervalAssignment<Number>>& getIntervalResets() const { return mIntervalResets; }

	void setVector( const vector_t<Number>& in, std::size_t I = 0 );
	void setMatrix( const matrix_t<Number>& in, std::size_t I = 0 );
	void setIntervals( const std::vector<carl::Interval<Number>>& intervals, std::size_t I = 0 );

	bool isAffineIdentity() const;
	bool isIntervalIdentity() const;
	bool isIdentity() const;
	bool isIdentity( std::size_t I ) const;

	std::size_t hash() const;
	/**
	 * decomposes reset
	 */
	void decompose( const std::vector<std::vector<std::size_t>>& partition );

	friend std::ostream& operator<<( std::ostream& ostr, const Reset<Number>& a ) {
		if ( a.isIdentity() ) {
			ostr << "Identity";
			return ostr;
		}
		for ( std::size_t i = 0; i < a.size(); ++i ) {
			ostr << a.getAffineReset( i );
			if ( a.getIntervals( i ).size() > 0 && !a.isIntervalIdentity() ) {
				ostr << "\n";
				for ( const auto& i : a.getIntervals( i ) ) {
					ostr << i << ", ";
				}
			}
		}
		return ostr;
	}

	friend bool operator==( const Reset<Number>& lhs, const Reset<Number>& rhs ) {
		if ( lhs.size() != rhs.size() ) {
			return false;
		}

		for ( std::size_t i = 0; i < lhs.size(); ++i ) {
			if ( !( lhs.getAffineReset( i ) == rhs.getAffineReset( i ) ) ) {
				return false;
			}
			if ( !( lhs.getIntervals( i ) == rhs.getIntervals( i ) ) ) {
				return false;
			}
		}
		return true;
	}

	friend bool operator!=( const Reset<Number>& lhs, const Reset<Number>& rhs ) {
		return !( lhs == rhs );
	}
};

template <typename Number>
Reset<Number> combine(
	  const Reset<Number>& lhs, const Reset<Number>& rhs,
	  const std::vector<std::string> haVar, const std::vector<std::string> lhsVar, const std::vector<std::string> rhsVar );

}  // namespace hypro

namespace std {

template <typename Number>
struct hash<hypro::Reset<Number>> {
	std::size_t operator()( const hypro::Reset<Number>& reset ) const {
		std::size_t seed = 0;
		for ( std::size_t i = 0; i < reset.size(); ++i ) {
			carl::hash_add( seed, reset.getAffineReset( i ) );
			carl::hash_add( seed, reset.getIntervalReset( i ) );
		}
		return seed;
	}
};

}  // namespace std

#include "Reset.tpp"
