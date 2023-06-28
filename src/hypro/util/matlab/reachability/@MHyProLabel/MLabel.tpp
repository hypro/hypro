/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MLabel.h"

void MLabel::new_name(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLabel - new_name: Expecting an output.");
    if (nrhs != 3) mexErrMsgTxt("MLabel - new_name: Expecting two input arguments.");

    char name[64];
    mxGetString(prhs[2], name, sizeof(name));
    hypro::Label *temp = new hypro::Label(name);
    plhs[0] = convertPtr2Mat<hypro::Label>(temp);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "new_name input:\n" );
    // mexPrintf( "name: %s\n", name );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLabel::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLabel - copy: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLabel - copy: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLabel - copy: One or more arguments were ignored.");

    hypro::Label *origin = convertMat2Ptr<hypro::Label>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Label>(new hypro::Label(*origin));
}

void MLabel::del_label(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MLabel - del_label: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLabel - del_label: One or more arguments were ignored.");

    destroyObject<hypro::Label>(prhs[2]);
}

void MLabel::getName(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLabel - getName: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MLabel - getName: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MLabel - getName: One or more arguments were ignored.");

    hypro::Label *lab = convertMat2Ptr<hypro::Label>(prhs[2]);
    std::string name = lab->getName();
    plhs[0] = mxCreateString(name.c_str());

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getName output:\n" );
    // mexPrintf( "name: %s\n", name.c_str() );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLabel::setName(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MLabel - setName: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MLabel - setName: One or more arguments were ignored.");

    hypro::Label *lab = convertMat2Ptr<hypro::Label>(prhs[2]);
    char name[64];
    mxGetString(prhs[3], name, sizeof(name));
    lab->setName(name);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setName input:\n" );
    // mexPrintf( "name: %s\n", name );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLabel::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLabel - equals: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MLabel - equals: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MLabel - equals: One or more arguments were ignored.");

    hypro::Label *lab1 = convertMat2Ptr<hypro::Label>(prhs[2]);
    hypro::Label *lab2 = convertMat2Ptr<hypro::Label>(prhs[3]);

    mxLogical ans = false;
    if (*lab1 == *lab2) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "equals input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "equal\n" );
    // } else {
    // 	mexPrintf( "not equal\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLabel::unequals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLabel - unequals: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MLabel - unequals: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MLabel - unequals: One or more arguments were ignored.");

    hypro::Label *lab1 = convertMat2Ptr<hypro::Label>(prhs[2]);
    hypro::Label *lab2 = convertMat2Ptr<hypro::Label>(prhs[3]);

    mxLogical ans = false;
    if (*lab1 != *lab2) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "unequals input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "unequal\n" );
    // } else {
    // 	mexPrintf( "not unequal\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLabel::less(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MLabel - less: Expecting an output.");
    if (nrhs < 4) mexErrMsgTxt("MLabel - less: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MLabel - less: One or more arguments were ignored.");

    hypro::Label *lab1 = convertMat2Ptr<hypro::Label>(prhs[2]);
    hypro::Label *lab2 = convertMat2Ptr<hypro::Label>(prhs[3]);

    mxLogical ans = false;
    if (*lab1 < *lab2) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "less input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "less\n" );
    // } else {
    // 	mexPrintf( "not less\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MLabel::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_name(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1) {
        del_label(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        getName(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        setName(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        less(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MLabel - Command not recognized.");
}
