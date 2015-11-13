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
	typedef std::vector<Point<Number>> vertexSet;
	// typedef std::vector<Facet<Number>> neighborFacets;

	/**
	 * Members
	 */
  private:
	vertexSet mVertices;
	std::vector<std::shared_ptr<Facet<Number>>> mNeighbors;
	Hyperplane<Number> mHyperplane;

	/**
	 * Constructors & Destructor
	 */
  public:
	Ridge() {}

	Ridge( const Ridge<Number>& f ) {
		mVertices = f.vertices();
		mNeighbors = f.neighbors();
		mHyperplane = f.hyperplane();
	}

	Ridge( std::shared_ptr<Facet<Number>> facet1, std::shared_ptr<Facet<Number>> facet2 ) {
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

		mHyperplane = Hyperplane<Number>();  // mNormal,mScalar);
		// save mHyperplane as intersect of the facets
	}

	~Ridge() {}

	/**
	 * Getters and Setters
	 */

	vertexSet& rVertices() { return mVertices; }

	vertexSet vertices() const { return mVertices; }

	std::vector<std::shared_ptr<Facet<Number>>>& rNeighbors() { return mNeighbors; }

	std::vector<std::shared_ptr<Facet<Number>>> neighbors() const { return mNeighbors; }

	Hyperplane<Number> hyperplane() const { return mHyperplane; }
};

template <typename Number>
std::ostream& operator<<( std::ostream& _ostr, const Ridge<Number>& _f ) {
	_ostr << "Ridge: " << std::endl;
	for ( const auto& vertex : _f.vertices() ) _ostr << vertex << ", ";
	return _ostr;
}

}  // namespace

namespace std {
    template<class Number>
    struct hash<hypro::Ridge<Number>>{
        std::size_t operator() (const hypro::Ridge<Number>& ridge) const {
            std::size_t seed;
            std::hash<hypro::Point<Number>> pointHasher;
            std::vector<hypro::Point<Number>> vertices = ridge.vertices();
            for (int i = 0; i < vertices.rows(); i++) {
                boost::hash_combine(seed, pointHasher(vertices(i)));
            }
            return seed;
        }
    };
}
