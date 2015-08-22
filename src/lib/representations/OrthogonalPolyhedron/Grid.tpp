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

            // get the position of the first element greater then the coordinate + 1
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