/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../carlTypes.h"

#include <vector>

namespace hypro {
    namespace qe {
        using cellDescription = std::vector<FormulasT>;

        static cellDescription
        getCellDescription(const FormulasT &poly, const std::vector <carl::Variable> &variableOrder,
                           const FormulaT &newConstraint) {
            cellDescription res;

            // Data to store in tree
            using FormulaIterators = std::vector<FormulasT::const_iterator>;

            // tree to keep track of the whole process
            CellTree <FormulaIterators> cTree;

            // iterate over all passed variables
            for (auto vIt = variableOrder.begin(); vIt != variableOrder.end(); ++vIt) {
            }

            return res;
        }
    }  // namespace qe
}  // namespace hypro
