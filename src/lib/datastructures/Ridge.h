/*
 * A file which contains the data for a ridge needed by the algorithm for convex hulls.
 * File:   Ridge.h
 * Author: tayfun
 *
 * @since 2014-12-10
 * @version 2014-12-10
 */

#pragma once

#include "../config.h"
#include "../representations/Hyperplane/Hyperplane.h"
#include "Facet.h"
#include "Point.h"

namespace hypro
{
    template<class Number>
    class Ridge
    {
        public:
        /**
         * Typedefs
         */
            typedef std::set<Point<Number>> vertices;
            typedef std::vector<Facet> neighbors;

        /**
         * Members
         */
        private:
            vertices            mVertices;
            neighbors           mNeighbors;
            Polynomial          mHyperplane;

        /**
         * Constructors & Destructor
         */
        public:
            Ridge() :
                    mVertices(),
                    mNeighbors(),
                    mHyperplane()
            {}

            Ridge( const Ridge<Number>& f) :
                    mVertices(f.vertices()),
                    mNeighbors(f.neighbors()),
                    mHyperplane(f.hyperplane())
            {}

            Ridge( Facet facet1, Facet facet2)
            {
                std::vector<Facet> facets;
                facets.push_back(facet1);
                facets.push_back(facet2);
                mNeighbors = facets;
                mVertices = new std::set<Point<Number>>();
                for(int i = 0; i<facet1.vertices().size();i++) {
                    for(int j = 0; j<facet2.vertices().size();j++) {
                        if(facet1.vertices()[i] == facet2.vertices(j)) {
                            mVertices.push_back(facet1.vertices()[i]);
                        }
                    }
                }
                mHyperplane = new Hyperplane(getNormalVector(),getScalar());
                //save mHyperplane as intersect of the facets

            }

            ~Ridge()
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

            void addNeighbors(std::vector<Facet> facets)
            {
                if(mNeighbors.empty())
                {
                   for(int i = 0; i < facets.size(); i++)
                   {
                       mNeighbors.push_back(facets[i]);
                   }
                   mVertices = new std::set<Point<Number>>();
                    for(int i = 0; i<facet1.vertices().size();i++) {
                        for(int j = 0; j<facet2.vertices().size();j++) {
                            if(facet1.vertices()[i] == facet2.vertices(j)) {
                                mVertices.push_back(facet1.vertices()[i]);
                            }
                        }
                    }
                    mHyperplane = new Hyperplane(getNormalVector(),getScalar());
                }
            }

       /**     void setPoints(std::vector<Point<Number>> points)
            {
                if(mVertices.empty())
                {
                for(int i = 0; i < points.size(); i++)
                    {
                        mVertices.insert(points[i]);
                    }
                }
            }
*/
            Polynomial hyperplane() const
            {
                return mHyperplane;
            }

            hypro::vector_t<Number> getNormalVector () {
                return null;
            }

            hypro::scalar_t<Number> getScalar () {
                return null;
            }

    };
}
