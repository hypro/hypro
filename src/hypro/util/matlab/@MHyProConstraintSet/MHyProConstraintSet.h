#pragma once


// #include "../../../datastructures/Halfspace.h"
// #include <iostream>
// #include <map>
// #include <cassert>
#include "../@MHyProGeometricObjectInterface/MHyProGeometricObject.h"
#include "mex.h"
#include "matrix.h"
#include "../ClassHandle.h"
#include "../ObjectHandle.h"


class MHyProConstraintSet: public MHyProGeometricObject<hypro::ConstraintSet<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void isAxisAligned(int, mxArray**, int, const mxArray**);
        static void addConstraint(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
        static void reduceNumberRepresentation(int, mxArray**, int, const mxArray**);
};

#include "MHyProConstraintSet.tpp"