#include "ReLU.h"

namespace hypro {

template <typename Number>
std::vector<hypro::Starset<Number>> ReLU<Number>::stepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) {
	std::vector<hypro::Starset<Number>> result = std::vector<hypro::Starset<Number>>();

	int k = input_sets.size();
	for ( int j = 0; j < k; j++ ) {
		hypro::vector_t<Number> center = input_sets[j].center();
		hypro::matrix_t<Number> basis = input_sets[j].generator();
		hypro::HPolytope<Number> politope = input_sets[j].constraints();

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

		result.push_back( star_1 );
		result.push_back( star_2 );
	}

	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> ReLU<Number>::approxStepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) {
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

}  // namespace hypro
