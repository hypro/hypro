#include "ReLU.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> ReLU<Number>::stepReLU( int i, const std::vector<hypro::Starset<Number>>& input_sets ) {
	std::vector<hypro::Starset<Number>> result;

	for ( auto& input_set : input_sets ) {
		auto center = input_set.center();
		auto basis = input_set.generator();
		auto politope = input_set.constraints();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = politope.evaluate( -dir_vect );
		auto eval_high_result = politope.evaluate( dir_vect );

		if ( eval_low_result.errorCode == SOLUTION::INFEAS ||
			 eval_low_result.errorCode == SOLUTION::UNKNOWN ||
			 eval_high_result.errorCode == SOLUTION::INFEAS ||
			 eval_high_result.errorCode == SOLUTION::UNKNOWN ) {
			continue;
		}

		// lower bound is positive
		if ( eval_low_result.errorCode == SOLUTION::FEAS ) {
			Number lb = -eval_low_result.supportValue + center[i];
			if ( lb >= 0 || carl::AlmostEqual2sComplement( lb, Number( 0 ) ) ) {
				result.emplace_back( center, basis, politope );
				continue;
			}
		}

		// upper bound is negative
		if ( eval_high_result.errorCode == SOLUTION::FEAS ) {
			Number ub = eval_high_result.supportValue + center[i];
			if ( ub <= 0 || carl::AlmostEqual2sComplement( ub, Number( 0 ) ) ) {
				basis.row(i).setZero();
                center[i] = 0;
                result.emplace_back(center, basis, politope);
				continue;
			}
		}

		// x_i >= 0
		auto politope_1 = politope;
		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( -basis.row( i ) ), center[i] );
		politope_1 = politope_1.intersectHalfspace( pos_1 );
		result.emplace_back( center, basis, politope_1 );
		
		// x_i < 0
		auto center_2 = center;
		auto basis_2 = basis;
		auto politope_2 = politope;
		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( basis.row( i ) ), -center[i] );
		politope_2 = politope_2.intersectHalfspace( neg_1 );
		basis_2.row(i).setZero();
		center_2[i] = 0;
		result.emplace_back( center_2, basis_2, politope_2 );
	}

	return result;
}

