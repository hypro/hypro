/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../types.h"
#include "../../util/adaptions_eigen/adaptions_eigen.h"

#include <bits/c++config.h>
#include <carl/interval/Interval.h>
#include <vector>

namespace hypro {

enum class ResetType { affine = 0,
					   interval,
					   none };

template <typename Number>
struct AffineTransformation {
	ConstraintSetT<Number> mTransformation;

	AffineTransformation() = default;
	AffineTransformation( const AffineTransformation<Number>& orig ) = default;
	AffineTransformation( AffineTransformation<Number>&& orig ) = default;
	AffineTransformation<Number>& operator=( const AffineTransformation<Number>& rhs ) = default;
	AffineTransformation<Number>& operator=( AffineTransformation<Number>&& rhs ) = default;
	~AffineTransformation() {}

	AffineTransformation( const ConstraintSetT<Number>& r )
		: mTransformation( r ) {}
	AffineTransformation( const matrix_t<Number>& linearTransformation, const vector_t<Number>& translation )
		: mTransformation( ConstraintSetT<Number>( linearTransformation, translation ) ) {}

	static ResetType type() { return ResetType::affine; }

	std::size_t size() const { return mTransformation.size(); }

	bool isIdentity() const {
		if ( mTransformation.matrix() != matrix_t<Number>::Identity( mTransformation.matrix().rows(), mTransformation.matrix().rows() ) || mTransformation.vector() != vector_t<Number>::Zero( mTransformation.vector().rows() ) ) {
			return false;
		}
		return true;
	}

	bool isIdentity( Eigen::Index I ) const {
		for ( Eigen::Index j = 0; j < mTransformation.matrix().cols(); ++j ) {
			if ( ( j != I && mTransformation.matrix()( I, j ) != Number( 0 ) ) || ( ( j == I && mTransformation.matrix()( I, j ) != Number( 1 ) ) ) ) {
				return false;
			}
		}
		if ( mTransformation.vector()( I ) != Number( 0 ) ) {
			return false;
		}
		return true;
	}

	bool isConstant() const {
		if ( mTransformation.matrix() == matrix_t<Number>::Zero( mTransformation.matrix().rows(), mTransformation.matrix().rows() ) ) {
			return true;
		}
		return false;
	}

	bool isSingular() const {
		for ( Eigen::Index rowIndex = 0; rowIndex < mTransformation.matrix().rows(); ++rowIndex ) {
			matrix_t<Number> expected0 = matrix_t<Number>::Zero( 1, mTransformation.matrix().rows() );
			matrix_t<Number> expected1 = matrix_t<Number>::Zero( 1, mTransformation.matrix().rows() );
			expected1( 0, rowIndex ) = Number( 1.0 );
			if ( mTransformation.matrix().row( rowIndex ) != expected0 && mTransformation.matrix().row( rowIndex ) != expected1 ) {
				return false;
			}
		}
		return true;
	}

	friend std::ostream& operator<<( std::ostream& out, const AffineTransformation<Number>& in ) {
		if ( in.isIdentity() ) {
			out << "Identity";
			return out;
		}
		bool firstrow = true;
		for ( Eigen::Index row = 0; row < in.mTransformation.matrix().rows(); ++row ) {
			// skip identity resets
			if ( in.isIdentity( std::size_t( row ) ) ) {
				continue;
			}
			if ( !firstrow ) {
				out << "\n";
			} else {
				firstrow = false;
			}
			out << "x" << row << " := ";
			bool allZero = false;
			if ( in.mTransformation.matrix().row( row ) == matrix_t<Number>::Zero( 1, in.mTransformation.matrix().cols() ) ) {
				allZero = true;
				if ( in.mTransformation.vector()( row ) == 0 ) {
					out << "0";
				}
			} else {
				out << to_string<Number>( in.mTransformation.matrix().row( row ) );
			}
			if ( in.mTransformation.vector()( row ) != 0 ) {
				if ( allZero || in.mTransformation.vector()( row ) < 0 ) {
					out << in.mTransformation.vector()( row );
				} else {
					out << " + " << in.mTransformation.vector()( row );
				}
			}
		}
		return out;
	}

	friend bool operator==( const AffineTransformation<Number>& lhs, const AffineTransformation<Number>& rhs ) {
		return lhs.mTransformation == rhs.mTransformation;
	}

