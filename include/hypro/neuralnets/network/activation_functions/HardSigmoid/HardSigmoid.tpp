#include "HardSigmoid.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoid<Number>::exactHardSigmoid( int i, std::vector<hypro::Starset<Number>>& input_sets, float minValue, float maxValue ) {
	auto result = std::vector<hypro::Starset<Number>>();
	for ( const auto& set : input_sets ) {
		hypro::vector_t<Number> center = set.center();
		hypro::matrix_t<Number> basis = set.generator();
		hypro::HPolytope<Number> polytope = set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = polytope.evaluate( -dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

		if ( eval_low_result.errorCode == SOLUTION::INFEAS ||
			 eval_low_result.errorCode == SOLUTION::UNKNOWN ||
			 eval_high_result.errorCode == SOLUTION::INFEAS ||
			 eval_high_result.errorCode == SOLUTION::UNKNOWN ) {
			continue;
		}

		// initialise lower and upper bounds
		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];
		lb = ( eval_low_result.errorCode == SOLUTION::INFTY ) ? Number( INT_MIN ) : lb;
		ub = ( eval_high_result.errorCode == SOLUTION::INFTY ) ? Number( INT_MAX ) : lb;

		// if lower bound is greater than minValue and upper bound less than maxValue, this part corresponds to the function: ( 1 / ( maxValue - minValue ) ) x + ( minValue / ( minValue - maxValue ) )
		if ( ( lb > minValue ) && ( ub < maxValue ) ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = ( 1 / ( maxValue - minValue ) );
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = ( minValue / ( minValue - maxValue ) );
			result.emplace_back( center_1, basis, polytope );
			continue;
		}

		// if upper bound is less than minValue, we project the input on 0
		if ( ub <= minValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			center = transformationMatrix * center;
			result.emplace_back( center, basis, polytope );
			continue;
		}
		// if lower bound is greater than maxValue, we project the input on maxValue
		if ( lb >= maxValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = 1.0;
			result.emplace_back( center_1, basis, polytope );
			continue;
		}
		if ( ( lb <= minValue ) && ( ub < maxValue ) ) {
			// split the star input into the part that is greater than minValue
			// this part corresponds to the function: ( 1 / ( maxValue - minValue ) ) x + ( minValue / ( minValue - maxValue ) )
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constraint_1 = basis_1.row( i ) * ( -1 );
			hypro::Halfspace<Number> remaining = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), ( center_1[i] - minValue ) );
			polytope_1 = polytope_1.intersectHalfspace( remaining );

			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = ( 1 / ( maxValue - minValue ) );
			basis_1 = transformationMatrix * basis_1;
			center_1( i ) = ( minValue / ( minValue - maxValue ) );
			result.emplace_back( center_1, basis_1, polytope_1 );

			// split the star input into the part that is less than minValue
			// this part is projected on 0
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constraint_2 = basis_2.row( i );
			hypro::Halfspace<Number> projected_min = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), ( minValue - center_2[i] ) );
			polytope_2 = polytope_2.intersectHalfspace( projected_min );

			hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_1( i, i ) = 0.0;
			basis_2 = transformationMatrix_1 * basis_2;
			center_2 = transformationMatrix_1 * center_2;
			result.emplace_back( center_2, basis_2, polytope_2 );
			continue;
		}

		if ( ( lb > minValue ) && ( lb < maxValue ) && ( ub >= maxValue ) ) {
			// split the star input into the part that is less than maxValue
			// this part corresponds to the function: ( 1 / ( maxValue - minValue ) ) x + ( minValue / ( minValue - maxValue ) )
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constraint_1 = basis_1.row( i );
			hypro::Halfspace<Number> remaining = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), ( maxValue - center_1[i] ) );
			polytope_1 = polytope_1.intersectHalfspace( remaining );

			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = ( 1 / ( maxValue - minValue ) );
			basis_1 = transformationMatrix * basis_1;
			center_1( i ) = ( minValue / ( minValue - maxValue ) );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			// split the star input into the part that is greater than maxValue
			// thia part is projected on 1
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constraint_2 = basis_2.row( i ) * ( -1 );
			hypro::Halfspace<Number> projected_max = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), ( center_2[i] - maxValue ) );
			polytope_2 = polytope_2.intersectHalfspace( projected_max );

			hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_1( i, i ) = 0.0;
			basis_2 = transformationMatrix_1 * basis_2;
			center_2( i ) = 1.0;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			result.push_back( star_1 );
			result.push_back( star_2 );
			continue;
		}

		if ( ( lb <= minValue ) && ( ub >= maxValue ) ) {
			// split the star input into the part between minValue and maxValue
			// this part corresponds to the function: ( 1 / ( maxValue - minValue ) ) x + ( minValue / ( minValue - maxValue ) )
			hypro::vector_t<Number> center_1 = center;
			hypro::matrix_t<Number> basis_1 = basis;
			hypro::HPolytope<Number> polytope_1 = polytope;

			hypro::vector_t<Number> constraint_1 = basis_1.row( i );
			hypro::vector_t<Number> constraint_2 = basis_1.row( i ) * ( -1 );
			hypro::Halfspace<Number> remaining_1 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_1 ), maxValue - center_1[i] );
			hypro::Halfspace<Number> remaining_2 = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_2 ), center_1[i] - minValue );
			polytope_1 = polytope_1.intersectHalfspace( remaining_1 );
			polytope_1 = polytope_1.intersectHalfspace( remaining_2 );

			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = ( 1 / ( maxValue - minValue ) );
			basis_1 = transformationMatrix * basis_1;
			center_1( i ) = ( minValue / ( minValue - maxValue ) );
			hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, polytope_1 );

			// split the star input into the part that is greater than maxValue
			// this part is projected on 1
			hypro::vector_t<Number> center_2 = center;
			hypro::matrix_t<Number> basis_2 = basis;
			hypro::HPolytope<Number> polytope_2 = polytope;

			hypro::vector_t<Number> constraint_4 = basis_2.row( i ) * ( -1 );
			hypro::Halfspace<Number> projected_max = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_4 ), center_2[i] - maxValue );
			polytope_2 = polytope_2.intersectHalfspace( projected_max );

			hypro::matrix_t<Number> transformationMatrix_2 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_2( i, i ) = 0.0;
			basis_2 = transformationMatrix_2 * basis_2;
			center_2( i ) = 1.0;
			hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, polytope_2 );

			// split the star input into the part less than minValue
			// this part is projected on 0
			hypro::vector_t<Number> center_3 = center;
			hypro::matrix_t<Number> basis_3 = basis;
			hypro::HPolytope<Number> polytope_3 = polytope;

			hypro::vector_t<Number> constraint_3 = basis_3.row( i );
			hypro::Halfspace<Number> projected_min = hypro::Halfspace<Number>( hypro::Point<Number>( constraint_3 ), minValue - center_3[i] );
			polytope_3 = polytope_3.intersectHalfspace( projected_min );

			hypro::matrix_t<Number> transformationMatrix_1 = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix_1( i, i ) = 0.0;
			basis_3 = transformationMatrix_1 * basis_3;
			center_3 = transformationMatrix_1 * center_3;
			hypro::Starset<Number> star_3 = hypro::Starset<Number>( center_3, basis_3, polytope_3 );

			result.push_back( star_1 );
			result.push_back( star_2 );
			result.push_back( star_3 );
		}
	}
	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoid<Number>::approxHardSigmoid( int i, std::vector<hypro::Starset<Number>>& input_sets, float minValue, float maxValue ) {
	std::vector<hypro::Starset<Number>> result;
	for ( auto& input_star : input_sets ) {
		auto center = input_star.center();
		auto basis = input_star.generator();
		auto shape = input_star.shape();
		auto limits = input_star.limits();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = input_star.constraints().evaluate( -dir_vect );
		auto eval_high_result = input_star.constraints().evaluate( dir_vect );

		if ( eval_low_result.errorCode == SOLUTION::INFEAS ||
			 eval_low_result.errorCode == SOLUTION::UNKNOWN ||
			 eval_high_result.errorCode == SOLUTION::INFEAS ||
			 eval_high_result.errorCode == SOLUTION::UNKNOWN ) {
			continue;
		}

		bool feas_low = ( eval_low_result.errorCode == SOLUTION::FEAS );
		bool feas_high = ( eval_high_result.errorCode == SOLUTION::FEAS );
		bool unbounded_low = ( eval_low_result.errorCode == SOLUTION::INFTY );
		bool unbounded_high = ( eval_high_result.errorCode == SOLUTION::INFTY );

		// initialise lower and upper bounds
		Number lb = feas_low ? -eval_low_result.supportValue + center[i] : Number( 0 );
		Number ub = feas_high ? eval_high_result.supportValue + center[i] : Number( 0 );

		//  if lower bound is greater than minValue and upper bound less than maxValue, this part corresponds to the function: ( 1 / ( maxValue - minValue ) ) x + ( minValue / ( minValue - maxValue ) )
		if ( ( lb > minValue ) && ( ub < maxValue ) ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = ( 1 / ( maxValue - minValue ) );
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = ( minValue / ( minValue - maxValue ) );
			result.emplace_back( center_1, shape, limits, basis );
			continue;
		}
		// if upper bound is less than minValue, we project the input on 0
		if ( ub <= minValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			center = transformationMatrix * center;
			result.emplace_back( center, shape, limits, basis );
			continue;
		}
		// if lower bound is greater than maxValue, we project the input on 1
		if ( lb >= maxValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = 1.0;
			result.emplace_back( center_1, shape, limits, basis );
			continue;
		}
		if ( feas_low && feas_high && ( lb <= minValue ) && ( ub < maxValue ) ) {
			resizeShapeAndLimits( shape, limits, 3 );

			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = first_constraint;
			limits[limits.rows() - 3] = 0.0;

			// second constraint: x_(m+1) >= ( 1 / (maxValue - minValue ) ) * x_i - ( minValue / ( maxValue - minValue ) )
			hypro::vector_t<Number> second_constraint = basis.row( i );
			second_constraint = second_constraint * ( 1 / ( maxValue - minValue ) );
			second_constraint.conservativeResize( second_constraint.rows() + 1 );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = second_constraint;
			limits[limits.rows() - 2] = -( ( center[i] - minValue ) / ( maxValue - minValue ) );

			// third constrain: x_(m+1) <= ((ub - minValue)/(maxValue - minValue)) * ((x_i - lb)/(ub - lb))
			hypro::vector_t<Number> third_constraint = basis.row( i );
			third_constraint = third_constraint * ( -( ( ub - minValue ) / ( maxValue - minValue ) ) * ( 1 / ( ub - lb ) ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = ( ( ( ub - minValue ) / ( maxValue - minValue ) ) * ( ( center[i] - lb ) / ( ub - lb ) ) );
		}

		if ( feas_low && feas_high && ( lb > minValue ) && ( lb < maxValue ) && ( ub >= maxValue ) ) {
			resizeShapeAndLimits( shape, limits, 3 );

			// first constraint: x_(m+1) <= 1
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 3 ) = first_constraint;
			limits[limits.rows() - 3] = 1.0;

			// second constraint: x_(m+1) <= ( 1 / (maxValue - minValue ) ) * x_i - ( minValue / ( maxValue - minValue ) )
			hypro::vector_t<Number> second_constraint = basis.row( i );
			second_constraint = second_constraint * ( -( 1 / ( maxValue - minValue ) ) );
			second_constraint.conservativeResize( second_constraint.rows() + 1 );
			second_constraint[second_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 2 ) = second_constraint;
			limits[limits.rows() - 2] = ( center[i] - minValue ) / ( maxValue - minValue );

			// third constraint: x_(m+1) >= 1 + ((maxValue - lb)/(maxValue - minValue)) * ((x_i - ub)/(ub - lb))
			hypro::vector_t<Number> third_constraint = basis.row( i );
			third_constraint = third_constraint * ( ( maxValue - lb ) / ( maxValue - minValue ) ) * ( 1 / ( ub - lb ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = -1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = ( ( maxValue - lb ) / ( maxValue - minValue ) ) * ( ( ub - center[i] ) / ( ub - lb ) ) - 1;
		}

		if ( feas_low && feas_high && ( lb <= minValue ) && ( ub >= maxValue ) ) {
			resizeShapeAndLimits( shape, limits, 4 );
			// first constraint: x_(m+1) <= 1
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 4 ) = first_constraint;
			limits[limits.rows() - 4] = 1.0;

			// second constraint: x_(m+1) >= 0
			hypro::vector_t<Number> second_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = second_constraint;
			limits[limits.rows() - 3] = 0.0;

			// third constraint: x_(m+1) <= ( 1 / ( maxValue - lb ) ) * x_i - ( lb / ( maxValue - lb ) )
			hypro::vector_t<Number> third_constraint = basis.row( i );
			third_constraint = third_constraint * ( -( 1 / ( maxValue - lb ) ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = 1;
			shape.row( shape.rows() - 2 ) = third_constraint;
			limits[limits.rows() - 2] = ( center[i] - lb ) / ( maxValue - lb );

			// fourth constraint: x_(m+1) >= ( 1 / ( ub - minValue ) ) * x_i - ( minValue / ( ub - minValue ) )
			hypro::vector_t<Number> fourth_constraint = basis.row( i );
			fourth_constraint = fourth_constraint * ( 1 / ( ub - minValue ) );
			fourth_constraint.conservativeResize( fourth_constraint.rows() + 1 );
			fourth_constraint( fourth_constraint.rows() - 1 ) = -1;
			shape.row( shape.rows() - 1 ) = fourth_constraint;
			limits[limits.rows() - 1] = -( ( center[i] - minValue ) / ( ub - minValue ) );
		}

		// unbounded cases
		if ( unbounded_low && ( minValue <= ub && ub <= maxValue ) ) {
			resizeShapeAndLimits( shape, limits, 3 );

			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = first_constraint;
			limits[limits.rows() - 3] = 0.0;

			// second constraint: x_(m+1) >= ( 1 / (maxValue - minValue ) ) * x_i - ( minValue / ( maxValue - minValue ) )
			hypro::vector_t<Number> second_constraint = basis.row( i );
			second_constraint = second_constraint * ( 1 / ( maxValue - minValue ) );
			second_constraint.conservativeResize( second_constraint.rows() + 1 );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = second_constraint;
			limits[limits.rows() - 2] = -( ( center[i] - minValue ) / ( maxValue - minValue ) );

			// third constraint: x_(m+1) <= ub
			hypro::vector_t<Number> third_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			third_constraint[third_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = ub;
		}

		if ( unbounded_low && ub > maxValue ) {
			resizeShapeAndLimits( shape, limits, 3 );

			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = first_constraint;
			limits[limits.rows() - 3] = 0.0;

			// second constraint: x_(m+1) <= 1
			hypro::vector_t<Number> second_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			second_constraint[second_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 2 ) = second_constraint;
			limits[limits.rows() - 2] = 1.0;

			// third constraint: x_(m+1) >= ( 1 / ( ub - minValue ) ) * x_i - ( minValue / ( ub - minValue ) )
			hypro::vector_t<Number> third_constraint = basis.row( i );
			third_constraint = third_constraint * ( 1 / ( ub - minValue ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = -1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = -( ( center[i] - minValue ) / ( ub - minValue ) );
		}

		if ( ( minValue <= lb && lb <= maxValue ) && unbounded_high ) {
			resizeShapeAndLimits( shape, limits, 3 );

			// first constraint: x_(m+1) <= 1
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 3 ) = first_constraint;
			limits[limits.rows() - 3] = 1.0;

			// second constraint: x_(m+1) >= 0
			hypro::vector_t<Number> second_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = second_constraint;
			limits[limits.rows() - 2] = lb;

			// third constraint: x_(m+1) <= ( 1 / (maxValue - minValue ) ) * x_i - ( minValue / ( maxValue - minValue ) )
			hypro::vector_t<Number> third_constraint = basis.row( i );
			third_constraint = third_constraint * ( -( 1 / ( maxValue - minValue ) ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint[third_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = ( center[i] - minValue ) / ( maxValue - minValue );
		}

		if ( lb < minValue && unbounded_high ) {
			resizeShapeAndLimits( shape, limits, 3 );

			// first constraint: x_(m+1) <= 1
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 3 ) = first_constraint;
			limits[limits.rows() - 3] = 1.0;

			// second constraint: x_(m+1) >= 0
			hypro::vector_t<Number> second_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = second_constraint;
			limits[limits.rows() - 2] = 0.0;

			// third constraint: x_(m+1) <= ( 1 / ( maxValue - lb ) ) * x_i - ( lb / ( maxValue - lb ) )
			hypro::vector_t<Number> third_constraint = basis.row( i );
			third_constraint = third_constraint * ( -( 1 / ( maxValue - lb ) ) );
			third_constraint.conservativeResize( third_constraint.rows() + 1 );
			third_constraint( third_constraint.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = third_constraint;
			limits[limits.rows() - 1] = ( center[i] - lb ) / ( maxValue - lb );
		}

		if ( unbounded_low && unbounded_high ) {
			resizeShapeAndLimits( shape, limits, 2 );
			// first constraint: x_(m+1) <= 1
			hypro::vector_t<Number> first_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			first_constraint[first_constraint.rows() - 1] = 1;
			shape.row( shape.rows() - 2 ) = first_constraint;
			limits[limits.rows() - 2] = 1.0;

			// second constraint: x_(m+1) >= 0
			hypro::vector_t<Number> second_constraint = hypro::vector_t<Number>::Zero( shape.cols() );
			second_constraint[second_constraint.rows() - 1] = -1;
			shape.row( shape.rows() - 1 ) = second_constraint;
			limits[limits.rows() - 1] = 0.0;
		}

		hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		transformationMatrix( i, i ) = 0.0;
		basis = transformationMatrix * basis;
		center = transformationMatrix * center;

		// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( i, basis.cols() - 1 ) = 1;

		result.emplace_back( center, shape, limits, basis );
	}
	return result;
}

template <typename Number>
void HardSigmoid<Number>::resizeShapeAndLimits( hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows ) {
	shape.conservativeResize( shape.rows() + rows, shape.cols() + 1 );
	shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );
	limits.conservativeResize( limits.rows() + rows );
}

}  // namespace hypro