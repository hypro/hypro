/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <iosfwd>

namespace hypro {

    struct TreeStatistic {
        double avgBranching = 0.0;
        double avgLevel = 0.0;
        std::size_t nodeCnt = 0;
        std::size_t depth = 0;
        std::vector <std::size_t> levelCnt;
    };

}  // namespace hypro

namespace std {

    inline std::ostream &operator<<(std::ostream &out, const hypro::TreeStatistic &in) {
        out << "Average branching: \t\t" << in.avgBranching << std::endl;
        out << "Average refinement level: \t" << in.avgLevel << std::endl;
        out << "Maximal refinement level: \t" << in.levelCnt.size() - 1 << std::endl;
        out << "Number nodes: \t\t\t" << in.nodeCnt << std::endl;
        out << "Depth: \t\t\t\t" << in.depth << std::endl;
        std::size_t i = 0;
        while (i < in.levelCnt.size()) {
            out << "Nodes at level " << i << ": " << in.levelCnt[i] << std::endl;
            ++i;
        }
        return out;
    }

}  // namespace std
