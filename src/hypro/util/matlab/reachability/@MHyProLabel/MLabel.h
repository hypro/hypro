/*
*   Wrapper class for label.
*/

#pragma once

#include "../../../../datastructures/HybridAutomaton/Label.h"
#include "../../../../types.h"
#include <map>
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MLabel{

    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_name(int, mxArray**, int, const mxArray**);
        static void copy(int, mxArray**, int, const mxArray**);
        static void del_label(int, mxArray**, int, const mxArray**);
        static void getName(int, mxArray**, int, const mxArray**);
        static void setName(int, mxArray**, int, const mxArray**);
        static void equals(int, mxArray**, int, const mxArray**);
        static void unequals(int, mxArray**, int, const mxArray**);
        static void less(int, mxArray**, int, const mxArray**);
};

#include "MLabel.tpp"