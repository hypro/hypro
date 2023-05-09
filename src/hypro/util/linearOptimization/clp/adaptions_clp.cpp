/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 *
 */
#include "hypro/util/linearOptimization/clp/adaptions_clp.h"

#ifdef HYPRO_USE_CLP

namespace hypro {

SOLUTION clpCheckConsistency( clp_context& context ) {
    // remove lower bounds on columns    
    for(int i = 0; i < context.matrix.getNumCols(); ++i){
        context.mColumnLowerBounds[i] = -COIN_DBL_MAX;
    }
    // load problem into problem instance
    context.lp.loadProblem( context.matrix, context.mColumnLowerBounds, nullptr, nullptr, context.mLowerBounds, context.mUpperBounds );

    context.lp.primal();
    return context.lp.primalFeasible() ? SOLUTION::FEAS : SOLUTION::INFEAS;
}

void clpPrintProblem( clp_context& context ) {
    for ( int i = 0; i < context.matrix.getNumRows(); ++i ){
    std::cout << context.mLowerBounds[i] << " <= ";
    for(int j= 0; j< context.matrix.getNumCols(); ++j ){
        context.matrix.printMatrixElement( i, j );
        std::cout << " ";
    }
    std::cout << " <= " << context.mUpperBounds[i] << "\n";
  }
}
}  // namespace hypro
#endif
