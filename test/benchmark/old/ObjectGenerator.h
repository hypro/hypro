/*
 * Copyright (c) 2021.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *
 */

#pragma once

#include "../../hypro/datastructures/Halfspace.h"
#include "../../hypro/datastructures/Point.h"
#include "../../hypro/representations/types.h"
#include "../../hypro/types.h"
#include <random>

namespace hypro {
template <typename Representation, typename Number>
class ObjectGenerator {
  private:
	BenchmarkSetup<Number> mSetup;
	mutable std::mt19937 mRand;
	mutable std::uniform_real_distribution<double> mDistr;

  public:
	ObjectGenerator( BenchmarkSetup<Number> _setup )
		: mSetup( _setup ),
		  mRand( 4 )  // chosen by fair dice roll. Guaranteed to be random.
	{}

	Representation createSet() const {}

	Representation createSet( BenchmarkSetup<Number> _setup ) const {
		std::vector<Point<Number>> pointVector;
		std::uniform_real_distribution<double> distr( carl::toDouble( _setup.minValue ),
													  carl::toDouble( _setup.maxValue ) );
		for ( unsigned i = 0; i < _setup.vertices; ++i ) {
			vector_t<Number> coordinates( _setup.dimension );
			for ( unsigned j = 0; j < _setup.dimension; ++j ) {
				coordinates( j ) = Number( distr( mRand ) );
				// std::cout << "coordinates(" << j << ") = " << coordinates(j) << std::endl;
			}
			pointVector.push_back( Point<Number>( coordinates ) );
		}
		return Representation( pointVector );
	}

	vector_t<Number> createVector( BenchmarkSetup<Number> _setup ) const {
		std::uniform_real_distribution<double> distr( carl::toDouble( _setup.minValue ),
													  carl::toDouble( _setup.maxValue ) );
		vector_t<Number> coordinates( _setup.dimension );
		for ( unsigned j = 0; j < _setup.dimension; ++j ) {
			coordinates( j ) = Number( distr( mRand ) );
		}
		return coordinates;
	}

	Point<Number> createPoint( BenchmarkSetup<Number> _setup ) const { return Point<Number>( createVector( _setup ) ); }

	matrix_t<Number> createMatrix( BenchmarkSetup<Number> _setup ) const {
		std::uniform_real_distribution<double> distr( 0.0, 1.0 );  // Todo: Check if this is sufficient.
		matrix_t<Number> res( _setup.dimension, _setup.dimension );
		for ( unsigned i = 0; i < _setup.dimension; ++i ) {
			for ( unsigned j = 0; j < _setup.dimension; ++j ) {
				res( i, j ) = Number( distr( mRand ) );
			}
		}
		return res;
	}

	Halfspace<Number> createLimitedHalfspace( BenchmarkSetup<Number> _setup, Representation& rep ) const {
		if ( Representation::type() == hypro::representation_name::box ) {
			// Generate normal
			vector_t<Number> normal = ( createVector( _setup ) );
			// normal.normalize();
			// Generate point inside box
			vector_t<Number> p = vector_t<Number>::Zero( rep.dimension() );
			for ( unsigned i = 0; i < rep.dimension(); i++ ) {
				std::uniform_real_distribution<double> distr( carl::toDouble( rep.min().at( i ) ),
															  carl::toDouble( rep.max().at( i ) ) );
				p( i ) = Number( distr( mRand ) );
			}
			// Compute halfplane distance
			Number offset = normal.dot( p );
			// Generate halfspace
			return Halfspace<Number>( normal, offset );
		} else {
			assert( false && "creating limited halfspaces not implemented yet for other types" );
			return Halfspace<Number>();
		}
	}

  private:
};

template <typename Representation, typename Number>
struct BaseGenerator {
  protected:
	BenchmarkSetup<Number> mSetup;
	ObjectGenerator<Representation, Number> mGenerator;

  public:
	typedef void type;
	BaseGenerator( const BenchmarkSetup<Number>& _setup ) : mSetup( _setup ), mGenerator( _setup ) {}
	virtual void operator()() const = 0;
};
}  // namespace hypro
