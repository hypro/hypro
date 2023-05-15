/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Wrapper class for boxes.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"

#include <iostream>
#include <string>

class MBox : public MGeometricObject<hypro::Box<double>> {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void boxFromSingleInterval(int, mxArray **, int, const mxArray **);

    static void boxFromIntervals(int, mxArray **, int, const mxArray **);

    static void boxFromPoints(int, mxArray **, int, const mxArray **);

    static void empty(int, mxArray **, int, const mxArray **);

    static void intervals(int, mxArray **, int, const mxArray **);

    static void insert(int, mxArray **, int, const mxArray **);

    static void limits(int, mxArray **, int, const mxArray **);

    static void constraints(int, mxArray **, int, const mxArray **);

    static void interval(int, mxArray **, int, const mxArray **);

    static void at(int, mxArray **, int, const mxArray **);

    static void is_symmetric(int, mxArray **, int, const mxArray **);

    static void max(int, mxArray **, int, const mxArray **);

    static void min(int, mxArray **, int, const mxArray **);

    static void type(int, mxArray **, int, const mxArray **);

    static void makeSymmetric(int, mxArray **, int, const mxArray **);

    static void minkowskiDecomposition(int, mxArray **, int, const mxArray **);
};

#include "MBox.tpp"
