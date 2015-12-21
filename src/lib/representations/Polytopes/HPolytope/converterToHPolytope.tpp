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
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::HPolytope<Number>& _target ){
        _target = _source;
        return true;        
    }
    
    //conversion from V-Polytope to H-Polytope
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::HPolytope<Number>& _target ){
        _target = HPolytope<Number>(_source);                                                    //converts the source object into an H-polytope via constructor
        return true;
    }
    
    //conversion from Box to H-Polytope
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::HPolytope<Number>& _target ){
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
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::HPolytope<Number>& _target ){
        return true;
    } 

}  // namespace


