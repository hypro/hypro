#pragma once

#include "../@MHyProGeometricObject/MGeometricObject.h"
#include "../../../../representations/GeometricObject.h"
#include "../../../../datastructures/Halfspace.h"
#include <iostream>
#include <map>
#include <cassert>
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MSupportFunction: public MGeometricObject<hypro::SupportFunction<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_empty(int, mxArray**, int, const mxArray**);
        static void new_points(int, mxArray**, int, const mxArray**);
        static void new_intervals(int, mxArray**, int, const mxArray**);
        static void new_halfspaces(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
        static void depth(int, mxArray**, int, const mxArray**);
        static void operationCount(int, mxArray**, int, const mxArray**);
        static void contains_vec(int, mxArray**, int, const mxArray**);
        static void contains_dir(int, mxArray**, int, const mxArray**);
        static void swap(int, mxArray**, int, const mxArray**);
        static void scale(int, mxArray**, int, const mxArray**);
        static void forceLinTransReduction(int, mxArray**, int, const mxArray**);
        static void cleanUp(int, mxArray**, int, const mxArray**);
        static void collectProjections(int, mxArray**, int, const mxArray**);
        static void reduceNumberRepresentation(int, mxArray**, int, const mxArray**);

};

#include "MSupportFunction.tpp"