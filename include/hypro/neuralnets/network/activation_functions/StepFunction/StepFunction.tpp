#include "StepFunction.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> StepFunction<Number>::exactStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, Number value, Number minValue, Number maxValue ) {
	auto result = std::vector<hypro::Starset<Number>>();

	for ( const auto& set : input_sets ) {
		auto center = set.center();
		auto basis = set.generator();
		auto polytope = set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = polytope.evaluate( -dir_vect );
		auto eval_high_result = polytope.evaluate( dir_vect );

		// initialise lower and upper bounds
		Number lb = -eval_low_result.supportValue + center[i];
		Number ub = eval_high_result.supportValue + center[i];

		// if lower bound is greater than step value, we project the input on maxValue
		if ( eval_low_result.errorCode == SOLUTION::FEAS && lb >= value ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = maxValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, basis, polytope );
			result.push_back( res_star );
			continue;
		}

		// if upper bound is less than step value, we project the input on minValue
		if ( eval_high_result.errorCode == SOLUTION::FEAS && ub < value ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = minValue;
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

template <typename Number>
std::vector<hypro::Starset<Number>> StepFunction<Number>::approxStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, Number value, Number minValue, Number maxValue ) {
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

		// if upper bound is less than step value, we project the input on minValue
		// if minValue and maxValue are the same, we can use the exact method without any splits
		if ( ub < value || maxValue == minValue ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			hypro::vector_t<Number> center_1 = center;
			center_1( i ) = minValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, shape, limits, basis );
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
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center_1, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}

		//if the uppper bound is the only value mapped to maxValue
		if (ub == value){
			// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
			shape.conservativeResize( shape.rows() + 2, shape.cols() + 1 );
			shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );	// fill up last column with zeros
			limits.conservativeResize( limits.rows() + 2 );
			
			// first constraint: x_(m+1) (minValue < maxValue ? (>=) : (<=)) minValue
			hypro::vector_t<Number> constr1 = hypro::vector_t<Number>::Zero( shape.cols() );
			constr1[constr1.rows() - 1] = (minValue < maxValue) ? -1 : 1;
			shape.row( shape.rows() - 2 ) = constr1;
			limits[limits.rows() - 2] = minValue * ((minValue < maxValue) ? -1 : 1);
			
			//second constraint: x_(m+1) <= (((maxValue - minValue) * x_i + value * minValue - lb * maxValue ) / (value - lb))	
			hypro::vector_t<Number> constr2 = basis.row( i ) * ((maxValue - minValue) /  (value - lb)) * ((minValue < maxValue) ? -1 : 1);
			constr2.conservativeResize( constr2.rows() + 1 );
			constr2( constr2.rows() - 1 ) = (minValue < maxValue) ? -1 : 1;
			shape.row( shape.rows() - 1 ) = constr2;
			limits[limits.rows() - 1] = (((maxValue - minValue) * center[i] + value * minValue - lb * maxValue ) / (value - lb)) * ((minValue < maxValue) ? -1 : 1);	
			
			// Third implicit constraint (x_i <= value)

			// Ensure x_(m+1) is the only influence on the values of dimension i of the new starset
			hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			I_i( i, i ) = 0.0;
			basis = I_i * basis;
			center = I_i * center;
			
			basis.conservativeResize( basis.rows(), basis.cols() + 1 );
			basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
			basis( i, basis.cols() - 1 ) = 1;

			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}

		// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
		shape.conservativeResize( shape.rows() + 4, shape.cols() + 1 );
		shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );	// fill up last column with zeros
		limits.conservativeResize( limits.rows() + 4 );
		
		// first constraint: x_(m+1) >= minValue
		hypro::vector_t<Number> constr1 = hypro::vector_t<Number>::Zero( shape.cols() );
		constr1[constr1.rows() - 1] = (minValue < maxValue) ? -1 : 1;
		shape.row( shape.rows() - 4 ) = constr1;
		limits[limits.rows() - 4] = minValue * ((minValue < maxValue) ? -1 : 1);
		
		// second constraint: x_(m+1) <= maxValue
		hypro::vector_t<Number> constr2 = hypro::vector_t<Number>::Zero( shape.cols() );
		constr2[constr2.rows() - 1] = (minValue < maxValue) ? 1 : -1;
		shape.row( shape.rows() - 3 ) = constr2;
		limits[limits.rows() - 3] = maxValue * ((minValue < maxValue) ? 1 : -1);
		
		// third constraint: x_(m+1) >= (((maxValue - minValue) * x_i + ub * minValue - value * maxValue ) / (ub - value))
		hypro::vector_t<Number> constr3 = basis.row( i ) * ((maxValue - minValue) / (ub - value)) * ((minValue < maxValue) ? 1 : -1);
		constr3.conservativeResize( constr3.rows() + 1 );
		constr3( constr3.rows() - 1 ) = (minValue < maxValue) ? -1 : 1;
		shape.row( shape.rows() - 2 ) = constr3;
		limits[limits.rows() - 2] = (((maxValue - minValue) * center[i] + ub * minValue - value * maxValue ) / (ub - value)) * ((minValue < maxValue) ? -1 : 1);

		//fourth constraint: x_(m+1) <= (((maxValue - minValue) * x_i + value * minValue - lb * maxValue ) / (value - lb))	
		hypro::vector_t<Number> constr4 = basis.row( i ) * ((maxValue - minValue) /  (value - lb)) * ((minValue < maxValue) ? -1 : 1);
		constr4.conservativeResize( constr4.rows() + 1 );
		constr4( constr4.rows() - 1 ) = (minValue < maxValue) ? 1 : -1;
		shape.row( shape.rows() - 1 ) = constr4;
		limits[limits.rows() - 1] = (((maxValue - minValue) * center[i] + value * minValue - lb * maxValue ) / (value - lb)) * ((minValue < maxValue) ? 1 : -1);	
		

		// Ensure x_(m+1) is the only influence on the values of dimension i of the new starset
		hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		I_i( i, i ) = 0.0;
		basis = I_i * basis;
		center = I_i * center;
		
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( i, basis.cols() - 1 ) = 1;

		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
		result.push_back( res_star );
	}

	return result;
}
}  // namespace hypro