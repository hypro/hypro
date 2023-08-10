
/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "adaptions_z3.h"

namespace hypro {

    template<typename Number>
    EvaluationResult <Number>
    z3OptimizeLinearPostSolve(bool maximize, const vector_t <Number> &_direction, const matrix_t <Number> &constraints,
                              const vector_t <Number> &constants, const std::vector <carl::Relation> &relations,
                              const EvaluationResult <Number> &preSolution) {
        EvaluationResult <Number> res;
        z3Context c;
        z3::optimize z3Optimizer(c);
        std::vector <z3::expr> variables;

        std::pair <z3::expr, z3::expr> formulaObjectivePair = createFormula<Number>(constraints, constants, relations,
                                                                                    _direction, c, variables);
        z3Optimizer.add(formulaObjectivePair.first);

        z3Optimizer.push();
        if (preSolution.errorCode == SOLUTION::FEAS) {
            addPreSolution(z3Optimizer, c, preSolution, _direction, formulaObjectivePair.second);
        } else if (preSolution.errorCode == SOLUTION::INFEAS) {
            if (z3Optimizer.check() == z3::unsat) {
                // std::cout << "Z3 infeas." << std::endl;
                return preSolution;     // presolver correctly detected infeasibility.
            }                         // if presolver falsely detected infeasibility, we cope with this case below.
        } else {                     // if presolver already detected unboundedness we return its result.
            return preSolution;         // Todo: Check unboundedness
        }

        z3::optimize::handle result(0);
        if (maximize) {
            result = z3Optimizer.maximize(formulaObjectivePair.second);
        } else {
            result = z3Optimizer.minimize(formulaObjectivePair.second);
        }

        if (z3::sat == z3Optimizer.check()) {
            z3::expr z3res = maximize ? z3Optimizer.upper(result) : z3Optimizer.lower(result);
            assert(z3res.is_arith());

            z3::model m = z3Optimizer.get_model();
            // check whether unbounded
            std::stringstream sstr;
            sstr << z3res;

            if (sstr.str() == std::string("oo") || sstr.str() == std::string("(* (- 1) oo)")) {
                res = EvaluationResult<Number>(1, SOLUTION::INFTY);
            } else {
                res.supportValue = z3ResToNumber<Number>(c, z3res);
                vector_t <Number> pointCoordinates = vector_t<Number>::Zero(constraints.cols());
                for (unsigned i = 0; i < variables.size(); ++i) {
                    z3::func_decl currentVar = variables.at(i).decl();
                    if (Z3_model_get_const_interp(c, m, currentVar) != nullptr) {
                        z3::ast varValue = m.get_const_interp(currentVar);
                        pointCoordinates(i) = z3ResToNumber<Number>(c, varValue);
                    }
                }
                res.errorCode = SOLUTION::FEAS;
                res.optimumValue = pointCoordinates;
            }
        } else {
            // presolution made the problem infeasible
            res = preSolution;
        }
        return res;
    }

    template<typename Number>
    EvaluationResult <Number>
    z3OptimizeLinear(bool maximize, const vector_t <Number> &_direction, const matrix_t <Number> &constraints,
                     const vector_t <Number> &constants, const std::vector <carl::Relation> &relations) {
        // std::cout << __func__ << " in direction " << convert<Number,double>(_direction).transpose() << " with constraints" << std::endl << constraints << std::endl << constants << std::endl;
        EvaluationResult <Number> res;
        z3Context c;
        z3::optimize z3Optimizer(c);
        std::vector <z3::expr> variables;

        // create formula and objective
        std::pair <z3::expr, z3::expr> formulaObjectivePair = createFormula<Number>(constraints, constants, relations,
                                                                                    _direction, c, variables);

        // inform and add constraints
        z3Optimizer.add(formulaObjectivePair.first);

        // optimize with objective function
        z3::optimize::handle result(0);
        if (maximize) {
            result = z3Optimizer.maximize(formulaObjectivePair.second);
        } else {
            result = z3Optimizer.minimize(formulaObjectivePair.second);
        }

        // verify and set result
        if (z3::sat == z3Optimizer.check()) {
            z3::expr z3res = maximize ? z3Optimizer.upper(result) : z3Optimizer.lower(result);
            assert(z3res.is_arith());

            z3::model m = z3Optimizer.get_model();
            // check whether unbounded
            std::stringstream sstr;
            sstr << z3res;

            if (sstr.str() == std::string("oo") || sstr.str() == std::string("(* (- 1) oo)")) {
                res = EvaluationResult<Number>(1, SOLUTION::INFTY);
            } else {
                res.supportValue = z3ResToNumber<Number>(c, z3res);
                vector_t <Number> pointCoordinates = vector_t<Number>::Zero(constraints.cols());
                for (unsigned i = 0; i < variables.size(); ++i) {
                    z3::func_decl currentVar = variables.at(i).decl();
                    if (Z3_model_get_const_interp(c, m, currentVar) != nullptr) {
                        z3::ast varValue = m.get_const_interp(currentVar);
                        pointCoordinates(i) = z3ResToNumber<Number>(c, varValue);
                    }
                }
                res.errorCode = SOLUTION::FEAS;
                res.optimumValue = pointCoordinates;
            }
        } else {
            res = EvaluationResult<Number>(0, SOLUTION::INFEAS);
        }
        return res;
    }

