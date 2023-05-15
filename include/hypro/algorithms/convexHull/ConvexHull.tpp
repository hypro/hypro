/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ConvexHull.h"

namespace hypro {

    template<typename Number>
    ConvexHull<Number>::ConvexHull(const std::vector<Point<Number>> points) {
        // TODO: Avoid this by internally using set directly.
        std::set<Point<Number>> tmp;
        tmp.insert(points.begin(), points.end());
        mPoints.insert(mPoints.end(), tmp.begin(), tmp.end());
    }

    template<typename Number>
    ConvexHull<Number>::ConvexHull(const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone)
            : mPoints(), mCone(cone) {
        std::set<Point<Number>> tmp;
        tmp.insert(points.begin(), points.end());
        mPoints.insert(mPoints.end(), tmp.begin(), tmp.end());
    }

    template<typename Number>
    ConvexHull<Number>::ConvexHull(const std::vector<Point<Number>> points, const std::vector<vector_t<Number>> cone,
                                   const std::vector<vector_t<Number>> linealty)
            : mPoints(), mCone(cone), mLinealtySpace(linealty) {
        std::set<Point<Number>> tmp;
        tmp.insert(points.begin(), points.end());
        mPoints.insert(mPoints.end(), tmp.begin(), tmp.end());
    }

    template<typename Number>
    std::vector<Point<Number>> ConvexHull<Number>::getPoints() const {
        return mPoints;
    }

    template<typename Number>
    std::vector<vector_t<Number>> ConvexHull<Number>::getCone() const {
        return mCone;
    }

    template<typename Number>
    std::vector<vector_t<Number>> ConvexHull<Number>::getLinealtySpace() const {
        return mLinealtySpace;
    }

    template<typename Number>
    std::vector<Halfspace<Number>> ConvexHull<Number>::getConeHsv() const {
        return mConeHsv;
    }

    template<typename Number>
    std::vector<Halfspace<Number>> ConvexHull<Number>::getDualHsv() const {
        return mDualHsv;
    }

    template<typename Number>
    std::vector<Halfspace<Number>> ConvexHull<Number>::getHsv() const {
        return mHsv;
    }

    template<typename Number>
    void ConvexHull<Number>::findOffset() {
        // compute barycenter
        mOffset = vector_t<Number>::Zero(mPoints[0].rawCoordinates().size());
        for (const auto &point: mPoints) {
            mOffset += point.rawCoordinates();
        }
        mOffset = mOffset / mPoints.size();

        // translate all points to make the barycenter the origin.
        unsigned index = 0;
        for (auto &point: mPoints) {
            point.setCoordinates(point.rawCoordinates() - mOffset);

            // small tuning - remove point that lies exactly on the barycenter, as we know it lies inside
            // Comment: Not neccesaryly true, what if it is the only point?
            if (point.rawCoordinates().nonZeros() == 0) {
                mPoints.erase(mPoints.begin() + index);
            }
            ++index;
        }
    }

    template<typename Number>
    void ConvexHull<Number>::toDual() {
        for (const auto &p: mPoints) {
            mDualHsv.push_back(Halfspace<Number>(p.rawCoordinates(), Number(1)));
            assert(mDualHsv.back().normal() == p.rawCoordinates());
        }
    }

    template<typename Number>
    void ConvexHull<Number>::toPrimal(const std::vector<Point<Number>> points) {
        // std::cout << __func__ << " created " << points.size() << " points in dual." << std::endl;
        for (const auto &p: points) {
            mHsv.push_back(Halfspace<Number>(p.rawCoordinates(), Number(1)));
            assert(mHsv.back().normal() == p.rawCoordinates());
        }
    }

