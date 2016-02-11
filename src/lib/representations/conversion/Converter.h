#pragma once

#include "../Box/Box.h"
#include "../Polytopes/HPolytope/HPolytope.h"
#include "../Polytopes/VPolytope/VPolytope.h"

namespace hypro {

template<typename Number>
class Converter {
	public:

		using Box = BoxT<Number,Converter>;
		using HPolytope = HPolytopeT<Number,Converter>;
		using VPolytope = VPolytopeT<Number,Converter>;

		static VPolytope toVPolytope(const HPolytope& source) {
			return std::move(VPolytope(source.vertices()));
		}

		static HPolytope toHPolytope(const Box& source) {
			unsigned dim = source.dimension();                                                     //gets dimension of box
			assert( dim >= 1);                                                                      //only continue if dimension is at least 1

			matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
			for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
				directions( 2 * i, i ) = -1;
				directions( 2 * i + 1, i ) = 1;                                                   //write fixed entries (because of box) into the normal matrix (2 each column)
			}

			vector_t<Number> distances = vector_t<Number>( 2 * dim );                               //initialize distance vector with 2*dim rows

			std::vector<carl::Interval<Number>> intervals = source.boundaries();                   //gets intervals of box
			for ( unsigned i = 0; i < dim; ++i ) {                                                  //for every dimension:
				distances( 2 * i ) = -intervals[i].lower();
				distances( 2 * i + 1 ) = intervals[i].upper();                                    //write inverted lower bound values and upper bound values into the distance vector
			}														                              //constructs an H-Polytope with normal matrix and distance vector

			return std::move(HPolytope(directions, distances));
		}

		static HPolytope toHPolytope(const VPolytope& source) {
			HPolytope target;
			if ( !source.empty() ) {
				// degenerate cases
				unsigned size = source.size();
				unsigned dimension = source.dimension();
				if ( size == 1 ) {
					// TODO: Return Box constraints.
				} else if ( size < dimension ) {
					std::vector<Point<Number>> vertices = source.vertices();

					// ATTENTION: Assumption here: source is reduced, such that the d points in source span a d-1 dimensional object.

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
							target.insert( facet->hyperplane() );
						}

					}

					assert( false );
				} else {
					//std::cout << "Conv Hull" << std::endl;
					// TODO: Chose suitable convex hull algorithm
					typename std::vector<Point<Number>> points = source.vertices();
					std::vector<std::shared_ptr<Facet<Number>>> facets = convexHull( points ).first;
					//std::cout << "Conv Hull end" << std::endl;
					for ( auto &facet : facets ) {
						target.insert( facet->hyperplane() );
					}
					facets.clear();
				}
			}
			return std::move(target);
		}

		static Box toBox(const VPolytope& source) {
			Box target;
			typename VPolytope::pointVector vertices = source.vertices();                          //gets vertices as a vector from the source object
			assert( !vertices.empty() );                                                                    //only continue if any actual vertices were received at all
			vector_t<Number> minima = vertices[0].rawCoordinates();                                         //creates a vector_t with the first vertex of the source object
			vector_t<Number> maxima = vertices[0].rawCoordinates();                                         //creates another vector_t with the first vertex of the source object

			for ( const auto& vertex : vertices ) {                                                         //for each vertex of the source object
				for ( unsigned d = 0; d < source.dimension(); ++d ) {                                  //for every dimension
					minima( d ) = vertex.at( d ) < minima( d ) ? vertex.at( d ) : minima( d );      //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
					maxima( d ) = vertex.at( d ) > maxima( d ) ? vertex.at( d ) : maxima( d );      //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
					assert( minima( d ) <= maxima( d ) );                                           //only continue if the maximum value is not smaller than the minimum value
				}
			}

			std::vector<carl::Interval<Number>> intervals;
			for ( unsigned i = 0; i < source.dimension(); ++i ) {                                          //for every dimension
				intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );              //create one interval per dimension with the corresponding minimal and maximal values
			}

			target = Box( intervals );                                                             //creates a box with the computed intervals

			//if(mode == EXACT){                                                                              //checks if conversion was exact
			//    bool foundEqual;
			//    std::vector<Point<Number>> newVertices = target.vertices();                                //computes vertices from the just newly created box
			//    for (const auto& newVertex : newVertices){                                                  //for every new vertex (from the box)
			//        foundEqual = source.hasVertex(newVertex);                                              //checks if source-object contains the new vertex
			//        if (foundEqual == false){                                                               //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
			//            return false;
			//        }
			//    }
			//}

			return std::move(target);
		}

		static Box toBox(const HPolytope& source) {
			Box target;
			typename VPolytope::pointVector vertices = source.vertices();                          //gets vertices as a vector from the source object (is actually a conversion from H-Polytope to V-Polytope)
			assert( !vertices.empty() );                                                                    //only continue if any actual vertices were received at all
			vector_t<Number> minima = vertices[0].rawCoordinates();                                         //creates a vector_t with the first vertex of the source object
			vector_t<Number> maxima = vertices[0].rawCoordinates();                                         //creates another vector_t with the first vertex of the source object

			for ( const auto& vertex : vertices ) {                                                         //for each vertex of the source object
				for ( unsigned d = 0; d < source.dimension(); ++d ) {                                  //for every dimension
					minima( d ) = vertex.at( d ) < minima( d ) ? vertex.at( d ) : minima( d );      //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
					maxima( d ) = vertex.at( d ) > maxima( d ) ? vertex.at( d ) : maxima( d );      //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
					assert( minima( d ) <= maxima( d ) );                                           //only continue if the maximum value is not smaller than the minimum value
				}
			}

			std::vector<carl::Interval<Number>> intervals;
			for ( unsigned i = 0; i < source.dimension(); ++i ) {                                          //for every dimension
				intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );              //create one interval per dimension with the corresponding minimal and maximal values
			}

			target = Box( intervals );                                                             //creates a box with the computed intervals

			//if(mode == EXACT){                                                                              //checks if conversion was exact
			//    bool foundEqual;
			//    std::vector<Point<Number>> newVertices = target.vertices();                                //computes vertices from the just newly created box
			//    for (const auto& newVertex : newVertices){                                                  //for every new vertex (from the box)
			//        foundEqual = source.contains(newVertex);                                               //checks if source-object contains the new vertex
			//        if (foundEqual == false){                                                               //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
			//            return false;
			//        }
			//    }
			//}

			return target;
		}
};

template<typename Number>
using Box = typename Converter<Number>::Box;

template<typename Number>
using HPolytope = typename Converter<Number>::HPolytope;

template<typename Number>
using VPolytope = typename Converter<Number>::VPolytope;

} // namespace

