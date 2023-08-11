/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

namespace hypro {
    template<typename Number>
    void addPreSolution(smtrat::SimplexSolver &solver, const EvaluationResult <Number> &preSolution,
                        const vector_t <Number> &direction, const smtrat::Poly &objective, bool maximize) {
        // add assignment from presolution
        VariablePool &varPool = VariablePool::getInstance();
        for (unsigned i = 0; i < preSolution.optimumValue.rows(); ++i) {
            if (direction(i) != 0) {
                smtrat::Poly bound = varPool.carlVarByIndex(i) -
                                     carl::convert<Number, smtrat::Rational>(preSolution.optimumValue(i));
                smtrat::FormulaT boundConstraint;
                if (direction(i) > 0) {
                    boundConstraint = smtrat::FormulaT(bound, carl::Relation::GEQ);
                } else {
                    boundConstraint = smtrat::FormulaT(bound, carl::Relation::LEQ);
                }
                // std::cout << "Inform and add bound constraint " << boundConstraint << std::endl;
                solver.inform(boundConstraint);
                solver.add(boundConstraint);
            }
        }

        // add constraint for improvement of glpk solution.
        smtrat::Poly preSolutionPolynomial =
                objective - carl::convert<Number, smtrat::Rational>(preSolution.supportValue);
        smtrat::FormulaT preSolutionConstraint;
        if (maximize) {
            preSolutionConstraint = smtrat::FormulaT(preSolutionPolynomial, carl::Relation::GEQ);
        } else {
            preSolutionConstraint = smtrat::FormulaT(preSolutionPolynomial, carl::Relation::LEQ);
        }
        // std::cout << "Inform and add improvement constraint " << preSolutionConstraint << std::endl;

        solver.inform(preSolutionConstraint);
        solver.add(preSolutionConstraint);
    }

    template<typename Number>
    EvaluationResult <Number>
    extractSolution(smtrat::SimplexSolver &solver, const smtrat::Poly &objective, unsigned dimension) {
        smtrat::ModelValue valuation = solver.optimum(objective);
        EvaluationResult <Number> res;
        assert(!valuation.isBool());
        assert(!valuation.isSqrtEx());
        assert(!valuation.isRAN());
        assert(!valuation.isBVValue());
        assert(!valuation.isSortValue());
        assert(!valuation.isUFModel());
        if (valuation.isMinusInfinity() || valuation.isPlusInfinity()) {
            // std::cout << __func__ << ": INFTY" << std::endl;
            res = EvaluationResult<Number>(1, SOLUTION::INFTY);
        } else {
            assert(valuation.isRational());
            res = EvaluationResult<Number>(carl::convert<smtrat::Rational, Number>(valuation.asRational()),
                                           SOLUTION::FEAS);
            smtrat::Model assignment = solver.model();
            vector_t <Number> point = vector_t<Number>(dimension);
            for (unsigned d = 0; d < dimension; ++d) {
                // if the variable did not occur in the current call, set to 0.
                if (assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) == assignment.end()) {
                    point(d) = 0;
                } else {
                    assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d)) != assignment.end());
                    assert(assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.isRational());
                    point(d) = carl::convert<smtrat::Rational, Number>(
                            assignment.find(hypro::VariablePool::getInstance().carlVarByIndex(d))->second.asRational());
                }
            }
            res.optimumValue = point;
            //#ifdef VERIFY_RESULT
            // solver.push();
            // smtrat::FormulaT inversedObjective(objective-valuation.asRational(), carl::Relation::GREATER);
            // solver.inform(inversedObjective);
            // solver.add(inversedObjective);
            // if(solver.check() != smtrat::Answer::UNSAT) {
            //	outputToSmtlibFormat(solver,fileCounter++, objective, filenamePrefix);
            //}
            // solver.pop();
            //#endif
        }
        return res;
    }

    template<typename Number>
    carl::Relation negateRelation(const carl::Relation &_rel) {
        switch (_rel) {
            case carl::Relation::EQ:
                return carl::Relation::EQ;
            case carl::Relation::NEQ:
                return carl::Relation::NEQ;
            case carl::Relation::LEQ:
                return carl::Relation::GREATER;
            case carl::Relation::GEQ:
                return carl::Relation::LESS;
            case carl::Relation::LESS:
                return carl::Relation::GEQ;
            case carl::Relation::GREATER:
                return carl::Relation::LEQ;
            default:
                assert(false);
                return carl::Relation::EQ;
        }
    }

}  // namespace hypro
