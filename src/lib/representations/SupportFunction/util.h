/* 
 * @file   util.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	February 24, 2015
 * @version	February 24, 2015
 */

#pragma once

namespace hypro {
	/*
    * This structure describes the result of a support function evaluation
    */
	template<typename Number>
    struct evaluationResult {
    	Number supportValue;	// the value returned by the support function evaluation
    	vector_t<Number> optimumValue;	// the point leading to the support function value (extremum in direction)
    	int errorCode; 	// potential error code indicating success or failure of the evaluation
    
        /*  Potential error codes are:
            
         *  General:
         *  -1000  in case the support function object does not implement a proper evaluate function   
            
         *  For polytopes:
                
         *  GLP_OPT
         *  GLP_FEAS
         *  GLP_INFEAS
         *  GLP_NOFEAS
         *  GLP_UNBND
         *  GLP_UNDEF
         
         * For NonLinear:  // TODO: add error status
         */
    };
}