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
			transformationMatrix( i, i ) = negativeSlope;
			basis = transformationMatrix * basis;
			center = transformationMatrix * center;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		// otherwise split the star set into the part greater equal ~0
		hypro::vector_t<Number> center_1 = center;
		hypro::matrix_t<Number> basis_1 = basis;
		hypro::HPolytope<Number> polytope_1 = polytope;

		hypro::vector_t<Number> constraint_1 = basis_1.row( i ) * ( -1 );
		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), center_1[i] );
		polytope_1 = polytope_1.intersectHalfspace( pos_1 );
		hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

		result.push_back( star_1 );

		// split the star set into the part less than ~0
		hypro::vector_t<Number> center_2 = center;
		hypro::matrix_t<Number> basis_2 = basis;
		hypro::HPolytope<Number> polytope_2 = polytope;

		hypro::vector_t<Number> constraint_2 = basis_2.row( i );
		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), -center_2[i] );
		polytope_2 = polytope_2.intersectHalfspace( neg_1 );

		hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix( i, i ) = negativeSlope;
		basis_2 = transformationMatrix * basis_2;
		center_2 = transformationMatrix * center_2;
		hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

		result.push_back( star_2 );
	}

	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLU<Number>::approxLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope ) {
	std::vector<hypro::Starset<Number>> result = std::vector<hypro::Starset<Number>>();
	int k = input_sets.size();
	for ( int j = 0; j < k; j++ ) {
		hypro::Starset<Number> input_star = input_sets[j];

		hypro::vector_t<Number> center = input_star.center();
		hypro::matrix_t<Number> basis = input_star.generator();
		hypro::matrix_t<Number> shape = input_star.shape();
		hypro::vector_t<Number> limits = input_star.limits();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = input_star.constraints().evaluate( -1.0 * dir_vect );
		auto eval_high_result = input_star.constraints().evaluate( dir_vect );

		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];

		if ( lb >= -1e-8 ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}
		if ( ub <= +1e-8 ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = negativeSlope;
			basis = transformationMatrix * basis;
			center = transformationMatrix * center;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}

		// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
		shape.conservativeResize( shape.rows() + 3, shape.cols() + 1 );
		shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );
		limits.conservativeResize( limits.rows() + 3 );

		// first constraint: x_(m+1) >= x_i * negativeSlope
		hypro::vector_t<Number> first_constraint = basis.row( i );
		first_constraint = first_constraint * negativeSlope;
		first_constraint.conservativeResize( first_constraint.rows() + 1 );
		first_constraint[first_constraint.rows() - 1] = -1;
		shape.row( shape.rows() - 3 ) = first_constraint;
		limits[limits.rows() - 3] = -( negativeSlope * center[i] );

		// second constraint: x_(m+1) >= x_i
		hypro::vector_t<Number> second_constraint = basis.row( i );
		second_constraint.conservativeResize( second_constraint.rows() + 1 );
		second_constraint[second_constraint.rows() - 1] = -1;
		shape.row( shape.rows() - 2 ) = second_constraint;
		limits[limits.rows() - 2] = -center[i];

		// third constrain: x_(m+1) <= ( ( ub - ( negativeSlope * lb ) ) / ( ub - lb ) ) * x_i - ( ( ( ub * lb ) * ( negativeSlope - 1 ) ) / ( ub - lb ) )
		hypro::vector_t<Number> third_constraint = basis.row( i );
		third_constraint = third_constraint * ( -( ( ub - ( negativeSlope * lb ) ) / ( ub - lb ) ) );
		third_constraint.conservativeResize( third_constraint.rows() + 1 );
		third_constraint( third_constraint.rows() - 1 ) = 1;
		shape.row( shape.rows() - 1 ) = third_constraint;
		limits[limits.rows() - 1] = ( ( ub - negativeSlope * lb ) * center[i] + lb * ub * ( negativeSlope - 1 ) ) / ( ub - lb );

		hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix( i, i ) = 0.0;
		basis = transformationMatrix * basis;
		center = transformationMatrix * center;

		// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( i, basis.cols() - 1 ) = 1;

		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
		result.push_back( res_star );
	}
	return result;
}

}  // namespace hypro