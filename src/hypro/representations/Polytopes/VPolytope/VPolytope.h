/*
 * The class implementing the vertex representation of a convex polytope.
 * @file   VPolytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 *
 * @since   2014-02-25
 * @version 2014-02-25
 */
#pragma once

#ifndef INCL_FROM_GOHEADER
	static_assert(false, "This file may only be included indirectly by GeometricObject.h");
#endif

#include "../Cone.h"
#include "../../../algorithms/convexHull/ConvexHull.h"
#include "util/convexHull.h"
#include "util/linearOptimization/Optimizer.h"
#include "util/Permutator.h"
#include "util/pca.h"
#include "datastructures/Facet.h"
#include <set>
#include <cassert>
#include <vector>

namespace hypro {

template <typename Number, typename Converter>
class VPolytopeT {
  public:

	using pointVector = std::vector<Point<Number>>;

	/***************************************************************************
	 * Members
	 **************************************************************************/
  private:
	mutable pointVector mVertices;
	Cone<Number> mCone;
	bool mReduced;

	std::vector<std::set<unsigned>> mNeighbors;

  public:
	/***************************************************************************
	 * Constructors
	 **************************************************************************/

	// constructors for bounded v-polyhedra -> v-polytopes
	VPolytopeT();
	VPolytopeT( const Point<Number>& point );
	VPolytopeT( const pointVector& points );
	VPolytopeT( const std::vector<vector_t<Number>>& rawPoints );
	VPolytopeT( const matrix_t<Number>& _constraints, const vector_t<Number> _constants );

	VPolytopeT( const VPolytopeT& orig ) = default;
	VPolytopeT( VPolytopeT&& _orig ) = default;

	~VPolytopeT() {
	}

	/***************************************************************************
	* General interface
	**************************************************************************/

	VPolytopeT linearTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	VPolytopeT minkowskiSum( const VPolytopeT& rhs ) const;
	VPolytopeT intersect( const VPolytopeT& rhs ) const;
	VPolytopeT intersectHalfspace( const Halfspace<Number>& rhs ) const;
	VPolytopeT intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	std::pair<bool, VPolytopeT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<bool, VPolytopeT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const vector_t<Number>& vec ) const;
	bool contains( const VPolytopeT& _other ) const;
	VPolytopeT unite( const VPolytopeT& rhs ) const;
	VPolytopeT unite( const std::vector<VPolytopeT>& rhs ) const;

	void clear();

	/***************************************************************************
	 * Getters, Setters, Iterators
	 **************************************************************************/

	bool empty() const { return mVertices.empty(); }

	static VPolytopeT Empty() { return VPolytopeT(); }

	std::size_t dimension() const {
		if ( mVertices.empty() ) return 0;
		return mVertices[0].dimension();
	}

	std::size_t size() const { return mVertices.size(); }

	static representation_name type() { return representation_name::polytope_v; }

	bool reduced() const { return mReduced; }

	Number supremum() const;

	const Cone<Number>& cone() const { return mCone; }

	void setCone( const Cone<Number>& _cone ) { mCone = _cone; }

	void setNeighbors( const Point<Number>& _point, const std::set<Point<Number>>& _neighbors ) {
		unsigned pos = 0;
		while ( pos < mVertices.size() && ( mVertices[pos] != _point ) ) ++pos;

		if ( mVertices[pos] == _point ) {
			for ( const auto& neighbor : _neighbors ) {
				unsigned nPos = 0;
				while ( nPos < mVertices.size() && ( mVertices[nPos] != neighbor ) ) ++nPos;

				if ( mVertices[nPos] == neighbor ) {
					mNeighbors[pos].insert( nPos );
					mNeighbors[nPos].insert( pos );
				}
			}
		}
	}

	void unsafeSetNeighbors( const std::vector<std::set<unsigned>>& _neighbors ) { mNeighbors = _neighbors; }

	std::vector<Point<Number>> neighbors( const Point<Number>& _point ) const {
		std::vector<Point<Number>> result;
		unsigned pos = 0;
		while ( pos < mVertices.size() && ( mVertices[pos] != _point ) ) ++pos;

		if ( mVertices[pos] == _point ) {
			for ( unsigned nPos : mNeighbors[pos] ) result.emplace_back( mVertices[nPos] );
		}
		return std::move( result );
	}

	typename pointVector::iterator insert( const Point<Number>& i ) {
		assert( dimension() == 0 || dimension() == i.dimension() );
		mReduced = false;
		auto res = mVertices.insert( mVertices.end(), i );
		mNeighbors.push_back( std::set<unsigned>() );
		return res;
	}

	typename pointVector::iterator insert( const vector_t<Number>& _coord ) {
		assert( dimension() == 0 || dimension() == _coord.rows() );
		mReduced = false;
		mNeighbors.push_back( std::set<unsigned>() );
		return mVertices.insert( mVertices.end(), Point<Number>( _coord ) );
	}

