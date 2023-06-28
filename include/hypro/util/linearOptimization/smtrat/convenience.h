/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Holds convenience functions when working with SMTRat.
 */
#pragma once

#include <hypro/flags.h>
#include "../../../types.h"

#include "../../../datastructures/Point.h"
#include "../../VariablePool.h"

#include <fstream>

namespace hypro {

    template<typename Number>
    static std::unordered_map<FormulaT<mpq_class>, std::size_t>
    createFormula(const matrix_t<Number> &_constraints, const vector_t<Number> _constants,
                  const std::vector<carl::Relation> &relations) {
        assert(_constraints.rows() == _constants.rows());
        assert(relations.size() == _constraints.rows());

        VariablePool &pool = VariablePool::getInstance();

        std::unordered_map<FormulaT<mpq_class>, std::size_t> constraints;
        for (unsigned rowIndex = 0; rowIndex < _constraints.rows(); ++rowIndex) {
            carl::MultivariatePolynomial<mpq_class> row;
            for (unsigned colIndex = 0; colIndex < _constraints.cols(); ++colIndex) {
                row += carl::convert<Number, mpq_class>(_constraints(rowIndex, colIndex)) *
                       pool.carlVarByIndex(colIndex);
            }
            row -= carl::convert<Number, mpq_class>(_constants(rowIndex));
            // std::cout << "atempt to insert constraint " << rowIndex << " (" << _constraints.row(rowIndex) << ", " << _constants(rowIndex) << ")" << std::endl;
            constraints.insert(std::make_pair(FormulaT<mpq_class>(row, relations[rowIndex]), rowIndex));
        }
        return constraints;
    }

    template<typename Number>
    static std::unordered_map<FormulaT<mpq_class>, std::size_t>
    createFormula(const std::vector<carl::Interval<Number>> &_intervals) {
        VariablePool &pool = VariablePool::getInstance();

        std::unordered_map<FormulaT<mpq_class>, std::size_t> constraints;
        for (unsigned intervalIndex = 0; intervalIndex < _intervals.size(); ++intervalIndex) {
            carl::MultivariatePolynomial<mpq_class> lower;
            switch (lowerBoundType(_intervals[intervalIndex])) {
                case carl::BoundType::STRICT: {
                    lower += pool.carlVarByIndex(intervalIndex) -
                             carl::convert<Number, mpq_class>(_intervals[intervalIndex].lower());
                    constraints.insert(
                            std::make_pair(FormulaT<mpq_class>(lower, carl::Relation::GREATER), intervalIndex));
                    break;
                }
                case carl::BoundType::WEAK: {
                    lower += pool.carlVarByIndex(intervalIndex) -
                             carl::convert<Number, mpq_class>(_intervals[intervalIndex].lower());
                    constraints.insert(std::make_pair(FormulaT<mpq_class>(lower, carl::Relation::GEQ), intervalIndex));
                    break;
                }
                case carl::BoundType::INFTY: {
                    break;
                }
            }
            carl::MultivariatePolynomial<mpq_class> upper;
            switch (upperBoundType(_intervals[intervalIndex])) {
                case carl::BoundType::STRICT: {
                    upper += pool.carlVarByIndex(intervalIndex) -
                             carl::convert<Number, mpq_class>(_intervals[intervalIndex].lower());
                    constraints.insert(std::make_pair(FormulaT<mpq_class>(upper, carl::Relation::LESS), intervalIndex));
                    break;
                }
                case carl::BoundType::WEAK: {
                    upper += pool.carlVarByIndex(intervalIndex) -
                             carl::convert<Number, mpq_class>(_intervals[intervalIndex].lower());
                    constraints.insert(std::make_pair(FormulaT<mpq_class>(upper, carl::Relation::LEQ), intervalIndex));
                    break;
                }
                case carl::BoundType::INFTY: {
                    break;
                }
            }
        }
        return constraints;
    }

    template<typename Number>
    static std::unordered_map<FormulaT<mpq_class>, std::size_t> createFormula(const Point<Number> &_point) {
        VariablePool &pool = VariablePool::getInstance();

        std::unordered_map<FormulaT<mpq_class>, std::size_t> constraints;
        for (unsigned d = 0; d < _point.dimension(); ++d) {
            carl::MultivariatePolynomial<mpq_class> row;
            row += mpq_class(-carl::convert<Number, mpq_class>(_point.at(d))) + pool.carlVarByIndex(d);
            // std::cout << "atempt to insert constraint " << d << " (" << _constraints.row(d) << ", " << _constants(d) << ")" << std::endl;
            constraints.insert(std::make_pair(FormulaT<mpq_class>(row, carl::Relation::EQ), d));
        }
        return constraints;
    }

    template<typename InType>
    static carl::MultivariatePolynomial<mpq_class> createObjective(const vector_t<InType> &_objective) {
        carl::MultivariatePolynomial<mpq_class> objective;
        VariablePool &pool = VariablePool::getInstance();

        // get new variables
        for (unsigned index = 0; index < _objective.rows(); ++index) {
            objective += carl::convert<InType, mpq_class>(_objective(index)) * pool.carlVarByIndex(index);
        }
        return objective;
    }

#ifdef VERIFY_RESULT
    static void outputToSmtlibFormat( const smtrat::SimplexSolver& solver, unsigned count, const smtrat::Poly& objective, const std::string& _prefix ) {
        std::string filename = _prefix + std::to_string( count ) + ".smt2";
        std::ofstream ofs( filename, std::ofstream::app );
        ofs << "(set-logic QF_LRA)\n"
            << "(set-info :smt-lib-version 2.0)\n(push 1)";
        ofs << ( (FormulaT<mpq_class>)solver.formula() ).toString( false, 1, "", true, false, true, true );
        ofs << "(maximize " << objective.toString( false ) << " )\n";
        ofs << "(check-sat)\n(reset)" << std::endl;
        ofs.close();
    }
#endif

}  // namespace hypro
