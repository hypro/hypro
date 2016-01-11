/**
 * Specialization for a converter to a support function.
 * @file converterToSupportFunction.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-13
 * @version	2015-12-16
 */

#pragma once

namespace hypro {
    /**
     * @brief Converts a support function into another support function.
     * @detail Simply overwrites _target with _source.
     *   
     * @param _source Support function that needs to be converted.
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */   
    template <typename Number>
    static bool convert( const hypro::SupportFunction<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER);
    
    /**
     * @brief Converts a box into a support function.
     * @detail Constructs a fixed normal matrix and reads distances from the box intervals.
     *   
     * @param _source Box that needs to be converted.
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */   
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER );
    
    /**
     * @brief Converts a polytope in V-representation into a support function.
     * 
     * @detail Converts the source object into an H-Polytope first with the corresponding constructor, then reads out halfplanes and passes them on to the target object.
     * 
     * @param _source V-polytope that needs to be converted.
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */   
    
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER );
    
    
    /**
     * @brief Converts a polytope in H-representation into a support function
     * @detail Simply gets halfplanes from source object and passes them on to the target object.
     *
     * @param _source H-polytope that needs to be converted
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */  
    
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER );
    
    /**
     * @brief Converts a zonotope into a support function
     * 
     *
     * @param _source Zonotope that needs to be converted
     * @param _target An arbitrary support function that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */  
    
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::SupportFunction<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER );
    
        
}  // namespace

#include "converterToSupportFunction.tpp"