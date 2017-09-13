#include "Transformation.h"

namespace hypro {

//const typename HybridAutomaton<Number>::locationStateMap& HybridAutomaton<Number>::localBadStates() const
template <typename Number>
Transformation<Number>::Transformation (const HybridAutomaton<Number>& _hybrid) {
    Matrix<Number> matrix_in_parser;
    Matrix<Number> matrix_calc;
    size_t m_size;
    Matrix<Number> V;                             //backtransformation
    Matrix<Number> Vinv;                          //dumped after use
    Vector<Number> b_tr;                          //transformed and dumped after use
    //STindependentFunct  mSTindependentFunct;
    //STdependentFunct    mSTdependentFunct;
    //STevalFunctions     mSTevalFunctions;
    //STallValues<Number> mSTallValues;
    //std::cout<<"size mSTallValues: "<< sizeof(mSTallValues);
    mTransformedHA = HybridAutomaton<Number>();
    //std::cout << _hybrid ;
    unsigned locID = 0;
    for ( Location<Number>* LocPtr : _hybrid.locations() ) {
        matrix_in_parser = LocPtr->flow();   //matrix was pased as reference
        m_size = matrix_in_parser.cols(); //rows
        //ASSERTION SIZE >= 1 --> delete new locations/skip?
        //are old Matrices freed automatically on new initialization?
        m_size -= 1;
        STallValues<Number> mSTallvalues;   //all values for Location
        //mSTallvalues.STinputVectors.x0 = Vector<Number>(m_size);    //<----------------------- WRONG
        //declare_structures(m_size,mSTindependentFunct,mSTdependentFunct,mSTevalFunctions );
        b_tr        = Vector<Number>(m_size);
        matrix_calc = Matrix<Number>(m_size,m_size);
        V           = Matrix<Number>(m_size,m_size);
        Vinv        = Matrix<Number>(m_size,m_size);
        b_tr        = matrix_in_parser.topRightCorner(m_size,1);//map?
        matrix_calc = matrix_in_parser.topLeftCorner(m_size,m_size);        
        std::cout<<"A: "<<std::endl<<matrix_calc;
        Eigen::EigenSolver<Matrix<Number>> es(matrix_calc);    //decompose matrix
        V << es.eigenvectors().real();
        //mSTindependentFunct.D.diagonal() << es.eigenvalues().real();
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
        std::cout << matrix_in_parser;
        //Location( locID, matrix_in_parser );
        //addLocation( Location<Number>* _location );
        //TODO x0 and x0_2 -> we need points!!!
        //use std::unorderd_map ?
    }
    //locations transformed + condition okay --> transform rest
}
//template <typename Number> 
//void Transformation<Number>::declare_structures(const int n, 
//        STindependentFunct& mSTindependentFunct,
//        STdependentFunct  & mSTdependentFunct,
//        STevalFunctions   & mSTevalFunctions ) {
//    //in_eq1.x0 = Vector<Number>(n);                          //TODO calculate number of points
//    //in_eq1.x0_2 = Vector<Number>(n);                        //NOT NEEDED
//    mSTindependentFunct.xinhom = Vector<Number>(n);
//	mSTindependentFunct.D = DiagonalMatrix<Number>(2);      //type Number size 2
//    mSTdependentFunct.x_tr = Matrix<Number>::Zero(n,3);     //TODO calculate number of points
//    mSTdependentFunct.x_tr.col(2).array() = 0;
//    mSTdependentFunct.xhom = Matrix<Number>::Zero(2,2);
//    //in_traj.x_tr = Matrix<Number>::Zero(n,2);       //TODO calculate number of points
//    //in_traj.xhom = Matrix<Number>::Zero(n,2);
//    mSTevalFunctions.deriv  = Matrix<Number>(n,2);
//    mSTevalFunctions.direct = BoolMatrix<Number>(n,2);
//    mSTevalFunctions.direct.setConstant(0);
//}
//locationSet& locations() const;
//transitionSet& transitions() const;
//locationStateMap& initialStates() const;
//locationStateMap& localBadStates() const;
//setVector& globalBadStates()
//template <typename Number>

} //namespace hypro
