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
void Transformation<Number>::transform( HybridAutomaton<Number>& _hybrid ) {
    HybridAutomaton<Number> res;
    Matrix matrix_in_parser;
    Matrix matrix_calc;
    size_t m_size;
    Matrix V; = Matrix(n,n);                             //backtransformation
    Matrix Vinv; = Matrix(n,n);                          //dumped after use
    Vector b_tr; = Vector(n);                            //transformed and dumped after use
    for ( Location<Number>* LocPtr : _hybrid.locations() ) {
        matrix_in_parser = LocPtr->flow();   //matrix was pased as reference
        m_size = matrix_in_parser.cols(); //rows
        //SIZE >= 1
        m_size -= 1;
        std::cout<<"Matrix SIZE: " << m_size << std::endl;
        //reserve storage
        


        matrix_calc = matrix_in_parser.topLeftCorner(m_size,m_size);        
        //std::cout<<"submatrix: " << matrix.topLeftCorner(m_size,m_size) << std::endl;
        //calculate matrix decomposition
        std::cout<<"A: "<<std::endl<<matrix_calc;
        Eigen::EigenSolver<Matrix> es(matrix_calc);    //decompose matrix directly + constructor
    //V << es.eigenvectors().real();
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
