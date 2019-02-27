#pragma once

#include "../../../types.h"
#include "mex.h"
#include "matrix.h"
#include "../Handles/ClassHandle.h"
#include "../Handles/ObjectHandle.h"
#include "MFlow.h"

class MLinearFlow: public MFlow<hypro::linearFlow<double>>{
 public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
        static void new_mat(int, mxArray**, int, const mxArray**);
        static void setFlowMatrix(int, mxArray**, int, const mxArray**);
        static void addRow(int, mxArray**, int, const mxArray**);
        static void getFlowMatrix(int, mxArray**, int, const mxArray**);
        static void isIdentity(int, mxArray**, int, const mxArray**);
        static void hasNoFlow(int, mxArray**, int, const mxArray**);
        static void outstream(int, mxArray**, int, const mxArray**);

};

#include "MLinearFlow.tpp"