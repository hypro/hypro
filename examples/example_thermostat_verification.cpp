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
	std::shared_ptr<hypro::LayerBase<Number>> stepFunLayer = std::make_shared<hypro::StepFunctionLayer<Number>>( 1, 0, 7.5, 0, 15 );

	/*
	// Thermostat verification using an input temperature and control mode
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

	// Thermostat verification using an input poly which represent temperature and control mode
	// read an input set
	hypro::HPolytope<Number> inputPoly;
	if ( argc > 3 ) {
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		inputPoly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	}
	std::cout << "The input polytope:\n"
			  << inputPoly << std::endl;

	hypro::Starset<Number> inputStar(inputPoly);

	std::vector<hypro::HPolytope<Number>> safePoly = std::vector<hypro::HPolytope<Number>>();
	if ( argc > 4 ) {
		std::cout << "Reading safety specification from: " << argv[4] << std::endl;
		safePoly = hypro::readKHpolytopesFromFile<Number>( argv[4] );
	}
	std::cout << "The disjunction of safe polytopes:\n"
			  << safePoly << std::endl;

	// apply forwardpass method + measure the time
	auto start = std::chrono::steady_clock::now();
	std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( inputStar, method, false );

	// apply stepFunction to the output of forwardPass
	auto result = stepFunLayer->forwardPass( output, method, false );

	auto end = std::chrono::steady_clock::now();
	auto analysisTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	std::cout << "Total time elapsed during NN reachability analysis: " << analysisTime << " ms" << std::endl;

	// Checking safety of the reachable sets
	bool safe = true;
	for ( const auto& o : result ) {
		// std::cout << "Output set: " << o << std::endl;
		// std::cout << "Is empty: " << o.empty() << std::endl;
		for ( const auto& v : o.vertices() ) {
			std::cout << "Vertex is: " << v << std::endl;
			std::cout << "Contained in safe set: " << safePoly[0].contains(v) << std::endl;
			safe &= safePoly[0].contains(v);
		} 
	}

	std::cout << "Network is safe: " << (safe ? "true" : "false") << std::endl;

	if ( !safe && method == hypro::NN_REACH_METHOD::EXACT){
		// counter example
		std::vector<hypro::Starset<Number>> counterSet;
		auto inputCenter = hypro::Starset<Number>( inputPoly ).center();
		auto inputBasis = hypro::Starset<Number>( inputPoly ).generator();
		for ( auto o : result ) {
			for ( const auto& v : o.vertices() ) {
				if ( !safePoly[0].contains(v) ) {
					o.setCenter( inputCenter );
					o.setGenerators( inputBasis );
					counterSet.push_back( o );
				}
			}
		}

		std::cout << "\nCounterexamples: " << std::endl << std::endl;
		for ( int i = 0; i < counterSet.size(); i++ ) {
			std::cout << "Counter-set " << i << std::endl;
			auto pointSet = uniform_sampling( counterSet[i], 1 );
			if (pointSet.empty()) continue;
			auto point = *pointSet.begin();
			auto pointVector = hypro::vector_t<Number>( 2 );
			pointVector << point.coordinate( 0 ), point.coordinate( 1 );

			hypro::vector_t<Number> counterExample = neuralNetwork.forwardPass( pointVector );
			// std::cout << "Value before stepfunction: " << counterExample << std::endl;

			auto resultSF = stepFunLayer->forwardPass( counterExample );

			std::cout << "Counter example candidate: \n" << pointVector;
			std::cout << "Output value: " << resultSF << std::endl;
		}

		/*
		// take only one counter example of the counterSet
		std::set<hypro::Point<Number>> x = uniform_sampling( counterSet.at( 0 ), 1 );

		auto point = *x.begin();
		auto inputVector = hypro::vector_t<Number>( 2 );
		inputVector << point.coordinate( 0 ), point.coordinate( 1 );

		hypro::vector_t<Number> counterExample = neuralNetwork.forwardPass( inputVector );
		std::cout << "Value before stepfunction: " << counterOutput << std::endl;

		std::shared_ptr<hypro::LayerBase<Number>> layerSF = std::make_shared<hypro::StepFunctionLayer<Number>>( 1, 0, 7.5, 0, 15 );
		auto resultSF = layer->forwardPass( counterOutput );

		std::cout << "Output value: " << result SF<< std::endl;
		*/
	}
}
