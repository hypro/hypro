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
    matrix_t<Number> matrix_setting;
    matrix_t<Number> matrix_calc;
    for ( Location<Number>* LocPtr : _hybrid.locations() ) {
        matrix_t<Number> matrix = LocPtr->flow();   //matrix was pased as reference
    }

}
//locationSet& locations() const;
//transitionSet& transitions() const;
//locationStateMap& initialStates() const;
//locationStateMap& localBadStates() const;
//setVector& globalBadStates()
//template <typename Number>

} //namespace hypro
