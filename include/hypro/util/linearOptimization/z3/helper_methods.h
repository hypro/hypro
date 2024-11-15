/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "z3Context.h"

#include <z3.h>

namespace hypro {

    template<typename Number>
    void addPreSolution(z3::optimize &solver, z3Context &c, const EvaluationResult <Number> &preSolution,
                        const vector_t <Number> &direction, const z3::expr &objective) {
        // add assignment from presolution

        z3::expr_vector constraints(c);
        z3::expr_vector variables(c);
        for (unsigned i = 0; i < direction.rows(); ++i) {
            z3::expr var(c);
            std::string varName = "x_" + std::to_string( i );
            var = c.real_const(varName.c_str());
            variables.push_back(var);
            // TRACE( "hypro.optimizer", "Created z3 Variable " << var );
        }
        // TRACE( "hypro.optimizer", "Variables.size() " << variables.size() );

        // create and add bound constraints
        for (unsigned i = 0; i < direction.rows(); ++i) {
            if (direction(i) != 0) {
                z3::expr coeff(c);
                coeff = c.real_val((carl::convert<Number, mpq_class>(preSolution.optimumValue(i))));
                // TRACE( "hypro.optimizer", "Coefficient is " << coeff );

                z3::expr bound(c);
                // TRACE( "hypro.optimizer", "Variable is " << variables[j] );
                bound = variables[i] - coeff;
                if (direction(i) > 0) {
                    z3::expr constraint(bound >= 0);
                    solver.add(constraint);
                } else {
                    z3::expr constraint(bound <= 0);
                    solver.add(constraint);
                }
            }
        }

        // add constraint for improvement of glpk solution.
        z3::expr preSolutionPolynomial =
                objective - c.real_val(carl::convert<Number, mpq_class>(preSolution.supportValue));
        z3::expr preSolutionConstraint(preSolutionPolynomial >= 0);

        // TRACE( "hypro.optimizer", "Inform and add improvement constraint " << preSolutionConstraint );
        solver.add(preSolutionConstraint);
    }

}  // namespace hypro
