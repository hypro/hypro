#include "MTransition.h"

void MTransition::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - new_empty: Expecting an output.");

    hypro::Transition<double>* temp = new hypro::Transition<double>();
    plhs[0] = convertPtr2Mat<hypro::Transition<double>>(temp);
}

void MTransition::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - copy: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - copy: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - copy: One or more arguments were ignored.");
    
    hypro::Transition<double>* origin = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    plhs[0] = convertPtr2Mat<hypro::Transition<double>>(new hypro::Transition<double>(*origin));
}

void MTransition::new_source_target(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - new_source_target: Expecting an output.");
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - new_source_target: One or more arguments are missing.");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - new_source_target: One or more arguments were ignored.");

    hypro::Location<double>* source = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* target = convertMat2Ptr<hypro::Location<double>>(prhs[3]);

    hypro::Transition<double>* tran = new hypro::Transition<double>(source, target);
    plhs[0] = convertPtr2Mat<hypro::Transition<double>>(new hypro::Transition<double>(*tran));

}

void MTransition::new_full(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - new_full: Expecting an output.");
    if(nrhs < 6)
        mexErrMsgTxt("MTransition - new_full: One or more arguments are missing.");
    if(nrhs > 6)
        mexWarnMsgTxt("MTransition - new_full: One or more arguments were ignored.");

    hypro::Location<double>* source = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* target = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    const hypro::Condition<double>* guard = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
    const hypro::Reset<double>* reset = convertMat2Ptr<hypro::Reset<double>>(prhs[5]);

    hypro::Transition<double>* tran = new hypro::Transition<double>(source, target, *guard, *reset);
    plhs[0] = convertPtr2Mat<hypro::Transition<double>>(new hypro::Transition<double>(*tran));
}

void MTransition::delete_tran(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - delete_tran: Expecting an output.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - delete_tran: One or more arguments were ignored.");
    destroyObject<hypro::Transition<double>>(prhs[2]);
}

void MTransition::getTarget(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - getTarget: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getTarget: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getTarget: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Location<double>* target = tran->getTarget();
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*target));
}

void MTransition::getSource(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - getSource: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getSource: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getSource: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Location<double>* target = tran->getSource();
    plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*target));
}

void MTransition::getGuard(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - getGuard: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getGuard: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getGuard: One or more arguments were ignored.");
    
    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Condition<double> cond = tran->getGuard();
    plhs[0] = convertPtr2Mat<hypro::Condition<double>>(new hypro::Condition<double>(cond));
}

void MTransition::getReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - getReset: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getReset: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getReset: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Reset<double> res = tran->getReset();
    plhs[0] = convertPtr2Mat<hypro::Reset<double>>(new hypro::Reset<double>(res));
}

void MTransition::getAggregation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getAggregation: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getAggregation: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Aggregation agg =  tran->getAggregation();

    if(agg == hypro::Aggregation::none){
        mexPrintf("none\n");
    }else if(agg == hypro::Aggregation::boxAgg){
        mexPrintf("boxAgg\n");
    }else{
        mexPrintf("parallelotopeAgg\n");
    }
}

void MTransition::getTriggerTime(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - getReset: Expecting an output.");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getReset: One or more arguments are missing.");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getReset: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    double time = tran->getTriggerTime();
    plhs[0] = mxCreateDoubleScalar(time);
}

void MTransition::isUrgent(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - isUrgent: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - isUrgent: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - isUrgent: One or more input arguments were ignored.");

    hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const bool isurgent = temp->isUrgent();
    plhs[0] = mxCreateLogicalScalar(isurgent);
}

void MTransition::isTimeTriggered(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - isTimeTriggered: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - isTimeTriggered: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - isTimeTriggered: One or more input arguments were ignored.");

    hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const bool ans = temp->isTimeTriggered();
    plhs[0] = mxCreateLogicalScalar(ans);
}

void MTransition::hasIdentityReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - hasIdentityReset: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - hasIdentityReset: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - hasIdentityReset: One or more input arguments were ignored.");

    hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const bool ans = temp->hasIdentityReset();
    plhs[0] = mxCreateLogicalScalar(ans);
}

void MTransition::getLabels(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - getLabels: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - getLabels: One argument missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - getLabels: One or more input arguments were ignored.");

    hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    std::vector<hypro::Label> labs = temp->getLabels();
    int len = labs.size();
    const mwSize dims[2] = {1, (mwSize) len};
    plhs[0]  = mxCreateCellArray(2,dims);
    objArray2Matlab(labs, plhs[0], len);
}

