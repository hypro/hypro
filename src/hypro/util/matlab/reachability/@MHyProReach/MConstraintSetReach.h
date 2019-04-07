#pragma once

#include "MReach.h"
#include "mex.h"
#include "matrix.h"
#include "../../handles/ClassHandle.h"
#include "../../handles/ObjectHandle.h"


class MConstraintSetReach: public MReach<hypro::State<double, hypro::ConstraintSet<double>>>{
    public:
        static void process(int, mxArray**, int, const mxArray**);
    private:
};

#include "MConstraintSetReach.tpp"