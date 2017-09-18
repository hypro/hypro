#include "Transformation.h"

namespace hypro {

template <typename Number, typename Representation>
Transformation<Number,Representation>::Transformation (const HybridAutomaton<Number>& _hybrid) {
    Matrix<Number> matrix_in_parser;
    Matrix<Number> matrix_calc;
    size_t m_size, i;
    Matrix<Number> V;                             //backtransformation
    Matrix<Number> Vinv;                          //dumped after use
    Vector<Number> b_tr;                          //transformed and dumped after use
    LocationManager<Number>& locationManager = LocationManager<Number>::getInstance();
    locationSet locations;
    Location<Number>* PtrtoNewLoc;
    //std::cout<<"size mSTallValues: "<< sizeof(mSTallValues);
    mTransformedHA = HybridAutomaton<Number>();
//LOCATIONS
    for (Location<Number>* LocPtr : _hybrid.getLocations() ) {
        matrix_in_parser = LocPtr->getFlow();   //copy for calculation; TODO (getsize() missing) many flows
        m_size = matrix_in_parser.cols(); //rows
        //ASSERTION SIZE >= 1 --> delete new locations/skip?
        m_size -= 1;
        STallValues<Number> mSTallvalues;
        declare_structures(mSTallvalues, m_size);
        b_tr        = Vector<Number>(m_size);
        matrix_calc = Matrix<Number>(m_size,m_size);
        V           = Matrix<Number>(m_size,m_size);
        Vinv        = Matrix<Number>(m_size,m_size);
        b_tr        = matrix_in_parser.topRightCorner(m_size,1);//map?
        matrix_calc = matrix_in_parser.topLeftCorner(m_size,m_size);        
        std::cout<<"A: "<<std::endl<<matrix_calc;
    //LOCATION TRANSFORMATION
        Eigen::EigenSolver<Matrix<Number>> es(matrix_calc);    //decompose matrix
        V << es.eigenvectors().real();
        mSTallvalues.mSTindependentFunct.D.diagonal() << es.eigenvalues().real();
        Vinv = V.inverse();
        //ASSERTION CONDITION OF Vin --> define behavior
        //TODO condition number Vinv
        std::cout <<"Vinv: " << std::endl << Vinv;
        //std::cout <<"D: "    << std::endl << D;
        matrix_calc = Vinv*matrix_calc;
        b_tr        = Vinv*b_tr;
        std::cout<<"Vinv*A("<<m_size<<"x"<<m_size<<"),b_tr"<<std::endl;
        //rows,cols in eigen
        matrix_in_parser.topLeftCorner(m_size,m_size) =  matrix_calc;
        matrix_in_parser.topRightCorner(m_size,1) = b_tr;   //size
        //std::cout << matrix_in_parser;
	    PtrtoNewLoc = locationManager.create(matrix_in_parser);
        locations.insert(PtrtoNewLoc);
        mLocationPtrsMap.insert(std::make_pair(LocPtr, PtrtoNewLoc));   //cant use const type* const
    //INVARIANTS(TYPE CONDITION)        [TODO output stream broken with assertion without invariants!]
        const Condition<Number>& invar1 = LocPtr->getInvariant();
        Condition<Number> invar1NEW; // = PtrtoNewLoc->getInvariant();
        //inv: A'= A*V
        for( i=0; i<invar1.size(); ++i ) {
            invar1NEW.setMatrix(invar1.getMatrix(i)*V,i);
            invar1NEW.setVector(invar1.getVector(i)  ,i);    
        }
        //invar1.setMatrix(mInvariant.getMatrix()*V);    //inv: A'= A*V
        //invar1NEW.setVector(mInvariant.getVector());
        PtrtoNewLoc->setInvariant(invar1NEW);
    //SAVING STRUCT
        //mSTallvalues.mSTinputVectors.x0       //MOVE TO ALG
        //mSTallvalues.mSTinputVectors.x0_2     //MOVE TO ALG
        //mSTallvalues.mSTindependentFunct.D = {.xin}   //already assigned
        mSTallvalues.mSTindependentFunct.xinhom    = b_tr.array() / mSTallvalues.mSTindependentFunct.D.diagonal().array();
        //mSTallvalues.mSTindependentFunct.delta      = //TODO check if existing
        //mSTallvalues.mSTindependentFunct.deltalimit = //TODO check if existing
        //mSTallvalues.mSTdependentFunct.x_tr   //MOVE TO ALG
        //mSTallvalues.mSTdependentFunct.xhom   //MOVE TO ALG
        //mSTallvalues.mSTevalFunctions                 //assigned in init
        mSTallvalues.mSTflowpipeSegment.Vinv       = Vinv;
        mSTallvalues.mSTflowpipeSegment.V          = V; //rest of flow used only for plotting
        mLocPtrtoComputationvaluesMap.insert(std::make_pair(PtrtoNewLoc, mSTallvalues));
    }
    mTransformedHA.setLocations(locations); //add LocationSet to HybridAutomaton
//TRANSITIONS
    transitionSet transitions;
    for (Transition<Number>* TransPtr : _hybrid.getTransitions() ) {
        Transition<Number>* NewTransPtr = new Transition<Number>(*TransPtr);  //! TODO !
        //transitions not freed, shared_ptr too costly in multithreaded context
    //POINTER
        //we need ptr->source 4 times
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
        //inv: A'= A*V
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
    //State = Vinv*A and Vinv*b -> State.linearTransformation(Vinv)
    locationStateMap initialStates;
    State<Number,ConstraintSet<Number>> state1NEW;
    for(typename locationStateMap::const_iterator it=_hybrid.getInitialStates().begin(); 
      it!=_hybrid.getInitialStates().end(); ++it) {
        Location<Number>* NewLocPtr = mLocationPtrsMap[it->first];
        const Matrix<Number> & Vinv = 
          mLocPtrtoComputationvaluesMap[NewLocPtr].mSTflowpipeSegment.Vinv;
        state1NEW = it->second.linearTransformation(Vinv);
        state1NEW.setLocation(NewLocPtr);
        initialStates.insert(make_pair(NewLocPtr, state1NEW));
    }
    mTransformedHA.setInitialStates  (initialStates);
//LOCAL BAD STATES (condition [matrix,vector] matrix=matrix*V
//typename locationConditionMap::const_iterator DOES NOT WORK
    for (auto it = _hybrid.getLocalBadStates().begin();
      it!=_hybrid.getLocalBadStates().end(); ++it ) {
        Location<Number>* NewLocPtr = mLocationPtrsMap[it->first];
        const Condition<Number> & badState = it->second;
        Condition<Number> badStateNEW;
        const Matrix<Number> & V = 
          mLocPtrtoComputationvaluesMap[NewLocPtr].mSTflowpipeSegment.V;
        for(i=0; i<badState.size(); ++i) {
            badStateNEW.setMatrix(badState.getMatrix(i)*V, i);
            badStateNEW.setVector(badState.getVector(i)  , i);
        }
        mTransformedHA.addLocalBadState(NewLocPtr, badStateNEW);
    }
//GLOBAL BAD STATES
    transformGlobalBadStates(_hybrid);
    //DEBUG??
}
template <typename Number, typename Representation>
void Transformation<Number,Representation>::transformGlobalBadStates
  (const HybridAutomaton<Number>& _hybrid) {
    //check if transformation is according to hybrid automaton
   // for(std::pair<locationSet::iterator, locationPtrMap> it= _hybrid.getLocations().begin(); 
   //   it!=_hybrid.getLocations().end(); ++i) {
   //     
   //     if(

   // }
   // 
   //// for (std::pair<intIter, dubIter> i(intVec.begin(), dubVec.begin());
   ////   i.first != intVec.end() /* && i.second != dubVec.end() */;
   ////   ++i.first, ++i.second) {
   ////     result += (*i.first) * (*i.second);
   //// }

   // //check if there exists a transformation to this Hybrid automaton
   // if(!globalBadStatesTransformed) {
   //     for (Condition<Number> & globalBadStates: _hybrid.getGlobalBadStates()) {
   //         
   //     }

   //     globalBadStatesTransformed = true;
   // }
//    mTransformedHA.setGlobalBadStates(_hybrid.getGlobalBadStates());
}
//TODO Set von global->local mapping
//in transformed automata in local sets saving
//NOT POSSIBLE DUE TO SIMPLE MATRIX/VECTOR:
        // A transformation: A' = A*V <-- V.linearTransformation(A)
        //V.linearTransformation(mInvariant.getMatrix())
//TODO inhomogen plot is only used directly after Constructor and uses that objects
    //in_traj.xhom.col(0) = ind_f.xinhom.array() + in_traj.x_tr.col(0).array();
    //in_traj.xhom.col(1) = ind_f.xinhom.array() + in_traj.x_tr.col(1).array();
    //mSTallvalues.mSTdependentFunct.x_tr.col(0) = Vinv*mSTallvalues.mSTinputVectors.x0  ;  //MOVE TO ALG
    //mSTallvalues.mSTdependentFunct.x_tr.col(1) = Vinv*mSTallvalues.mSTinputVectors.x0_2;  //MOVE TO ALG
    //mSTallvalues.mSTdependentFunct.xhom.col(0) = mSTallvalues.mSTindependentFunct.array() //MOVE TO ALG
    //  + dep_f.x_tr.col(0).array();
    //mSTallvalues.mSTdependentFunct.xhom.col(1) = mSTallvalues.mSTindependentFunct.array() //MOVE TO ALG
    //  + dep_f.x_tr.col(1).array();

template <typename Number, typename Representation>
void Transformation<Number,Representation>::declare_structures(STallValues<Number>& mSTallValues, const int n) {
    mSTallValues.mSTindependentFunct.xinhom  = Matrix<Number>(n,n);
    mSTallValues.mSTinputVectors.x0          = Vector<Number>(n);
    mSTallValues.mSTinputVectors.x0_2        = Vector<Number>(n);
    mSTallValues.mSTindependentFunct.D       = DiagonalMatrix<Number>(n);
    mSTallValues.mSTindependentFunct.xinhom  = Matrix<Number>(n,n);
    mSTallValues.mSTdependentFunct.xhom      = Matrix<Number>(n,n);
    //TODO change to multiple values, last column for transformation maxmin
    mSTallValues.mSTdependentFunct.x_tr      = Matrix<Number>::Zero(n,3);    
    mSTallValues.mSTdependentFunct.x_tr.col(2).array() = 0;
    mSTallValues.mSTevalFunctions.deriv      = Matrix<Number>(n,n);
    //TODO CHANGE 2 to number of points ?! or use 2 column with numbers: 
    //[max,min] for direct [-max,-min] for indirect starting at !!1!!
    mSTallValues.mSTevalFunctions.direct     = BoolMatrix(n,2);
    mSTallValues.mSTevalFunctions.direct.setConstant(0);
    mSTallValues.mSTflowpipeSegment.V        = Matrix<Number>(n,n);
    mSTallValues.mSTflowpipeSegment.Vinv     = Matrix<Number>(n,n);
    //delta, deltalimit of STindependentFunc missing
    //flowpipe only V for backtransformation into original system
}
//mark if in transformed system x0<x0_2 in 3rd column
template <typename Number, typename Representation>
void Transformation<Number,Representation>::mark_x0isMin(Matrix<Number>& x_tr, const int n) {
    for(int i=0; i<n; ++i) {   //check if x0_tr >= x0_2_tr
        if(x_tr(i,0) < x_tr(i,1)) {
            x_tr(i,2) = 1; //mark second column to recognize later
        }
    }
}
//x0<x0_2 will never change, so we can simply swap to transform systems
template <typename Number, typename Representation>
void Transformation<Number,Representation>::swap_x0isMax(Matrix<Number>& x_tr, const int n) {
    //std::cout << "x_tr beforeback: "<< std::endl << x_tr << std::endl;
    Vector<Number> tmp = Vector<Number>(n);
    for(int i=0; i<n; ++i) {
        if(x_tr(i,2) == 1) {
            tmp(i)    = x_tr(i,0);
            x_tr(i,0) = x_tr(i,1);
            x_tr(i,1) = tmp(i);
        }
    }
    //std::cout << "x_tr afterback: "<< std::endl << x_tr << std::endl;
}
//locationSet& locations() const;
//transitionSet& transitions() const;
//locationStateMap& initialStates() const;
//locationStateMap& localBadStates() const;
//setVector& globalBadStates()
template <typename Number, typename Representation>
void Transformation<Number,Representation>::output_HybridAutomaton() {
    std::cout << mTransformedHA << std::endl << "-------------- ENDOFAUTOMATA ------------------" << std::endl;
}
} //namespace hypro
