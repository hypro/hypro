#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

// Custom square root function for mpq_class numbers
mpq_class sqrt(const mpq_class& x) {
    mpf_class x_mpf(x); // Convert mpq_class to mpf_class
    mpf_sqrt(x_mpf.get_mpf_t(), x_mpf.get_mpf_t()); // Compute square root
    return mpq_class(x_mpf); // Convert back to mpq_class
}

// use exact arithmetic.
typedef mpq_class Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {
	// print system arguments
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
	std::cout << "The reachability method is " << method._to_string() << std::endl
			  << std::endl;

	// define input file name
	const char* filename = "../examples/nnet/fc_2-2-2.nnet";
	if ( argc > 2 )
		filename = argv[2];
	std::cout << "NN input filename is: " << filename << std::endl;

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> nnet = hypro::NNet<Number>( filename );
	// std::cout << nnet << std::endl;

	hypro::NeuralNetwork<Number> neuralNetwork = hypro::NeuralNetwork<Number>( nnet );
	std::cout << neuralNetwork << std::endl;
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	
	// a simple rectangle [_]
	hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
	constr << 1, 0, -1, 0, 0, 1, 0, -1;
	limits << 2, 1, 1, 1;
	hypro::HPolytope<Number> inputPoly = hypro::HPolytope<Number>( constr, limits );
	if ( argc > 3 ) {
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		inputPoly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	}
	std::cout << "The input polytope:\n" << inputPoly << std::endl;

	hypro::matrix_t<Number> constr2 = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits2 = hypro::vector_t<Number>( 4 );
	constr2 << 1, 0, -1, 0, 0, 1, 0, -1;
	limits2 << 0.5, 0, 1, 0;
	std::vector<hypro::HPolytope<Number>> safePoly = std::vector<hypro::HPolytope<Number>>();
	if ( argc > 4 ) {
		std::cout << "Reading safety specification from: " << argv[4] << std::endl;
		safePoly = hypro::readKHpolytopesFromFile<Number>( argv[4] );
	} else {
		safePoly.push_back( hypro::HPolytope<Number>( constr2, limits2 ) );
	}
	std::cout << "The disjunction of safe polytopes:\n" << safePoly << std::endl;

	// Transform input and safe polytopes to star set
	hypro::reachability::ReachabilityTree NNtree = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly );
	bool create_plots = false;
    bool normalize_input = true;
    bool normalize_output = true;

	start = std::chrono::steady_clock::now();
    bool isSafe = NNtree.verify( method, hypro::SEARCH_STRATEGY::DFS, create_plots, normalize_input, normalize_output );
	end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during NN reachability analysis: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;

	std::cout << "Program finished successfully." << std::endl;

	return 0;
}
