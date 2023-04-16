#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/parser/representations/parseHPolytope.tpp"

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

	/*
	// read an input vector
	auto inputVector = hypro::vector_t<Number>(2);
	Number inputTemp;
	Number inputControll;
	if ( argc > 3 ) {
		inputTemp = atoi( argv[3] );
	}
	if ( argc > 4 ) {
		inputControll = atoi( argv[4] );
	}
	inputVector << inputTemp, inputControll;
	std::cout << "The input value: " << inputVector << std::endl;

	// apply forwardpass method + measure the time
	auto start = std::chrono::steady_clock::now();
	hypro::vector_t<Number> output = neuralNetwork.forwardPass( inputVector );
	auto end = std::chrono::steady_clock::now();
	auto analysisTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	std::cout << "Total time elapsed during NN reachability analysis: " << analysisTime << " ms" << std::endl;

	std::cout << "Value before stepfunction: " << output << std::endl;

	std::shared_ptr<hypro::LayerBase<Number>> layer = std::make_shared<hypro::StepFunctionLayer<Number>>( 1, 0, 7.5, 0, 15 );
	auto result = layer->forwardPass( output );

	std::cout << "Output value: " << result << std::endl;

	if ( ( result.array() == 0.0 ).any() ) {
		std::cout << "OFF" << std::endl;
	} else {
		std::cout << "ON" << std::endl;
	}

	*/
	// read an input set
	hypro::HPolytope<Number> inputPoly;
	if ( argc > 3 ) {
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		inputPoly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	}
	std::cout << "The input polytope:\n"
			  << inputPoly << std::endl;

	auto start = std::chrono::steady_clock::now();
	std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( hypro::Starset<Number>( inputPoly ), method, false );
	auto end = std::chrono::steady_clock::now();
	auto analysisTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	std::cout << "Total time elapsed during NN reachability analysis: " << analysisTime << " ms" << std::endl;

	std::shared_ptr<hypro::LayerBase<Number>> layer = std::make_shared<hypro::StepFunctionLayer<Number>>( 2, 0, 7.5, 2, 15 );
	auto result = layer->forwardPass( output, method, false );

	for ( const auto& o : output ) {
		std::cout << "Output before stepfunction: " << o << std::endl;
		std::cout << "Vertices before stepfunction: " << o.vertices() << std::endl;
	}

	for ( const auto& o : result ) {
		std::cout << "Output after stepfunction: " << o << std::endl;
		std::cout << "Vertices after stepfunction: " << o.vertices() << std::endl;
	}
}
