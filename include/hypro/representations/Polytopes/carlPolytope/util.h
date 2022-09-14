/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "../../../carlTypes.h"
#include "../../../datastructures/Halfspace.h"
#include "../../../util/VariablePool.h"
#include "../../../util/adaptions_carl/adaptions_formula.h"

namespace hypro {

template <typename N, typename D>
inline ConstraintT<N> rowToConstraint( const vector_t<D>& normal, const D& offset, carl::Relation rel = carl::Relation::LEQ ) {
	PolyT<N> p;
	for ( Eigen::Index col = 0; col < normal.rows(); ++col ) {
		p += carl::convert<D, N>( normal( col ) ) *
			 PolyT<N>( VariablePool::getInstance().carlVarByIndex( col ) );
	}
	p -= carl::convert<D, N>( offset );
	return ConstraintT<N>( p, rel );
}

template <typename N, typename D>
inline FormulasT<N> halfspacesToFormulas( const matrix_t<D>& constraints, const vector_t<D>& constants ) {
	FormulasT<N> newConstraints;

	for ( Eigen::Index row = 0; row < constraints.rows(); ++row ) {
		newConstraints.emplace_back( FormulaT<N>( rowToConstraint<N, D>( vector_t<D>( constraints.row( row ) ), constants( row ), carl::Relation::LEQ ) ) );
	}
	return newConstraints;
}

template <typename N, typename D>
inline FormulasT<N> equationsToFormulas( const matrix_t<D>& constraints, const vector_t<D>& constants ) {
	FormulasT<N> newConstraints;

	for ( Eigen::Index row = 0; row < constraints.rows(); ++row ) {
		newConstraints.emplace_back( FormulaT<N>( rowToConstraint<N, D>( vector_t<D>( constraints.row( row ) ), constants( row ), carl::Relation::EQ ) ) );
	}
	return newConstraints;
}

template <typename N, typename D>
inline ConstraintsT<N> halfspacesToConstraints( const matrix_t<D>& constraints, const vector_t<D>& constants ) {
	ConstraintsT<N> newConstraints;

	for ( Eigen::Index row = 0; row < constraints.rows(); ++row ) {
		newConstraints.emplace_back( rowToConstraint<N, D>( constraints.row( row ), constants( row ), carl::Relation::LEQ ) );
	}
	return newConstraints;
}

template <typename N, typename D>
inline ConstraintsT<N> equationsToConstraints( const matrix_t<D>& constraints, const vector_t<D>& constants ) {
	ConstraintsT<N> newConstraints;

	for ( Eigen::Index row = 0; row < constraints.rows(); ++row ) {
		newConstraints.emplace_back( rowToConstraint<N, D>( constraints.row( row ), constants( row ), carl::Relation::EQ ) );
	}
	return newConstraints;
}

template <typename N>
inline FormulasT<N> constraintsToFormulas( const std::vector<ConstraintT<N>>& in ) {
	FormulasT<N> res;
	std::for_each( in.begin(), in.end(), [&]( auto in ) { res.emplace_back( FormulaT<N>( in ) ); } );
	return res;
}

template <typename N, typename D>
FormulasT<N> intervalToFormulas( const carl::Interval<D>& interval, const carl::Variable& var ) {
	TRACE( "hypro.representations.carlPolytope", "Create interval constraints for variable " << var );
	FormulasT<N> res;
	res.emplace_back( ConstraintT<N>( PolyT<N>( var ) - PolyT<N>( carl::convert<D, N>( interval.lower() ) ),
									  carl::Relation::GEQ ) );
	res.emplace_back( ConstraintT<N>( PolyT<N>( var ) - PolyT<N>( carl::convert<D, N>( interval.upper() ) ),
									  carl::Relation::LEQ ) );
	return res;
}

template <typename N, typename D>
FormulasT<N> intervalToFormulas( const carl::Interval<D>& interval, std::size_t variableIndex ) {
	TRACE( "hypro.representations.carlPolytope", "Create interval constraints for variable index " << variableIndex );
	return intervalToFormulas<N, D>( interval, VariablePool::getInstance().carlVarByIndex( variableIndex ) );
}

template <typename N, typename D>
vector_t<D> constraintNormal( const ConstraintT<N>& c, std::size_t dim ) {
	TRACE( "hypro.representations.carlPolytope", "Compute normal from " << c << " with dimension " << dim );
	vector_t<D> normal = vector_t<D>::Zero( dim );
	for ( const auto& var : c.variables() ) {
		assert( VariablePool::getInstance().hasDimension( getVar( var ) ) );
		assert( c.lhs().isLinear() );
		assert( c.lhs().coeff( getVar( var ), 1 ).isNumber() );
		TRACE( "hypro.representations.carlPolytope",
			   "Variable " << getVar( var ) << " with dimension "
						   << VariablePool::getInstance().id( getVar( var ) ) );
		if ( c.relation() == carl::Relation::LEQ || c.relation() == carl::Relation::LESS ||
			 c.relation() == carl::Relation::EQ ) {
			normal( VariablePool::getInstance().id( getVar( var ) ) ) =
				  carl::convert<N, D>( constantPart( c.lhs().coeff( getVar( var ), 1 ) ) );
		} else {
			normal( VariablePool::getInstance().id( getVar( var ) ) ) =
				  -carl::convert<N, D>( constantPart( c.lhs().coeff( getVar( var ), 1 ) ) );
		}
	}
	return normal;
}

template <typename N, typename D>
D normalizedOffset( const ConstraintT<N>& c ) {
	if ( c.relation() == carl::Relation::LEQ || c.relation() == carl::Relation::LESS ||
		 c.relation() == carl::Relation::EQ ) {
		return -carl::convert<N, D>( constantPart( c.lhs() ) );
	} else {
		return carl::convert<N, D>( constantPart( c.lhs() ) );
	}
}

template <typename N, typename D>
std::vector<Halfspace<D>> constraintToHalfspace( const ConstraintT<N>& constraint, std::size_t dim ) {
	TRACE( "hypro.representations.carlPolytope",
		   "Compute half-spaces from " << constraint << " with dimension " << dim );
	std::vector<Halfspace<D>> res;

	D offset = normalizedOffset<N, D>( constraint );
	vector_t<D> normalV = constraintNormal<N, D>( constraint, dim );

	res.emplace_back( Halfspace<D>{ normalV, offset } );
	TRACE( "hypro.representations.carlPolytope", "Hsp: " << res.back() );

	if ( constraint.relation() == carl::Relation::EQ ) {
		res.emplace_back( Halfspace<D>{ -normalV, -offset } );
		TRACE( "hypro.representations.carlPolytope", "Hsp: " << res.back() );
	}

	return res;
}

template <typename N, typename D>
std::vector<Halfspace<D>> computeHalfspaces( const FormulaT<N>& formula, std::size_t dim ) {
	assert( formula.isConstraintConjunction() );

	std::vector<Halfspace<D>> res;
	std::vector<ConstraintT<N>> constraints;
	getConstraints( formula, constraints );

	for ( const auto& c : constraints ) {
		auto tmp = constraintToHalfspace<N, D>( c, dim );
		res.insert( res.end(), tmp.begin(), tmp.end() );
	}

	return res;
}

template <typename N, typename D>
D computeWidening( const ConstraintT<N>& constraint ) {
	if ( constantPart( constraint.lhs() ) == carl::constant_zero<N>().get() ) {
		return 0;
	}

	// check if origin contained
	bool originContained = constantPart( constraint.lhs() ) > 0;
	D widening = 0.0001;
	D normOff = normalizedOffset<N, D>( constraint );

	// if origin contained, increase abs. value of offset
	if ( originContained ) {
		if ( normOff > 0 ) {
			return widening;
		} else {
			return -widening;
		}
	}
	// else reduce abs value of offset

	if ( normOff > 0 ) {
		return -widening;
	} else {
		return widening;
	}
}

}  // namespace hypro
