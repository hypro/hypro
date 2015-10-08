#ifdef USE_SMTRAT
/**
 * @file SimplexSolver.h
 */
#pragma once

#include <lib/solver/Manager.h>
#include "../../config.h"
#include "convenience.h"

namespace smtrat
{
    /**
     * Simple strategy only using the LRA module of SMT-RAT
     *
     * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
     * @since		2015-10-06
     * @version		2015-10-07
     *
     */
    class SimplexSolver:
        public Manager
    {
        public:
            SimplexSolver( bool _externalModuleFactoryAdding = false );
            ~SimplexSolver();

    };

} // namespace smtrat
#endif