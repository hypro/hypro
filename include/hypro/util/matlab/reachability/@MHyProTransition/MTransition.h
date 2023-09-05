/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *   Wrapper class for transition.
 */
#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

class MTransition {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void new_empty(int, mxArray **, int, const mxArray **);

    static void new_source_target(int, mxArray **, int, const mxArray **);

    static void new_full(int, mxArray **, int, const mxArray **);

    static void copy(int, mxArray **, int, const mxArray **);

    static void delete_tran(int, mxArray **, int, const mxArray **);

    static void getTarget(int, mxArray **, int, const mxArray **);

    static void getSource(int, mxArray **, int, const mxArray **);

    static void getGuard(int, mxArray **, int, const mxArray **);

    static void getReset(int, mxArray **, int, const mxArray **);

    static void getAggregation(int, mxArray **, int, const mxArray **);

    static void getTriggerTime(int, mxArray **, int, const mxArray **);

    static void isUrgent(int, mxArray **, int, const mxArray **);

    static void isTimeTriggered(int, mxArray **, int, const mxArray **);

    static void hasIdentityReset(int, mxArray **, int, const mxArray **);

    static void getLabels(int, mxArray **, int, const mxArray **);

    static void hash(int, mxArray **, int, const mxArray **);

    static void setSource(int, mxArray **, int, const mxArray **);

    static void setTarget(int, mxArray **, int, const mxArray **);

    static void setGuard(int, mxArray **, int, const mxArray **);

    static void setReset(int, mxArray **, int, const mxArray **);

    static void setAggregation(int, mxArray **, int, const mxArray **);

    static void setUrgent(int, mxArray **, int, const mxArray **);

    static void setTriggerTime(int, mxArray **, int, const mxArray **);

    static void setLabels(int, mxArray **, int, const mxArray **);

    static void addLabel(int, mxArray **, int, const mxArray **);

    static void getDotRepresentation(int, mxArray **, int, const mxArray **);

    static void isComposedOf(int, mxArray **, int, const mxArray **);

    static void decompose(int, mxArray **, int, const mxArray **);

    static void outstream(int, mxArray **, int, const mxArray **);

    static void equals(int, mxArray **, int, const mxArray **);

    static void nequals(int, mxArray **, int, const mxArray **);
};

#include "MTransition.tpp"
