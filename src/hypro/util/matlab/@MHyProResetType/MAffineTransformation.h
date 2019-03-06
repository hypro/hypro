#pragma once

#include "../../../datastructures/HybridAutomaton/ResetTypes.h"
#include "../../../types.h"
#include <map>
#include "mex.h"
#include "matrix.h"
#include "../Handles/ClassHandle.h"
#include "../Handles/ObjectHandle.h"


class MAffineTransformation{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_empty(int, mxArray**, int, const mxArray**);
        static void copy(int, mxArray**, int, const mxArray**);
        static void new_constraints(int, mxArray**, int, const mxArray**);
        static void delete_reset(int, mxArray**, int, const mxArray**);
        static void type(int, mxArray**, int, const mxArray**);
        static void size(int, mxArray**, int, const mxArray**);
        static void isIdentity(int, mxArray**, int, const mxArray**);
        static void equals(int, mxArray**, int, const mxArray**);
};

#include "MAffineTransformation.tpp"