	typename pointVector::iterator insert( const typename pointVector::const_iterator begin,
										   const typename pointVector::const_iterator end ) {
		assert( dimension() == 0 || dimension() == begin->dimension() );
		mReduced = false;
		mNeighbors.push_back( std::set<unsigned>() );
		return mVertices.insert( mVertices.end(), begin, end );
	}

	const pointVector& vertices() const { return mVertices; }

	bool hasVertex( const Point<Number>& vertex ) const {
		for ( const auto point : mVertices ) {
			if ( point == vertex ) return true;
		}
		return false;
	}

	bool hasVertex( const vector_t<Number>& vertex ) const { return ( mVertices.find( vertex ) != mVertices.end() ); }

	typename pointVector::iterator begin() { return mVertices.begin(); }
	typename pointVector::const_iterator begin() const { return mVertices.begin(); }
	typename pointVector::iterator end() { return mVertices.end(); }
	typename pointVector::const_iterator end() const { return mVertices.end(); }

	void print() const { std::cout << *this << std::endl; }

	void removeRedundancy();

	template<typename N = Number, carl::DisableIf< carl::is_float<N> > = carl::dummy>
	void reduceNumberRepresentation(unsigned limit = fReach_DENOMINATOR) const {
		if(!mVertices.empty()) {
	 		// determine barycenter to set rounding directions
			unsigned dimension = mVertices.begin()->rawCoordinates().rows();
			vector_t<Number> barycenter = vector_t<Number>::Zero(dimension);
			for(const auto& vertex : mVertices) {
				barycenter = barycenter + (vertex.rawCoordinates()/ Number(unsigned(mVertices.size())));
			}
			for(auto& vertex : mVertices) {
				vector_t<Number> roundingDirections = vertex.rawCoordinates() - barycenter;
				for(unsigned d = 0; d < dimension; ++d) {
					assert(d < vertex.dimension());
					if(carl::getDenom(vertex.at(d)) > limit) {
						Number u = Number(carl::getDenom(vertex.at(d))/carl::getDenom(vertex.at(d))) - Number(limit);
						Number roundedNumerator;
						Number oldNumerator = Number(carl::getNum(vertex.at(d)));
						if(roundingDirections(d) > 0) // round towards infinity
							roundedNumerator = carl::ceil( Number(oldNumerator - (oldNumerator/u)) );
						else // round towards -infinity
							roundedNumerator = carl::floor( Number(oldNumerator - (oldNumerator/u)) );

						vertex[d] = roundedNumerator / Number(limit);
					}
				}
			}
		}
	}

	template<typename N = Number, carl::EnableIf< carl::is_float<N> > = carl::dummy>
	void reduceNumberRepresentation(unsigned = fReach_DENOMINATOR) const {}

	void updateNeighbors();

  private:
	/***************************************************************************
	 * Auxiliary functions
	 **************************************************************************/
	static bool belowPlanes(const vector_t<Number>& vertex, const matrix_t<Number>& normals, const vector_t<Number>& offsets);
	static bool abovePlanes(const vector_t<Number>& vertex, const matrix_t<Number>& normals, const vector_t<Number>& offsets);

	template<typename N = Number, carl::DisableIf< std::is_same<N, double> > = carl::dummy>
	static bool insidePlanes(const vector_t<Number>& vertex, const matrix_t<Number>& normals, const vector_t<Number>& offsets) {
		for(unsigned rowIndex = 0; rowIndex < normals.rows(); ++rowIndex){
			// compare with tolerance of 128 ULPs. (Note: When type is different from double, this should do proper equivalence comparison)
			if( vertex.dot(normals.row(rowIndex)) != offsets(rowIndex) ){
				return false;
			}
		}
		return true;
	}

	template<typename N = Number, carl::EnableIf< std::is_same<N, double> > = carl::dummy>
	static bool insidePlanes(const vector_t<double>& vertex, const matrix_t<double>& normals, const vector_t<double>& offsets) {
		for(unsigned rowIndex = 0; rowIndex < normals.rows(); ++rowIndex){
			// compare with tolerance of 128 ULPs. (Note: When type is different from double, this should do proper equivalence comparison)
			if( !carl::AlmostEqual2sComplement(vertex.dot(normals.row(rowIndex)),offsets(rowIndex), 128) ){
				return false;
			}
		}
		return true;
	}

	/***************************************************************************
	 * Operators
	 **************************************************************************/
  public:
	VPolytopeT<Number, Converter>& operator=( const VPolytopeT<Number, Converter>& rhs ) = default;
	VPolytopeT<Number, Converter>& operator=( VPolytopeT<Number, Converter>&& rhs ) = default;
	bool operator==( const VPolytopeT<Number, Converter>& rhs ) const;
};

template <typename Number, typename Converter>
std::ostream& operator<<( std::ostream& out, const hypro::VPolytopeT<Number, Converter>& lhs ) {
	out << "{ ";
	for ( const auto& vector : lhs ) {
		out << vector << " ";
	}
	out << "}";
	return out;
}

}  // namespace

#include "VPolytope.tpp"
