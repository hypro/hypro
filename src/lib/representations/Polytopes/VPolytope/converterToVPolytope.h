/**
 * Specialization for a converter to a V-polytope.
 * @file converterToVPolytope.h
 * @author Simon Froitzheim
 *
 * @since	2015-12-17
 * @version	2015-12-17
 */

#pragma once

namespace hypro {
    /**
     * @brief Converts a V-Polytope into another V-Polytope.
     * @detail Simply overwrites _target with _source.
     *   
     * @param _source V-Polytope that needs to be converted.
     * @param _target An arbitrary V-Polytope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::VPolytope<Number>& _target );
    
    /**
     * @brief Converts a polytope in H-representation into a V-Polytope.
     * 
     *   
     * @param _source H-polytope that needs to be converted.
     * @param _target An arbitrary V-Polytope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::VPolytope<Number>& _target );
    
    /**
     * @brief Converts a box into a V-Polytope.
     * 
     *   
     * @param _source Box that needs to be converted.
     * @param _target An arbitrary V-Polytope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::VPolytope<Number>& _target );
    
    /**
     * @brief Converts a zonotope into a V-Polytope.
     * 
     *   
     * @param _source Zonotope that needs to be converted.
     * @param _target An arbitrary V-Polytope that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::VPolytope<Number>& _target );   

}  // namespace

#include "converterToVPolytope.tpp"

