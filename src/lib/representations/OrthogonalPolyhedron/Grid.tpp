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
		mVertices(vertices)
	{
		induceGrid(vertices);
	}

	template<typename Number>
	Grid<Number>::Grid(const std::vector<Vertex<Number>>& _vertices) :
		mVertices(vSet<Number>(_vertices.begin(), _vertices.end()))
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
		for(const auto& point : mGridMap) {
			res.emplace_back(calculateOriginal(point.first), point.second);
		}
		return std::move(res);
	}

	template<typename Number>
	bool Grid<Number>::empty() const {
		return mGridMap.empty();
	}

	template<typename Number>
	bool Grid<Number>::colorAt(const Point<Number>& point) const {
		Point Number> inducedPoint = calculateInduced(point);
		// the point is not a vertex (vertices are inserted at the beginning) and not yet calculated.
		if(mGridMap.find(inducedPoint) != mGridMap.end())
			return mGridMap.at(inducedPoint);

		return colorAtInduced(inducedPoint);
	}

	template<typename Number>
	bool Grid<Number>::colorAtInduced(const Point<int>& inducedPoint) const {
		// the point is not a vertex (vertices are inserted at the beginning) and not yet calculated.
		if(mGridMap.find(inducedPoint) != mGridMap.end())
			return mGridMap.at(inducedPoint);

		// calculate color recursively

	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::iNeighborhoodInduced(const Point<Number>& _inducedPoint, unsigned _dimension) const {
		assert(_dimension < mInducedGridPoints.size());
		std::vector<Point<Number>> result;

		unsigned d = this->dimension();
		Point<Number> directPredecessor = std::move(Point<Number>::zero(d));
		for(unsigned dim = 0; dim < d; ++dim) {
			unsigned p = 0;
			while(mInducedGridPoints.at(dim).at(p) < _inducedPoint.at(dim)) ++p;

			if (p > 0)
				directPredecessor[dim] = mInducedGridPoints.at(dim).at(p-1);
		}

		std::vector<std::vector<Number>> possibleCoords;
		for(unsigned j = 0; j < d; ++j) {
			if(_dimension != j) {
				possibleCoords.insert(possibleCoords.back(), std::move(std::vector<Number>({directPredecessor.at(j), _inducedPoint.at(j)})));
			} else {
				possibleCoords.emplace_back(std::move(std::vector<Number>({_inducedPoint.at(j)})));
			}
		}
		pointIt<Number> pIt(possibleCoords);

		while(!pIt.end){
			result.emplace_back(std::move(++pIt));
		}
		return std::move(result);
	}

	template<typename Number>
	Point<Number> Grid<Number>::iPredecessor(const Point<Number>& _point, unsigned _dimension) const {
		return std::move(iNeighborInduced(_point,_dimension));
	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::iSliceInduced(unsigned i, Number pos) const {
		std::vector<Point<Number>> result;

		std::vector<std::vector<Number>> tmp;
		for(unsigned j = 0; j < mInducedGridPoints.size(); ++j) {
			if(i != j) {
				tmp.emplace_back(mInducedGridPoints.at(j));
			} else {
				tmp.emplace_back(std::move(std::vector<Number>({pos})));
			}
		}
		pointIt<Number> pIt(tmp);

		while(!pIt.end){
			result.emplace_back(std::move(++pIt));
		}
		return std::move(result);
	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::iNeighborhood(const Point<Number>& _inducedPoint, unsigned _dimension) const {
		std::vector<Point<Number>> result;
		result.emplace_back(iNeighborhoodInduced(_inducedPoint,_dimension));
		return std::move(result);
	}

	template<typename Number>
	std::vector<Point<Number>> Grid<Number>::neighborhoodInduced(const Point<Number>& _inducedPoint) const {
		std::vector<Point<Number>> result;
		unsigned d = this->dimension();

		// calculate direct predecessor point in all dimensions
		Point<Number> directPredecessor = std::move(Point<Number>::zero(d));
		for(unsigned dim = 0; dim < d; ++dim) {
			unsigned p = 0;
			while(mInducedGridPoints.at(dim).at(p) < _inducedPoint.at(dim)) ++p;

			if (p > 0)
				directPredecessor[dim] = mInducedGridPoints.at(dim).at(p-1);
		}

		// get all 2^d i-neighbors by combination of the point and its direct predecessor
		for(unsigned i = 0; i < std::pow(2,d); ++i) {
			std::bitset<MAX_DIMENSION_LIMIT> map(i);
			unsigned pos = 0;
			Point<Number> neighbor(directPredecessor);
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
	bool Grid<Number>::isVertex(const Point<Number>& _point) const {

	}

	template<typename Number>
	bool Grid<Number>::isOnIEdge(const Point<Number>& _point, unsigned i) const {

	}

	template<typename Number>
	void Grid<Number>::insert(const Point<Number>& point, bool color) {
		mGridMap.insert(std::make_pair(calculateInduced(point), color));
	}

	template<typename Number>
	void Grid<Number>::insertInduced(const Point<int>& inducedPoint, bool color) {
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
	typename Grid<Number>::gridMap::const_iterator Grid<Number>::findInduced(const Point<int>& inducedPoint) const {
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

        for (auto it : vertices) {
            this->insert(it.rPoint(), it.color());
        }
    }

    template<typename Number>
    Point<int> Grid<Number>::calculateInduced(const Point<Number>& point) const
    {
        vector_t<int> coordinates(mInducedGridPoints.size());
        for (auto inducedGridPointsIt : mInducedGridPoints) {
            unsigned fixed = inducedGridPointsIt.first;
            std::vector<Number> inducedGridPoints = inducedGridPointsIt.second;

            // get the position of the first element greater than the coordinate + 1
            auto pos = std::upper_bound(inducedGridPoints.begin(), inducedGridPoints.end(),
                    point.coordinate(fixed));

            // insert the index of the element one before the element found above
            coordinates[fixed] = pos - 1 - inducedGridPoints.begin();
        }

        return Point<int>(coordinates); // return induced point
    }

    template<typename Number>
    Point<Number> Grid<Number>::calculateOriginal(const Point<int>& inducedPoint) const
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
    vSet<int> Grid<Number>::translateToInduced(const vSet<Number>& vertices) const
    {
        vSet<int> induced;
        for (auto it : vertices) {
            Vertex<int> v = calculateInduced(it.point());
            v.setColor(it.color());
            induced.insert(v);
        }
        return induced;
    }

    template<typename Number>
    vSet<Number> Grid<Number>::translateToOriginal(const vSet<int>& inducedVertices) const
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
