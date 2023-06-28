/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "util/adaptions_carl/adaptions_includes.h"

namespace hypro {

    enum class QuantifierType {
        EXISTS,
        FORALL
    };

    template<typename Number>
    using PolyT = carl::MultivariatePolynomial<Number>;

    template<typename Number>
    using ConstraintT = carl::Constraint<PolyT<Number> >;

    template<typename Number>
    using ConstraintsT = std::vector<ConstraintT<Number> >;

    template<typename Number>
    using FormulaT = carl::Formula<PolyT<Number> >;

    template<typename Number>
    using FormulasT = std::vector<FormulaT<Number> >;

    using QEQuery = std::vector<std::pair<QuantifierType, std::vector<carl::Variable> > >;

}  // namespace hypro
