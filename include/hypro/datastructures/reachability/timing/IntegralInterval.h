#pragma once

#include <algorithm>
#include <iosfwd>

namespace hypro {

/**
 * Integer valued interval containing both its bounds.
 */
struct Interval {
	int lower;
	int upper;

	int width() const {
		return upper - lower + 1;
	}

	bool operator==( Interval const& other ) const {
		return lower == other.lower && upper == other.upper;
	}

	void intersect( Interval const& other ) {
		*this = intersect( *this, other );
	}

	void convexHull( Interval const& other ) {
		lower = std::min( lower, other.lower );
		upper = std::max( upper, other.upper );
	}

	static Interval intersect( Interval const& left, Interval const& right ) {
		return { std::max( left.lower, right.lower ), std::min( left.upper, right.upper ) };
	}

	friend std::ostream& operator<<( std::ostream& out, Interval const& interval ) {
		out << "[ " << interval.lower << ", " << interval.upper << " ]";
		return out;
	}
};

}  // namespace hypro