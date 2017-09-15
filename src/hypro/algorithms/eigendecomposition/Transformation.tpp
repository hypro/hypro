#include "Transformation.h"

namespace hypro {

template <typename Number, typename Representation>
Transformation<Number,Representation>::Transformation (const HybridAutomaton<Number>& _hybrid) {
    Matrix<Number> matrix_in_parser;
    Matrix<Number> matrix_calc;
    size_t m_size;
    Matrix<Number> V;                             //backtransformation
    Matrix<Number> Vinv;                          //dumped after use
    Vector<Number> b_tr;                          //transformed and dumped after use
    LocationManager<Number>& locationManager = LocationManager<Number>::getInstance();
    locationSet locations;
    Location<Number>* PtrtoNewLoc;
    //std::cout<<"size mSTallValues: "<< sizeof(mSTallValues);
    mTransformedHA = HybridAutomaton<Number>();
    for (Location<Number>* LocPtr : _hybrid.getLocations() ) {
        matrix_in_parser = LocPtr->getFlow();   //copy for calculation; TODO (getsize() missing) many flows
        m_size = matrix_in_parser.cols(); //rows
        //ASSERTION SIZE >= 1 --> delete new locations/skip?
        //are old Matrices freed automatically on new initialization?
        m_size -= 1;
        STallValues<Number> mSTallvalues;               //declare all values for Location
        declare_structures(mSTallvalues, m_size);       //init --> TODO map including
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
    //INVARIANTS(TYPE CONDITION)        [output stream broken with assertion without invariants!]
        Condition<Number> mInvariant;
        Condition<Number> mInvariantNEW;
        //const Condition<Number>&
        mInvariant = LocPtr->getInvariant();            //object for invariants
        mInvariantNEW = PtrtoNewLoc->getInvariant();    //object for invariants
        //std::cout << "Inv: " << mInvariant << std::endl;
        //setTransitions(const transitionSet& trans);    <-
        //for( std::size_t i = 0 : mInvariant.size()-1 ) {    //TODO MODIFY Loop through invariants
        //    mInvariantNEW.setMatrix(Converter.linearTransformation(mInvariant.getMatrix()*V);    //inv: A'= A*V
        //    
        //}
        // A transformation: A' = A*V <-- V.linearTransformation(A)
        //V.linearTransformation(mInvariant.getMatrix())
        mInvariantNEW.setMatrix(mInvariant.getMatrix()*V);    //inv: A'= A*V
        mInvariantNEW.setVector(mInvariant.getVector());
        PtrtoNewLoc->setInvariant(mInvariantNEW);
    //SAVING STRUCT
        mSTallvalues.mSTinputVectors.x0     = //TODO THIS
        mSTallvalues.mSTinputVectors.x0_2   = //TODO THIS
        //mSTallvalues.mSTindependentFunct.D = {.xin}   //already assigned
        mSTallvalues.mSTindependentFunct.xinhom    = b_tr.array() / mSTallvalues.mSTindependentFunct.D.diagonal().array();
        //mSTallvalues.mSTindependentFunct.delta      = //check if existing
        //mSTallvalues.mSTindependentFunct.deltalimit = //check if existing
        mSTallvalues.mSTdependentFunct.x_tr.col(0) = Vinv*mSTallvalues.mSTinputVectors.x0  ;
        mSTallvalues.mSTdependentFunct.x_tr.col(1) = Vinv*mSTallvalues.mSTinputVectors.x0_2;
        mSTallvalues.mSTdependentFunct.xhom.col(0) = mSTallvalues.mSTindependentFunct.array()
          + dep_f.x_tr.col(0).array();
        mSTallvalues.mSTdependentFunct.xhom.col(1) = mSTallvalues.mSTindependentFunct.array()
          + dep_f.x_tr.col(1).array();
        //mSTallvalues.mSTevalFunctions                 //assigned in init
        mSTallvalues.mSTflowpipeSegment.V          = V; //rest of flow used only for plotting

    //dep_f
    //dep_f

        mLocPtrtoComputationvaluesMap.insert(std::make_pair(PtrtoNewLoc, mSTallvalues));
    }
    mTransformedHA.setLocations(locations); //add LocationSet to HybridAutomaton
    //TRANSITIONS
        //std::cout << "Location: " << *PtrtoNewLoc;   //?? tryout
    transitionSet transitions;
    //State --> linearTransformation 
    //Guards Condition
    //Reset --> Vector von ConstraintSets [Hpolytope]
    //Converter

    //for (Transition<Number>* TransPtr : _hybrid.getTransitions() ) {
    //   transitions.insert( 


    //}
    //TODO
    mTransformedHA.setTransitions    (transitions);
    //WITHOUT OUTPUT
    mTransformedHA.setInitialStates  (_hybrid.getInitialStates())  ;
    mTransformedHA.setLocalBadStates (_hybrid.getLocalBadStates()) ;
    mTransformedHA.setGlobalBadStates(_hybrid.getGlobalBadStates());
    //INVARIANTS TRANSFORMATION
        //
        //PtrtoNewLoc -> setInvariant( const struct Location<Number>::Invariant& _inv );
    //TRANSITIONTS???
    //
}
//TODO inhomogen plot is only used directly after Constructor and uses that objects
//in_traj.xhom.col(0) = ind_f.xinhom.array() + in_traj.x_tr.col(0).array();
//in_traj.xhom.col(1) = ind_f.xinhom.array() + in_traj.x_tr.col(1).array();

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
    mSTallValues.STflowpipeSegment.V = Matrix<Number>(n,n);
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
