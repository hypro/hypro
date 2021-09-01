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