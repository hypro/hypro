#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability_tree/ReachabilitySettings.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// Custom square root function for mpq_class numbers
mpq_class sqrt( const mpq_class& x ) {
	mpf_class x_mpf( x );							   // Convert mpq_class to mpf_class
	mpf_sqrt( x_mpf.get_mpf_t(), x_mpf.get_mpf_t() );  // Compute square root
	return mpq_class( x_mpf );						   // Convert back to mpq_class
}

// use exact arithmetic.
typedef mpq_class Number;  // -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {
	// printing benchmark outputs to file
	ofstream outfile;
	if ( argc == 5 ) {
		outfile.open( "benchmark_output.txt", ios::app );
		outfile << "\n\n";
	}

	// print system arguments
	std::cout << "\nSystem arguments: ";
	for ( int i = 0; i < argc; i++ ) {
		std::cout << argv[i] << " ";
		outfile << argv[i] << " ";
	}
	std::cout << "\n\n";
	outfile << "\n";

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
	hypro::COUNTEREXAMPLE_STRATEGY counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::Z3_BASIC;			//Z3_BASIC, RANDOM, Z3_SMALL_REPRESENTATION, REMEMBERING_COUNTEREXAMPLES
	hypro::REFINEMENT_TYPE refinementType = hypro::REFINEMENT_TYPE::EXACT_SOURCES;						// AVOIDANT, FULL, EXACT_SOURCES, REMEMBERING_SOURCES
	hypro::TRACING_STRATEGY backpropagationStrategy = hypro::TRACING_STRATEGY::FULL_REUSED_PREDICATE;	// SINGLESTEP, BINARYSEARCH, REMEMBERING_SEARCH , UNSAT_CORE, FULL_REUSED_PREDICATE
	hypro::PREDICATE_TRACING_ORIGIN originChoosingStrategy = hypro::PREDICATE_TRACING_ORIGIN::FIRST; // FIRST, LAST, MIDDLE, ALL
	bool tryReusingPredicates = true;
	bool removeSafeSubtrees = false;
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

		if(strlen(argv[1]) > 1){
			switch ( argv[1][1] ) {
				case 'b':
					counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::Z3_BASIC;
					break;
				case 'r':
					counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::RANDOM;
					break;
				case 's':
					counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::Z3_SMALL_REPRESENTATION;
					break;
				case 'm':
					counterExampleStrategy = hypro::COUNTEREXAMPLE_STRATEGY::REMEMBERING_COUNTEREXAMPLES;
					break;
						
				default:
					break;
			}
		}

		if(strlen(argv[1]) > 2){
			switch ( argv[1][2] ) {
				case 's':
					backpropagationStrategy =  hypro::TRACING_STRATEGY::SINGLESTEP;
					break;
				case 'b':
					backpropagationStrategy = hypro::TRACING_STRATEGY::BINARYSEARCH;
					break;
				case 'r':
					backpropagationStrategy = hypro::TRACING_STRATEGY::REMEMBERING_SEARCH;
					break;
				case 'u':
					backpropagationStrategy = hypro::TRACING_STRATEGY::UNSAT_CORE;
					break;
				case 'p':
					backpropagationStrategy = hypro::TRACING_STRATEGY::FULL_REUSED_PREDICATE;
					break;
				case 'l':
					backpropagationStrategy = hypro::TRACING_STRATEGY::REUSED_PREDICATE_WITH_LP;
					break;
				default:
					break;
			}
		}

		if(strlen(argv[1]) > 3){
			switch ( argv[1][3] ) {
				case 'a':
					refinementType =  hypro::REFINEMENT_TYPE::AVOIDANT;
					break;
				case 'f':
					refinementType = hypro::REFINEMENT_TYPE::FULL;
					break;
				case 'e':
					refinementType = hypro::REFINEMENT_TYPE::EXACT_SOURCES;
					break;
				case 'r':
					refinementType = hypro::REFINEMENT_TYPE::REMEMBERING_SOURCES;
					break;
				case 'p':
					refinementType = hypro::REFINEMENT_TYPE::PATH_WISE_ORIGINS;
					break;
				default:
					break;
			}
		}

		if(strlen(argv[1]) > 4){
			switch ( argv[1][4] ) {
				case 'f':
					originChoosingStrategy =  hypro::PREDICATE_TRACING_ORIGIN::FIRST;
					break;
				case 'l':
					originChoosingStrategy = hypro::PREDICATE_TRACING_ORIGIN::LAST;
					break;
				case 'm':
					originChoosingStrategy = hypro::PREDICATE_TRACING_ORIGIN::MIDDLE;
					break;
				case 'a':
					originChoosingStrategy = hypro::PREDICATE_TRACING_ORIGIN::ALL;
					break;
				default:
					break;
			}
		}
		
		if(strlen(argv[1]) > 5){
			tryReusingPredicates = argv[1][5] == 't';
		}

		if(strlen(argv[1]) > 6){
			removeSafeSubtrees = argv[1][6] == 't';
		}
	}
	std::cout << "The used methods are:" 
			  << "\n Reachability: " << method
			  << "\n Counterexample: " << counterExampleStrategy
			  << "\n Refinment: " << refinementType
			  << "\n Tracing: " << backpropagationStrategy
			  << "\n Try to reuse predicates: " << (tryReusingPredicates ? "yes" : "no");
	if (backpropagationStrategy == hypro::TRACING_STRATEGY::FULL_REUSED_PREDICATE) {
		std::cout << "\n Choosen Origin: " << originChoosingStrategy;
	}
	std::cout << std::endl;

	// define input file name
	const char* filename = "../examples/nn_benchmarks/networks/nnet/small_examples/fc_2-2-2.nnet";
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
	std::cout << "The input polytope:\n"
			  << inputPoly << std::endl;

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
	std::cout << "The disjunction of safe polytopes:\n"
			  << safePoly << std::endl;

	// hypro::matrix_t<Number> linTransform = hypro::matrix_t<Number>( 2, 2 );
	// hypro::vector_t<Number> offset = hypro::vector_t<Number>( 2 );
	// linTransform << 0.707106781,-0.707106781, 0.707106781,0.707106781;
	// offset << -0.5,-0.5;

	// hypro::Starset<Number> inputStar(inputPoly.matrix(),inputPoly.vector());
	// inputStar = inputStar.affineTransformation(linTransform,offset);
	// hypro::ReLULayer<Number> r(0,0);
	// r.reachReLU(inputStar, hypro::NN_REACH_METHOD::OVERAPPRX ,true);
	// return 0;

	// Transform input and safe polytopes to star set
	
	hypro::reachability::ReachabilityTree NNtree = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly, counterExampleStrategy, refinementType, backpropagationStrategy, removeSafeSubtrees);
	NNtree.setTryReusingPredicates(tryReusingPredicates);
	NNtree.setPredicateTracingOrigin(originChoosingStrategy);
	bool bothSearchStrategy = !true;
	bool create_plots = !true;
	bool normalize_input = true;
	bool normalize_output = true;
	start = std::chrono::steady_clock::now();
	bool isSafe = NNtree.verify( method, hypro::SEARCH_STRATEGY::DFS, create_plots, normalize_input, normalize_output );
	end = std::chrono::steady_clock::now();
	std::cout << "Total time elapsed during NN reachability analysis: "
			  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	outfile << "Total time elapsed during NN reachability analysis: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;

	if ( bothSearchStrategy && method == hypro::NN_REACH_METHOD::EXACT ) {
		hypro::reachability::ReachabilityTree NNtree2 = hypro::reachability::ReachabilityTree<Number>( neuralNetwork, inputPoly, safePoly, counterExampleStrategy, refinementType, backpropagationStrategy );
		start = std::chrono::steady_clock::now();
		bool isSafe = NNtree2.verify( method, hypro::SEARCH_STRATEGY::BFS, create_plots, normalize_input, normalize_output );
		end = std::chrono::steady_clock::now();
		std::cout << "Total time elapsed during NN reachability analysis: "
				  << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
		outfile << "Total time elapsed during NN reachability analysis: "
				<< std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count() << " ms" << std::endl;
	}
	if (argc == 5) {
		outfile.close();
	}
	std::cout << "The used methods are:" 
			  << "\n Reachability: " << method
			  << "\n Counterexample: " << counterExampleStrategy
			  << "\n Tracing: " << backpropagationStrategy
			  << "\n Refinment: " << refinementType
			  << "\n Try to reuse predicates: " << (tryReusingPredicates ? "yes" : "no");
	if (backpropagationStrategy == hypro::TRACING_STRATEGY::FULL_REUSED_PREDICATE) {
		std::cout << "\n Choosen Origin: " << originChoosingStrategy;
	}
	std::cout << std::endl;

	return 0;
}
