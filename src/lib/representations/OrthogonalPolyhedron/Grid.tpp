/**
 * @file    Grid.tpp
 * @author 	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2015-08-26
 */

#include "Grid.h"


namespace hypro
{

	/*
	*	Constructors
	*/

	template<typename Number>
	Grid<Number>::Grid() {}

	template<typename Number>
	Grid<Number>::Grid(const vSet<Number>& vertices) :
		mVertices()
	{
		induceGrid(vertices);
	}

	template<typename Number>
	Grid<Number>::Grid(const std::vector<Vertex<Number>>& _vertices) :
		mVertices()
	{
		induceGrid(vSet<Number>(_vertices.begin(), _vertices.end()));
	}

	template<typename Number>
	Grid<Number>::Grid(const Grid<Number>& copy) :
		mVertices(copy.mVertices),
		mGridMap(copy.mGridMap),
		mInducedGridPoints(copy.mInducedGridPoints)
	{}

	/*
	*	Getter & Setter
	*/

	template<typename Number>
	unsigned Grid<Number>::size() const {
		return mGridMap.size();
	}

	template<typename Number>
	unsigned Grid<Number>::dimension() const {
		return mInducedGridPoints.size();
	}

	template<typename Number>
	std::vector<carl::Variable> Grid<Number>::variables() const {
		std::vector<carl::Variable> res;
		if(mGridMap.empty())
			return res;

		res = mGridMap.begin()->first.variables();
		return std::move(res);
	}

	template<typename Number>
	std::vector<Vertex<Number>> Grid<Number>::vertices() const {
		std::vector<Vertex<Number>> res;
		for(const auto& point : mVertices) {
			std::cout << "Calculated vertex " << calculateOriginal(point.point()) << " from " << point.point() << std::endl;
			if(point.point() != Point<int>::zero(point.point().dimension())) { // do not add origin 
				res.emplace_back(calculateOriginal(point.point()), point.color());

			}
		}
		return std::move(res);
	}

	template<typename Number>
	bool Grid<Number>::empty() const {
		return mGridMap.empty();
	}

	template<typename Number>
	bool Grid<Number>::colorAt(const Point<Number>& point) const {
		Point<int> inducedPoint = calculateInduced(point);
		// the point is not a vertex (vertices are inserted at the beginning) and not yet calculated.
		if(mGridMap.find(inducedPoint) != mGridMap.end())
			return mGridMap.at(inducedPoint);

		return colorAtInduced(inducedPoint);
	}

	template<typename Number>
	bool Grid<Number>::colorAtInduced(const Point<unsigned>& inducedPoint) const {
		std::cout << __func__ << " " << inducedPoint << std::endl;
		// the point is not a vertex (vertices are inserted at the beginning) and not yet calculated.
		if(mGridMap.find(inducedPoint) != mGridMap.end())
			return mGridMap.at(inducedPoint);

		/* calculate color recursively:
		 * - go through all directions j: There exists j such that for all j-neighbors(x) (except x itself) it holds: 
		 * 		color(j-pred(jneigh)) == color(j-neigh)
		 * 		-> color(x) = color(j-pred(j-neigh))
		 */

		unsigned dim = dimension();
		bool colorDirection = true;
		bool color = false;
		for(unsigned j = 0; j < dim; ++j) {
			std::cout << "Evaluate "<< inducedPoint <<" in direction " << j << std::endl;
			colorDirection = true;
			std::vector<Point<unsigned>> jneighs = iNeighborhoodInduced(inducedPoint,j);
			for(const auto& p : jneighs) {
				std::cout << j << "-Neighbor: " << p << std::endl; 
			}
			for(const auto& x : jneighs) {
				if(x != inducedPoint) {
					std::cout << "Get color at " << x << std::endl;
					color = colorAtInduced(x);
					if(colorAtInduced(x) != colorAtInduced(iPredecessorInduced(x,j))) {
						colorDirection = false;
						break;
					}
				}
			}
			if(colorDirection){
				mGridMap[inducedPoint] = color;
				break;
			}
		}
		return color;
	}

	template<typename Number>
	std::vector<Point<unsigned>> Grid<Number>::iNeighborhoodInduced(const Point<unsigned>& _inducedPoint, unsigned _dimension) const {
		std::cout << __func__ << " " << _inducedPoint << " " << _dimension << std::endl;
		assert(_dimension < mInducedGridPoints.size());
		std::vector<Point<unsigned>> result;

		unsigned d = this->dimension();
		Point<unsigned> directPredecessor(_inducedPoint);
		std::cout << "Direct predecessor before: " << directPredecessor << std::endl;
		for(unsigned dim = 0; dim < d; ++dim) {
			if(_inducedPoint.at(dim) > 0)
				directPredecessor[dim] = (_inducedPoint.at(dim))-1;
		}
		std::cout << "Direct predecessor: " << directPredecessor << std::endl;

		std::vector<std::vector<unsigned>> possibleCoords;
		for(unsigned j = 0; j < d; ++j) {
			if(_dimension != j) {
				std::vector<unsigned> tmp({directPredecessor.at(j), _inducedPoint.at(j)});
				possibleCoords.emplace_back(std::move(tmp));
			} else {
				std::vector<unsigned> tmp({_inducedPoint.at(j)});
				possibleCoords.emplace_back(std::move(tmp));
			}
		}
		pointIt<unsigned> pIt(possibleCoords);

		while(!pIt.end){
			result.emplace_back(std::move(++pIt));
		}
		return std::move(result);
	}

