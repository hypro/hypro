#include "Transformation.h"

namespace hypro {

template <typename Number>
Transformation<Number>::Transformation (const HybridAutomaton<Number>& _hybrid) {
    const size_t CONDITION_LIMIT = 100;
    Matrix<Number> matrix_in_parser;
    size_t m_size, i;
    Matrix<Number> V_EVD;
    DiagonalMatrix<Number> D_EVD;
    Matrix<Number> Vinv_EVD;
    Matrix<Number> V;                             //backtransformation
    Matrix<Number> Vinv;                          //transformation
    Matrix<Number> A_in;
    Vector<Number> b_tr;                          //later transformed b
    Matrix<Number> A_nonlinear;
    Vector<Number> b_nonlinear;
    LocationManager<Number>& locationManager = LocationManager<Number>::getInstance();
    locationSet locations;
    Location<Number>* PtrtoNewLoc;
    mTransformedHA = HybridAutomaton<Number>();
//LOCATIONS
    for (Location<Number>* LocPtr : _hybrid.getLocations() ) {
        matrix_in_parser = LocPtr->getFlow();   //copy for calculation; TODO (getsize() missing) many flows
        m_size = matrix_in_parser.cols(); //rows
        assert(m_size>=1);  //exit if location size <1-> underflow error
        m_size -= 1;
        STallValues<Number> mSTallvalues;
        mSTallvalues.mSTindependentFunct.expFunctionType.reserve(m_size);
        for (i=0; i<m_size; ++i) {
            mSTallvalues.mSTindependentFunct.expFunctionType[i] = EXP_FUNCT_TYPE::INITIALIZED;
        }
//        std::generate(  mSTallvalues.mSTindependentFunct.expFunctionType.begin(), 
//                        mSTallvalues.mSTindependentFunct.expFunctionType.end() 
//                                                    EXP_FUNCT_TYPE::INITIALIZED);
        declare_structures(mSTallvalues, m_size);
        b_tr        = Vector<Number>(m_size);
        A_in        = Matrix<Number>(m_size,m_size);
        V           = Matrix<Number>(m_size,m_size);                //NOTE this is as copy already in mSTallvalues
        Vinv        = Matrix<Number>(m_size,m_size);
        b_tr        = matrix_in_parser.topRightCorner(m_size,1);
        A_in        = matrix_in_parser.topLeftCorner(m_size,m_size);
        std::cout<<"A: "<<std::endl<<A_in;
        size_t numberLinear = countLinearAndRemember(A_in, m_size, mSTallvalues);
        //std::cout << "Number of Linear Terms: " << numberLinear <<"\n";
    //NOFLOW 
        if(numberLinear  == m_size) {
            std::cout << "no FLOW\n";
            Vinv.setIdentity(m_size,m_size);
            V.setIdentity(m_size,m_size);
            mSTallvalues.mSTindependentFunct.D.diagonal().setZero(m_size);
        } else {
    //SOME FLOW
        //if there exists linear terms, adapt size to do EVD accordingly
           if(numberLinear > 0) {
            //size adjusting
                std::cout << "flow with linear terms\n";
                size_t nonLinearsize = m_size - numberLinear;
                //adapt size and insert nonlinear
                A_nonlinear = Matrix<Number>(nonLinearsize,nonLinearsize);
                b_nonlinear = Vector<Number>(nonLinearsize);
                V_EVD       = Matrix<Number>(nonLinearsize,nonLinearsize);
                D_EVD       = DiagonalMatrix<Number>(nonLinearsize);
                Vinv_EVD    = Matrix<Number>(nonLinearsize,nonLinearsize);
                std::cout << "nonLinearsize: " << nonLinearsize << "\n";
                std::cout << "A_nonlinear\n" << A_nonlinear;
                insertNonLinearAndClassify(A_in, b_tr, m_size, A_nonlinear, b_nonlinear, mSTallvalues);
                EigenvalueDecomposition(A_nonlinear, nonLinearsize, CONDITION_LIMIT, V_EVD, D_EVD, Vinv_EVD);
                A_nonlinear = Vinv_EVD*A_nonlinear;
                b_nonlinear = Vinv_EVD*b_nonlinear;
            //3 things
                adjustLinearAndEVDcomponents(V_EVD, D_EVD, Vinv_EVD, A_in, b_nonlinear, m_size, V, Vinv, b_tr, mSTallvalues);
           } else {
    //NO LINEAR TERMS
                std::cout << "no linear terms\n";
                EigenvalueDecomposition(A_in, m_size, CONDITION_LIMIT, V, mSTallvalues.mSTindependentFunct.D, Vinv);
            //adjusting A,b
                A_in = Vinv*A_in;
                b_tr = Vinv*b_tr;
           }
        }
        matrix_in_parser.topLeftCorner(m_size,m_size) =  A_in;
        matrix_in_parser.topRightCorner(m_size,1) = b_tr;   //size
    //END USELESS
        //std::cout << matrix_in_parser;
	    PtrtoNewLoc = locationManager.create(matrix_in_parser);
        locations.insert(PtrtoNewLoc);
        mLocationPtrsMap.insert(std::make_pair(LocPtr, PtrtoNewLoc));
    //SAVING STRUCT
        TRACE("hypro.eigendecomposition", "D exact:\n" << mSTallvalues.mSTindependentFunct.D.diagonal() );
        //TRACE("hypro.eigendecomposition", "D approx:\n" << Ddouble.diagonal() );
        TRACE("hypro.eigendecomposition", "b_tr :\n" << b_tr );
        for( i=0; i<m_size; ++i) {
    //START MOVE
    //TODO COMPARISON ALMOST EQUAL 0 [else div by 0]
            if ( mSTallvalues.mSTindependentFunct.D.diagonal()(i) == 0 ) {
                mSTallvalues.mSTindependentFunct.xinhom(i)    = b_tr(i);
            } else {
                mSTallvalues.mSTindependentFunct.xinhom(i)    = b_tr(i) / mSTallvalues.mSTindependentFunct.D.diagonal()(i);
            }
        }
    //TODO INSERT HERE MODIFICATION of Vinv
        mSTallvalues.mSTflowpipeSegment.Vinv       = Vinv;
        mSTallvalues.mSTflowpipeSegment.V          = V;
        mLocPtrtoComputationvaluesMap.insert(std::make_pair(PtrtoNewLoc, mSTallvalues));
    //END MOVE
        //std::cout << "old loc: "<<LocPtr<<"\n";
        //std::cout << "new loc: "<<PtrtoNewLoc<<"\n";
    //INVARIANTS(TYPE CONDITION)
        const Condition<Number>& invar1 = LocPtr->getInvariant();
        Condition<Number> invar1NEW;
        //inv: A'= A*V
        for( i=0; i<invar1.size(); ++i ) {
            invar1NEW.setMatrix(invar1.getMatrix(i)*V,i);
            invar1NEW.setVector(invar1.getVector(i)  ,i);    
        }
        PtrtoNewLoc->setInvariant(invar1NEW);
    }
    mTransformedHA.setLocations(locations); 
    //TRANSITIONS
    transitionSet transitions;
    for (Transition<Number>* TransPtr : _hybrid.getTransitions() ) {
        Transition<Number>* NewTransPtr = new Transition<Number>(*TransPtr);  //! TODO !
        //transitions not freed, shared_ptr too costly in multithreaded context
    //POINTER
        Location<Number>*   NewSourceLocPtr = mLocationPtrsMap[TransPtr->getSource()];
        Location<Number>*   NewTargetLocPtr = mLocationPtrsMap[TransPtr->getTarget()];
        const Matrix<Number> & VSource = 
          mLocPtrtoComputationvaluesMap[NewSourceLocPtr].mSTflowpipeSegment.V;
        const Matrix<Number> & VinvTarget = 
          mLocPtrtoComputationvaluesMap[NewTargetLocPtr].mSTflowpipeSegment.Vinv;

        NewTransPtr->setSource(NewSourceLocPtr);
        NewTransPtr->setTarget(NewTargetLocPtr);
    //GUARD ( when transition can be made )
        const Condition<Number>& guard1    = TransPtr->getGuard();
        Condition<Number> guard1NEW; // = NewTransPtr->getGuard();
        //inv: A'= A*V; get V from location!!
        for( i=0; i<guard1.size(); ++i ) {
            guard1NEW.setMatrix(guard1.getMatrix(i)*VSource ,i);    
            guard1NEW.setVector(guard1.getVector(i)         ,i);    
        }
        NewTransPtr->setGuard(guard1NEW);
    //RESET ( reset into new location )
        const Reset<Number>& reset1    = TransPtr->getReset();
        Reset<Number> reset1NEW;// = NewTransPtr->getReset();
        //inv: A'= V^(-1)*A
        for( i=0; i<reset1.size(); ++i ) {
            reset1NEW.setMatrix(VinvTarget * reset1.getMatrix(i),i);
            reset1NEW.setVector(VinvTarget * reset1.getVector(i),i);
        }
        NewTransPtr->setReset(reset1NEW);
        transitions.insert(NewTransPtr);
    //LOCATION HAS TRANSITIONS
        NewTargetLocPtr->addTransition(NewTransPtr);
    }
    mTransformedHA.setTransitions    (transitions);
//INITIAL STATES
    locationStateMap initialStates;
    for(typename locationStateMap::const_iterator it=_hybrid.getInitialStates().begin(); 
      it!=_hybrid.getInitialStates().end(); ++it) {
        Location<Number>* NewLocPtr = mLocationPtrsMap[it->first];
        State<Number,ConstraintSet<Number>> state1NEW = State<Number,ConstraintSet<Number>>(it->second);
        state1NEW.setTimestamp(carl::Interval<Number>(0) );
        state1NEW.setLocation(NewLocPtr);
        mTransformedHA.addInitialState(state1NEW);
    }
//LOCAL BAD STATES (condition [matrix,vector] matrix=matrix*V
//typename locationConditionMap::const_iterator DOES NOT WORK
    for (typename HybridAutomaton<Number>::locationConditionMap::const_iterator it = _hybrid.getLocalBadStates().begin();
      it!=_hybrid.getLocalBadStates().end(); ++it ) {
        Location<Number>* NewLocPtr = mLocationPtrsMap[it->first];
        TRACE("hypro.eigendecomposition","OldLocPtr" << it->first);
        TRACE("hypro.eigendecomposition","NewLocPtr" << NewLocPtr);
        const Condition<Number> & badState = it->second;
        TRACE("hypro.eigendecomposition","BadState" << badState);
        Condition<Number> badStateNEW;
        const Matrix<Number> & V = 
          mLocPtrtoComputationvaluesMap[NewLocPtr].mSTflowpipeSegment.V;
        for(i=0; i<badState.size(); ++i) {
            badStateNEW.setMatrix(badState.getMatrix(i)*V, i);
            badStateNEW.setVector(badState.getVector(i)  , i);
        }
        TRACE("hypro.eigendecomposition","transformed localBadState: " << badStateNEW);
        mTransformedHA.addLocalBadState(NewLocPtr, badStateNEW);
    }
    //analyzeExponentialFunctions(); TODO REMOVE/MODIFY before!
    //for (const auto & locBadState : mTransformedHA.getLocalBadStates() ) {
    //    TRACE("hypro.eigendecomposition","in location: " << locBadState.first)
    //    TRACE("hypro.eigendecomposition","after trafo State:" << locBadState.second);
    //}
}
template <typename Number>
void Transformation<Number>::addGlobalBadStates
  (const HybridAutomaton<Number>& _hybrid, const bool transform) {

//CHECK MATCH OF LOCATION PTRS
    assert( _hybrid.getLocations().size() == mLocationPtrsMap.size() );
    typename locationPtrMap::const_iterator locIt = mLocationPtrsMap.begin();
    typename locationPtrMap::const_iterator endLocIt = mLocationPtrsMap.end();
    for (typename locationSet::iterator origIt=_hybrid.getLocations().begin();
      origIt!=_hybrid.getLocations().end(); ++origIt) {
        //locations is set -> value is ptrs to origLoc, in map key is ptrs to origLoc
        assert( *origIt == locIt->first );
        if(locIt != endLocIt)
            ++locIt;
    }
    assert( locIt == endLocIt );
//TRANSFORMATION -> add to localBadStates
    if (transform) {
        assert (!globalBadStatesTransformed);
        //TODO MEMORY ASSERTION?
        size_t i;
        for (typename conditionVector::const_iterator it = _hybrid.getGlobalBadStates().begin(); 
          it!=_hybrid.getGlobalBadStates().end(); ++it) {
            //transform each global badstate by setting of according localBadState
           //1. loop through global states
           //2. loop through ptr to location map and create new localBadState
            for (typename locationPtrMap::iterator locMapIt = mLocationPtrsMap.begin(); 
              locMapIt!=mLocationPtrsMap.end(); ++locMapIt) {
                Condition<Number> badStateNEW;
                const Matrix<Number> & V = mLocPtrtoComputationvaluesMap[locMapIt->second].mSTflowpipeSegment.V;
                for(i=0; i<it->size(); ++i) {
                    badStateNEW.setMatrix(it->getMatrix(i)*V, i);
                    badStateNEW.setVector(it->getVector(i)  , i);
                }
                mTransformedHA.addLocalBadState(locMapIt->second, badStateNEW);
            }
        }
    globalBadStatesTransformed = true;
    } else {
//NO TRANSFORMATION -> add to globalBadStates
        size_t i;
        for (typename conditionVector::const_iterator it = _hybrid.getGlobalBadStates().begin(); 
          it!=_hybrid.getGlobalBadStates().end(); ++it) {
           //loop through global states + copy to other HybridAutomaton
            for (typename locationPtrMap::iterator locMapIt = mLocationPtrsMap.begin(); 
              locMapIt!=mLocationPtrsMap.end(); ++locMapIt) {
                Condition<Number> globalbadStateNEW;
                for(i=0; i<it->size(); ++i) {
                    globalbadStateNEW.setMatrix(it->getMatrix(i), i);
                    globalbadStateNEW.setVector(it->getVector(i), i);
                }
                mTransformedHA.addGlobalBadState(globalbadStateNEW);
            }
        }
    }
}
//template <typename Number>
//void Transformation<Number>::analyzeExponentialFunctions() {
////TODO Location multiple flows and states (map of states to flows)
//    for ( auto &structObject : mLocPtrtoComputationvaluesMap) {
//        const size_t dimension = structObject.second.mSTflowpipeSegment.V.rows();
//        structObject.second.mSTindependentFunct.expFunctionType.reserve(dimension);
//        TRACE("hypro.eigendecomposition","looping through " << (structObject.first));//ptr-adress of location
//        //TRACE("hypro.eigendecomposition","Loc: " << V);
//        for(size_t i=0; i<dimension; ++i) {
//            //1. divergence D>0, 2. convergence D<0, 3. linear D=0
//            //4. const [never used yet since we can then not use decomposition]
//        //TODO close to 0
//            if(structObject.second.mSTindependentFunct.D.diagonal()(i) == 0) {
//                structObject.second.mSTindependentFunct.expFunctionType[i] = EXP_FUNCT_TYPE::LINEAR;
//                //TRACE("hypro.eigendecomposition","linear behaviour of " << i);
//            } else {
//                if(structObject.second.mSTindependentFunct.D.diagonal()(i) < 0) {
//                    structObject.second.mSTindependentFunct.expFunctionType[i] = EXP_FUNCT_TYPE::CONVERGENT;
//                    //TRACE("hypro.eigendecomposition","V\n" << V);
//                    //TRACE("hypro.eigendecomposition","V\n" << V);
//                } else {
//                    structObject.second.mSTindependentFunct.expFunctionType[i] = EXP_FUNCT_TYPE::DIVERGENT;
//                    //TRACE("hypro.eigendecomposition","V\n" << V);
//                    //TRACE("hypro.eigendecomposition","V\n" << V);
//                }
//            }
//        }
//    }
//}

template <typename Number>
void Transformation<Number>::declare_structures(STallValues<Number>& mSTallValues, const int n) {
    mSTallValues.mSTindependentFunct.D       = DiagonalMatrix<Number>(n);
    mSTallValues.mSTindependentFunct.xinhom  = Vector<Number>(n);
    mSTallValues.mSTflowpipeSegment.V        = Matrix<Number>(n,n);
    mSTallValues.mSTflowpipeSegment.Vinv     = Matrix<Number>(n,n);
}
//count linear and remember in according std::vector
template <typename Number>
size_t Transformation<Number>::countLinearAndRemember(const Matrix<Number>& A_in, 
        const size_t dimension, STallValues<Number>& mSTallvalues) {
    std::cout << "starting linear counting\n";
    //dimension = dimension of A_in
    size_t count_linearVariables = 0;
    size_t nrow, ncol;
    bool linear;
    for(nrow=0; nrow<dimension; ++nrow) {
        linear = true;
        //if(A_in.row(nrow).array() == 0) //TODO ISSUE FIXING?
        for(ncol=0; ncol<dimension; ++ncol) {
            if(A_in(nrow,ncol) != 0) {
                linear = false;
                break;
            }
        }
        if(linear == true) {
            ++count_linearVariables;
            mSTallvalues.mSTindependentFunct.expFunctionType[nrow] = EXP_FUNCT_TYPE::LINEAR;
        } else {
            assert( A_in(nrow,nrow != 0) ); //diagonal of nonlinear-term has to be defined
        }
    }
    return count_linearVariables;
}
//having linear terms, we grep nonlinear terms to calculate with
template <typename Number>
void Transformation<Number>::insertNonLinearAndClassify(const Matrix<Number>& A_in, const Vector<Number>& b_in, 
        const size_t dimension, Matrix<Number>& A_nonlinear, Vector<Number>& b_nonlinear, STallValues<Number>& mSTallvalues) {
    //std::cout << "starting Nonlinear building\n";
    //dimension of A_in
    size_t ncol, nrow;
    size_t count_linVar_row = 0;
    size_t count_linVar_col = 0;
//CHECK if according vector contains linear behavior -> skip columns
//for rows: count the according occurences to access correct element
    for (ncol=0; ncol<dimension; ++ncol) {
        if(mSTallvalues.mSTindependentFunct.expFunctionType[ncol] == EXP_FUNCT_TYPE::LINEAR) {
            ++count_linVar_col;
            continue;
        }
        count_linVar_row = 0;
        for(nrow=0; nrow<dimension; ++nrow) {
            if(mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
                ++count_linVar_row;
            } else {
                //std::cout << "nrow,countLin:" <<nrow<<","<<count_linVar_row<<" ncol,countLin:" << ncol <<","<<count_linVar_col << "\n";
                //std::cout << "A_nonlinear: \n" << A_nonlinear << "\n";
                A_nonlinear(nrow-count_linVar_row,ncol-count_linVar_col) = A_in(nrow,ncol);
                //std::cout << "A_nonlinear: \n" << A_nonlinear << "\n";
            }
        }
    }
    count_linVar_col = 0;
    for (ncol=0; ncol<dimension; ++ncol) {
        if(mSTallvalues.mSTindependentFunct.expFunctionType[ncol] == EXP_FUNCT_TYPE::LINEAR) {
            ++count_linVar_col;
            if(b_in(ncol) == 0) {
                mSTallvalues.mSTindependentFunct.expFunctionType[ncol] = EXP_FUNCT_TYPE::CONSTANT;
            }
        } else {
            b_nonlinear(ncol-count_linVar_col) = b_in(ncol);

        }
    }
    std::cout << "A_nonlinear after reduction\n"<< A_nonlinear;
}
template <typename Number>
void Transformation<Number>::EigenvalueDecomposition(const Matrix<Number>& A_nonlinear, 
        const size_t dimensionNonLinear, const size_t CONDITION_LIMIT, Matrix<Number>& V_EVD, 
        DiagonalMatrix<Number>& D_EVD, Matrix<Number>& Vinv_EVD) {
    //std::cout << "starting EVD\n";
//EVD returns bad results on one dimension TODO verify results
//TODO (if needed) make circularity checks of components
    if(dimensionNonLinear == 1) {
        V_EVD         (0,0) = 1;
        Vinv_EVD      (0,0) = 1;
        D_EVD.diagonal()(0) = A_nonlinear(0,0);
        return;
    }
    //assert(A_nonlinear.asDiagonal().array() != 0); //any element = 0 => ERROR/not diagonizable
    DiagonalMatrixdouble Ddouble    = DiagonalMatrixdouble(dimensionNonLinear); //formulation in .h
    Matrix<double> Vdouble          = Matrix<double>(dimensionNonLinear,dimensionNonLinear);
    Matrix<double> Vinvdouble       = Matrix<double>(dimensionNonLinear,dimensionNonLinear);
    Matrix<double> matrixCalcDouble = Matrix<double>(dimensionNonLinear,dimensionNonLinear);
    matrixCalcDouble = convert<Number,double> (A_nonlinear);
    Eigen::EigenSolver<Matrix<double>> es(matrixCalcDouble);
    Vdouble << es.eigenvectors().real();
    Ddouble.diagonal() << es.eigenvalues().real();
    Vinvdouble = Vdouble.inverse();
//ASSERTION CONDITION TODO making this faster for big/sparse matrices
    Eigen::JacobiSVD<Matrix<double>> svd(Vinvdouble);  
    double cond = svd.singularValues()(0)  / svd.singularValues()(svd.singularValues().size()-1);
    if(std::abs(cond) > CONDITION_LIMIT) {
        FATAL("hypro.eigendecomposition","condition is higher than CONDITION_LIMIT");
    }
    std::cout <<"A_nonlinear\n" << A_nonlinear;
    std::cout <<"Vinv_EVD(condition): ("<< cond <<")\n" << Vinv_EVD;
//CONVERSION TO RATIONAL
    V_EVD = convert<double,Number>(Vdouble);
    D_EVD = convert<double,Number>(Ddouble);
    Vinv_EVD = convert<double,Number>(Vinvdouble);
    TRACE("hypro.eigendecomposition","V\n" << V_EVD);
    TRACE("hypro.eigendecompositoin","Vinv\n" << Vinv_EVD);
}
template <typename Number>
void Transformation<Number>::adjustLinearAndEVDcomponents(
        const Matrix<Number>& V_EVD, const DiagonalMatrix<Number>& D_EVD, const Matrix<Number>& Vinv_EVD, 
        const Matrix<Number>& A_in, const Vector<Number>& b_nonlinear, const size_t dimension, 
        Matrix<Number>& V, Matrix<Number>& Vinv, 
        Vector<Number>& b_tr, STallValues<Number>& mSTallvalues) {
//1.setting V,Vinv,D,b_tr accordingly
    V.setIdentity   (dimension,dimension);
    Vinv.setIdentity(dimension,dimension);
    mSTallvalues.mSTindependentFunct.D.diagonal().setZero(dimension);
    size_t nrow, ncol;
    size_t count_linVar_row = 0;
    size_t count_linVar_col = 0;
    for (ncol=0; ncol<dimension; ++ncol) {
        if(mSTallvalues.mSTindependentFunct.expFunctionType[ncol] == EXP_FUNCT_TYPE::LINEAR) {
            ++count_linVar_col;
            continue;
        }
        count_linVar_row = 0;
        for(nrow=0; nrow<dimension; ++nrow) {
            if(mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
                ++count_linVar_row;
                continue;
            } else {
                V    (nrow,ncol) = V_EVD   (nrow-count_linVar_row,ncol-count_linVar_col);
                Vinv (nrow,ncol) = Vinv_EVD(nrow-count_linVar_row,ncol-count_linVar_col);
                mSTallvalues.mSTindependentFunct.D.diagonal()(ncol) = D_EVD.diagonal()(ncol-count_linVar_col);
            }
        }
    //ASSIGN b_tr
        b_tr(ncol) = b_nonlinear(ncol-count_linVar_col);
    }
    mSTallvalues.mSTflowpipeSegment.V = V;
    mSTallvalues.mSTflowpipeSegment.Vinv = Vinv;

//2.ADJUSTING b_tr (b_nonlinear was assigned)
    std::cout << "A_in\n" << A_in;
    std::cout << b_tr;
    for(nrow=0; nrow<dimension; ++nrow) {
        if(mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == EXP_FUNCT_TYPE::LINEAR) {
            for(ncol=0; ncol<dimension; ++ncol) {
                b_tr(ncol) += A_in(nrow,ncol)*b_tr(nrow);
            }
        }
    }
    std::cout << "A_in\n" << A_in;
    std::cout << b_tr << "\n";
//3.ANALYZING D
    for(nrow=0; nrow<dimension; ++nrow) {
        if(mSTallvalues.mSTindependentFunct.expFunctionType[nrow] == INITIALIZED) {
            assert (mSTallvalues.mSTindependentFunct.D.diagonal()(ncol) != 0);
            //TODO ASSERTION fails, DiagonalMatrix OUTOFBOUNDS !!!
            if(mSTallvalues.mSTindependentFunct.D.diagonal()(ncol) > 0) {
                mSTallvalues.mSTindependentFunct.expFunctionType[nrow] = CONVERGENT;
            } else {
                mSTallvalues.mSTindependentFunct.expFunctionType[nrow] = DIVERGENT;
            }
        }
    }
}

template <typename Number>
void Transformation<Number>::output_HybridAutomaton() {
    std::cout << mTransformedHA << "\n-------------- ENDOFAUTOMATA ------------------" << std::endl;
}

} //namespace hypro
