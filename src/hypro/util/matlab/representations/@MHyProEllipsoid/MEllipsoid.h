#pragma once

#include "../@MHyProGeometricObject/MGeometricObject.h"
#include <iostream>
#include <map>
#include <cassert>
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MEllipsoid: public MGeometricObject<hypro::Ellipsoid<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void ellipsoid_rad(int, mxArray**, int, const mxArray**);
        static void ellipsoid_mat(int, mxArray**, int, const mxArray**);
        // static void evaluate(int, mxArray**, int, const mxArray**);
        static void approxEllipsoidTMatrix(int, mxArray**, int, const mxArray**);
        static void ostream(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
};

#include "MEllipsoid.tpp"