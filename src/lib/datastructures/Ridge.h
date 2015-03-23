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
#include "Hyperplane.h"

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
		// typedef std::vector<Facet<Number>> neighborFacets;

	/**
	 * Members
	 */
	private:
		vertexSet            mVertices;
		// neighborFacets           mNeighbors;
		Hyperplane<Number>          mHyperplane;
		vector_t<Number>			mNormal;
		Number			mScalar;

	/**
	 * Constructors & Destructor
	 */
	public:
		Ridge() {

		}

		Ridge( const Ridge<Number>& f) :
			mVertices(f.vertices()),
			// mNeighbors = f.neighbors();
			mHyperplane(f.hyperplane()),
			mNormal(f.getNormal()),
			mScalar(f.getScalar())
		{}

		Ridge( std::set<Point<Number>> facet1, std::set<Point<Number>> facet2)
		{
			 //   std::vector<Facet<Number>> facets;
			 //   facets.push_back(facet1);
			 //   facets.push_back(facet2);
			 //   mNeighbors = facets;

			mVertices = std::set<Point<Number>>();
			for(Point<Number> facet_1: facet1) {
				for(Point<Number> facet_2: facet2) {
					if(facet_1 == facet_2) {
						mVertices.insert(facet_1);
					}
				}
			}
			mNormal = getNormalVector();
			mScalar = getScalarVector();
			mHyperplane = Hyperplane<Number>(mNormal,mScalar);
			//save mHyperplane as intersect of the facets
		}

		Ridge( std::vector<Point<Number>> facet1, std::vector<Point<Number>> facet2)
		{
			 //   std::vector<Facet<Number>> facets;
			 //   facets.push_back(facet1);
			 //   facets.push_back(facet2);
			 //   mNeighbors = facets;

			mVertices = std::set<Point<Number>>();
			for(Point<Number> facet_1: facet1) {
				for(Point<Number> facet_2: facet2) {
					if(facet_1 == facet_2) {
						mVertices.insert(facet_1);
					}
				}
			}
			mNormal = getNormalVector();
			mScalar = getScalarVector();
			mHyperplane = Hyperplane<Number>(mNormal,mScalar);
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

		vector_t<Number> getNormal () const
		{
			return mNormal;
		}

		Number getScalar () const
		{
			return mScalar;
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
					for(int j = 0; j<fvector_t<Number> getNormalVector () {
			std::vector<vector_t<Number>> vectors = new std::vector<vector_t<Number>>(mVertices.size());
			vectors[0] = mVertices[0].rawCoordinates();
			for(int i = 1; i < mVertices.size(); i++) {
				 vectors[i] = ( vectors[0]) - (mVertices[i].rawCoordinates());
			}
			matrix_t<Number> matrix = new matrix_t<Number,vectors.size(),vectors[0].size()> ();
			for(int i = 0; i < vectors.size(); i++) {
				for(int j = 0; j < vectors[0].size(); j++) {
					matrix(i,j) = vectors[i](j);
				}
			}
			vector_t<Number> b = new vector_t<Number,vectors.size(),1> ();
			for(int i = 0; i < vectors.size(); i++) {
				b(i) = 0;
			}
			vector_t<Number> result = matrix.fullPivHouseholderQr().solve(b);
			return result;
		}

		Number getScalarVector () {
			return new Number (mNormal.dot(mVertices[0].rawCoordinates()));
		}

		Hyperplane<Number> hyperplane() const
		{
			return mHyperplane;
		}acet2.vertices().size();j++) {
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
		Hyperplane<Number> hyperplane() const
		{
			return mHyperplane;
		}

		vector_t<Number> getNormalVector () {
			std::vector<vector_t<Number>> vectors = std::vector<vector_t<Number>>();
			std::vector<Point<Number>> vertex = std::vector<Point<Number>>();
			for(Point<Number> p: mVertices){
				vertex.push_back(p);
			}
			vectors[0] = vertex[0].rawCoordinates();
			for(unsigned i = 1; i < vertex.size(); i++) {
				vectors[i] = ( vectors[0]) - (vertex[i].rawCoordinates());
			}
			matrix_t<Number> matrix = matrix_t<Number> (vectors.size(),vectors[0].size());
			for(unsigned i = 0; i < vectors.size(); i++) {
				for(unsigned j = 0; j < vectors[0].size(); j++) {
					matrix(i,j) = vectors[i](j);
				}
			}
			vector_t<Number> b = vector_t<Number> (vectors.size());
			for(unsigned i = 0; i < vectors.size(); i++) {
				b(i) = 0;
			}
			vector_t<Number> result = matrix.fullPivHouseholderQr().solve(b);
			return result;
		}

		Number getScalarVector () {
			std::vector<Point<Number>> vertex = std::vector<Point<Number>>();
			for(Point<Number> p: mVertices){
				vertex.push_back(p);
			}
			return Number (mNormal.dot(vertex[0].rawCoordinates()));
		}

};
}
