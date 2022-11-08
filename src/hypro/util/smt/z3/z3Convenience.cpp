/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 12.07.22.
 */

#ifndef HYPRO_Z3CONVENIENCE_H
#define HYPRO_Z3CONVENIENCE_H
#include <hypro/flags.h>
#ifdef HYPRO_USE_Z3
#include "hypro/util/VariablePool.h"
#include "hypro/util/exceptions.h"
#include "hypro/util/linearOptimization/z3/z3Context.h"
#include "hypro/util/smt/SMTSolver.h"
#include "hypro/util/smt/SmtResult.h"

#include <z3++.h>

namespace hypro {

z3::expr toZ3( const FormulaT<tNumber>& inFormula, z3Context& c, std::map<std::size_t, z3::expr>& z3variables ) {
	switch ( getType( inFormula ) ) {
		case carl::FormulaType::CONSTRAINT: {
			auto& pool = VariablePool::getInstance();
			const auto& constraint = inFormula.constraint();
			const auto& pol = constraint.lhs();
			assert( isLinear( pol ) );
			auto vars = variables( pol );
			z3::expr poly = c.real_val( constantPart( pol ) );
			for ( const auto& v : vars ) {
				auto coef = pol.coeff( v, 1 );
				auto z3coeff = c.real_val( constantPart( coef ) );
				if ( z3variables.count( pool.id( v ) ) == 0 ) {
					const char* varName = ( "x_" + std::to_string( pool.id( v ) ) ).c_str();
					auto var = c.real_const( varName );
					z3variables.emplace( std::make_pair( pool.id( v ), var ) );
					poly = poly + z3coeff * var;
				} else {
					poly = poly + z3coeff * z3variables.at( pool.id( v ) );
				}
			}
			switch ( constraint.relation() ) {
				case carl::Relation::LEQ:
					return z3::expr( poly <= 0 );
				case carl::Relation::EQ:
					return z3::expr( poly == 0 );
				case carl::Relation::GEQ:
					return z3::expr( poly >= 0 );
				case carl::Relation::GREATER:
					return z3::expr( poly > 0 );
				case carl::Relation::LESS:
					return z3::expr( poly < 0 );
				case carl::Relation::NEQ:
					return z3::expr( poly != 0 );
			}
			break;
		}
		case carl::FormulaType::AND: {
			z3::expr formula = toZ3( *inFormula.begin(), c, z3variables );
			for ( auto it = std::next( inFormula.begin() ); it != std::end( inFormula ); ++it ) {
				formula = formula && toZ3( *it, c, z3variables );
			}
			return formula;
		}
		case carl::FormulaType::OR: {
			z3::expr formula = toZ3( *inFormula.begin(), c, z3variables );
			for ( auto it = std::next( inFormula.begin() ); it != std::end( inFormula ); ++it ) {
				formula = formula || toZ3( *it, c, z3variables );
			}
			return formula;
		}
		case carl::FormulaType::NOT: {
			return !toZ3( inFormula.subformula(), c, z3variables );
		}
		case carl::FormulaType::IMPLIES: {
			const auto& lhs = inFormula.subformulas().front();
			const auto& rhs = inFormula.subformulas().back();
			return z3::implies( toZ3( lhs, c, z3variables ), toZ3( rhs, c, z3variables ) );
		}
		case carl::FormulaType::IFF: {
			const auto& lhs = inFormula.subformulas().front();
			const auto& rhs = inFormula.subformulas().back();
			return toZ3( lhs, c, z3variables ) == toZ3( rhs, c, z3variables );
		}
		default:
			throw NotImplemented();
	}
}

SmtResult solveZ3( const FormulaT<tNumber>& inFormula ) {
	using namespace z3;
	z3Context c;

	std::map<std::size_t, expr> vars;
	expr formula = toZ3( inFormula, c, vars );

	std::cout << "Solve " << formula << std::endl;
	solver s( c );
	s.add( formula );
	SmtResult res;
	switch ( s.check() ) {
		case unsat: {
			res.sat = false;
			break;
		}
		case sat: {
			res.sat = true;
			std::cout << "Model: " << s.get_model() << std::endl;
			break;
		}
		case unknown: {
			throw std::logic_error( "Solution to LRA-formula cannot be unknown" );
			break;
		}
	}
	return res;
}

}  // namespace hypro

#endif	// HYPRO_USE_Z3
#endif	// HYPRO_Z3CONVENIENCE_H
