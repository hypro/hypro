/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * Example file for linear transformation of a H-Polytope.
 * @brief [brief description]
 * @details [long description]
 *
 */

#include <hypro/datastructures/Halfspace.h>
#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>

using namespace hypro;

int main() {
    typedef mpq_class Number;

    HPolytope<Number> box;
    box.insert(Halfspace<Number>({Number(1), Number(0)}, Number(1)));
    box.insert(Halfspace<Number>({Number(0), Number(1)}, Number(1)));
    box.insert(Halfspace<Number>({Number(-1), Number(0)}, Number(1)));
    box.insert(Halfspace<Number>({Number(0), Number(-1)}, Number(1)));

    matrix_t<Number> A = matrix_t<Number>(2, 2);
    A << 2, 0, 0, 2;
    vector_t<Number> b = vector_t<Number>(2);
    b << 5, 0;

    HPolytope<Number> boxTrafoed = box.affineTransformation(A, b);
    // HPolytope<Number> boxTrafoed =
    // box.linearTransformation(A,vector_t<Number>::Zero(2));
    std::cout << boxTrafoed << std::endl;

    Plotter<Number> &plotter = Plotter<Number>::getInstance();
    plotter.addObject(box.vertices());
    unsigned obj2 = plotter.addObject(boxTrafoed.vertices());
    plotter.setObjectColor(obj2, plotting::colors[plotting::red]);

    plotter.plot2d();

    return 0;
}
