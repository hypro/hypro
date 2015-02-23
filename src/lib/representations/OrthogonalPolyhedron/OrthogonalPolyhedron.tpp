/** 
 * @file    OrthogonalPolyhedron.tpp
 * @author  Sebastian Junges
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2014-05-28
 */


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
    bool OrthogonalPolyhedron<Number>::linearTransformation(OrthogonalPolyhedron<Number>& result, const matrix_t<Number>& A, const vector_t<Number>& b) const {
    	VertexContainer<Number> newVertices(mVertices);
    	newVertices.linearTransformation(A, b);
    	result = OrthogonalPolyhedron<Number>(newVertices);
    	// TODO: undefined behavior, does not update colors of vertices nor fix the non-parallel edges
    	return false;
    }

    template<typename Number>
    bool OrthogonalPolyhedron<Number>::minkowskiSum(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const {
    	// TODO
    	// Definition: A+B = { a + b | a ∈ A, b ∈ B}
    	// Idea: put one polyhedron on all the vertices of the other one
    	// Problem: Which vertices to connect, which to remove?
    	// Thoughts: do two vertices belong to former neighbors?
    	//           store the "color" of a moved polyhedron
        return false;
    }
        
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::intersect(OrthogonalPolyhedron<Number>& result, const OrthogonalPolyhedron<Number>& rhs) const {
        assert(mVariables == rhs.mVariables);
        
        // first initialize the set of potential vertices
        vSet<Number> potentialVertices;
        calculatePotentialVertices(potentialVertices, mVertices.vertices(), rhs.mVertices.vertices());
        
        // create a temporary grid including all potential vertices
        Grid<Number> tmpGrid(potentialVertices);
        vSet<int> inducedPotentialVertices = tmpGrid.translateToInduced(potentialVertices);
        
        // the container to store the actual vertices
        VertexContainer<Number> vertices;
        typename NeighborhoodContainer::neighborhood neighbors;
        std::map<Point<int>, bool> coloringIntersection;
        
        // check all potential vertices if they are in fact vertices
        for (auto vertexIt : inducedPotentialVertices) {
            // calculate the neighbor coloring intersection
            neighbors = mNeighborhood.getNeighborhood(vertexIt.point(), true); // include the point itself
            coloringIntersection.clear();

            for (auto neighborIt : neighbors) {
                Point<Number> original = tmpGrid.calculateOriginal(neighborIt);
                bool color1 = this->contains(original);
                bool color2 = rhs.contains(original);
                coloringIntersection.insert(std::make_pair(neighborIt, color1 && color2));
            }
            
            // if the point is a vertex, add it with its calculated color
            if (checkVertexCondition(vertexIt, coloringIntersection)) {
                vertices.insert(tmpGrid.calculateOriginal(vertexIt.point()), coloringIntersection.at(vertexIt.point()));
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
        assert(mVariables == rhs.mVariables);
        
        // first initialize the set of potential vertices
        vSet<Number> potentialVertices;
        calculatePotentialVertices(potentialVertices, mVertices.vertices(), rhs.mVertices.vertices());
        for (auto vertexIt : this->mVertices.vertices()) {
            if ( !rhs.contains(vertexIt.point()) ) {
                potentialVertices.insert(vertexIt.point());
            }
        }
        for (auto vertexIt : rhs.mVertices.vertices()) {
            if ( !this->contains(vertexIt.point()) ) {
                potentialVertices.insert(vertexIt.point());
            }
        }
        
        // create a temporary grid including all potential vertices
        Grid<Number> tmpGrid(potentialVertices);
        vSet<int> inducedPotentialVertices = tmpGrid.translateToInduced(potentialVertices);
        
        // the container to store the actual vertices
        VertexContainer<Number> vertices;
        typename NeighborhoodContainer::neighborhood neighbors;
        std::map<Point<int>, bool> coloringUnion;
        
        // check all potential vertices if they are in fact vertices
        for (auto vertexIt : inducedPotentialVertices) {
            // calculate the neighbor coloring intersection
            neighbors = mNeighborhood.getNeighborhood(vertexIt.point(), true); // include the point itself
            coloringUnion.clear();

            for (auto neighborIt : neighbors) {
                Point<Number> original = tmpGrid.calculateOriginal(neighborIt);
                bool color1 = this->contains(original);
                bool color2 = rhs.contains(original);
                coloringUnion.insert(std::make_pair(neighborIt, color1 || color2));
            }
            
            // if the point is a vertex, add it with its calculated color
            if (checkVertexCondition(vertexIt, coloringUnion)) {
                vertices.insert(tmpGrid.calculateOriginal(vertexIt.point()), coloringUnion.at(vertexIt.point()));
            }
        }

        result = OrthogonalPolyhedron<Number>(vertices);
        
        return true;
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
     * Using only the induced point makes calculating neighborship and predecessors much easier.
     * 
     * @param inducedPoint
     * @return 
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::containsInduced(const Point<int>& inducedPoint) const {
        // check if we already know the color of this point
        auto it = mGrid.findInduced(inducedPoint);
        if (it != mGrid.end()) {
            return it->second;
        }
        
        bool color = false;

        // check if the point is in our boundary box
        if (boundaryBox().contains(mGrid.calculateOriginal(inducedPoint))) {
            // there exists a dimension
            for (auto dimensionIt : mVariables) {
                auto neighborsInFixed = mNeighborhood.getNeighborhoodForDimension(inducedPoint, dimensionIt);
                bool dimensionOk = true;
                
                // for all neighbors we must ensure
                for (auto neighborIt : neighborsInFixed) {
                    Point<Number> predecessor = neighborIt.getPredecessorInDimension(dimensionIt);
                    if (containsInduced(neighborIt) != containsInduced(predecessor)) {
                        dimensionOk = false;
                        break;
                    }
                }
                
                // if the dimension is ok the point's color is the same as its predecessor
                if (dimensionOk) {
                    Point<Number> predecessor = inducedPoint.getPredecessorInDimension(dimensionIt);
                    color = containsInduced(predecessor);
                    break;
                }
            }
        }
        
        // save calculated color for later use
        mGrid.insertInduced(inducedPoint, color);
        return color;
    }

    /**
     * Calculate all potential vertices by combining two sets of vertices.
     * 
     * @see intersect
     * @see unite
     * 
     * @param potentialVertices
     * @param vertices1
     * @param vertices2
     */
    template<typename Number>
    void OrthogonalPolyhedron<Number>::calculatePotentialVertices(vSet<Number>& potentialVertices, const vSet<Number>& vertices1, const vSet<Number>& vertices2) const {
        for (auto vertexIt1 : vertices1) {
            for (auto vertexIt2 : vertices2) {
                Point<Number> max = Point<Number>::coordinateMax(vertexIt1.point(), vertexIt2.point());
                potentialVertices.insert(max);
            }
        }   
    }
    
    /**
     * Checks if the given point is a vertex based on the vertex condition.
     * ∀i ∈ {1, . . . , d}. ∃x' ∈ N i(x). c(x'i−) 6= c(x').
     * 
     * @param vertex
     * @param coloring
     * @return bool
     */
    template<typename Number>
    bool OrthogonalPolyhedron<Number>::checkVertexCondition(const Vertex<int>& vertex, const std::map<Point<int>, bool>& coloring) const {
        bool pointExists;
        
//        for (auto dimensionIt : vertex.variables()) {
        for (unsigned i = 0; i != vertex.dimension(); ++i) {
			carl::Variable var = hypro::VariablePool::getInstance().carlVarByIndex(i);
            auto neighborsInFixed = mNeighborhood.getNeighborhoodForDimension(vertex.point(), var, true); // include the point itself
            pointExists = false;
            for (auto neighborIt : neighborsInFixed) {
                Point<Number> predecessor = neighborIt.getPredecessorInDimension(var);
                if (coloring.at(neighborIt) != coloring.at(predecessor)) {
                    pointExists = true;
                    break;
                }
            }

            if (!pointExists) {
                return false;
            }
        }
        
        return true;
    }
    
}
