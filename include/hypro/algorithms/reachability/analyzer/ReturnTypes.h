/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../../datastructures/reachability/ReachTreev2.h"
#include "../../../types.h"

#include <variant>

namespace hypro {

    template<class Success, class Failure>
    struct AnalysisResult {
        std::variant<Success, Failure> variant;

        REACHABILITY_RESULT result() {
            return std::holds_alternative<Success>(variant) ? REACHABILITY_RESULT::SAFE : REACHABILITY_RESULT::UNKNOWN;
        }

        bool isSuccess() { return std::holds_alternative<Success>(variant); }

        bool isFailure() { return !isSuccess(); }

        Success &success() { return std::get<Success>(variant); }

        Failure &failure() { return std::get<Failure>(variant); }

        operator std::variant<Success, Failure> &() {
            return variant;
        }
    };

    struct VerificationSuccess {
    };

/**
 * @brief Contains the results of a failed analysis
 * @tparam Representation The representation type that the analysis used
 */
    template<typename Representation, typename Location>
    struct Failure {
        ReachTreeNode<Representation, Location> *conflictNode{};  ///< The node where a conflict occured, i.e. a bad state was intersected.
    };

    template<typename Representation, typename Location>
    Failure(ReachTreeNode<Representation, Location> *) -> Failure<Representation, Location>;

}  // namespace hypro
