#include "hypro/datastructures/Point.h"
#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/representations/GeometricObjectBase.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

typedef double Number;

int main( int argc, char* argv[] ) {
	// Find the input network file names
	std::vector<std::string> filenames;
	const fs::path path{"../examples/nn_benchmarks/networks/nnet/custom"};
	for ( auto const& entry : fs::directory_iterator{ path } ) {
		filenames.push_back( entry.path() );
	}
	std::sort(filenames.begin(), filenames.end(), [](std::string a, std::string b){return a.size() < b.size() || (a.size() == b.size() && a < b);});

	// read the input properties
	std::vector<hypro::vector_t<Number>> inputs;
	std::ifstream inputFile( "inputs.txt" );
	std::string line;
	for (int i = 0; std::getline( inputFile, line ); i++ ) {
		line = line.substr( line.find( ":" ) + 1, line.size() );
		char* val = std::strtok( line.data(), "," );
		std::vector<Number> myVec;
		while ( val != NULL ) {
			myVec.push_back(carl::convert<double, Number>( std::atof( val ) ));
			val = std::strtok( NULL, "," );
		}
		inputs.push_back( hypro::vector_t<Number>(myVec.size()) );
		for (int j = 0; j < myVec.size(); j++){
			inputs[i](j) = myVec[j];
		}
	}
	inputFile.close();

	assert(inputs.size() == filenames.size());

	for( int i = 0; i < filenames.size(); i++){
		std::cout << filenames[i] << ":";
		// Read and build neural network
		hypro::NNet<Number> nn_NNet = hypro::NNet<Number>( filenames[i].c_str() );
		hypro::NeuralNetwork<Number> neuralNetwork = hypro::NeuralNetwork<Number>( nn_NNet );

		// apply forwardpass method
		hypro::vector_t<Number> output = neuralNetwork.forwardPass( inputs[i], false, false );
		for (int j = 0; j < output.size(); j++)
			std::cout << output[j] << (j != output.size() - 1 ? ", " : "" );
		std::cout << std::endl;
	}
}
