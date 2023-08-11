/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Created by stefan on 06.09.21.
 */

#ifndef HYPRO_PATHUTIL_H
#define HYPRO_PATHUTIL_H

#include "Pathv2.h"

namespace hypro {

    template<typename N>
    bool has_discrete_cycle(const Path<N> &path) {
        for (auto cur_it = std::begin(path.elements); cur_it != std::end(path.elements); ++cur_it) {
            if (std::find_if(std::next(cur_it), std::end(path.elements),
                             [&cur_it](const auto &elem) { return elem.second == cur_it->second; }) !=
                std::end(path.elements)) {
                // std::cout << "Path " << path << " has a discrete cycle with location " << ( ( cur_it )->second->getTarget()->getName() ) << std::endl;
                return true;
            }
        }
        return false;
    }

}  // namespace hypro

#endif    // HYPRO_PATHUTIL_H
