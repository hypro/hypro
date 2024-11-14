/**
 * @file ReLULayer.tpp
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ReLULayer.h"

namespace hypro {

template <typename Number>
ReLULayer<Number>::ReLULayer()
	: LayerBase<Number>() {}

template <typename Number>
ReLULayer<Number>::ReLULayer( unsigned short int layerSize, unsigned short int layerIndex )
	: LayerBase<Number>( layerSize, layerIndex ) {}

template <typename Number>
const NN_LAYER_TYPE ReLULayer<Number>::layerType() const {
	return NN_LAYER_TYPE::RELU;
}

template <typename Number>
vector_t<Number> ReLULayer<Number>::forwardPass( const vector_t<Number>& inputVec, int i ) const {
	vector_t<Number> outputVec = inputVec;
	outputVec[i] = outputVec[i] >= 0 ? outputVec[i] : 0;
	return outputVec;
}

template <typename Number>
vector_t<Number> ReLULayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	vector_t<Number> outputVec = inputVec;
	for ( int i = 0; i < outputVec.size(); ++i ) {
		outputVec[i] = outputVec[i] >= 0 ? outputVec[i] : 0;
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> ReLULayer<Number>::reachReLU( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	std::vector<hypro::Starset<Number>> I_n = std::vector<hypro::Starset<Number>>();
	I_n.push_back( inputSet );
	for ( int i = 0; i < inputSet.generator().rows(); i++ ) {
		// std::cout << "Neuron index:" << i << std::endl;
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				I_n = ReLU<Number>::stepReLU( i, I_n );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				I_n = ReLU<Number>::approxStepReLU( i, I_n );
				break;
			default:
				FATAL( "hypro.neuralnets.reachability", "Invalid analysis method specified" );
		}
	}
	return I_n;
}

template <typename Number>
std::vector<hypro::Starset<Number>> ReLULayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	std::vector<hypro::Starset<Number>> I_n = std::vector<hypro::Starset<Number>>();
	I_n.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			I_n = ReLU<Number>::stepReLU( index, I_n );
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			I_n = ReLU<Number>::approxStepReLU( index, I_n );
			break;
		default:
			FATAL( "hypro.neuralnets.reachability", "Invalid analysis method specified" );
	}
	return I_n;
}

template <typename Number>
std::vector<Starset<Number>> ReLULayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	std::vector<Starset<Number>> result = std::vector<Starset<Number>>();
	int N = inputSets.size();  // number of input stars

	// #pragma omp parallel for  // TODO: try to set up the thread pool in advance (at the start of the analysis), then here at the for loops just use the existing threads
	for ( int i = 0; i < N; ++i ) {
		std::vector<hypro::Starset<Number>> resultSets;
		resultSets = reachReLU( inputSets[i], method, plotIntermediates );

		// #pragma omp critical
		{
			result.insert( result.end(), resultSets.begin(), resultSets.end() );
		}
	}
	return result;
}

template <typename Number>
Point<Number> ReLULayer<Number>::propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const {
	assert( neuronNumber < y.dimension() );
	assert( y[neuronNumber] >= 0 );

	// std::cout << "relu " << neuronNumber << " backpropagation" << std::endl;

	// if the points coordinate at the corresponding neurons dimension is positive, then the point is not changed
	if ( y[neuronNumber] > 0 ) {
		return y;
	}

	// if it is negative need to apply linear optimization in the inputset (or other algorithm) to find the corresponding point
	// TODO: implement this
	return y;
}

}  // namespace hypro
