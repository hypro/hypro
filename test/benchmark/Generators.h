#pragma once

#include "ObjectGenerator.h"

namespace hypro {

enum operation : int {
	LINEARTRAFO = 0,
	MINKOWSKISUM = 1,
	INTERSECTION = 2,
	CONTAINS = 3,
	UNION = 4,
	INTERSECTHALFSPACE = 5
};

template <typename Representation, typename Number, int operation>
struct Generator : public BaseGenerator<Representation, Number> {
	typedef void type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup ) {}
	void operator()() const override {}
};

template <typename Representation, typename Number>
struct Generator<Representation, Number, operation::LINEARTRAFO> : public BaseGenerator<Representation, Number> {
	typedef std::tuple<Representation, matrix_t<Number>, vector_t<Number>> type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup )
		: BaseGenerator<Representation, Number>( _setup ), name( "linear transformation" ) {}

	type operator()() const override {
		return std::make_tuple( this->mGenerator.createSet( this->mSetup ),
								this->mGenerator.createMatrix( this->mSetup ),
								this->mGenerator.createVector( this->mSetup ) );
	}
};

template <typename Representation, typename Number>
struct Generator<Representation, Number, operation::MINKOWSKISUM> : public BaseGenerator<Representation, Number> {
	typedef std::tuple<Representation, Representation> type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup )
		: BaseGenerator<Representation, Number>( _setup ), name( "Minkowski sum" ) {}

	type operator()() const override {
		return std::make_tuple( this->mGenerator.createSet( this->mSetup ),
								this->mGenerator.createSet( this->mSetup ) );
	}
};

template <typename Representation, typename Number>
struct Generator<Representation, Number, operation::INTERSECTION> : public BaseGenerator<Representation, Number> {
	typedef std::tuple<Representation, Representation> type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup )
		: BaseGenerator<Representation, Number>( _setup ), name( "intersect" ) {}

	type operator()() const override {
		return std::make_tuple( this->mGenerator.createSet( this->mSetup ),
								this->mGenerator.createSet( this->mSetup ) );
	}
};

template <typename Representation, typename Number>
struct Generator<Representation, Number, operation::CONTAINS> : public BaseGenerator<Representation, Number> {
	typedef std::tuple<Representation, Point<Number>> type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup )
		: BaseGenerator<Representation, Number>( _setup ), name( "contains" ) {}

	type operator()() const override {
		return std::make_tuple( this->mGenerator.createSet( this->mSetup ),
								this->mGenerator.createPoint( this->mSetup ) );
	}
};

template <typename Representation, typename Number>
struct Generator<Representation, Number, operation::UNION> : public BaseGenerator<Representation, Number> {
	typedef std::tuple<Representation, Representation> type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup )
		: BaseGenerator<Representation, Number>( _setup ), name( "unite" ) {}

	type operator()() const override {
		return std::make_tuple( this->mGenerator.createSet( this->mSetup ),
								this->mGenerator.createSet( this->mSetup ) );
	}
};

template <typename Representation, typename Number>
struct Generator<Representation, Number, operation::INTERSECTHALFSPACE> : public BaseGenerator<Representation, Number> {
	typedef std::pair<Representation, Halfspace<Number>> type;
	std::string name;

	explicit Generator( const BenchmarkSetup<Number>& _setup )
		: BaseGenerator<Representation, Number>( _setup ), name( "intersectHalfspace" ) {}

	type operator()() const override {
		Representation rep = this->mGenerator.createSet( this->mSetup );
		return std::make_pair( rep, this->mGenerator.createLimitedHalfspace( this->mSetup, rep ) );
	}
};

}  // namespace hypro
