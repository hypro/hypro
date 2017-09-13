#include "Transformation.h"

namespace hypro {

template <typename Number>
Transformation<Number>::Transformation (const HybridAutomaton<Number>& _hybrid) {
    Matrix<Number> matrix_in_parser;
    Matrix<Number> matrix_calc;
    size_t m_size;
    Matrix<Number> V;                             //backtransformation
    Matrix<Number> Vinv;                          //dumped after use
    Vector<Number> b_tr;                          //transformed and dumped after use
    LocationManager<Number>& locationManager = LocationManager<Number>::getInstance();
    locationSet locations;
    //std::cout<<"size mSTallValues: "<< sizeof(mSTallValues);
    mTransformedHA = HybridAutomaton<Number>();
    for ( Location<Number>* const &LocPtr : _hybrid.getLocations() ) {
        matrix_in_parser = LocPtr->getFlow();   //copy matrix here to calculate
        m_size = matrix_in_parser.cols(); //rows
        //ASSERTION SIZE >= 1 --> delete new locations/skip?
        //are old Matrices freed automatically on new initialization?
        m_size -= 1;
        STallValues<Number> mSTallvalues;               //declare all values for Location
        declare_structures(mSTallvalues, m_size);       //init
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
	    Location<Number>* PtrtoNewLoc = locationManager.create(matrix_in_parser);
        locations.insert(PtrtoNewLoc);
        mLocationPtrsMap.insert(std::make_pair(LocPtr, PtrtoNewLoc));
    }
    mTransformedHA.setLocations(locations);

    //INVARIANTS TRANSFORMATION
        //
        //PtrtoNewLoc -> setInvariant( const struct Location<Number>::Invariant& _inv );
    //TRANSITIONTS???
    //
}
template <typename Number>
void Transformation<Number>::declare_structures(STallValues<Number>& mSTallValues, const int n) {
    
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
    //delta, deltalimit in STindependentFunc missing
    //flowpipe not needed
}
//mark if in transformed system x0<x0_2 in 3rd column
template <typename Number>
void Transformation<Number>::mark_x0isMin(Matrix<Number>& x_tr, const int n) {
    for(int i=0; i<n; ++i) {   //check if x0_tr >= x0_2_tr
        if(x_tr(i,0) < x_tr(i,1)) {
            x_tr(i,2) = 1; //mark second column to recognize later
        }
    }
}
//x0<x0_2 will never change, so we can simply swap to transform systems
template <typename Number>
void Transformation<Number>::swap_x0isMax(Matrix<Number>& x_tr, const int n) {
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
template <typename Number>
void Transformation<Number>::output_HybridAutomaton() {
    std::cout << mTransformedHA << std::endl << "-------------- ENDOFAUTOMATA ------------------" << std::endl;
}
} //namespace hypro
