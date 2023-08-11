/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Implementation of principal component analysis for a set of sample points.
 * @file  pca.h
 * @author Simon Froitzheim
 *
 * @since       2015-02-15
 * @version     2015-02-15
 */

#pragma once

#include "../datastructures/Halfspace.h"
#include "../datastructures/Point.h"

namespace hypro {

/**
 * @brief Class implementing principal component analysis
 * @tparam Number
 */
    template<typename Number>
    class PrincipalComponentAnalysis {
    private:
        mutable Point<Number> mMean;                             ///< mean value of sample set
        std::vector<Point<Number>> mSamples;                     ///< sample set
        mutable std::vector<Halfspace<Number>> mBoxConstraints;     ///< oriented bounding box
        mutable bool mBoxComputed = false;                         ///< flag to indicate box has been computed
        mutable bool mMeanComputed = false;                         ///< flag to indicate mean has been computed

    public:
        /// default constructor
        PrincipalComponentAnalysis() = default;

        /**
         * @brief Construct a new Principal Component Analysis object from a set of samples
         * @param samples
         */
        PrincipalComponentAnalysis(const std::vector<Point<Number>> &samples)
                : mMean(), mSamples(samples), mBoxConstraints(), mBoxComputed(false), mMeanComputed(false) {}

        /// copy constructor
        PrincipalComponentAnalysis(const PrincipalComponentAnalysis<Number> &orig) = default;

        /// returns the mean value over the sample set
        const Point<Number> &mean() const;

        /// getter for the sample set
        const std::vector<Point<Number>> &samples() const { return mSamples; }

        /// returns the oriented bounding box of the sample set
        const std::vector<Halfspace<Number>> box() const;

        /// setter for sample set
        void setSamples(const std::vector<Point<Number>> &samples);

        /// method to call mean-value computation
        void computeMean() const;

        /// method to call computation of oriented bounding box
        void computeOrientedBox() const;
    };

}  // namespace hypro

#include "pca.tpp"
