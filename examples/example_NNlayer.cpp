#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/parser/neuralnets/nnet/NNet.h"
#include "hypro/parser/representations/parseHPolytope.tpp"
#include "hypro/representations/Starset/Starset.h"
#include "hypro/util/plotting/Plotter.h"

#include <iostream>

// use floating point arithmetic.
typedef double Number;

int main( int argc, char* argv[] ) {
	std::cout << "\nSystem arguments: ";
	for ( int i = 0; i < argc; i++ ) {
		std::cout << argv[i] << " ";
	}
	std::cout << "\n\n";

	// Define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.name = "Activation Functions of FFNN";
	settings.filename = "FFNN_";
	settings.fill = true;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;
	settings.xPlotInterval = carl::Interval<double>( -6, +6 );
	settings.yPlotInterval = carl::Interval<double>( -6, +6 );

	// Get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );
	plotter.clear();

	// Define the reachability method
	hypro::NN_REACH_METHOD method{};
	if ( argc > 1 ) {
		switch ( tolower( argv[1][0] ) ) {
			case 'e':
				method = hypro::NN_REACH_METHOD::EXACT;
				break;
			case 'o':
				method = hypro::NN_REACH_METHOD::OVERAPPRX;
				break;
			default:
				method = hypro::NN_REACH_METHOD::EXACT;
				break;
		}
	}

	// Define the layer type
	std::shared_ptr<hypro::LayerBase<Number>> layer;
	if ( argc > 2 ) {
		switch ( tolower( argv[2][0] ) ) {
			case 'l':
				std::cout << "Using LeakyReLu layer." << std::endl;
				layer = std::make_shared<hypro::LeakyReLULayer<Number>>( 2, 0 );
				break;
			case 't':
				std::cout << "Using HardTanh layer." << std::endl;
				layer = std::make_shared<hypro::HardTanhLayer<Number>>( 2, 0 );
				break;
			case 's':
				std::cout << "Using HardSigmoid layer." << std::endl;
				layer = std::make_shared<hypro::HardSigmoidLayer<Number>>( 2, 0 );
				break;
			default:
				std::cout << "Unknown layer argument. Using LeakyReLu layer." << std::endl;
				layer = std::make_shared<hypro::LeakyReLULayer<Number>>( 2, 0 );
				break;
		}
	}

	hypro::HPolytope<Number> input_poly;

	if ( argc > 3 ) {
		// Use the file parameter as input
		std::cout << "Reading input constraints from: " << argv[3] << std::endl;
		input_poly = hypro::readHpolytopeFromFile<Number>( argv[3] );
	} else {
		// Define a simple rectangle as the default input polytope
		std::cout << "Using default input constraints." << std::endl;
		hypro::matrix_t<Number> constr = hypro::matrix_t<Number>( 4, 2 );
		hypro::vector_t<Number> limits = hypro::vector_t<Number>( 4 );
		constr << 1, 0, -1, 0, 0, 1, 0, -1;
		limits << 2, 1, 1, 1;
		input_poly = hypro::HPolytope<Number>( constr, limits );
	}

	hypro::vector_t<Number> center = hypro::vector_t<Number>( 2 );
	center << 0, 0;

	hypro::matrix_t<Number> basis = hypro::matrix_t<Number>( 2, 2 );
	basis << 0.7071, -0.7071, 0.7071, 0.7071;

	// Create star set vector from input polytope
	auto star_set = hypro::Starset<Number>( center, basis, input_poly );
	std::vector<hypro::Starset<Number>> inputSets;
	inputSets.push_back( star_set );

	std::cout << inputSets << std::endl;

	// Plot input set
	plotter.addObject( star_set.vertices(), hypro::plotting::colors[hypro::plotting::green] );
	plotter.plot2d();
	plotter.clear();

	// Apply forward pass
	auto output_set = layer->forwardPass( inputSets, method, true );
}