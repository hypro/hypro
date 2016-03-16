/**
 * Specialization for a converter to a box.
 * @file converterToBox.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-12
 * @version	2016-01-11
 */

#include "Converter.h"

//TODO alternative approach for H -> Box (testing which is faster)

// conversion from box to box (no differentiation between conversion modes - always EXACT)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const Box& _source, const CONV_MODE mode ) {
	return _source;
}
// conversion from support function to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const SupportFunction& _source, const CONV_MODE mode ) {
	unsigned dim = _source.dimension();                                                                     //gets dimension from the source object

	matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
	for ( unsigned i = 0; i < dim; ++i ) {                                                                  //for every dimension
		directions( 2 * i, i ) = -1;
		directions( 2 * i + 1, i ) = 1;                                                                 //write fixed entries (because of box) into the normal matrix (2 each column)
	}

	std::vector<evaluationResult<Number>> distances = _source.multiEvaluate( directions );                                       //evaluate the source support function into these 2*dim directions (to get the interval end points)

	std::vector<carl::Interval<Number>> intervals;
	for ( unsigned i = 0; i < dim; ++i ) {                                                                  //for every dimension
        carl::BoundType lowerBound = carl::BoundType::WEAK;
        carl::BoundType upperBound = carl::BoundType::WEAK;
        if(distances[2*i].errorCode == SOLUTION::INFTY)
            lowerBound = carl::BoundType::INFTY;
        if(distances[2*i+1].errorCode == SOLUTION::INFTY)
            upperBound = carl::BoundType::INFTY;
		intervals.push_back( carl::Interval<Number>( -distances[2*i].supportValue, lowerBound, distances[2*i+1].supportValue, upperBound ) );   //create one interval with the corresponding left and right end points (inverted lower interval end points)
	}

    // if (mode == EXACT){                                                                                      //checks if conversion was exact
    //     bool foundEqual;
    //     std::vector<Point<Number>> newVertices = _target.vertices();                                         //computes vertices from the just newly created box
    //     for (const auto& newVertex : newVertices){                                                           //for every new vertex (from the box)
    //         foundEqual = _source.contains(newVertex);                                                        //checks if source-object contains the new vertex
    //         if (foundEqual == false){                                                                        //if source object doesn't contain any of the new vertices, the target object has to be an overapproximation (and thus no exact conversion is possible)
    //             return false;
    //         }
    //     }
    // }

	return BoxT<Number,Converter>( intervals );
}

//conversion from V-Polytope to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const VPolytope& _source, const CONV_MODE mode ) {
	typename VPolytopeT<Number,Converter>::pointVector vertices = _source.vertices();               //gets vertices as a vector from the source object
	assert( !vertices.empty() );                                                                    //only continue if any actual vertices were received at all
	vector_t<Number> minima = vertices[0].rawCoordinates();                                         //creates a vector_t with the first vertex of the source object
	vector_t<Number> maxima = vertices[0].rawCoordinates();                                         //creates another vector_t with the first vertex of the source object

	for ( const auto& vertex : vertices ) {                                                         //for each vertex of the source object
		for ( unsigned d = 0; d < _source.dimension(); ++d ) {                                  //for every dimension
			minima( d ) = vertex.at( d ) < minima( d ) ? vertex.at( d ) : minima( d );      //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
			maxima( d ) = vertex.at( d ) > maxima( d ) ? vertex.at( d ) : maxima( d );      //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
			assert( minima( d ) <= maxima( d ) );                                           //only continue if the maximum value is not smaller than the minimum value
		}
	}

	std::vector<carl::Interval<Number>> intervals;
	for ( unsigned i = 0; i < _source.dimension(); ++i ) {                                          //for every dimension
		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );              //create one interval per dimension with the corresponding minimal and maximal values
	}

    // if(mode == EXACT){                                                                               //checks if conversion was exact
    //     bool foundEqual;
    //     std::vector<Point<Number>> newVertices = _target.vertices();                                 //computes vertices from the just newly created box
    //     for (const auto& newVertex : newVertices){                                                   //for every new vertex (from the box)
    //         foundEqual = _source.hasVertex(newVertex);                                               //checks if source-object contains the new vertex
    //         if (foundEqual == false){                                                                //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
    //             return false;
    //         }
    //     }
    // }

	return BoxT<Number,Converter>( intervals );                                          //creates a box with the computed intervals
}

