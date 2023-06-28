/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/representations/GeometricObjectBase.h>

using namespace hypro;

int main() {

    using maptype = Eigen::Map<Eigen::Matrix<double, Eigen::Dynamic, 1>>;

    double *values = new double[3];
    values[0] = 1.0;
    values[1] = 2.0;
    values[2] = 3.0;

    std::size_t dim = 3;

    maptype testMap = maptype(values, dim);

    for (std::size_t i = 0; i < dim; ++i) {
        std::cout << testMap(i) << std::endl;
    }

    vector_t<double> testVec{testMap};

    for (std::size_t i = 0; i < dim; ++i) {
        std::cout << testVec(i) << std::endl;
    }

    delete values;

    return 0;
}
