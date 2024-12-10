#include "hypro/neuralnets/network/NeuralNetwork.h"
#include "hypro/neuralnets/network/layers/GenerealPiecewiseLinear/GeneralPiecewiseLinearLayer.h"

#include <iostream>

typedef mpq_class Number;

int main(int argc, char* argv[]) {
    unsigned short layerSize = 10;
    unsigned short layerIndex = 0;
    size_t numPieces = 2;
    std::vector<Number> lowerBounds = {DBL_MIN, -1, +1};
    std::vector<Number> upperBounds = {-1, +1, DBL_MAX};
    std::vector<Number> slopes = {-1, 0, +1};
    std::vector<Number> offsets = {0, 0, 0};


    // create a general piece-wise linear function
	std::shared_ptr<hypro::LayerBase<Number>> pieceWiseLinLayer = std::make_shared<hypro::GeneralPiecewiseLinearLayer<Number>>(layerSize, layerIndex, numPieces, lowerBounds, upperBounds, slopes, offsets);
    std::cout << "pieceWiseLinLayer: " << pieceWiseLinLayer->layerType()._to_string() << std::endl;
	// auto result1 = layer1->forwardPass( output, method, false );

    return 0;
}