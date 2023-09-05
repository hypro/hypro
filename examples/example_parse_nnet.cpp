// #include "hypro/representations/Starset/Starset.h"
#include "hypro/neuralnets/parser/NNet.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <iostream>

// use rational arithmetic.
typedef double Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

void test_network_read() {
	// Build network and time how long build takes
	const char* filename = "../examples/nnet/fc_2-2.nnet";
	std::cout << "Filename is: " << filename << std::endl;

	auto start_create = std::chrono::steady_clock::now();
	hypro::NNet<Number>* test_net = new hypro::NNet<Number>( filename );
	auto build_network = std::chrono::steady_clock::now() - start_create;
	// std::cout << test_net << std::endl;

	if ( test_net != NULL ) {
		// Set up variables for evaluating network
		auto start_evaluate = std::chrono::steady_clock::now();
		int num_runs = 4;
		hypro::vector_t<Number> input = hypro::vector_t<Number>::Zero( 2 );
		input << 1, 2;
		hypro::vector_t<Number> output = hypro::vector_t<Number>::Zero( 2 );
		bool normalizeInput = false;
		bool normalizeOutput = false;

		std::cout << "Starting calculations..." << std::endl;
		for ( int i = 0; i < num_runs; i++ ) {
			// input[0] += 1000.0;
			// input[1] += 0.2;
			output = test_net->evaluateNetwork( input, normalizeInput, normalizeOutput );

			// Print out final input/output values
			std::cout << "Inputs: " << std::endl
					  << input << std::endl;
			std::cout << "Outputs: " << std::endl
					  << output << std::endl;

			input = output;
		}
		// Stop clock and then destruct network
		auto evaluate_network = std::chrono::steady_clock::now() - start_evaluate;

		// Compute times and print out
		std::cout << "Time taken to load the network: "
				  << std::chrono::duration_cast<std::chrono::microseconds>( build_network ).count() << " µs" << std::endl;
		std::cout << "Time taken for " << num_runs << " forward passes: "
				  << std::chrono::duration_cast<std::chrono::microseconds>( evaluate_network ).count() << " µs" << std::endl;

		delete test_net;
	}
}

void test_acas_xu() {
	const char* filename = "../examples/nnet/acasxu/ACASXU_experimental_v2a_1_1.nnet";
	std::cout << "Filename is: " << filename << std::endl;

	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> acas_xu = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << acas_xu << std::endl;

	hypro::vector_t<Number> input = hypro::vector_t<Number>::Zero( 5 );
	input << 1, 2, 3, 4, 5;

	start = std::chrono::steady_clock::now();
	hypro::vector_t<Number> output = acas_xu.evaluateNetwork( input );
	end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during evaluating the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;

	std::cout << "Network input " << std::endl
			  << input << std::endl;
	std::cout << "Network output " << std::endl
			  << output << std::endl;
}

void test_network_plot() {
	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.setFilename( "Rotate_net" );

	// define input file name
	const char* filename = "../examples/nnet/fc_rotate.nnet";
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> rotate_nn = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << rotate_nn << std::endl;

	// create an input starset
	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
	center << 5, 2;
	basis << 1, 0, 0, 1;
	constr << 1, 0, -1, 0, 0, 1, 0, -1;
	limits << 2, 1, 1, 1;
	hypro::Starset<Number> input_star = hypro::Starset<Number>( center, constr, limits, basis );
	plotter.addObject( input_star.vertices() );

	for ( int i = 0; i < rotate_nn.numLayers(); i++ ) {
		std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layer_i = rotate_nn.layerParams( i );
		hypro::matrix_t<Number> weights = layer_i.first;
		hypro::vector_t<Number> biases = layer_i.second;
		input_star = input_star.affineTransformation( weights, biases );
		plotter.addObject( input_star.vertices() );
	}

	// make the plot in 2D
	plotter.plot2d();
}

