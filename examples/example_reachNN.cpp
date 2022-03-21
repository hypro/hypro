#include "hypro/neuralnets/parser/NNet.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <iostream>
#include <vector>

// use rational arithmetic.
typedef double Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {	
	std::cout << "System arguments: ";
	for(int i = 0; i < argc; i++) {
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;

	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.name = "Reachability analysis of FFNN with ReLU activation function";
	settings.filename = "FFNN_ReLU_reach";
	settings.fill = true;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;
	settings.xPlotInterval = carl::Interval<double>(-2.2, +2.2);
	settings.yPlotInterval = carl::Interval<double>(-2.2, +2.2);
	// settings.overwriteFiles = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );
	plotter.clear();

	// define input file name
	const char* filename = "../examples/nnet/fc_relu.nnet";
	if(argc > 2)
		filename = argv[2];
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> rotate_nn = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << rotate_nn << std::endl;

	// a simple rectangle [_]
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
	// hypro::vector_t<Number> limits = hypro::vector_t<Number>( 3 );
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
	if(argc > 3) {
		std::cout << "Reading input star from: " << argv[3] << std::endl;
		input_star = hypro::Starset<Number>::readFromFile(argv[3]);
	}
	std::cout << input_star << std::endl;
	// plotter.addObject( input_star.vertices(), hypro::plotting::colors[hypro::plotting::red] );
	// plotter.plot2d();
	// plotter.clear();

	hypro::reachability::NN_reach_method method = hypro::reachability::NN_reach_method::EXACT;
	if(argc > 1 && (argv[1][0] == 'o' || argv[1][0] == 'O'))
		method = hypro::reachability::NN_reach_method::OVERAPPRX;
		
	hypro::reachability::ReachNN<Number> reach_nn = hypro::reachability::ReachNN<Number>( rotate_nn );
	std::vector<hypro::Starset<Number>> output_set = reach_nn.forwardAnalysis( input_star, method, false );

	int N = output_set.size();
	for ( int i = 0; i < N; i++ ) {
		// std::cout << output_set[i] << std::endl;
		// std::vector<hypro::Point<Number>> vertices = output_set[i].vertices();
		// std::cout << "Vertices: " << vertices << std::endl;
		// plotter.addObject( vertices, hypro::plotting::colors[(2 * i) % 9] );
		bool COC_is_not_minimal = true;
		for ( int j = 1; j < output_set[i].dimension(); j++) {
			// std::cout << "Checking output safety constraint: " << j << std::endl;
			hypro::vector_t<Number> center = output_set[i].center();
			hypro::matrix_t<Number> basis = output_set[i].generator();
			hypro::matrix_t<Number> shape = output_set[i].shape();
			hypro::matrix_t<Number> limits = output_set[i].limits();

			shape.conservativeResize(shape.rows() + 1, shape.cols());
			limits.conservativeResize(limits.rows() + 1, 1);

			shape.row(shape.rows() - 1) = basis.row(0) - basis.row(j);
			limits.row(limits.rows() - 1) = center.row(j) - center.row(0);

			hypro::Starset<Number> new_star = hypro::Starset<Number>(center, shape, limits, basis);
			// std::cout << "Checking emptiness" << std::endl;
			if(new_star.empty()) {
				COC_is_not_minimal = false;
				break;
			}

			// hypro::vector_t<Number> normal_vect = hypro::vector_t<Number>::Zero(output_set[i].dimension());
			// normal_vect[0] = -1;
			// normal_vect[i] = +1;
			// Number offset = 0;
			// hypro::Halfspace<Number> constraint_part = hypro::Halfspace<Number>(hypro::Point<Number>(normal_vect), offset);
			// if(output_set[i].satisfiesHalfspace(constraint_part).first == hypro::CONTAINMENT::FULL) {
			// 	COC_is_not_minimal = true;
			// 	break;
			// }
		}
		if(COC_is_not_minimal) {
			std::cout << "Star number " << i << " satisfied property 3 (4)" << std::endl;
		} else {
			std::cout << "Star number " << i << "does not satisfy property 3 (4)" << std::endl;
		}
	}
	// plotter.plot2d();

	return 0;
}
