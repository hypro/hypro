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
std::vector<hypro::Starset<Number>> LeakyReLU<Number>::approxLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope) {
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
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> biasVector = hypro::vector_t<Number>(center.rows());
			biasVector(i) = negativeSlope;
			center = transformationMatrix * center + biasVector;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}

		// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
		shape.conservativeResize( shape.rows() + 3, shape.cols() + 1 );
		shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );
		limits.conservativeResize( limits.rows() + 3 );

		//first constraint: x_(m+1) >= x_i * negativeSlope
		hypro::vector_t<Number> first_constr = basis.row( i );
		first_constr = first_constr * negativeSlope;
		first_constr.conservativeResize( first_constr.rows() + 1 );
		first_constr[first_constr.rows() - 1] = -1;
		shape.row( shape.rows() - 3 ) = first_constr;
		limits[limits.rows() - 3] = -( center[i] * negativeSlope);

		// second constraint: x_(m+1) >= x_i
		hypro::vector_t<Number> second_constr = basis.row( i );
		second_constr.conservativeResize( second_constr.rows() + 1 );
		second_constr[second_constr.rows() - 1] = -1;
		shape.row( shape.rows() - 2 ) = second_constr;
		limits[limits.rows() - 2] = -center[i];

		// third constrain: x_(m+1) <= ( (ub - negativeSlope) * (x_i - lb) / (ub - lb) ) + negativeSlope * lb
		hypro::vector_t<Number> third_constr = basis.row( i );
		third_constr = third_constr * ( -( ( ub - ( negativeSlope * lb ) ) / ( ub - lb ) ) );
		third_constr.conservativeResize( third_constr.rows() + 1 );
		third_constr( third_constr.rows() - 1 ) = 1;
		shape.row( shape.rows() - 1 ) = third_constr;
		limits[limits.rows() - 1] = ( ub * ( center[i] + negativeSlope - lb ) ) / ( ub - lb );

		// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( i, basis.cols() - 1 ) = 1;

		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
		result.push_back( res_star );
	}

	return result;
}

} // namespace hypro