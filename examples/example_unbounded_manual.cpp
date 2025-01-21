#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/reachability/ReachNN.h"
#include "hypro/neuralnets/reachability_tree/ReachabilityTree.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/representations/Starset/Starset.h"
#include "hypro/neuralnets/network/activation_functions/ReLU/ReLU.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/util/plotting/Plotter.h"

#include <chrono>
#include <hypro/representations/sampling/sampling.h>
#include <iomanip>
#include <iostream>
#include <vector>

// use floating point arithmetic.
typedef double Number;	// -3090.30109487     <=>      -3090.3   (mpq_class vs double)

int main( int argc, char* argv[] ) {
	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.name = "Reachability analysis of ReLU activation function";
	settings.filename = "RELU_REACH";
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

	// a simple rectangle [_]
	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	hypro::matrix_t<Number> shape_bounded = hypro::matrix_t<Number>( 4, 2 );
	hypro::vector_t<Number> limits_bounded = hypro::vector_t<Number>( 4 );
	center << -0.5, -0.5;
	basis << 0.7071, -0.7071, 0.7071, 0.7071;
	shape_bounded << 1, 0, -1, 0, 0, 1, 0, -1;
	limits_bounded << 2, 1, 1, 1;

	hypro::Starset<Number> bounded_input_star( center, shape_bounded, limits_bounded, basis );
	std::vector<hypro::Starset<Number>> bounded_input_star_vector;
	bounded_input_star_vector.push_back( bounded_input_star );

	size_t color = 0;

	plotter.clear();
	plotter.addObject( bounded_input_star_vector[0].vertices(), hypro::plotting::colors[color++] );
	plotter.plot2d();

	std::vector<hypro::Starset<Number>> bounded_step1_star_vector = hypro::ReLU<Number>::stepReLU( 0, bounded_input_star_vector );
	plotter.clear();
	for ( auto star : bounded_step1_star_vector ) {
		plotter.addObject( star.vertices(), hypro::plotting::colors[color++] );
	}
    plotter.plot2d();

    std::vector<hypro::Starset<Number>> bounded_step2_star_vector = hypro::ReLU<Number>::stepReLU( 1, bounded_step1_star_vector );
	plotter.clear();
	for ( auto star : bounded_step2_star_vector ) {
		plotter.addObject( star.vertices(), hypro::plotting::colors[color++] );
	}
    plotter.plot2d();

    std::vector<hypro::Starset<Number>> bounded_step1_star_OA = hypro::ReLU<Number>::approxStepReLU( 0, bounded_input_star_vector );
    plotter.clear();
    plotter.addObject( bounded_step1_star_OA[0].vertices(), hypro::plotting::colors[color++] );
    plotter.plot2d();

    std::vector<hypro::Starset<Number>> bounded_step2_star_OA = hypro::ReLU<Number>::approxStepReLU( 1, bounded_step1_star_OA );
    plotter.clear();
    plotter.addObject( bounded_step2_star_OA[0].vertices(), hypro::plotting::colors[color++] );
    plotter.plot2d();

	hypro::matrix_t<Number> shape_unbounded = hypro::matrix_t<Number>( 3, 2 );
	hypro::vector_t<Number> limits_unbounded = hypro::vector_t<Number>( 3 );
	shape_unbounded << 1, 0, 0, 1, 0, -1;
	limits_unbounded << 2, 1, 1;

	hypro::Starset<Number> unbounded_input_star( center, shape_unbounded, limits_unbounded, basis );
    std::cout << "Unbounded input star: \n" << unbounded_input_star << std::endl;
	std::vector<hypro::Starset<Number>> unbounded_input_star_vector;
	unbounded_input_star_vector.push_back( unbounded_input_star );

    plotter.clear();
	plotter.addObject( unbounded_input_star_vector[0].vertices(), hypro::plotting::colors[color++] );
	plotter.plot2d();

    // std::cout << "Vertices: " << unbounded_input_star_vector[0].vertices() << std::endl;

    std::vector<hypro::Starset<Number>> unbounded_step1_star_vector = hypro::ReLU<Number>::stepReLU( 0, unbounded_input_star_vector );
    std::cout << "After ReLU-1: \n";
    for (auto star : unbounded_step1_star_vector) {
        std::cout << star << std::endl;
    }

    std::vector<hypro::Starset<Number>> unbounded_step2_star_vector = hypro::ReLU<Number>::stepReLU( 1, unbounded_step1_star_vector );
    std::cout << "After ReLU-2: \n";
    for (auto star : unbounded_step2_star_vector) {
        std::cout << star << std::endl;
    }

    std::vector<hypro::Starset<Number>> unbounded_step1_star_OA = hypro::ReLU<Number>::approxStepReLU( 0, unbounded_input_star_vector );
    std::cout << "After OAReLU-1: \n" << unbounded_step1_star_OA[0] << std::endl;

    std::vector<hypro::Starset<Number>> unbounded_step2_star_OA = hypro::ReLU<Number>::approxStepReLU( 1, unbounded_step1_star_OA );
    std::cout << "After OAReLU-2: \n" << unbounded_step2_star_OA[0] << std::endl;

    int n = 10;
    for ( auto exact_star : bounded_step2_star_vector ) {
        std::set<hypro::Point<Number>> samples = uniform_sampling( exact_star, n );
        for (auto sample : samples ) {
            bool included = false;
            for ( auto star : unbounded_step2_star_vector ) {
                if (star.contains(sample)) {
                    included = true;
                    break;
                }
            }
            if( ! included ) {
                std::cout << "!!!!!!!!!!!!!!!!! EXACT UB not included" << std::endl;
            } else {
                std::cout << "EXACT UB included" << std::endl;
            }

            if ( bounded_step2_star_OA[0].contains(sample) ) {
                std::cout << "OA B included" << std::endl;
            } else {
                std::cout << "!!!!!!!!!!!!!!!!!OA B not included" << std::endl;
            }

            if ( unbounded_step2_star_OA[0].contains(sample) ) {
                std::cout << "OA UB included" << std::endl;
            } else {
                std::cout << "!!!!!!!!!!!!!!!!!OA UB not included" << std::endl;
            }
        }
    }

    std::set<hypro::Point<Number>> samples = uniform_sampling( bounded_step2_star_OA[0], n );
    for (auto sample : samples ) {
        if ( unbounded_step2_star_OA[0].contains(sample) ) {
            std::cout << "OA UB included" << std::endl;
        } else {
            std::cout << "!!!!!!!!!!!!!!!!! OA UB not included" << std::endl;
        }
    }

    for ( auto star : unbounded_step2_star_vector) {
        std::set<hypro::Point<Number>> smpls = uniform_sampling( star, n );
        for ( auto sample : smpls ) {
            if ( unbounded_step2_star_OA[0].contains(sample) ) {
                std::cout << "OA UB included" << std::endl;
            } else {
                std::cout << "!!!!!!!!!!!!!!!!! OA UB not included" << std::endl;
            }
        }
    }
}
