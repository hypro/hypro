/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "hypro/representations/Box/intervalMethods.h"

namespace hypro {

    void reduceIntervalsNumberRepresentation(std::vector<carl::Interval<mpq_class>> &intervals, unsigned limit) {
        mpq_class limit2 = mpq_class(limit) * mpq_class(limit);
        for (auto &interval: intervals) {
            // std::cout << "(Upper Bound) mpq_class: " << intervals[d].upper() << std::endl;
            if (interval.upper() != 0) {
                mpq_class numerator = getNumerator(interval.upper());
                mpq_class denominator = getDenominator(interval.upper());
                mpq_class largest =
                        carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
                if (largest > limit2) {
                    mpq_class dividend = largest / mpq_class(limit);
                    assert(largest / dividend == limit);
                    mpq_class val = mpq_class(carl::ceil(numerator / dividend));
                    mpq_class newDenom;
                    if (interval.upper() > 0) {
                        newDenom = mpq_class(carl::floor(denominator / dividend));
                    } else {
                        newDenom = mpq_class(carl::ceil(denominator / dividend));
                    }
                    if (newDenom != 0) {
                        val = val / newDenom;
                        assert(val >= interval.upper());
                        setUpperBound(interval, mpq_class(val));
                    }
                    // std::cout << "Assert: " << val << " >= " << interval.upper() << std::endl;
                    // std::cout << "(Upper bound) Rounding Error: " << carl::convert<mpq_class,double>(val - interval.upper()) << std::endl;
                }
            }

            // std::cout << "(Lower Bound) mpq_class: " << interval.lower() << std::endl;
            if (interval.lower() != 0) {
                mpq_class numerator = getNumerator(interval.lower());
                mpq_class denominator = getDenominator(interval.lower());
                mpq_class largest =
                        carl::abs(numerator) > carl::abs(denominator) ? carl::abs(numerator) : carl::abs(denominator);
                if (largest > limit2) {
                    mpq_class dividend = largest / mpq_class(limit);
                    assert(largest / dividend == limit);
                    mpq_class val = mpq_class(carl::floor(numerator / dividend));
                    mpq_class newDenom;
                    if (interval.lower() > 0) {
                        newDenom = mpq_class(carl::ceil(denominator / dividend));
                    } else {
                        newDenom = mpq_class(carl::floor(denominator / dividend));
                    }
                    if (newDenom != 0) {
                        val = val / newDenom;
                        assert(val <= interval.lower());
                        setLowerBound(interval, val);
                    }
                    // std::cout << "Assert: " << val << " <= " << interval.lower() << std::endl;
                    // std::cout << "(Lower bound) Rounding Error: " << carl::convert<mpq_class,double>(val - interval.lower()) << std::endl;
                }
            }
        }
    }

}  // namespace hypro