//conversion from H-Polytope to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const HPolytope& _source, const CONV_MODE mode ) {
	typename VPolytope::pointVector vertices = _source.vertices();                                  //gets vertices as a vector from the source object (is actually a conversion from H-Polytope to V-Polytope)
	assert( !vertices.empty() );                                                                    //only continue if any actual vertices were received at all
	vector_t<Number> minima = vertices[0].rawCoordinates();                                         //creates a vector_t with the first vertex of the source object
	vector_t<Number> maxima = vertices[0].rawCoordinates();                                         //creates another vector_t with the first vertex of the source object

	for ( const auto& vertex : vertices ) {                                                         //for each vertex of the source object
		for ( unsigned d = 0; d < _source.dimension(); ++d ) {                                  //for every dimension
			minima( d ) = vertex.at( d ) < minima( d ) ? vertex.at( d ) : minima( d );      //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
			maxima( d ) = vertex.at( d ) > maxima( d ) ? vertex.at( d ) : maxima( d );      //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
			assert( minima( d ) <= maxima( d ) );                                           //only continue if the maximum value is not smaller than the minimum value
		}
	}

	std::vector<carl::Interval<Number>> intervals;
	for ( unsigned i = 0; i < _source.dimension(); ++i ) {                                          //for every dimension
		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );              //create one interval per dimension with the corresponding minimal and maximal values
	}

    // if(mode == EXACT){                                                                              //checks if conversion was exact
    //     bool foundEqual;
    //     std::vector<Point<Number>> newVertices = _target.vertices();                                //computes vertices from the just newly created box
    //     for (const auto& newVertex : newVertices){                                                  //for every new vertex (from the box)
    //         foundEqual = _source.contains(newVertex);                                               //checks if source-object contains the new vertex
    //         if (foundEqual == false){                                                               //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
    //             return false;
    //         }
    //     }
    // }

    return BoxT<Number,Converter>( intervals );                                             //creates a box with the computed intervals
}

//alternative approach
/*
        template<typename Number>
        boo
    Box<Number> Converter<Number>::toBox( const HPolytope<Number>& _source, const CONV_MODE mode ) {
                unsigned dim = _source.dimension();                                                                              //gets dimension from the source object

                matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                                            //initialize normal matrix as zero matrix with 2*dim rows and dim columns
                for ( unsigned i = 0; i < dim; ++i ) {                                                                           //for every dimension
                        directions( 2 * i, i ) = -1;
                        directions( 2 * i + 1, i ) = 1;                                                                          //write fixed entries (because of box) into the normal matrix (2 each column)
                }

                vector_t<Number> distances = vector_t<Number>::Zero(2 * dim);
                for ( unsigned i = 0; i < dim, ++i ) {                                                                          //evaluate the source support function into these 2*dim directions (to get the interval end points)
                        distances( 2 * i) = evaluate(directions.row(2*i).transpose() );
                        distances( 2 * i + 1) = evaluate(directions.row(2*i+1).transpose() );
                }

                std::vector<carl::Interval<Number>> intervals;
                for ( unsigned i = 0; i < dim; ++i ) {                                                                           //for every dimension
                        intervals.push_back( carl::Interval<Number>( -distances( 2 * i ), distances( 2 * i + 1 ) ) );             //create one interval with the corresponding left and right end points
                }

                _target = BoxT<Number,Converter>( intervals );                                                                              //creates a box with the computed intervals

                 if (mode == EXACT){                                                                                             //checks if conversion was exact
                         bool foundEqual;
                         std::vector<Point<Number>> newVertices = _target.vertices();                                            //computes vertices from the just newly created box
                                 for (const auto& newVertex : newVertices){                                                      //for every new vertex (from the box)
                                           foundEqual = _source.contains(newVertex);                                             //checks if source-object contains the new vertex
                                           if (foundEqual == false){                                                             //if source object doesn't contain any of the new vertices, the target object has to be an overapproximation (and thus no exact conversion is possible)
                                                return false;
                                           }
                                 }
                 }

                 return true;
        }
 */

