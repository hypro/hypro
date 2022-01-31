/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "Generators.h"
#include "Result.h"

namespace hypro {

template <typename Representation, typename Number, int operation>
struct Executor {
	void run( typename Generator<Representation, Number, operation>::type _in ) {}
};

template <typename Representation, typename Number>
struct Executor<Representation, Number, operation::LINEARTRAFO> {
	Result run( typename Generator<Representation, Number, operation::LINEARTRAFO>::type _in ) {
		std::get<0>( _in ).affineTransformation( std::get<1>( _in ), std::get<2>( _in ) );
		return Result();
	}
};

template <typename Representation, typename Number>
struct Executor<Representation, Number, operation::MINKOWSKISUM> {
	Result run( typename Generator<Representation, Number, operation::MINKOWSKISUM>::type _in ) {
		std::get<0>( _in ).minkowskiSum( std::get<1>( _in ) );
		return Result();
	}
};

template <typename Representation, typename Number>
struct Executor<Representation, Number, operation::INTERSECTION> {
	Result run( typename Generator<Representation, Number, operation::INTERSECTION>::type _in ) {
		std::get<0>( _in ).intersect( std::get<1>( _in ) );
		return Result();
	}
};

template <typename Representation, typename Number>
struct Executor<Representation, Number, operation::CONTAINS> {
	Result run( typename Generator<Representation, Number, operation::CONTAINS>::type _in ) {
		std::get<0>( _in ).contains( std::get<1>( _in ) );
		return Result();
	}
};

template <typename Representation, typename Number>
struct Executor<Representation, Number, operation::UNION> {
	Result run( typename Generator<Representation, Number, operation::UNION>::type _in ) {
		std::get<0>( _in ).unite( std::get<1>( _in ) );
		return Result();
	}
};

template <typename Representation, typename Number>
struct Executor<Representation, Number, operation::INTERSECTHALFSPACE> {
	Result run( typename Generator<Representation, Number, operation::INTERSECTHALFSPACE>::type _in ) {
		std::get<0>( _in ).intersectHalfspace( std::get<1>( _in ) );
		return Result();
	}
};

}  // namespace hypro