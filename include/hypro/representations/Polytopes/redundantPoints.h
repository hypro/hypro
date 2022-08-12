#include "../../types.h"
#include "../../util/linearOptimization/Optimizer.h"

namespace hypro {

template <typename Number>
std::vector<Point<Number>> removeRedundantPoints( const std::vector<Point<Number>>& points ) {
	if ( !points.empty() ) {
		// Find redundant vertices by checking whether a vertex can be represented as convex combination of the other vertices
		std::size_t vertexCount = points.size();
		std::vector<std::size_t> redundantVertices{};
		for ( std::size_t vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex ) {
			if ( vertexCount - redundantVertices.size() == 1 ) {
				// Only one vertex remaining
				break;
			}
			matrix_t<Number> A = matrix_t<Number>( points[0].dimension(), vertexCount - redundantVertices.size() - 1 );
			Eigen::Index colIndex = 0;
			for ( std::size_t i = 0; i < vertexCount; ++i ) {
				// Only use other non-redundant for convex combination
				if ( i != vertexIndex && std::find( redundantVertices.begin(), redundantVertices.end(), i ) == redundantVertices.end() ) {
					A.col( colIndex ) = points[i].rawCoordinates();
					colIndex += 1;
				}
			}

			// Convex combination should equal the current vertex
			Optimizer<Number> opt( A, points[vertexIndex].rawCoordinates() );
			opt.setRelations( std::vector<carl::Relation>( points[0].dimension(), carl::Relation::EQ ) );

			// Bound columns
			for ( Eigen::Index colIndex = 0; colIndex < A.cols(); ++colIndex ) {
				vector_t<Number> constraint = vector_t<Number>::Zero( A.cols() );
				constraint( colIndex ) = 1;
				opt.addConstraint( constraint, 1, carl::Relation::LEQ );
				opt.addConstraint( constraint, 0, carl::Relation::GEQ );
			}
			// Add constraint that all coefficients add up to 1
			vector_t<Number> constraint = vector_t<Number>::Ones( A.cols() );
			opt.addConstraint( constraint, 1, carl::Relation::EQ );

			if ( opt.checkConsistency() ) {
				redundantVertices.push_back( vertexIndex );
			}
		}

		// Create new list of vertices that only contains the non-redundant ones
		std::vector<Point<Number>> reducedVertices( vertexCount - redundantVertices.size() );
		std::size_t reducedIndex = 0;
		for ( std::size_t vIndex = 0; vIndex < vertexCount; ++vIndex ) {
			if ( std::find( redundantVertices.begin(), redundantVertices.end(), vIndex ) == redundantVertices.end() ) {
				reducedVertices[reducedIndex] = points[vIndex];
				reducedIndex += 1;
			}
		}

		return reducedVertices;
	}
    return points;
}

}  // namespace hypro
