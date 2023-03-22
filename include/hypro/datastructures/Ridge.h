/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
#include "Facet.h"

namespace hypro {
template <class Number>
class Ridge {
  public:
	/**
	 * Typedefs
	 */
	using vertexSet = std::vector<Point<Number>>;

	/**
	 * Members
	 */
  private:
	vertexSet mVertices;
	std::vector<std::weak_ptr<Facet<Number>>> mNeighbors;
	Halfspace<Number> mHalfspace;

	/**
	 * Constructors & Destructor
	 */
  public:
	Ridge() {}

	Ridge( const Ridge<Number>& f ) {
		mVertices = f.vertices();
		mNeighbors = f.neighbors();
		mHalfspace = f.halfspace();
	}

	Ridge( std::shared_ptr<Facet<Number>> facet1, std::shared_ptr<Facet<Number>> facet2 )
		: mHalfspace( Halfspace<Number>() ) {
		//   std::vector<Facet<Number>> facets;
		//   facets.push_back(facet1);
		//   facets.push_back(facet2);
		//   mNeighbors = facets;
		mNeighbors.push_back( facet1 );
		mNeighbors.push_back( facet2 );
		mVertices = std::vector<Point<Number>>();
		for ( unsigned i = 0; i < facet1->vertices().size(); i++ ) {
			for ( unsigned j = 0; j < facet2->vertices().size(); j++ ) {
				if ( facet1->vertices()[i] == facet2->vertices()[j] ) {
					mVertices.push_back( facet1->vertices()[i] );
				}
			}
		}

		// mHalfspace = Halfspace<Number>();  // mNormal,mScalar);
		//  save mHalfspace as intersect of the facets
	}

	~Ridge() {}

	/**
	 * Getters and Setters
	 */

	vertexSet& rVertices() { return mVertices; }

	vertexSet vertices() const { return mVertices; }

	std::vector<std::weak_ptr<Facet<Number>>>& rNeighbors() { return mNeighbors; }

	std::vector<std::weak_ptr<Facet<Number>>> neighbors() const { return mNeighbors; }

	Halfspace<Number> halfspace() const { return mHalfspace; }
};

template <typename Number>
std::ostream& operator<<( std::ostream& _ostr, const Ridge<Number>& _f ) {
	_ostr << "Ridge: " << std::endl;
	for ( const auto& vertex : _f.vertices() ) _ostr << vertex << ", ";
	return _ostr;
}

}  // namespace hypro

namespace std {
template <class Number>
struct hash<hypro::Ridge<Number>> {
	std::size_t operator()( const hypro::Ridge<Number>& ridge ) const {
		std::size_t seed;
		std::hash<hypro::Point<Number>> pointHasher;
		std::vector<hypro::Point<Number>> vertices = ridge.vertices();
		for ( int i = 0; i < vertices.rows(); i++ ) {
			carl::hash_add( seed, pointHasher( vertices( i ) ) );
		}
		return seed;
	}
};
}  // namespace std
