#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

typedef mpq_class Number;

using namespace hypro;

int main( int argc, char* argv[] ) {
	std::cout << "\nSystem arguments: ";
	for ( int i = 0; i < argc; i++ ) {
		std::cout << argv[i] << " ";
	}
	std::cout << "\n\n";

    // define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.name = "Reachability analysis of thermostat benchmark";
	settings.filename = "FNN_Reach";
	settings.fill = true;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;
	settings.xPlotInterval = carl::Interval<double>( -15, 25 );
	settings.yPlotInterval = carl::Interval<double>( -2, 2 );
	// settings.overwriteFiles = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );
	plotter.clear();

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
	std::cout << "The reachability method is " << method._to_string() << std::endl;

	// Define NN input file name
	const char* filename;
	if ( argc > 2 ){
        filename = argv[2];
    } else {
        std::cout << "Expected a file location for the FNN. Aborting..." << std::endl;
        return -1;
    }
		
	std::cout << "NN input filename is: " << filename << std::endl;

	// Read and build neural network
	hypro::NNet<Number> nn_NNet = hypro::NNet<Number>( filename );    
	hypro::NeuralNetwork<Number> neuralNetwork = hypro::NeuralNetwork<Number>( nn_NNet );
	//append hard sigmoid layer
	neuralNetwork.appendLayer(std::make_shared<hypro::HardSigmoidLayer<Number>>(1, 3, -2.5, 2.5));
	//append step function layer
    neuralNetwork.appendLayer(std::make_shared<hypro::StepFunctionLayer<Number>>(1, 4, 0.5, 0, 1));

    std::cout << neuralNetwork << std::endl;
	
	// Thermostat verification using an input poly which represent temperature and control mode
	hypro::HPolytope<Number> inputPoly;
	std::string prop_name;
	if ( argc > 3 ) {
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		prop_name = std::string(argv[3]);
		assert((prop_name[prop_name.size() - 4] == 'M') ||  (prop_name[prop_name.size() - 4] == 'R'));
		inputPoly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	} else {
        std::cout << "Expected a file location for the input polytope. Aborting..." << std::endl;
        return -1;
    }
	std::cout << "The input polytope:\n" << inputPoly << std::endl;

    // Extract the safety specification
    int safeValue = prop_name[prop_name.size() - 4] == 'M' ? 0 : 1; 
    std::vector<hypro::HPolytope<Number>> safePoly = std::vector<hypro::HPolytope<Number>>();
    matrix_t<Number> C(2,1);
    C << 1,-1;
    vector_t<Number> d(2);
    d << safeValue,-safeValue;
    safePoly.push_back(HPolytope<Number>(C,d));
	std::cout << "The disjunction of safe polytopes:\n" << safePoly << std::endl;

    // Settings for verification
	hypro::COUNTEREXAMPLE_STRATEGY counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::Z3_BASIC;
	hypro::REFINEMENT_TYPE refinementType = hypro::REFINEMENT_TYPE::EXACT_SOURCES;							  // FULL , AVOIDANT, EXACT_SOURCES
	hypro::BACKPROPAGATION_STRATEGY backpropagationStrategy = hypro::BACKPROPAGATION_STRATEGY::BINARYSEARCH;  // SINGLESTEP, BINARYSEARCH, REMEMBERING_SEARCH, 
	hypro::reachability::ReachabilityTree NNtree = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly, counterExampleStrategy, refinementType, backpropagationStrategy );
	bool create_plots = !true;
	bool normalize_input = true;
	bool normalize_output = true;

    // Verify
	auto start = std::chrono::steady_clock::now();
	bool isSafe = NNtree.verify( method, hypro::SEARCH_STRATEGY::BFS, create_plots, normalize_input, normalize_output );
	auto end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during NN reachability analysis: " << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
    
    return 0;
}
