/*
 * @file   Polytope.h
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include <hypro/flags.h>

#ifdef HYPRO_USE_PPL
#include "../../datastructures/Facet.h"
#include "../../datastructures/Halfspace.h"
#include "../../datastructures/Point.h"
#include "../../datastructures/Ridge.h"
#include "../../util/VariablePool.h"
#include "../../util/convexHull.h"
#include "../GeometricObjectBase.h"
#include "../Polytopes/Cone.h"
#include "../Polytopes/Fan.h"
#include "PolytopeSetting.h"
#include "util.h"

#include <cassert>
#include <gmp.h>
#include <map>
#include <sstream>
#include <string>
CLANG_WARNING_DISABLE( "-Wunused-local-typedef" )
#include <ppl.hh>
CLANG_WARNING_RESET
#include <carl/core/Variable.h>

namespace hypro {

/**
 * @brief      A wrapper class encapsulating PPL-polytopes.
 *
 * @tparam     Number     The used number type.
 * @tparam     Converter  The used converter.
 *
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, class Setting>
class PolytopeT : private GeometricObjectBase {
  public:
	typedef Setting Settings;
	typedef Number NumberType;

  private:
	Parma_Polyhedra_Library::C_Polyhedron mPolyhedron;
	mutable std::vector<Point<Number>> mPoints;
	mutable bool mPointsUpToDate;
	Fan<Number> mFan;

  public:
	PolytopeT();
	PolytopeT( const PolytopeT& orig );
	PolytopeT( unsigned dimension );
	PolytopeT( const Point<Number>& point );
	PolytopeT( const typename std::vector<Point<Number>>& points );
	PolytopeT( const typename std::vector<vector_t<Number>>& points );
	PolytopeT( const matrix_t<Number>& A, const vector_t<Number>& b );
	PolytopeT( const matrix_t<Number>& A );
	PolytopeT( const Parma_Polyhedra_Library::C_Polyhedron& _rawPoly );

	virtual ~PolytopeT();

	/**
	 * Getters and Setters
	 */

	static representation_name type() { return representation_name::ppl_polytope; }

	/**
	 * Returns true, if the generatorset is empty.
	 * @return
	 */
	bool empty() const;

	/**
	 * Adds a point to the polytope. Note that if the point lies inside the
	 * current polytope, this has no effect.
	 * @param point
	 */
	void addPoint( const Point<Number>& point );

	void updatePoints() const;

	/**initConvexHull
	 * Returns the set of points which form the polytope.
	 * @return Pointset.
	 */
	std::vector<Point<Number>> vertices( const matrix_t<Number>& = matrix_t<Number>::Zero( 0, 0 ) ) const;

	/*
	 * returns the fan of the Polytope
	 */
	const Fan<Number>& fan();

	/*
	 * returns a reference to the fan of the Polytope
	 */
	Fan<Number>& rFan();

	/*
	 * sets the fan of the Polytope
	 */
	void setFan( const Fan<Number>& _fan );

	void calculateFan();

	/**
	 * Prints the polytopes' generators obtained from the PPL to stdout.
	 */
	void print() const;

	/*
	 *
	 */
	friend std::ostream& operator<<( std::ostream& lhs, const PolytopeT<Number, Converter, Setting>& rhs ) {
		using Parma_Polyhedra_Library::IO_Operators::operator<<;
		lhs << "[";
		lhs << rhs.rawPolyhedron();
		lhs << "]" << std::endl;
		return lhs;
	}

	/**
	 * PPL related functions
	 */
	const Parma_Polyhedra_Library::C_Polyhedron& rawPolyhedron() const;

	/**
	 * Geometric Object interface
	 */
	std::size_t dimension() const;
	PolytopeT linearTransformation( const matrix_t<Number>& A ) const;
	PolytopeT affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const;
	PolytopeT projectOn( const std::vector<std::size_t>& dimensions ) const;
	PolytopeT assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& ) const {
		WARN( "hypro", "Not implemented." );
		return *this;
	}
	PolytopeT minkowskiSum( const PolytopeT& rhs ) const;
	// implemented according to Komei Fukuda 2004
	PolytopeT altMinkowskiSum( PolytopeT& rhs );
	PolytopeT intersect( const PolytopeT& rhs ) const;
	PolytopeT intersectHalfspace( const Halfspace<Number>& rhs ) const;
	PolytopeT intersectHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	std::pair<CONTAINMENT, PolytopeT> satisfiesHalfspace( const Halfspace<Number>& rhs ) const;
	std::pair<CONTAINMENT, PolytopeT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;
	PolytopeT hull() const;
	bool contains( const Point<Number>& point ) const;
	bool contains( const PolytopeT& poly ) const;
	PolytopeT unite( const PolytopeT& rhs ) const;
	// static PolytopeT<Number,Converter,Setting> unite(const PolytopeT<Number,Converter,Setting>& polytopes);
	//   static std::vector<Facet<Number>> convexHull(const std::vector<Point<Number>> points);

	/**
	 * @brief      Reduces the polytope by removing redundant constraints. The number representation is already optimized
	 * by PPL internally.
	 */
	void reduceRepresentation() { removeRedundancy(); }

	/**
	 * Polytope related
	 */
	Number supremum() const;

	void removeRedundancy() {}

	// PolytopeT<Number,Converter,Setting>& operator= (const PolytopeT<Number,Converter,Setting>& rhs);

	/**
	 * Auxiliary functions
	 */
	int computeMaxVDegree();
	Point<Number> computeMaxPoint();
	Point<Number> computeInitVertex( PolytopeT _secondPoly );
	Point<Number> localSearch( Point<Number>& _vertex, Point<Number>& _sinkMaximizerTarget );
};

/** @} */

}  // namespace hypro

#include "Polytope.tpp"

#endif
