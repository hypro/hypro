/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file SimplexSolver.h
 */
#pragma once

#include "../../../flags.h"

#ifdef HYPRO_USE_SMTRAT
#include <lib/solver/Manager.h>
#include <smtrat-modules/LRAModule/LRAModule.h>

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
        setStrategy( { addBackend<LRAModule<LRASettings2>>() } );
    }
};

}  // namespace smtrat

#include "convenience.h"
#endif
