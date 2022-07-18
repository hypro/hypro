#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/parser/NNet.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

// use floating point arithmetic.
typedef double Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {
	std::cout << "\nSystem arguments: ";
	for ( int i = 0; i < argc; i++ ) {
		std::cout << argv[i] << " ";
	}
	std::cout << "\n\n";

	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.name = "Reachability analysis of FFNN with ReLU activation function";
	settings.filename = "FFNN_ReLU_reach";
	settings.fill = true;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;
	settings.xPlotInterval = carl::Interval<double>( -2.2, +2.2 );
	settings.yPlotInterval = carl::Interval<double>( -2.2, +2.2 );
	// settings.overwriteFiles = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );
	plotter.clear();

	// define the reachability method
	hypro::NN_REACH_METHOD method = hypro::NN_REACH_METHOD::CEGAR;
	if ( argc > 1 ) {
		switch ( argv[1][0] ) {
			case 'c':
			case 'C':
				method = hypro::NN_REACH_METHOD::CEGAR;
				break;
			case 'e':
			case 'E':
				method = hypro::NN_REACH_METHOD::EXACT;
				break;
			case 'o':
			case 'O':
				method = hypro::NN_REACH_METHOD::OVERAPPRX;
				break;
			default:
				method = hypro::NN_REACH_METHOD::CEGAR;
		}
	}

	// define input file name
	const char* filename = "../examples/nnet/fc_2-2-2.nnet";
	if ( argc > 2 )
		filename = argv[2];
	std::cout << "Filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> rotate_nn = hypro::NNet<Number>( filename );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	// std::cout << rotate_nn << std::endl;

	hypro::NeuralNetwork<Number> network = hypro::NeuralNetwork<Number>( rotate_nn );
	std::cout << network << std::endl;

	// a simple rectangle [_]
	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
	center << 0, 0;
	basis << 1, 0, 0, 1;
	constr << 1, 0, -1, 0, 0, 1, 0, -1;
	limits << 2, 1, 1, 1;
	hypro::Starset<Number> input_star = hypro::Starset<Number>( center, constr, limits, basis );
	if ( argc > 3 ) {
		std::cout << "Reading input star from: " << argv[3] << std::endl;
		input_star = hypro::Starset<Number>::readFromFile( argv[3] );
	}
	std::cout << input_star << std::endl;

	hypro::vector_t<Number> center2 = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis2 = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> constr2 = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits2 = hypro::vector_t<Number>( 4 );
	center2 << 0, 0;
	basis2 << 1, 0, 0, 1;
	constr2 << 1, 0, -1, 0, 0, 1, 0, -1;
	limits2 << 0.5, 0, 1, 0;
	hypro::Starset<Number> safe_star = hypro::Starset<Number>( center2, constr2, limits2, basis2 );
	if ( argc > 4 ) {
		std::cout << "Reading safety specification from: " << argv[4] << std::endl;
		safe_star = hypro::Starset<Number>::readFromFile( argv[4] );
	}
	std::cout << safe_star << std::endl;

	hypro::reachability::ReachNN<Number> reach_nn = hypro::reachability::ReachNN<Number>( rotate_nn );
	hypro::reachability::ReachabilityTree<Number> reach_tree( network, input_star.constraints(), safe_star.constraints() );

	bool create_plots = false;

	start = std::chrono::steady_clock::now();
	// std::vector<hypro::Starset<Number>> output_set = reach_nn.forwardAnalysis( input_star, method, create_plots );	// old verification implemented for NNet
	// std::vector<hypro::Starset<Number>> output_set = network.forwardPass( input_star, method, create_plots); // new method implemented for general Neural Network wrapper class
	// std::vector<hypro::Starset<Number>> output_set = reach_tree.forwardPass(method, hypro::SEARCH_STRATEGY::DFS);
	bool isSafe = reach_tree.verify( method, hypro::SEARCH_STRATEGY::DFS );
	end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during NN reachability analysis: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;

	// // verificaton (and plotting) of the output sets
	// int N = output_set.size();
	// std::cout << "Number of final stars: " << N << std::endl;
	// int num_not_satisfied = 0;
	// for ( int i = 0; i < N; i++ ) {
	// 	// std::cout << output_set[i] << std::endl;
	// 	std::vector<hypro::Point<Number>> vertices = output_set[i].vertices();
	// 	// std::cout << "Vertices: " << vertices << std::endl;
	// 	plotter.addObject( vertices, hypro::plotting::colors[( 2 * i ) % 9] );

	// 	hypro::vector_t<Number> center = output_set[i].center();
	// 	hypro::matrix_t<Number> basis = output_set[i].generator();
	// 	hypro::matrix_t<Number> shape = output_set[i].shape();
	// 	hypro::matrix_t<Number> limits = output_set[i].limits();

	// 	for ( int j = 1; j < output_set[i].dimension(); j++ ) {
	// 		// std::cout << "Checking output safety constraint: " << j << std::endl;

	// 		shape.conservativeResize( shape.rows() + 1, shape.cols() );
	// 		limits.conservativeResize( limits.rows() + 1, 1 );

	// 		shape.row( shape.rows() - 1 ) = basis.row( 0 ) - basis.row( j );
	// 		limits.row( limits.rows() - 1 ) = center.row( j ) - center.row( 0 );
	// 	}

	// 	hypro::Starset<Number> new_star = hypro::Starset<Number>( center, shape, limits, basis );
	// 	// std::cout << "Checking emptiness" << std::endl;
	// 	if ( new_star.empty() ) {
	// 		// std::cout << "Star number " << i << " satisfied property 4" << std::endl;

	// 		// std::cout << output_set[i] << std::endl;
	// 		// std::vector<hypro::Point<Number>> vertices = output_set[i].vertices();
	// 		// std::cout << "Vertices: " << vertices << std::endl;
	// 	} else {
	// 		std::cout << "Star number " << i << " violates the property" << std::endl;

	// 		// std::cout << output_set[i] << std::endl;
	// 		// std::vector<hypro::Point<Number>> vertices = output_set[i].vertices();
	// 		// std::cout << "Vertices: " << vertices << std::endl;

	// 		// std::cout << "The new star: " << std::endl;
	// 		// std::cout << new_star << std::endl;
	// 		// std::cout << "New star vertices: " << new_star.vertices() << std::endl;

	// 		// std::vector<hypro::Point<Number>> inner_vertices = new_star.constraints().vertices();
	// 		// hypro::vector_t<Number> new_center = new_star.center();
	// 		// hypro::matrix_t<Number> new_basis = new_star.generator();

	// 		// for( auto point : inner_vertices ) {
	// 		// 	std::cout << "Inner point: " << point << std::endl;
	// 		// 	hypro::Point<Number> star_point = point.affineTransformation(new_basis, new_center);
	// 		// 	std::cout << "One new point: " << star_point << std::endl;
	// 		// }

	// 		num_not_satisfied++;
	// 	}
	// }

	// std::cout << std::fixed;
	// std::cout << std::setprecision( 2 );
	// std::cout << "In total " << ( ( (double)num_not_satisfied / N ) * 100.0 ) << "\% of stars violates the property." << std::endl;

	// plotter.addObject( safe_star.vertices(), hypro::plotting::colors[hypro::plotting::bordeaux] );
	// plotter.plot2d();

	std::cout << "Program finished successfully." << std::endl;

	return 0;
}
