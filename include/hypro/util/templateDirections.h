/**
 * Specialization of some helper functions for computing template directions
 * @file templateDirections.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @version	2016-03-18
 */

#pragma once
#include "sequenceGeneration/SequenceGenerator.h"

namespace hypro {

/*
 * Compute a uniform distribution of directions for a dimension-dimensional space template polytope
 */
#define PI 3.14159265359
template <typename Number>
static std::vector<vector_t<Number>> computeTemplate( std::size_t dimension, std::size_t numberDirections ) {
	if ( dimension == 1 ) {
		std::vector<vector_t<Number>> directions;
		vector_t<Number> v0 = vector_t<Number>::Zero( 1 );
		vector_t<Number> v1 = vector_t<Number>::Zero( 1 );
		v0 << 1;
		v1 << -1;
		directions.emplace_back( v0 );
		directions.emplace_back( v1 );
		return directions;
	}

	double degree = ( 360 / (double)numberDirections ) * PI / 180.0;
	std::vector<vector_t<Number>> directions;

	if ( numberDirections == 4 ) {
		for ( std::size_t i = 0; i < dimension; ++i ) {
			vector_t<Number> dir = vector_t<Number>::Zero( dimension );
			dir( i ) = 1;
			directions.push_back( dir );
			dir( i ) = -1;
			directions.push_back( dir );
		}
		return directions;
	} else if ( numberDirections == 8 ) {
		/*
		vector_t<Number> v0 = vector_t<Number>::Zero(2);
		vector_t<Number> v1 = vector_t<Number>::Zero(2);
		vector_t<Number> v2 = vector_t<Number>::Zero(2);
		vector_t<Number> v3 = vector_t<Number>::Zero(2);
		vector_t<Number> v4 = vector_t<Number>::Zero(2);
		vector_t<Number> v5 = vector_t<Number>::Zero(2);
		vector_t<Number> v6 = vector_t<Number>::Zero(2);
		vector_t<Number> v7 = vector_t<Number>::Zero(2);

		v0 << 1,0;
		v1 << 1,1;
		v2 << 0,1;
		v3 << -1,1;
		v4 << -1,0;
		v5 << -1,-1;
		v6 << 0,-1;
		v7 << 1,-1;

		directions2d.push_back(v0);
		directions2d.push_back(v1);
		directions2d.push_back(v2);
		directions2d.push_back(v3);
		directions2d.push_back(v4);
		directions2d.push_back(v5);
		directions2d.push_back(v6);
		directions2d.push_back(v7);
		*/
		// first create box template, then add combinations.
		for ( std::size_t i = 0; i < dimension; ++i ) {
			vector_t<Number> dir = vector_t<Number>::Zero( dimension );
			dir( i ) = 1;
			directions.push_back( dir );
			dir( i ) = -1;
			directions.push_back( dir );
		}

		// create the diagonal directions
		Permutator permutator( dimension, 2 );
		std::vector<std::size_t> permutation;
		while ( !permutator.end() ) {
			permutation = permutator();
			vector_t<Number> dir = vector_t<Number>::Zero( dimension );
			dir( permutation[0] ) = 1;
			dir( permutation[1] ) = 1;
			directions.push_back( dir );
			dir( permutation[0] ) = -1;
			dir( permutation[1] ) = -1;
			directions.push_back( dir );
			dir( permutation[0] ) = -1;
			dir( permutation[1] ) = 1;
			directions.push_back( dir );
			dir( permutation[0] ) = 1;
			dir( permutation[1] ) = -1;
			directions.push_back( dir );
		}
		return directions;
	} else {
		std::vector<vector_t<Number>> directions2d;
		// create directions2d
		vector_t<Number> templateVector2d = vector_t<Number>::Zero( 2 );  // init templateVector2d
		templateVector2d( 0 ) = 1;
		templateVector2d( 1 ) = 0;
		directions2d.push_back( templateVector2d );

		matrix_t<Number> m( 2, 2 );	 // init matrix
		m( 0, 0 ) = carl::rationalize<Number>( cos( degree ) );
		m( 0, 1 ) = carl::rationalize<Number>( ( -1 ) * sin( degree ) );
		m( 1, 0 ) = carl::rationalize<Number>( sin( degree ) );
		m( 1, 1 ) = carl::rationalize<Number>( cos( degree ) );

		for ( unsigned i = 0; i < ( numberDirections - 1 ); ++i ) {
			// Rotate templateVector
			templateVector2d = m * templateVector2d;
			directions2d.push_back( templateVector2d );
		}
		// copy directions2d into directions
		Permutator permutator( dimension, 2 );
		std::vector<std::size_t> permutation;
		while ( !permutator.end() ) {
			permutation = permutator();
			for ( vector_t<Number> vectorOfdirections2d : directions2d ) {
				vector_t<Number> templateVector = vector_t<Number>::Zero( dimension );	// init templateVector

				templateVector( permutation.at( 0 ) ) = vectorOfdirections2d( 0 );
				templateVector( permutation.at( 1 ) ) = vectorOfdirections2d( 1 );

				if ( std::find( directions.begin(), directions.end(), templateVector ) == directions.end() ) {
					directions.push_back( templateVector );
				}
			}
		}

		return directions;
	}
}

template <typename Number>
static std::vector<vector_t<Number>> computeTemplate( std::vector<std::size_t> dimensions, std::size_t numberDirections, std::size_t dim ) {
	std::vector<vector_t<Number>> directions;

	if ( numberDirections == 4 ) {
		for ( auto i : dimensions ) {
			vector_t<Number> dir = vector_t<Number>::Zero( dim );
			dir( i ) = 1;
			directions.push_back( dir );
			dir( i ) = -1;
			directions.push_back( dir );
		}
		return directions;
	} else if ( numberDirections == 8 ) {
		for ( auto i : dimensions ) {
			vector_t<Number> dir = vector_t<Number>::Zero( dim );
			dir( i ) = 1;
			directions.push_back( dir );
			dir( i ) = -1;
			directions.push_back( dir );
		}

		// create the diagonal directions
		Permutator permutator( dimensions.size(), 2 );
		std::vector<std::size_t> permutation;
		while ( !permutator.end() ) {
			permutation = permutator();
			vector_t<Number> dir = vector_t<Number>::Zero( dim );
			dir( dimensions[permutation[0]] ) = 1;
			dir( dimensions[permutation[1]] ) = 1;
			directions.push_back( dir );
			dir( dimensions[permutation[0]] ) = -1;
			dir( dimensions[permutation[1]] ) = -1;
			directions.push_back( dir );
			dir( dimensions[permutation[0]] ) = -1;
			dir( dimensions[permutation[1]] ) = 1;
			directions.push_back( dir );
			dir( dimensions[permutation[0]] ) = 1;
			dir( dimensions[permutation[1]] ) = -1;
			directions.push_back( dir );
		}
		return directions;
	} else {
		std::vector<vector_t<Number>> directions2d;
		double degree = ( 360 / (double)numberDirections ) * PI / 180.0;
		// create directions2d
		vector_t<Number> templateVector2d = vector_t<Number>::Zero( 2 );  // init templateVector2d
		templateVector2d( 0 ) = 1;
		templateVector2d( 1 ) = 0;
		directions2d.push_back( templateVector2d );

		matrix_t<Number> m( 2, 2 );	 // init matrix
		m( 0, 0 ) = carl::rationalize<Number>( cos( degree ) );
		m( 0, 1 ) = carl::rationalize<Number>( ( -1 ) * sin( degree ) );
		m( 1, 0 ) = carl::rationalize<Number>( sin( degree ) );
		m( 1, 1 ) = carl::rationalize<Number>( cos( degree ) );

		for ( unsigned i = 0; i < ( numberDirections - 1 ); ++i ) {
			// Rotate templateVector
			templateVector2d = m * templateVector2d;
			directions2d.push_back( templateVector2d );
		}

		// std::cout << "Call to permutator with " << dimensions.size() << " choices and a set size of 2." << std::endl;

		// copy directions2d into directions
		Permutator permutator( dimensions.size(), 2 );
		std::vector<std::size_t> permutation;
		while ( !permutator.end() ) {
			permutation = permutator();
			// std::cout << "Progress permutation " << permutation << std::endl;
			for ( vector_t<Number> vectorOfdirections2d : directions2d ) {
				vector_t<Number> templateVector = vector_t<Number>::Zero( dim );  // init templateVector
				// std::cout << "Process template direction " << vectorOfdirections2d << std::endl;

				auto pos = dimensions.begin();
				std::size_t permPos = permutation.at( 0 );
				// std::cout << "PermPos = " << permPos << std::endl;
				//  TODO: This does not make sense?
				while ( permPos > 0 ) {
					++pos;
					--permPos;
				}
				// std::cout << "Real pos: " << *pos << std::endl;

				templateVector( *pos ) = vectorOfdirections2d( 0 );

				pos = dimensions.begin();
				permPos = permutation.at( 1 );
				// std::cout << "PermPos = " << permPos << std::endl;
				while ( permPos > 0 ) {
					++pos;
					--permPos;
				}
				// std::cout << "Real pos: " << *pos << std::endl;

				templateVector( *pos ) = vectorOfdirections2d( 1 );

				// std::cout << "New template vector: " << templateVector << std::endl;

				if ( std::find( directions.begin(), directions.end(), templateVector ) == directions.end() ) {
					directions.push_back( templateVector );
				}
			}
		}
		return directions;
	}
}

}  // namespace hypro
