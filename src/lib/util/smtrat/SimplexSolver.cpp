/**
 * @file SimplexSolver.cpp
 */

#ifdef USE_SMTRAT
#include "SimplexSolver.h"
//#include "config.h"

namespace smtrat
{

    SimplexSolver::SimplexSolver( bool _externalModuleFactoryAdding ):
        Manager( _externalModuleFactoryAdding )
    {
        size_t position = 0;
        position = addBackendIntoStrategyGraph( position, MT_LRAModule );
    }

    SimplexSolver::~SimplexSolver(){}

} // namespace smtrat
#endif