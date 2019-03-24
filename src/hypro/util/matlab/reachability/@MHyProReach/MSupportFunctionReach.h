#pragma once

#include "MReach.h"
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MSupportFunctionReach: public MReach<hypro::SupportFunction<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
};

#include "MSupportFunctionReach.tpp"