template <typename Number>
std::vector<std::pair<hypro::Starset<Number>, char>> ReLU<Number>::stepReLUWithHistory( int i, const hypro::Starset<Number>& input_set ) {
	std::vector<std::pair<hypro::Starset<Number>, char>> result = std::vector<std::pair<hypro::Starset<Number>, char>>();

	hypro::vector_t<Number> center = input_set.center();
	hypro::matrix_t<Number> basis = input_set.generator();
	hypro::HPolytope<Number> politope = input_set.constraints();

	hypro::vector_t<Number> dir_vect = basis.row( i );
	auto eval_low_result = politope.evaluate( -1.0 * dir_vect );
	auto eval_high_result = politope.evaluate( dir_vect );

	Number lb = -eval_low_result.supportValue + center[i];
	Number ub = eval_high_result.supportValue + center[i];

		if ( lb >= 0 || carl::AlmostEqual2sComplement(lb, Number(0)) ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, politope );
			result.push_back( res_star );
			continue;
		}
		if ( ub <= 0 || carl::AlmostEqual2sComplement(ub, Number(0)) ) {
			hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			I_i( i, i ) = 0.0;
			basis = I_i * basis;
			center = I_i * center;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, politope );
			result.push_back( res_star );
			continue;
		}

	// x_i >= 0
	hypro::vector_t<Number> center_1 = center;
	hypro::matrix_t<Number> basis_1 = basis;
	hypro::HPolytope<Number> politope_1 = politope;

	hypro::vector_t<Number> temp_1 = basis_1.row( i ) * ( -1 );
	hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_1 ), center_1[i] );
	politope_1 = politope_1.intersectHalfspace( pos_1 );
	hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, politope_1 );

	// x_i < 0
	hypro::vector_t<Number> center_2 = center;
	hypro::matrix_t<Number> basis_2 = basis;
	hypro::HPolytope<Number> politope_2 = politope;

	hypro::vector_t<Number> temp_2 = basis_2.row( i );
	hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_2 ), -center_2[i] );
	politope_2 = politope_2.intersectHalfspace( neg_1 );
	hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
	I_i( i, i ) = 0.0;
	center_2 = I_i * center_2;
	basis_2 = I_i * basis_2;
	hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, politope_2 );

	result.push_back( std::make_pair(star_1, '1') );
	result.push_back( std::make_pair(star_2, '2') );

	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> ReLU<Number>::approxStepReLU( int i, const std::vector<hypro::Starset<Number>>& input_sets ) {
	std::vector<hypro::Starset<Number>> result;
	for (auto& input_star : input_sets) {
		auto center = input_star.center();
		auto basis = input_star.generator();
		auto shape = input_star.shape();
		auto limits = input_star.limits();

		hypro::vector_t<Number> dir_vect = basis.row( i );
		auto eval_low_result = input_star.constraints().evaluate( -dir_vect );
		auto eval_high_result = input_star.constraints().evaluate( dir_vect );

		// if (eval_low_result.errorCode == SOLUTION::INFTY)
		// 	std::cout << "At neuron index " << i << " there was no lower bound" << std::endl;
		// if (eval_high_result.errorCode == SOLUTION::INFTY)
		// 	std::cout << "At neuron index " << i << " there was no upper bound" << std::endl;

		if ( eval_low_result.errorCode == SOLUTION::INFEAS ||
			 eval_low_result.errorCode == SOLUTION::UNKNOWN ||
			 eval_high_result.errorCode == SOLUTION::INFEAS ||
			 eval_high_result.errorCode == SOLUTION::UNKNOWN ) {
			std::cout << "Ignoring empty star." << std::endl;
			continue;
		}

		bool feas_low = ( eval_low_result.errorCode == SOLUTION::FEAS );
		bool feas_high = ( eval_high_result.errorCode == SOLUTION::FEAS );
		bool unbounded_low = ( eval_low_result.errorCode == SOLUTION::INFTY );
		bool unbounded_high = ( eval_high_result.errorCode == SOLUTION::INFTY );

		Number lb = feas_low ? -eval_low_result.supportValue + center[i] : Number(-DBL_MAX);
        Number ub = feas_high ? eval_high_result.supportValue + center[i] : Number(DBL_MAX);

		// std::cout << "[lb, ub] = [" << lb << ", " << ub << "]" << std::endl; 

		if ( feas_low && ( lb >= 0 || carl::AlmostEqual2sComplement( lb, Number( 0 ) ) ) ) {
			result.emplace_back( center, shape, limits, basis );
			continue;
		}

		if ( feas_high && ( ub <= 0 || carl::AlmostEqual2sComplement( ub, Number( 0 ) ) ) ) {
			basis.row(i).setZero();
			center[i] = 0;
			result.emplace_back( center, shape, limits, basis );
			continue;
		}

		// bounded from both sides
		if ( feas_low && feas_high ) {
			resizeShapeAndLimits(shape, limits, 3);

			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero( shape.cols() );
			fst_constr[fst_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = fst_constr;
			limits[limits.rows() - 3] = 0;

			// second constraint: x_(m+1) >= x_i
			hypro::vector_t<Number> snd_constr = basis.row( i );
			snd_constr.conservativeResize( snd_constr.rows() + 1 );
			snd_constr[snd_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = snd_constr;
			limits[limits.rows() - 2] = -center[i];

			// third constraint: x_(m+1) <= ub * (x_i - lb) / (ub - lb)
			hypro::vector_t<Number> trd_constr = basis.row( i );
			trd_constr = trd_constr * ( -( ub / ( ub - lb ) ) );
			trd_constr.conservativeResize( trd_constr.rows() + 1 );
			trd_constr( trd_constr.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = trd_constr;
			limits[limits.rows() - 1] = ( ub * ( center[i] - lb ) ) / ( ub - lb );
		}

		// no upper-bound
		if ( feas_low && unbounded_high ) {
			resizeShapeAndLimits(shape, limits, 3);

			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero( shape.cols() );
			fst_constr[fst_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = fst_constr;
			limits[limits.rows() - 3] = 0;

			// second constraint: x_(m+1) >= x_i
			hypro::vector_t<Number> snd_constr = basis.row( i );
			snd_constr.conservativeResize( snd_constr.rows() + 1 );
			snd_constr[snd_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = snd_constr;
			limits[limits.rows() - 2] = -center[i];

			// third constraint: x_(m+1) <= x_i + lb
			hypro::vector_t<Number> trd_constr = ( -1 ) * basis.row( i );
			trd_constr.conservativeResize( trd_constr.rows() + 1 );
			trd_constr( trd_constr.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = trd_constr;
			limits[limits.rows() - 1] = center[i] - lb;
		}

		// no lower-bound
		if ( unbounded_low && feas_high ) {
			resizeShapeAndLimits(shape, limits, 3);

			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero( shape.cols() );
			fst_constr[fst_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 3 ) = fst_constr;
			limits[limits.rows() - 3] = 0;

			// second constraint: x_(m+1) >= x_i
			hypro::vector_t<Number> snd_constr = basis.row( i );
			snd_constr.conservativeResize( snd_constr.rows() + 1 );
			snd_constr[snd_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = snd_constr;
			limits[limits.rows() - 2] = -center[i];

			// third constraint: x_(m+1) <= ub
			hypro::vector_t<Number> trd_constr = hypro::vector_t<Number>::Zero( shape.cols() );
			trd_constr( trd_constr.rows() - 1 ) = 1;
			shape.row( shape.rows() - 1 ) = trd_constr;
			limits[limits.rows() - 1] = ub;
		}

		// unbounded in both directions
		if ( unbounded_low && unbounded_high ) {
			resizeShapeAndLimits(shape, limits, 2);
			
			// first constraint: x_(m+1) >= 0
			hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero( shape.cols() );
			fst_constr[fst_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 2 ) = fst_constr;
			limits[limits.rows() - 2] = 0;

			// second constraint: x_(m+1) >= x_i
			hypro::vector_t<Number> snd_constr = basis.row( i );
			snd_constr.conservativeResize( snd_constr.rows() + 1 );
			snd_constr[snd_constr.rows() - 1] = -1;
			shape.row( shape.rows() - 1 ) = snd_constr;
			limits[limits.rows() - 1] = -center[i];
		}

		// "unlink" x_i from all previous predicate variables
		basis.row(i).setZero();
		center[i] = 0;

		// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector (link)
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( i, basis.cols() - 1 ) = 1;

		result.emplace_back( center, shape, limits, basis );
	}

	return result;
}

template <typename Number>
std::vector<std::pair<hypro::Starset<Number>, char>> ReLU<Number>::stepReLUWithHistory( int i, const hypro::Starset<Number>& input_set ) {
	std::vector<std::pair<hypro::Starset<Number>, char>> result = std::vector<std::pair<hypro::Starset<Number>, char>>();

	hypro::vector_t<Number> center = input_set.center();
	hypro::matrix_t<Number> basis = input_set.generator();
	hypro::HPolytope<Number> politope = input_set.constraints();

	hypro::vector_t<Number> dir_vect = basis.row( i );
	auto eval_low_result = politope.evaluate( -1.0 * dir_vect );
	auto eval_high_result = politope.evaluate( dir_vect );

	Number lb = -eval_low_result.supportValue + center[i];
	Number ub = eval_high_result.supportValue + center[i];

	if ( lb >= 0 || carl::AlmostEqual2sComplement(lb, Number(0)) ) {
		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, politope );
		result.push_back( std::make_pair(res_star, '1') );
		return result;
	}

	if ( ub <= 0 || carl::AlmostEqual2sComplement(ub, Number(0)) ) {
		hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		I_i( i, i ) = 0.0;
		basis = I_i * basis;
		center = I_i * center;
		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, politope );
		result.push_back( std::make_pair(res_star, '2') );
		return result;
	}

	// x_i >= 0
	hypro::vector_t<Number> center_1 = center;
	hypro::matrix_t<Number> basis_1 = basis;
	hypro::HPolytope<Number> politope_1 = politope;

	hypro::vector_t<Number> temp_1 = basis_1.row( i ) * ( -1 );
	hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_1 ), center_1[i] );
	politope_1 = politope_1.intersectHalfspace( pos_1 );
	hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, politope_1 );

	// x_i < 0
	hypro::vector_t<Number> center_2 = center;
	hypro::matrix_t<Number> basis_2 = basis;
	hypro::HPolytope<Number> politope_2 = politope;

	hypro::vector_t<Number> temp_2 = basis_2.row( i );
	hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_2 ), -center_2[i] );
	politope_2 = politope_2.intersectHalfspace( neg_1 );
	hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
	I_i( i, i ) = 0.0;
	center_2 = I_i * center_2;
	basis_2 = I_i * basis_2;
	hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, politope_2 );

	result.push_back( std::make_pair(star_1, '1') );
	result.push_back( std::make_pair(star_2, '2') );

	return result;
}

