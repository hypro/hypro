/**
 * Specialization for a converter to a box.
 * @file converterToBox.tpp
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-12
 * @version	2015-12-16
 */

#include "converterToBox.h"

namespace hypro{
    
//TODO testing!!!

// conversion from box to box    
template <typename Number>
static bool convert( const hypro::Box<Number>& _source, hypro::Box<Number>& _target, const CONV_MODE mode ) {
	_target = _source;
	return true;
}
// conversion from support function to box
//TODO return value (check for exact conversion)
template <typename Number>
static bool convert( const hypro::SupportFunction<Number>& _source, hypro::Box<Number>& _target, const CONV_MODE mode ) {
	unsigned dim = _source.dimension();                                                                     //gets dimension from the source object                                                               

	matrix_t<Number> directions = matrix_t<Number>::Zero( 2 * dim, dim );                                   //initialize normal matrix as zero matrix with 2*dim rows and dim columns
	for ( unsigned i = 0; i < dim; ++i ) {                                                                  //for every dimension
		directions( 2 * i, i ) = -1;
		directions( 2 * i + 1, i ) = 1;                                                                 //write fixed entries (because of box) into the normal matrix (2 each column)
	}

	vector_t<Number> distances = _source.multiEvaluate( directions );                                       //evaluate the source support function into these 2*dim directions (to get the interval end points)

	std::vector<carl::Interval<Number>> intervals;
	for ( unsigned i = 0; i < dim; ++i ) {                                                                  //for every dimension
		intervals.push_back( carl::Interval<Number>( distances( 2 * i ), distances( 2 * i + 1 ) ) );    //create one interval with the corresponding left and right end points
	}

	_target = Box<Number>( intervals );                                                                     //creates a box with the computed intervals

	return true; 
}

//conversion from V-Polytope to box
template <typename Number>
static bool convert( const hypro::VPolytope<Number>& _source, hypro::Box<Number>& _target, const CONV_MODE mode ) {
	typename VPolytope<Number>::pointVector vertices = _source.vertices();                          //gets vertices as a vector from the source object
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

	_target = Box<Number>( intervals );                                                             //creates a box with the computed intervals
        
        if(mode == EXACT){                                                                              //checks if conversion was exact
            bool foundEqual;                            
            std::vector<Point<Number>> newVertices = _target.vertices();                                //gets vertices from the just newly created box
            for (const auto& newVertex : newVertices){                                                  //for every new vertex (from the box)
                foundEqual = _source.hasVertex(newVertex);                                              //checks if source-object contains the new vertex                                                   
                if (foundEqual == false){                                                               //if no equal vertex was found, the target object has to be an overapproximation
                    return false;
                }
            }
        } 
        
	return true;
}

//conversion from H-Polytope to box
//TODO alternative approach with evaluating the 2d main directions + how exactly works vertices()?
template <typename Number>
static bool convert( const hypro::HPolytope<Number>& _source, hypro::Box<Number>& _target, const CONV_MODE mode ) {
	typename VPolytope<Number>::pointVector vertices = _source.vertices();                          //gets vertices as a vector from the source object (is actually a conversion from H-Polytope to V-Polytope)
	assert( !vertices.empty() );                                                                    //only continue if any actual vertices were received at all
	vector_t<Number> minima = vertices->begin().rawCoordinates();                                   //creates a vector_t with the first vertex of the source object
	vector_t<Number> maxima = vertices->begin().rawCoordinates();                                   //creates another vector_t with the first vertex of the source object

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

	_target = Box<Number>( intervals );                                                             //creates a box with the computed intervals
        
        if(mode == EXACT){                                                                              //checks if conversion was exact
            bool foundEqual;                            
            std::vector<Point<Number>> newVertices = _target.vertices();                                //gets vertices from the just newly created box
            for (const auto& newVertex : newVertices){                                                  //for every new vertex (from the box)
                foundEqual = _source.hasVertex(newVertex);                                              //checks if source-object contains the new vertex
                if (foundEqual == false){                                                               //if no equal vertex was found, the target object has to be an overapproximation
                    return false;
                }
            }
        } 
        
        return true;
}

//TODO validation
template <typename Number>
static bool convert( const hypro::Zonotope<Number>& _source, hypro::Box<Number>& _target, const CONV_MODE mode ) {
	Zonotope<Number> tmp = _source.intervalHull();
	std::vector<vector_t<Number>> vertices = tmp.computeZonotopeBoundary();
	assert( !vertices.empty() );
	vector_t<Number> minima = vertices[0];
	vector_t<Number> maxima = vertices[0];

	for ( std::size_t i = 0; i < vertices.size(); ++i ) {
		for ( std::size_t d = 0; d < _source.dimension(); ++d ) {
			minima( d ) = vertices[i]( d ) < minima( d ) ? vertices[i]( d ) : minima( d );
			maxima( d ) = vertices[i]( d ) > maxima( d ) ? vertices[i]( d ) : maxima( d );
			assert( minima( d ) <= maxima( d ) );
		}
	}

	std::vector<carl::Interval<Number>> intervals;
	for ( std::size_t i = 0; i < _source.dimension(); ++i ) {
		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );
	}

