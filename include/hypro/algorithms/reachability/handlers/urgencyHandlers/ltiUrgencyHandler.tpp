/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ltiUrgencyHandler.h"

namespace hypro {

template <typename Representation>
template <typename Location>
std::vector<Representation> ltiUrgencyHandler<Representation>::urgentSetDifference(
	  const std::vector<Representation>& segment, Transition<Number, Location>* trans ) {
	std::vector<Representation> splitSegment;
	for ( const Representation& s : segment ) {
		std::vector<Representation> sDiff = setDifference( s, trans->getJumpEnablingSet() );
		if ( sDiff.size() > 1 ) {
			COUNT( "Set difference split" );
		}
		splitSegment.insert( splitSegment.end(), sDiff.begin(), sDiff.end() );
	}
	return splitSegment;
}

template <class Representation>
template <typename Location>
Representation ltiUrgencyHandler<Representation>::cutoff( Representation const& set, Transition<Number, Location>* trans ) {
	auto condition = trans->getJumpEnablingSet();
	if ( condition.isTrue() || set.empty() ) {
		return Representation::Empty();
	} else if ( condition.isFalse() || set.empty() ) {
		return set;
	} else if ( intersect( set, condition ).first == CONTAINMENT::FULL ) {
		return Representation::Empty();
	}
	START_BENCHMARK_OPERATION( "Cutoff setup" );
	std::size_t dimension = set.dimension();

	// Used to check whether points satisfy the condition
	Optimizer<Number> conditionOptimizer( condition.getMatrix(), condition.getVector() );
	// Used to replace vertices
	Optimizer<Number> vertexOptimizer;

	// Build matrix and vector for vertex optimizer
	matrix_t<Number> mat( condition.getMatrix().rows() + 2 * dimension + 4, dimension + 2 );
	vector_t<Number> vec( mat.rows() );
	mat.bottomLeftCorner( condition.getMatrix().rows(), condition.getMatrix().cols() ) = condition.getMatrix();
	mat.bottomRightCorner( condition.getMatrix().rows(), 2 ) = matrix_t<Number>::Zero( condition.getMatrix().rows(), 2 );
	mat.topRows( 2 * dimension + 4 ) = matrix_t<Number>::Zero( 2 * dimension + 4, dimension + 2 );
	for ( std::size_t i = 0; i < dimension; ++i ) {
		mat( 2 * i, i ) = -1;
		mat( 2 * i + 1, i ) = 1;
	}
	// equations for lambda and 1 - lambda (sum equals 1, both >= 0)
	mat( 2 * dimension, dimension ) = 1;
	mat( 2 * dimension, dimension + 1 ) = 1;
	mat( 2 * dimension + 1, dimension ) = -1;
	mat( 2 * dimension + 1, dimension + 1 ) = -1;
	mat( 2 * dimension + 2, dimension ) = -1;
	mat( 2 * dimension + 3, dimension + 1 ) = -1;

	vec.tail( condition.getVector().rows() ) = condition.getVector();
	vec.head( 2 * dimension ) = vector_t<Number>::Zero( 2 * dimension );
	vec( 2 * dimension ) = 1;
	vec( 2 * dimension + 1 ) = -1;
	vec( 2 * dimension + 2 ) = 0;
	vec( 2 * dimension + 3 ) = 0;

	vertexOptimizer.setVector( vec );

	// Used to maximize in the direction of other vertices
	vector_t<Number> lambda = vector_t<Number>::Zero( dimension + 2 );
	lambda( dimension + 1 ) = 1;
	STOP_BENCHMARK_OPERATION( "Cutoff setup" );

	START_BENCHMARK_OPERATION( "Cutoff compute vertices" );
	std::vector<Point<Number>> oldVertices = set.vertices();
	STOP_BENCHMARK_OPERATION( "Cutoff compute vertices" );
	std::vector<Point<Number>> newVertices;
	START_BENCHMARK_OPERATION( "Cutoff replace vertices" );
	for ( const auto& vertex : oldVertices ) {
		// only replace vertices that satisfy the condition
		if ( !conditionOptimizer.checkPoint( vertex ) ) {
			newVertices.push_back( vertex );
			continue;
		}
		// start replacing vertex
		std::vector<Point<Number>> replacement;
		for ( const auto& otherVertex : oldVertices ) {
			if ( conditionOptimizer.checkPoint( otherVertex ) ) continue;
			// set up LP problem
			for ( std::size_t i = 0; i < dimension; ++i ) {
				mat( 2 * i, dimension ) = vertex.at( i );
				mat( 2 * i + 1, dimension ) = -vertex.at( i );
				mat( 2 * i, dimension + 1 ) = otherVertex.at( i );
				mat( 2 * i + 1, dimension + 1 ) = -otherVertex.at( i );
			}
			vertexOptimizer.setMatrix( mat );
			// solve LP problem and add new vertex for replacement
			const auto res = vertexOptimizer.evaluate( lambda, false );
			assert( res.errorCode == SOLUTION::FEAS );
			assert( res.supportValue >= 0 ||
					res.supportValue <= 1 ||
					carl::AlmostEqual2sComplement( res.supportValue, Number( 0 ) ) ||
					carl::AlmostEqual2sComplement( res.supportValue, Number( 1 ) ) );
			if ( res.supportValue == 0 ) {
				replacement = { vertex };
				break;
			}
			assert( res.supportValue < 1 );
			replacement.push_back( Point<Number>( res.optimumValue.head( dimension ) ) );
		}
		newVertices.insert( newVertices.end(), replacement.begin(), replacement.end() );
	}
	STOP_BENCHMARK_OPERATION( "Cutoff replace vertices" );
	if ( newVertices == oldVertices ) {
		return set;
	}
	START_BENCHMARK_OPERATION( "Cutoff convert back" );
	VPolytope<Number> newPol( newVertices );
	Representation res;
	convert( newPol, res );
	STOP_BENCHMARK_OPERATION( "Cutoff convert back" );
	return res;
}

}  // namespace hypro