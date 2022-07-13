/*
 * Copyright (c) 2022.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 12.07.22.
 */

#ifndef HYPRO_Z3CONVENIENCE_H
#define HYPRO_Z3CONVENIENCE_H
#include <hypro/flags.h>
#ifdef HYPRO_USE_Z3
#include "hypro/types.h"
#include "hypro/util/linearOptimization/z3/z3Context.h"
#include "hypro/util/smt/SMTSolver.h"
#include "hypro/util/smt/SmtResult.h"

#include <z3++.h>

namespace hypro {

z3::expr toZ3( const FormulaT<tNumber>& inFormula, z3Context& c, std::map<std::size_t, z3::expr>& z3variables );

SmtResult solveZ3( const FormulaT<tNumber>& inFormula );

}  // namespace hypro

#endif	// HYPRO_USE_Z3
#endif	// HYPRO_Z3CONVENIENCE_H
