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
    unsigned int OrthogonalPolyhedron<Number>::dimension() const {
        return mVertices.dimension();
    }	
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::linearTransformation(OrthogonalPolyhedron<Number>& result) const {
        return false;
    }

    template<typename Number>
    bool OrthogonalPolyhedron<Number>::minkowskiSum(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const {
        return false;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::intersect(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const {
        assert(mVariables == rhs.mVariables);
        
        // first initialize the set of potential vertices
        vSet<Number> potentialVertices;
        for (auto vertexIt1 : mVertices.vertices()) {
            for (auto vertexIt2 : rhs.mVertices.vertices()) {
                Point<Number> max = Point<Number>::coordinateMax(vertexIt1, vertexIt2);
                potentialVertices.insert(max);
            }
        }
        
        // create a temporary grid including all potential vertices
        Grid<Number> tmpGrid;
        tmpGrid.reserveInducedGrid(mVariables);
        tmpGrid.induceGrid(potentialVertices);
        potentialVertices = tmpGrid.translateToInduced(potentialVertices);
        
        // the container to store the actual vertices
        VertexContainer<Number> vertices;
        
        // check all potential vertices if they are in fact vertices
        for (auto vertexIt : potentialVertices) {
            // calculate the neighbour colouring intersection
            auto neighbours = vertexIt.getAllNeighbours(true); // include the point itself
            std::map<Point<Number>, bool> colouringIntersection;
            for (auto neighbourIt : neighbours) {
                Point<Number> original = tmpGrid.calculateOriginal(neighbourIt);
                bool colour1 = contains(original);
                bool colour2 = rhs.contains(original);
                colouringIntersection.insert(std::make_pair(neighbourIt, colour1 && colour2));
            }
            
            bool isVertex = true, pointExists;
            
            // check the vertex condition: ∀i ∈ {1, . . . , d}. ∃x' ∈ N i(x). c(x'i−) 6= c(x').
            for (auto dimensionIt : mVariables) {
                auto neighboursInFixed = vertexIt.getAllNeighborsForAFixedDimension(dimensionIt, true); // include the point itself
                pointExists = false;
                for (auto neighbourIt : neighboursInFixed) {
                    Point<Number> predecessor = neighbourIt.getPredecessorInDimension(dimensionIt);
                    if (colouringIntersection.at(neighbourIt) != colouringIntersection.at(predecessor)) {
                        pointExists = true;
                        break;
                    }
                }
                
                if (!pointExists) {
                    isVertex = false;
                    break;
                }
            }
            
            // if the point is a vertex, add it with its calculated colour
            if (isVertex) {
                vertices.insert(tmpGrid.calculateOriginal(vertexIt), colouringIntersection.at(vertexIt));
            }
        }

        result = OrthogonalPolyhedron<Number>(vertices);
        
        return true;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::hull(OrthogonalPolyhedron<Number>& result) const {
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
    bool OrthogonalPolyhedron<Number>::contains(const Point<Number>& point) const {
        return containsInduced(mGrid.calculateInduced(point));
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::unite(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const {
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
    Box<Number> OrthogonalPolyhedron<Number>::boundaryBox() const {
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
    void OrthogonalPolyhedron<Number>::updateBoundaryBox() const {
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
            for (it = mVertices.begin()++; it != mVertices.end(); ++it) {
                auto interval = mBoundaryBox.pInterval(dimensionIt);
                auto val = it->at(dimensionIt);
                if (val > interval->upper()) {
                    interval->setUpper(val);
                } else if (val < interval->lower()) {
                    interval->setLower(val);
                }
            }
        }
        
        mBoxUpToDate = true;
    }
        
    /**
     * Checks if the orthogonal polyhedron contains the given induced point.
     * Using only the induced point makes calculating neighbourship and predecessors much easier.
     * 
     * @param inducedPoint
     * @return 
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::containsInduced(const Point<Number>& inducedPoint) const {
        // check if we already know the colour of this point
        auto it = mGrid.findInduced(inducedPoint);
        if (it != mGrid.end()) {
            return it->second;
        }
        
        bool colour = false;

        // check if the point is in our boundary box
        if (boundaryBox().contains(mGrid.calculateOriginal(inducedPoint))) {
            // there exists a dimension
            for (auto dimensionIt : mVariables) {
                auto neighboursInFixed = inducedPoint.getAllNeighborsForAFixedDimension(dimensionIt);
                bool dimensionOk = true;
                
                // for all neighbours we must ensure
                for (auto neighbourIt : neighboursInFixed) {
                    Point<Number> predecessor = neighbourIt.getPredecessorInDimension(dimensionIt);
                    if (containsInduced(neighbourIt) != containsInduced(predecessor)) {
                        dimensionOk = false;
                        break;
                    }
                }
                
                // if the dimension is ok the point's colour is the same as its predecessor
                if (dimensionOk) {
                    Point<Number> predecessor = inducedPoint.getPredecessorInDimension(dimensionIt);
                    colour = containsInduced(predecessor);
                    break;
                }
            }
        }
        
        // save calculated colour for later use
        mGrid.insertInduced(inducedPoint, colour);
        return colour;
    }
    
}
