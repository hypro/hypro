/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

namespace hypro {
    namespace detail {
/**
 * @brief Implements choices where duplicate elements are allowed and the order of (different-valued) elements can be used to distinguish tuples.
 */
        struct WithReturningNoOrder {
            /// generates the first tuple representing a choice of numberChoices elements with values maximal domainUpperBound-1
            static std::vector<std::size_t> initialize(std::size_t numberChoices, std::vector<std::size_t>) {
                return std::vector<std::size_t>(numberChoices, 0);
            }

            /// generates the next tuple according to the type of choice
            static std::pair<bool, std::vector<std::size_t>>
            increment(std::vector<std::size_t> cur, std::vector<std::size_t> max) {
                // find pos to iterate
                std::size_t pos = 0;
                while (pos < cur.size() && cur.at(pos) == max.at(pos) - 1) {
                    ++pos;
                }

                // check whether last item has already been enumerated
                if (pos == cur.size()) {
                    return std::make_pair(true, cur);
                }

                // actual increment
                cur[pos] += 1;

                while (pos > 0) {
                    --pos;
                    cur[pos] = 0;
                }

                return std::make_pair(false, cur);
            }
        };

/**
 * @brief Implements choices where no duplicate elements are allowed and the order of elements cannot be used to distinguish tuples
 */
        struct NoReturningWithoutOrder {
            /// generates the first tuple representing a choice of numberChoices elements with values maximal domainUpperBound-1
            static std::vector<std::size_t>
            initialize(std::size_t numberChoices, std::vector<std::size_t> domainUpperBound) {
                std::vector<std::size_t> res = std::vector<std::size_t>(numberChoices, 0);
                assert(numberChoices == domainUpperBound.size());
                if (numberChoices <= domainUpperBound.size()) {
                    for (std::size_t i = 0; i < numberChoices; ++i) {
                        res[i] = numberChoices - i - 1;
                    }
                }
                return res;
            }

            /// generates the next tuple according to the type of choice
            static std::pair<bool, std::vector<std::size_t>>
            increment(std::vector<std::size_t> cur, std::vector<std::size_t> max) {
                // find pos to iterate
                std::size_t pos = 0;
                while (pos < cur.size() && cur.at(pos) == max.at(pos) - pos - 1) {
                    ++pos;
                }

                if (pos == cur.size()) {
                    return std::make_pair(true, cur);
                }

                cur[pos] += 1;
                while (pos > 0) {
                    --pos;
                    cur[pos] = cur[pos + 1] + 1;
                }

                return std::make_pair(false, cur);
            }
        };

    }  // namespace detail
}  // namespace hypro
