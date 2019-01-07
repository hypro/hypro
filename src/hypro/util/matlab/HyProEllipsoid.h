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
#include "HyProGeometricObject.h"


class HyProEllipsoid: public HyProGeometricObject<hypro::Ellipsoid<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void ellipsoid_rad(int, mxArray**, int, const mxArray**);
        static void ellipsoid_mat(int, mxArray**, int, const mxArray**);
        static void evaluate(int, mxArray**, int, const mxArray**);
        static void approxEllipsoidTMatrix(int, mxArray**, int, const mxArray**);
        static void ostream(int, mxArray**, int, const mxArray**);
        
};

#include "HyProEllipsoid.tpp"