    template<typename Number>
    void ConvexHull<Number>::convexHullVertices() {     //!!modify the points
#ifndef NDEBUG
        std::cout << __func__ << ": Input:" << std::endl;
        std::vector<Point<Number>> originalPoints;
        for (const auto &vertex: mPoints) {
            std::cout << vertex << std::endl;
            originalPoints.push_back(vertex);
        }
#endif

        if (mPoints.size() == 0) {  // emptyset
            // set up half-spaces which describe the empty set.
            vector_t<Number> h1 = vector_t<Number>(1);
            vector_t<Number> h2 = vector_t<Number>(1);
            h1[0] = 1;
            h2[0] = -1;
            mHsv.push_back(Halfspace<Number>(h1, Number(-1)));
            mHsv.push_back(Halfspace<Number>(h2, Number(-1)));
        } else {  // non-empty
            unsigned dimension = mPoints[0].rawCoordinates().size();

            // translate all points to make the barycenter the new origin.
            findOffset();
            if (mPoints.size() == 0) {  // if all points coincide with the barycenter
                Point<Number> zeroPoint = Point<Number>(vector_t<Number>::Zero(dimension));
                mPoints.push_back(zeroPoint);
                // set half-spaces describing the origin (a box arount 0).
                for (unsigned index = 0; index < dimension; ++index) {
                    vector_t<Number> newNormal = vector_t<Number>::Zero(dimension);
                    newNormal[index] = 1;
                    mHsv.push_back(Halfspace<Number>(newNormal, Number(0)));
                    newNormal[index] = -1;
                    mHsv.push_back(Halfspace<Number>(newNormal, Number(0)));
                }
            } else {  // the polytope contains more than one point.
                // switch to dual description - convert facet enumeration to vertex enumeration in the dual.
                toDual();
                // construct vertex enumerator.
                VertexEnumeration<Number> ev = VertexEnumeration<Number>(mDualHsv);
                // compute vertex enumeration.
                ev.enumerateVertices();
                // Todo: Check what this means exactly. Guess: Unbounded object.
                for (const auto &l: ev.getLinealtySpace()) {
                    mHsv.push_back(Halfspace<Number>(l, Number(0)));
                    mHsv.push_back(Halfspace<Number>(-1 * l, Number(0)));
                    std::cout << "LinealtySpace NOT empty!" << std::endl;
                }
                // convert back to primal to extract the facets.
                toPrimal(ev.getPoints());
            }
            // revert translation to the barycenter to the original position.
            translateHsv();
            // debug output.
            std::cout << __func__ << ": Result: " << std::endl;
            for (const auto &plane: mHsv) {
                std::cout << plane << std::endl;
            }

#ifndef NDEBUG
            for (const auto plane: mHsv) {
                std::cout << "Plane: " << plane << std::endl;
                for (const auto point: originalPoints) {
                    std::cout << "contains " << point << std::endl;
                    if (!plane.contains(point)) {
                        std::cout << "diff: " << point.rawCoordinates().dot(plane.normal()) << " VS (<=) "
                                  << plane.offset() << std::endl;
                    }
                    assert(plane.contains(point));
                }
            }
#endif
        }
    }

    template<typename Number>
    void ConvexHull<Number>::conicHull() {
        if (mCone.size() == 0) {
            vector_t<Number> h1 = vector_t<Number>(
                    2);  // in case the function is called in the polyhedric hull, the absurd answer is in dimension 2, so a dimension can be removed
            vector_t<Number> h2 = vector_t<Number>(2);
            h1[0] = 1;
            h1[1] = 1;
            h2[0] = -1;
            h2[1] = -1;
            mConeHsv.push_back(Halfspace<Number>(h1, Number(-1)));
            mConeHsv.push_back(Halfspace<Number>(h2, Number(-1)));
        } else {
            std::vector<Point<Number>> points;
            for (const auto &cone: mCone) {
                points.push_back(Point<Number>(cone));
            }
            Point<Number> zero = Point<Number>::Zero(mCone[0].size());
            points.push_back(zero);
            ConvexHull<Number> ch = ConvexHull<Number>(points);
            ch.convexHullVertices();
            for (const auto &hs: ch.getHsv()) {
                if (hs.offset() == 0) {
                    mConeHsv.push_back(hs);
                }
            }
        }
    }

