#pragma once

#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MConstraintSet: public MGeometricObject<hypro::ConstraintSet<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_empty(int, mxArray**, int, const mxArray**);
        static void isAxisAligned(int, mxArray**, int, const mxArray**);
        static void addConstraint(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
        static void reduceNumberRepresentation(int, mxArray**, int, const mxArray**);
        static void linearTransformation(int, mxArray**, int, const mxArray**);
};

#include "MConstraintSet.tpp"