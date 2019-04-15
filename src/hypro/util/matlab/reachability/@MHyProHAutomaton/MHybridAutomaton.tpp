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
    // void MHybridAutomaton::new_loc_init(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nlhs != 1)
    //         mexErrMsgTxt("MHybridAutomaton - new_loc_init: One output expected.");
    //     if(nrhs < 4)
    //         mexErrMsgTxt("MHybridAutomaton - new_loc_init: One or more arguments are missing.");
        
    //     const mwSize *loc_dims;
    //     int loc_num;
    //     loc_dims = mxGetDimensions(prhs[2]);
    //     loc_num = loc_dims[1];
    //     const std::vector<hypro::Location<double>> locs = objArray2Hypro<hypro::Location<double>>(prhs[2], loc_num);
    //     const std::map<const hypro::Location<double>*, hypro::Condition<double>> mapping = ObjectHandle::mLocCondMap2Hypro(prhs[3]);
        
    //     std::vector<std::unique_ptr<hypro::Location<double>>> ptr_locs;
    //     for(const auto &elem : locs){
    //         hypro::Location<double>* l = new hypro::Location<double>(elem);
    //         std::unique_ptr<hypro::Location<double>> loc = std::make_unique<hypro::Location<double>>(*l);
    //         ptr_locs.emplace_back(std::move(loc));
    //     }

    //     // hypro::HybridAutomaton<double>* temp = new hypro::HybridAutomaton<double>(ptr_locs, mapping);
    //     // plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(temp);
    // }

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

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::vector<hypro::Location<double>*> temp = autom->getLocations();
        std::vector<hypro::Location<double>> locations;

        for(const auto &elem : temp){
            locations.emplace_back(*elem);
        }

        mxArray* m_array_out;
        int len = temp.size();
        const mwSize dims[2] = {1,(mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        objArray2Matlab(locations, plhs[0], len);
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

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
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

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
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

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::vector<hypro::Transition<double>*> trans = autom->getTransitions();
        int len = trans.size();
        const mwSize dims[2] = {1, (mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        objArray2Matlab(trans, plhs[0], len);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getInitialStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getInitialStates: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getInitialStates: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getInitialStates: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        const std::map<const hypro::Location<double>*, hypro::Condition<double>> mapping = autom->getInitialStates();

        ObjectHandle::convert2Matlab(mapping, plhs[0], mapping.size());
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLocalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getLocalBadStates: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getLocalBadStates: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getLocalBadStates: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        const std::map<const hypro::Location<double>*, hypro::Condition<double>> mapping = autom->getLocalBadStates();

        ObjectHandle::convert2Matlab(mapping, plhs[0], mapping.size());
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

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
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

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::vector<std::string> vars = autom->getVariables();
        int len = vars.size();
        const mwSize dims[2] = {1, (mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        ObjectHandle::convert2Matlab(vars, plhs[0] , dims);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getLabels(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getLabels: One output expected.");   
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getLabels: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getLabels: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::set<hypro::Label> labels = autom->getLabels();
        std::vector<hypro::Label> labels_vec;

        //Convert set to vector as it does not matter to Matlab
        for(const auto &elem : labels){
            labels_vec.emplace_back(elem);
        }

        int len = labels_vec.size();
        const mwSize dims[2] = {1, (mwSize) len};
        plhs[0]  = mxCreateCellArray(2,dims);
        objArray2Matlab(labels_vec, plhs[0], len);

    }

    /**
     * @brief
     * @param A hybrid automaton and a vector of locations.
     **/    
    void MHybridAutomaton::setLocations(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - setLocations: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - setLocations: One or more arguments were ignored.");

        const mwSize* dims;
        int dimy;
        dims = mxGetDimensions(plhs[3]);
        dimy = dims[0];
        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::vector<hypro::Location<double>> locs = objArray2Hypro<hypro::Location<double>>(prhs[3], dimy);
        
        std::vector<std::unique_ptr<hypro::Location<double>>> locs_ptr;
        for(const auto &elem : locs){
            hypro::Location<double>* l = new hypro::Location<double>(elem);
            std::unique_ptr<hypro::Location<double>> loc = std::make_unique<hypro::Location<double>>(*l);
            locs_ptr.emplace_back(std::move(loc));
        }
        autom->setLocations(std::move(locs_ptr));
    }

    // /**
    //  * @brief
    //  **/    
    // void MHybridAutomaton::setTransitions(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){

    // }

    /**
     * @brief
     **/    
    // void MHybridAutomaton::setInitialStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nrhs < 5)
    //         mexErrMsgTxt("MHybridAutomaton - setInitialStates: One or more arguments are missing.");
    //     if(nrhs > 5)
    //         mexWarnMsgTxt("MHybridAutomaton - setInitialStates: One or more arguments were ignored.");

    //     const mwSize *dims;
    //     int len;
    //     dims = mxGetDimensions(prhs[3]);
    //     len = (int) dims[0];


    //     hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    //     std::vector<hypro::Location<double>> locations = ObjectHandle::objArray2Hypro<hypro::Location<double>>(prhs[3], len);
    //     std::vector<hypro::Condition<double>> conditions = ObjectHandle::objArray2Hypro<hypro::Condition<double>>(prhs[4], len);
    //     std::map<const hypro::Location<double>*, hypro::Condition<double>> mapping;


    //     // TODO
        
    //     // autom->setInitialStates(mapping);
    // }

    /**
     * @brief
     **/    
    // void MHybridAutomaton::setLocalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nrhs < 4)
    //         mexErrMsgTxt("MHybridAutomaton - setLocalBadStates: One or more arguments are missing.");
    //     if(nrhs > 4)
    //         mexWarnMsgTxt("MHybridAutomaton - setLocalBadStates: One or more arguments were ignored.");

    //     hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    //     const std::map<const hypro::Location<double>*, hypro::Condition<double>> mapping = ObjectHandle::mLocCondMap2Hypro(prhs[3]);
    //     autom->setLocalBadStates(mapping);
    // }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setGlobalBadStates(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - setGlobalBadStates: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - setGlobalBadStates: One or more arguments were ignored.");

        const mwSize* dims;
        int dimy;
        dims = mxGetDimensions(plhs[3]);
        dimy = dims[0];
        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::vector<hypro::Condition<double>> conds = objArray2Hypro<hypro::Condition<double>>(prhs[3], dimy);
        autom->setGlobalBadStates(conds);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::setVariables(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - setVariables: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - setVariables: One or more arguments were ignored.");

        const mwSize* dims;
        int dimy;
        dims = mxGetDimensions(plhs[3]);
        dimy = dims[0];
        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::vector<std::string> vars = ObjectHandle::mStringVector2Hypro(prhs[3], dimy);
        autom->setVariables(vars);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::addLocation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - addLocation: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - addLocation: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
        autom->addLocation(*loc);
    }

      /**
       * @brief
       **/  
    //void MHybridAutomaton::addLocation_ptr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        //TODO???
    //}

    /**
     * @brief
     **/    
    // void MHybridAutomaton::addTransition(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nrhs < 4)
    //         mexErrMsgTxt("MHybridAutomaton - addTransition: One or more arguments are missing.");
    //     if(nrhs > 4)
    //         mexWarnMsgTxt("MHybridAutomaton - addTransition: One or more arguments were ignored.");

    //     hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    //     hypro::Transition<double>* temp = convertMat2Ptr<hypro::Transition<double>>(prhs[3]);
    //     std::unique_ptr<hypro::Transition<double>> tran = std::make_unique<hypro::Transition<double>>(*temp);
    //     // autom->addTransition(std::move(tran));
    // }

       /**
        * @brief
        **/ 
    // void MHybridAutomaton::addTransition_ptr(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        //TODO?
    //}

    /**
     * @brief
     **/    
    void MHybridAutomaton::addInitialState(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 5)
            mexErrMsgTxt("MHybridAutomaton - addInitialState: One or more arguments are missing.");
        if(nrhs > 5)
            mexWarnMsgTxt("MHybridAutomaton - addInitialState: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
        hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
        autom->addInitialState(loc, *cond);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::addLocalBadState(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 5)
            mexErrMsgTxt("MHybridAutomaton - addLocalBadState: One or more arguments are missing.");
        if(nrhs > 5)
            mexWarnMsgTxt("MHybridAutomaton - addLocalBadState: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::Location<double>* loc = convertMat2Ptr<hypro::Location<double>>(prhs[3]);
        hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[4]);
        autom->addLocalBadState(&(*loc), *cond);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::addGlobalBadState(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - addGlobalBadState: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - addGlobalBadState: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::Condition<double>* cond = convertMat2Ptr<hypro::Condition<double>>(prhs[3]);
        autom->addGlobalBadState(*cond);
    }


    /**
     * @brief
     **/    
    void MHybridAutomaton::reduce(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - addGlobalBadState: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - addGlobalBadState: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        autom->reduce();
    }

    /**
     * @brief THIS IS CORRECT BUT CANNOT BE USED NOW
     **/    
    // void MHybridAutomaton::isComposedOf(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nlhs != 1)
    //          mexErrMsgTxt("MHybridAutomaton - isComposedOf: One output expected.");
    //     if(nrhs < 4)
    //         mexErrMsgTxt("MHybridAutomaton - isComposedOf: One or more arguments are missing.");
    //     if(nrhs > 4)
    //         mexWarnMsgTxt("MHybridAutomaton - isComposedOf: One or more arguments were ignored.");

    //     hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    //     hypro::HybridAutomaton<double>* rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);
    //     autom->isComposedOf(*rhs);
    // }

    /**
     * @brief THIS IS CORRECT BUT CANNOT BE USED NOW
     **/    
    // void MHybridAutomaton::getDotRepresentation(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nlhs != 1)
    //          mexErrMsgTxt("MHybridAutomaton - getDotRepresentation: One output expected.");
    //     if(nrhs < 3)
    //         mexErrMsgTxt("MHybridAutomaton - getDotRepresentation: One or more arguments are missing.");
    //     if(nrhs > 3)
    //         mexWarnMsgTxt("MHybridAutomaton - getDotRepresentation: One or more arguments were ignored.");

    //     hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    //     std::string rep = autom->getDotRepresentation();
    //     plhs[0] = mxCreateString(rep.c_str());
    // }

    /**
     * @brief
     **/    
    void MHybridAutomaton::getStatistics(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - getStatistics: One output expected.");
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - getStatistics: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - getStatistics: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        std::string rep = autom->getStatistics();
        plhs[0] = mxCreateString(rep.c_str());
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::equals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - equals: One output expected.");
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - equals: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - equals: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::HybridAutomaton<double>* rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);
        mxLogical ans = false;
        if(*autom == *rhs)
            ans = true;
        plhs[0] = mxCreateLogicalScalar(ans);
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::unequals(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - unequals: One output expected.");
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - unequals: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - unequals: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::HybridAutomaton<double>* rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);
        mxLogical ans = false;
        if(*autom != *rhs)
            ans = true;
        plhs[0] = mxCreateLogicalScalar(ans);
    }

    /**
     * @brief TODO
     **/    
    // void MHybridAutomaton::or_operator(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
    //     if(nlhs != 1)
    //          mexErrMsgTxt("MHybridAutomaton - or_operator: One output expected.");
    //     if(nrhs < 4)
    //         mexErrMsgTxt("MHybridAutomaton - or_operator: One or more arguments are missing.");
    //     if(nrhs > 4)
    //         mexWarnMsgTxt("MHybridAutomaton - or_operator: One or more arguments were ignored.");

    //     hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
    //     hypro::HybridAutomaton<double>* rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);

    //     hypro::HybridAutomaton<double> temp = *autom || *rhs;
    //     plhs[0] = convertPtr2Mat<hypro::HybridAutomaton<double>>(new hypro::HybridAutomaton<double>(temp));
    // }

    /**
     * @brief
     **/    
    void MHybridAutomaton::plus(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - plus: One output expected.");
        if(nrhs < 4)
            mexErrMsgTxt("MHybridAutomaton - plus: One or more arguments are missing.");
        if(nrhs > 4)
            mexWarnMsgTxt("MHybridAutomaton - plus: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        hypro::HybridAutomaton<double>* rhs = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[3]);

        hypro::HybridAutomatonComp<double> temp = *autom + *rhs;
        plhs[0] = convertPtr2Mat<hypro::HybridAutomatonComp<double>>(new hypro::HybridAutomatonComp<double>(temp));
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::outstream(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        //TODO?
    }

    /**
     * @brief
     **/    
    void MHybridAutomaton::checkConsistency(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[]){
        if(nlhs != 1)
             mexErrMsgTxt("MHybridAutomaton - unequals: One output expected.");
        if(nrhs < 3)
            mexErrMsgTxt("MHybridAutomaton - unequals: One or more arguments are missing.");
        if(nrhs > 3)
            mexWarnMsgTxt("MHybridAutomaton - unequals: One or more arguments were ignored.");

        hypro::HybridAutomaton<double>* autom = convertMat2Ptr<hypro::HybridAutomaton<double>>(prhs[2]);
        bool cons = autom->checkConsistency();
        mxLogical ans = false;
        if(cons)
            ans = true;
        plhs[0] = mxCreateLogicalScalar(ans);
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
        // if (!strcmp("new_loc_init", cmd)){  
        //     new_loc_init(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
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
        // if (!strcmp("setInitialStates", cmd)){  
        //     setInitialStates(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
        // if (!strcmp("setLocalBadStates", cmd)){  
        //     setLocalBadStates(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
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
        // if (!strcmp("addTransition", cmd)){  
        //     addTransition(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
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
        // if (!strcmp("removeTransition", cmd)){  
        //     removeTransition(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
        if (!strcmp("decompose", cmd)){  
            decompose(nlhs, plhs, nrhs, prhs);
            return;
        }
        if (!strcmp("reduce", cmd)){  
            reduce(nlhs, plhs, nrhs, prhs);
            return;
        }
        // if (!strcmp("isComposedOf", cmd)){  
        //     isComposedOf(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
        // if (!strcmp("getDotRepresentation", cmd)){  
        //     getDotRepresentation(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
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
        // if (!strcmp("or_operator", cmd)){  
        //     or_operator(nlhs, plhs, nrhs, prhs);
        //     return;
        // }
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
