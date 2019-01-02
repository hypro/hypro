#pragma once

#include "../../representations/GeometricObject.h"
#include "../../datastructures/Halfspace.h"
#include <iostream>
#include <map>
#include <cassert>
#include "mex.h"
#include "matrix.h"
#include "ClassHandle.h"
#include "ObjectHandle.h"


class HyProEllipsoid{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void ellipsoid_rad(int, mxArray**, int, const mxArray**);
        static void ellipsoid_mat(int, mxArray**, int, const mxArray**);
        static void copy(int, mxArray**, int, const mxArray**);
        static void deleteEllipsoid(int, mxArray**, int, const mxArray**);
        static void matrix(int, mxArray**, int, const mxArray**);
        static void dimension(int, mxArray**, int, const mxArray**);
        static void is_empty(int, mxArray**, int, const mxArray**);
        static void equal(int, mxArray**, int, const mxArray**);
        static void unequal(int, mxArray**, int, const mxArray**);
        static void ostream(int, mxArray**, int, const mxArray**);
        static void linearTransformation(int, mxArray**, int, const mxArray**);
        static void affineTransformation(int, mxArray**, int, const mxArray**);
        static void minkowskiSum(int, mxArray**, int, const mxArray**);
        static void evaluate(int, mxArray**, int, const mxArray**);
        static void approxEllipsoidTMatrix(int, mxArray**, int, const mxArray**);
        
};

#include "HyProEllipsoid.tpp"