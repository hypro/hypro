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
		// if upper bound is less than minValue, we project the set on minValue
		if ( ub < minValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> biasVector = hypro::vector_t<Number>( center.rows() );
			biasVector( i ) = minValue;
			center = transformationMatrix * center + biasVector;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}
		// if lower bound is greater than maxValue, we project the set on maxValue
		if ( lb > maxValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> biasVector = hypro::vector_t<Number>( center.rows() );
			biasVector( i ) = maxValue;
			center = transformationMatrix * center + biasVector;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		if ( ( lb < minValue ) && ( minValue <= ub ) && ( ub <= maxValue ) ) {
			// split the star set into the part between minValue and maxValue
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constr_1 = basis_1.row( i ) * ( -1 );
			hypro::vector_t<Number> constr_2 = basis_1.row( i );
			hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_1 ), maxValue - center_1[i] );
			hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_2 ), minValue - center_1[i] );

			polytope_1 = polytope_1.intersectHalfspace( pos_1 );
			polytope_1 = polytope_1.intersectHalfspace( neg_1 );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			// split the star set into the part less than minValue
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constr_3 = basis_1.row( i );
			hypro::Halfspace<Number> neg_2 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_3 ), minValue - center_2[i] );
			polytope_2 = polytope_2.intersectHalfspace( neg_2 );

			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis_2 = transformationMatrix * basis_2;
			hypro::vector_t<Number> biasVector = hypro::vector_t<Number>( center.rows() );
			biasVector( i ) = minValue;
			center_2 = transformationMatrix * center_2 + biasVector;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			result.push_back( star_1 );
			result.push_back( star_2 );

			continue;
		}

		if ( ( ub > maxValue ) && ( minValue <= lb ) && ( lb <= maxValue ) ) {
			// split the star set into the part between minValue and maxValue
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constr_1 = basis_1.row( i ) * ( -1 );
			hypro::vector_t<Number> constr_2 = basis_1.row( i );
			hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_1 ), maxValue - center_1[i] );
			hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_2 ), minValue - center_1[i] );

			polytope_1 = polytope_1.intersectHalfspace( pos_1 );
			polytope_1 = polytope_1.intersectHalfspace( neg_1 );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			result.push_back( star_1 );

			// split the star set into the part that is greater than maxValue
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constr_3 = basis_1.row( i ) * ( -1 );
			hypro::Halfspace<Number> pos_2 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_3 ), maxValue - center_2[i] );
			polytope_2 = polytope_2.intersectHalfspace( pos_2 );

			hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_1( i, i ) = 0.0;
			basis_2 = transformationMatrix_1 * basis_2;
			hypro::vector_t<Number> biasVector_1 = hypro::vector_t<Number>( center.rows() );
			biasVector_1( i ) = maxValue;
			center_2 = transformationMatrix_1 * center_2 + biasVector_1;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			result.push_back( star_2 );

			continue;
		}
		// otherwise split the star set into the part between minValue and maxValue
		hypro::vector_t<Number> center_1 = center;
		hypro::matrix_t<Number> basis_1 = basis;
		hypro::HPolytope<Number> polytope_1 = polytope;

		hypro::vector_t<Number> constr_1 = basis_1.row( i ) * ( -1 );
		hypro::vector_t<Number> constr_2 = basis_1.row( i );
		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_1 ), maxValue - center_1[i] );
		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_2 ), minValue - center_1[i] );

		polytope_1 = polytope_1.intersectHalfspace( pos_1 );
		polytope_1 = polytope_1.intersectHalfspace( neg_1 );
		hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

		result.push_back( star_1 );

		// split the star set into the part that is greater than maxValue
		hypro::vector_t<Number> center_2 = center;
		hypro::matrix_t<Number> basis_2 = basis;
		hypro::HPolytope<Number> polytope_2 = polytope;

		hypro::vector_t<Number> constr_3 = basis_1.row( i ) * ( -1 );
		hypro::Halfspace<Number> pos_2 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_3 ), maxValue - center_2[i] );
		polytope_2 = polytope_2.intersectHalfspace( pos_2 );

		hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix_1( i, i ) = 0.0;
		basis_2 = transformationMatrix_1 * basis_2;
		hypro::vector_t<Number> biasVector_1 = hypro::vector_t<Number>( center.rows() );
		biasVector_1( i ) = maxValue;
		center_2 = transformationMatrix_1 * center_2 + biasVector_1;
		hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

		result.push_back( star_2 );

		// split the star set into the part less than minValue
		hypro::vector_t<Number> center_3 = center;
		hypro::matrix_t<Number> basis_3 = basis;
		hypro::HPolytope<Number> polytope_3 = polytope;

		hypro::vector_t<Number> constr_4 = basis_1.row( i );
		hypro::Halfspace<Number> neg_2 = hypro::Halfspace<Number>( hypro::Point<Number>( constr_4 ), minValue - center_3[i] );
		polytope_3 = polytope_3.intersectHalfspace( neg_2 );

		hypro::matrix_t<Number> transformationMatrix_2 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix_2( i, i ) = 0.0;
		basis_3 = transformationMatrix_2 * basis_3;
		hypro::vector_t<Number> biasVector_2 = hypro::vector_t<Number>( center.rows() );
		biasVector_2( i ) = minValue;
		center_3 = transformationMatrix_2 * center_3 + biasVector_2;
		hypro::Starset<Number> star_3 = hypro::Starset<Number>( center_3, basis_3, polytope_3 );

		result.push_back( star_3 );
	}
	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanh<Number>::approxHardTanh( int i, std::vector<hypro::Starset<Number>>& input_sets ) {
}

}  // namespace hypro