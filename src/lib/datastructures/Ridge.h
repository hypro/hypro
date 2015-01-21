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
            typedef std::set<Point<Number>> vertexSet;
          //  typedef std::vector<Facet<Number>> neighborFacets;

        /**
         * Members
         */
        private:
            vertexSet            mVertices;
           // neighborFacets           mNeighbors;
            Polynomial          mHyperplane;

        /**
         * Constructors & Destructor
         */
        public:
            Ridge() {

            }

            Ridge( const Ridge<Number>& f) {
                    mVertices = f.vertices();
              //      mNeighbors = f.neighbors();
                    mHyperplane = f.hyperplane();
            }

            Ridge( std::set<Point<Number>> facet1, std::set<Point<Number>> facet2)
            {
             //   std::vector<Facet<Number>> facets;
             //   facets.push_back(facet1);
             //   facets.push_back(facet2);
             //   mNeighbors = facets;

            	mVertices = new std::set<Point<Number>>();
                for(int i = 0; i<facet1.size();i++) {
                    for(int j = 0; j<facet2.size();j++) {
                        if(facet1[i] == facet2[j]) {
                            mVertices.push_back(facet1[i]);
                        }
                    }
                }
                mHyperplane = new Hyperplane<Number>(getNormalVector(),getScalar());
                //save mHyperplane as intersect of the facets

            }

            ~Ridge()
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

          //  neighborFacets& rNeighbors()
          //
          //      return mNeighbors;
          //  }

          //  neighborFacets neighbors() const
          //  {
          //      return mNeighbors;
          //  }

          /*  void addNeighbors(std::vector<Facet<Number>> facets)
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
*/
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

            vector_t<Number> getNormalVector () {
                return new vector_t<Number>();
            }

            scalar_t<Number> getScalar () {
                return new scalar_t<Number>();
            }

    };
}
