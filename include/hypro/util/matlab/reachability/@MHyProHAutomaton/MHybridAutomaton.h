/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 *   Wrapper class for hybrid automata.
 */

#pragma once

#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"
#include "matrix.h"
#include "mex.h"

class MHybridAutomaton {
public:
    static void process(int, mxArray **, int, const mxArray **);

private:
    static void new_empty(int, mxArray **, int, const mxArray **);

    static void copy(int, mxArray **, int, const mxArray **);

    static void new_loc_init(int, mxArray **, int, const mxArray **);

    static void delete_autom(int, mxArray **, int, const mxArray **);

    static void getLocations(int, mxArray **, int, const mxArray **);

    static void getLocation_by_hash(int, mxArray **, int, const mxArray **);

    static void getLocation_by_name(int, mxArray **, int, const mxArray **);

    static void getTransitions(int, mxArray **, int, const mxArray **);

    static void getInitialStates(int, mxArray **, int, const mxArray **);

    static void getLocalBadStates(int, mxArray **, int, const mxArray **);

    static void getGlobalBadStates(int, mxArray **, int, const mxArray **);

    static void dimension(int, mxArray **, int, const mxArray **);

    static void getVariables(int, mxArray **, int, const mxArray **);

    static void getLabels(int, mxArray **, int, const mxArray **);

    static void setLocations(int, mxArray **, int, const mxArray **);

    static void setInitialStates(int, mxArray **, int, const mxArray **);

    static void setLocalBadStates(int, mxArray **, int, const mxArray **);

    static void setGlobalBadStates(int, mxArray **, int, const mxArray **);

    static void setVariables(int, mxArray **, int, const mxArray **);

    static void addLocation(int, mxArray **, int, const mxArray **);

    static void addTransition(int, mxArray **, int, const mxArray **);

    static void addInitialState(int, mxArray **, int, const mxArray **);

    static void addLocalBadStates(int, mxArray **, int, const mxArray **);

    static void addGlobalBadStates(int, mxArray **, int, const mxArray **);

    static void decompose(int, mxArray **, int, const mxArray **);

    static void reduce(int, mxArray **, int, const mxArray **);

    static void isComposedOf(int, mxArray **, int, const mxArray **);

    static void getDotRepresentation(int, mxArray **, int, const mxArray **);

    static void getStatistics(int, mxArray **, int, const mxArray **);

    static void equals(int, mxArray **, int, const mxArray **);

    static void unequals(int, mxArray **, int, const mxArray **);

    static void plus(int, mxArray **, int, const mxArray **);

    static void outstream(int, mxArray **, int, const mxArray **);

    static void checkConsistency(int, mxArray **, int, const mxArray **);

    static void parallelComposition(int, mxArray **, int, const mxArray **);
};

#include "MHybridAutomaton.tpp"
