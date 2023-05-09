/*
 * Copyright (c) 2021-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 09.09.21.
 */
#pragma once

#include "../../datastructures/reachability/Settings.h"
#include "Plotter.h"
#include "ReachTreePlotter.h"

#include <cstdlib>
#include <iostream>
#include <string>

namespace hypro::plotting {

    template<typename Representation>
    class InteractivePlotter {
    public:
        InteractivePlotter(std::vector<ReachTreeNode<Representation>> &roots, PlottingSettings settings)
                : mRoots(roots), mSettings(std::move(settings)) {}

        void run();

    private:
        void addSegments(ReachTreeNode<Representation> *node);

        void removeSegments(ReachTreeNode<Representation> *node);

        void plotCurrent();

        void printCurrentOptions() const;

        ReachTreeNode<Representation> *mCurrent = nullptr;
        std::vector<ReachTreeNode<Representation>> &mRoots;
        PlottingSettings mSettings;
        std::map<ReachTreeNode<Representation> *, std::vector<std::size_t>> mNodeSegmentMapping{};
        std::map<const Location<typename Representation::NumberType> *, std::size_t> mLocationColorMapping{};
    };

}  // namespace hypro::plotting

#include "InteractivePlotter.tpp"
