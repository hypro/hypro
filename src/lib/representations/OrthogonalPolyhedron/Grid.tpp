/** 
 * @file    Grid.tpp
 * @author  Benedikt Seidl
 *
 * @since   2014-04-14
 * @version 2014-04-14
 */

#include "Grid.h"


namespace hypro
{
    template<typename Number>
    void Grid<Number>::reserveInducedGrid(const std::vector<carl::Variable>& variables)
    {
        std::vector<Number > v;
        for (auto it : variables) {
            mVariables.push_back(it);
            mInducedGridPoints.insert(std::make_pair(it, v));
        }
    }
    
    template<typename Number>
    void Grid<Number>::insertVerticesInMap(const vSet<Number>& vertices)
    {
        for (auto it : vertices) {
            this->insert(it.rPoint(), it.color());
        }
    }
    
    template<typename Number>
    void Grid<Number>::induceGrid(const vSet<Number>& vertices)
    {
        for (auto it : mInducedGridPoints) {
            // insert origin as vertex
            it.second.push_back(Number(0));
            
            // Projection of all points to the axes.
            for (auto vertex : vertices) {
                assert( vertex.hasDimensions(mVariables));
                it.second.push_back(vertex.coordinate(it.first));
            }
            
            // Sort every dimension, erase duplicate entries.
            std::sort(it.second.begin(), it.second.end());
            auto itr = std::unique(it.second.begin(), it.second.end());
            it.second.resize(itr - it.second.begin());
            mInducedGridPoints[it.first] = it.second;
        }

        clear();
    }
    
    template<typename Number>
    Point<Number> Grid<Number>::nextPointOnGrid(const Point<Number>& x) const
    {
        typename Point<Number>::coordinateMap coordinates;
        
        for (auto inducedGridPointsIt : mInducedGridPoints) {

            auto fixed = inducedGridPointsIt.first;
            auto inducedGridPoints = inducedGridPointsIt.second;

            // get the position of the first element greater then the coordinate + 1
            auto it = std::upper_bound(inducedGridPoints.begin(), inducedGridPoints.end(),
                    x.coordinate(fixed));

            // insert the element one before the element found above
            coordinates.insert(std::make_pair(fixed,
                    inducedGridPoints.at(it - inducedGridPoints.begin() - 1)));
        }
        
        Point<Number> induced(coordinates);
        return induced;
    }
    
    template<typename Number>
    Point<int> Grid<Number>::calculateInduced(const Point<Number>& point) const
    {
        Point<int>::coordinateMap coordinates;
        for (auto inducedGridPointsIt : mInducedGridPoints) {
            auto fixed = inducedGridPointsIt.first;
            auto inducedGridPoints = inducedGridPointsIt.second;

            // get the position of the first element greater then the coordinate + 1
            auto it = std::upper_bound(inducedGridPoints.begin(), inducedGridPoints.end(),
                    point.coordinate(fixed));

            // insert the index of the element one before the element found above
            coordinates.insert(std::make_pair(fixed, it - 1 - inducedGridPoints.begin()) );
        }
        
        Point<int> induced(coordinates);
        return induced;
    }
    
    template<typename Number>
    Point<Number> Grid<Number>::calculateOriginal(const Point<int>& inducedPoint) const
    {
        typename Point<Number>::coordinateMap coordinates;
        for (auto coordinateIt : inducedPoint.coordinates()) {
            auto fixed = coordinateIt.first;
            auto inducedGridPoints = mInducedGridPoints.at(fixed);
            // get the value of the element at the specified position
            auto it = inducedGridPoints.at(coordinateIt.second);
            
            // insert the value
            coordinates.insert(std::make_pair(fixed, it));
        }
        
        Point<Number> induced(coordinates);
        return induced;
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