#include "Transformation.h"

namespace hypro {

/*     
 *
 *
 */
//template <typename Number>
//Transformation::Transformation( HybridAutomaton<Number>& _hybrid ) {
////go through all locations
//    
//}
//const typename HybridAutomaton<Number>::locationStateMap& HybridAutomaton<Number>::localBadStates() const

template <typename Number>
Transformation<Number>::Transformation (const HybridAutomaton<Number>& _hybrid, HybridAutomaton<Number>& transformed_ha) {
    Matrix matrix_in_parser;
    Matrix matrix_calc;
    size_t m_size;
    Matrix V;                             //backtransformation
    Matrix Vinv;                          //dumped after use
    Vector b_tr;                          //transformed and dumped after use
    for ( Location<Number>* LocPtr : _hybrid.locations() ) {
    //for(std::pair<std::set<Location<Number>*>::iterator,std::set<Location<Number>*>::iterator> 
    //        it(_hybrid.locations().begin(),transformed_ha.locations().begin());
    //        it.first != _hybrid.locations().end(); /*transformed of same size due to copy*/
    //        ++it.first, ++it.second) {
        matrix_in_parser = LocPtr->flow();   //matrix was pased as reference
        m_size = matrix_in_parser.cols(); //rows
        //ASSERTION SIZE >= 1
        m_size -= 1;
        std::cout<<"Matrix SIZE: " << m_size << std::endl;
        //reserve storage
        
        V    = Matrix(m_size,m_size);
        Vinv = Matrix(m_size,m_size);
        b_tr = Vector(m_size);
        matrix_calc = matrix_in_parser.topLeftCorner(m_size,m_size);        
        //std::cout<<"submatrix: " << matrix.topLeftCorner(m_size,m_size) << std::endl;
        //calculate matrix decomposition
        std::cout<<"A: "<<std::endl<<matrix_calc;
        Eigen::EigenSolver<Matrix> es(matrix_calc);    //decompose matrix directly + constructor
        //transform location with V^(-1)
        V << es.eigenvectors().real();
        //ind_f.D.diagonal() << es.eigenvalues().real();
        Vinv = V.inverse();
        matrix_calc = Vinv*matrix_calc;
        b_tr        = Vinv*b_tr;
        //TODO x0 and x0_2 getting independent? of model input?!?
        //ITERATION OVER BOTH AUTOMATA USELESS --> JUST USE ONE in constructor and transform it
        //afterwards connect with syntax like above all states std::unorderd_map useful therefore
        //ind_f.D.diagonal() << es.eigenvalues().real();
    //Vinv = V.inverse();
    }
}
//locationSet& locations() const;
//transitionSet& transitions() const;
//locationStateMap& initialStates() const;
//locationStateMap& localBadStates() const;
//setVector& globalBadStates()
//template <typename Number>

} //namespace hypro
