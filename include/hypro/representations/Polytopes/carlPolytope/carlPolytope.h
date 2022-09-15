/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#ifndef INCL_FROM_GOHEADER
static_assert( false, "This file may only be included indirectly by GeometricObjectBase.h" );
#endif

#include "../../../algorithms/quantifierElimination/qe.h"
#include "../../../carlTypes.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../util/VariablePool.h"
#include "../../../util/linearOptimization/Optimizer.h"
#include "../../../util/logging/Logger.h"
#include "carlPolytopeSetting.h"
#include "util.h"

namespace hypro {

/**
 * @brief Class for representing polytopes as CArL-formulas.
 *
 * @tparam Number
 * @tparam Converter
 * @tparam Setting
 * \ingroup geoState @{
 */
template <typename Number, typename Converter, typename Setting>
class CarlPolytopeT : private GeometricObjectBase {
  public:
	// typedefs
	using Settings = Setting;
	using NumberType = Number;
	static constexpr auto type_enum = representation_name::carl_polytope;

  private:
	FormulaT<tNumber> mFormula;							 /// The description of the polytope as a conjunction of linear constraints.
	mutable std::vector<Halfspace<Number>> mHalfspaces;	 /// Caches transformed half-spaces.
	mutable std::size_t mDimension = 0;					 /// Stores the state space dimension the polytope resides in.
	mutable bool mSpaceDimensionSet = false;			 /// used to indicate that the space dimension has been set externally, which overrides anything else.
  public:
	CarlPolytopeT()
		: mFormula()
		, mHalfspaces() {}

	CarlPolytopeT( const CarlPolytopeT& in ) = default;
	CarlPolytopeT( CarlPolytopeT&& in ) = default;

	CarlPolytopeT( const FormulaT<tNumber>& formula, std::size_t dimension = 0 )
		: mFormula( formula )
		, mHalfspaces()
		, mDimension( dimension ) {
#ifdef CARL_OLD_STRUCTURE
		assert( formula.isRealConstraintConjunction() );
#else
		assert( formula.is_real_constraint_conjunction() );
#endif
		if ( dimension == 0 ) {
			detectDimension();
		}
		TRACE( "hypro.representations.carlPolytope", "Constructed P from " << mFormula );
	}

	CarlPolytopeT( const matrix_t<Number>& constraints, const vector_t<Number>& constants );

	CarlPolytopeT( const std::vector<carl::Interval<Number>>& intervals );

	static CarlPolytopeT Empty();

	CarlPolytopeT intersect( const CarlPolytopeT& rhs ) const;

	CarlPolytopeT projectOn( const std::vector<std::size_t>& dimensions ) const;

	CarlPolytopeT assignIntervals( const std::map<std::size_t, carl::Interval<Number>>& ) const {
		WARN( "hypro", "Not implemented." );
		return *this;
	}

	CarlPolytopeT linearTransformation( const matrix_t<Number>& A ) const;

	CarlPolytopeT minkowskiSum( const CarlPolytopeT& ) const {
		assert( false && "NOT IMPLEMENTED" );
		return CarlPolytopeT();
	}

	CarlPolytopeT unite( const CarlPolytopeT& ) const {
		assert( false && "NOT IMPLEMENTED" );
		return CarlPolytopeT();
	}

	CarlPolytopeT affineTransformation( const matrix_t<Number>&, const vector_t<Number>& ) const;

	std::pair<CONTAINMENT, CarlPolytopeT> satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const;

	bool contains( const Point<Number>& point ) const;

	bool contains( const CarlPolytopeT& rhs ) const;

	EvaluationResult<Number> evaluate( const vector_t<Number>& ) const {
		assert( false && "NOT IMPLEMENTED" );
		return EvaluationResult<Number>();
	}

	std::vector<EvaluationResult<Number>> multiEvaluate( const matrix_t<Number>&, bool ) const {
		assert( false && "NOT IMPLEMENTED" );
		return std::vector<EvaluationResult<Number>>();
	}

	std::size_t dimension() const {
		TRACE( "hypro.representations.carlPolytope", "Dimension " << mDimension << ". forced: " << mSpaceDimensionSet );
		return mDimension;
	}
	const FormulaT<tNumber>& getFormula() const { return mFormula; }
	const std::vector<Halfspace<Number>>& getHalfspaces() const;
	std::vector<carl::Interval<Number>> getIntervals() const;

	void setDimension( std::size_t d ) {
		TRACE( "hypro.representations.carlPolytope", "Set dimension to " << d );
		mDimension = d;
		mSpaceDimensionSet = true;
	}
	void addConstraint( const ConstraintT<tNumber>& constraint );
	void addConstraints( const std::vector<ConstraintT<tNumber>>& constraints );
	void addIntervalConstraints( const carl::Interval<Number>& intv, const carl::Variable& var );
	void substituteVariable( carl::Variable oldVar, carl::Variable newVar );

	std::vector<carl::Variable> getVariables() const;
	void eliminateVariable( carl::Variable var );
	void eliminateVariables( const std::vector<carl::Variable>& vars );
	void eliminateVariables( const QEQuery& vars );

	std::vector<Point<Number>> vertices() const;
	matrix_t<Number> matrix() const;
	vector_t<Number> vector() const;
	std::size_t size() const { return mFormula.size(); }
	bool empty() const;
	static representation_name type() { return representation_name::carl_polytope; }

	CarlPolytopeT make_rectangular() const;

	void removeRedundancy();
	void reduceRepresentation();
	void choseOrder( QEQuery& ) { /* right now do nothing - add heuristics later. */
	}

	friend std::ostream& operator<<( std::ostream& out, const CarlPolytopeT<Number, Converter, Setting>& in ) {
		out << in.getFormula();
		return out;
	}

	friend bool operator==( const CarlPolytopeT<Number, Converter, Setting>& lhs, const CarlPolytopeT<Number, Converter, Setting>& rhs ) {
		return lhs.mFormula == rhs.mFormula;
	}

	friend bool operator!=( const CarlPolytopeT<Number, Converter, Setting>& lhs, const CarlPolytopeT<Number, Converter, Setting>& rhs ) {
		return !( lhs.mFormula == rhs.mFormula );
	}

	CarlPolytopeT& operator=( const CarlPolytopeT& in ) {
		this->mFormula = in.mFormula;
		this->mDimension = in.mDimension;
		this->mSpaceDimensionSet = in.mSpaceDimensionSet;
		return *this;
	}

	CarlPolytopeT& operator=( CarlPolytopeT&& in ) {
		this->mFormula = std::move( in.mFormula );
		this->mDimension = in.mDimension;
		this->mSpaceDimensionSet = in.mSpaceDimensionSet;
		return *this;
	}

  private:
	void clearCache() const;
	void detectDimension() const;

	/**
	 * @brief Should only be used in assertions to detect inconsistency in mDimension.
	 */
	bool dimensionWasCorrectlySet() const;
};

/** @} */

}  // namespace hypro

#include "carlPolytope.tpp"