    template<typename Number>
    bool z3CheckConsistency(const matrix_t <Number> &constraints, const vector_t <Number> &constants,
                            const std::vector <carl::Relation> &relations) {
        z3Context c;
        z3::optimize z3Optimizer(c);

        // create formula and objective
        z3::expr_vector constraintsExpression = createFormula<Number>(constraints, constants, relations, c);
        // std::cout << "constraints " << constraintsExpression << std::endl;
        // std::cout << constraints << std::endl << constants << std::endl;
        for (unsigned i = 0; i < constraintsExpression.size(); i++) {
            z3Optimizer.add(constraintsExpression[i]);
            // std::cout << "constraint " << constraintsExpression[i] << std::endl;
        }
        z3::check_result res = z3Optimizer.check();
        // std::cout << "result: " << res << std::endl;
        return (z3::sat == res);
    }

    template<typename Number>
    bool z3CheckPoint(const matrix_t <Number> &constraints, const vector_t <Number> &constants,
                      const std::vector <carl::Relation> &relations, const Point <Number> &point) {
        z3Context c;
        z3::solver z3Solver(c);

        // create formula and objective
        z3::expr formula = createFormula<Number>(point, constraints, constants, relations, c);

        // inform and add constraints
        z3Solver.add(formula);

        // verify and set result
        return (z3::sat == z3Solver.check());
    }

    template<typename Number>
    EvaluationResult <Number>
    z3GetInternalPoint(const matrix_t <Number> &constraints, const vector_t <Number> &constants,
                       const std::vector <carl::Relation> &relations) {
        z3Context c;
        EvaluationResult <Number> res;
        z3::solver z3Solver(c);

        z3::expr_vector constraintsExpression = createFormula<Number>(constraints, constants, relations, c);
        for (unsigned i = 0; i < constraintsExpression.size(); i++) {
            z3Solver.add(constraintsExpression[i]);
        }

        if (z3Solver.check() == z3::sat) {
            z3::model m = z3Solver.get_model();
            vector_t <Number> pointCoordinates = vector_t<Number>::Zero(constraints.cols());
            for (unsigned i = 0; i < constraints.cols(); ++i) {
                z3::func_decl var = m.get_const_decl(i);
                if (Z3_model_get_const_interp(c, m, var) != nullptr) {
                    pointCoordinates(i) = Number(Z3_get_numeral_double(c, m.get_const_interp(var)));
                }
            }
            res = EvaluationResult<Number>(pointCoordinates, SOLUTION::FEAS);
        } else {
            res = EvaluationResult<Number>(SOLUTION::INFEAS);
        }
        return res;
    }

    template<typename Number>
    std::vector <std::size_t>
    z3RedundantConstraints(const matrix_t <Number> &constraints, const vector_t <Number> &constants,
                           const std::vector <carl::Relation> &relations) {
        std::vector <std::size_t> res;
        z3Context c;
        z3::solver z3Solver(c);
        z3Solver.push();

        // TODO: ATTENTION: This relies upon that Z3 maintains the order of the constraints!
        z3::expr_vector formulas = createFormula(constraints, constants, relations, c);

        if (formulas.size() == 1) {
            return res;
        }

        assert(unsigned(formulas.size() + res.size()) == constraints.rows());
        for (unsigned i = 0; i < formulas.size(); ++i) {
            z3Solver.add(formulas[i]);
        }

        // first call to check satisfiability
        z3::check_result firstCheck = z3Solver.check();
#ifdef DEBUG_MSG
        // std::cout << __func__ << " Original problem solution: " << firstCheck << std::endl;
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
        for (unsigned constraintIndex = 0; constraintIndex < formulas.size(); ++constraintIndex) {
            z3::expr originalConstraint = formulas[constraintIndex];
#ifdef DEBUG_MSG
            // std::cout << __func__ << " Original constraint: " << originalConstraint << std::endl;
#endif
            z3::expr negatedConstraint = !originalConstraint;

            z3Solver.push();
            for (unsigned i = 0; i < formulas.size(); ++i) {
                // If a constraint has already been marked as redundant, we do not need to
                // to check satisfiability with that constraint in this current iteration.
                bool ignore = false;
                for (unsigned alreadyRedundant = 0; alreadyRedundant < res.size(); ++alreadyRedundant) {
                    if (i == res[alreadyRedundant]) {
                        ignore = true;
                    }
                }
                if (ignore) continue;

                // Add constraints
                if (i == constraintIndex) {
                    z3Solver.add(negatedConstraint);
                } else {
                    z3Solver.add(formulas[i]);
                }
            }

            z3::check_result isRedundant = z3Solver.check();
            assert(isRedundant != z3::check_result::unknown);
            if (isRedundant == z3::check_result::unsat) {
#ifdef DEBUG_MSG
                // std::cout << __func__ << " is redundant." << std::endl;
#endif
                res.push_back(constraintIndex);
            }

            z3Solver.pop();
        }
        return res;
    }

}  // namespace hypro
