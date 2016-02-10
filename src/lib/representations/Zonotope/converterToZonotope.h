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
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER  );
    
    /**
     * @brief Converts a polytope in H-representation into a Zonotope.
     * 
     *   
     * @param _source H-polytope that needs to be converted.
     * @param _target An arbitrary Zonotope that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER  );
    
    /**
     * @brief Converts a box into a Zonotope.
     * @detail Computes the corresponding generator for every dimension by simply computing the length of each box interval (divided by 2)
     * and center of the box by addition of the interval end points (also divided by 2).
     *   
     * @param _source Box that needs to be converted.
     * @param _target An arbitrary Zonotope that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation). Note that this function will always convert exactly.
     * @return Return value is true if the requested conversion was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode = CONV_MODE::EXACT  );
    
    /**
     * @brief Converts a V-Polytope into a zonotope.
     * 
     *   
     * @param _source V-Polytope that needs to be converted.
     * @param _target An arbitrary zonotope that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER  );   
    
    /**
     * @brief Converts a support function into a zonotope.
     * 
     *   
     * @param _source Support function that needs to be converted.
     * @param _target An arbitrary zonotope that gets overwritten with the converted object.
     * @param mode The requested conversion mode (exact conversion or overapproximation).
     * @return Return value is true if the requested conversion was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::SupportFunction<Number>& _source, hypro::Zonotope<Number>& _target, const CONV_MODE mode = CONV_MODE::OVER  );   

}  // namespace

#include "converterToZonotope.tpp"