	_target = Box<Number>( intervals );

	return false;  // Todo: if precise, return true
}

//conversion from Polytope to box (different data structure)
template <typename Number>
static bool convert( const hypro::Polytope<Number>& _source, hypro::Box<Number>& _target, const CONV_MODE mode ) {
	std::vector<Point<Number>> points = _source.vertices();                                                                         //gets vertices as a vector from the source object
	assert( !points.empty() );                                                                                                      //only continue if any actual vertices were received at all

	vector_t<Number> minima = points[0].rawCoordinates();                                                                           //creates a vector_t with the first vertex of the source object
	vector_t<Number> maxima = points[0].rawCoordinates();                                                                           //creates another vector_t with the first vertex of the source object

	for ( std::size_t i = 0; i < points.size(); ++i ) {                                                                             //for each vertex of the source object
		for ( std::size_t d = 0; d < _source.dimension(); ++d ) {                                                               //for every dimension
			minima( d ) = points[i].rawCoordinates()( d ) < minima( d ) ? points[i].rawCoordinates()( d ) : minima( d );    //if the value at position d in the vector is smaller than the minimum value to this point, it becomes the new minimum value.
			maxima( d ) = points[i].rawCoordinates()( d ) > maxima( d ) ? points[i].rawCoordinates()( d ) : maxima( d );    //if the value at position d in the vector is greater than the maximum value to this point, it becomes the new maximum value.
			assert( minima( d ) <= maxima( d ) );                                                                           //only continue if the maximum value is not smaller than the minimum value
		}
	}

	std::vector<carl::Interval<Number>> intervals;
	for ( std::size_t i = 0; i < _source.dimension(); ++i ) {                                                                       //for every dimension 
		intervals.push_back( carl::Interval<Number>( minima( i ), maxima( i ) ) );                                              //create one interval per dimension with the corresponding minimal and maximal values
	}

	_target = Box<Number>( intervals );                                                                                             //creates a box with the computed intervals
        
        if(mode == EXACT){                                                                                                              //checks if conversion was exact
            bool foundEqual;                            
            std::vector<Point<Number>> newVertices = _target.vertices();                                                                //gets vertices from the just newly created box
            for (const auto& newVertex : newVertices){                                                                                  //for every new vertex (from the box)
                foundEqual = false;                                                                     
                for (const auto& oldVertex : points){                                                                                   //checks if source-object contains the new vertex
                    if (newVertex == oldVertex){
                        foundEqual = true;
                    }
                }
                if (foundEqual == false){                                                                                               //if no equal vertex was found, the target object has to be an overapproximation
                    return false;
                }
            }
        } 

	return true;    
}
    
} //namespace