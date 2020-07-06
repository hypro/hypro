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
}  // namespace hypro
#endif
