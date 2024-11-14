/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "ReachNN.h"

namespace hypro {
namespace reachability {

template <typename Number>
std::vector<hypro::Starset<Number>> ReachNN<Number>::forwardAnalysis( const hypro::Starset<Number>& input_set, NN_REACH_METHOD method, bool plot_intermediates ) const {
	// std::cout << method << std::endl;
	// std::cout << mNNet << std::endl;
	// std::cout << input_set.constraints() << std::endl;
	std::vector<hypro::Starset<Number>> result = std::vector<hypro::Starset<Number>>();
	result.push_back( input_set );
	for ( int l = 0; l < mNNet.numLayers(); l++ ) {
		std::cout << "Computing output of layer: " << l << std::endl;
		result = layerReach( l, result, method, plot_intermediates );
		std::cout << "Number of stars: " << result.size() << std::endl;
	}

	return result;
}

template <typename Number>
std::vector<hypro::Starset<Number>> ReachNN<Number>::layerReach( int l, const std::vector<hypro::Starset<Number>>& input_sets, NN_REACH_METHOD method, bool plot_intermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	std::vector<hypro::Starset<Number>> result = std::vector<hypro::Starset<Number>>();
	int N = input_sets.size();	// number of input stars

	// get layer parameters l
	std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layer_l = mNNet.layerParams( l );
	hypro::matrix_t<Number> weights = layer_l.first;
	hypro::vector_t<Number> biases = layer_l.second;

	// this for loop could be parallelized
	// #pragma omp parallel for
	for ( int i = 0; i < N; i++ ) {
		if ( plot_intermediates ) {
			// #pragma omp critical
			plotter.addObject( input_sets[i].vertices(), hypro::plotting::colors[hypro::plotting::red] );
		}

		hypro::Starset<Number> current_star = input_sets[i].affineTransformation( weights, biases );

		if ( plot_intermediates ) {
			// #pragma omp critical
			// std::cout << "Here: " << current_star.vertices() << std::endl;
			plotter.addObject( current_star.vertices(), hypro::plotting::colors[hypro::plotting::green] );
			plotter.plot2d();
			plotter.clear();
		}

		std::vector<hypro::Starset<Number>> result_stars;
		if ( l < mNNet.numLayers() - 1 ) {
			// the last layer is just an affine transformation, so it does not have ReLU activation functions
			// in the case of ACAS Xu networks, there are 6 hidden layers in total 300 ReLU nodes,  + 5 output nodes, those are only affine mappings
			result_stars = reachReLU( current_star, method, plot_intermediates );
		} else {
			// std::cout << "Last layer, no ReLU step applied" << std::endl;
			result_stars = std::vector<hypro::Starset<Number>>();
			result_stars.push_back( current_star );
		}
		// #pragma omp critical
		{
			result.insert( result.end(), result_stars.begin(), result_stars.end() );
		}
	}

	return result;	// empty list
}

template <typename Number>
std::vector<hypro::Starset<Number>> ReachNN<Number>::reachReLU( const hypro::Starset<Number>& input_star1, NN_REACH_METHOD method, bool plot_intermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	std::vector<hypro::Starset<Number>> I_n = std::vector<hypro::Starset<Number>>();
	I_n.push_back( input_star1 );
	for ( int i = 0; i < input_star1.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				// apply the exact method
				// std::cout << "Applying the exact method" << std::endl;
				I_n = stepReLU( i, I_n );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				// apply the overapproximate method
				// std::cout << "Applying the overapproximate method" << std::endl;
				// std::cout << "Applying ReLU on dimension: " << i << std::endl;
				I_n = approxStepReLU( i, I_n );
				// std::cout << "Inner polytope shape: (num_constrains, dim_constrains) = (" << I_n[I_n.size() - 1].constraints().size() << ", " << I_n[I_n.size() - 1].constraints().dimension() << ")" << std::endl;

				break;
			default:
				FATAL( "hypro.neuralnets.reachability", "Invalid analysis method specified" );
				// std::cout << "Invalid analysis method specified" << std::endl;
		}
		if ( plot_intermediates ) {
			// #pragma omp critical
			for ( int j = 0; j < I_n.size(); j++ ) {
				plotter.addObject( I_n[j].vertices(), hypro::plotting::colors[( 2 * j ) % 9] );
			}
			plotter.plot2d();
			plotter.clear();
		}
	}
	return I_n;
}

template <typename Number>
std::vector<hypro::Starset<Number>>
ReachNN<Number>::stepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) const {
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

		if ( lb >= 0 ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, basis, politope );
			result.push_back( res_star );
			continue;
		}
		if ( ub <= 0 ) {
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
std::vector<hypro::Starset<Number>>
ReachNN<Number>::approxStepReLU( int i, std::vector<hypro::Starset<Number>>& input_sets ) const {
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

		if ( lb >= 0 ) {
			hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
			result.push_back( res_star );
			continue;
		}
		if ( ub <= 0 ) {
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
		shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero(
			  shape.rows() );  // fill up last column with zeros
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

		// std::cout << "Creating new star" << std::endl;

		hypro::Starset<Number> res_star = hypro::Starset<Number>( center, shape, limits, basis );
		result.push_back( res_star );
	}

	return result;
}

}  // namespace reachability
}  // namespace hypro
