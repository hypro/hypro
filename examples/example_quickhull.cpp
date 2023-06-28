/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/algorithms/quickhull/Quickhull.h>
#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

using number_t = mpq_class;

int main() {
    std::vector<Point<number_t>> points;

    points.push_back(Point<number_t>{6, 0, 1});
    points.push_back(Point<number_t>{1, 12, 18});
    points.push_back(Point<number_t>{1, 0, 15});
    points.push_back(Point<number_t>{3, 14, 3});
    points.push_back(Point<number_t>{17, 4, 16});

    HPolytope<number_t> hpoly{points};

    VPolytope<number_t> vpoly{hpoly.matrix(), hpoly.vector()};

    TRACE("quickhull", vpoly);
}
