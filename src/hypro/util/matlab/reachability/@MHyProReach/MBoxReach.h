#pragma once

#include "MReach.h"
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MBoxReach: public MReach<hypro::Box<double>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
};

#include "MBoxReach.tpp"