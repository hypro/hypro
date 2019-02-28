#pragma once

#include "../@MHyProGeometricObjectInterface/MHyProGeometricObject.h"
#include "../../../datastructures/Halfspace.h"
#include <iostream>
#include <map>
#include <cassert>
#include "mex.h"
#include "matrix.h"
#include "../Handles/ClassHandle.h"
#include "../Handles/ObjectHandle.h"


class MHyProEllipsoid: public MHyProGeometricObject<hypro::Ellipsoid<double>>{
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

#include "MHyProEllipsoid.tpp"