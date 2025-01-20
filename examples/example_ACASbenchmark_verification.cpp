#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
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

	// Define the reachability method
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

	// Define NN input file name
	const char* filename;
	if ( argc > 2 )
		filename = argv[2];
	std::cout << "NN input filename is: " << filename << std::endl;

	// Read and build neural network
	hypro::NNet<Number> nn_NNet = hypro::NNet<Number>( filename );
	hypro::NeuralNetwork<Number> neuralNetwork = hypro::NeuralNetwork<Number>( nn_NNet );

	// Read input polytope
	hypro::HPolytope<Number> inputPoly;
	if ( argc > 3 ) {
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		inputPoly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	}
	std::cout << "The input polytope:\n"
			  << inputPoly << std::endl;

	// Read safe input
	std::vector<hypro::HPolytope<Number>> safePoly = std::vector<hypro::HPolytope<Number>>();
	if ( argc > 4 ) {
		std::cout << "Reading safety specification from: " << argv[4] << std::endl;
		safePoly = hypro::readKHpolytopesFromFile<Number>( argv[4] );
	}
	std::cout << "The disjunction of safe polytopes:\n"
			  << safePoly << std::endl;

	// Transform input and safe polytopes to star set
	hypro::reachability::ReachabilityTree NNtree = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly );
	hypro::Starset<Number> input_starset = NNtree.prepareInput( true );
	std::cout << "Normalized input set: " << input_starset << std::endl;
	std::vector<hypro::HPolytope<Number>> safe_set = NNtree.prepareSafeSet( true );
	std::cout << "Normalized safe set: " << safe_set << std::endl;

	if ( argc > 5 && std::string(argv[5]) == "unbounded") {
		std::cout << "Removing upper bound on ownship speed..." << std::endl;
		hypro::matrix_t<Number> shape = input_starset.shape();
		hypro::vector_t<Number> limits = input_starset.limits();
		shape.conservativeResize(shape.rows() - 1, shape.cols());
		limits.conservativeResize(limits.rows() - 1);
		input_starset = hypro::Starset<Number>(input_starset.center(), shape, limits, input_starset.generator());
		std::cout << "Done" << std::endl;
		std::cout << "New unbounded star set: " << input_starset << std::endl;
		std::cout << "Set is empty: " << input_starset.empty() << std::endl;
	}

	// Apply the reachability analysis to the input star set and measure the required time
	auto start = std::chrono::steady_clock::now();
	std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( input_starset, method, false );
	// std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( unbounded_input_starset, method, false );
	auto end = std::chrono::steady_clock::now();
	auto analysisTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	std::cout << "Reachability Analysis Time (ms): " << analysisTime << std::endl;

	// Check if all output star set is safe, e.g. if it is contained in the safe zone
	start = std::chrono::steady_clock::now();
	bool all_safe = true;
	for ( int k = 0; k < output.size(); k++ ) {
		hypro::reachability::ReachabilityNode node = hypro::reachability::ReachabilityNode<Number>( output[k], method, 0, 0 );
		bool isCurrentSafe = node.checkSafeRecursive( output[k], 0, safe_set );
		all_safe &= isCurrentSafe;
	}
	end = std::chrono::steady_clock::now();
	std::cout << std::boolalpha;
	std::cout << "Reachable Set is Safe: " << all_safe << std::endl;
	auto safetyCheckTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	std::cout << "Safety Check Time (ms): " << safetyCheckTime << std::endl;

	std::cout << "Total Time (ms): " << analysisTime + safetyCheckTime << std::endl;
	std::cout << "Number of Output Star Sets: " << output.size() << std::endl;
}
