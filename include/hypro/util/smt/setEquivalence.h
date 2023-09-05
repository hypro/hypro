/*
 * Copyright (c) 2023-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 06.06.23.
 */

#ifndef HYPRO_SETEQUIVALENCE_H
#define HYPRO_SETEQUIVALENCE_H

#include <hypro/flags.h>

#ifdef HYPRO_HAVE_SMT

#include "hypro/types.h"
#include "hypro/util/linearOptimization/smtrat/convenience.h"

namespace hypro {

    /**
     * Constructs a representation of the formula expressing (Ax <= b && ! (Cx <= d)) || (Cx <= d && !(Ax <= b)).
     * @tparam N
     * @param A
     * @param b
     * @param C
     * @param d
     * @return
     */
    template<typename N>
    FormulaT<mpq_class>
    createTestSetEquivalenceFormula(const matrix_t<N> &A, const vector_t<N> &b, const matrix_t<N> &C,
                                    const vector_t<N> &d) {
        std::unordered_map<FormulaT<mpq_class>, std::size_t> rhsMapping = createFormula<mpq_class>(
                convert<N, mpq_class>(A),
                convert<N, mpq_class>(b),
                std::vector<carl::Relation>(
                        A.rows(),
                        carl::Relation::LEQ));
        std::unordered_map<FormulaT<mpq_class>, std::size_t> lhsMapping = createFormula<mpq_class>(
                convert<N, mpq_class>(C),
                convert<N, mpq_class>(d),
                std::vector<carl::Relation>(
                        A.rows(),
                        carl::Relation::LEQ));


        carl::FormulaSet<PolyT<mpq_class>> rhsConstraints;
        for (const auto &[constraint, _]: rhsMapping) {
            rhsConstraints.insert(constraint);
        }
        FormulaT<N> rhs = FormulaT<mpq_class>(carl::FormulaType::AND, rhsConstraints);

        carl::FormulaSet<PolyT<mpq_class>> lhsConstraints;
        for (const auto &[constraint, _]: lhsMapping) {
            lhsConstraints.insert(constraint);
        }
        FormulaT<N> lhs = FormulaT<mpq_class>(carl::FormulaType::AND, lhsConstraints);

        auto negatedRhs = FormulaT<mpq_class>(carl::FormulaType::NOT, rhs);
        auto negatedLhs = FormulaT<mpq_class>(carl::FormulaType::NOT, lhs);

        auto rhsNotLhs = FormulaT<mpq_class>(carl::FormulaType::AND, rhs, negatedLhs);
        auto lhsNotRhs = FormulaT<mpq_class>(carl::FormulaType::AND, lhs, negatedRhs);

        return FormulaT<mpq_class>(carl::FormulaType::OR, rhsNotLhs, lhsNotRhs);
    }

} // namespace hypro

#endif

#endif //HYPRO_SETEQUIVALENCE_H
