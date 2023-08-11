/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "MHybridAutomaton.h"

void MHybridAutomaton::new_empty(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - new_empty: Expecting an output.");

    hypro::HybridAutomaton<double> *temp = new hypro::HybridAutomaton<double>();
    plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(temp);
}

void MHybridAutomaton::new_loc_init(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - new_loc_init: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - new_loc_init: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - new_loc_init: One or more arguments were ignored.");

    std::vector<std::unique_ptr<hypro::Location<double>>> locs = ObjectHandle::mLocsVector2Hypro(prhs[2]);
    const std::map<const hypro::Location<double> *, hypro::Condition<double>> mapping =
            ObjectHandle::mLocCondMap2Hypro(prhs[3]);
    mexErrMsgTxt("NOT IMPLEMENTED");
    // hypro::HybridAutomaton<double>* temp = new hypro::HybridAutomaton<double>(locs, mapping);
    // plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(temp);
}

void MHybridAutomaton::copy(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - copy: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - copy: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - copy: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *origin = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(new hypro::HybridAutomaton<double>(*origin));
}

void MHybridAutomaton::delete_autom(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - delete_autom: Expecting an output.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - delete_autom: One or more arguments were ignored.");
    destroyObject<hypro::HybridAutomaton<double>>(prhs[2]);
}

void MHybridAutomaton::dimension(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - dimension: Expecting an output.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - dimension: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - dimension: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *obj = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::size_t dim = obj->dimension();
    plhs[0] = mxCreateDoubleScalar(dim);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "dimension output:\n" );
    // mexPrintf( "dimension: %d\n", (double) dim );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::decompose(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // if(nrhs < 4)
    //     mexErrMsgTxt("MHybridAutomaton - decompose: One or more arguments are missing.");
    // if(nrhs > 4)
    //     mexWarnMsgTxt("MHybridAutomaton - decompose: One or more arguments were ignored.");

    // mxArray* m_in_vec;
    // double* in_vec;
    // const mwSize* dims;
    // int rows, cols;

    // m_in_vec = mxDuplicateArray(prhs[3]);
    // in_vec = mxGetPr(m_in_vec);
    // dims = mxGetDimensions(prhs[3]);
    // cols = dims[1];
    // rows = dims[0];
    // std::vector<std::vector<size_t>> decomposition = ObjectHandle::mVectorOfVectors2Hypro(m_in_vec,rows, cols);
    // hypro::HybridAutomaton<double>* obj = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    // obj->decompose();
    // obj->decompose(decomposition);
}