    template<typename Number>
    void ConvexHull<Number>::polyhedriclHull() {
        try {
            if (mPoints.size() == 0) {
                throw std::string("\n WARNING: empty set. \n");
            }
            std::vector<vector_t<Number>> newCone;
            for (const auto &p: mPoints) {
                vector_t<Number> aux = vector_t<Number>(p.rawCoordinates().size() + 1);
                for (unsigned index = 0; index < p.rawCoordinates().size(); ++index) {
                    aux[index] = p.rawCoordinates()[index];
                }
                aux[p.rawCoordinates().size()] = 1;
                newCone.push_back(aux);
            }
            for (const auto &c: mCone) {
                vector_t<Number> aux = vector_t<Number>(c.size() + 1);
                for (unsigned index = 0; index < c.size(); ++index) {
                    aux[index] = c[index];
                }
                aux[c.size()] = 0;
                newCone.push_back(aux);
            }
            for (const auto &l: mLinealtySpace) {
                vector_t<Number> aux = vector_t<Number>(l.size() + 1);
                vector_t<Number> aux2 = vector_t<Number>(l.size() + 1);
                for (unsigned index = 0; index < l.size(); ++index) {
                    aux[index] = l[index];
                    aux2[index] = -1 * l[index];
                }
                aux[l.size()] = 0;
                aux2[l.size()] = 0;
                newCone.push_back(aux);
                newCone.push_back(aux2);
            }
            std::vector<Point<Number>> empty;
            ConvexHull<Number> ch = ConvexHull<Number>(empty, newCone);
            ch.conicHull();
            std::vector<Halfspace<Number>> hsv = ch.getConeHsv();
            for (auto &hs: hsv) {
                hs.setOffset(hs.offset() - hs.normal()[hs.normal().size() - 1]);    // projection fonction
                vector_t<Number> aux = vector_t<Number>(hs.normal().size() - 1);
                for (unsigned index = 0; index < hs.normal().size() - 1; ++index) {
                    aux[index] = hs.normal()[index];
                }
                vector_t<Number> zero = vector_t<Number>::Zero(hs.normal().size() - 1);
                hs.setNormal(aux);
                if (aux != zero) {
                    mHsv.push_back(hs);
                }
            }
        } catch (std::string const &message) {
            std::cout << message;
        }
    }

    template<typename Number>
    void ConvexHull<Number>::translateHsv() {
        // Todo: Check if this does the right thing (seems so).
        for (auto &hs: mHsv) {
            for (unsigned index = 0; index < hs.normal().size(); ++index) {
                hs.setOffset(hs.offset() + hs.normal()[index] * mOffset[index]);
            }
        }
    }

    template<typename Number>
    // not used
    void ConvexHull<Number>::projectOnLinealty() {
        if (mPoints.size() != 0 && mLinealtySpace.size() != 0) {
            unsigned dim = mPoints[0].rawCoordinates().size();
            unsigned index = 0;
            std::vector<Number> norms;
            std::vector<vector_t<Number>> projectionBase;
            while (projectionBase.size() < dim && index < mLinealtySpace.size()) {
                vector_t<Number> nextLineatyVector = mLinealtySpace[index];
                for (unsigned vectorIndex = 0; vectorIndex < projectionBase.size(); ++vectorIndex) {
                    nextLineatyVector = nextLineatyVector - projectionBase[vectorIndex] *
                                                            (projectionBase[vectorIndex].dot(nextLineatyVector) /
                                                             norms[vectorIndex]);
                }
                int i = 0;
                while (i < nextLineatyVector.size()) {
                    if (nextLineatyVector[i] != 0) {
                        break;
                    }
                    ++i;
                }
                if (i < nextLineatyVector.size()) {
                    projectionBase.push_back(nextLineatyVector);
                    norms.push_back(nextLineatyVector.dot(nextLineatyVector));
                }
                ++index;
            }
            mLinealtySpace = projectionBase;
            for (auto &p: mPoints) {
                index = 0;
                for (const auto &pv: projectionBase) {
                    p.setCoordinates(p.rawCoordinates() - pv * (pv.dot(p.rawCoordinates()) / norms[index]));
                    ++index;
                }
            }
        }
    }

}  // namespace hypro
