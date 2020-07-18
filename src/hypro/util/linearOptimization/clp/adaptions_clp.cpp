/**
 *
 */
#include "adaptions_clp.h"
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

void clpPrintProblem( clp_context& context, double* objective ) {
    for (int i = 0; i < context.matrix.getNumCols(); ++i ){
        std::cout << objective[i] << " ";
    }
    std::cout << "\n";
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