//conversion from zonotope to box (no differentiation between conversion modes - always OVER)
template<typename Number>
typename Converter<Number>::Box Converter<Number>::toBox( const Zonotope& _source, const CONV_MODE mode ) {
        typename std::vector<vector_t<Number>> vertices = _source.vertices();                                   //computes vertices from source object
	assert( !vertices.empty() );                                                                            //only continue if any actual vertices were received at all
	vector_t<Number> minima = vertices[0];                                                                  //creates a vector_t with the first vertex of the source object
	vector_t<Number> maxima = vertices[0];                                                                  //creates another vector_t with the first vertex of the source object

	for ( std::size_t i = 0; i < vertices.size(); ++i ) {                                                   //for each vertex of the source object
		for ( std::size_t d = 0; d < _source.dimension(); ++d ) {                                       //for every dimension
			minima( d ) = vertices[i]( d ) < minima( d ) ? vertices[i]( d ) : minima( d );          //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
			maxima( d ) = vertices[i]( d ) > maxima( d ) ? vertices[i]( d ) : maxima( d );          //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
			assert( minima( d ) <= maxima( d ) );                                                   //only continue if the maximum value is not smaller than the minimum value
		}
	}

	std::vector<carl::Interval<Number>> intervals;
	for ( std::size_t i = 0; i < _source.dimension(); ++i ) {                                               //for every dimension
		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );                      //create one interval per dimension with the corresponding minimal and maximal values
	}

    // if(mode == EXACT){                                                                                      //checks if conversion was exact
    //     bool foundEqual;
    //     std::vector<Point<Number>> newVertices = _target.vertices();                                        //computes vertices from the just newly created box
    //     for (const auto& newVertex : newVertices){                                                          //for every new vertex (from the box)
    //         foundEqual = false;
    //         for (const auto& oldVertex : vertices){                                                         //checks if source-object contains the new vertex
    //             if (newVertex == oldVertex){
    //                 foundEqual = true;
    //             }
    //         }
    //         if (foundEqual == false){                                                                       //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
    //             return false;
    //         }
    //     }
    // }

	return BoxT<Number,Converter>( intervals );                                                 //creates a box with the computed intervals
}

//conversion from Polytope to box (different data structure)
//template<typename Number>
//Box Converter<Number>::toBox( const hypro::Polytope<Number>& _source, const CONV_MODE mode ) {
//	std::vector<Point<Number>> points = _source.vertices();                                                                         //gets vertices as a vector from the source object
//	assert( !points.empty() );                                                                                                      //only continue if any actual vertices were received at all
//
//	vector_t<Number> minima = points[0].rawCoordinates();                                                                           //creates a vector_t with the first vertex of the source object
//	vector_t<Number> maxima = points[0].rawCoordinates();                                                                           //creates another vector_t with the first vertex of the source object
//
//	for ( std::size_t i = 0; i < points.size(); ++i ) {                                                                             //for each vertex of the source object
//		for ( std::size_t d = 0; d < _source.dimension(); ++d ) {                                                               //for every dimension
//			minima( d ) = points[i].rawCoordinates()( d ) < minima( d ) ? points[i].rawCoordinates()( d ) : minima( d );    //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
//			maxima( d ) = points[i].rawCoordinates()( d ) > maxima( d ) ? points[i].rawCoordinates()( d ) : maxima( d );    //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
//			assert( minima( d ) <= maxima( d ) );                                                                           //only continue if the maximum value is not smaller than the minimum value
//		}
//	}
//
//	std::vector<carl::Interval<Number>> intervals;
//	for ( std::size_t i = 0; i < _source.dimension(); ++i ) {                                                                       //for every dimension
//		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );                                              //create one interval per dimension with the corresponding minimal and maximal values
//	}
//
//    // if(mode == EXACT){                                                                                                              //checks if conversion was exact
//    //     bool foundEqual;
//    //     std::vector<Point<Number>> newVertices = _target.vertices();                                                                //computes vertices from the just newly created box
//    //     for (const auto& newVertex : newVertices){                                                                                  //for every new vertex (from the box)
//    //         foundEqual = false;
//    //         for (const auto& oldVertex : points){                                                                                   //checks if source-object contains the new vertex
//    //             if (newVertex == oldVertex){
//    //                 foundEqual = true;
//    //             }
//    //         }
//    //         if (foundEqual == false){                                                                                               //if no equal vertex was found, the target object has to be an overapproximation (and thus no exact conversion is possible)
//    //             return false;
//    //         }
//    //     }
//    // }
//
//	return std::move(BoxT<Number,Converter>( intervals ));
//}
