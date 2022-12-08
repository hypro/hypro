#include "LeakyReLU.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLU<Number>::exactLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope ) {
	std::vector<hypro::Starset<Number>> result = std::vector<hypro::Starset<Number>>();

	int k = input_sets.size();
	for ( int j = 0; j < k; j++ ) {
		hypro::vector_t<Number> center = input_sets[j].center();
		hypro::matrix_t<Number> basis = input_sets[j].generator();
		hypro::HPolytope<Number> polytope = input_sets[j].constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = polytope.evaluate( -1.0 * dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];

		// if lower bound is greater than ~0, we leave the star set as it is
		if ( lb >= -1e-8 ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		// if upper bound is less than ~0, we project the star set on the negativeSlope
		if ( ub <= +1e-8 ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> biasVector = hypro::vector_t<Number>(center.rows());
			biasVector(i) = negativeSlope;
			center = transformationMatrix * center + biasVector;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		// otherwise split the star set into the part greater equal ~0
		hypro::vector_t<Number> center_1 = center;
		hypro::matrix_t<Number> basis_1 = basis;
		hypro::HPolytope<Number> polytope_1 = polytope;

		hypro::vector_t<Number> constr_1 = basis_1.row( i ) * ( -1 );
		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_1 ), center_1[i] );
		polytope_1 = polytope_1.intersectHalfspace( pos_1 );
		hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

		result.push_back( star_1 );

		//split the star set into the part less than ~0
		hypro::vector_t<Number> center_2 = center;
		hypro::matrix_t<Number> basis_2 = basis;
		hypro::HPolytope<Number> polytope_2 = polytope;

		hypro::vector_t<Number> constr_2 = basis_2.row( i );
		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_2 ), -center_2[i] );
		polytope_2 = polytope_2.intersectHalfspace( neg_1 );

		hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix( i, i ) = 0.0;
		basis_2 = transformationMatrix * basis_2;
		hypro::vector_t<Number> biasVector = hypro::vector_t<Number>(center.rows());
		biasVector(i) = negativeSlope;
		center_2 = transformationMatrix * center_2 + biasVector;
		hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

		result.push_back( star_2 );
	}

	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLU<Number>::approxLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) {

}

} // namespace hypro