void MHybridAutomaton::getLocations(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getLocations: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getLocations: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getLocations: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<hypro::Location<double> *> temp = autom->getLocations();
    std::vector<hypro::Location<double>> locations;

    for (const auto &elem: temp) {
        locations.emplace_back(*elem);
    }

    int len = temp.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(locations, plhs[0], len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLocations output:\n" );
    // for(int i = 0; i < len; i++){
    // 	mexPrintf("loc %d: %s addr: %d\n", i, temp[i]->getName().c_str(), &temp[i]);
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getLocation_by_hash(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getLocation_by_hash: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - getLocation_by_hash: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - getLocation_by_hash: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::size_t hash = (std::size_t) mxGetScalar(prhs[3]);
    hypro::Location<double> *loc = autom->getLocation(hash);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*loc));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLocation_by_hash input:\n" );
    // mexPrintf("hash: %d\n", (double) hash);
    // mexPrintf("output\n");
    // mexPrintf("loc: %s\n", loc->getName());
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getLocation_by_name(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getLocation_by_name: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - getLocation_by_name: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - getLocation_by_name: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    char name[64];
    mxGetString(prhs[3], name, sizeof(name));
    hypro::Location<double> *loc = autom->getLocation(name);
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(loc);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLocation_by_name input:\n" );
    // mexPrintf("name: %d\n", name);
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getTransitions(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getTransitions: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getTransitions: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getTransitions: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<hypro::Transition<double> *> trans = autom->getTransitions();
    int len = trans.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(trans, plhs[0], len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getTransitions output:\n" );
    // for(int i = 0; i < trans.size(); i++){
    // 	hypro::Transition<double>* curr = trans[i];
    // 	hypro::Location<double>* target = curr->getTarget();
    // 	hypro::Location<double>* source = curr->getSource();
    // 	std::string tName = target->getName();
    // 	std::string sName = source->getName();
    // 	mexPrintf( "transition %s -> %s\n", tName.c_str(), sName.c_str() );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getInitialStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getInitialStates: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getInitialStates: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getInitialStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    const std::map<const hypro::Location<double> *, hypro::Condition<double>> mapping = autom->getInitialStates();
    int len = mapping.size();
    mwSize dims[2] = {1, (mwSize) len};
    const char *fieldnames[] = {"loc", "cond"};
    plhs[0] = mxCreateStructArray(2, dims, 2, fieldnames);
    ObjectHandle::convert2Matlab(mapping, plhs[0]);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getInitialStates input:\n" );
    // mexPrintf( "mapping size: %d\n", len );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getLocalBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getLocalBadStates: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getLocalBadStates: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getLocalBadStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    const std::map<const hypro::Location<double> *, hypro::Condition<double>> mapping = autom->getLocalBadStates();
    int len = mapping.size();
    mwSize dims[2] = {1, (mwSize) len};
    const char *fieldnames[] = {"loc", "cond"};
    plhs[0] = mxCreateStructArray(2, dims, 2, fieldnames);
    ObjectHandle::convert2Matlab(mapping, plhs[0]);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getLocalBadStates input:\n" );
    // mexPrintf( "mapping size: %d\n", len );

    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getGlobalBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getGlobalBadStates: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getGlobalBadStates: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getGlobalBadStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<hypro::Condition<double>> conds = autom->getGlobalBadStates();
    int len = conds.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(conds, plhs[0], len);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getGlobalBadStates input:\n" );
    // mexPrintf( "mapping size: %d\n", len );
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getVariables(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getVariables: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getVariables: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getVariables: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<std::string> vars = autom->getVariables();
    int len = vars.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    ObjectHandle::convert2Matlab(vars, plhs[0], dims);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "getVariables output:\n" );
    // for(int i = 0; i < len; i++){
    // 	mexPrintf("var %d: %s\n", i, vars[i].c_str());
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::getLabels(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getLabels: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getLabels: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getLabels: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::set<hypro::Label> labels = autom->getLabels();
    std::vector<hypro::Label> labels_vec;

    // Convert set to vector as it does not matter to Matlab
    for (const auto &elem: labels) {
        labels_vec.emplace_back(elem);
    }

    int len = labels_vec.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0] = mxCreateCellArray(2, dims);
    objArray2Matlab(labels_vec, plhs[0], len);
}

void MHybridAutomaton::setLocations(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - setLocations: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - setLocations: One or more arguments were ignored.");

    const mwSize *dims;
    int dimy;
    dims = mxGetDimensions(plhs[3]);
    dimy = dims[0];
    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<hypro::Location<double>> locs = ObjectHandle::objArray2Hypro<hypro::Location<double>>(prhs[3], dimy);

    std::vector<std::unique_ptr<hypro::Location<double>>> locs_ptr;
    for (const auto &elem: locs) {
        hypro::Location<double> *l = new hypro::Location<double>(elem);
        std::unique_ptr<hypro::Location<double>> loc = std::make_unique<hypro::Location<double>>(*l);
        locs_ptr.emplace_back(std::move(loc));
    }
    autom->setLocations(std::move(locs_ptr));

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setLocations input:\n" );
    // for(int i = 0; i < locs.size(); i++){
    // 	mexPrintf("loc %d: %s\n", i, locs[i].getName().c_str());
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::setInitialStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - setInitialStates: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - setInitialStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    const std::map<const hypro::Location<double> *, hypro::Condition<double>> mapping =
            ObjectHandle::mLocCondMap2Hypro(prhs[3]);
    autom->setInitialStates(mapping);
}

void MHybridAutomaton::setLocalBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - setLocalBadStates: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - setLocalBadStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    const std::map<const hypro::Location<double> *, hypro::Condition<double>> mapping =
            ObjectHandle::mLocCondMap2Hypro(prhs[3]);
    autom->setLocalBadStates(mapping);
}

void MHybridAutomaton::setGlobalBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - setGlobalBadStates: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - setGlobalBadStates: One or more arguments were ignored.");

    const mwSize *dims;
    int dimy;
    dims = mxGetDimensions(plhs[3]);
    dimy = dims[0];
    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<hypro::Condition<double>> conds =
            ObjectHandle::objArray2Hypro<hypro::Condition<double>>(prhs[3], dimy);
    autom->setGlobalBadStates(conds);
}

void MHybridAutomaton::setVariables(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - setVariables: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - setVariables: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro(prhs[3]);
    autom->setVariables(vars);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "setVariables output:\n" );
    // for(int i = 0; i < vars.size(); i++){
    // 	mexPrintf("var %d: %s\n", i, vars[i].c_str());
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::addLocation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - addLocation: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - addLocation: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    hypro::Location<double> *newLocPtr = autom->addLocation(*loc);

    plhs[0] = convertSmartPtr2Mat<hypro::Location<double>>(newLocPtr);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "addLocation input:\n" );
    // mexPrintf("location %s\n", loc->getName().c_str());
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::addTransition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - addTransition: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - addTransition: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::Transition<double> *temp = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
    mexErrMsgTxt("NOT IMPLEMENTED");
    // autom->addTransition(std::move(std::make_unique<hypro::Transition<double>>(*temp)));
}

void MHybridAutomaton::addInitialState(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MHybridAutomaton - addInitialState: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MHybridAutomaton - addInitialState: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
    autom->addInitialState(loc, *cond);
}

