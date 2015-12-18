/**
 * Specialization for a converter to a box.
 * @file converterToBox.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author Simon Froitzheim
 *
 * @since	2015-05-12
 * @version	2015-12-16
 */

#pragma once

namespace hypro {
    /**
     * @brief Converts a box into another box.
     * @detail Simply overwrites _target with _source.
     *   
     * @param _source Box that needs to be converted.
     * @param _target An arbitrary box that gets overwritten with the converted object.
     * @return Return value is true if a direct conversion was made, false in case of an overapproximation. (It is possible that although a direct conversion was requested, only an overapproximation could be performed.)
     */  
    template <typename Number>
    static bool convert( const hypro::Box<Number>& _source, hypro::Box<Number>& _target );
    
    /**
     * @brief Converts a support function into a box.
     * 
     *   
     * @param _source Support Function that needs to be converted.
     * @param _target An arbitrary box that gets overwritten with the converted object.
     * @return Return value is true if a direct conversion was made, false in case of an overapproximation. (It is possible that although a direct conversion was requested, only an overapproximation could be performed.)
     */  
    template <typename Number>
    static bool convert( const hypro::SupportFunction<Number>& _source, hypro::Box<Number>& _target );
    
    /**
     * @brief Converts a polytope in V-representation into a box. (overapproximation in the general case)
     * @detail Computes the minimal and maximal point component for every dimension and sets up intervals ranging from the corresponding minimal value to the corresponding maximal value for every dimension.
     *   
     * @param _source V-polytope that needs to be converted.
     * @param _target An arbitrary box that gets overwritten with the converted object.
     * @return Return value is true if a direct conversion was made, false in case of an overapproximation. (It is possible that although a direct conversion was requested, only an overapproximation could be performed.)
     */  
    template <typename Number>
    static bool convert( const hypro::VPolytope<Number>& _source, hypro::Box<Number>& _target );
    
    /**
     * @brief Converts a polytope in H-representation into a box.
     * 
     *   
     * @param _source H-polytope that needs to be converted.
     * @param _target An arbitrary box that gets overwritten with the converted object.
     * @return Return value is true if a direct conversion was made, false in case of an overapproximation. (It is possible that although a direct conversion was requested, only an overapproximation could be performed.)
     */  
    template <typename Number>
    static bool convert( const hypro::HPolytope<Number>& _source, hypro::Box<Number>& _target );
    
    /**
     * @brief Converts a zonotope into a box.
     * 
     *   
     * @param _source Zonotope that needs to be converted.
     * @param _target An arbitrary box that gets overwritten with the converted object.
     * @return Return value is true if the conversion process was successful.
     */  
    template <typename Number>
    static bool convert( const hypro::Zonotope<Number>& _source, hypro::Box<Number>& _target );
    
    /**
     * @brief Converts a polytope into a box.
     * 
     *   
     * @param _source Polytope that needs to be converted.
     * @param _target An arbitrary box that gets overwritten with the converted object.
     * @return Return value is true if a direct conversion was made, false in case of an overapproximation. (It is possible that although a direct conversion was requested, only an overapproximation could be performed.)
     */  
    template <typename Number>
    static bool convert( const hypro::Polytope<Number>& _source, hypro::Box<Number>& _target );
    
    

}  // namespace

#include "converterToBox.tpp"