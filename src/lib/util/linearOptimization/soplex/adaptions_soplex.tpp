
#pragma once
#include "adaptions_soplex.h"

namespace hypro {

	template<typename Number>
	EvaluationResult<Number> soplexOptimizeLinear(const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const EvaluationResult<Number>& preSolution) {
		soplex::SoPlex solver;

		/* set the objective sense */
		solver.setIntParam(soplex::SoPlex::CHECKMODE, soplex::SoPlex::CHECKMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::SOLVEMODE, soplex::SoPlex::SOLVEMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::READMODE, soplex::SoPlex::READMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::SYNCMODE, soplex::SoPlex::SYNCMODE_AUTO);
   		solver.setIntParam(soplex::SoPlex::VERBOSITY, soplex::SoPlex::VERBOSITY_ERROR);
   		solver.setRealParam(soplex::SoPlex::FEASTOL, 0.0);
   		solver.setRealParam(soplex::SoPlex::OPTTOL, 0.0);

		soplex::DSVectorRational dummycol(0);
		for(unsigned varIndex = 0; varIndex < _direction.rows(); ++varIndex ) {
			mpq_t a;
			mpq_init(a);
			mpq_set(a, (carl::convert<Number,mpq_class>(_direction(varIndex))).get_mpq_t());
			solver.addColRational(soplex::LPColRational(soplex::Rational(a), dummycol, soplex::infinity, soplex::Rational(-1)*soplex::infinity));
			mpq_clear(a);
		}

		/* then constraints one by one */
		for(unsigned rowIndex = 0; rowIndex < constraints.rows(); ++rowIndex) {
			soplex::DSVectorRational row(constraints.cols());
			for(unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex) {
				mpq_t a;
				mpq_init(a);
				mpq_set(a, (carl::convert<Number,mpq_class>(constraints(rowIndex, colIndex))).get_mpq_t());
				row.add(colIndex, soplex::Rational(a));
				//std::cout << "Added coefficient: " << soplex::Rational(a) << std::endl;
				mpq_clear(a);
			}
			//std::cout << "Created row: " << row << std::endl;
			mpq_t a;
			mpq_init(a);
			mpq_set(a, (carl::convert<Number,mpq_class>(constants(rowIndex))).get_mpq_t());
			//std::cout << "Constraint: " << soplex::Rational(-1)*soplex::infinity << " <= " << row << " <= " << soplex::Rational(a) << std::endl;
			solver.addRowRational(soplex::LPRowRational(soplex::Rational(-1)*soplex::infinity, row, soplex::Rational(a) ));
			mpq_clear(a);
		}

		// std::cout << solver.statisticString() << std::endl;
		//solver.writeFileRational("dump.lp", NULL, NULL, NULL);
		//exit(0);

		/* solve LP */
		soplex::SPxSolver::Status stat;
		soplex::DVectorRational prim(constraints.cols());
		soplex::DVectorRational dual(constraints.rows());
		stat = solver.solve();

		switch(stat) {
			case soplex::SPxSolver::OPTIMAL:{
				vector_t<Number> optimalPoint = vector_t<Number>(constraints.cols());
				solver.getPrimalRational(prim);
				for(unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex) {
					optimalPoint(colIndex) = carl::convert<mpq_class,Number>(mpq_class(*(prim[colIndex]).getMpqPtr()));
				}
				//std::cout << "Result evaluation (optimal): " << EvaluationResult<Number>(carl::convert<mpq_class,Number>(mpq_class(*(solver.objValueRational()).getMpqPtr())), optimalPoint, SOLUTION::FEAS) << std::endl;
				//std::cout << "Optimal point: " <<  optimalPoint << std::endl;
				return EvaluationResult<Number>(carl::convert<mpq_class,Number>(mpq_class(*(solver.objValueRational()).getMpqPtr())), optimalPoint, SOLUTION::FEAS);
			}
			case soplex::SPxSolver::UNBOUNDED:{
				return EvaluationResult<Number>(SOLUTION::INFTY);
			}
			case soplex::SPxSolver::INFEASIBLE:{
				return EvaluationResult<Number>(SOLUTION::INFEAS);
			}
			default:
				assert(false);
				return EvaluationResult<Number>();
		}
	}


