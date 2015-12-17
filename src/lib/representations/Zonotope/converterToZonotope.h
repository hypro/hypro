/**
 * Specialization for a converter to a Zonotope.
 * @file converterToZonotope.h
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#pragma once

namespace hypro {
    /**
     * @brief Converts a Zonotope into another Zonotope.
     * @detail Simply overwrites _target with _source.
     *   
     * @param _source Zonotope that needs to be converted.
     * @param _target An arbitrary Zonotope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::Zonotope<Number>& _target );
    
    /**
     * @brief Converts a polytope in H-representation into a Zonotope.
     * 
     *   
     * @param _source H-polytope that needs to be converted.
     * @param _target An arbitrary Zonotope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::Zonotope<Number>& _target );
    
    /**
     * @brief Converts a box into a Zonotope.
     * 
     *   
     * @param _source Box that needs to be converted.
     * @param _target An arbitrary Zonotope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::Zonotope<Number>& _target );
    
    /**
     * @brief Converts a V-Polytope into a zonotope.
     * 
     *   
     * @param _source V-Polytope that needs to be converted.
     * @param _target An arbitrary zonotope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::Zonotope<Number>& _target );   

}  // namespace

#include "converterToZonotope.tpp"

