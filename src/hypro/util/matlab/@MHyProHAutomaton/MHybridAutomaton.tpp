#include "MHybridAutomaton.h"

    /**
     * @brief
     **/
    void MHybridAutomaton::new_empty(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
            mexErrMsgTxt("MHybridAutomaton - new_empty: Expecting an output.");

        hypro::HybridAutomaton<double>* temp = new hypro::HybridAutomaton<double>();
        plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(temp);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::new_loc_init(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
            mexErrMsgTxt("MHybridAutomaton - new_sets: One output expected.");
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - new_sets: One or more arguments are missing.");
        
        const mwSize *loc_dims;
        int loc_num;
        loc_dims = mxGetDimensions(prhs[2]);
        loc_num = loc_dims[0];
        std::vector<hypro::Location<double>> locs = objArray2Hypro<hypro::Location<double>>(prhs[2], loc_num);
        //TODO
    }

    /**
     * @brief
     **/
    void MHybridAutomaton::copy(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
            mexErrMsgTxt("MHybridAutomaton - copy: Expecting an output.");
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - copy: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - copy: One or more arguments were ignored.");

        
        hypro::HybridAutomaton<double> *origin = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(new hypro::HybridAutomaton<double>(*origin));
    }

    /**
     * @brief
     **/
    void MHybridAutomaton::delete_autom(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - delete_autom: Expecting an output.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - delete_autom: One or more arguments were ignored.");
        destroyObject<hypro::HybridAutomaton<double>>(prhs[2]);
    }

    /**
     * @brief
     **/
    void MHybridAutomaton::dimension(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
            mexErrMsgTxt("MHybridAutomaton - dimension: Expecting an output.");
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - dimension: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - dimension: One or more arguments were ignored.");
        
        hypro::HybridAutomaton<double>* obj = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::size_t dim = obj->dimension();
        plhs[0] = mxCreateDoubleScalar(dim);
    }

    /**
     * @brief
     **/
    void MHybridAutomaton::decompose(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        // if(nrhs < 4)
        //     mexErrMsgTxt("MHybridAutomaton - decompose: One or more arguments are missing.");
        // if(nrhs > 4)
        //     mexWarnMsgTxt("MHybridAutomaton - decompose: One or more arguments were ignored.");
        
        // mxArray* m_in_vec;
        // double* in_vec;
        // const mwSize* dims;
        // int dimx, dimy;
        
        // m_in_vec = mxDuplicateArray(prhs[3]);
        // in_vec = mxGetPr(m_in_vec);
        // dims = mxGetDimensions(prhs[3]);
        // dimy = dims[0];
        // dimx = dims[1];
        // std::vector<std::vector<size_t>> decomposition = ObjectHandle::mVectorOfVectors2Hypro(in_vec,dimx, dimy);
        // hypro::HybridAutomaton<double>* obj = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        //obj->decompose();
        // obj->decompose(decomposition);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocations(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getLocations: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getLocations: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getLocations: One or more arguments were ignored.");

        /*hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(plhs[2]);
        std::vector<hypro::Location<double>> locs = autom->getLocations();
        int len = locs.size();
        const mwSize dims[2] = {1, (mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        objArray2Matlab(locs, plhs[0], len);*/
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocation_by_hash(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getLocation_by_hash: One output expected.");   
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - getLocation_by_hash: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - getLocation_by_hash: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(plhs[2]);
        std::size_t hash = (std::size_t) mxGetScalar(prhs[3]);
        hypro::Location<double>* loc = autom->getLocation(hash);
        plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*loc));
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocation_by_name(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getLocation_by_name: One output expected.");   
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - getLocation_by_name: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - getLocation_by_name: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(plhs[2]);
        char name[64];
        mxGetString(prhs[3], name, sizeof(name));
        hypro::Location<double>* loc = autom->getLocation(name);
        plhs[0] = convertPtr2Mat<hypro::Location<double>>(new hypro::Location<double>(*loc));
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getTransitions(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getTransitions: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getTransitions: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getTransitions: One or more arguments were ignored.");

        // hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(plhs[2]);
        // std::vector<hypro::Transition<double>>* trans = autom->getTransitions();
        // int len = trans.size();
        // const mwSize dims[2] = {1, (mwSize) len};
        // plhs[0]  = mxCreateCellArray(2,dims);
        // objArray2Matlab(*trans, plhs[0], len);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getInitialStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        //TODO
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        //TODO
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getGlobalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getGlobalBadStates: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getGlobalBadStates: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getGlobalBadStates: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(plhs[2]);
        std::vector<hypro::Condition<double>> conds = autom->getGlobalBadStates();
        int len = conds.size();
        const mwSize dims[2] = {1, (mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        objArray2Matlab(conds, plhs[0], len);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getVariables(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getVariables: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getVariables: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getVariables: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(plhs[2]);
        std::vector<std::string> vars = autom->getVariables();
        int len = vars.size();
        const mwSize dims[2] = {1, (mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        objArray2Matlab(vars, plhs[0], len);
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

    // /**
    //  * @brief
    //  **/    
    // void MHybridAutomaton::setTransitions(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    // }

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


        if (!strcmp("new_empty", cmd)){  
            new_empty(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("copy", cmd)){  
            copy(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("new_loc", cmd)){  
            new_loc_init(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("delete", cmd)){  
            delete_autom(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocations", cmd)){  
            getLocations(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocation_by_hash", cmd)){  
            getLocation_by_hash(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocation_by_name", cmd)){  
            getLocation_by_name(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getTransitions", cmd)){  
            getTransitions(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getInitialStates", cmd)){  
            getInitialStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLocalBadStates", cmd)){  
            getLocalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getGlobalBadStates", cmd)){  
            getGlobalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("dimension", cmd)){  
            dimension(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getVariables", cmd)){  
            getVariables(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getLabels", cmd)){  
            getLabels(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setLocations", cmd)){  
            setLocations(nlhs, plhs, nrhs, prhs);
            return;
        }

        // if (!strcmp("setTransitions", cmd)){  
        //     setTransitions(nlhs, plhs, nrhs, prhs);
        //     return;
        // }

        if (!strcmp("setInitialStates", cmd)){  
            setInitialStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setLocalBadStates", cmd)){  
            setLocalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setGlobalBadStates", cmd)){  
            setGlobalBadStates(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("setVariables", cmd)){  
            setVariables(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addLocation", cmd)){  
            addLocation(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addTransition", cmd)){  
            addTransition(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addInitialState", cmd)){  
            addInitialState(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addLocalBadState", cmd)){  
            addLocalBadState(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("addGlobalBadState", cmd)){  
            addGlobalBadState(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("removeTransition", cmd)){  
            removeTransition(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("decompose", cmd)){  
            decompose(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("reduce", cmd)){  
            reduce(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("isComposedOf", cmd)){  
            isComposedOf(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getDotRepresentation", cmd)){  
            getDotRepresentation(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("getStatistics", cmd)){  
            getStatistics(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("equals", cmd)){  
            equals(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("unequals", cmd)){  
            unequals(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("or_operator", cmd)){  
            or_operator(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("plus", cmd)){  
            plus(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("outstream", cmd)){  
            outstream(nlhs, plhs, nrhs, prhs);
            return;
        }

        if (!strcmp("checkConsistency", cmd)){  
            checkConsistency(nlhs, plhs, nrhs, prhs);
            return;
        }
    

    mexErrMsgTxt("MHybridAutomaton - Command not recognized.");
}
