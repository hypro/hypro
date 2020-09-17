/**
 * @file SimplexSolver.h
 */
#pragma once
#include "../../../flags.h"
#ifdef HYPRO_USE_SMTRAT
#include <smtrat-modules/LRAModule/LRAModule.h>
#include <lib/solver/Manager.h>

namespace smtrat {
/**
     * Simple strategy only using the LRA module of SMT-RAT
     *
     * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
     * @since		2015-10-06
     * @version		2015-12-08
     *
     */
class SimplexSolver : public Manager {
  public:
	SimplexSolver()
		: Manager() {
		setStrategy( {addBackend<LRAModule<LRASettings2>>()} );
	}
};

}  // namespace smtrat

#include "convenience.h"
#endif
