/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#ifdef HYPRO_USE_SOPLEX
#include "../../../types.h"
#include "soplex_hypro.h"

namespace hypro {
namespace detail {

template <typename Number>
soplex::SoPlex initializeSolver( const matrix_t<Number>& constraints, const vector_t<Number>& constants, const std::vector<carl::Relation>& relations ) {
    soplex::SoPlex solver;

    solver.setIntParam( soplex::SoPlex::CHECKMODE, soplex::SoPlex::CHECKMODE_RATIONAL );
    solver.setIntParam( soplex::SoPlex::SOLVEMODE, soplex::SoPlex::SOLVEMODE_RATIONAL );
    solver.setIntParam( soplex::SoPlex::READMODE, soplex::SoPlex::READMODE_RATIONAL );
    solver.setIntParam( soplex::SoPlex::SYNCMODE, soplex::SoPlex::SYNCMODE_AUTO );
    solver.setIntParam( soplex::SoPlex::VERBOSITY, soplex::SoPlex::VERBOSITY_ERROR );
    solver.setRealParam( soplex::SoPlex::FEASTOL, 0.0 );
    solver.setRealParam( soplex::SoPlex::OPTTOL, 0.0 );

    // Add free variables without objective
    soplex::DSVectorRational columns( 0 );
    for ( unsigned varCount = 0; varCount < constraints.cols(); ++varCount ) {
        solver.addColRational( soplex::LPColRational( soplex::Rational( 0 ), columns, soplex::infinity, soplex::Rational( -1 ) * soplex::infinity ) );
    }

    // Add constraints
    for ( unsigned rowIndex = 0; rowIndex < constraints.rows(); ++rowIndex ) {
        // Create row
        soplex::DSVectorRational row( constraints.cols() );
        for ( unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex ) {
            mpq_t a;
            mpq_init( a );
            mpq_set( a, ( carl::convert<Number, mpq_class>( constraints( rowIndex, colIndex ) ) ).get_mpq_t() );
            row.add( colIndex, soplex::Rational( a ) );
            mpq_clear( a );
        }

        // Set bounds on row
        mpq_t a;
        mpq_init( a );
        mpq_set( a, ( carl::convert<Number, mpq_class>( constants( rowIndex ) ) ).get_mpq_t() );
        switch ( relations[rowIndex] ) {
            case carl::Relation::LEQ:
                solver.addRowRational( soplex::LPRowRational( soplex::Rational( -1 ) * soplex::infinity, row, soplex::Rational( a ) ) );
                break;
            case carl::Relation::GEQ:
                solver.addRowRational( soplex::LPRowRational( soplex::Rational( a ), row, soplex::infinity ) );
                break;
            case carl::Relation::EQ:
                solver.addRowRational( soplex::LPRowRational( soplex::Rational( a ), row, soplex::Rational( a ) ) );
                break;
            default:
                // cannot handle strict inequalities.
                assert( false );
                std::cout << "This should not happen." << std::endl;
        }
        mpq_clear( a );
    }

    return solver;
}

template <typename Number>
EvaluationResult<Number> extractSolution( soplex::SoPlex& solver ) {
    soplex::SPxSolver::Status stat;
    stat = solver.solve();

    soplex::DVectorRational prim( solver.numCols() );
    soplex::DVectorRational dual( solver.numRows() );

    switch ( stat ) {
        case soplex::SPxSolver::OPTIMAL: {
            vector_t<Number> optimalPoint = vector_t<Number>( solver.numCols() );
            solver.getPrimalRational( prim );
            for ( int colIndex = 0; colIndex < solver.numCols(); ++colIndex ) {
                optimalPoint( colIndex ) = carl::convert<mpq_class, Number>( mpq_class( *( prim[colIndex] ).getMpqPtr() ) );
            }
            // std::cout << "Result evaluation (optimal): " << EvaluationResult<Number>(carl::convert<mpq_class,Number>(mpq_class(*(solver.objValueRational()).getMpqPtr())), optimalPoint, SOLUTION::FEAS) << std::endl;
            // std::cout << "Optimal point: " <<  optimalPoint << std::endl;
            return EvaluationResult<Number>( carl::convert<mpq_class, Number>( mpq_class( *( solver.objValueRational() ).getMpqPtr() ) ), optimalPoint, SOLUTION::FEAS );
        }
        case soplex::SPxSolver::UNBOUNDED: {
            vector_t<Number> optimalPoint = vector_t<Number>( solver.numCols() );
            solver.getPrimalRational( prim );
            for ( int colIndex = 0; colIndex < solver.numCols(); ++colIndex ) {
                optimalPoint( colIndex ) = carl::convert<mpq_class, Number>( mpq_class( *( prim[colIndex] ).getMpqPtr() ) );
            }
            // std::cout << "Result evaluation (optimal): " << EvaluationResult<Number>(carl::convert<mpq_class,Number>(mpq_class(*(solver.objValueRational()).getMpqPtr())), optimalPoint, SOLUTION::FEAS) << std::endl;
            // std::cout << "Optimal point: " <<  optimalPoint << std::endl;
            return EvaluationResult<Number>( carl::convert<mpq_class, Number>( mpq_class( *( solver.objValueRational() ).getMpqPtr() ) ), optimalPoint, SOLUTION::INFTY );
        }
        case soplex::SPxSolver::INFEASIBLE: {
            return EvaluationResult<Number>( SOLUTION::INFEAS );
        }
        default:
            assert( false );
            return EvaluationResult<Number>();
    }
}

}  // namespace detail

}  // namespace hypro
#endif
