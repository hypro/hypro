/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MFlow.h"

template<typename T>
void MFlow<T>::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - new_empty: Expecting an output.");

    T *temp = new T();
    plhs[0] = convertPtr2Mat<T>(temp);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("new_empty\n");
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - copy: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MFlow - copy: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - copy: One or more arguments were ignored.");

    T *origin = convertMat2Ptr<T>(prhs[2]);
    plhs[0] = convertPtr2Mat<T>(new T(*origin));

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("copy\n");
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::delete_flow(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MFlow - delete_flow: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - delete_flow: One or more arguments were ignored.");

    destroyObject<T>(prhs[2]);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("delete\n");
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::type(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - type: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MFlow - type: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - type: One or more arguments were ignored.");

    T *flow = convertMat2Ptr<T>(prhs[2]);
    hypro::DynamicType type = flow->type();
    std::string ans = "";

    if (type == hypro::DynamicType::affine) {
        ans = "affine";
    } else if (type == hypro::DynamicType::discrete) {
        ans = "discrete";
    } else if (type == hypro::DynamicType::linear) {
        ans = "linaer";
    } else if (type == hypro::DynamicType::rectangular) {
        ans = "rectangluar";
    } else {
        ans = "timed";
    }
    plhs[0] = mxCreateString(ans.c_str());

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("type output:\n");
    mexPrintf("type: %s\n", ans.c_str());
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::dimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - dimension: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MFlow - dimension: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - dimension: One or more arguments were ignored.");

    T *flow = convertMat2Ptr<T>(prhs[2]);
    std::size_t dim = flow->dimension();
    plhs[0] = mxCreateDoubleScalar(dim);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("dimension output:\n");
    mexPrintf("dim: %d\n", (double) dim);
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::isTimed(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - isTimed: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MFlow - isTimed: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - isTimed: One or more arguments were ignored.");

    T *flow = convertMat2Ptr<T>(prhs[2]);
    const bool ans = flow->isTimed();
    plhs[0] = mxCreateLogicalScalar(ans);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("isTimed output:\n");
    if (ans) {
        mexPrintf("timed\n");
    } else {
        mexPrintf("not timed\n");
    }
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::isDiscrete(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - isDiscrete: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MFlow - isDiscrete: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - isDiscrete: One or more arguments were ignored.");

    T *flow = convertMat2Ptr<T>(prhs[2]);
    const bool ans = flow->isDiscrete();
    plhs[0] = mxCreateLogicalScalar(ans);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("isDiscrete output:\n");
    if (ans) {
        mexPrintf("discrete\n");
    } else {
        mexPrintf("not discrete\n");
    }
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - ==: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MFlow - ==: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MFlow - ==: One or more arguments were ignored.");

    T *flow_1 = convertMat2Ptr<T>(prhs[2]);
    T *flow_2 = convertMat2Ptr<T>(prhs[3]);
    mxLogical ans = false;
    if (*flow_1 == *flow_2) ans = true;

    plhs[0] = mxCreateLogicalScalar(ans);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("equals output:\n");
    if (ans) {
        mexPrintf("equal\n");
    } else {
        mexPrintf("not equal\n");
    }
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::unequals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - !=: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MFlow - !=: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MFlow - !=: One or more arguments were ignored.");

    T *flow_1 = convertMat2Ptr<T>(prhs[2]);
    T *flow_2 = convertMat2Ptr<T>(prhs[3]);
    mxLogical ans = false;
    if (*flow_1 != *flow_2) ans = true;

    plhs[0] = mxCreateLogicalScalar(ans);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("unequals output:\n");
    if (ans) {
        mexPrintf("unequal\n");
    } else {
        mexPrintf("not unequal\n");
    }
    //+++++++++++++TESTING++++++++++++++++++++
}

template<typename T>
void MFlow<T>::size(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MFlow - size: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MFlow - size: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MFlow - size: One or more arguments were ignored.");

    T *flow = convertMat2Ptr<T>(prhs[2]);
    std::size_t s = flow->size();
    plhs[0] = mxCreateDoubleScalar(s);

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("size output:\n");
    mexPrintf("size: %d\n", (double) s);
    //+++++++++++++TESTING++++++++++++++++++++
}
