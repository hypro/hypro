#include "ltiTimeEvolutionHandler.h"

namespace hypro {
template <typename State, typename Number>
State ltiApplyTimeEvolution( const State& currentSegment, const matrix_t<Number>& transformation, const vector_t<Number>& translation, tNumber timeStepSize ) {
	return currentSegment.partiallyApplyTimeStep( hypro::ConstraintSet<Number>( transformation, translation ), timeStepSize, 0 );
}

}  // namespace hypro
