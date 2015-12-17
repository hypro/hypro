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

    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::HPolytope<Number>& _target ){
        _target = _source;
        return true;        
    }
    //TODO
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::HPolytope<Number>& _target ){
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::HPolytope<Number>& _target ){
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::HPolytope<Number>& _target ){
        return true;
    } 

}  // namespace


