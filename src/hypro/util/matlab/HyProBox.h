#pragma once

#include "../../representations/GeometricObject.h"
#include <iostream>
#include "mex.h"
#include "matrix.h"
#include "ClassHandle.h"
#include "ObjectHandle.h"


class HyProBox{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void emptyBox(int, mxArray**, const mxArray**);
        static void copyBox(int, mxArray**, const mxArray**);
        static void boxFromSingleInterval(int, mxArray**, const mxArray**);
        static void boxFromIntervals(int, mxArray**, const mxArray**);
        static void boxFromPoints(int, mxArray**, const mxArray**);
        static void boxFromMatrix(int, mxArray**, int, const mxArray**);
        static void deleteBox(int nlhs, int nrhs, const mxArray *prhs[]);
        static void getSettings(int, mxArray**, const mxArray**);
        static void empty(int, mxArray**, int, const mxArray**);
        static void intervals(int, mxArray**, const mxArray**);
        static void insert(int, mxArray**, int, const mxArray**);
        static void limits(int, mxArray**, int, const mxArray**);
        static void constraints(int, mxArray**, int, const mxArray**);
        static void interval(int, mxArray**, int, const mxArray**);
        static void at(int, mxArray**, int, const mxArray**);
        static void is_empty(int, mxArray**, int, const mxArray**);
        static void is_symmetric(int, mxArray**, int, const mxArray**);
        static void max(int, mxArray**, int, const mxArray**);
        static void min(int, mxArray**, int, const mxArray**);
        static void supremum(int, mxArray**, int, const mxArray**);
        static void vertices(int, mxArray**, int, const mxArray**);
        static void evaluate(int, mxArray**, int, const mxArray**);
        static void multiEvaluate(int, mxArray**, int, const mxArray**);
        static void equals(int, mxArray**, int, const mxArray**);
        static void unequal(int, mxArray**, int, const mxArray**);
        static void multiply(int, mxArray**, int, const mxArray**);
        static void outstream(int, mxArray**, int, const mxArray**);
        static void dimension(int, mxArray**, int, const mxArray**);
        static void removeRedundancy(int, mxArray**, int, const mxArray**);
        static void box_size(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
        static void reduceNumberRepresentation(int, mxArray**, int, const mxArray**);
        static void makeSymmetric(int, mxArray**, int, const mxArray**);
        static void satisfiesHalfspace(int, mxArray**, int, const mxArray**);
        static void satisfiesHalfspaces(int, mxArray**, int, const mxArray**);
        static void project(int, mxArray**, int, const mxArray**);
        static void linearTransformation(int, mxArray**, int, const mxArray**);
        static void affineTransformation(int, mxArray**, int, const mxArray**);
        static void minkowskiSum(int, mxArray**, int, const mxArray**);
        static void minkowskiDecomposition(int, mxArray**, int, const mxArray**);
        static void intersect(int, mxArray**, int, const mxArray**);
        static void intersectHalfspace(int, mxArray**, int, const mxArray**);
        static void intersectHalfspaces(int, mxArray**, int, const mxArray**);
        static void contains_point(int, mxArray**, int, const mxArray**);
        static void contains_box(int, mxArray**, int, const mxArray**);
        static void unite_box(int, mxArray**, int, const mxArray**);
        static void unite_boxes(int, mxArray**, int, const mxArray**);
        static void reduceRepresentation(int, mxArray**, int, const mxArray**);
        static void clear_box(int, mxArray**, int, const mxArray**);
        static void matrix(int, mxArray**, int, const mxArray**);
        static void vector(int, mxArray**, int, const mxArray**);

};

#include "HyProBox.tpp"