void MHybridAutomaton::addLocalBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 5) mexErrMsgTxt("MHybridAutomaton - addLocalBadStates: One or more arguments are missing.");
    if (nrhs > 5) mexWarnMsgTxt("MHybridAutomaton - addLocalBadStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::Location<double> *loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
    autom->addLocalBadStates(&(*loc), *cond);
}

void MHybridAutomaton::addGlobalBadStates(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - addGlobalBadStates: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - addGlobalBadStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::Condition<double> *cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    autom->addGlobalBadStates(*cond);
}

void MHybridAutomaton::reduce(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - addGlobalBadStates: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - addGlobalBadStates: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    autom->reduce();
}

void MHybridAutomaton::isComposedOf(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - isComposedOf: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - isComposedOf: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - isComposedOf: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::HybridAutomaton<double> *rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);
    // autom->isComposedOf( *rhs );
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MHybridAutomaton::getDotRepresentation(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getDotRepresentation: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getDotRepresentation: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getDotRepresentation: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    // std::string rep = autom->getDotRepresentation();
    // plhs[0] = mxCreateString( rep.c_str() );

    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MHybridAutomaton::getStatistics(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - getStatistics: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - getStatistics: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - getStatistics: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    std::string rep = autom->getStatistics();
    plhs[0] = mxCreateString(rep.c_str());

    //+++++++++++++TESTING++++++++++++++++++++
    mexPrintf("getStatistics output:\n");
    mexPrintf("statistic: %s\n", rep.c_str());
    //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::equals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - equals: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - equals: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - equals: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::HybridAutomaton<double> *rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);
    mxLogical ans = false;
    if (*autom == *rhs) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "equals input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "yes\n" );
    // } else {
    // 	mexPrintf( "no\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::unequals(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - unequals: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - unequals: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - unequals: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::HybridAutomaton<double> *rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);
    mxLogical ans = false;
    if (*autom != *rhs) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "unequals input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "yes\n" );
    // } else {
    // 	mexPrintf( "no\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::plus(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - plus: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - plus: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - plus: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::HybridAutomaton<double> *rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);

    // hypro::HybridAutomatonComp<double> temp = *autom + *rhs;
    // plhs[0] = convertPtr2Mat<hypro::HybridAutomatonComp<double>>(new hypro::HybridAutomaton<double>( temp ) );
    mexErrMsgTxt("NOT IMPLEMENTED");
}

void MHybridAutomaton::outstream(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // TODO?
}

void MHybridAutomaton::checkConsistency(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - checkConsistency: One output expected.");
    if (nrhs < 3) mexErrMsgTxt("MHybridAutomaton - checkConsistency: One or more arguments are missing.");
    if (nrhs > 3) mexWarnMsgTxt("MHybridAutomaton - checkConsistency: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    bool cons = autom->checkConsistency();
    mxLogical ans = false;
    if (cons) ans = true;
    plhs[0] = mxCreateLogicalScalar(ans);

    // //+++++++++++++TESTING++++++++++++++++++++
    // mexPrintf( "checkConsistency input:\n" );
    // if ( ans ) {
    // 	mexPrintf( "yes\n" );
    // } else {
    // 	mexPrintf( "no\n" );
    // }
    // //+++++++++++++TESTING++++++++++++++++++++
}

void MHybridAutomaton::parallelComposition(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (nlhs != 1) mexErrMsgTxt("MHybridAutomaton - parallelComposition: One output expected.");
    if (nrhs < 4) mexErrMsgTxt("MHybridAutomaton - parallelComposition: One or more arguments are missing.");
    if (nrhs > 4) mexWarnMsgTxt("MHybridAutomaton - parallelComposition: One or more arguments were ignored.");

    hypro::HybridAutomaton<double> *autom_lhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    hypro::HybridAutomaton<double> *autom_rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);

    // hypro::HybridAutomaton<double> comp_autom = *autom_lhs || *autom_rhs;

    // plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>( new hypro::HybridAutomaton<double>( comp_autom ) );
}

void MHybridAutomaton::process(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2) {
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3) {
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4) {
        new_loc_init(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1) {
        delete_autom(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7) {
        getLocations(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8) {
        getLocation_by_hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9) {
        getLocation_by_name(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10) {
        getTransitions(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11) {
        getInitialStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12) {
        getLocalBadStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13) {
        getGlobalBadStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5) {
        dimension(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14) {
        getVariables(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15) {
        getLabels(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16) {
        setLocations(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17) {
        setInitialStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18) {
        setLocalBadStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19) {
        setGlobalBadStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20) {
        setVariables(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21) {
        addLocation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 32) {
        addTransition(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 22) {
        addInitialState(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 23) {
        addLocalBadStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 24) {
        addGlobalBadStates(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6) {
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 25) {
        reduce(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 26) {
        isComposedOf(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 27) {
        getDotRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 28) {
        getStatistics(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 29) {
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 30) {
        unequals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 31) {
        plus(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 32) {
        parallelComposition(nlhs, plhs, nrhs, prhs);
        return;
    }
    mexErrMsgTxt("MHybridAutomaton - Command not recognized.");
}
