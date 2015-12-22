/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.tpp
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#include "converterToVPolytope.h"

namespace hypro {

    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::VPolytope<Number>& _target, const CONV_MODE mode ){
        _target = _source;
        return true;        
    }
    //TODO
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::VPolytope<Number>& _target, const CONV_MODE mode ){
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::VPolytope<Number>& _target, const CONV_MODE mode ){
        return true;
    }
    
    //TODO
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::VPolytope<Number>& _target, const CONV_MODE mode ){
        return true;
    } 

}  // namespace



