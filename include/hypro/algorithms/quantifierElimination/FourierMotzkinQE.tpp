/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "FourierMotzkinQE.h"

namespace hypro {
template <typename Number>
FormulaT<Number> FourierMotzkinQE<Number>::eliminateQuantifiers() {
	DEBUG( "hypro.algorithms.qe", "Eliminate in: " << mFormula );
	// iterate over query
	for ( const auto& QuantifierVariablesPair : mQuery ) {
		// we are ignoring the quantifier type
		assert( QuantifierVariablesPair.first == QuantifierType::EXISTS );

		// eliminate one variable after the other
		for ( const auto& var : QuantifierVariablesPair.second ) {
			DEBUG( "hypro.algorithms.qe", "Elimiate " << var );

			auto bounds = findBounds( var );
			// combine all lower-upper bound pairs.
			FormulasT<Number> newConstraints;
			if ( !bounds[2].empty() ) {
				DEBUG( "hypro.algorithms.qe", "Found equation(s), substitute." );
				newConstraints = substituteEquations( bounds, var );
			} else {
				DEBUG( "hypro.algorithms.qe", "Create lower-upper bound pairs." );
				newConstraints = createNewConstraints( bounds, var );
			}

			// add all constraints which are not containing var to newConstraints
			for ( const auto formulaIt : bounds[3] ) {
				assert( getType( formulaIt ) == carl::FormulaType::CONSTRAINT );
				newConstraints.emplace_back( formulaIt );
			}

			// assemble new formula
			mFormula = FormulaT<Number>( carl::FormulaType::AND, newConstraints );
			DEBUG( "hypro.algorithms.qe", "Done elimiating " << var << ", new formula size: " << mFormula.size() << ", new formula: " << mFormula );
		}
	}

	DEBUG( "hypro.algorithms.qe", "Formula after elimination: " << mFormula );

	return mFormula;
}

template <typename Number>
typename FourierMotzkinQE<Number>::FormulaPartition FourierMotzkinQE<Number>::findBounds(
	  const carl::Variable& variable ) {
	TRACE( "hypro.algorithms.qe", "Find bounds in " << mFormula );
	// result vector initialized with three subsets
	typename FourierMotzkinQE<Number>::FormulaPartition res{ 4, std::vector<FormulaT<Number>>() };
	// corner-cases
	if ( !isNary( mFormula ) && getType( mFormula ) != carl::FormulaType::CONSTRAINT ) {
		// if any other case happens, this should not be
		assert( isFalse( mFormula ) || isTrue( mFormula ) );
		return res;
	}

	// if the formula only contains one constraint, check for occurence of the variable.
	if ( getType( mFormula ) == carl::FormulaType::CONSTRAINT ) {
		if ( !hasVariable( mFormula.constraint(), variable ) ) {
			res[3].push_back( mFormula );
		} else {
			if ( mFormula.constraint().relation() == carl::Relation::EQ ) {
				res[2].push_back( mFormula );
			} else if ( isLinearLowerBound( mFormula.constraint(), variable ) ) {
				res[0].push_back( mFormula );
			} else {
				res[1].push_back( mFormula );
			}
		}
		return res;
	}

	// More than one constaint: search formula to find bounds
	for ( auto formulaIt = mFormula.begin(); formulaIt != mFormula.end(); ++formulaIt ) {
		assert( getType( *formulaIt ) == carl::FormulaType::CONSTRAINT );
		if ( hasVariable( ( *formulaIt ).constraint(), variable ) ) {
			if ( ( *formulaIt ).constraint().relation() == carl::Relation::EQ ) {
				res[2].push_back( *formulaIt );
			} else if ( isLinearLowerBound( ( *formulaIt ).constraint(), variable ) ) {
				res[0].push_back( *formulaIt );
			} else {
				res[1].push_back( *formulaIt );
			}
		} else {
			res[3].push_back( *formulaIt );
		}
	}

	return res;
}

template <typename Number>
FormulasT<Number> FourierMotzkinQE<Number>::createNewConstraints(
	  const typename FourierMotzkinQE<Number>::FormulaPartition& bounds, carl::Variable v ) {
	FormulasT<Number> constraints;

	// combine all pairs of lower and upper bounds.
	for ( const auto& lowerBnd : bounds[0] ) {
		for ( const auto& upperBnd : bounds[1] ) {
			TRACE( "hypro.algorithms.qe", "Combine " << ( lowerBnd ) << " and " << ( upperBnd ) );

			PolyT<Number> lhs = getRemainder( lowerBnd.constraint(), v, true );

			TRACE( "hypro.algorithms.qe", "Lhs is " << lhs );

			PolyT<Number> rhs = getRemainder( upperBnd.constraint(), v, false );

			TRACE( "hypro.algorithms.qe", "Rhs is " << rhs );

			constraints.emplace_back( FormulaT<Number>( ConstraintT<Number>( lhs - rhs, carl::Relation::LEQ ) ) );

			TRACE( "hypro.algorithms.qe", "Created new constraint: " << constraints.back() );
		}
	}

	// copy the rest
	for ( const auto& c : bounds[2] ) {
		constraints.emplace_back( c );
	}
	for ( const auto& c : bounds[3] ) {
		constraints.emplace_back( c );
	}

	return constraints;
}

template <typename Number>
FormulasT<Number> FourierMotzkinQE<Number>::substituteEquations(
	  const typename FourierMotzkinQE<Number>::FormulaPartition& bounds, carl::Variable v ) {
	assert( !bounds[2].empty() );
	FormulasT<Number> constraints;

	// check if equations are pairwise equal - if not return false, otherwise use one of the equations.
	// Todo: This test is not correct: having x = 3 + y and x = 3 would fail this test but still is satisfiable when y
	// is existentially quantified or if it is all-quantified it is after x.
	FormulasT<Number> substitutes;
	if ( bounds[2].size() == 1 ) {
		substitutes.push_back( FormulaT<Number>( bounds[2].front() ) );
	} else {
		for ( auto f = bounds[2].begin(); f != bounds[2].end(); ++f ) {
			assert( getType( *f ) == carl::FormulaType::CONSTRAINT );
			assert( f->constraint().relation() == carl::Relation::EQ );

			for ( auto g = std::next( f ); g != bounds[2].end(); ++g ) {
				assert( getType( *g ) == carl::FormulaType::CONSTRAINT );
				assert( g->constraint().relation() == carl::Relation::EQ );
				FormulaT<Number> newEq =
					  FormulaT<Number>( f->constraint().lhs() - g->constraint().lhs(), carl::Relation::EQ );

				// 1st case: equalities contradict each other - quit substitution.
				if ( getType( newEq ) == carl::FormulaType::FALSE ) {
					constraints.clear();
					constraints.emplace_back( FormulaT<Number>( carl::FormulaType::FALSE ) );
					return constraints;
				} else if ( getType( newEq ) == carl::FormulaType::TRUE ) {
					// both equations are completely equal, just take one.
					substitutes.push_back( FormulaT<Number>( *f ) );
				} else {
					// the equations are no equal but involve different variables, e.g. [eliminate x]: x = y AND x = z
					substitutes.push_back( FormulaT<Number>( *f ) );
					substitutes.push_back( FormulaT<Number>( *g ) );
					// Todo: We could add the constraint y = z.
				}
			}
		}
	}

	// substitute
	for ( const auto& f : substitutes ) {
		TRACE( "hypro.algorithms.qe", "Substitute variable " << v << " using: " << f );
		assert( getType( f ) == carl::FormulaType::CONSTRAINT );
		PolyT<Number> substitute = -( f.constraint().lhs() - f.constraint().coefficient( v, 1 ) * v ) / f.constraint().coefficient( v, 1 );
		TRACE( "hypro.algorithms.qe", "Substitution polynomial is: " << substitute );
		// lower bounds
		for ( auto fc : bounds[0] ) {
			assert( getType( fc ) == carl::FormulaType::CONSTRAINT );
			constraints.emplace_back( hypro::substitute( fc.constraint().lhs(), v, substitute ),
									  // constraints.emplace_back( fc.constraint().lhs().substitute( v, substitute ),
									  fc.constraint().relation() );
			TRACE( "hypro.algorithms.qe", "Substitute lower bound " << fc << " to " << constraints.back() );
		}
		// upper bounds
		for ( auto fc : bounds[1] ) {
			assert( getType( fc ) == carl::FormulaType::CONSTRAINT );
			constraints.emplace_back( hypro::substitute( fc.constraint().lhs(), v, substitute ),
									  // constraints.emplace_back( fc.constraint().lhs().substitute( v, substitute ),
									  fc.constraint().relation() );
			TRACE( "hypro.algorithms.qe", "Substitute upper bound " << fc << " to " << constraints.back() );
		}
	}

	return constraints;
}

template <typename Number>
PolyT<Number> FourierMotzkinQE<Number>::getRemainder( const ConstraintT<Number>& c, carl::Variable v, bool ) {
	auto tmp = c.lhs() / c.coefficient( v, 1 );	 // now v has the coefficient 1.
	return -tmp;
	/*
	if(isLowerBnd) {
		if(c.relation() == carl::Relation::LESS || c.relation() == carl::Relation::LEQ) {
			return (c.lhs() - c.coefficient(v,1)*v)/c.coefficient(v,1);
		} else {
			return -((c.lhs() - c.coefficient(v,1)*v)/c.coefficient(v,1));
		}
	} else {
		if(c.relation() == carl::Relation::LESS || c.relation() == carl::Relation::LEQ) {
			return -((c.lhs() - c.coefficient(v,1)*v)/c.coefficient(v,1));
		} else {
			return (c.lhs() - c.coefficient(v,1)*v)/c.coefficient(v,1);
		}
	}
	*/
}

template <typename Number>
bool FourierMotzkinQE<Number>::isLinearLowerBound( const ConstraintT<Number>& c, carl::Variable v ) {
	assert( hasVariable( c, v ) );
	assert( isNumber( c.coefficient( v, 1 ) ) );

	// is linear lower bound when the coefficient is > 0 and the relation is LEQ or LESS, or if the coefficient is < 0
	// and the relation is GEQ or GREATER.
	if ( ( ( c.relation() == carl::Relation::LEQ || c.relation() == carl::Relation::LESS ) &&
		   c.coefficient( v, 1 ) < 0 ) ||
		 ( ( c.relation() == carl::Relation::GEQ || c.relation() == carl::Relation::GREATER ) &&
		   c.coefficient( v, 1 ) > 0 ) ) {
		// std::cout << c << " is lower bound." << std::endl;
		return true;
	}
	// std::cout << c << " is no lower bound." << std::endl;
	return false;
}

}  // namespace hypro
