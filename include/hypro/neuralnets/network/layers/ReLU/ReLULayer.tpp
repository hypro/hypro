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
	: mLayerSize( 0 ) {}

template <typename Number>
ReLULayer<Number>::ReLULayer( unsigned short int layerSize )
	: mLayerSize( layerSize ) {}

template <typename Number>
const NN_LAYER_TYPE ReLULayer<Number>::layerType() const {
	return NN_LAYER_TYPE::RELU;
}

template <typename Number>
unsigned short int ReLULayer<Number>::layerSize() const {
	return mLayerSize;
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
std::vector<hypro::Starset<Number>> ReLULayer<Number>::reachReLU( const hypro::Starset<Number>& input_star1, NN_REACH_METHOD method, bool plotIntermediates ) const {
	std::vector<hypro::Starset<Number>> I_n = std::vector<hypro::Starset<Number>>();
	I_n.push_back( input_star1 );
	for ( int i = 0; i < input_star1.generator().rows(); i++ ) {
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
std::vector<Starset<Number>> ReLULayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	std::vector<Starset<Number>> result = std::vector<Starset<Number>>();
	int N = inputSet.size();  // number of input stars

#pragma omp parallel for  // TODO: try to set up the thread pool in advance (at the start of the analysis), then here at the for loops just use the existing threads
	for ( int i = 0; i < N; ++i ) {
		std::vector<hypro::Starset<Number>> resultSets;
		resultSets = reachReLU( inputSet[i], method, plotIntermediates );

#pragma omp critical
		{
			result.insert( result.end(), resultSets.begin(), resultSets.end() );
		}
	}
	return result;
}

}  // namespace hypro
