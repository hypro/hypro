/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 17.02.22.
 */

#include "gtest/gtest.h"
#include <hypro/flags.h>

#ifdef HYPRO_HAVE_SMT

#include <hypro/util/smt/setEquivalence.h>
#include <hypro/util/smt/SMTSolver.h>


TEST(UtilityTest, SMTSetEquivalenceUnitBox) {
    using M = hypro::matrix_t<mpq_class>;
    using V = hypro::vector_t<mpq_class>;

    // unit box
    M A = M::Zero(4, 2);
    V b = V::Ones(4);
    A << 1, 0, -1, 0, 0, 1, 0, -1;

    auto testEquivalenceFormula = hypro::createTestSetEquivalenceFormula(A, b, A, b);
    auto solver = hypro::SMTSolver(testEquivalenceFormula);
    auto res = solver.solve();

    // the formula should be true, if a point can be found that is in one but not in the other set
    EXPECT_FALSE(res.sat);
}

TEST(UtilityTest, SMTSetEquivalenceScaledUnitBoxes) {
    using M = hypro::matrix_t<mpq_class>;
    using V = hypro::vector_t<mpq_class>;

    // unit box
    M A = M::Zero(4, 2);
    V b = V::Ones(4);
    A << 1, 0, -1, 0, 0, 1, 0, -1;

    {
        auto testEquivalenceFormula = hypro::createTestSetEquivalenceFormula(A, b, A, V(2 * b));
        auto solver = hypro::SMTSolver(testEquivalenceFormula);
        auto res = solver.solve();

        // the formula should be true, if a point can be found that is in one but not in the other set
        EXPECT_TRUE(res.sat);
    }
    {
        auto testEquivalenceFormula = hypro::createTestSetEquivalenceFormula(A, V(2 * b), A, b);
        auto solver = hypro::SMTSolver(testEquivalenceFormula);
        auto res = solver.solve();

        // the formula should be true, if a point can be found that is in one but not in the other set
        EXPECT_TRUE(res.sat);
    }
}

#endif
