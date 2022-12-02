#include "HardTanh.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanh<Number>::exactHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets ) {
	auto result = std::vector<hypro::Starset<Number>>();

	for(const auto& set : input_sets) {
		hypro::vector_t<Number> center = set.center();
		hypro::matrix_t<Number> basis = set.generator();
		hypro::HPolytope<Number> polytope = set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row(i);

		auto eval_low_result = polytope.evaluate(-1.0 * dir_vect);
		auto eval_high_result = polytope.evaluate(dir_vect);

		// initialise lower and upper bounds
		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];

		// if lower bound is greater than -1 and upper bound less than 1, we leave the star set as it is
		if(lb >= -1 && ub <= +1) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}
		// if upper bound is less than -1, we project the set on -1
		if(ub <= -1) {

		}
		// if lower bound is greater than 1, we project the set on 1
		if(lb >= 1) {

		}

		//otherwise split the star set into positive part

		//split the star set into negative part9
	}
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanh<Number>::approxHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets ) {

}

} // namespace hypro