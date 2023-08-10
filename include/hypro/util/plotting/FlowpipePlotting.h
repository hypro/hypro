/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by Stefan Schupp <stefan.schupp@tuwien.ac.at> on 03.03.22.
 */

#pragma once

#include "../../datastructures/reachability/ReachTreev2.h"
#include "../../datastructures/reachability/ReachTreev2Util.h"
#include "Plotter.h"

#include <vector>

namespace hypro {

    template<typename Representation>
    void plotReachableSets(const std::vector<ReachTreeNode<Representation>> &roots,
                           Plotter<typename Representation::NumberType> &plt,
                           const std::vector<std::size_t> &dimensions) {
        if (dimensions.size() != 2) {
            throw std::logic_error("Require exactly two dimensions for plotting");
        }
        for (const auto &root: roots) {
            for (const ReachTreeNode<Representation> &node: preorder(root)) {
                for (const auto &set: node.getFlowpipe()) {
                    plt.addObject(set.projectOn(dimensions).vertices());
                }
            }
        }
    }

}  // namespace hypro
