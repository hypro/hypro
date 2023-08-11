/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * A container for vertices.
 * @file   VertexContainer.h
 *
 * @author Sebastian Junges
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since	2011-06-08
 * @version 2014-05-28
 */

#pragma once

#include "Vertex.h"

namespace hypro {

    template<typename Number>
    class VertexContainer {
    private:
        /***********************************************************************
         * Member
         **********************************************************************/
        vSet<Number> mVertices;
        mutable std::size_t mHash = 0;

    public:
        /***********************************************************************
         * Constructors & Destructors
         **********************************************************************/
        VertexContainer() {}

        VertexContainer(const Vertex<Number> &_vertex)
                : mVertices() { mVertices.insert(_vertex); }

        VertexContainer(const vSet<Number> &vertices)
                : mVertices(vertices) {}

        VertexContainer(const std::vector<Vertex<Number>> &_vertices)
                : mVertices() {
            mVertices.insert(_vertices.begin(), _vertices.end());
        }

        VertexContainer(const VertexContainer &orig) { mVertices = orig.mVertices; }

        ~VertexContainer() {}

        /***********************************************************************
         * Getters & Setters
         **********************************************************************/

        std::size_t dimension() const {
            if (mVertices.size() == 0) return 0;
            return (*mVertices.begin()).dimension();
        }

        std::vector<carl::Variable> variables() const {
            if (mVertices.size() == 0) return std::vector<carl::Variable>();
            return (*mVertices.begin()).variables();
        }

        std::size_t size() const { return mVertices.size(); }

        bool empty() const { return mVertices.empty(); }

        vSet<Number> &rVertices() { return mVertices; }

        vSet<Number> vertices() const { return mVertices; }

        vList<Number> getSmallerVertices(const Point<Number> &p) {
            vList<Number> verticesInBoundary;
            for (auto vertexIt = mVertices.begin(); vertexIt != mVertices.end(); ++vertexIt) {
                if ((*vertexIt).isInBoundary(p)) verticesInBoundary.push_back(*vertexIt);
            }
            return verticesInBoundary;
        }

        /**
         *
         * @param p
         * @return
         */
        inline std::pair<bool, bool> isVertex(const Point<Number> &p) const {
            vSetIt<Number> it = mVertices.find(Vertex<Number>(p, false));
            if (it == mVertices.end())
                return std::pair<bool, bool>(false, false);
            else
                return std::pair<bool, bool>(true, it->getColor());
        }

        /**
         *
         * @return
         */
        inline bool originIsVertex() const {
            if (mVertices.size() == 0) return false;
            Vertex<Number> origin = Vertex<Number>(mVertices.begin()->point().newEmpty(), true);
            return (mVertices.find(origin) != mVertices.end());
        }

        /***********************************************************************
         * Operators & Functions
         **********************************************************************/

        VertexContainer<Number> &operator=(const VertexContainer<Number> &rhs) {
            if (this == &rhs) return (*this);
            mVertices.clear();
            mVertices = rhs.mVertices;
            mHash = 0;
            return *this;
        }

        inline vSetIt<Number> find(const Point<Number> &p, bool colour = false) const {
            return find(Vertex<Number>(p, colour));
        }

        inline vSetIt<Number> find(const Vertex<Number> &v) const {
            vSetIt<Number> it = mVertices.find(v);
            if (it != mVertices.end() && it->color() != v.color()) it = mVertices.end();
            return it;
        }

        inline void move(const Point<Number> &p) {
            vSet<Number> tmp;
            vSetIt<Number> tmpIt = tmp.begin();
            for (vSetIt<Number> it = mVertices.begin(); it != mVertices.end(); ++it) {
                Vertex<Number> v = Vertex<Number>(*it);
                v.rPoint().move(p);
                tmp.insert(tmpIt, v);
                tmpIt++;
            }
            mHash = 0;
            mVertices = tmp;
        }

        inline void linearTransformation(const matrix_t<Number> &A, const vector_t<Number> &b) {
            vSet<Number> tmp;
            vSetIt<Number> tmpIt = tmp.begin();
            for (vSetIt<Number> it = mVertices.begin(); it != mVertices.end(); ++it) {
                Vertex<Number> v = Vertex<Number>(*it);
                v.rPoint().linearTransformation(A, b);
                tmp.insert(tmpIt, v);
                tmpIt++;
            }
            mHash = 0;
            mVertices = tmp;
        }