	template<typename Number>
	bool soplexCheckConsistency(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
		soplex::SoPlex solver;

		/* set the objective sense */
   		solver.setIntParam(soplex::SoPlex::CHECKMODE, soplex::SoPlex::CHECKMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::SOLVEMODE, soplex::SoPlex::SOLVEMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::READMODE, soplex::SoPlex::READMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::SYNCMODE, soplex::SoPlex::SYNCMODE_AUTO);
   		solver.setIntParam(soplex::SoPlex::VERBOSITY, soplex::SoPlex::VERBOSITY_ERROR);
   		solver.setRealParam(soplex::SoPlex::FEASTOL, 0.0);
   		solver.setRealParam(soplex::SoPlex::OPTTOL, 0.0);

		soplex::DSVectorRational dummycol(constraints.cols());
		for(unsigned varIndex = 0; varIndex < constraints.cols(); ++varIndex ) {
			solver.addColRational(soplex::LPColRational(soplex::Rational(1), dummycol, soplex::infinity, soplex::Rational(-1)*soplex::infinity));
		}

		/* then constraints one by one */
		for(unsigned rowIndex = 0; rowIndex < constraints.rows(); ++rowIndex) {
			soplex::DSVectorRational row(constraints.cols());
			for(unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex) {
				mpq_t a;
				mpq_init(a);
				mpq_set(a, (carl::convert<Number,mpq_class>(constraints(rowIndex, colIndex))).get_mpq_t());
				row.add(colIndex, soplex::Rational(a));
				//std::cout << "Before conversion: " << carl::convert<Number,mpq_class>(constraints(rowIndex, colIndex)) << std::endl;
				//std::cout << "Test: " << (carl::convert<Number,mpq_class>(constraints(rowIndex, colIndex))).get_mpq_t() << std::endl;
				//std::cout << "a(" << rowIndex << ", " << colIndex << ") = " << a << std::endl;
				mpq_clear(a);
			}
			mpq_t a;
			mpq_init(a);
			mpq_set(a, (carl::convert<Number,mpq_class>(constants(rowIndex))).get_mpq_t());
			solver.addRowRational(soplex::LPRowRational(soplex::Rational(-1)*soplex::infinity, row, soplex::Rational(a) ));
			//std::cout << "Row: " << row << std::endl;
			mpq_clear(a);
		}

		/* solve LP */
		solver.solve();
		//solver.writeFileRational("dump.lp", NULL, NULL, NULL);

		return (solver.hasPrimal());
	}

	template<typename Number>
	bool soplexCheckPoint(const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& point) {
		soplex::SoPlex solver;

		solver.setIntParam(soplex::SoPlex::CHECKMODE, soplex::SoPlex::CHECKMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::SOLVEMODE, soplex::SoPlex::SOLVEMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::READMODE, soplex::SoPlex::READMODE_RATIONAL);
   		solver.setIntParam(soplex::SoPlex::SYNCMODE, soplex::SoPlex::SYNCMODE_AUTO);
   		solver.setIntParam(soplex::SoPlex::VERBOSITY, soplex::SoPlex::VERBOSITY_ERROR);
   		solver.setRealParam(soplex::SoPlex::FEASTOL, 0.0);
   		solver.setRealParam(soplex::SoPlex::OPTTOL, 0.0);

		soplex::DSVectorRational dummycol(0);
		for(unsigned varIndex = 0; varIndex < constraints.cols(); ++varIndex ) {
			mpq_t a;
			mpq_init(a);
			mpq_set(a, (carl::convert<Number,mpq_class>(point.at(varIndex))).get_mpq_t());
			solver.addColRational(soplex::LPColRational(soplex::Rational(1), dummycol, a, a));
			mpq_clear(a);
		}

		/* then constraints one by one */
		for(unsigned rowIndex = 0; rowIndex < constraints.rows(); ++rowIndex) {
			soplex::DSVectorRational row(constraints.cols());
			for(unsigned colIndex = 0; colIndex < constraints.cols(); ++colIndex) {
				mpq_t a;
				mpq_init(a);
				mpq_set(a, (carl::convert<Number,mpq_class>(constraints(rowIndex, colIndex))).get_mpq_t());
				row.add(colIndex, soplex::Rational(a));
				mpq_clear(a);
			}
			mpq_t a;
			mpq_init(a);
			mpq_set(a, (carl::convert<Number,mpq_class>(constants(rowIndex))).get_mpq_t());
			solver.addRowRational(soplex::LPRowRational(soplex::Rational(-1)*soplex::infinity, row, soplex::Rational(a) ));
			mpq_clear(a);
		}

		/* solve LP */
		solver.solve();

		return solver.hasPrimal();
	}

} // namespace hypro
