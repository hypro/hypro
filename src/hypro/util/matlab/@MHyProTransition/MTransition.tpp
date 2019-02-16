#include "MTransition.h"

/**
* @brief
**/
void MTransition::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - new_empty: Expecting an output.");

    hypro::Transition<double>* temp = new hypro::Transition<double>();
    plhs[0] = convertPtr2Mat<hypro::Transition<double>>(temp);
}

/**
* @brief
**/
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

/**
* @brief
**/
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

/**
* @brief
**/
void MTransition::new_full(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    if(nlhs != 1)
        mexErrMsgTxt("MTransition - new_full: Expecting an output.");
    if(nrhs < 6)
        mexErrMsgTxt("MTransition - new_full: One or more arguments are missing.");
    if(nrhs > 6)
        mexWarnMsgTxt("MTransition - new_full: One or more arguments were ignored.");

    hypro::Location<double>* source = convertMat2Ptr<hypro::Location<double>>(prhs[2]);
    hypro::Location<double>* target = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
    hypro::Condition<double>* guard = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
    hypro::Reset<double>* reset = convertMat2Ptr<hypro::Condition<double>>(prhs[5]);

    
}

/**
* @brief
**/
void MTransition::del_label(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getTarget(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getSource(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getGuard(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getAggregation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getTriggerTime(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::isUrgent(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::isTimeTriggered(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::hasIdentityReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getLabels(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::hash(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setSource(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setTarget(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setGuard(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setReset(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setAggregation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setUrgent(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setTriggerTime(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::setLabels(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::addLabel(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
     if(nlhs != 1)
        mexErrMsgTxt("MTransition- getDotRepresentation: Expecting an output!");
    if(nrhs < 4)
        mexErrMsgTxt("MTransition- getDotRepresentation: One or more arguments are missing!");
    if(nrhs > 4)
        mexWarnMsgTxt("MTransition - getDotRepresentation: One or more arguments were ignored.");

    hypro::Transition<double>* tran = convertMat2Ptr<hypro::Transition<double>>(plhs[2]);
    
}

/**
* @brief
**/
void MTransition::isComposedOf(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}

/**
* @brief
**/
void MTransition::nequals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

}



/**
 * @brief
 **/
void MTransition::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    // Get the command string
    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
        mexErrMsgTxt("MTransition - First input should be a command string less than 64 characters long.");


    if (!strcmp("new_empty", cmd) && nrhs == 2){  
        new_empty(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("copy", cmd) && nrhs == 2){  
        copy(nlhs, plhs, nrhs, prhs);
        return;
    }

    if (!strcmp("del_label", cmd) && nrhs == 2){  
        del_label(nlhs, plhs, nrhs, prhs);
        return;
    }

    mexErrMsgTxt("MTransition - Command not recognized.");
}