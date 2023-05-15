/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *   Wrapper class for linear flow.
 */

#pragma once

#include "../../../../types.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "MFlow.h"
#include "matrix.h"
#include "mex.h"

class MLinearFlow : public MFlow<hypro::linearFlow<double>> {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void new_mat(int, mxArray **, int, const mxArray **);

    static void setFlowMatrix(int, mxArray **, int, const mxArray **);

    static void addRow(int, mxArray **, int, const mxArray **);

    static void getFlowMatrix(int, mxArray **, int, const mxArray **);

    static void isIdentity(int, mxArray **, int, const mxArray **);

    static void hasNoFlow(int, mxArray **, int, const mxArray **);

    static void outstream(int, mxArray **, int, const mxArray **);
};

#include "MLinearFlow.tpp"
