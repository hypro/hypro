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
            typedef std::vector<Facet<Number>> neighborsSet;
            typedef std::vector<Point<Number>> outsideSet;

        /**
         * Members
         */
        private:
            vertexSet            mVertices;
            neighborsSet           mNeighbors;
            Hyperplane<Number>          mHyperplane;
            outsideSet          mOutsideSet;
            vector_t<Number>			mNormal;
            scalar_t<Number>			mScalar;

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
				mOutsideSet(f.getOutsideSet()),
            	mNormal(f.getNormal()),
            	mScalar(f.getScalar())
            {}

            Facet( Ridge<Number> r, Point<Number> p)
            {
                mVertices = std::set<Point<Number>>();
                mVertices.insert(p);
                for(Point<Number> pt: r.vertices())
                {
                    mVertices.insert(pt);
                }
                mNormal = getNormalVector();
                mScalar = getScalarVector();
                mHyperplane = Hyperplane<Number>(mNormal,mScalar);
                //mHyperplane = Hyperplane<Number>(mVertices);
                mNeighbors = std::vector<Facet<Number>>();
                mOutsideSet = std::vector<Point<Number>>();

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
                mNeighbors.push_back(facet);
            }

            vector_t<Number> getNormal () const
        	{
               	return mNormal;
            }

            scalar_t<Number> getScalar () const
            {
               	return mScalar;
            }

            void setPoints(std::vector<Point<Number>> points)
            {
                if(mVertices.empty()) {
                    for(unsigned i = 0; i < points.size(); i++) {
                        mVertices.insert(points[i]);
                    }
                    std::cout << __func__ << " : " << __LINE__ << std::endl;
                    mNormal = getNormalVector();
                    mScalar = getScalarVector();
                    std::cout << __func__ << " : " << __LINE__ << std::endl;
                    mHyperplane = Hyperplane<Number>(mNormal,mScalar);
                }
            }

            vector_t<Number> getNormalVector () {
            	std::vector<vector_t<Number>> vectors;
            	std::vector<Point<Number>> vertex;
            	for(Point<Number> p: mVertices){
            		vertex.push_back(p);
            	}

            	std::cout << __func__ << " : " << __LINE__ << std::endl;

            	std::cout << vertex[0].rawCoordinates() << std::endl;
            	//vectors.push_back(vector_t<Number>::Zero(vertex[0].rawCoordinates().rows()));
            	vectors.push_back(vertex[0].rawCoordinates());
            	std::cout << __func__ << " : " << __LINE__ << std::endl;
               	for(unsigned i = 1; i < vertex.size(); i++) {
               		std::cout << __func__ << " : " << __LINE__ << std::endl;
                     vectors.push_back(( vectors[0]) - (vertex[i].rawCoordinates()));
                     std::cout << __func__ << " : " << __LINE__ << std::endl;
                }

               	std::cout << __func__ << " : " << __LINE__ << std::endl;

                matrix_t<Number> matrix = matrix_t<Number>(vectors.size(),vectors[0].size());
            	for(unsigned i = 0; i < vectors.size(); i++) {
            		for(unsigned j = 0; j < vectors[i].size(); j++) {
            			matrix(i,j) = vectors[i](j);
            		}
            	}
                vector_t<Number> b = vector_t<Number>::Zero(vectors.size());
                std::cout << __func__ << " : " << __LINE__ << std::endl;
            	vector_t<Number> result = matrix.fullPivHouseholderQr().solve(b);
            	std::cout << __func__ << " : " << __LINE__ << std::endl;
            	return result;
            }

            scalar_t<Number> getScalarVector () {
            	std::vector<Point<Number>> vertex = std::vector<Point<Number>>(mVertices.size());
            	for(Point<Number> p: mVertices){
            	   vertex.push_back(p);
            	}
            	std::cout << __func__ << " : " << __LINE__ << std::endl;
            	std::cout << mNormal << " ** " << std::endl << vertex[0].rawCoordinates()<< std::endl;
               	return scalar_t<Number> (mNormal.dot(vertex[0].rawCoordinates()));
            }

            Hyperplane<Number> hyperplane() const
            {
                return mHyperplane;
            }

            /*
             * Checks if a point is above, i.e. a positive distance to the Hyperplane.
             * @return true, if the point is above.vertices()
             */
            bool check_if_above(Point<Number> p)
            {
                //return (mHyperplane.signedDistance(p) > 0);
            	scalar_t<Number> temp = scalar_t<Number> (mNormal.dot(p.rawCoordinates()));
            	return temp-mScalar>0 ;
            }

            void addPointToOutsideSet(Point<Number> point)
            {
                mOutsideSet.push_back(point);
            }

            std::vector<Point<Number>> getOutsideSet() const
            {
                return mOutsideSet;
            }

            /*
             * Determines the point furthest away from the Hyperplane. The points to be considered are saved in hashlist.
             * @return The Point which has the highest distance to the Hyperplane.
             */
            Point<Number> furthest_Point()
        	{
            	if(mOutsideSet.empty()) {
               		return Point<Number>();
            	}
                else {
                	Point<Number> result = mOutsideSet[0];
                	scalar_t<Number> max = scalar_t<Number> (mNormal.dot(mOutsideSet[0].rawCoordinates()));//mHyperplane.signedDistance(result);
                	for(unsigned i = 1; i<mOutsideSet.size(); i++){
                    	scalar_t<Number> temp = scalar_t<Number> (mNormal.dot(mOutsideSet[i].rawCoordinates()));
                     	if(temp>max){
                     		max=temp;
                     		result=mOutsideSet[i];
                     	}
                	}
                	return result;
                }
        	}

            bool isNeighbor(Facet<Number> facet)
            {
                for(unsigned i = 0; i < mNeighbors.size(); i++) {
                    if(mNeighbors[i] == facet) {
                        return true;
                    }
                }
                return false;
            }

            friend bool operator==(const Facet<Number>& _f1, const Facet<Number>& _f2)
            {
            	return (_f1.vertices() == _f2.vertices());
            }


    };

    template<typename Number>
    std::ostream & operator<< (std::ostream& _ostr, const Facet<Number>& _f)
	{
		_ostr << "Facet : \n";
		for (const auto& vertex : _f.vertices()) {
			_ostr << vertex << "\n " ;
	}
		return _ostr;
	}
}
