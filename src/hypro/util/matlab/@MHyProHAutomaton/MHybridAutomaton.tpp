#include "MHybridAutomaton.h"

    /**
     * @brief
     **/
    void MHybridAutomaton::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
            mexErrMsgTxt("MHybridAutomaton - new_empty: One output expected.");

        plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(new hypro::HybridAutomaton<double>);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
            mexErrMsgTxt("MHybridAutomaton - copy: One output expected.");
        if(nrhs <3)
             mexErrMsgTxt("MHybridAutomaton - copy: One or more arguments are missing.");

        hypro::HybridAutomaton<double>* hybrid = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        plhs[0] = convertPtr2Mat(new hypro::HybridAutomaton<double>(*hybrid));
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::new_loc(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::del_automaton(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocations(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocation_by_hash(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocation_by_name(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getTransitions(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getInitialStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getGlobalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::dimension(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getVariables(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLabels(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setLocations(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setTransitions(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setInitialStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setLocalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setGlobalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setVariables(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::addLocation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

      /**
       * @brief
       **/  
    //void MHybridAutomaton::addLocation_ptr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    //}

    /**
     * @brief
     **/    
    void MHybridAutomaton::addTransition(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

       /**
        * @brief
        **/ 
    // void MHybridAutomaton::addTransition_ptr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    //}

    /**
     * @brief
     **/    
    void MHybridAutomaton::addInitialState(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::addLocalBadState(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::addGlobalBadState(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::removeTransition(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::reduce(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::isComposedOf(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getStatistics(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::unequals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::or_operator(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::plus(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::checkConsistency(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    }


    /**
     * @brief
     **/
    void MHybridAutomaton::process(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        // Get the command string
        char cmd[64];
        if (nrhs < 1 || mxGetString(prhs[1], cmd, sizeof(cmd)))
            mexErrMsgTxt("MHybridAutomaton - First input should be a command string less than 64 characters long.");


        if (!strcmp("new_empty", cmd) && nrhs == 2){  
            new_empty(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("copy", cmd) && nrhs == 2){  
            copy(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("new_loc", cmd) && nrhs == 2){  
            new_loc(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("del_automaton", cmd) && nrhs == 2){  
            del_automaton(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocations", cmd) && nrhs == 2){  
            getLocations(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocation_by_hash", cmd) && nrhs == 2){  
            getLocation_by_hash(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocation_by_name", cmd) && nrhs == 2){  
            getLocation_by_name(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getTransitions", cmd) && nrhs == 2){  
            getTransitions(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getInitialStates", cmd) && nrhs == 2){  
            getInitialStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocalBadStates", cmd) && nrhs == 2){  
            getLocalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getGlobalBadStates", cmd) && nrhs == 2){  
            getGlobalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("dimension", cmd) && nrhs == 2){  
            dimension(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getVariables", cmd) && nrhs == 2){  
            getVariables(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLabels", cmd) && nrhs == 2){  
            getLabels(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setLocations", cmd) && nrhs == 2){  
            setLocations(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setTransitions", cmd) && nrhs == 2){  
            setTransitions(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setInitialStates", cmd) && nrhs == 2){  
            setInitialStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setLocalBadStates", cmd) && nrhs == 2){  
            setLocalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setGlobalBadStates", cmd) && nrhs == 2){  
            setGlobalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setVariables", cmd) && nrhs == 2){  
            setVariables(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addLocation", cmd) && nrhs == 2){  
            addLocation(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addTransition", cmd) && nrhs == 2){  
            addTransition(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addInitialState", cmd) && nrhs == 2){  
            addInitialState(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addLocalBadState", cmd) && nrhs == 2){  
            addLocalBadState(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addGlobalBadState", cmd) && nrhs == 2){  
            addGlobalBadState(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("removeTransition", cmd) && nrhs == 2){  
            removeTransition(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("decompose", cmd) && nrhs == 2){  
            decompose(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("reduce", cmd) && nrhs == 2){  
            reduce(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("isComposedOf", cmd) && nrhs == 2){  
            isComposedOf(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getDotRepresentation", cmd) && nrhs == 2){  
            getDotRepresentation(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getStatistics", cmd) && nrhs == 2){  
            getStatistics(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("equals", cmd) && nrhs == 2){  
            equals(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("unequals", cmd) && nrhs == 2){  
            unequals(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("or_operator", cmd) && nrhs == 2){  
            or_operator(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("plus", cmd) && nrhs == 2){  
            plus(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("outstream", cmd) && nrhs == 2){  
            outstream(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("checkConsistency", cmd) && nrhs == 2){  
            checkConsistency(nlhs, plhs, nrhs, prhs);
            return;
        }
    

    mexErrMsgTxt("Hy- Command not recognized.");
}
