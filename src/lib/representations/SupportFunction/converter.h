/**
 * Specialization for a converter to a support function.
 * @file converter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2015-05-13
 * @version	2015-05-13
 */

#pragma once

namespace hypro {
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, SupportFunction<Number>& _target );
    
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, SupportFunction<Number>& _target );
    
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, SupportFunction<Number>& _target );
    
        
}  // namespace

#include "converter.tpp"