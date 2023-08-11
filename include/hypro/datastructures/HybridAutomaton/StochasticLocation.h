/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Class that describes a location of a stochastic hybrid automaton.
 */

#pragma once

#include "Location.h"

namespace hypro {

    template<typename LocationType>
    class StochasticTransition;

/**
 * @brief      Class for a location in a stochastic automaton.
 * @tparam     Number  The used number type.
 */
    template<typename Number>
    class StochasticLocation : public Location<Number> {
    public:
        using stochasticTransitionVector = std::vector<std::unique_ptr<StochasticTransition<StochasticLocation<Number>>>>;

    private:
        // Number mProbability = 1;
        matrix_t<Number> mLocationDistribution;
        DistributionType mDistributionType;
        Number mExpLambda;
        Number mNormalSigma;
        Number mNormalMu;

    public:
        StochasticLocation()
                : Location<Number>(), mLocationDistribution() {}

        StochasticLocation(const std::string &name)
                : Location<Number>(name), mLocationDistribution() {}

        StochasticLocation(const StochasticLocation &_loc)
                : Location<Number>(_loc), mLocationDistribution(_loc.getLocationDistribution()) {
            mExpLambda = _loc.getExpLambda();
        }

        explicit StochasticLocation(const matrix_t<Number> &_mat)
                : Location<Number>(_mat), mLocationDistribution() {}

        StochasticLocation(const matrix_t<Number> &_mat, stochasticTransitionVector &&_trans,
                           const Condition<Number> &_inv, const matrix_t<Number> &_dist,
                           stochasticTransitionVector &&_stotrans)
                : Location<Number>(_mat, _trans, _inv), mLocationDistribution(_dist) {}

        ~StochasticLocation() {}

        void setLocationDistribution(const matrix_t<Number> locationDistribution) {
            mLocationDistribution = locationDistribution;
        }

        const matrix_t<Number> &getLocationDistribution() const {
            return mLocationDistribution;
        }

        void setLocationDistributionType(DistributionType distributionType) {
            mDistributionType = distributionType;
        }

        DistributionType getLocationDistributionType() const {
            return mDistributionType;
        }

        void setExpLambda(Number lambda) {
            mExpLambda = lambda;
        }

        const Number getExpLambda() const {
            return mExpLambda;
        }

        void setNormalSigma(Number sigma) {
            mNormalSigma = sigma;
        }

        Number getNormalSigma() {
            return mNormalSigma;
        }

        void setNormalMu(Number mu) {
            mNormalMu = mu;
        }

        Number getNormalMu() {
            return mNormalMu;
        }
    };

}  // namespace hypro
