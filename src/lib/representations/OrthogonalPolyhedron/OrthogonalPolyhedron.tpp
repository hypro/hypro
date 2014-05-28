/** 
 * @file    OrthogonalPolyhedron.tpp
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-05-28
 */

#include "OrthogonalPolyhedron.h"


namespace hypro
{

    

    /***************************************************************************
     * Public methods
     ***************************************************************************/
        
    /**********************************
     * Geometric Object functions
     **********************************/
    
    template<typename Number>
    unsigned int OrthogonalPolyhedron<Number>::dimension() {
        return mVertices.dimension();
    }	
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::linearTransformation(OrthogonalPolyhedron<Number>& result) {
        return false;
    }

    template<typename Number>
    bool OrthogonalPolyhedron<Number>::minkowskiSum(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) {
        return false;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::intersect(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) {
        return false;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::hull(OrthogonalPolyhedron<Number>& result) {
        return false;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::contains(const Point<Number>& point) {
        return false;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::unite(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) {
        return false;
    }
        
    /**********************************
     * Other functions
     **********************************/
    
    /**
     * Returns it the polyhedron is empty.
     * 
     * @return true if number of vertices equals 0.
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::empty() const {
        return mVertices.empty();
    }
    
    /**
     * Returns the list of variables of this polyhedron
     */
    template<typename Number>
    std::vector<carl::Variable> OrthogonalPolyhedron<Number>::variables() const {
        return mVariables;
    }
    
}
