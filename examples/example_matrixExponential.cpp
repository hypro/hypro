/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hypro/types.h>


int main() {
    using namespace hypro;
    using Number = double;

    matrix_t<Number> A = matrix_t<Number>::Zero(13, 13);
    vector_t<Number> p = vector_t<Number>::Ones(13);

    A << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
            0, 1.605, 4.868, -3.5754, -0.8198, 0.427, -0.045, -0.1942, 0.3626, -0.0946, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0,
            0, 0.8718, 3.814, -0.0754, 1.1936, 3.6258, -3.2396, -0.595, 0.1294, -0.0796, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0,
            0, 0.7132, 3.573, -0.0964, 0.8472, 3.2568, -0.0876, 1.2726, 3.072, -3.1356, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;

    std::cout << "A: " << std::endl << A << std::endl;

    matrix_t<Number> A1 = (A).exp();
    matrix_t<Number> A2 = (A * 0.1).exp();
    matrix_t<Number> A3 = (A * 0.01).exp();
    matrix_t<Number> A4 = (A * 0.001).exp();

    // test different exponentiations.
    std::cout << "exp A1: " << std::endl << A1 << std::endl;

    std::cout << "exp A2: " << std::endl << A2 << std::endl;

    std::cout << "exp A3: " << std::endl << A3 << std::endl;

    std::cout << "exp A4: " << std::endl << A4 << std::endl;

    std::cout << "######################" << std::endl;

    vector_t<Number> r1 = p;
    vector_t<Number> r2 = p;
    vector_t<Number> r3 = p;
    vector_t<Number> r4 = p;

    for (int i1 = 0; i1 < 1000; ++i1) {
        r1 = A1 * (r1);
        for (int i2 = 0; i2 < 10; ++i2) {
            r2 = A2 * (r2);
            for (int i3 = 0; i3 < 10; ++i3) {
                r3 = A3 * (r3);
                for (int i4 = 0; i4 < 10; ++i4) {
                    r4 = A4 * (r4);
                }
            }
        }
    }

    std::cout << "P1 " << r1 << std::endl;
    std::cout << "P2 " << r2 << std::endl;
    std::cout << "P3 " << r3 << std::endl;
    std::cout << "P4 " << r4 << std::endl;

    return 0;
}