	template<typename Number>
	Point<unsigned> Grid<Number>::iPredecessorInduced(const Point<unsigned>& _point, unsigned _dimension) const {
		Point<unsigned> res(_point);
		res[_dimension] = res[_dimension] > 0 ? res[_dimension] - 1 : 0;
		return std::move(res);
	}

	template<typename Number>
	Point<Number> Grid<Number>::iPredecessor(const Point<Number>& _point, unsigned _dimension) const {
		return calculateOriginal(iPredecessorInduced(_point,_dimension));
	}

	template<typename Number>
	std::vector<Point<unsigned>> Grid<Number>::iSliceInduced(unsigned i, int pos) const {
		std::vector<Point<unsigned>> result;

		std::vector<std::vector<unsigned>> tmp;
		for(unsigned j = 0; j < mInducedGridPoints.size(); ++j) {
			if(i != j) {
				tmp.emplace_back(std::vector<unsigned>({i}));
			} else {
				std::vector<unsigned> positions;
				positions.resize(mInducedGridPoints.at(j).size());
				for(unsigned k = 0; k < mInducedGridPoints.at(j).size(); ++k)
					positions.emplace_back(k);

				tmp.emplace_back(std::move(positions));
			}
		}
		pointIt<unsigned> pIt(tmp);

		while(!pIt.end){
			result.emplace_back(std::move(++pIt));
		}
		return std::move(result);
	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::iSlice(unsigned i, Number pos) const {
		unsigned inducedPos = 0;
		while (mInducedGridPoints.at(i)[inducedPos] < pos) ++inducedPos;

		if(inducedPos > 0)
			--inducedPos;

		std::vector<Point<unsigned>> tmp = iSliceInduced(i,inducedPos);
		std::vector<Point<Number>> res;
		for(const auto& p : tmp)
			res.emplace_back(calculateOriginal(p));

		return std::move(res);
	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::iNeighborhood(const Point<Number>& _point, unsigned _dimension) const {
		std::vector<Point<unsigned>> neighborhood = iNeighborhoodInduced(calculateInduced(_point),_dimension);
		std::vector<Point<Number>> res;
		for(const auto& n : neighborhood)
			res.emplace_back(calculateOriginal(n));

		return std::move(res);
	}

	template<typename Number>
	std::vector<Point<unsigned>> Grid<Number>::neighborhoodInduced(const Point<unsigned>& _inducedPoint) const {
		std::vector<Point<unsigned>> result;
		unsigned d = this->dimension();

		// calculate direct predecessor point in all dimensions
		Point<unsigned> directPredecessor(_inducedPoint);
		for(unsigned dim = 0; dim < d; ++dim) {
			directPredecessor[dim] = _inducedPoint.at(dim) > 0 ? _inducedPoint.at(dim)-1 : 0;
		}

		// get all 2^d i-neighbors by combination of the point and its direct predecessor
		for(unsigned i = 0; i < std::pow(2,d); ++i) {
			std::bitset<MAX_DIMENSION_LIMIT> map(i);
			unsigned pos = 0;
			Point<unsigned> neighbor(directPredecessor);
			while(pos < d) {
				if(map.test(pos))
					neighbor[pos] = _inducedPoint.at(pos);
				++pos;
			}
			result.emplace_back(std::move(neighbor));
		}

		return std::move(result);
	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::neighborhood(const Point<Number>& _point) const {
		std::vector<Point<unsigned>> tmp = neighborhoodInduced(calculateInduced(_point));
		std::vector<Point<Number>> res;
		for(const auto& p : tmp)
			res.emplace_back(calculateOriginal(p));

		return std::move(res);
	}

	template<typename Number>
	bool Grid<Number>::isVertex(const Point<Number>& _point) const {
		for(const auto& vertex : mVertices) {
			if(calculateOriginal(vertex.point()) == _point)
				return true;
		}
		return false;
	}

	template<typename Number>
	bool Grid<Number>::isOnIFacet(const Point<Number>& _point, unsigned i) const {
		// either the point is a vertex or there is a color change in its i-neighborhood -> color change is easier to check
		Point<unsigned> inducedPoint = calculateInduced(_point);
		std::vector<Point<unsigned>> iNeighborhood = iNeighborhoodInduced(_point,i);
		for(const auto& x : iNeighborhood){
			if(colorAtInduced(x) != colorAtInduced(iPredecessorInduced(x,i)))
				return true;
		}
		return false;
	}

	template<typename Number>
	void Grid<Number>::insert(const Point<Number>& point, bool color) {
		mGridMap.insert(std::make_pair(calculateInduced(point), color));
	}

	template<typename Number>
	void Grid<Number>::insertInduced(const Point<unsigned>& inducedPoint, bool color) {
		mGridMap.insert(std::make_pair(inducedPoint, color));
	}

	template<typename Number>
	void Grid<Number>::clear() {
		mGridMap.clear();
	}

	template<typename Number>
	typename Grid<Number>::gridMap::const_iterator Grid<Number>::find(const Point<Number>& point) const {
		return mGridMap.find(calculateInduced(point));
	}

	template<typename Number>
	typename Grid<Number>::gridMap::const_iterator Grid<Number>::findInduced(const Point<unsigned>& inducedPoint) const {
		return mGridMap.find(inducedPoint);
	}

	template<typename Number>
	typename Grid<Number>::gridMap::const_iterator Grid<Number>::end() const {
		return mGridMap.end();
	}

	template<typename Number>
	void Grid<Number>::induceGrid(const vSet<Number>& vertices)
	{
		clear();

		std::vector<Number> v;
		v.resize(vertices.size()+1); // we add the origin
		for (unsigned i = 0; i != vertices.begin()->dimension(); ++i) {
			// insert origin as vertex
			v = std::vector<Number>({Number(0)});

			// Projection of all points to the axes.
			for (auto& vertex : vertices) {
				v.push_back(vertex.coordinate(i));
			}

			// Sort every dimension, erase duplicate entries.
			std::sort(v.begin(), v.end());
			auto itr = std::unique(v.begin(), v.end());
			v.resize(itr - v.begin());

			mInducedGridPoints[i] = v;
		}

		// set color of origin manually (always white)
		this->insertInduced(Point<unsigned>::zero(mInducedGridPoints.size()), false);

		// set up datastructures for colors of vertices and vertices
		for (auto it : vertices) {
			this->insert(it.rPoint(), it.color());
			mVertices.insert(Vertex<int>(calculateInduced(it.point()),it.color()));
			std::cout << "Added induced Vertex " <<  Vertex<int>(calculateInduced(it.point()),it.color()) << std::endl;
		}

		std::cout << "Grid " << *this << std::endl;
	}

	template<typename Number>
	Point<unsigned> Grid<Number>::calculateInduced(const Point<Number>& point) const
	{
		vector_t<unsigned> coordinates(mInducedGridPoints.size());
		for (auto inducedGridPointsIt : mInducedGridPoints) {
			unsigned fixedDimension = inducedGridPointsIt.first;
			std::vector<Number> inducedGridPoints = inducedGridPointsIt.second;

			// get the position of the first element greater than the coordinate + 1
			unsigned pos = 0;
			while(pos < inducedGridPoints.size() && inducedGridPoints[pos] <= point.at(fixedDimension)) ++pos;

			// insert the index of the element one before the element found above
			coordinates[fixedDimension] = pos - 1;
		}

		std::cout << "Point " << point << " induces " << Point<unsigned>(coordinates) << std::endl;

		return std::move(Point<unsigned>(coordinates)); // return induced point
	}

	template<typename Number>
	Point<Number> Grid<Number>::calculateOriginal(const Point<unsigned>& inducedPoint) const
	{
		vector_t<Number> coordinates(mInducedGridPoints.size());
		for (auto inducedGridPointsIt : mInducedGridPoints) {
			unsigned fixed = inducedGridPointsIt.first;
			std::vector<Number> inducedGridPoints = inducedGridPointsIt.second;

			// get the value of the element at the specified position
			int induced = inducedPoint.at(fixed);

			coordinates[fixed] = inducedGridPoints.at(induced);
		}

		return Point<Number> (coordinates); // return original point
	}

	template<typename Number>
	vSet<unsigned> Grid<Number>::translateToInduced(const vSet<Number>& vertices) const
	{
		vSet<unsigned> induced;
		for (auto it : vertices) {
			Vertex<unsigned> v = calculateInduced(it.point());
			v.setColor(it.color());
			induced.insert(v);
		}
		return induced;
	}

	template<typename Number>
	vSet<Number> Grid<Number>::translateToOriginal(const vSet<unsigned>& inducedVertices) const
	{
		vSet<Number> original;
		for (auto it : inducedVertices) {
			Vertex<Number> v = calculateOriginal(it.point());
			v.setColor(it.color());
			original.insert(v);
		}
		return original;
	}

}
