/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 30.08.22.
 */

#ifndef HYPRO_BOUNDEDNESS_H
#define HYPRO_BOUNDEDNESS_H

#include "GeometricObjectBase.h"

#include <hypro/util/exceptions.h>

namespace hypro {

template <template <class, class, class> typename Set, typename Number, typename Converter, typename Setting>
bool isBounded( const Set<Number, Converter, Setting>& in ) {
	throw NotImplemented();
}

// overrides for specific implementations

/**
 * @brief Overload for checking boundedness for boxes.
 * @tparam Number The number type
 * @tparam Converter The converter
 * @tparam Setting The used settings
 * @param in The input box
 * @return True, if the box is unbounded in at least one dimension, false otherwise.
 */
template <typename Number, typename Converter, typename Setting>
bool isBounded( const BoxT<Number, Converter, Setting>& in ) {
	if ( in.empty() ) {
		return true;
	}
	return std::none_of( std::begin( in.intervals() ), std::end( in.intervals() ), []( const auto& intv ) { return isUnbounded( intv ); } );
}

/**
 * @brief Overload for checking boundedness for h-polytopes.
 * @details Checks, if the bounding box of the polytope is bounded.
 * @tparam Number The number type
 * @tparam Converter The converter
 * @tparam Setting The used settings
 * @param in The input polytope in h-representation
 * @return True, if the polytope is unbounded in at least one dimension, false otherwise.
 */
template <typename Number, typename Converter, typename Setting>
bool isBounded( const HPolytopeT<Number, Converter, Setting>& in ) {
	auto box = Converter::toBox( in );
	return isBounded( box );
}

}  // namespace hypro

#endif	// HYPRO_BOUNDEDNESS_H
