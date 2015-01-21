/* 
 * A file which contains the data for a facet needed by the algorithm for convex hulls.
 * File:   Facet.h
 * Author: stefan, tayfun
 *
 * Created on March 19, 2014, 4:08 PM
 * @version 2015-01-21
 */

#pragma once

#include "../config.h"
#include "../representations/Hyperplane/Hyperplane.h"
#include "Ridge.h"
#include "Point.h"


namespace hypro
{
    template<class Number>
    class Facet
    {
        public:
        /**
         * Typedefs
         */
            typedef std::set<Point<Number>> vertices;
            typedef std::set<Facet> neighbors;
            typedef std::vector<Point<Number>> outsideSet;

        /**
         * Members
         */
        private:
            vertices            mVertices;
            neighbors           mNeighbors;
            Polynomial          mHyperplane;
            outsideSet          mOutsideSet;

        /**
         * Constructors & Destructor
         */
        public:
            Facet() : 
                    mVertices(),
                    mNeighbors(),
                    mHyperplane(),
                    mOutsideSet()
            {}

            Facet( const Facet<Number>& f) :
                    mVertices(f.vertices()),
                    mNeighbors(f.neighbors()),
                    mHyperplane(f.hyperplane()),
                    mOutsideSet(f.outsideSet())
            {}

            Facet( Ridge<Number> r, Point<Number> p)
            {
                mVertices = new std::set<Point<Number>>();
                mVertices.insert(p);
                for(int i = 0; i < r.vertices().size; i++)
                {
                    mVertices.insert(r.vertices[i]);
                }
                mHyperplane = new Hyperplane(getNormalVector(),getScalar());
                mNeighbors = new std::set<Facet>();
                mOutsideSet = new std::vector<Point<Number>>();

            }

            ~Facet()
            {}

            /**
             * Getters and Setters
             */

            vertices& rVertices()
            {
                return mVertices;
            }

            vertices vertices() const
            {
                return mVertices;
            }

            neighbors& rNeighbors()
            {
                return mNeighbors;
            }

            neighbors neighbors() const
            {
                return mNeighbors;
            }

            void addNeighbor(Facet facet)
            {
                mNeighbors.insert(facet);
            }

            void setPoints(std::vector<Point<Number>> points)
            {
                if(mVertices.empty()) {
                    for(int i = 0; i < points.size(); i++) {
                        mVertices.insert(points[i]);
                    }
                    mHyperplane = new Hyperplane(getNormalVector(),getScalar());
                }
            }

            hypro::vector_t<Number> getNormalVector () {
                return null;
            }

            hypro::scalar_t<Number> getScalar () {
                return null;
            }

            Polynomial hyperplane() const
            {
                return mHyperplane;
            }

            /*
             * Checks if a point is above, i.e. a positive distance to the Hyperplane.
             * @return true, if the point is above.
             */
            bool check_if_above(Point<Number> p)
            {
                //if ((multiplicate p with hyperplane.normalVector and subtract?/add? hyperplane.offset)>0)
                //true : return true else: false
            }

            void addPointToOutsideSet(Point<Number> point)
            {
                mOutsideSet.push_back(point);
            }

            std::vector<Point<Number>> outsideSet()
            {
                return mOutsideSet;
            }

            /*
             * Determines the point furthest away from the Hyperplane. The points to be considered are saved in hashlist.
             * @return The Point which has the highest distance to the Hyperplane.
             */
            Point<Number> furthest_Point()
            {
                return mOutsideSet[0]; // default return
            }

            bool isNeighbor(Facet facet)
            {
                for(int i = 0; i < neighbors.size(); i++) {
                    if(neighbors[i].isEqual(facet)) {
                        return true;
                    }
                }
                return false;
            }
    };
}
