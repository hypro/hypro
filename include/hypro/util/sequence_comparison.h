#pragma once
#include "convenienceOperators.h"
#include "logging/Logger.h"

#include <algorithm>

namespace hypro {

/**
 * @brief Compares two vectors of pointerst by checking whether the pointed-to contents agree.
 * @tparam T Content-type
 * @param lhs Left-hand-side sequence
 * @param rhs Right-hand-side sequence
 * @return true If all elements from the lhs are found in the rhs
 * @return false Otherwise
 */
template <typename T>
bool contains( const std::vector<T*>& lhs, const std::vector<T*>& rhs ) {
	TRACE( "hypro.util", "Compare sequences " << lhs << " and " << rhs );
	if ( lhs.size() != rhs.size() ) {
		return false;
	}
	for ( auto lhsIt = lhs.begin(); lhsIt != lhs.end(); ++lhsIt ) {
		auto found = std::find_if( rhs.begin(), rhs.end(), [&lhsIt]( const auto* rhs ) { return **lhsIt == *rhs; } );
		if ( found == rhs.end() ) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Compares two sequences of pointers.
 * @tparam T The type which is pointed to
 * @param lhs Left-hand-side sequence
 * @param rhs Right-hand-side sequence
 * @return true If both sequences contain each other, i.e., all pointed to elements are equal.
 * @return false Otherwise
 */
template <typename T>
bool is_equal( const std::vector<T*>& lhs, const std::vector<T*>& rhs ) {
	TRACE( "hypro.datastructures", "Call to function" );
	return contains( lhs, rhs ) && contains( rhs, lhs );
}

}  // namespace hypro
