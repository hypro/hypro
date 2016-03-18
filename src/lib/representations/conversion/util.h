/**
 * Contains utilities for conversion functions. (Mainly underapproximation)
 * @file util.h
 * @author Simon Froitzheim
 *
 * @since	2016-03-17
 * @version	2016-03-17
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Hyperplane.h"
#include "../SupportFunction/SupportFunction.h"

//TODO implement kickoff-function

namespace hypro{

template <typename Number, typename Converter>
std::vector<Point<Number>> computeBoundaryPoints (const SupportFunctionT<Number,Converter>& sf, const matrix_t<Number>& directions, const unsigned curDim) {
    //determines how many directions need to be checked
    unsigned numberOfDirections = directions.rows();
    //gets dimension in which is currently computed
    unsigned dim = directions.cols();
    //only continue if directions and object match dimensionwise
    assert (dim == sf.dimension());
    //generates an empty PointVector for the return value
    std::vector<Point<Number>> res = std::vector<Point<Number>>(numberOfDirections);
    //if the function has an object that is not yet certainly a singleton (i.e. dimension is greater than zero)
    if (curDim > 0){
        //generates an empty vector of a PointVector for the return values of the recursive calls
        std::vector<std::vector<Point<Number>>> recursiveSolutions = std::vector<std::vector<Point<Number>>>(numberOfDirections)(numberOfDirections);
        for(unsigned i=0; i<numberOfDirections; ++i){
            //determines current evaluation direction
            vector_t<Number> curNormal = directions.row(i);
            
            //lets the support function evaluate the offset of the halfspace for the current direction
            evaluationResult<Number> offset = sf.evaluate(curNormal);
            //if result is infinity, try the next direction
            if(offset.errorCode == SOLUTION::INFTY){
                continue;
            }
            Number constant = offset.supportValue;
            //creates the current halfspace
            Hyperplane<Number> curPlane = Hyperplane<Number>(curNormal, constant);
            
            //creates a hyperplanevector containing only the recently created hyperplane
            std::vector<Hyperplane<Number>> curPlaneVector = std::vector<Hyperplane<Number>>(1);
            curPlaneVector[0] = curPlane;
            
            //intersects the current support function with the hyperplane
            SupportFunctionT<Number,Converter> curFace = sf.intersect(SupportFunctionT<Number, Converter>(curPlaneVector));
            //only continue if face has still the same dimension as the source object (although it is technically now a dim-1 object at most)
            assert(curFace.dimension() == dim);
            
            //TODO implement this method
            //matrix_t newDirections = computeOrthogonalDirections(curNormal);
            
            //recursive call of this function for the current face
            //recursiveSolutions[i] = computeBoundaryPoints(face, newDirections, curDim-1);
            
            //removes duplicate points in order to enable the arithmetic mean to yield best possible results
            //recursiveSolutions[i] = removeDuplicatePoints(recursiveSolutions[i]);
            
            //TODO implement this method
            //res(i) = computeArithmeticMean(recursiveSolutions(i));
            }
        return res;
   } else {
        //TODO implement this method
        //return sf.toPoint();
   }    
}    
    

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
} // namespace
