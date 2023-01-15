#include "HardTanh.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanh<Number>::exactHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets, float minValue, float maxValue ) {
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

		// if lower bound is greater than minValue and upper bound less than maxValue, we leave the star set as it is
		if ( ( lb >= minValue ) && ( ub <= maxValue ) ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}
		// if upper bound is less than minValue, we project the input on minValue
		if ( ub < minValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;

			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = minValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, basis, polytope );
			result.push_back( res_star );
			continue;
		}
		// if lowe bound is greater than maxValue, we project the input on maxValue
		if( lb > maxValue){
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;

			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = maxValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		if ( ( lb < minValue ) && ( ub <= maxValue ) ) {
			// split the star input into the part that is greater than minValue
			// this part remain as it is
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constraint_1 = basis_1.row( i ) * ( -1 );
			hypro::Halfspace<Number> remaining = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), ( center_1[i] - minValue ) );
			polytope_1 = polytope_1.intersectHalfspace( remaining );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			// split the star input into the part that is less than minValue
			// this part is projected on minValue
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constraint_2 = basis_2.row( i );
			hypro::Halfspace<Number> projected_min = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), ( minValue - center_2[i] ) );
			polytope_2 = polytope_2.intersectHalfspace( projected_min );

			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis_2 = transformationMatrix * basis_2;
			center_2( i ) = minValue;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			result.push_back( star_1 );
			result.push_back( star_2 );
			continue;
		}

		if ( ( lb >= minValue ) && ( lb <= maxValue ) && ( ub > maxValue ) ) {
			// split the star input into the part that is less than maxValue
			// this part remain as it is
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constraint_1 = basis_1.row( i );
			hypro::Halfspace<Number> remaining = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), ( maxValue - center_1[i] ) );
			polytope_1 = polytope_1.intersectHalfspace( remaining );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			// split the star input into the part that is greater than maxValue
			// thia part is projected on maxValue
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constraint_2 = basis_2.row( i ) * ( -1 );
			hypro::Halfspace<Number> projected_max = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), ( center_2[i] - maxValue ) );
			polytope_2 = polytope_2.intersectHalfspace( projected_max );

			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis_2 = transformationMatrix * basis_2;
			center_2( i ) = maxValue;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			result.push_back( star_1 );
			result.push_back( star_2 );
			continue;
		}

		if ( ( lb < -1 ) && ( ub > 1 ) ) {
			// split the star input into the part between minValue and maxValue
			// this part remain as it is
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constraint_1 = basis_1.row( i );
			hypro::vector_t<Number> constraint_2 = basis_1.row( i ) * ( -1 );
			hypro::Halfspace<Number> remaining_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), maxValue - center_1[i] );
			hypro::Halfspace<Number> remainign_2 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), center_1[i] - minValue );

			polytope_1 = polytope_1.intersectHalfspace( remaining_1 );
			polytope_1 = polytope_1.intersectHalfspace( remainign_2 );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			// split the star input into the part less than minValue
			// this part is projected on minValue
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constraint_3 = basis_2.row( i );
			hypro::Halfspace<Number> projected_min = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_3 ), minValue - center_2[i] );
			polytope_2 = polytope_2.intersectHalfspace( projected_min );


			hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_1( i, i ) = 0.0;
			basis_2 = transformationMatrix_1 * basis_2;
			center_2( i ) = minValue;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			// split the star input into the part that is greater than maxValue
			// this part is projected on maxValue
			hypro::vector_t<Number> center_3 = center;
			hypro::matrix_t<Number> basis_3 = basis;
			hypro::HPolytope<Number> polytope_3 = polytope;

			hypro::vector_t<Number> constraint_4 = basis_1.row( i ) * ( -1 );
			hypro::Halfspace<Number> projected_max = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_4 ), center_3[i] - maxValue );
			polytope_3 = polytope_3.intersectHalfspace( projected_max );

			hypro::matrix_t<Number> transformationMatrix_2 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_2( i, i ) = 0.0;
			basis_3 = transformationMatrix_2 * basis_3;
			center_3( i ) = maxValue;
			hypro::Starset<Number> star_3 = hypro::Starset<Number>( center_3, basis_3, polytope_3 );

			result.push_back( star_1 );
			result.push_back( star_2 );
			result.push_back( star_3 );
		}
	}
	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanh<Number>::approxHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets ) {
}

}  // namespace hypro