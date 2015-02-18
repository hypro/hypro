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
            typedef std::set<vector_t<Number>> vertexSet;
            typedef std::set<Facet<Number>> neighborsSet;
            typedef std::vector<vector_t<Number>> outsideSet;

        /**
         * Members
         */
        private:
            vertexSet            mVertices;
            neighborsSet           mNeighbors;
            Hyperplane<Number>          mHyperplane;
            outsideSet          mOutsideSet;

        /**
         * Constructors & Destructor
         */
        public:
            Facet()
            {}

            Facet( const Facet<Number>& f) :
				mVertices(f.vertices()),
				mNeighbors(f.neighbors()),
				mHyperplane(f.hyperplane()),
				mOutsideSet(f.outsideSet)
            {}

            Facet( Ridge<Number> r, vector_t<Number> p)
            {
                mVertices = std::set<vector_t<Number>>();
                mVertices.insert(p);
                for(int i = 0; i < r.vertices().size; i++)
                {
                    mVertices.insert(r.vertices[i]);
                }
                mHyperplane = Hyperplane<Number>(mVertices);
                mNeighbors = std::set<Facet<Number>>();
                mOutsideSet = std::vector<vector_t<Number>>();

			}
			
			Facet(const std::set<vector_t<Number>>& _vertices) :
					mNeighbors()
			{
				if(!_vertices.empty()) {
					mVertices.insert(_vertices.begin(), _vertices.end());
					unsigned dimension = _vertices.begin()->rows();
					if(_vertices.size() < dimension) {
						mHyperplane = Hyperplane<Number>();
					} else if (_vertices.size() > dimension) {
						// TODO: Introduce check for degeneracy -> if not degenerate, reduce and initialize plane
						mHyperplane = Hyperplane<Number>(); // TODO: temporary!
					} else {
						// proper amount of vertices for initialization of hyperplane
						std::vector<vector_t<Number>> edges;
						for(unsigned i = 0; i < _vertices.size()-1; ++i) {
							for(unsigned j = i+1; j < _vertices.size(); ++j) {
								edges.insert(vector_t<Number>(_vertices(j) - _vertices(i)));
							}
						}

						assert(edges.size() == dimension-1);
						mHyperplane = Hyperplane<Number>( *(_vertices.begin()), edges );
					}
				}
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

            void setPoints(std::vector<vector_t<Number>> points)
            {
                if(mVertices.empty()) {
                    for(int i = 0; i < points.size(); i++) {
                        mVertices.insert(points[i]);
                    }
                    mHyperplane = Hyperplane<Number>(getNormalVector(),getScalar());
                }
            }

            vector_t<Number> getNormalVector () {
                return vector_t<Number>();
            }

            scalar_t<Number> getScalar () {
                return scalar_t<Number>();
            }

            Hyperplane<Number> hyperplane() const
            {
                return mHyperplane;
            }

            /*
             * Checks if a point is above, i.e. a positive distance to the Hyperplane.
             * @return true, if the point is above.
             */
            bool check_if_above(Point<Number> p)
            {
                return (mHyperplane.signedDistance(p) > 0);
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
