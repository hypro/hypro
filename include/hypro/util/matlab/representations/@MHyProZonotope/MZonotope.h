/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * Wrapper class for zonotopes.
 */

#pragma once

#include "../../../../representations/Zonotope/Zonotope.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "matrix.h"
#include "mex.h"

#include <iostream>
#include <string>

class MZonotope : public MGeometricObject<hypro::Zonotope<double>> {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void newZonotopeDimension(int, mxArray **, int, const mxArray **);

    static void newZonotopeCG(int, mxArray **, int, const mxArray **);

    static void copyDimensions(int, mxArray **, int, const mxArray **);

    static void emptyAt(int, mxArray **, int, const mxArray **);

    static void setCenter(int, mxArray **, int, const mxArray **);

    static void setGenerators(int, mxArray **, int, const mxArray **);

    static void addGenerators(int, mxArray **, int, const mxArray **);

    static void center(int, mxArray **, int, const mxArray **);

    static void generators(int, mxArray **, int, const mxArray **);

    static void order(int, mxArray **, int, const mxArray **);

    static void removeEmptyGenerators(int, mxArray **, int, const mxArray **);

    static void uniteEqualVectors(int, mxArray **, int, const mxArray **);

    static void changeDimension(int, mxArray **, int, const mxArray **);

    static void print(int, mxArray **, int, const mxArray **);

    static void reduceOrder(int, mxArray **, int, const mxArray **);

    static void computeZonotopeBoundary(int, mxArray **, int, const mxArray **);

    static void intersectHalfspacesMethod(int, mxArray **, int, const mxArray **);

    static void intersectHalfspaceMethod(int, mxArray **, int, const mxArray **);

    static void intersectMinMax(int, mxArray **, int, const mxArray **);

    static void intervalHull(int, mxArray **, int, const mxArray **);

    static void supremum(int, mxArray **, int, const mxArray **);

    static void type(int, mxArray **, int, const mxArray **);

    static void reduceNumberRepresentation(int, mxArray **, int, const mxArray **);
};

#include "MZonotope.tpp"