        /**
         *
         * @return
         */
        inline vSetIt<Number> begin() const { return mVertices.begin(); }

        /**
         *
         * @return
         */
        inline vSetIt<Number> end() const { return mVertices.end(); }

        /**
         *
         * @param v
         * @return A bidirectional iterator to the inserted Vertex.
         * Not safe.
         */
        inline std::pair<vSetIt<Number>, bool> insert(const Vertex<Number> &v) {
            mHash = 0;
            return mVertices.insert(v);
        }

        /**
         *
         * @param begin
         * @param end
         */
        template<typename ForwardIterator>
        inline void insert(ForwardIterator begin, ForwardIterator end) {
            mHash = 0;
            mVertices.insert(begin, end);
        }

        /**
         *
         * @param p
         * @param c
         * @return
         */
        inline std::pair<vSetIt<Number>, bool> insert(const Point<Number> &p, const bool c = false) {
            mHash = 0;
            return insert(Vertex<Number>(p, c));
        }

        /**
         *
         * @param v
         * @param pos
         * @return
         */
        template<typename BiIterator>
        inline vSetIt<Number> insert(const Vertex<Number> &v, const BiIterator pos) {
            mHash = 0;
            return mVertices.insert(pos, v);
        }

        inline vSetIt<Number> insertAtBack(const Vertex<Number> &v) {
            mHash = 0;
            return mVertices.insert(--mVertices.end(), v);
        }

        /**
         *
         * @param p
         * @param c
         * @param pos
         * @return
         */
        template<typename BiIterator>
        inline vSetIt<Number> insert(const Point<Number> &p, bool c, const BiIterator pos) {
            mHash = 0;
            return insert(Vertex<Number>(p, c), pos);
        }

        /**
         *
         * @param pos
         */
        template<typename BiIterator>
        inline void erase(BiIterator pos) {
            mHash = 0;
            mVertices.erase(pos);
        }

        /**
         *
         * @param p Vertex that is erased.
         */
        inline void erase(const Vertex<Number> &p) {
            mHash = 0;
            mVertices.erase(p);
        }

        /**
         * clears the underlying container.
         */
        inline void clear() {
            mHash = 0;
            mVertices.clear();
        }

        inline bool set(const Point<Number> &p, bool c) {
            typename std::set<Vertex<Number>>::iterator it = mVertices.find(Vertex<Number>(p, false));
            if (it == mVertices.end()) return false;
            mHash = false;
            mVertices.erase(it);
            insert(p, c, it);
            return true;
        }

        /**
         * @return Hash value
         */
        std::size_t getHash() const {
            if (this->mHash == 0) {
                // regenerate hash
                this->mHash = std::hash<vSet<Number>>()(this->vertices());
            }
            return this->mHash;
        }

        /**
         *
         * @param c1
         * @param c2
         * @return true, if they are equal.
         */
        friend bool operator==(const VertexContainer<Number> &c1, const VertexContainer<Number> &c2) {
            if (c1.getHash() != c2.getHash()) {
                return false;
            }

            return c1.mVertices == c2.mVertices;
        }

        /**
         *
         * @param c1
         * @param c2
         * @return true, if they are not equal.
         */
        friend bool operator!=(const VertexContainer<Number> &c1, const VertexContainer<Number> &c2) {
            return !(c1 == c2);
        }

        /**
         *
         * @param p
         * @return
         */
        const bool &operator[](const Point<Number> &p) const { return isVertex(p).second; }

        friend std::ostream &operator<<(std::ostream &ostr, const VertexContainer<Number> &cont) {
            for (auto it = cont.begin(); it != cont.end(); ++it) {
                ostr << (*it) << "\n";
            }
            return ostr;
        }
    };
}  // namespace hypro

namespace std {
    template<class Number>
    struct hash<hypro::VertexContainer<Number>> {
        std::size_t operator()(hypro::VertexContainer<Number> const &vertexContainer) const {
            return std::hash<hypro::vSet<Number>>()(vertexContainer.vertices());
        }
    };

    template<class Number>
    struct hash<set<hypro::Vertex<Number>>> {
        std::size_t operator()(hypro::vSet<Number> const &set) const {
            size_t result = 0;
            hash<hypro::Vertex<Number>> vertexHasher;
            for (auto it = set.begin(); it != set.end(); it++) {
                carl::hash_add(result, vertexHasher(*it));
            }
            return result;
        }
    };
}  // namespace std
