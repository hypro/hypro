#ifdef USE_SMTRAT
/**
 * @file SimplexSolver.h
 */
#pragma once

#include <lib/solver/Manager.h>
#include <lib/modules/SATModule/SATModule.h>
#include <lib/modules/LRAModule/LRAModule.h>
//#include "../../config.h"
#include "convenience.h"

namespace smtrat
{
    /**
     * Simple strategy only using the LRA module of SMT-RAT
     *
     * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
     * @since		2015-10-06
     * @version		2015-12-08
     *
     */
    class SimplexSolver:
        public Manager
    {
        public:
            SimplexSolver(): Manager() {
				setStrategy(
	            {
	                addBackend<SATModule<SATSettings1>>(
	                {
	                    addBackend<LRAModule<LRASettings1>>()
	                })
	            });
			}

    };

} // namespace smtrat
#endif