/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * @file    Grid.h
 * @author 	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 * @author  Benedikt Seidl
 */

#pragma once

#include "../../datastructures/Point.h"
#include "../../datastructures/Vertex.h"
#include "../../types.h"

#include <bitset>
#include <map>
#include <vector>

namespace hypro {

/**
 * @brief      Struct holding a point iterator allowing to iterate over a vector of points represented by their coordinates.
 *
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    struct pointIt {
        typename std::vector<std::vector<Number>> v;
        std::vector<typename std::vector<Number>::const_iterator> it;
        bool end = false;

        pointIt(const std::vector<std::vector<Number>> &_v)
                : v(_v) {
            for (std::size_t i = 0; i < v.size(); ++i) it.push_back(v.at(i).begin());

            end = false;
        }

        // prefix
        Point<Number> operator++() {
            if (end) return std::move(current());
            ++it.back();
            std::size_t i = it.size() - 1;
            while (it.at(i) == v.at(i).end()) {
                it[i] = v.at(i).begin();
                if (i == 0) {
                    end = true;
                    return std::move(current());
                }
                --i;
                it[i]++;
            }
            return current();
        }

        // postfix
        Point<Number> operator++(int) { return ++(*this); }

        Point<Number> current() {
            assert(v.size() == it.size());
            Point<Number> res(vector_t<Number>::Zero(v.size()));
            for (std::size_t i = 0; i < v.size(); ++i) res[i] = *it.at(i);

            return res;
        }
    };

/**
 * @brief      Class for a grid which maps points to their assigned color.
 *
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    class Grid {
    public:
        using gridMap = std::map<Point<std::size_t>, bool>;     // store calculated colors
        using gridPoints = std::map<std::size_t, std::vector<Number>>;
        using gridMapIterator = gridMap::iterator;
        using gridPointsIterator = typename gridPoints::iterator;

    private:
        std::set<Vertex<std::size_t>> mVertices;
        mutable gridMap mGridMap;  // is mutable to allow storing of intermediate results
        mutable gridPoints mInducedGridPoints;

    public:
        /**
         * Constructor
         */
        Grid();

        Grid(const vSet<Number> &vertices);

        Grid(const std::vector<Vertex<Number>> &_vertices);

        Grid(const Grid<Number> &copy);

        Grid<Number> &operator=(const Grid<Number> &) = default;

        Grid<Number> &operator=(Grid<Number> &&) = default;

        /**
         * Returns the size ie. the number of points saved in this grid.
         *
         * @return
         */
        std::size_t size() const;

        std::size_t dimension() const;

        std::vector<carl::Variable> variables() const;

        std::vector<Vertex<Number>> vertices() const;

        std::vector<Number> inducedDimensionAt(std::size_t dimension) const;

        bool empty() const;

        /**
         * Returns the color of the given point.
         *
         * @param point
         * @return the color of the point
         */
        bool colorAt(const Point<Number> &point) const;

        bool colorAtInduced(const Point<std::size_t> &inducedPoint) const;

        std::vector<Point<Number>> allBlack() const;

        void colorAll() const;

        Point<std::size_t> iPredecessorInduced(const Point<std::size_t> &_point, std::size_t _dimension) const;

        Point<Number> iPredecessor(const Point<Number> &_point, std::size_t _dimension) const;

        Point<std::size_t> iSuccessorInduced(const Point<std::size_t> &_point, std::size_t _dimension) const;

        Point<Number> iSuccessor(const Point<Number> &_point, std::size_t _dimension) const;

        Point<std::size_t> directPredecessorInduced(const Point<std::size_t> &_point) const;

        Point<Number> directPredecessor(const Point<Number> &_point) const;

        Point<std::size_t> directSuccessorInduced(const Point<std::size_t> &_point) const;

        Point<Number> directSuccessor(const Point<Number> &_point) const;

        std::vector<Point<std::size_t>> iSliceInduced(std::size_t i) const;

        std::vector<Point<Number>> iSlice(std::size_t i, Number pos) const;

        std::vector<Point<std::size_t>> iNeighborhoodInduced(const Point<std::size_t> &_inducedPoint,
                                                             std::size_t _dimension) const;

        std::vector<Point<Number>> iNeighborhood(const Point<Number> &_point, std::size_t _dimension) const;

        std::vector<Point<std::size_t>> neighborhoodInduced(const Point<std::size_t> &_inducedPoint) const;

        std::vector<Point<Number>> neighborhood(const Point<Number> &_point) const;

        bool isVertex(const Point<Number> &_point) const;

        bool isOnIFacet(const Point<Number> &_point, std::size_t i) const;

        bool isOnFacet(const Point<Number> &_point) const;

        bool isOutside(const Point<Number> &_point) const;

        /**
         * Inserts the value for the point.
         *
         * @param point
         * @param color
         */
        void insert(const Point<Number> &point, bool color);

        void insertInduced(const Point<std::size_t> &inducedPoint, bool color);

        void addCoordinate(Number value, std::size_t dimension);

        static Grid<Number> combine(const Grid<Number> &a, const Grid<Number> &b);

        void clear();

        typename gridMap::const_iterator find(const Point<Number> &point) const;

        typename gridMap::const_iterator findInduced(const Point<std::size_t> &inducedPoint) const;

        typename gridMap::const_iterator end() const;

        /**
         * Clears the grid, induces it and sets up the vertices.
         *
         * @param vertices
         */
        void induceGrid(const vSet<Number> &vertices);

        /**
         * Calculates the coordinates of this point on the induced grid.
         *
         * @param point
         * @return induced point
         */
        std::pair<Point<std::size_t>, bool> calculateInduced(const Point<Number> &point) const;

        /**
         * Calculates the original coordinates of this induced point.
         * @param inducedPoint
         * @return original point
         */
        Point<Number> calculateOriginal(const Point<std::size_t> &inducedPoint) const;

        /**
         * Translates the points to induced points.
         *
         * @param vertices
         * @return induced vertices
         */
        vSet<std::size_t> translateToInduced(const vSet<Number> &vertices) const;

        /**
         * Translates the induced points to original points.
         *
         * @param inducedVertices
         * @return original vertices
         */
        vSet<Number> translateToOriginal(const vSet<std::size_t> &inducedVertices) const;

        friend bool operator==(const Grid<Number> &op1, const Grid<Number> &op2) {
            return op1.mInducedGridPoints == op2.mInducedGridPoints;
        }

        friend bool operator!=(const Grid<Number> &op1, const Grid<Number> &op2) {
            return op1.mInducedGridPoints != op2.mInducedGridPoints;
        }

        friend std::ostream &operator<<(std::ostream &out, const Grid<Number> &grid) {
            out << "[";
            for (std::size_t d = 0; d < grid.mInducedGridPoints.size(); ++d) {
                out << std::endl
                    << d << ": ";
                for (std::size_t p = 0; p < grid.mInducedGridPoints.at(d).size(); ++p)
                    out << grid.mInducedGridPoints.at(d).at(p) << " ";
            }
            out << std::endl
                << "]" << std::endl;
            return out;
        }
    };
}  // namespace hypro
#include "Grid.tpp"
