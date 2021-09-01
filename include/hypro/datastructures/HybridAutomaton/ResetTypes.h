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

	std::size_t size() { return mTransformation.size(); }

	bool isIdentity() const {
		if ( mTransformation.matrix() != matrix_t<Number>::Identity( mTransformation.matrix().rows(), mTransformation.matrix().rows() ) || mTransformation.vector() != vector_t<Number>::Zero( mTransformation.vector().rows() ) ) {
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
		bool firstrow = true;
		for ( Eigen::Index row = 0; row < in.mTransformation.matrix().rows(); ++row ) {
			if ( !firstrow ) {
				out << "\n";
			} else {
				firstrow = false;
			}
			out << "x" << row << " := " << to_string<Number>( in.mTransformation.matrix().row( row ) );
		}
		return out;
	}

	friend bool operator==( const AffineTransformation<Number>& lhs, const AffineTransformation<Number>& rhs ) {
		return lhs.mTransformation == rhs.mTransformation;
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
