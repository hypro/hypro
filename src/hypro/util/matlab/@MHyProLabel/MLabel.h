#pragma once

#include "../../../datastructures/HybridAutomaton/Label.h"
#include "../../../types.h"
#include <map>
#include "mex.h"
#include "matrix.h"
#include "../ClassHandle.h"
#include "../ObjectHandle.h"

class MLabel{

    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_empty(int, mxArray**, int, const mxArray**);
        static void copy(int, mxArray**, int, const mxArray**);
        static void del_label(int, mxArray**, int, const mxArray**);

};

#include "MLabel.tpp"