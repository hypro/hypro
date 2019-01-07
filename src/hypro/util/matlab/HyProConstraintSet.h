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

class HyProConstraintSet: public HyProGeometricObject<hypro::ConstraintSet<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void isAxisAligned(int, mxArray**, int, const mxArray**);
        static void addConstraint(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
        static void reduceNumberRepresentation(int, mxArray**, int, const mxArray**);
};

#include "HyProConstraintSet.tpp"