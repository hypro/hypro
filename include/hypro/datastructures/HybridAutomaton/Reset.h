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
	Reset() = default;
	Reset( const Reset& orig )
		: mAffineResets( orig.getAffineResets() )
		, mIntervalResets( orig.getIntervalResets() ) {}

	Reset( Reset&& orig ) = default;
	Reset& operator=( const Reset<Number>& orig ) = default;
	Reset& operator=( Reset<Number>&& orig ) = default;
	Reset( const matrix_t<Number>& mat, const vector_t<Number>& vec );
	Reset( const std::vector<carl::Interval<Number>>& intervals );
	~Reset() {}

	bool empty() const { return mAffineResets.empty(); }
	std::size_t size() const { return mAffineResets.size(); }

	const vector_t<Number>& getVector( std::size_t I = 0 ) const;
	const matrix_t<Number>& getMatrix( std::size_t I = 0 ) const;
	matrix_t<Number>& rGetMatrix( std::size_t I = 0 );
	vector_t<Number>& rGetVector( std::size_t I = 0 );
	const std::vector<carl::Interval<Number>>& getIntervals( std::size_t I = 0 ) const;
	std::vector<carl::Interval<Number>>& rGetIntervals( std::size_t I = 0 );

	const AffineTransformation<Number>& getAffineReset( std::size_t I = 0 ) const { return mAffineResets[I]; }
	const std::vector<AffineTransformation<Number>>& getAffineResets() const { return mAffineResets; }
	const IntervalAssignment<Number>& getIntervalReset( std::size_t I = 0 ) const { return mIntervalResets[I]; }
	const std::vector<IntervalAssignment<Number>>& getIntervalResets() const { return mIntervalResets; }

	void setVector( const vector_t<Number>& in, std::size_t I = 0 );
	void setMatrix( const matrix_t<Number>& in, std::size_t I = 0 );
	void setIntervals( const std::vector<carl::Interval<Number>>& intervals, std::size_t I = 0 );

	bool isAffineIdentity() const;
	bool isIntervalIdentity() const;
	bool isIdentity() const;

	std::size_t hash() const;
	/**
	 * decomposes reset
	 */
	void decompose( const Decomposition& decomposition );

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
			if ( lhs.getAffineReset( i ) != rhs.getAffineReset( i ) ) {
				return false;
			}
			if ( lhs.getIntervals( i ) != rhs.getIntervals( i ) ) {
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
