
#pragma once
#include "adaptions_z3.h"

namespace hypro {

	template<typename Number>
	EvaluationResult<Number> z3OptimizeLinear(const vector_t<Number>& _direction, const matrix_t<Number>& constraints, const vector_t<Number>& constants, const EvaluationResult<Number>& preSolution) {
		//std::cout << __func__ << " in direction " << convert<Number,double>(_direction).transpose() << " with constraints" << std::endl << constraints << std::endl << constants << std::endl;
		EvaluationResult<Number> res;
		z3Context c;
		z3::optimize z3Optimizer(c);
		std::vector<z3::expr> variables;

		// create formula and objective
		std::pair<z3::expr, z3::expr> formulaObjectivePair = createFormula<Number>(constraints, constants, _direction, c, variables);

		// inform and add constraints
		z3Optimizer.add(formulaObjectivePair.first);

		// optimize with objective function
		z3::optimize::handle result = z3Optimizer.maximize(formulaObjectivePair.second);

		#ifdef DEBUG_MSG
		std::cout << "Optimizer String: " << z3Optimizer << std::endl;
		#endif

		// verify and set result
		if(z3::sat == z3Optimizer.check()) {
			z3::expr z3res = z3Optimizer.upper(result);
			assert(z3res.is_arith());

			z3::model m = z3Optimizer.get_model();
			//std::cout << "Model: " << m << std::endl;
			//std::cout << "Num consts in model: " << m.num_consts() << ", and dimension: " << constraints.cols() << " and variable size: " << variables.size() <<std::endl;
			//assert(m.num_consts() == constraints.cols());
			//assert(variables.size() == m.num_consts());
			vector_t<Number> pointCoordinates = vector_t<Number>::Zero(constraints.cols());
			for( unsigned i = 0; i < variables.size(); ++i ){
				z3::func_decl tmp = variables.at(i).decl();
				//std::cout << Z3_get_numeral_decimal_string(c, m.get_const_interp(m.get_const_decl(i)), 100) << std::endl;
				if(Z3_model_get_const_interp(c,m,tmp) != nullptr){
					pointCoordinates(i) = Number(Z3_get_numeral_string(c,m.get_const_interp(tmp)));
				}
			}
            res.errorCode = SOLUTION::FEAS;
			// check whether unbounded
			std::stringstream sstr;
			sstr << z3res;

			if (std::string("oo") == sstr.str()) {
		       res = EvaluationResult<Number>( 1, pointCoordinates, INFTY );
			}
			else {
		       // std::cout << "Point satisfying res: " << pointCoordinates << std::endl;
		       // std::cout << "Result numeral string: " << Z3_get_numeral_string(c,z3res) << std::endl;
		       res.supportValue = Number(Z3_get_numeral_string(c,z3res));
		       res.optimumValue = pointCoordinates;
			}
		}
		return res;
	}


	template<typename Number>
	bool z3CheckConsistency(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
		z3Context c;
		z3::optimize z3Optimizer(c);

		// create formula and objective
		z3::expr_vector constraintsExpression = createFormula<Number>(constraints, constants, c);
		//std::cout << "constraints " << constraintsExpression << std::endl;
		//std::cout << constraints << std::endl << constants << std::endl;
		for (unsigned i = 0; i < constraintsExpression.size(); i++) {
			z3Optimizer.add(constraintsExpression[i]);
			//std::cout << "constraint " << constraintsExpression[i] << std::endl;
		}
		z3::check_result res = z3Optimizer.check();
		//std::cout << "result: " << res << std::endl;
		return (z3::sat == res);
	}

	template<typename Number>
	bool z3CheckPoint(const matrix_t<Number>& constraints, const vector_t<Number>& constants, const Point<Number>& point) {
		z3Context c;
		z3::solver z3Solver(c);

		// create formula and objective
		z3::expr formula = createFormula<Number>(point,  constraints, constants, c);

		// inform and add constraints
		z3Solver.add(formula);

		// verify and set result
		return (z3::sat == z3Solver.check());
	}

	template<typename Number>
	std::vector<std::size_t> z3RedundantConstraints(const matrix_t<Number>& constraints, const vector_t<Number>& constants) {
		std::vector<std::size_t> res;
		z3Context c;
		z3::solver z3Solver(c);
		z3Solver.push();

		// TODO: ATTENTION: This relies upon that Z3 maintains the order of the constraints!
		z3::expr_vector formulas = createFormula(constraints, constants, c );

		if(formulas.size() == 1){
			return res;
		}

		assert(unsigned(formulas.size() + res.size()) == constraints.rows());
		for(unsigned i = 0; i < formulas.size(); ++i) {
			z3Solver.add(formulas[i]);
		}

		// first call to check satisfiability
		z3::check_result firstCheck = z3Solver.check();
		#ifdef DEBUG_MSG
		std::cout << __func__ << " Original problem solution: " << firstCheck << std::endl;
		#endif
		switch (firstCheck) {
			case z3::check_result::unsat: {
				return res;
				break;
			}
			case z3::check_result::sat: {
				break;
			}
			default: {
				assert(false);
				break;
			}
		}

		z3Solver.pop();
		for(unsigned constraintIndex = 0; constraintIndex < formulas.size(); ++constraintIndex) {
			z3::expr originalConstraint = formulas[constraintIndex];
			#ifdef DEBUG_MSG
			std::cout << __func__ << " Original constraint: " << originalConstraint << std::endl;
			#endif
			z3::expr negatedConstraint = !originalConstraint;

			z3Solver.push();
			for(unsigned i = 0; i < formulas.size(); ++i){
				if(i == constraintIndex) {
					z3Solver.add(negatedConstraint);
				} else {
					z3Solver.add(formulas[i]);
				}
			}

			z3::check_result isRedundant = z3Solver.check();
			assert(isRedundant != z3::check_result::unknown);
			if(isRedundant == z3::check_result::unsat){
				#ifdef DEBUG_MSG
				std::cout << __func__ << " is redundant." << std::endl;
				#endif
				res.push_back(constraintIndex);
			}

			z3Solver.pop();
		}
		return res;
	}


} // namespace hypro
