/**
 * @file SimplexSolver.cpp
 */

#include "SimplexSolver.h"
//#include "config.h"

namespace smtrat
{

    SimplexSolver::SimplexSolver( bool _externalModuleFactoryAdding ):
        Manager( _externalModuleFactoryAdding )
    {
        size_t position = 0;
        //#ifdef SMTRAT_ENABLE_LRAModule
        position = addBackendIntoStrategyGraph( position, MT_LRAModule );
        //#endif
    }

    SimplexSolver::~SimplexSolver(){}

} // namespace smtrat