void test_relu_exact() {
	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.filename = "FFReLU_net";
	settings.fill = true;
	settings.pointSize = 3.0;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );

	// define input file name
	const char* filename = "../examples/nnet/fc_relu.nnet";
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> rotate_nn = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << rotate_nn << std::endl;

	// create an input starset and plot it

	// a simple rectangle [_]
	// hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	// hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	// hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
	// hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
	// center << 0, 0;
	// basis << 1, 0, 0, 1;
	// constr << 1, 0, -1, 0, 0, 1, 0, -1;
	// limits << 2, 1, 1, 1;

	// a triangle  |>
	// hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	// hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	// hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 3, 2 );
	// hypro::vector_t<Number> limits = hypro::vector_t<Number>( 3 );\
	// center << 0, 0;
	// basis << 1, 0, 0, 1;
	// constr << -1, 0, 1, 1, 1, -1;
	// limits << 1, 1, 1;
	// hypro::Starset<Number> input_star = hypro::Starset<Number>( center, constr, limits, basis );
	// plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::red] );

	// another triangle /_|
	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 3, 2 );
	hypro::vector_t<Number> limits = hypro::vector_t<Number>( 3 );
	center << 0, 0;
	basis << -2, 0, 0, 1;
	constr << -1, 0, 0, -1, 1, 1;
	limits << 1, 2, 1;

	hypro::Starset<Number> input_star = hypro::Starset<Number>( center, constr, limits, basis );
	plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::red] );

	for ( int i = 0; i < rotate_nn.numLayers(); i++ ) {
		// get layer parameters i
		std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layer_i = rotate_nn.layerParams( i );
		hypro::matrix_t<Number> weights = layer_i.first;
		hypro::vector_t<Number> biases = layer_i.second;

		// apply the affine transformation and plot
		input_star = input_star.affineTransformation( weights, biases );
		plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::green] );
		plotter.plot2d();
		plotter.clear();

		// apply ReLU function and plot
		// apply ReLU on x_1

		hypro::vector_t<Number> center = input_star.center();
		hypro::matrix_t<Number> basis = input_star.generator();
		hypro::HPolytope<Number> politope = input_star.constraints();

		// x_1 >= 0
		hypro::vector_t<Number> center_1 = center;
		hypro::matrix_t<Number> basis_1 = basis;
		hypro::HPolytope<Number> politope_1 = politope;

		hypro::vector_t<Number> temp_1 = basis_1.row( 0 ) * ( -1 );
		hypro::Halfspace<Number> pos_1 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_1 ), center_1[0] );
		politope_1 = politope_1.intersectHalfspace( pos_1 );
		hypro::Starset<Number> star_1 = hypro::Starset<Number>( center_1, basis_1, politope_1 );
		plotter.addObject( star_1.vertices(), hypro::plotting::colors[hypro::plotting::bordeaux] );
		// std::cout << center_1 << std::endl
		// 		  << basis_1 << std::endl
		// 		  << politope_1 << std::endl;

		// x_1 <  0
		hypro::vector_t<Number> center_2 = center;
		hypro::matrix_t<Number> basis_2 = basis;
		hypro::HPolytope<Number> politope_2 = politope;

		hypro::matrix_t<Number> I2_0 = hypro::matrix_t<Number>::Identity(2, 2);
		I2_0(0, 0) = 0;

		hypro::vector_t<Number> temp_2 = basis_2.row( 0 );
		hypro::Halfspace<Number> neg_1 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_2 ), -center_2[0] );
		politope_2 = politope_2.intersectHalfspace( neg_1 );
		center_2 = I2_0 * center_2;
		basis_2 = I2_0 * basis_2;
		hypro::Starset<Number> star_2 = hypro::Starset<Number>( center_2, basis_2, politope_2 );
		plotter.addObject( star_2.vertices(), hypro::plotting::colors[hypro::plotting::lila] );
		// std::cout << center_2 << std::endl
		// 		  << basis_2 << std::endl
		// 		  << politope_2 << std::endl;
		plotter.plot2d();
		plotter.clear();

		//apply ReLU on x_2
		// x_1 >= 0, x_2 >= 0
		hypro::vector_t<Number> center_3 = center_1;
		hypro::matrix_t<Number> basis_3 = basis_1;
		hypro::HPolytope<Number> politope_3 = politope_1;

		hypro::vector_t<Number> temp_3 = basis_3.row( 1 ) * ( -1 );
		hypro::Halfspace<Number> pos_2 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_3 ), center_3[1] );
		politope_3 = politope_3.intersectHalfspace( pos_2 );
		hypro::Starset<Number> star_3 = hypro::Starset<Number>( center_3, basis_3, politope_3 );
		plotter.addObject( star_3.vertices(), hypro::plotting::colors[hypro::plotting::turquoise] );
		// std::cout << center_1 << std::endl
		// 		  << basis_1 << std::endl
		// 		  << politope_3 << std::endl;

		// x_1 >= 0, x_2 < 0
		hypro::vector_t<Number> center_4 = center_1;
		hypro::matrix_t<Number> basis_4 = basis_1;
		hypro::HPolytope<Number> politope_4 = politope_1;

		hypro::matrix_t<Number> I2_1 = hypro::matrix_t<Number>::Identity(2, 2);
		I2_1(1, 1) = 0;

		center_4 = I2_1 * center_4;
		basis_4 = I2_1 * basis_4;
		hypro::vector_t<Number> temp_4 = basis_4.row( 1 );
		hypro::Halfspace<Number> neg_2 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_4 ), -center_4[1] );
		politope_4 = politope_4.intersectHalfspace( neg_2 );
		hypro::Starset<Number> star_4 = hypro::Starset<Number>( center_4, basis_4, politope_4 );
		plotter.addObject( star_4.vertices(), hypro::plotting::colors[hypro::plotting::petrol] );
		// std::cout << center_4 << std::endl
		// 		  << basis_4 << std::endl
		// 		  << politope_4 << std::endl;

		// x_1 < 0, x_2 >= 0
		hypro::vector_t<Number> center_5 = center_2;
		hypro::matrix_t<Number> basis_5 = basis_2;
		hypro::HPolytope<Number> politope_5 = politope_2;

		hypro::vector_t<Number> temp_5 = basis_5.row( 1 ) * ( -1 );
		hypro::Halfspace<Number> pos_3 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_5 ), center_5[1] );
		politope_5 = politope_5.intersectHalfspace( pos_3 );
		hypro::Starset<Number> star_5 = hypro::Starset<Number>( center_5, basis_5, politope_5 );
		plotter.addObject( star_5.vertices(), hypro::plotting::colors[hypro::plotting::orange] );
		// std::cout << center_5 << std::endl
		// 		  << basis_5 << std::endl
		// 		  << politope_5 << std::endl;

		// x_1 < 0, x_2 < 0
		hypro::vector_t<Number> center_6 = center_2;
		hypro::matrix_t<Number> basis_6 = basis_2;
		hypro::HPolytope<Number> politope_6 = politope_2;

		center_6 = I2_1 * center_6;
		basis_6 = I2_1 * basis_6;
		hypro::vector_t<Number> temp_6 = basis_6.row( 1 );
		hypro::Halfspace<Number> neg_3 = hypro::Halfspace<Number>( hypro::Point<Number>( temp_6 ), -center_6[1] );
		politope_6 = politope_6.intersectHalfspace( neg_3 );
		hypro::Starset<Number> star_6 = hypro::Starset<Number>( center_6, basis_6, politope_6 );
		// plotter.addObject( star_6.vertices(), hypro::plotting::colors[hypro::plotting::bordeaux] );
		plotter.addPoints( star_6.vertices() );
		// std::cout << center_6 << std::endl
		// 		  << basis_6 << std::endl
		// 		  << politope_6 << std::endl;
	}

	// set color and make the plot in 2D
	plotter.plot2d();
}

