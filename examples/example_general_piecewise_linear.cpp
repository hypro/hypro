#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/network/layers/GenerealPiecewiseLinear/GeneralPiecewiseLinearLayer.h"

#include <iostream>

typedef mpq_class Number;

int main(int argc, char* argv[]) {
	// define plotter settings
	hypro::plotting::gnuplotSettings settings;
	settings.name = "Reachability analysis of FFNN with general piece-wise linear activation function";
	settings.filename = "FFNN_general_piecewise";
	settings.fill = true;
	settings.linewidth = 3.0;
	settings.keepAspectRatio = true;
	settings.xPlotInterval = carl::Interval<double>( -3.5, +3.5 );
	settings.yPlotInterval = carl::Interval<double>( -4.5, +4.5 );
	// settings.overwriteFiles = true;

	// get plotter reference.
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
	plotter.updateSettings( settings );
	plotter.clear();

    unsigned short layerSize = 10;
    unsigned short layerIndex = 0;
    size_t numPieces = 3;
    std::vector<Number> lowerBounds = {DBL_MIN, -1, +1};
    std::vector<Number> upperBounds = {-1, +1, DBL_MAX};
    std::vector<Number> slopes = {-2, 0, +3};
    std::vector<Number> offsets = {1, 2, 3};


    // create a general piece-wise linear function
	std::shared_ptr<hypro::LayerBase<Number>> pieceWiseLinLayer = std::make_shared<hypro::GeneralPiecewiseLinearLayer<Number>>(layerSize, layerIndex, numPieces, lowerBounds, upperBounds, slopes, offsets);
    std::cout << "pieceWiseLinLayer: " << pieceWiseLinLayer->layerType()._to_string() << std::endl;

    hypro::vector_t<Number> center(2);
    hypro::matrix_t<Number> basis(2, 2);
    hypro::matrix_t<Number> shape(4, 2);
    hypro::vector_t<Number> limits(4);
    center << 0, 0;
    basis << 1, 0, 0, 1;
    shape << 1, -1, -1, +1, -1, 0, 1, 0;
    limits << 1, 1, 3, 3;

    hypro::Starset<Number> input_star(center, shape, limits, basis);
    std::cout << "Input star is: " << input_star << std::endl;
    plotter.addObject(input_star.vertices());
    plotter.plot2d();

    std::vector<hypro::Starset<Number>> input_stars;
    input_stars.push_back(input_star);
	auto result1 = pieceWiseLinLayer->forwardPass( input_stars, hypro::NN_REACH_METHOD::EXACT, true );

    return 0;
}