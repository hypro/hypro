#include "HardSigmoid.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoid<Number>::exactHardSigmoid( int i, std::vector<hypro::Starset<Number>>& input_sets ) {
	for(const auto& set : input_sets) {
		hypro::vector_t<Number> center = set.center();
		hypro::matrix_t<Number> basis = set.generator();
		hypro::HPolytope<Number> polytope = set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = polytope.evaluate( -1.0 * dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

		// initialise lower and upper bounds
		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];


	}
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoid<Number>::approxHardSigmoid( int i, std::vector<hypro::Starset<Number>>& input_sets ) {

}
}