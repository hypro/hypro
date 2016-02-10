/**
 * Specialization for a converter to an H-polytope.
 * @file converterToHPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "converterToHPolytope.h"

namespace hypro {
    //conversion from H-Polytope to H-Polytope
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::HPolytope<Number>& _target, const CONV_MODE mode ){
        _target = _source;
        return true;
    }

    //conversion from V-Polytope to H-Polytope
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::HPolytope<Number>& _target, const CONV_MODE mode ){
        if ( !_source.empty() ) {
			// degenerate cases
			unsigned size = _source.size();
			unsigned dimension = _source.dimension();
			if ( size == 1 ) {
				// TODO: Return Box constraints.
			} else if ( size < dimension ) {
				std::vector<Point<Number>> vertices = _source.vertices();

				// ATTENTION: Assumption here: _source is reduced, such that the d points in _source span a d-1 dimensional object.

				// find all hyperplanar descriptions by reducing to d dimensions (get the plane)
				std::size_t dim = vertices.size();
				polytope::dPermutator permutator(dimension, dim);

				std::vector<unsigned> permutation;
				while(!permutator.end()) {
					permutation = permutator();

					// project to chosen dimensions
					std::vector<Point<Number>> reducedVertices;
					reducedVertices.reserve(dim);
					for(const auto& vertex : vertices) {
						vector_t<Number> reductor = vector_t<Number>(dim);
						for(unsigned d = 0; d < dim; ++d)
							reductor(d) = vertex.at(d);

						reducedVertices.push_back(Point<Number>(std::move(reductor)));
					}

					std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( reducedVertices ).first;
					//std::cout << "Conv Hull end" << std::endl;
					for ( auto &facet : facets ) {
						_target.insert( facet->hyperplane() );
					}

				}

				assert( false );
			} else {
				//std::cout << "Conv Hull" << std::endl;
				// TODO: Chose suitable convex hull algorithm
				typename std::vector<Point<Number>> points = _source.vertices();
				std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
				//std::cout << "Conv Hull end" << std::endl;
				for ( auto &facet : facets ) {
					_target.insert( facet->hyperplane() );
				}
				facets.clear();
			}
		}                                                  //converts the source object into an H-polytope via constructor
        return true;
    }

    //conversion from Box to H-Polytope
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::HPolytope<Number>& _target, const CONV_MODE mode ){
         unsigned dim = _source.dimension();                                                     //gets dimension of box
         assert( dim >= 1);                                                                      //only continue if dimension is at least 1

         matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
         for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
               directions( 2 * i, i ) = -1;
               directions( 2 * i + 1, i ) = 1;                                                   //write fixed entries (because of box) into the normal matrix (2 each column)
         }

         vector_t<Number> distances = vector_t<Number>( 2 * dim );                               //initialize distance vector with 2*dim rows

         std::vector<carl::Interval<Number>> intervals = _source.boundaries();                   //gets intervals of box
         for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
               distances( 2 * i ) = -intervals[i].lower();
               distances( 2 * i + 1 ) = intervals[i].upper();                                    //write inverted lower bound values and upper bound values into the distance vector
         }

         _target = HPolytope<Number>(directions, distances);                                     //constructs an H-Polytope with normal matrix and distance vector

         return true;
    }

    //TODO conversion from zonotope to H-Polytope
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::HPolytope<Number>& _target, const CONV_MODE mode ){
        return true;
    }

    //TODO conversion from support function to H-Polytope
    template <typename Number>
    static bool convert( const hypro::SupportFunction<Number>& _source, hypro::HPolytope<Number>& _target, const CONV_MODE mode){
        return true;
    }

}  // namespace


