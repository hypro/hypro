/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 25.07.22.
 */

#ifndef HYPRO_CONVENIENCESTLFUNCTIONS_H
#define HYPRO_CONVENIENCESTLFUNCTIONS_H

#include <algorithm>
#include <vector>

namespace hypro {

/**
 * Get the index of an element in a vector
 * @tparam T Type of elements
 * @param sequence The vector
 * @param elem The element to search for
 * @return The index of the element in the vector or -1 if the element is not contained
 */
template <typename T>
std::size_t getIndex( const std::vector<T>& sequence, T&& elem ) {
	auto it = std::find( std::begin( sequence ), std::end( sequence ), std::forward<T>( elem ) );
	if ( it == std::end( sequence ) ) {
		return -1;
	}
	return ( it - std::begin( sequence ) );
}

}  // namespace hypro

#endif	// HYPRO_CONVENIENCESTLFUNCTIONS_H
