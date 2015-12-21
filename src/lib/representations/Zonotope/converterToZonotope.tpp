/**
 * Specialization for a converter to a zonotope.
 * @file converterToZonotope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "converterToZonotope.h"

namespace hypro {

    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::Zonotope<Number>& _target ){
        _target = _source;
        return true;        
    }
    //TODO
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::Zonotope<Number>& _target ){
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::Zonotope<Number>& _target ){
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::Zonotope<Number>& _target ){
        return true;
    } 

}  // namespace

