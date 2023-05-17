/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//
// Created by Stefan Schupp on 17.05.23.
//

#ifndef HYPRO_DELEGATES_H
#define HYPRO_DELEGATES_H

#include "../../../types.h"
#include "../../../util/linearOptimization/Optimizer.h"
#include "../../../util/linearOptimization/z3/adaptions_z3.h"
#include <hypro/flags.h>

namespace hypro::impl {

    template<typename N>
    bool isEmptySafe(const matrix_t<N> &constraints, const vector_t<N> &constants) {
        return !Optimizer(constraints, constants).checkConsistency();
    }

    template<>
    inline bool isEmptySafe(const matrix_t<mpq_class> &constraints, const vector_t<mpq_class> &constants) {
#ifdef HYPRO_USE_Z3
        return !z3CheckConsistency(constraints, constants,
                                   std::vector<carl::Relation>(constraints.rows(), carl::Relation::LEQ));
#else
        return !Optimizer(constraints, constants).checkConsistency();
#endif
    }

} // namespace

#endif //HYPRO_DELEGATES_H
