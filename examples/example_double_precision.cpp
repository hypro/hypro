/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//
// Created by Jannik Hüls on 01.08.18.
//

#include <hypro/representations/GeometricObjectBase.h>
#include <hypro/util/plotting/Plotter.h>
#include <gmpxx.h>

int main() {
    using Number = double;
    // using Number = mpq_class;
    using namespace hypro;

    vector_t<Number> v = vector_t<Number>::Zero(3);
    v << 0, 0, 0;
    Point<Number> p4(v);
    v << 3, 1, 0;
    Point<Number> p1(v);
    v << 5, 5, 0;
    Point<Number> p2(v);
    v << 5, 5, 5;
    Point<Number> p3(v);

    HPolytope<Number> boxPolytope({p1, p2, p3, p4});
}
