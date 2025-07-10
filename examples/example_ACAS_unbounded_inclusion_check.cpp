#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include <hypro/representations/sampling/sampling.h>
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

	std::cout << "Removing upper bound on ownship speed..." << std::endl;
	hypro::matrix_t<Number> shape = input_starset.shape();
	hypro::vector_t<Number> limits = input_starset.limits();
	shape.conservativeResize(shape.rows() - 1, shape.cols());
	limits.conservativeResize(limits.rows() - 1);
	hypro::Starset<Number> unbounded_input_starset = hypro::Starset<Number>(input_starset.center(), shape, limits, input_starset.generator());
	std::cout << "Done" << std::endl;
	std::cout << "New unbounded star set: " << unbounded_input_starset << std::endl;
	std::cout << "Set is empty: " << unbounded_input_starset.empty() << std::endl;


    hypro::vector_t<Number> center = input_starset.center();
    hypro::matrix_t<Number> generator = input_starset.generator();
    hypro::matrix_t<Number> shape_bounded = input_starset.shape();
    hypro::vector_t<Number> limits_bounded = input_starset.limits();

    hypro::matrix_t<Number> shape_unbounded = unbounded_input_starset.shape();
    hypro::vector_t<Number> limits_unbounded = unbounded_input_starset.limits();
    
    hypro::Starset<Number> bounded_input_EXACT = hypro::Starset<Number>(center, shape_bounded, limits_bounded, generator);
    hypro::Starset<Number> bounded_input_OA = hypro::Starset<Number>(center, shape_bounded, limits_bounded, generator);
    hypro::Starset<Number> unbounded_input_EXACT = hypro::Starset<Number>(center, shape_unbounded, limits_unbounded, generator);
    hypro::Starset<Number> unbounded_input_OA = hypro::Starset<Number>(center, shape_unbounded, limits_unbounded, generator);

    std::vector<hypro::Starset<Number>> output_bounded_EXACT = neuralNetwork.forwardPass( bounded_input_EXACT, hypro::NN_REACH_METHOD::EXACT, false );
    std::vector<hypro::Starset<Number>> output_bounded_OA = neuralNetwork.forwardPass( bounded_input_EXACT, hypro::NN_REACH_METHOD::OVERAPPRX, false );
    std::vector<hypro::Starset<Number>> output_unbounded_EXACT = neuralNetwork.forwardPass( unbounded_input_EXACT, hypro::NN_REACH_METHOD::EXACT, false );
    std::vector<hypro::Starset<Number>> output_unbounded_OA = neuralNetwork.forwardPass( unbounded_input_EXACT, hypro::NN_REACH_METHOD::OVERAPPRX, false );

    std::cout << "EXQCT bounded num stars: " << output_bounded_EXACT.size() << std::endl;
    std::cout << "OA bounded num vars: " << output_bounded_OA[0].constraints().dimension() << std::endl;
    std::cout << "EXQCT unbounded num stars: " << output_unbounded_EXACT.size() << std::endl;
    std::cout << "OA unbounded num vars: " << output_unbounded_OA[0].constraints().dimension() << std::endl;


    int n = 10;
    for ( auto& exact_bounded_star : output_bounded_EXACT ) {
        std::set<hypro::Point<Number>> samples_bounded_EXACT = uniform_sampling( exact_bounded_star, n );
        std::cout << "Sampling done" << std::endl;
        for ( auto& sample : samples_bounded_EXACT ) {
            if ( ! output_bounded_OA[0].contains(sample) ) {
                std::cout << "Bounded OA set does not contain bounded exact sample!" << std::endl;
            } else {
                std::cout << "Included." << std::endl;
            }
            bool contains = false;
            for ( auto& exact_unbounded_star : output_unbounded_EXACT ) {
                if ( exact_unbounded_star.contains(sample) ) {
                    contains = true;
                    break;
                }
            }
            if ( ! contains ) {
                std::cout << "Unbounded exact set does not contain bounded exact sample!" << std::endl;
            } else {
                std::cout << "Included." << std::endl;
            }
            if ( ! output_unbounded_OA[0].contains(sample) ) {
                std::cout << "Unbounded OA set does not contain bounded exact sample!" << std::endl;
            } else {
                std::cout << "Included." << std::endl;
            }
        }
    }

    std::set<hypro::Point<Number>> samples_bounded_OA = uniform_sampling( output_bounded_OA[0], n );
    std::cout << "Sampling done." << std::endl;
    for ( auto& sample : samples_bounded_OA ) {
        if ( ! output_unbounded_OA[0].contains(sample) ) {
            std::cout << "Unbounded OA set does not contain bounded OA sample!" << std::endl;
        } else {
            std::cout << "Included." << std::endl;
        }
    }

    for ( auto& exact_unbounded_star : output_unbounded_EXACT ) {
        std::set<hypro::Point<Number>> samples_unbounded_EXACT = uniform_sampling( exact_unbounded_star, n );
        std::cout << "Sampling done." << std::endl;
        for ( auto& sample : samples_unbounded_EXACT ) {
            if ( ! output_unbounded_OA[0].contains(sample) ) {
                std::cout << "Unbounded OA set does not contain unbounded exact sample!" << std::endl;
            } else {
                std::cout << "Included." << std::endl;
            }
        }
    }

    std::cout << "All done. " << std::endl;

	// // Apply the reachability analysis to the input star set and measure the required time
	// auto start = std::chrono::steady_clock::now();
	// // std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( input_starset, method, false );
	// std::vector<hypro::Starset<Number>> output = neuralNetwork.forwardPass( unbounded_input_starset, method, false );
	// auto end = std::chrono::steady_clock::now();
	// auto analysisTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	// std::cout << "Reachability Analysis Time (ms): " << analysisTime << std::endl;

	// // Check if all output star set is safe, e.g. if it is contained in the safe zone
	// start = std::chrono::steady_clock::now();
	// bool all_safe = true;
	// for ( int k = 0; k < output.size(); k++ ) {
	// 	hypro::reachability::ReachabilityNode node = hypro::reachability::ReachabilityNode<Number>( output[k], method, 0, 0 );
	// 	bool isCurrentSafe = node.checkSafeRecursive( output[k], 0, safe_set );
	// 	all_safe &= isCurrentSafe;
	// }
	// end = std::chrono::steady_clock::now();
	// std::cout << std::boolalpha;
	// std::cout << "Reachable Set is Safe: " << all_safe << std::endl;
	// auto safetyCheckTime = std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
	// std::cout << "Safety Check Time (ms): " << safetyCheckTime << std::endl;

	// std::cout << "Total Time (ms): " << analysisTime + safetyCheckTime << std::endl;
	// std::cout << "Number of Output Star Sets: " << output.size() << std::endl;
}
