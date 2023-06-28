/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
*   Wrapper class for location.
*/

#pragma once

#include <mex.h>
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"

class MLocation {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void new_empty(int, mxArray **, int, const mxArray **);

    static void new_matrix(int, mxArray **, int, const mxArray **);

    static void new_mat_tran_inv(int, mxArray **, int, const mxArray **);

    static void copy(int, mxArray **, int, const mxArray **);

    static void delete_loc(int, mxArray **, int, const mxArray **);

    static void getNumberFlow(int, mxArray **, int, const mxArray **);

    static void getLinearFlow(int, mxArray **, int, const mxArray **);

    static void getLinearFlows(int, mxArray **, int, const mxArray **);

    static void getInvariant(int, mxArray **, int, const mxArray **);

    static void getTransitions(int, mxArray **, int, const mxArray **);

    static void getExternalInput(int, mxArray **, int, const mxArray **);

    static void hasExternalInput(int, mxArray **, int, const mxArray **);

    static void hash(int, mxArray **, int, const mxArray **);

    static void getName(int, mxArray **, int, const mxArray **);

    static void dimension(int, mxArray **, int, const mxArray **);

    static void dimension_at(int, mxArray **, int, const mxArray **);

    static void setName(int, mxArray **, int, const mxArray **);

    static void setFlow(int, mxArray **, int, const mxArray **);

    static void setLinearFlow(int, mxArray **, int, const mxArray **);

    static void setLinearFlow_vec(int, mxArray **, int, const mxArray **);

    static void setInvariant(int, mxArray **, int, const mxArray **);

    // static void setTransition(int, mxArray**, int , const mxArray**);
    static void addTransition(int, mxArray **, int, const mxArray **);

    static void setExtInput(int, mxArray **, int, const mxArray **);

    static void isComposedOf(int, mxArray **, int, const mxArray **);

    // static void getDotRepresentation(int, mxArray**, int , const mxArray**);
    static void decompose(int, mxArray **, int, const mxArray **);

    static void less(int, mxArray **, int, const mxArray **);

    static void equals(int, mxArray **, int, const mxArray **);

    static void unequals(int, mxArray **, int, const mxArray **);

    static void outstream(int, mxArray **, int, const mxArray **);
};

#include "MLocation.tpp"