void MTransition::hash(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - hash: Expecting an output!");
    if(nrhs < 3)
        mexErrMsgTxt("MTransition - hash: One or more input arguments are missing!");
    if(nrhs > 3)
        mexWarnMsgTxt("MTransition - hash: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    std::size_t val = tran->hash();
    plhs[0] = mxCreateDoubleScalar(val);
}

void MTransition::setSource(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setSource: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setSource: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    tran->setSource(loc);
}

void MTransition::setTarget(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setTarget: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setTarget: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    tran->setTarget(loc);
}

void MTransition::setGuard(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setGuard: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setGuard: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
    tran->setGuard(*cond);
}

void MTransition::setReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setReset: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setReset: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Reset<double>* res = convertMat2Ptr<hypro::Reset<double>>(prhs[3]);
    tran->setReset(*res);
}

void MTransition::setAggregation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setAggregation: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setAggregation: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const int agg = (int) mxGetScalar(prhs[3]);

    if(agg == 0){
        tran->setAggregation(hypro::Aggregation::none);
    }else if(agg == 1){
        tran->setAggregation(hypro::Aggregation::boxAgg);
    }else{
        tran->setAggregation(hypro::Aggregation::parallelotopeAgg);
    }
}

void MTransition::setUrgent(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setSource: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setSource: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const double temp = (double) mxGetScalar(prhs[3]);
    bool val = true;
    if(temp == 0)
        val = false;
    tran->setUrgent(val);
}

void MTransition::setTriggerTime(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setTriggerTime: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setTriggerTime: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const double time = (double) mxGetScalar(prhs[3]);
    tran->setTriggerTime(time);
}

void MTransition::setLabels(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - setLabels: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - setLabels: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    const mwSize *dims;
    int num;
    dims = mxGetDimensions(prhs[3]);
    num = dims[1];
    std::vector<hypro::Label> labs = ObjectHandle::objArray2Hypro<hypro::Label>(prhs[3], num);
    tran->setLabels(labs);
}

void MTransition::addLabel(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nrhs < 4)
        mexErrMsgTxt("MTransition - addLabel: One or more input arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - addLabel: One or more input arguments were ignored!");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Label* lab = convertMat2Ptr<hypro::Label>(prhs[3]);
    tran->addLabel(*lab);
}

void MTransition::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition- getDotRepresentation: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MTransition- getDotRepresentation: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - getDotRepresentation: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(plhs[2]);
    std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro(prhs[3]);
    std::string str = tran->getDotRepresentation(vars);
    mxCreateString(str.c_str());
}

void MTransition::isComposedOf(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition- isComposedOf: Expecting an output!");
    if(nrhs < 6)
        mexErrMsgTxt("MTransition- isComposedOf: One or more arguments are missing!");
    if(nrhs > 6)
        mexWarnMsgTxt("MTransition - isComposedOf: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(plhs[2]);
    //TODO

}

void MTransition::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

void MTransition::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //TODO
}

void MTransition::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition- equals: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MTransition- equals: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - equals: One or more arguments were ignored.");

    hypro::Transition<double>* tran1 = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Transition<double>* tran2 = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);

    if(tran1 == tran2)
        plhs[0] = mxCreateLogicalScalar(true);
    else
        plhs[0] = mxCreateLogicalScalar(false);
}

void MTransition::nequals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition- nequals: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MTransition- nequals: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - nequals: One or more arguments were ignored.");

    hypro::Transition<double>* tran1 = convertMat2Ptr<hypro::Transition<double>>(prhs[2]);
    hypro::Transition<double>* tran2 = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);

    if(tran1 != tran2)
        plhs[0] = mxCreateLogicalScalar(true);
    else
        plhs[0] = mxCreateLogicalScalar(false);
}

void MTransition::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    int cmd = mxGetScalar(prhs[1]);

    if (cmd == 2){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 3){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 1){  
        delete_tran(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 4){  
        new_source_target(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 5){  
        new_full(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 6){  
        getTarget(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 7){  
        getSource(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 8){  
        getGuard(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 9){  
        getReset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 10){  
        getAggregation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 11){  
        getTriggerTime(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 12){  
        isUrgent(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 13){  
        isTimeTriggered(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 14){  
        hasIdentityReset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 15){  
        getLabels(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 16){  
        hash(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 17){  
        setSource(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 18){  
        setTarget(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 19){  
        setGuard(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 20){  
        setReset(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 21){  
        setAggregation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 22){  
        setUrgent(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 23){  
        setTriggerTime(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 24){  
        setLabels(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 25){  
        addLabel(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 26){  
        getDotRepresentation(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 27){  
        isComposedOf(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 28){  
        decompose(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 29){  
        equals(nlhs, plhs, nrhs, prhs);
        return;
    }
    if (cmd == 30){  
        nequals(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MTransition - Command not recognized.");
}