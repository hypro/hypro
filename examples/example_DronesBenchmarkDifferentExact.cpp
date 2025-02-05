#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/neuralnets/reachability_tree/ReachabilitySettings.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

// use exact arithmetic.
typedef mpq_class Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {
	// print system arguments
	std::cout << "\nSystem arguments: ";
	for ( int i = 0; i < argc; i++ ) {
		std::cout << argv[i] << " ";
	}
	std::cout << "\n\n";

	// define the reachability method
	hypro::NN_REACH_METHOD method = hypro::NN_REACH_METHOD::CEGAR;
	
	// define input file name
	const char* filename = "../examples/nn_benchmarks/networks/nnet/drones/AC3.nnet";

	// read and build neural network + time measurement
	auto start = std::chrono::steady_clock::now();
	hypro::NNet<Number> nnet = hypro::NNet<Number>( filename );
	// std::cout << nnet << std::endl;

	hypro::NeuralNetwork<Number> neuralNetwork = hypro::NeuralNetwork<Number>( nnet );
	std::cout << neuralNetwork << std::endl;
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during building the network: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	
	// input poly
    filename = "../examples/nn_benchmarks/properties/drones/properties/prop_AC3_02.in";
	hypro::HPolytope<Number> inputPoly  = hypro::readHpolytopeFromFile<Number>( filename );
	std::cout << "The input polytope:\n" << inputPoly << std::endl;

    // safety specification
    filename = "../examples/nn_benchmarks/properties/drones/safe_sets/safe_AC3_02.in";
	std::vector<hypro::HPolytope<Number>> safePoly = hypro::readKHpolytopesFromFile<Number>( filename );
	std::cout << "The disjunction of safe polytopes:\n" << safePoly << std::endl;

	// Transform input and safe polytopes to star set
	hypro::COUNTEREXAMPLE_STRATEGY counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::Z3_BASIC;
	hypro::REFINEMENT_TYPE refinementType = hypro::REFINEMENT_TYPE::AVOIDANT;
	hypro::BACKPROPAGATION_STRATEGY backpropagationStrategy = hypro::BACKPROPAGATION_STRATEGY::EXACT_SOURCES;
	bool create_plots = !true;
    bool normalize_input = true;
    bool normalize_output = true;

    for (int i : {80,86,126}){
		hypro::reachability::ReachabilityTree NNtree = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly , counterExampleStrategy, refinementType, backpropagationStrategy);
		// std::ofstream file;
		// file.open("tmp.txt", std::ios_base::app);
		// file << i << " ";
		// file.close();
		NNtree.rememberCounterexampleSource(1,i);
		start = std::chrono::steady_clock::now();
		bool isSafe = NNtree.verify( method, hypro::SEARCH_STRATEGY::DFS, create_plots, normalize_input, normalize_output, 100 );
		end = std::chrono::steady_clock::now();
		std::cout << "Total time elapsed during NN reachability analysis: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;

		std::cout << "Program finished successfully." << std::endl;
	}

	for (int i : {10,25,28}){
		hypro::reachability::ReachabilityTree NNtree = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly , counterExampleStrategy, refinementType, backpropagationStrategy);
		std::ofstream file;
		// file.open("tmp.txt", std::ios_base::app);
		// file << i << " ";
		// file.close();
		NNtree.rememberCounterexampleSource(3,i);
		start = std::chrono::steady_clock::now();
		bool isSafe = NNtree.verify( method, hypro::SEARCH_STRATEGY::DFS, create_plots, normalize_input, normalize_output, 100 );
		end = std::chrono::steady_clock::now();
		std::cout << "Total time elapsed during NN reachability analysis: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;

		std::cout << "Program finished successfully." << std::endl;
	}


	

	return 0;
}
