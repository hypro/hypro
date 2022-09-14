/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "carlPolytope.h"

namespace hypro {

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting>::CarlPolytopeT( const matrix_t<Number>& constraints, const vector_t<Number>& constants ) {
	TRACE( "hypro.representations.carlPolytope", "Construct P from " << constraints << " and " << constants );
	FormulasT<tNumber> newConstraints = halfspacesToFormulas<tNumber, Number>( constraints, constants );

	mFormula = FormulaT<tNumber>{ carl::FormulaType::AND, newConstraints };
	TRACE( "hypro.representations.carlPolytope", "Result formula: " << mFormula );
	detectDimension();
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting>::CarlPolytopeT( const std::vector<carl::Interval<Number>>& intervals ) {
	TRACE( "hypro.representations.carlPolytope", "Construct P from interval vector." );
	FormulasT<tNumber> newConstraints;

	for ( std::size_t i = 0; i < intervals.size(); ++i ) {
		auto tmp = intervalToFormulas<tNumber, Number>( intervals[i], i );
		newConstraints.insert( newConstraints.end(), tmp.begin(), tmp.end() );
	}
	mFormula = FormulaT<tNumber>{ carl::FormulaType::AND, newConstraints };
	TRACE( "hypro.representations.carlPolytope", "Result formula: " << mFormula );
	detectDimension();
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting> CarlPolytopeT<Number, Converter, Setting>::Empty() {
	auto res = CarlPolytopeT();
	res.setEmptyState( SETSTATE::EMPTY );
	return res;
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting> CarlPolytopeT<Number, Converter, Setting>::intersect( const CarlPolytopeT<Number, Converter, Setting>& rhs ) const {
	TRACE( "hypro.representations.carlPolytope", "Intersect " << *this << " and " << rhs );
	// assert(mFormula.isConstraintConjunction());
	// assert(rhs.getFormula().isConstraintConjunction());
	//  test for emptiness
	if ( this->empty() || rhs.empty() ) {
		return Empty();
	}

	// collect constraints
	std::vector<ConstraintT<tNumber>> newConstraints;
	getConstraints( mFormula, newConstraints );
	getConstraints( rhs.getFormula(), newConstraints );

	return CarlPolytopeT<Number, Converter, Setting>( FormulaT<tNumber>( carl::FormulaType::AND, constraintsToFormulas( newConstraints ) ) );
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting> CarlPolytopeT<Number, Converter, Setting>::projectOn( const std::vector<std::size_t>& dimensions ) const {
	TRACE( "hypro.representations.carlPolytope", "This: " << *this << " on dimensions " << dimensions );
	if ( this->empty() ) {
		return Empty();
	}
	// make sure the number of constraints allows for a projection via v-poly conversion
	matrix_t<Number> constraints = this->matrix();
	if ( constraints.rows() < constraints.cols() ) {
		assert( false );
		std::cout << "SHOULD NOT BE REACHABLE" << std::endl;
		return Empty();
	} else {
		// projection by means of a linear transformation
		matrix_t<Number> projectionMatrix = matrix_t<Number>::Zero( this->dimension(), this->dimension() );
		for ( auto i : dimensions ) {
			projectionMatrix( i, i ) = 1;
		}
		return this->linearTransformation( projectionMatrix );
	}
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting> CarlPolytopeT<Number, Converter, Setting>::linearTransformation( const matrix_t<Number>& A ) const {
	TRACE( "hypro.representations.carlPolytope", "P' = A*P, A:" << std::endl
																<< A << ", P: " << *this );
	if ( A.nonZeros() == 0 ) {
		return CarlPolytopeT<Number, Converter, Setting>::Empty();
	}
	if ( !this->empty() ) {
		Eigen::FullPivLU<matrix_t<Number>> lu( A );
		// if A has full rank, we can simply re-transform, otherwise use v-representation.
		if ( lu.rank() == A.rows() ) {
			TRACE( "hypro.representations.carlPolytope", "A has full rank - do not use v-conversion." );
			matrix_t<Number> constraints = this->matrix();
			vector_t<Number> constants = this->vector();
			assert( ( CarlPolytopeT<Number, Converter, Setting>( constraints * A.inverse(), constants ).size() == this->size() ) );
			return CarlPolytopeT<Number, Converter, Setting>( constraints * A.inverse(), constants );
		} else {
			TRACE( "hypro.representations.carlPolytope", "Use Fourier-Motzkin elimination for linear transformation." );
			auto problem_description = mFormula;
			std::size_t dim = this->dimension();
			matrix_t<Number> trafo = matrix_t<Number>::Zero( dim, dim * 2 );
			trafo.block( 0, 0, dim, dim ) = A;
			trafo.block( 0, dim, dim, dim ) = -matrix_t<Number>::Identity( dim, dim );
			FormulasT<tNumber> single_translations;
			for ( Eigen::Index row = 0; row < dim; ++row ) {
				single_translations.push_back( FormulaT<tNumber>{ rowToConstraint<tNumber, Number>( vector_t<Number>( trafo.row( row ) ), Number( 0 ), carl::Relation::EQ ) } );
			}
			FormulaT<tNumber> translation_formula{ carl::FormulaType::AND, single_translations };
			problem_description = FormulaT<tNumber>( carl::FormulaType::AND, problem_description, translation_formula );
			// assemble variables
			std::vector<carl::Variable> variables;
			for ( std::size_t i = 0; i < dim; ++i ) {
				variables.push_back( VariablePool::getInstance().carlVarByIndex( i ) );
			}

			FourierMotzkinQE<tNumber> qe_method{ problem_description, QEQuery{ { QuantifierType::EXISTS, variables } } };
			auto result = qe_method.eliminateQuantifiers();

			// substitute variables back
			for ( std::size_t i = 0; i < dim; ++i ) {
				result = substitute( result, VariablePool::getInstance().carlVarByIndex( dim + i ), FormulaT<tNumber>::PolynomialType( VariablePool::getInstance().carlVarByIndex( i ) ) );
			}
			return CarlPolytopeT{ result, dim };
		}
	} else {
		return *this;
	}
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting> CarlPolytopeT<Number, Converter, Setting>::affineTransformation( const matrix_t<Number>& A, const vector_t<Number>& b ) const {
	TRACE( "hypro.representations.carlPolytope", "Use Fourier-Motzkin elimination for affine transformation." );
	auto problem_description = mFormula;
	std::size_t dim = this->dimension();
	std::size_t rows = dim;
	std::size_t cols = dim * 2;
	std::size_t arows = A.rows();
	assert( A.rows() == dim );
	assert( A.cols() == dim );
	matrix_t<tNumber> trafo = matrix_t<tNumber>::Zero( rows, cols );
	trafo.block( 0, 0, rows, dim ) = convert<Number, tNumber>( A );
	trafo.block( 0, dim, dim, dim ) = -matrix_t<tNumber>::Identity( dim, dim );
	FormulasT<tNumber> single_translations;
	for ( Eigen::Index row = 0; row < dim; ++row ) {
		single_translations.push_back( FormulaT<tNumber>{ rowToConstraint<tNumber>( vector_t<tNumber>( trafo.row( row ) ), carl::convert<Number, tNumber>( -b( row ) ), carl::Relation::EQ ) } );
		TRACE( "hypro.representations.carlPolytope", "Add translation constraint " << single_translations.back() << " originating from " << vector_t<tNumber>( trafo.row( row ) ) << " and " << b( row ) );
	}
	FormulaT<tNumber> translation_formula{ carl::FormulaType::AND, single_translations };
	problem_description = FormulaT<tNumber>( carl::FormulaType::AND, problem_description, translation_formula );
	// assemble variables
	std::vector<carl::Variable> variables;
	for ( std::size_t i = 0; i < dim; ++i ) {
		variables.push_back( VariablePool::getInstance().carlVarByIndex( i ) );
	}

	FourierMotzkinQE<tNumber> qe_method{ problem_description, QEQuery{ { QuantifierType::EXISTS, variables } } };
	auto result = qe_method.eliminateQuantifiers();

	// substitute variables back
	for ( std::size_t i = 0; i < dim; ++i ) {
		result = substitute( result, VariablePool::getInstance().carlVarByIndex( dim + i ), PolyT<tNumber>( VariablePool::getInstance().carlVarByIndex( i ) ) );
	}
	return CarlPolytopeT{ result, dim };
}

template <typename Number, typename Converter, typename Setting>
std::pair<CONTAINMENT, CarlPolytopeT<Number, Converter, Setting>> CarlPolytopeT<Number, Converter, Setting>::satisfiesHalfspaces( const matrix_t<Number>& _mat, const vector_t<Number>& _vec ) const {
	DEBUG( "hypro.representations.carlPolytope", "Hsps " << _mat << std::endl
														 << _vec << " and this " << *this );
	auto resPoly = this->intersect( CarlPolytopeT<Number, Converter, Setting>( _mat, _vec ) );
	resPoly.removeRedundancy();

	TRACE( "hypro.representations.carlPolytope", "Resulting polytope " << resPoly );

	if ( resPoly == *this ) {
		return std::make_pair( CONTAINMENT::FULL, *this );
	}

	if ( resPoly.empty() ) {
		return std::make_pair( CONTAINMENT::NO, resPoly );
	}
	return std::make_pair( CONTAINMENT::PARTIAL, resPoly );
}

template <typename Number, typename Converter, typename Setting>
bool CarlPolytopeT<Number, Converter, Setting>::contains( const Point<Number>& point ) const {
	return std::all_of( getHalfspaces().begin(), getHalfspaces().end(), [&point]( const auto& hsp ) { return hsp.contains( point ); } );
}

template <typename Number, typename Converter, typename Setting>
bool CarlPolytopeT<Number, Converter, Setting>::contains( const CarlPolytopeT& rhs ) const {
	auto lhs_converted = HPolytopeT<Number, Converter, HPolytopeSetting>{ this->matrix(), this->vector() };
	auto rhs_converted = HPolytopeT<Number, Converter, HPolytopeSetting>{ rhs.matrix(), rhs.vector() };
	return lhs_converted.contains( rhs_converted );
}

template <typename Number, typename Converter, typename Setting>
const std::vector<Halfspace<Number>>& CarlPolytopeT<Number, Converter, Setting>::getHalfspaces() const {
	if ( this->empty() ) {
		mHalfspaces.clear();
		vector_t<Number> normal = vector_t<Number>::Ones( 1 );
		mHalfspaces.emplace_back( normal, Number( 1 ) );
		mHalfspaces.emplace_back( -normal, Number( -2 ) );
	}
	if ( mHalfspaces.empty() ) {
		mHalfspaces = computeHalfspaces<tNumber, Number>( mFormula, this->dimension() );
	}
	TRACE( "hypro.representations.carlPolytope", "Computed halfspaces.." );
	return mHalfspaces;
}

template <typename Number, typename Converter, typename Setting>
std::vector<carl::Interval<Number>> CarlPolytopeT<Number, Converter, Setting>::getIntervals() const {
	if ( this->empty() ) {
		std::vector<carl::Interval<Number>> res;
		res.emplace_back( createEmptyInterval<Number>() );
		return res;
	}
	// Note: Alternatively use FM-elimination.
	Optimizer<Number> opt{ this->matrix(), this->vector() };
	auto dim = Eigen::Index( this->dimension() );
	// use box-template, first normal points towards dimension, then negative
	auto directions = computeTemplate<Number>( dim, 4 );
	std::vector<EvaluationResult<Number>> evalResult;
	std::for_each( directions.begin(), directions.end(),
				   [&evalResult, &opt]( const auto& in ) { evalResult.emplace_back( std::move( opt.evaluate( in, true ) ) ); } );

	std::vector<carl::Interval<Number>> res;

	// assemble intervals from evaluation results
	assert( Eigen::Index( evalResult.size() ) == 2 * dim );
	for ( Eigen::Index d = 0; d < dim; ++d ) {
		res.emplace_back( -evalResult[2 * d + 1].supportValue, evalResult[2 * d].supportValue );
	}
	return res;
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::addConstraint( const ConstraintT<tNumber>& constraint ) {
	// reset Half-space cache
	mHalfspaces.clear();
	// if not empty, reset cache
	if ( mEmptyState != SETSTATE::EMPTY ) {
		mEmptyState = SETSTATE::UNKNOWN;
	} else {
		return;
	}
	// add constraint to formula
	std::vector<ConstraintT<tNumber>> constraints;
	getConstraints( mFormula, constraints );
	constraints.push_back( constraint );
	mFormula = FormulaT<tNumber>( carl::FormulaType::AND, constraintsToFormulas( constraints ) );
	detectDimension();
	TRACE( "hypro.representations.carlPolytope", "After adding a constraint " << *this );
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::addConstraints( const std::vector<ConstraintT<tNumber>>& constraints ) {
	std::for_each( std::begin( constraints ), std::end( constraints ), [&]( const auto& c ) { this->addConstraint( c ); } );
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::addIntervalConstraints( const carl::Interval<Number>& intv, const carl::Variable& var ) {
	TRACE( "hypro.representations.carlPolytope", "Input interval " << intv << " for variable " << var );
	auto tmp = intervalToFormulas<tNumber, Number>( intv, var );
	ConstraintsT<tNumber> newConstraints;
	for ( const auto& f : tmp ) {
		ConstraintsT<tNumber> tmpConstraints;
		getConstraints( f, tmpConstraints );
		for ( const auto& c : tmpConstraints ) {
			newConstraints.emplace_back( c );
			TRACE( "hypro.representations.carlPolytope", "Add new interval constraint " << c );
		}
	}
	this->addConstraints( newConstraints );
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::substituteVariable( carl::Variable oldVar, carl::Variable newVar ) {
	if ( this->empty() ) {
		return;
	}
	// reset half-space cache
	mHalfspaces.clear();
	// substitute
	mFormula = substitute( mFormula, oldVar, PolyT<tNumber>( newVar ) );
	TRACE( "hypro.representations.carlPolytope", "After substituting " << oldVar << " by " << newVar << ": " << *this );
	detectDimension();
}

template <typename Number, typename Converter, typename Setting>
std::vector<carl::Variable> CarlPolytopeT<Number, Converter, Setting>::getVariables() const {
	return std::vector<carl::Variable>{ mFormula.variables().begin(), mFormula.variables().end() };
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::eliminateVariable( carl::Variable var ) {
	DEBUG( "hypro.representations.carlPolytope", "Eliminate variable " << var << " in " << mFormula );
	if ( this->empty() ) {
		return;
	}
	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, std::vector<carl::Variable>( { var } ) ) );
	// std::cout << "Eliminate ... ";
	mFormula = eliminateQuantifiers( mFormula, query );
	// std::cout << "done. Remove redundancy ... ";
	// this->removeRedundancy();
	// std::cout << "done." << std::endl;
	detectDimension();
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::eliminateVariables( const std::vector<carl::Variable>& vars ) {
	DEBUG( "hypro.representations.carlPolytope", "Eliminate variables in " << mFormula );
	if ( this->empty() ) {
		return;
	}
	QEQuery query;
	query.emplace_back( std::make_pair( QuantifierType::EXISTS, vars ) );
	mFormula = eliminateQuantifiers( mFormula, query );
	detectDimension();
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::eliminateVariables( const QEQuery& vars ) {
	DEBUG( "hypro.representations.carlPolytope", "Eliminate variables in " << mFormula );
	if ( this->empty() ) {
		return;
	}
	// std::cout << "Eliminate ... ";
	mFormula = eliminateQuantifiers( mFormula, vars );
	// std::cout << "done." << std::endl;
	detectDimension();
}

template <typename Number, typename Converter, typename Setting>
std::vector<Point<Number>> CarlPolytopeT<Number, Converter, Setting>::vertices() const {
	DEBUG( "hypro.representations.carlPolytope", "Compute vertices from " << *this );
	if ( this->empty() ) {
		return std::vector<Point<Number>>{};
	}
	auto hpoly = Converter::toHPolytope( *this );
	DEBUG( "hypro.representations.carlPolytope", "As H-polytope: " << hpoly );
	return hpoly.vertices();
}

template <typename Number, typename Converter, typename Setting>
matrix_t<Number> CarlPolytopeT<Number, Converter, Setting>::matrix() const {
	if ( isFalse( mFormula ) ) {
		return matrix_t<Number>( 0, 0 );
	}
	// assert(dimensionWasCorrectlySet());
	detectDimension();
	matrix_t<Number> res = matrix_t<Number>( mFormula.size(), dimension() );
	std::vector<ConstraintT<tNumber>> constraints;
	getConstraints( mFormula, constraints );
	std::size_t i = 0;
	for ( const auto& c : constraints ) {
		res.row( i ) = constraintNormal<tNumber, Number>( c, dimension() );
		if ( c.relation() == carl::Relation::EQ ) {
			// res.conservativeResize(res.rows()+1, Eigen::NoChange_t);
			res.conservativeResize( res.rows() + 1, res.cols() );
			++i;
			res.row( i ) = -constraintNormal<tNumber, Number>( c, dimension() );
		}
		++i;
	}
	return res;
}

template <typename Number, typename Converter, typename Setting>
vector_t<Number> CarlPolytopeT<Number, Converter, Setting>::vector() const {
	if ( isFalse( mFormula ) ) {
		return vector_t<Number>( 0 );
	}
	// assert(dimensionWasCorrectlySet());
	detectDimension();
	vector_t<Number> res = vector_t<Number>( mFormula.size() );
	std::vector<ConstraintT<tNumber>> constraints;
	getConstraints( mFormula, constraints );
	std::size_t i = 0;
	for ( const auto& c : constraints ) {
		// widening: check if origin contained. If so, increase abs of offset, else, reduce abs. value.
		res( i ) = normalizedOffset<tNumber, Number>( c );	// + computeWidening<tNumber,Number>(c);
		if ( c.relation() == carl::Relation::EQ ) {
			res.conservativeResize( res.rows() + 1 );
			++i;
			res( i ) = -normalizedOffset<tNumber, Number>( c );	 // - computeWidening<tNumber,Number>(c);
		}
		++i;
	}
	return res;
}

template <typename Number, typename Converter, typename Setting>
bool CarlPolytopeT<Number, Converter, Setting>::empty() const {
	if ( mEmptyState == SETSTATE::UNKNOWN ) {
		if ( isFalse( mFormula ) ) {
			mEmptyState = SETSTATE::EMPTY;
			return true;
		}
		// Attention, we assume the formula is only one constraint.
		if ( mFormula.size() <= 1 ) {
			mEmptyState = mFormula.size() == 0 ? SETSTATE::UNIVERSAL : SETSTATE::NONEMPTY;
			return false;
		}
		Optimizer<Number> opt = Optimizer<Number>( this->matrix(), this->vector() );
		mEmptyState = opt.checkConsistency() ? SETSTATE::NONEMPTY : SETSTATE::EMPTY;
	}
	return mEmptyState == SETSTATE::EMPTY;
}

template <typename Number, typename Converter, typename Setting>
CarlPolytopeT<Number, Converter, Setting> CarlPolytopeT<Number, Converter, Setting>::make_rectangular() const {
	// Idea: Use FM-elimination to obtain all intervals for all variables consecutively.
	// Alternative: Use optimizer (current version).

	Optimizer<Number> opt{ this->matrix(), this->vector() };
	// use box-template
	auto directions = computeTemplate<Number>( this->dimension(), 4 );
	std::vector<EvaluationResult<Number>> evalResult;
	for ( const auto& dir : directions ) {
		evalResult.emplace_back( std::move( opt.evaluate( dir, true ) ) );
	}
	vector_t<Number> constants = vector_t<Number>( directions.size() );
	Eigen::Index pos = 0;
	for ( const auto& res : evalResult ) {
		constants( pos ) = res.supportValue;
		++pos;
	}
	return CarlPolytopeT<Number, Converter, Setting>( createMatrix( directions ), constants );
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::removeRedundancy() {
	if ( mFormula.size() <= 1 || this->empty() ) {
		return;
	}
	Optimizer<Number> opt = Optimizer<Number>( this->matrix(), this->vector() );
	std::vector<ConstraintT<tNumber>> constraints;
	getConstraints( mFormula, constraints );
	auto redundantConstraints = opt.redundantConstraints();
	for ( auto it = redundantConstraints.rbegin(); it != redundantConstraints.rend(); ++it ) {
		constraints.erase( constraints.begin() + *it );
	}
	mFormula = FormulaT<tNumber>( carl::FormulaType::AND, constraintsToFormulas( constraints ) );
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::reduceRepresentation() {
	if ( this->empty() ) {
		return;
	}
	Optimizer<Number> opt = Optimizer<Number>( this->matrix(), this->vector() );
	auto directions = computeTemplate<Number>( this->dimension(), 4 );
	matrix_t<Number> constraints = createMatrix( directions );
	vector_t<Number> constants = vector_t<Number>( constraints.rows() );
	Eigen::Index row = 0;
	for ( const auto& d : directions ) {
		auto evalRes = opt.evaluate( vector_t<Number>( d ), false );
		assert( evalRes.errorCode != SOLUTION::UNKNOWN );
		// if the polytope is empty, directly return empty polytope.
		if ( evalRes.errorCode == SOLUTION::INFEAS ) {
			mEmptyState = SETSTATE::EMPTY;
			return;
		}
		// if the polytope is unbounded, remove constraint.
		if ( evalRes.errorCode == SOLUTION::INFTY ) {
			constraints.conservativeResize( constraints.rows() - 1, constraints.cols() );
			constants.conservativeResize( constants.rows() - 1 );
			continue;
		}
		assert( evalRes.errorCode == SOLUTION::FEAS );
		constants( row ) = evalRes.supportValue;
	}
	FormulasT<tNumber> newConstraints = halfspacesToFormulas<tNumber, Number>( constraints, constants );

	mFormula = FormulaT<tNumber>{ carl::FormulaType::AND, newConstraints };
	TRACE( "hypro.representations.carlPolytope", "Result formula: " << mFormula );
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::clearCache() const {
	// reset half-space cache
	mHalfspaces.clear();
	// reset empty-cache
	mEmptyState = SETSTATE::UNKNOWN;
}

template <typename Number, typename Converter, typename Setting>
void CarlPolytopeT<Number, Converter, Setting>::detectDimension() const {
	if ( !mSpaceDimensionSet ) {
		std::size_t d = 0;
		// get maximal state space dimension based on the variables used in mFormula.
		std::for_each( mFormula.variables().begin(), mFormula.variables().end(), [&]( const carl::Variable& v ) { d = std::max( d, VariablePool::getInstance().id( v ) ); } );
		mDimension = d + 1;	 // add one as we start counting from zero.
		TRACE( "hypro.representations.carlPolytope", "Set dimension to " << mDimension );
	}
}

template <typename Number, typename Converter, typename Setting>
bool CarlPolytopeT<Number, Converter, Setting>::dimensionWasCorrectlySet() const {
	bool res = true;
#ifndef NDEBUG
	auto tmpDim = mDimension;
	std::size_t d = 0;
	// get maximal state space dimension based on the variables used in mFormula.
	std::for_each( mFormula.variables().begin(), mFormula.variables().end(), [&]( const carl::Variable& v ) { d = std::max( d, VariablePool::getInstance().id( v ) ); } );
	++d;
	if ( tmpDim < d ) {
		// std::cout << "Dimension of this " << *this << " was set to " << tmpDim << " but actually is " << d << std::endl;
		return false;
	}
#endif
	return res;
}

}  // namespace hypro
