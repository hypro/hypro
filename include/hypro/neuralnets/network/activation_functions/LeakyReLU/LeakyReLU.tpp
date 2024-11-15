#include "LeakyReLU.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLU<Number>::exactLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope ) {
	std::vector<hypro::Starset<Number>> result;
	for ( auto& input_set : input_sets ) {
		auto center = input_set.center();
		auto basis = input_set.generator();
		auto polytope = input_set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = polytope.evaluate( -dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

		if (eval_low_result.errorCode == SOLUTION::FEAS) {
			// if lower bound is greater than ~0, we leave the star set as it is
			Number lb = -eval_low_result.supportValue + center[i];
			if ( lb >= -1e-8 ) {
				result.emplace_back( center, basis, polytope );
				continue;
			}
		}

		if (eval_high_result.errorCode == SOLUTION::FEAS) {
			// if upper bound is less than ~0, we project the star set on the negativeSlope
			Number ub = eval_high_result.supportValue + center[i];
			if ( ub <= +1e-8 ) {
				basis.row( i ) *= negativeSlope;
				center[i] *= negativeSlope;
				result.emplace_back( center, basis, polytope );
				continue;
			}
		}

		// otherwise split the star set into the part greater equal ~0
		hypro::HPolytope<Number> polytope_1 = polytope;

		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( -basis.row( i ) ), center[i] );
		polytope_1 = polytope_1.intersectHalfspace( pos_1 );
		result.emplace_back( center, basis, polytope_1 );

		// split the star set into the part less than ~0
		hypro::vector_t<Number> center_2 = center;
		hypro::matrix_t<Number> basis_2 = basis;
		hypro::HPolytope<Number> polytope_2 = polytope;

		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( basis_2.row( i ) ), -center_2[i] );
		polytope_2 = polytope_2.intersectHalfspace( neg_1 );
		basis_2.row(i) *= negativeSlope;
		center_2[i] *= negativeSlope;
		result.emplace_back( center_2, basis_2, polytope_2 );
	}

	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLU<Number>::approxLeakyReLU( int i, std::vector<hypro::Starset<Number>>& input_sets, float negativeSlope ) {
	std::vector<hypro::Starset<Number>> result;
	for ( auto& input_star : input_sets ) {
		auto center = input_star.center();
		auto basis = input_star.generator();
		auto shape = input_star.shape();
		auto limits = input_star.limits();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = input_star.constraints().evaluate( -dir_vect );
		auto eval_high_result = input_star.constraints().evaluate( dir_vect );

        bool feas_low = (eval_low_result.errorCode == SOLUTION::FEAS);
        bool feas_high = (eval_high_result.errorCode == SOLUTION::FEAS);
        bool unbounded_low = (eval_low_result.errorCode == SOLUTION::INFTY);
        bool unbounded_high = (eval_high_result.errorCode == SOLUTION::INFTY);

		Number lb = feas_low ? -eval_low_result.supportValue + center[i] : Number(0);
        Number ub = feas_high ? eval_high_result.supportValue + center[i] : Number(0);

		if ( feas_low && lb >= -1e-8 ) {
			result.emplace_back( center, shape, limits, basis );
			continue;
		}
		if ( feas_high && ub <= +1e-8 ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = negativeSlope;
			basis = transformationMatrix * basis;
			center = transformationMatrix * center;
			result.emplace_back( center, shape, limits, basis );
			continue;
		}

		if(feas_low && feas_high) {
			resizeShapeAndLimits(shape, limits, 3);

			// first constraint: x_(m+1) >= x_i * negativeSlope
			hypro::vector_t<Number> first_constraint = basis.row( i ) * negativeSlope;
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
			hypro::vector_t<Number> third_constraint = basis.row( i ) * ( -( ( ub - ( negativeSlope * lb ) ) / ( ub - lb ) ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = ( ( ub - negativeSlope * lb ) * center[i] + lb * ub * ( negativeSlope - 1 ) ) / ( ub - lb );
		}

		if(unbounded_low && feas_high) {
			resizeShapeAndLimits(shape, limits, 3);

			// first constraint: x_(m+1) >= x_i * negativeSlope
			hypro::vector_t<Number> first_constraint = basis.row( i ) * negativeSlope;
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

			// third constrain: x_(m+1) <= negativeSlope * x_i + ub * (1 - negativeSlope)
			hypro::vector_t<Number> third_constraint = -(negativeSlope * basis.row( i ));
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] =   negativeSlope * center[i] + ub * (1.0 - negativeSlope);
		}

		if(feas_low && unbounded_high) {
			resizeShapeAndLimits(shape, limits, 3);

			// first constraint: x_(m+1) >= x_i * negativeSlope
			hypro::vector_t<Number> first_constraint = basis.row( i ) * negativeSlope;
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

			// third constrain: x_(m+1) <= x_i + lb * (negativeSlope - 1)
			hypro::vector_t<Number> third_constraint = -basis.row( i );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = center[i] + lb * (negativeSlope - 1.0);
		}

		if(unbounded_low && unbounded_high) {
			resizeShapeAndLimits(shape, limits, 2);

			// first constraint: x_(m+1) >= x_i * negativeSlope
			hypro::vector_t<Number> first_constraint = basis.row( i ) * negativeSlope;
			first_constraint.conservativeResize( first_constraint.rows() + 1 );
			first_constraint[first_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = first_constraint;
			limits[limits.rows() - 2] = -( negativeSlope * center[i] );

			// second constraint: x_(m+1) >= x_i
			hypro::vector_t<Number> second_constraint = basis.row( i );
			second_constraint.conservativeResize( second_constraint.rows() + 1 );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 1 ) = second_constraint;
			limits[limits.rows() - 1] = -center[i];
		}


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

template <typename Number>
void LeakyReLU<Number>::resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows) {
    shape.conservativeResize(shape.rows() + rows, shape.cols() + 1);
    shape.col(shape.cols() - 1) = hypro::vector_t<Number>::Zero(shape.rows());
    limits.conservativeResize(limits.rows() + rows);
}

}  // namespace hypro