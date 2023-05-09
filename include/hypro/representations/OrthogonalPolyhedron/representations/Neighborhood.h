/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file    Neighborhood.h
 * @author	Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#include "../OrthogonalPolyhedron.h"

namespace hypro {

/**
 * @brief      Specialization of orthogonal polyhedra by the neighborhood representation.
 *
 * @tparam     Number     The used number type.
 * @tparam     <unnamed>  The specialized representation type.
 */
    template<typename Number, ORTHO_TYPE::NEIGHBORHOOD>
    class OrthogonalPolyhedron {
    private:
        Grid<Number> mGrid;

    public:
        /***********************************************************************
         * Constructors
         ***********************************************************************/

        OrthogonalPolyhedron();

        OrthogonalPolyhedron(const Vertex<Number> &_vertex);

        OrthogonalPolyhedron(const VertexContainer<Number> &vertices);

        OrthogonalPolyhedron(const std::set<Vertex<Number>> &points);

        OrthogonalPolyhedron(const std::vector<Vertex<Number>> &points);

        OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type> &copy);

        OrthogonalPolyhedron(const OrthogonalPolyhedron<Number, Type> &&move);

        /***********************************************************************
         * Getter, Setter
         ***********************************************************************/

        std::vector<carl::Variable> variables() const;

        std::vector<Vertex<Number>> vertices() const;

        Box <Number> boundaryBox() const;

        void addVertex(const Vertex<Number> &_vertex);

        void addVertices(const std::vector<Vertex<Number>> &_vertices);

        bool empty() const;

        unsigned size() const;

        bool isVertex(const Point<Number> &_point) const;

        bool isOnIEdge(const Point<Number> &_point, unsigned i) const;

        bool isInternal(const Point<Number> &_point) const;

        bool isExternal(const Point<Number> &_point) const;

        std::vector<Point<Number>> iNeighborhood(const Point<Number> &_point, unsigned i) const;

        std::vector<Point<Number>> iNegNeighborhood(const Point<Number> &_point, unsigned i) const;

        std::vector<Point<Number>> neighborhood(const Point<Number> &_point) const;

        std::vector<Point<Number>> iSlice(unsigned i, Number pos) const;

        OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> iProjection(unsigned i) const;

        /***********************************************************************
         * Geometric Object functions
         ***********************************************************************/
        unsigned int dimension() const;

        OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> linearTransformation(const matrix_t<Number> &A,
                                                                                    const vector_t<Number> &b) const;

        OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> minkowskiSum(
                const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &rhs) const;

        OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> intersect(
                const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &rhs) const;

        OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> hull() const;

        bool contains(const Point<Number> &point) const;

        bool contains(const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &_other) const;

        OrthogonalPolyhedron<Number, Type>
        unite(const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &rhs) const;

        /***********************************************************************
         * Auxiliary functions
         ***********************************************************************/
        std::vector<std::vector<Point<Number>>> preparePlot(unsigned _xDim = 0, unsigned _yDim = 1) const;

        /***********************************************************************
         * Operators
         ***********************************************************************/

        OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &operator=(
                const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &_in) = default;

        OrthogonalPolyhedron<Number, TyORTHO_TYPE::NEIGHBORHOODpe> &operator=(
                OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &&) = default;

        friend bool operator==(const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &op1,
                               const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &op2) {
            return op1.mGrid == op2.mGrid;
        }

        friend bool operator!=(const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &op1,
                               const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &op2) {
            return op1.mGrid != op2.mGrid;
        }

        friend std::ostream &operator<<(std::ostream &ostr,
                                        const OrthogonalPolyhedron<Number, ORTHO_TYPE::NEIGHBORHOOD> &p) {
            ostr << "(";
            for (const auto &vertex: p.mGrid.vertices()) ostr << vertex << ", ";
            ostr << ")";
            return ostr;
        }

    private:
    };

}  // namespace hypro

#include "Neighborhood.tpp"
