/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 16.05.22.
 */

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/templateDirections.h>

int main() {
	using Number = double;
	std::size_t dim = 2;
	std::size_t directionCount = 8;

	auto directions = hypro::computeTemplate<Number>( dim, directionCount );
	// create a unit polytope (all distances are one)
	auto directionMatrix = hypro::createMatrix( directions );
	auto distanceVector = hypro::vector_t<Number>::Ones( directionCount );
	auto polytope = hypro::HPolytope<Number>( directionMatrix, distanceVector );

	// function sorting the template according to the L2-norm with the direction
	auto orderDirections = []( const auto& directions, const auto& direction ) {
		auto dim = directions.cols();
		std::map<Number, std::vector<Eigen::Index>> best;
		for ( Eigen::Index row = 0; row < directions.rows(); ++row ) {
			auto n = hypro::vector_t<Number>( directions.row( row ) ).dot( direction );
			if ( best.find( n ) == best.end() )
				best.insert( std::make_pair( n, std::vector<Eigen::Index>{ row } ) );
			else
				best[n].push_back( row );
		}
		return best;
	};
	auto direction = hypro::vector_t<Number>( dim );
	// direction.normalize();

	std::cout << "Direction: " << direction << std::endl;

	auto sorted = orderDirections( directionMatrix, direction );

	std::cout << "sorted directions:\n";
	for ( const auto& [value, index] : sorted ) {
		std::cout << value << ", ";
		for ( auto i : index ) {
			std::cout << i << ", ";
		}
		std::cout << std::endl;
	}

	// get the reference solution
	auto distance = polytope.evaluate( direction ).supportValue;
	// compute solution with the new approach, less aggressive for now
	auto constraints = hypro::matrix_t<Number>( dim, dim );
	auto constants = hypro::vector_t<Number>( dim );
	std::size_t count = 0;
	std::size_t pos = 0;
	std::size_t i = 0;
	while ( count < dim ) {
		constraints.row( count ) = directionMatrix.row( std::next( sorted.rbegin(), i )->second[pos] );
		constants( count ) = distanceVector( std::next( sorted.rbegin(), i )->second[pos] );
		++count;
		++pos;
		if ( count == std::next( sorted.rbegin(), i )->second.size() ) {
			pos = 0;
			++i;
		}
	}
	// For now use Optimizer - the benefit should be the reduced effort for the linear optimization
	auto opt = hypro::Optimizer( constraints, constants );
	auto distance_new = opt.evaluate( direction, true ).supportValue;

	std::cout << "Distance: " << distance << ", distance new: " << distance_new << std::endl;

	return 0;
}