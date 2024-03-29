/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This file contains the basic implementation of support functions of boxes and their evaluation methods.
 *
 * @author Stefan Schupp <stefan.schupp@cs.rwth-aachen.de>
 */

#pragma once

#include "../../types.h"
#include "../../util/logging/Logger.h"
#include "../../util/sequenceGeneration/SequenceGenerator.h"
#include "../../util/statistics/statistics.h"
#include "util.h"

#include <map>

namespace hypro {

/*
 * This class defines a support Function object representing a box
 * SupportFunctions can be evaluated in a specified direction l and return a correspondent EvaluationResult
 */
    template<typename Number, typename Setting>
    class BoxSupportFunction : GeometricObjectBase {
    private:
        std::vector<carl::Interval<Number>> mBox;

    public:
        BoxSupportFunction(const std::vector<carl::Interval<Number>> &intervals);

        BoxSupportFunction(const std::vector<Point<Number>> &_points);

        BoxSupportFunction(const BoxSupportFunction<Number, Setting> &_origin);

        ~BoxSupportFunction();

        BoxSupportFunction<Number, Setting> &operator=(const BoxSupportFunction<Number, Setting> &_orig);

        /**
         * Returns the dimension of the object.
         * @return
         */
        std::size_t dimension() const;

        SF_TYPE type() const;

        matrix_t<Number> constraints() const;

        vector_t<Number> constants() const;

        std::vector<Point<Number>> vertices() const;

        Point<Number> supremumPoint() const;

        /**
         * Evaluates the support function in the given direction.
         * @param l
         * @return
         */
        EvaluationResult<Number> evaluate(const vector_t<Number> &l, bool useExact) const;

        /**
         * @brief Evaluates the support function in the directions given in the passed matrix.
         * @details Uses the standard evaluate method for multiple directions.
         *
         * @param _A Matrix holding the directions in which to evaluate.
         * @return Vector of support values.
         */
        std::vector<EvaluationResult<Number>>
        multiEvaluate(const matrix_t<Number> &_A, bool useExact, bool setTemplate = false) const;

        /**
         * @brief Check if point is contained in the support function.
         * @details To check if the given point is contained in the support function we evaluate it in all its directions
         *(uses multiEvaluate).
         *
         * @param _point The point to check.
         * @return True, if the point is inside the support function.
         */
        bool contains(const Point<Number> &_point) const;

        /**
         * @brief Check if point is contained in the support function.
         * @details To check if the given point is contained in the support function we evaluate it in all its directions
         *(uses multiEvaluate).
         *
         * @param _point The point to check.
         * @return True, if the point is inside the support function.
         */
        bool contains(const vector_t<Number> &_point) const;

        bool empty() const;

        const std::vector<carl::Interval<Number>> &getIntervals() const { return mBox; }

        std::string getDotRepresentation() const;

        friend std::ostream &operator<<(std::ostream &lhs, const BoxSupportFunction<Number, Setting> &rhs) {
            for (const auto &i: rhs.mBox) {
                lhs << i << std::endl;
            }
            return lhs;     // << rhs.getBox();
        }
    };
}  // namespace hypro
#include "BoxSupportFunction.tpp"
