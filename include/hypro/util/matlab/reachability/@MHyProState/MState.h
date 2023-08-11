/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *   Wrapper class for state.
 */

#pragma once

#include "../../../../datastructures/HybridAutomaton/State.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

class MState {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void vertices(int, mxArray **, int, const mxArray **);

    static void copy(int, mxArray **, int, const mxArray **);

    static void del_state(int, mxArray **, int, const mxArray **);

    static void new_empty(int, mxArray **, int, const mxArray **);

    static void new_loc(int, mxArray **, int, const mxArray **);

    static void getLocation(int, mxArray **, int, const mxArray **);

    static void getNumberSets(int, mxArray **, int, const mxArray **);

    static void getSetType(int, mxArray **, int, const mxArray **);

    static void getSets(int, mxArray **, int, const mxArray **);

    static void getTypes(int, mxArray **, int, const mxArray **);

    static void getTimestamp(int, mxArray **, int, const mxArray **);

    static void isEmpty(int, mxArray **, int, const mxArray **);

    static void setLocation(int, mxArray **, int, const mxArray **);

    // static void setSet(int, mxArray**, int, const mxArray**);
    static void setSetType(int, mxArray **, int, const mxArray **);

    static void setTimestamp(int, mxArray **, int, const mxArray **);

    static void setSets(int, mxArray **, int, const mxArray **);

    static void setSetSave(int, mxArray **, int, const mxArray **);

    static void setSetDirect(int, mxArray **, int, const mxArray **);

    static void setAndConvertType(int, mxArray **, int, const mxArray **);

    static void addTimeToClocks(int, mxArray **, int, const mxArray **);

    static void unite(int, mxArray **, int, const mxArray **);

    static void satisfies(int, mxArray **, int, const mxArray **);

    static void satisfiesHalfspaces(int, mxArray **, int, const mxArray **);

    static void intersectHalfspaces(int, mxArray **, int, const mxArray **);

    static void partiallySatisfies(int, mxArray **, int, const mxArray **);

    static void applyTimeStep(int, mxArray **, int, const mxArray **);

    static void partiallyApplyTimeStep(int, mxArray **, int, const mxArray **);

    static void applyTransformation_vec(int, mxArray **, int, const mxArray **);

    static void applyTransformation_at(int, mxArray **, int, const mxArray **);

    static void applyTransformation(int, mxArray **, int, const mxArray **);

    static void linearTransformation(int, mxArray **, int, const mxArray **);

    static void affineTransformation(int, mxArray **, int, const mxArray **);

    static void partialIntervalAssignment(int, mxArray **, int, const mxArray **);

    static void partiallyApplyTransformation_vec(int, mxArray **, int, const mxArray **);

    static void partiallyApplyTransformation(int, mxArray **, int, const mxArray **);

    static void minkowskiSum(int, mxArray **, int, const mxArray **);

    static void partiallyMinkowskiSum(int, mxArray **, int, const mxArray **);

    static void contains(int, mxArray **, int, const mxArray **);

    static void projectOn(int, mxArray **, int, const mxArray **);

    static void getDimension(int, mxArray **, int, const mxArray **);

    static void getDimensionOffset(int, mxArray **, int, const mxArray **);

    static void getSupremum(int, mxArray **, int, const mxArray **);

    static void removeRedundancy(int, mxArray **, int, const mxArray **);

    static void partiallyRemoveRedundancy(int, mxArray **, int, const mxArray **);

    static void reduceRepresentation(int, mxArray **, int, const mxArray **);

    static void partiallyReduceRepresentation(int, mxArray **, int, const mxArray **);

    static void decompose(int, mxArray **, int, const mxArray **);

    static void outstream(int, mxArray **, int, const mxArray **);

    static void equals(int, mxArray **, int, const mxArray **);

    static void unequals(int, mxArray **, int, const mxArray **);
};

#include "MState.tpp"
