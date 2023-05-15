/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../representations/GeometricObjectBase.h"
#include "../parser/NNet.h"
#include "../../util/plotting/Plotter.h"
#include "../../util/logging/Logger.h"

#include <iostream>
#include <vector>  // change it later to a better container for Star-sets

namespace hypro {
    namespace reachability {

        enum NN_reach_method {
            EXACT,
            OVERAPPRX,
        };

// TODO: add comments and description/documentation for the different functions
        template<typename Number>
        class ReachNN {
        private:
            // members
            NNet<Number> mNNet;

        public:
            ReachNN(NNet<Number> nnet)
                    : mNNet(nnet) {}

            // methods
            std::vector<hypro::Starset<Number>>
            forwardAnalysis(const hypro::Starset<Number> &input_set, NN_reach_method method,
                            bool plot_intermediates = false) const;

            std::vector<hypro::Starset<Number>>
            layerReach(int l, const std::vector<hypro::Starset<Number>> &input_sets, NN_reach_method method,
                       bool plot_intermediates) const;

            std::vector<hypro::Starset<Number>>
            reachReLU(const hypro::Starset<Number> &input_star1, NN_reach_method method, bool plot_intermediates) const;

            std::vector<hypro::Starset<Number>> stepReLU(int i, std::vector<hypro::Starset<Number>> &input_sets) const;

            std::vector<hypro::Starset<Number>>
            approxStepReLU(int i, std::vector<hypro::Starset<Number>> &input_sets) const;
        };

    }  // namespace reachability
}  // namespace hypro

#include "ReachNN.tpp"
