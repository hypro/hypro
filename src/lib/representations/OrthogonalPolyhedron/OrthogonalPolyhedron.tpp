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
        if (!mBoxUpToDate) {
            updateBoundaryBox();
        }
        
        int nrofVertices = pow(2, dimension());
        VertexContainer<Number> container;
        Vertex<Number> vertex;
        
        for (int vertexNr = 0; vertexNr < nrofVertices; vertexNr++) {
            int i = 0;
            for (auto variableIt : mVariables) {
                // look if the bit of the current dimension is set
                if ((vertexNr >> i++) & 1) {
                    vertex[variableIt] = mBoundaryBox.interval(variableIt).upper();
                } else {
                    vertex[variableIt] = mBoundaryBox.interval(variableIt).lower();
                }
            }
            vertex.setColor(vertexNr == 0);
            container.insert(vertex);
        }
        result = OrthogonalPolyhedron<Number>(container);
        
        return true;
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
    
    /**
     * Returns and if necessary calculates the boundary box.
     */
    template<typename Number>
    Box<Number> OrthogonalPolyhedron<Number>::boundaryBox() {
        if (!mBoxUpToDate) {
            updateBoundaryBox();
        }
        return mBoundaryBox;
    }
        

    /***************************************************************************
     * Private methods
     ***************************************************************************/
    
    /**
     * Updates the boundary box
     */
    template<typename Number>
    void OrthogonalPolyhedron<Number>::updateBoundaryBox() {
        // If there are no vertices, the box is empty
        if (mVertices.empty()) {
            mBoundaryBox.clear();
        }
        
        vSetIt<Number> it = mVertices.begin();
        
        // Set the box to include the first vertex, so nothing goes wrong.
        // (Before, we should make sure there is a first one)
        for (auto dimensionIt : mVariables) {
            mBoundaryBox.insert(dimensionIt, typename Box<Number>::floatInterval(it->at(dimensionIt), it->at(dimensionIt)));
        }
        
        // Extend the box
        for (auto dimensionIt : mVariables) {
            for (; it != mVertices.end(); ++it) {
                auto interval = mBoundaryBox.interval(dimensionIt);
                auto val = it->at(dimensionIt);
                if (val > interval.upper()) {
                    interval.setUpper(val);
                } else if (val < interval.lower()) {
                    interval.setLower(val);
                }
            }
        }
        
        mBoxUpToDate = true;
    }
}
