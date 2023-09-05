/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 13.07.22.
 */

#ifndef HYPRO_SMTCONVENIENCE_H
#define HYPRO_SMTCONVENIENCE_H

#include "hypro/flags.h"

#ifdef HYPRO_HAVE_SMT
#include "GeometricObjectBase.h"
#include "hypro/util/exceptions.h"
#include "hypro/util/smt/SMTSolver.h"

namespace hypro {

template <class Set>
bool symbolicEquivalence( const Set& a, const Set& b ) {
    using F = FormulaT<tNumber>;
    auto A = Converter<typename Set::NumberType>::toCarlPolytope( a );
    auto B = Converter<typename Set::NumberType>::toCarlPolytope( b );

    // A -> B && B -> A
    auto formula = F( carl::FormulaType::AND, F( carl::FormulaType::IMPLIES, A.getFormula(), B.getFormula() ), F( carl::FormulaType::IMPLIES, B.getFormula(), A.getFormula() ) );
    // negation to check set equivalence
    auto negated_formula = F( carl::FormulaType::NOT, formula );
    // solver
    auto solver = SMTSolver( negated_formula );
    auto res = solver.solve();
    return !res;
}

}  // namespace hypro

#endif    // HYPRO_HAVE_SMT
#endif    // HYPRO_SMTCONVENIENCE_H
