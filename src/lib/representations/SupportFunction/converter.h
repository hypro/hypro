/**
 * Specialization for a converter to a support function.
 * @file converter.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-13
 * @version	2015-05-13
 */

#pragma once

namespace hypro {
    /**
     * @brief Converts a box into a support function.
     * @detail Constructs a fixed normal matrix and reads distances from the box intervals.
     *   
     * @param _source Box that needs to be converted.
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */   
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, const hypro::SupportFunction<Number>& _target );
    
    /**
     * @brief Converts a polytope in V-representation into a support function.
     * 
     * @detail Converts the source object into an H-Polytope first with the corresponding constructor, then reads out halfplanes and passes them on to the target object.
     * 
     * @param _source V-polytope that needs to be converted.
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */   
    
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, const hypro::SupportFunction<Number>& _target );
    
    
    /**
     * @brief Converts a polytope in H-representation into a support function
     * @detail Simply gets halfplanes from source object and passes them on to the target object.
     *
     * @param _source H-polytope that needs to be converted
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, const hypro::SupportFunction<Number>& _target );
    
    /**
     * @brief Converts a zonotope into a support function
     * 
     *
     * @param _source Zonotope that needs to be converted
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, const hypro::SupportFunction<Number>& _target );
    
        
}  // namespace

#include "converter.tpp"