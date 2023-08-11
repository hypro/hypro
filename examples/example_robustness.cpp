#include "hypro/datastructures/Point.h"
#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/representations/Starset/Starset.h"
#include "hypro/representations/sampling/sampling.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

typedef double Number;

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

	// read an input property
	hypro::HPolytope<Number> inputPoly;
	if ( argc > 3 ) {
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		inputPoly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	}
	std::cout << "The input property:\n"
			  << inputPoly << std::endl;

	// apply forwardpass method + measure the time
	auto start = std::chrono::steady_clock::now();
	std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( hypro::Starset<Number>( inputPoly ) , method, false );




	std::shared_ptr<hypro::LayerBase<Number>> layer1 = std::make_shared<hypro::HardSigmoidLayer<Number>>( 1, 0, -3, 3 );
	auto result1 = layer1->forwardPass( output, method, false );


	auto end = std::chrono::steady_clock::now();
	auto analysisTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	std::cout << "Total time elapsed during NN reachability analysis: " << analysisTime << " ms" << std::endl;


	// for ( const auto& o : output ) {
	// 	std::cout << "Vertices before hardsigmoid: " << o.vertices() << std::endl;
	// }

	// for ( const auto& o : result1 ) {
	// 	std::cout << "Vertices after hardsigmoid: " << o.vertices() << std::endl;
	// }

	std::shared_ptr<hypro::LayerBase<Number>> layer2 = std::make_shared<hypro::StepFunctionLayer<Number>>( 1, 0, 0.5, 0, 1 );
	auto result2 = layer2->forwardPass( result1, hypro::NN_REACH_METHOD::EXACT, false );

	for ( const auto& o : result2 ) {
		std::cout << "Classification result: " << (iszero(o.vertices()[0][0]) ? "ROCK" : "MINE") << std::endl;
	}
}
