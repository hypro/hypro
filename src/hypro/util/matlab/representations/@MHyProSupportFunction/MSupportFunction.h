/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Wrapper class for support functions.
 */

#pragma once

#include "../../../../datastructures/Halfspace.h"
#include "../../../../representations/GeometricObject.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"
#include <cassert>
#include <iostream>
#include <map>

class MSupportFunction : public MGeometricObject<hypro::SupportFunction<double>> {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void new_points(int, mxArray **, int, const mxArray **);

    static void new_intervals(int, mxArray **, int, const mxArray **);

    static void new_halfspaces(int, mxArray **, int, const mxArray **);

    static void type(int, mxArray **, int, const mxArray **);

    static void depth(int, mxArray **, int, const mxArray **);

    static void operationCount(int, mxArray **, int, const mxArray **);

    static void contains_vec(int, mxArray **, int, const mxArray **);

    static void contains_dir(int, mxArray **, int, const mxArray **);

    static void swap(int, mxArray **, int, const mxArray **);

    static void scale(int, mxArray **, int, const mxArray **);

    static void forceLinTransReduction(int, mxArray **, int, const mxArray **);

    static void cleanUp(int, mxArray **, int, const mxArray **);

    static void collectProjections(int, mxArray **, int, const mxArray **);

    static void reduceNumberRepresentation(int, mxArray **, int, const mxArray **);
};

#include "MSupportFunction.tpp"
