/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *   Wrapper class for reset.
 */

#pragma once

#include "../../../../types.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

#include <map>

class MReset {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void new_empty(int, mxArray **, int, const mxArray **);

    static void copy(int, mxArray **, int, const mxArray **);

    static void new_mat_vec(int, mxArray **, int, const mxArray **);

    static void new_intervals(int, mxArray **, int, const mxArray **);

    static void delete_reset(int, mxArray **, int, const mxArray **);

    static void empty(int, mxArray **, int, const mxArray **);

    static void size(int, mxArray **, int, const mxArray **);

    static void getVector(int, mxArray **, int, const mxArray **);

    static void getMatrix(int, mxArray **, int, const mxArray **);

    static void getIntervals(int, mxArray **, int, const mxArray **);

    static void getAffineReset_at(int, mxArray **, int, const mxArray **);

    static void getAffineResets(int, mxArray **, int, const mxArray **);

    static void getIntervalReset_at(int, mxArray **, int, const mxArray **);

    static void getIntervalResets(int, mxArray **, int, const mxArray **);

    static void setVector(int, mxArray **, int, const mxArray **);

    static void setMatrix(int, mxArray **, int, const mxArray **);

    static void setIntervals(int, mxArray **, int, const mxArray **);

    static void isIdentity(int, mxArray **, int, const mxArray **);

    static void hash(int, mxArray **, int, const mxArray **);

    static void decompose(int, mxArray **, int, const mxArray **);

    static void combine(int, mxArray **, int, const mxArray **);
};

#include "MReset.tpp"
