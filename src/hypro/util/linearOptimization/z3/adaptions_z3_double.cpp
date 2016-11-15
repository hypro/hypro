
#include "flags.h"
#ifdef HYPRO_USE_Z3

#include "adaptions_z3.h"
#include "../Optimizer.h"

namespace hypro {

	// specialization for double as double requires to use std::stod to be created from a string (the Z3 result).
	template<>
	EvaluationResult<double> z3OptimizeLinear(const vector_t<double>& _direction, const matrix_t<double>& constraints, const vector_t<double>& constants, const EvaluationResult<double>& preSolution ) {
		//std::cout << __func__ << " in direction " << convert<double,double>(_direction).transpose() << " with constraints" << std::endl << constraints << std::endl << constants << std::endl;
		EvaluationResult<double> res;
		z3Context c;
		z3::optimize z3Optimizer(c);
		std::vector<z3::expr> variables;

		// create formula and objective
		std::pair<z3::expr, z3::expr> formulaObjectivePair = createFormula<double>(constraints, constants, _direction, c, variables);

		// inform and add constraints
		z3Optimizer.add(formulaObjectivePair.first);

		#ifdef USE_PRESOLUTION
		z3Optimizer.push();
		if(preSolution.errorCode == FEAS) {
			addPreSolution(z3Optimizer, c, preSolution, _direction, formulaObjectivePair.second);
		} else if( preSolution.errorCode == INFEAS) {
			if(z3Optimizer.check() == z3::unsat){
				//std::cout << "SMTRAT infeas." << std::endl;
				return preSolution; // glpk correctly detected infeasibility.
			} // if glpk falsely detected infeasibility, we cope with this case below.
		} else { // if glpk already detected unboundedness we return its result.
			return preSolution;
		}
		#endif

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
			vector_t<double> pointCoordinates = vector_t<double>::Zero(constraints.cols());
			for( unsigned i = 0; i < variables.size(); ++i ){
				z3::func_decl tmp = variables.at(i).decl();
				if(Z3_model_get_const_interp(c,m,tmp) != nullptr){
					pointCoordinates(i) = std::stod(Z3_get_numeral_string(c,m.get_const_interp(tmp)));
				}
			}
            res.errorCode = SOLUTION::FEAS;
			// check whether unbounded
			std::stringstream sstr;
			sstr << z3res;

			if (std::string("oo") == sstr.str()) {
		       res = EvaluationResult<double>( 1, pointCoordinates, INFTY );
			}
			else {
		       // std::cout << "Point satisfying res: " << pointCoordinates << std::endl;
		       // std::cout << "Result numeral string: " << Z3_get_numeral_string(c,z3res) << std::endl;
		       res.supportValue = std::stod(Z3_get_numeral_string(c,z3res));
		       res.optimumValue = pointCoordinates;
			}
		} else {
			#ifdef USE_PRESOLUTION
				// in this case the constraints introduced by the presolution made the problem infeasible

				z3Optimizer.pop();
				z3::optimize::handle z3Check = z3Optimizer.maximize(formulaObjectivePair.second);
				assert(z3::unknown != z3Optimizer.check());
				if(z3::sat == z3Optimizer.check()) {
					z3::expr z3res = z3Optimizer.upper(z3Check);
					assert(z3res.is_arith());

					z3::model m = z3Optimizer.get_model();
					//std::cout << "Model: " << m << std::endl;
					//std::cout << "Num consts in model: " << m.num_consts() << ", and dimension: " << constraints.cols() << " and variable size: " << variables.size() <<std::endl;
					//assert(m.num_consts() == constraints.cols());
					//assert(variables.size() == m.num_consts());
					vector_t<double> pointCoordinates = vector_t<double>::Zero(constraints.cols());
					for( unsigned i = 0; i < variables.size(); ++i ){
						z3::func_decl tmp = variables.at(i).decl();
						//std::cout << Z3_get_numeral_decimal_string(c, m.get_const_interp(m.get_const_decl(i)), 100) << std::endl;
						if(Z3_model_get_const_interp(c,m,tmp) != nullptr){
							pointCoordinates(i) = std::stod(Z3_get_numeral_string(c,m.get_const_interp(tmp)));
						}
					}
		            res.errorCode = SOLUTION::FEAS;
					// check whether unbounded
					std::stringstream sstr;
					sstr << z3res;

					if (std::string("oo") == sstr.str()) {
				       res = EvaluationResult<double>( 1, pointCoordinates, INFTY );
					}
					else {
				       // std::cout << "Point satisfying res: " << pointCoordinates << std::endl;
				       // std::cout << "Result numeral string: " << Z3_get_numeral_string(c,z3res) << std::endl;
				       res.supportValue = std::stod(Z3_get_numeral_string(c,z3res));
				       res.optimumValue = pointCoordinates;
					}
				} else {
					assert(z3Check == z3::unsat);
					return EvaluationResult<double>( 0, SOLUTION::INFEAS );
				}
			#else
			return EvaluationResult<double>( 0, SOLUTION::INFEAS );
			#endif
		}
		return res;
	}

} // namespace hypro

#endif
