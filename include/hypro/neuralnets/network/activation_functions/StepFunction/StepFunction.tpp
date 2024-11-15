#include "StepFunction.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> StepFunction<Number>::exactStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, float value, float minValue, float maxValue ) {
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
std::vector<hypro::Starset<Number>> StepFunction<Number>::approxStepFunction( int i, std::vector<hypro::Starset<Number>>& input_sets, float value, float minValue, float maxValue ) {
	auto result = std::vector<hypro::Starset<Number>>();

	for ( auto& input_star : input_sets ) {
		auto center = input_star.center();
		auto basis = input_star.generator();
		auto shape = input_star.shape();
		auto limits = input_star.limits();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = input_star.constraints().evaluate( -dir_vect );
		auto eval_high_result = input_star.constraints().evaluate( dir_vect );

		bool feas_low = ( eval_low_result.errorCode == SOLUTION::FEAS );
		bool feas_high = ( eval_high_result.errorCode == SOLUTION::FEAS );
		bool unbounded_low = ( eval_low_result.errorCode == SOLUTION::INFTY );
		bool unbounded_high = ( eval_high_result.errorCode == SOLUTION::INFTY );

		Number lb = feas_low ? -eval_low_result.supportValue + center[i] : Number( 0 );
		Number ub = feas_high ? eval_high_result.supportValue + center[i] : Number( 0 );

		if ( feas_low && lb >= value ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			center[ i ] = maxValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis);
			result.push_back( res_star );
			continue;
		}

		if ( feas_high && ub <= value ) {
			hypro::matrix_t<Number> transformationMatrix = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			transformationMatrix( i, i ) = 0.0;
			basis = transformationMatrix * basis;
			center[ i ] = minValue;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}

		if ( feas_low && feas_high ) {
			resizeShapeAndLimit(shape, limits, 4);

			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero(shape.cols());
			fst_constr[fst_constr.rows() - 1] = -1;
            shape.row(shape.rows() - 4) = fst_constr;
            limits[limits.rows() - 4] = -minValue;

            hypro::vector_t<Number> snd_constr = hypro::vector_t<Number>::Zero(shape.cols());
            snd_constr[snd_constr.rows() - 1] = +1;
            shape.row(shape.rows() - 3) = snd_constr;
            limits[limits.rows() - 3] = +maxValue;

            hypro::vector_t<Number> trd_constr = basis.row(i);
            trd_constr *= -(maxValue - minValue) / (value - lb);
            trd_constr.conservativeResize(trd_constr.rows() + 1);
            trd_constr[trd_constr.rows() - 1] = 1;
            shape.row(shape.rows() - 2) = trd_constr;
            limits[limits.rows() - 2] = center[i] * (maxValue - minValue) / (value - lb) + (value * minValue - lb * maxValue)  / (value - lb);

			hypro::vector_t<Number> frt_constr = basis.row(i);
			frt_constr *= (maxValue - minValue) / (ub - value);
			frt_constr[frt_constr.rows() - 1] = -1;
            shape.row(shape.rows() - 1) = frt_constr;
            limits[limits.rows() - 1] = -center[i] * (maxValue - minValue) / (ub - value) - (ub * minValue - value * maxValue) / (ub - value);
		}

		if ( unbounded_low && feas_high ) {
			resizeShapeAndLimit(shape, limits, 3);

			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero(shape.cols());
			fst_constr[fst_constr.rows() - 1] = -1;
            shape.row(shape.rows() - 3) = fst_constr;
            limits[limits.rows() - 3] = -minValue;

            hypro::vector_t<Number> snd_constr = hypro::vector_t<Number>::Zero(shape.cols());
            snd_constr[snd_constr.rows() - 1] = +1;
            shape.row(shape.rows() - 2) = snd_constr;
            limits[limits.rows() - 2] = +maxValue;

			hypro::vector_t<Number> frt_constr = basis.row(i);
			frt_constr *= (maxValue - minValue) / (ub - value);
			frt_constr[frt_constr.rows() - 1] = -1;
            shape.row(shape.rows() - 1) = frt_constr;
            limits[limits.rows() - 1] = -center[i] * (maxValue - minValue) / (ub - value) - (ub * minValue - value * maxValue) / (ub - value);
		}

		if ( feas_low && unbounded_high ) {
			resizeShapeAndLimit(shape, limits, 3);

			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero(shape.cols());
			fst_constr[fst_constr.rows() - 1] = -1;
            shape.row(shape.rows() - 3) = fst_constr;
            limits[limits.rows() - 3] = -minValue;

            hypro::vector_t<Number> snd_constr = hypro::vector_t<Number>::Zero(shape.cols());
            snd_constr[snd_constr.rows() - 1] = +1;
            shape.row(shape.rows() - 2) = snd_constr;
            limits[limits.rows() - 2] = +maxValue;

            hypro::vector_t<Number> trd_constr = basis.row(i);
            trd_constr *= -(maxValue - minValue) / (value - lb);
            trd_constr.conservativeResize(trd_constr.rows() + 1);
            trd_constr[trd_constr.rows() - 1] = 1;
            shape.row(shape.rows() - 1) = trd_constr;
            limits[limits.rows() - 1] = center[i] * (maxValue - minValue) / (value - lb) + (value * minValue - lb * maxValue)  / (value - lb);
		}

		if ( unbounded_low && unbounded_high ) {
			resizeShapeAndLimit(shape, limits, 2);

			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero(shape.cols());
			fst_constr[fst_constr.rows() - 1] = -1;
            shape.row(shape.rows() - 2) = fst_constr;
            limits[limits.rows() - 2] = -minValue;

            hypro::vector_t<Number> snd_constr = hypro::vector_t<Number>::Zero(shape.cols());
            snd_constr[snd_constr.rows() - 1] = +1;
            shape.row(shape.rows() - 1) = snd_constr;
            limits[limits.rows() - 1] = +maxValue;
		}

        basis.row(i).setZero();
        center[i] = 0;

        basis.conservativeResize(basis.rows(), basis.cols() + 1);
        basis.col(basis.cols() - 1) = hypro::vector_t<Number>::Zero(basis.rows());
        basis(i, basis.cols() - 1) = 1;

        result.emplace_back(center, shape, limits, basis);
	}
	return result;
}

template <typename Number>
void StepFunction<Number>::resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows) {
    shape.conservativeResize(shape.rows() + rows, shape.cols() + 1);
    shape.col(shape.cols() - 1) = hypro::vector_t<Number>::Zero(shape.rows());
    limits.conservativeResize(limits.rows() + rows);
}

}  // namespace hypro