void test_relu_overapprx() {
	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.filename = "FFReLU_Overapprx";
	settings.fill = true;
	settings.pointSize = 3.0;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );

	// define input file name
	const char* filename = "../examples/nnet/fc_relu.nnet";
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> rotate_nn = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << rotate_nn << std::endl;

	// create an input starset and plot it

	// a simple rectangle: [_]
	// hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	// hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	// hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
	// hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
	// center << 0, 0;
	// basis << 1, 0, 0, 1;
	// constr << 1, 0, -1, 0, 0, 1, 0, -1;
	// limits << 2, 1, 1, 1;

	// a triangle:  |>
	// hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	// hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	// hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 3, 2 );
	// hypro::vector_t<Number> limits = hypro::vector_t<Number>( 3 );\
	// center << 0, 0;
	// basis << 1, 0, 0, 1;
	// constr << -1, 0, 1, 1, 1, -1;
	// limits << 1, 1, 1;

	// another triangle: /_|   (reversed, scaled)
	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 3, 2 );
	hypro::vector_t<Number> limits = hypro::vector_t<Number>( 3 );
	center << 0, 0;
	basis << -2, 0, 0, 1;
	constr << -1, 0, 0, -1, 1, 1;
	limits << 1, 2, 1;

	hypro::Starset<Number> input_star = hypro::Starset<Number>( center, constr, limits, basis );
	plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::red] );

	for ( int i = 0; i < rotate_nn.numLayers(); i++ ) {
		// get layer parameters i
		std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layer_i = rotate_nn.layerParams( i );
		hypro::matrix_t<Number> weights = layer_i.first;
		hypro::vector_t<Number> biases = layer_i.second;

		// apply the affine transformation and plot
		input_star = input_star.affineTransformation( weights, biases );
		plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::green] );
		plotter.plot2d();
		plotter.clear();

		// apply overapproximate ReLU function and plot
		// apply ReLU on x_1

		hypro::vector_t<Number> center = input_star.center();
		hypro::matrix_t<Number> basis = input_star.generator();
		hypro::matrix_t<Number> shape = input_star.shape();
		hypro::vector_t<Number> limits = input_star.limits();

		hypro::vector_t<Number> dir_vect_0 = basis.row(0);
		auto eval_low_result_0 = input_star.constraints().evaluate(-1.0 * dir_vect_0);
		auto eval_high_result_0 = input_star.constraints().evaluate(dir_vect_0);
		// std::cout << dir_vect_0 << std::endl;
		// std::cout << -1.0 * dir_vect_0 << std::endl;
		// std::cout << eval_low_result_0 << std::endl;
		// std::cout << eval_high_result_0 << std::endl;
		// std::cout << eval_low_result_0.supportValue + center[0] << std::endl;
		// std::cout << -eval_high_result_0.supportValue + center[0] << std::endl;
		// return;
		double lb_1 = -eval_low_result_0.supportValue + center[0];
		double ub_1 = eval_high_result_0.supportValue + center[0];
		std::cout << "[lb, ub] = " << "[" << lb_1 << ", " << ub_1 << "]" << std::endl;

		int m = basis.cols();
		m = m + 1;	// the number of variables increases by one

		// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
		shape.conservativeResize( shape.rows() + 3, shape.cols() + 1 );
		shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );	// fill up last column with zeros
		std::cout << "New shape size: (" << shape.rows() << ", " << shape.cols() << ")" << std::endl;
		limits.conservativeResize( limits.rows() + 3 );
		std::cout << "New limits size: (" << limits.rows() << ", " << limits.cols() << ")" << std::endl;

		// first constraint: x3 >= 0
		hypro::vector_t<Number> fst_constr_1 = hypro::vector_t<Number>::Zero( shape.cols() );
		fst_constr_1[fst_constr_1.rows() - 1] = -1;
		shape.row( shape.rows() - 3 ) = fst_constr_1;
		limits[limits.rows() - 3] = 0;

		// second constraint: x3 >= x1
		hypro::vector_t<Number> snd_constr_1 = basis.row( 0 );
		snd_constr_1.conservativeResize( snd_constr_1.rows() + 1 );
		snd_constr_1[snd_constr_1.rows() - 1] = -1;
		shape.row( shape.rows() - 2 ) = snd_constr_1;
		limits[limits.rows() - 2] = -center[0];

		// third constraint: x3 <= ub * (x1 - lb) / (ub - lb)
		hypro::vector_t<Number> trd_constr_1 = basis.row( 0 );
		trd_constr_1 = trd_constr_1 * ( -( ub_1 / ( ub_1 - lb_1 ) ) );
		trd_constr_1.conservativeResize( trd_constr_1.rows() + 1 );
		trd_constr_1( trd_constr_1.rows() - 1 ) = 1;
		shape.row( shape.rows() - 1 ) = trd_constr_1;
		limits[limits.rows() - 1] = ( ub_1 * ( center[0] - lb_1 ) ) / ( ub_1 - lb_1 );


		hypro::matrix_t<Number> I2_0 = hypro::matrix_t<Number>::Identity(2, 2);
		I2_0(0, 0) = 0;

		basis = I2_0 * basis;

		// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( 0, basis.cols() - 1 ) = 1;
		center = I2_0 * center;

		hypro::Starset<Number> star_1 = hypro::Starset<Number>( center, shape, limits, basis );
		std::cout << "Abstract star:" << std::endl
				  << star_1.center() << std::endl
				  << star_1.generator() << std::endl
				  << star_1.shape() << std::endl
				  << star_1.limits() << std::endl;
		plotter.addObject( star_1.vertices(), hypro::plotting::colors[hypro::plotting::orange] );
		plotter.plot2d();
		plotter.clear();

		hypro::vector_t<Number> dir_vect_1 = basis.row(1);
		auto eval_low_result_1 = star_1.constraints().evaluate(-1.0 * dir_vect_1);
		auto eval_high_result_1 = star_1.constraints().evaluate(dir_vect_1);

		double lb_2 = -eval_low_result_1.supportValue + center[1];
		double ub_2 = eval_high_result_1.supportValue + center[1];
		std::cout << "[lb, ub] = " << "[" << lb_2 << ", " << ub_2 << "]" << std::endl;

		m = m + 1;	// the number of variables increases by one

		// Resize the original shape matrix and limits vector, so that they have 3 more constraints and one more variable
		shape.conservativeResize( shape.rows() + 3, shape.cols() + 1 );
		shape.col( shape.cols() - 1 ) = hypro::vector_t<Number>::Zero( shape.rows() );	// fill up last column with zeros
		std::cout << "New shape size: (" << shape.rows() << ", " << shape.cols() << ")" << std::endl;
		limits.conservativeResize( limits.rows() + 3 );
		std::cout << "New limits size: (" << limits.rows() << ", " << limits.cols() << ")" << std::endl;

		// first constraint: x4 >= 0
		hypro::vector_t<Number> fst_constr_2 = hypro::vector_t<Number>::Zero( shape.cols() );
		fst_constr_2[fst_constr_2.rows() - 1] = -1;
		shape.row( shape.rows() - 3 ) = fst_constr_2;
		limits[limits.rows() - 3] = 0;

		// second constraint: x4 >= x2
		hypro::vector_t<Number> snd_constr_2 = basis.row( 1 );
		snd_constr_2.conservativeResize( snd_constr_2.rows() + 1 );
		snd_constr_2[snd_constr_2.rows() - 1] = -1;
		shape.row( shape.rows() - 2 ) = snd_constr_2;
		limits[limits.rows() - 2] = -center[1];

		// third constraint: x3 <= ub * (x1 - lb) / (ub - lb)
		hypro::vector_t<Number> trd_constr_3 = basis.row( 1 );
		trd_constr_3 = trd_constr_3 * ( -( ub_2 / ( ub_2 - lb_2 ) ) );
		trd_constr_3.conservativeResize( trd_constr_3.rows() + 1 );
		trd_constr_3( trd_constr_3.rows() - 1 ) = 1;
		shape.row( shape.rows() - 1 ) = trd_constr_3;
		limits[limits.rows() - 1] = ( ub_2 * ( center[1] - lb_2 ) ) / ( ub_2 - lb_2 );

		hypro::matrix_t<Number> I2_1 = hypro::matrix_t<Number>::Identity(2, 2);
		I2_1(1, 1) = 0;

		basis = I2_1 * basis;

		// extend the basis with the standard basis vector as last column and set the actual basis vector to the null-vector
		basis.conservativeResize( basis.rows(), basis.cols() + 1 );
		basis.col( basis.cols() - 1 ) = hypro::vector_t<Number>::Zero( basis.rows() );
		basis( 1, basis.cols() - 1 ) = 1;
		center = I2_1 * center;

		hypro::Starset<Number> star_2 = hypro::Starset<Number>( center, shape, limits, basis );
		std::cout << "Abstract star:" << std::endl
				  << star_2.center() << std::endl
				  << star_2.generator() << std::endl
				  << star_2.shape() << std::endl
				  << star_2.limits() << std::endl;
		plotter.addObject( star_2.vertices(), hypro::plotting::colors[hypro::plotting::bordeaux] );
	}

	// set color and make the plot in 2D
	plotter.plot2d();
}

void test_ACAS_property_4(int argc, char* argv[]) {
	// define input file name
	const char* filename = "../examples/nnet/acasxu/ACASXU_experimental_v2a_2_6.nnet";
	if(argc > 1)
		filename = argv[1];
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> acas_nn = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << acas_nn << std::endl;

	hypro::vector_t<Number> inputs = hypro::vector_t<Number>(5);
	inputs << 1600, 0, 0, 1100, 750;
	std::cout << "Input vector: " << inputs << std::endl;

	bool normalizeInput = true;
	bool normalizeOutput = true;
	hypro::vector_t<Number> outputs = acas_nn.evaluateNetwork(inputs, normalizeInput, normalizeOutput);
	std::cout << "Output vector: " << outputs << std::endl;
}

int main( int argc, char* argv[] ) {
	auto start = std::chrono::steady_clock::now();
	// test_network_read();
	// test_acas_xu();
	// test_network_plot();
	// test_relu_exact();
	// test_relu_overapprx();
	test_ACAS_property_4(argc, argv);
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during executing the program: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	return 0;
}