	friend AffineTransformation<Number> operator+( const AffineTransformation<Number>& lhs, const AffineTransformation<Number>& rhs ) {
		if ( rhs.isIdentity() ) {
			return lhs;
		}
		if ( lhs.isIdentity() ) {
			return rhs;
		}
		return AffineTransformation<Number>{ matrix_t<Number>( lhs.mTransformation.matrix() * ( rhs.mTransformation.matrix() ) ), lhs.mTransformation.vector() + lhs.mTransformation.matrix() * rhs.mTransformation.vector() };
	}
};

template <typename Number>
struct IntervalAssignment {
	std::vector<carl::Interval<Number>> mIntervals;

	IntervalAssignment() = default;
	IntervalAssignment( const IntervalAssignment<Number>& orig ) = default;
	IntervalAssignment( const std::vector<carl::Interval<Number>>& i )
		: mIntervals( i ) {}
	IntervalAssignment& operator=( const IntervalAssignment<Number>& rhs ) = default;
	IntervalAssignment& operator=( IntervalAssignment<Number>&& rhs ) = default;
	~IntervalAssignment() {}

	const std::vector<carl::Interval<Number>>& getIntervals() const { return mIntervals; }
	void setIntervals( const std::vector<carl::Interval<Number>>& intervals ) { mIntervals = intervals; }
	void setInterval( const carl::Interval<Number>& interval, std::size_t i ) {
		assert( i < size() );
		mIntervals[i] = interval;
	}

	static ResetType type() { return ResetType::interval; }

	std::size_t size() const { return mIntervals.size(); }

	bool isIdentity() const {
		return std::all_of( mIntervals.begin(), mIntervals.end(), []( const auto& i ) { return i.isEmpty(); } );
	}

	friend std::ostream& operator<<( std::ostream& out, const IntervalAssignment<Number>& in ) {
		bool first = true;
		std::size_t pos = 0;
		for ( const auto& i : in.mIntervals ) {
			if ( !first ) {
				out << "\n";
			} else {
				first = false;
			}
			if ( i.isEmpty() ) {
				out << "x" << pos << " := x" << pos;
				++pos;
			} else {
				out << "x" << pos << " := " << i;
			}
		}
		return out;
	}

	friend bool operator==( const IntervalAssignment<Number>& lhs, const IntervalAssignment<Number>& rhs ) {
		if ( lhs.mIntervals.size() != rhs.mIntervals.size() ) return false;

		for ( std::size_t i = 0; i < lhs.mIntervals.size(); ++i ) {
			if ( lhs.mIntervals[i] != rhs.mIntervals[i] ) return false;
		}
		return true;
	}
};

struct NoneAssignment {
	std::size_t mDimensions = 1;

	static ResetType type() { return ResetType::none; }

	std::size_t size() const { return mDimensions; }

	bool isIdentity() const {
		return false;
	}

	friend std::ostream& operator<<( std::ostream& out, const NoneAssignment& in ) {
		out << "NONE " << in.mDimensions;
		return out;
	}

	friend bool operator==( const NoneAssignment& lhs, const NoneAssignment& rhs ) {
		return lhs.size() == rhs.size();
	}
};

namespace detail {

template <typename T>
auto getType( const T& ) {
	return T::type();
}

}  // namespace detail

}  // namespace hypro

namespace std {
template <typename Number>
struct hash<hypro::AffineTransformation<Number>> {
	std::size_t operator()( const hypro::AffineTransformation<Number>& reset ) const {
		std::size_t seed = 0;
		carl::hash_add( seed, reset.mTransformation.matrix() );
		carl::hash_add( seed, reset.mTransformation.vector() );
		return seed;
	}
};

template <typename Number>
struct hash<hypro::IntervalAssignment<Number>> {
	std::size_t operator()( const hypro::IntervalAssignment<Number>& reset ) const {
		std::size_t seed = 0;
		carl::hash_add( seed, reset.mIntervals );
		return seed;
	}
};

template <>
struct hash<hypro::NoneAssignment> {
	std::size_t operator()( const hypro::NoneAssignment& reset ) const {
		std::size_t seed = 0;
		carl::hash_add( seed, reset.mDimensions );
		return seed;
	}
};
}  // namespace std
