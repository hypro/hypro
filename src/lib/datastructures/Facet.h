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
#include "Hyperplane.h"
//#include "Ridge.h"
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
		typedef std::vector<Point<Number>> pointVector;
		typedef std::vector<Facet<Number>> neighborsSet;

	/**
	 * Members
	 */
	private:
		pointVector			mVertices;
		neighborsSet			mNeighbors;
		Hyperplane<Number>		mHyperplane;
		pointVector			mOutsideSet;
		vector_t<Number>		mNormal;
		Number			mScalar;

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

		Facet( std::vector<Point<Number>> r, const Point<Number>& p, const Point<Number>& insidePoint)
		{
			r.push_back(p);
			setPoints(r, insidePoint);
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

		pointVector& rVertices()
		{
			return mVertices;
		}

		pointVector vertices() const
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

		void addNeighbor(const Facet<Number>& facet)
		{
			mNeighbors.push_back(facet); //check if already in the neighborset?
		}

		vector_t<Number> getNormal () const
		{
			return mNormal;
		}

		Number getScalar () const
		{
			return mScalar;
		}

		/*
		 * removes a given facet from the neighborset if it is inside the list
		 */
		void removeNeighbor(Facet<Number> facet)
		{
			for(unsigned i = 0; i<mNeighbors.size(); i++){
				if(facet == mNeighbors[i]){
					mNeighbors.erase(mNeighbors.begin() + i); //check for multiple entries?
				}
			}
		}

		void setPoints(std::vector<Point<Number>> points, Point<Number> _insidePoint)
		{
			if(mVertices.empty()) {
				for(unsigned i = 0; i < points.size(); i++) {
					mVertices.push_back(points[i]);
				}
				mNormal = getNormalVector();
				mScalar = getScalarVector();

				std::cout << "mNormal: " << mNormal << ", insidePoint: " << _insidePoint << std::endl;

				if(mNormal.dot(_insidePoint.rawCoordinates()) > mScalar)
					mNormal *= -1;
				mHyperplane = Hyperplane<Number>(mNormal,mScalar);
				std::cout << "mHyperplane: "<< mHyperplane << std::endl;
			}
		}

		vector_t<Number> getNormalVector () const {
			std::vector<vector_t<Number>> vectors;

			//std::cout << mVertices[0].rawCoordinates() << std::endl;
			//vectors.push_back(vector_t<Number>::Zero(mVertices[0].rawCoordinates().rows()));
			vectors.push_back(mVertices[0].rawCoordinates());
			for(unsigned i = 1; i < mVertices.size(); i++) {
				vectors.push_back(mVertices[i].rawCoordinates() - vectors[0]);
			}

			matrix_t<Number> matrix = matrix_t<Number>(vectors.size(),mVertices[0].rawCoordinates().size());
			for(unsigned i = 1; i < vectors.size(); i++) {
				for(unsigned j = 0; j < vectors[i].size(); j++) {
					matrix(i,j) = vectors[i](j);
				}
			}

			for(unsigned j = 0; j < vectors[0].size(); j++) {
				matrix(0,j) = 1;
			}
			vector_t<Number> b = vector_t<Number>::Zero(vectors.size());
			b(0) = 1;

			// std::cout << __func__ << ": A " << std::endl << matrix << std::endl << ",b " << std::endl << b << std::endl;
			vector_t<Number> result = matrix.fullPivHouseholderQr().solve(b);
			return result;
		}

		Number getScalarVector () const{
			// std::cout << mVertices[0]<< std::endl;
			 std::cout << mNormal << " ** " << std::endl;
			return Number (mNormal.dot(mVertices[0].rawCoordinates()));
		}

		const Hyperplane<Number>& hyperplane() const
		{
			return mHyperplane;
		}

		/*
		 * Iterators
		 */

		 typename pointVector::iterator begin() {
		 	return mVertices.begin();
		 }

		 typename pointVector::const_iterator begin() const{
		 	return mVertices.begin();
		 }

		 typename pointVector::iterator end() {
		 	return mVertices.end();
		 }

		 typename pointVector::const_iterator end() const{
		 	return mVertices.end();
		 }

		/*
		 * Functions 
		 */

		/*
		 * Checks if a point is above, i.e. a positive distance to the Hyperplane.
		 * @return true, if the point is above.vertices()
		 */
		bool isBelow(const Point<Number>& p) const {
			// return (mHyperplane.signedDistance(p) > 0);
			Number temp = Number (mNormal.dot(p.rawCoordinates()));
			std::cout << __func__ << " : " << p.rawCoordinates() << " * " << mNormal <<  " = ("<< temp << " - " << mScalar <<") = " << temp-mScalar << std::endl;
			return (temp-mScalar>0);
		}

		void addPointToOutsideSet(const Point<Number>& point)
		{
			mOutsideSet.push_back(point); //check double entries?
			std::cout << __func__ << " : " << __LINE__ << mOutsideSet << std::endl;
		}

		std::vector<Point<Number>> getOutsideSet() const
		{
			//std::cout << __func__ << " : " << __LINE__ << mOutsideSet << std::endl;
			return mOutsideSet;
		}

		/*
		 * Determines the point furthest away from the Hyperplane. The points to be considered are saved in hashlist.
		 * @return The Point which has the highest distance to the Hyperplane.
		 */
		Point<Number> furthest_Point() const 
		{
			if(mOutsideSet.empty()) {
				return Point<Number>();
			}
			else {
				Point<Number> result = mOutsideSet[0];
				Number max = Number (mNormal.dot(mOutsideSet[0].rawCoordinates()));//mHyperplane.signedDistance(result);
				for(unsigned i = 1; i<mOutsideSet.size(); i++){
					Number temp = Number (mNormal.dot(mOutsideSet[i].rawCoordinates()));
					if(temp>max){
						max=temp;
						result=mOutsideSet[i];
					}
				}
				return result;
			}
		}

		bool isNeighbor(const Facet<Number>& facet) const {
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

		friend bool operator!=(const Facet<Number>& _f1, const Facet<Number>& _f2)
		{
			return !(_f1 == _f2);
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
