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
            typedef std::set<Point<Number>> vertexSet;
            typedef std::set<Facet<Number>> neighborsSet;
            typedef std::vector<Point<Number>> outsideSet;

        /**
         * Members
         */
        private:
            vertexSet            mVertices;
            neighborsSet           mNeighbors;
            Polynomial          mHyperplane;
            outsideSet          mOutsideSet;

        /**
         * Constructors & Destructor
         */
        public:
            Facet()
            {}

            Facet( const Facet<Number>& f)
            {
                                mVertices = f.vertices();
                                mNeighbors = f.neighbors();
                                mHyperplane = f.hyperplane();
                                mOutsideSet = f.outsideSet();
                        }


            Facet( Ridge<Number> r, Point<Number> p)
            {
                mVertices = new std::set<Point<Number>>();
                mVertices.insert(p);
                for(int i = 0; i < r.vertices().size; i++)
                {
                    mVertices.insert(r.vertices[i]);
                }
                mHyperplane = new Hyperplane<Number>(getNormalVector(),getScalar());
                mNeighbors = new std::set<Facet<Number>>();
                mOutsideSet = new std::vector<Point<Number>>();

          }

            ~Facet()
            {}

            /**
             * Getters and Setters
             */

            vertexSet& rVertices()
            {
                return mVertices;
            }

            vertexSet vertices() const
            {
                return mVertices;
            }

            neighborsSet& rNeighbors()
            {
                return mNeighbors;
            }

            neighborsSet neighbors() const
            {
                return mNeighbors;
            }

            void addNeighbor(Facet<Number> facet)
            {
                mNeighbors.insert(facet);
            }

            void setPoints(std::vector<Point<Number>> points)
            {
                if(mVertices.empty()) {
                    for(int i = 0; i < points.size(); i++) {
                        mVertices.insert(points[i]);
                    }
                    mHyperplane = new Hyperplane<Number>(getNormalVector(),getScalar());
                }
            }

            vector_t<Number> getNormalVector () {
                return vector_t<Number>();
            }

            scalar_t<Number> getScalar () {
                return scalar_t<Number>();
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
            	return false;
            }

            void addPointToOutsideSet(Point<Number> point)
            {
                mOutsideSet.push_back(point);
            }

            std::vector<Point<Number>> getOutsideSet()
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

            bool isNeighbor(Facet<Number> facet)
            {
                for(int i = 0; i < mNeighbors.size(); i++) {
                    if(mNeighbors[i].isEqual(facet)) {
                        return true;
                    }
                }
                return false;
            }
    };
}
