#include "StepFunction.h"

namespace hypro {
template <typename Number>
std::vector<hypro::Starset<Number>> StepFunction<Number>::exactStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, float value, float minValue, float maxValue ) {
	auto result = std::vector<hypro::Starset<Number>>();

	for ( const auto& set : input_sets ) {
		hypro::vector_t<Number> center = set.center();
		hypro::matrix_t<Number> basis = set.generator();
		hypro::HPolytope<Number> polytope = set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = polytope.evaluate( -1.0 * dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

		// initialise lower and upper bounds
		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];

		// if upper bound is less than step value, we project the input on minValue
		if ( ub < value ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = minValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		// if lower bound is greater than step value, we project the input on maxValue
		if ( lb >= value ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = maxValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		// Split the star input into the part that is greater than step value
		hypro::vector_t<Number> center_1 = center;
		hypro::matrix_t<Number> basis_1 = basis;
		hypro::HPolytope<Number> polytope_1 = polytope;

		hypro::vector_t<Number> constraint_1 = basis_1.row( i ) * ( -1 );
		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), center_1[i] - value );
		polytope_1 = polytope_1.intersectHalfspace( pos_1 );

		hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix_1( i, i ) = 0.0;
		basis_1 = transformationMatrix_1 * basis_1;
		center_1( i ) = maxValue;
		hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

		// Split the star input into the part that is less than step value
		hypro::vector_t<Number> center_2 = center;
		hypro::matrix_t<Number> basis_2 = basis;
		hypro::HPolytope<Number> polytope_2 = polytope;

		hypro::vector_t<Number> constraint_2 = basis_2.row( i );
		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), value - center_2[i] );
		polytope_2 = polytope_2.intersectHalfspace( neg_1 );

		hypro::matrix_t<Number> transformationMatrix_2 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix_2( i, i ) = 0.0;
		basis_2 = transformationMatrix_2 * basis_2;
		center_2( i ) = minValue;
		hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

		result.push_back( star_1 );
		result.push_back( star_2 );
	}
	return result;
}
}  // namespace hypro