template <typename Number>
std::vector<std::pair<hypro::Starset<Number>, char>> ReLU<Number>::approxStepReLUWithHistory( int i, const Starset<Number>& input_set ) {
	std::vector<std::pair<hypro::Starset<Number>, char>> result = std::vector<std::pair<hypro::Starset<Number>, char>>();
		
	hypro::Starset<Number> input_star = input_set;

	hypro::vector_t<Number> center = input_star.center();
	hypro::matrix_t<Number> basis = input_star.generator();
	hypro::matrix_t<Number> shape = input_star.shape();
	hypro::vector_t<Number> limits = input_star.limits();

	hypro::vector_t<Number> dir_vect = basis.row( i );
	auto eval_low_result = input_star.constraints().evaluate( -1.0 * dir_vect );
	auto eval_high_result = input_star.constraints().evaluate( dir_vect );

	Number lb = -eval_low_result.supportValue + center[i];
	Number ub = eval_high_result.supportValue + center[i];

	// std::cout << "Star bounds = [" << lb << ", " << ub << "]" << std::endl;

		if ( lb >= 0 || carl::AlmostEqual2sComplement(lb, Number(0)) ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}
		if ( ub <= 0 || carl::AlmostEqual2sComplement(ub, Number(0)) ) {
			hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
			I_i( i, i ) = 0.0;
			basis = I_i * basis;
			center = I_i * center;
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}

	// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
	shape.conservativeResize( shape.rows() + 3, shape.cols() + 1 );
	shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );	// fill up last column with zeros
	// std::cout << "New shape size: (" << shape.rows() << ", " << shape.cols() << ")" << std::endl;
	limits.conservativeResize( limits.rows() + 3 );
	// std::cout << "New limits size: (" << limits.rows() << ", " << limits.cols() << ")" << std::endl;

	// first constraint: x_(m+1) >= 0
	hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero( shape.cols() );
	fst_constr[fst_constr.rows() - 1] = -1;
	shape.row( shape.rows() - 3 ) = fst_constr;
	limits[limits.rows() - 3] = 0;

	// second constraint: x_(m+1) >= x_i
	hypro::vector_t<Number> snd_constr = basis.row( i );
	snd_constr.conservativeResize( snd_constr.rows() + 1 );
	snd_constr[snd_constr.rows() - 1] = -1;
	shape.row( shape.rows() - 2 ) = snd_constr;
	limits[limits.rows() - 2] = -center[i];

	// third constraint: x_(m+1) <= ub * (x_i - lb) / (ub - lb)
	hypro::vector_t<Number> trd_constr = basis.row( i );
	trd_constr = trd_constr * ( -( ub / ( ub - lb ) ) );
	trd_constr.conservativeResize( trd_constr.rows() + 1 );
	trd_constr( trd_constr.rows() - 1 ) = 1;
	shape.row( shape.rows() - 1 ) = trd_constr;
	limits[limits.rows() - 1] = ( ub * ( center[i] - lb ) ) / ( ub - lb );

	hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
	I_i( i, i ) = 0.0;
	basis = I_i * basis;
	center = I_i * center;

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
std::vector<std::pair<hypro::Starset<Number>, char>> ReLU<Number>::approxStepReLUWithHistory( int i, const Starset<Number>& input_set ) {
	std::vector<std::pair<hypro::Starset<Number>, char>> result = std::vector<std::pair<hypro::Starset<Number>, char>>();
		
	hypro::Starset<Number> input_star = input_set;

	hypro::vector_t<Number> center = input_star.center();
	hypro::matrix_t<Number> basis = input_star.generator();
	hypro::matrix_t<Number> shape = input_star.shape();
	hypro::vector_t<Number> limits = input_star.limits();

	hypro::vector_t<Number> dir_vect = basis.row( i );
	auto eval_low_result = input_star.constraints().evaluate( -1.0 * dir_vect );
	auto eval_high_result = input_star.constraints().evaluate( dir_vect );

	Number lb = -eval_low_result.supportValue + center[i];
	Number ub = eval_high_result.supportValue + center[i];

	// std::cout << "Star bounds = [" << lb << ", " << ub << "]" << std::endl;

	if ( lb >= 0 || carl::AlmostEqual2sComplement(lb, Number(0)) ) {
		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
		result.push_back( std::make_pair(res_star, '1') );
		return result;
	}
	
	if ( ub <= 0 || carl::AlmostEqual2sComplement(ub, Number(0)) ) {
		hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
		I_i( i, i ) = 0.0;
		basis = I_i * basis;
		center = I_i * center;
		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
		result.push_back( std::make_pair(res_star, '2') );
		return result;
	}

	// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
	shape.conservativeResize( shape.rows() + 3, shape.cols() + 1 );
	shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );	// fill up last column with zeros
	// std::cout << "New shape size: (" << shape.rows() << ", " << shape.cols() << ")" << std::endl;
	limits.conservativeResize( limits.rows() + 3 );
	// std::cout << "New limits size: (" << limits.rows() << ", " << limits.cols() << ")" << std::endl;

	// first constraint: x_(m+1) >= 0
	hypro::vector_t<Number> fst_constr = hypro::vector_t<Number>::Zero( shape.cols() );
	fst_constr[fst_constr.rows() - 1] = -1;
	shape.row( shape.rows() - 3 ) = fst_constr;
	limits[limits.rows() - 3] = 0;

	// second constraint: x_(m+1) >= x_i
	hypro::vector_t<Number> snd_constr = basis.row( i );
	snd_constr.conservativeResize( snd_constr.rows() + 1 );
	snd_constr[snd_constr.rows() - 1] = -1;
	shape.row( shape.rows() - 2 ) = snd_constr;
	limits[limits.rows() - 2] = -center[i];

	// third constraint: x_(m+1) <= ub * (x_i - lb) / (ub - lb)
	hypro::vector_t<Number> trd_constr = basis.row( i );
	trd_constr = trd_constr * ( -( ub / ( ub - lb ) ) );
	trd_constr.conservativeResize( trd_constr.rows() + 1 );
	trd_constr( trd_constr.rows() - 1 ) = 1;
	shape.row( shape.rows() - 1 ) = trd_constr;
	limits[limits.rows() - 1] = ( ub * ( center[i] - lb ) ) / ( ub - lb );

	hypro::matrix_t<Number> I_i = hypro::matrix_t<Number>::Identity( center.rows(), center.rows() );
	I_i( i, i ) = 0.0;
	basis = I_i * basis;
	center = I_i * center;

	// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector
	basis.conservativeResize( basis.rows(), basis.cols() + 1 );
	basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
	basis( i, basis.cols() - 1 ) = 1;

	hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
	result.push_back( std::make_pair(res_star, '0') );
	
	return result;
}

// Resize helper function
template <typename Number>
void ReLU<Number>::resizeShapeAndLimits(hypro::matrix_t<Number>& shape, hypro::vector_t<Number>& limits, int rows) {
    shape.conservativeResize(shape.rows() + rows, shape.cols() + 1);
    shape.col(shape.cols() - 1) = hypro::vector_t<Number>::Zero(shape.rows());
    limits.conservativeResize(limits.rows() + rows);
}

}  // namespace hypro
