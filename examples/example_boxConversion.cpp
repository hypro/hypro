/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * \example example_boxConversion.cpp This example shows different approaches on how to convert a polytope in
 * H-representation to a box in HyPro.
 *
 * File:   example_boxConversion.cpp
 * Author: Simon Froitzheim
 *
 * Created on April 18, 2016, 3:39 PM
 */

#include <chrono>
#include <hypro/config.h>
#include <hypro/representations/GeometricObjectBase.h>

int main() {
	using namespace hypro;
	using namespace carl;

	typedef mpq_class Number;
	typedef std::chrono::high_resolution_clock clock;
	typedef std::chrono::microseconds timeunit;
	const int runs = 50;

	typename hypro::HPolytope<Number>::HalfspaceVector planes;
	hypro::HPolytope<Number> hpolytope;
	hypro::HPolytope<Number> hpolytope2;
	hypro::HPolytope<Number> hpolytope3;

	// first Hpolytope (simple triangle 2D)
	Halfspace<Number> hp1( { 1, 1 }, carl::rationalize<Number>( 1.4 ) );
	Halfspace<Number> hp2( { 0, -1 }, 1 );
	Halfspace<Number> hp3( { -1, 0 }, 1 );

	planes.push_back( hp1 );
	planes.push_back( hp2 );
	planes.push_back( hp3 );

	hpolytope = hypro::HPolytope<Number>( planes );

	// second Hpolytope (3d object)
	std::vector<vector_t<Number>> directions2 = computeTemplate<Number>( 3, 12 );
	matrix_t<Number> templateDirectionMatrix2 =
		  matrix_t<Number>( directions2.size(), 3 );

	// fills the matrix with the template directions
	for ( unsigned i = 0; i < directions2.size(); ++i ) {
		templateDirectionMatrix2.row( i ) = directions2[i];
	}

	vector_t<Number> distances2 = vector_t<Number>( directions2.size() );

	// fills the vector with a constant offset
	for ( unsigned i = 0; i < directions2.size(); ++i ) {
		distances2( i ) = 5;
	}

	hpolytope2 = hypro::HPolytope<Number>( templateDirectionMatrix2, distances2 );

	// third Hpolytope (3d object (nearly a ball))
	std::vector<vector_t<Number>> directions3 = computeTemplate<Number>( 3, 16 );
	matrix_t<Number> templateDirectionMatrix3 =
		  matrix_t<Number>( directions3.size(), 3 );

	// fills the matrix with the template directions
	for ( unsigned i = 0; i < directions3.size(); ++i ) {
		templateDirectionMatrix3.row( i ) = directions3[i];
	}

	vector_t<Number> distances3 = vector_t<Number>( directions3.size() );

	// fills the vector with a constant offset
	for ( unsigned i = 0; i < distances3.size(); ++i ) {
		distances3( i ) = 5;
	}

	hpolytope3 = hypro::HPolytope<Number>( templateDirectionMatrix3, distances3 );

	std::set<std::pair<long int, long int>> results2;
	std::set<std::pair<long int, long int>> results3;

	for ( int index = 0; index < runs; ++index ) {
		std::pair<long int, long int> testresult;

		// 2nd polytope
		clock::time_point start = clock::now();

		Converter<Number>::toBox( hpolytope2 );

		std::cout
			  << "Total time2(ConvexHull): "
			  << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
					   1000
			  << std::endl;
		testresult.first =
			  std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
			  1000;

		start = clock::now();
		Converter<Number>::toBox( hpolytope2, ALTERNATIVE );
		std::cout
			  << "Total time2(Evaluation): "
			  << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
					   1000
			  << std::endl;
		testresult.second =
			  std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
			  1000;
		results2.insert( testresult );

		// 3rd polytope
		start = clock::now();

		Converter<Number>::toBox( hpolytope3 );

		std::cout
			  << "Total time3(ConvexHull): "
			  << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
					   1000
			  << std::endl;
		testresult.first =
			  std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
			  1000;

		start = clock::now();
		Converter<Number>::toBox( hpolytope3, ALTERNATIVE );
		std::cout
			  << "Total time3(Evaluation): "
			  << std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
					   1000
			  << std::endl;
		testresult.second =
			  std::chrono::duration_cast<timeunit>( clock::now() - start ).count() /
			  1000;
		results3.insert( testresult );
	}

	double avgHull2 = 0;
	double avgEval2 = 0;
	double avgHull3 = 0;
	double avgEval3 = 0;

	for ( auto resultIt = results2.begin(); resultIt != results2.end();
		  ++resultIt ) {
		avgHull2 += double( ( *resultIt ).first / double( runs ) );
		avgEval2 += double( ( *resultIt ).second / double( runs ) );
	}

	for ( auto resultIt = results3.begin(); resultIt != results3.end();
		  ++resultIt ) {
		avgHull3 += double( ( *resultIt ).first / double( runs ) );
		avgEval3 += double( ( *resultIt ).second / double( runs ) );
	}

	std::cout << "AVGHull2: " << avgHull2 << ", AVGEval2: " << avgEval2
			  << std::endl;
	std::cout << "AVGHull3: " << avgHull3 << ", AVGEval3: " << avgEval3
			  << std::endl;

	return 0;
}
