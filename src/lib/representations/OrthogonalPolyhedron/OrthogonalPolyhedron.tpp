/**
 * @file    OrthogonalPolyhedron.tpp
 * @author  Sebastian Junges
 * @author	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 *
 * @since   2014-03-17
 * @version 2015-07-09
 */


namespace hypro
{
	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron() :
		mGrid(),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron(const Vertex<Number>& _vertex) :
		mGrid(),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{
		mGrid.insert(_vertex.point(), _vertex.color());
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron(const VertexContainer<Number>& _vertices) :
		mGrid(_vertices.vertices()),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron(const std::set<Vertex<Number>>& _vertices) :
		mGrid(_vertices),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron(const std::vector<Vertex<Number>>& _vertices) :
		mGrid(_vertices),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type>& copy) :
		mGrid(copy.vertices()),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type>::OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type>&& move) :
		mGrid(std::move(move.mGrid)),
		mBoundaryBox(),
		mBoxUpToDate(false)
	{}

	/**********************************
	 * Getter & setter
	 **********************************/

	/**
	 * Returns the list of variables of this polyhedron
	 */
	template<typename Number, ORTHO_TYPE Type>
	std::vector<carl::Variable> OrthogonalPolyhedron<Number, Type>::variables() const {
		return mGrid.variables();
	}

	template<typename Number, ORTHO_TYPE Type>
	std::vector<Vertex<Number>> OrthogonalPolyhedron<Number, Type>::vertices() const {
		return mGrid.vertices();
	}

	/**
	 * Returns and if necessary calculates the boundary box.
	 */
	template<typename Number, ORTHO_TYPE Type>
	Box<Number> OrthogonalPolyhedron<Number, Type>::boundaryBox() const {
		if (!mBoxUpToDate) {
			updateBoundaryBox();
		}
		return mBoundaryBox;
	}

	template<typename Number, ORTHO_TYPE Type>
	void OrthogonalPolyhedron<Number, Type>::addVertex(const Vertex<Number>& _vertex){
		mGrid.insert(_vertex);
	}

	template<typename Number, ORTHO_TYPE Type>
	void OrthogonalPolyhedron<Number, Type>::addVertices(const std::vector<Vertex<Number>>& _vertices){
		for(const auto& vertex : _vertices)
			mGrid.insert(vertex);
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::empty() const {
		return mGrid.empty();
	}

	template<typename Number, ORTHO_TYPE Type>
	unsigned OrthogonalPolyhedron<Number, Type>::size() const {
		return mGrid.size();
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::isVertex(const Point<Number>& _point) const {
		for(unsigned dimension : this->dimension()) {
			if(!isOnIEdge(_point, dimension))
				return false;
		}
		return true;
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::isOnIEdge(const Point<Number>& _point, unsigned i) const {
		std::vector<Point<Number>> iNeighbors = mGrid.iNeighborhood(_point,i);
		for(const auto& neighbor : iNeighbors) {
			if(mGrid.colorAt(neighbor) != mGrid.colorAt(mGrid.iPredecessor(neighbor,i))) return true;
		}
		return false;
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::isInternal(const Point<Number>& _point) const {
		return (mGrid.colorAt(_point) == true);
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::isExternal(const Point<Number>& _point) const {
		return !isInternal(_point);
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::color(const Point<Number>& _point) const {
		return mGrid.colorAt(_point);
	}

	template<typename Number, ORTHO_TYPE Type>
	std::vector<Point<Number>> OrthogonalPolyhedron<Number, Type>::iNeighborhood(const Point<Number>& _point, unsigned i) const {
		return mGrid.iNeighborhood(_point,i);
	}

	template<typename Number, ORTHO_TYPE Type>
	std::vector<Point<Number>> OrthogonalPolyhedron<Number, Type>::iNegNeighborhood(const Point<Number>& _point, unsigned i) const {
		return mGrid.iNeighborhood(mGrid.iPredecessor(_point,i),i);
	}

	template<typename Number, ORTHO_TYPE Type>
	std::vector<Point<Number>> OrthogonalPolyhedron<Number, Type>::neighborhood(const Point<Number>& _point) const {
		return std::move(mGrid.neighborhood(_point));
	}

	template<typename Number, ORTHO_TYPE Type>
	std::vector<Point<Number>> OrthogonalPolyhedron<Number, Type>::iSlice(unsigned i, Number pos) const {
		// TODO: ATTENTION, this is the induced version, transform!
		return std::move(mGrid.iSlice(i,pos));
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number,Type> OrthogonalPolyhedron<Number, Type>::iProjection(unsigned i) const {
		// TODO: Required for dimension reduction and more sophisticated containment methods.
	}


	/**********************************
	 * Geometric Object functions
	 **********************************/

	template<typename Number, ORTHO_TYPE Type>
	unsigned int OrthogonalPolyhedron<Number, Type>::dimension() const {
		return mGrid.dimension();
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type> OrthogonalPolyhedron<Number, Type>::linearTransformation(const matrix_t<Number>& A, const vector_t<Number>& b) const {
		/*
		VertexContainer<Number> newVertices(mVertices);
		newVertices.linearTransformation(A, b);
		OrthogonalPolyhedron<Number, Type> result = OrthogonalPolyhedron<Number, Type>(newVertices);
		// TODO: undefined behavior, does not update colors of vertices nor fix the non-parallel edges
		return result;
		*/
		OrthogonalPolyhedron<Number, Type> result;
		return result;
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type> OrthogonalPolyhedron<Number, Type>::minkowskiSum(const OrthogonalPolyhedron<Number, Type>& rhs) const {
		// TODO
		// Definition: A+B = { a + b | a ∈ A, b ∈ B}
		// Idea: put one polyhedron on all the vertices of the other one
		// Problem: Which vertices to connect, which to remove?
		// Thoughts: do two vertices belong to former neighbors?
		//           store the "color" of a moved polyhedron
		OrthogonalPolyhedron<Number, Type> result;
		return result;
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type> OrthogonalPolyhedron<Number, Type>::intersect(const OrthogonalPolyhedron<Number, Type>& rhs) const {
		std::vector<Vertex<Number>> potentialVertices;
		std::vector<Vertex<Number>> v1 = this->vertices();
		std::vector<Vertex<Number>> v2 = rhs.vertices();
		std::vector<Vertex<Number>> vertices;

		// potential vertices are all original vertices and their pairwise componentwise-max.
		potentialVertices.insert(potentialVertices.end(), v1.begin(), v1.end());
		potentialVertices.insert(potentialVertices.end(), v2.begin(), v2.end());
		for(const auto& vA : v1) {
			for(const auto& vB : v2) {
				potentialVertices.emplace_back(Point<Number>::coordinateMax(vA.point(),vB.point()));
			}
		}

		// determine 'real' vertices out of candidates
		for(auto pIt = potentialVertices.begin(); pIt != potentialVertices.end(); ++pIt) {
			std::vector<Point<Number>> aNeighbors = this->neighborhood(pIt->point());
			std::vector<Point<Number>> bNeighbors = rhs.neighborhood(pIt->point());

			Vertex<Number> newVertex(*pIt);
			unsigned parity = 0;
			for(const auto& nA : aNeighbors) {
				// skip this point, if the color is white -> white is dominating
				if(mGrid.colorAt(nA)){
					for(const auto& nB : bNeighbors) {
						// map the vertices onto each other by comparing their offset pattern ( which is 1 on every dimension the neighbor varies from the point)
						if( Point<Number>::lesserDimensionPattern(nA, (*pIt).point()) == Point<Number>::lesserDimensionPattern(nB, (*pIt).point()) ) {
							// if both are black, the neighbor would be black too -> increase parity
							if(rhs.color(nB))
								++parity;
							break;
						}
					}
				}
			}

			// the potential vertex is a real vertex, if the parity is odd.
			if(parity % 2 != 0) {
				// determine color by determining color in both polytopes, white dominates
				newVertex.setColor(this->color(pIt->point()) && rhs.color(pIt->point()));
				vertices.push_back(newVertex);
			}
		}
		
		return (OrthogonalPolyhedron<Number, Type>(std::move(vertices)));
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type> OrthogonalPolyhedron<Number, Type>::hull() const {
		if (!mBoxUpToDate) {
			updateBoundaryBox();
		}

		int nrofVertices = pow(2, dimension());
		VertexContainer<Number> container;
		Vertex<Number> vertex;

		for (int vertexNr = 0; vertexNr < nrofVertices; vertexNr++) {
			int i = 0;
			for (auto variableIt : mGrid.variables()) {
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
		OrthogonalPolyhedron<Number, Type> result = OrthogonalPolyhedron<Number, Type>(container);

		return result;
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::contains(const Point<Number>& point) const {
		return mGrid.colorAt(point);
	}

	template<typename Number, ORTHO_TYPE Type>
	bool OrthogonalPolyhedron<Number, Type>::contains(const OrthogonalPolyhedron<Number,Type>& _other) const {
		for(const auto& vertex : _other.vertices()) {
			if(!contains(vertex.point()))
				return false;
		}
		return true;
	}

	template<typename Number, ORTHO_TYPE Type>
	OrthogonalPolyhedron<Number, Type> OrthogonalPolyhedron<Number, Type>::unite(const OrthogonalPolyhedron<Number, Type>& rhs) const {
		std::vector<Vertex<Number>> vertices;

		std::vector<Vertex<Number>> v1 = this->vertices();
		std::vector<Vertex<Number>> v2 = rhs.vertices();

		// create union by determining color in both polyhedra. TODO

		return std::move(OrthogonalPolyhedron<Number, Type>(vertices));
	}

	/**********************************
	 * Other functions
	 **********************************/

	template<typename Number, ORTHO_TYPE Type>
	std::vector<std::vector<Point<Number>>> OrthogonalPolyhedron<Number, Type>::preparePlot(unsigned _xDim, unsigned _yDim) const {
		std::vector<std::vector<Point<Number>>> result;

		std::vector<Point<Number>> points = mGrid.allBlack();

		// add points
		for(auto point : points){
			point.reduceToDimensions(std::vector<unsigned>({_xDim,_yDim}));
			Point<Number> lowerRight = mGrid.iSuccessor(point,0);
			lowerRight.reduceToDimensions(std::vector<unsigned>({_xDim,_yDim}));
			Point<Number> upperRight = mGrid.directSuccessor(point);
			upperRight.reduceToDimensions(std::vector<unsigned>({_xDim,_yDim}));
			Point<Number> upperLeft = mGrid.iSuccessor(point,1);
			upperLeft.reduceToDimensions(std::vector<unsigned>({_xDim,_yDim}));

			//std::cout << "point " << point << " corresponds to box " << point << " , " << lowerRight << " , " << upperRight << " , " << upperLeft << std::endl;
			result.emplace_back(std::vector<Point<Number>>({point, lowerRight, upperRight, upperLeft }));
		}

		return result;
	}

	/***************************************************************************
	 * Private methods
	 ***************************************************************************/

	/**
	 * Updates the boundary box
	 */
	template<typename Number, ORTHO_TYPE Type>
	void OrthogonalPolyhedron<Number, Type>::updateBoundaryBox() const {
		// If there are no vertices, the box is empty
		if (mGrid.empty()) {
			mBoundaryBox.clear();
		}

		std::vector<Vertex<Number>> vertices = mGrid.vertices();
		mBoundaryBox = Box<Number>(vertices);

		mBoxUpToDate = true;
	}
}
