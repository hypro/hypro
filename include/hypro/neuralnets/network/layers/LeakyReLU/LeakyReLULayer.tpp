/**
* @file LeakyReLULayer.tpp
* @author Hana Masara <hana.masara@rwth-aachen.de>
* @brief
* @version 0.1
* @date 2022-12-07
*
* @copyright Copyright (c) 2022
*
 */
#include "../hypro/util/plotting/Plotter.h"
#include "LeakyReLULayer.h"

namespace hypro {

template <typename Number>
LeakyReLULayer<Number>::LeakyReLULayer( unsigned short layerSize, unsigned short layerIndex, float negativeSlope )
	: LayerBase<Number>( layerSize, layerIndex)
	, mNegativeSlope( negativeSlope ) {

	if(negativeSlope <= 0 || negativeSlope >= 1 ){
		FATAL( "hypro.neuralnets.activation_functions.LeakyReLU", "Invalid value for the negative slope ( 0 < negative slope < 1)" );
	}
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLULayer<Number>::reachLeakyReLU( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool /*plotIntermediates*/ ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	for ( auto i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				resultSet = LeakyReLU<Number>::exactLeakyReLU( i, resultSet, mNegativeSlope );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				resultSet = LeakyReLU<Number>::approxLeakyReLU( i, resultSet );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.LeakyReLU", "Invalid analysis method specified" );
		}
	}
	return resultSet;
}

template <typename Number>
const NN_LAYER_TYPE LeakyReLULayer<Number>::layerType() const {
	return NN_LAYER_TYPE::LEAKY_RELU;
}

template <typename Number>
vector_t<Number> LeakyReLULayer<Number>::forwardPass( const vector_t<Number>& inputVec, int i ) const {
	auto outputVec = inputVec;
	outputVec[i] = outputVec[i] >= 0 ? outputVec[i] : (outputVec[i]*mNegativeSlope);
	return outputVec;
}

template <typename Number>
vector_t<Number> LeakyReLULayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	auto outputVec = inputVec;
	for ( int i = 0; i < outputVec.size(); ++i ) {
		outputVec[i] = outputVec[i] >= 0 ? outputVec[i] : (outputVec[i]*mNegativeSlope);
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLULayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			resultSet = LeakyReLU<Number>::exactLeakyReLU( index, resultSet, mNegativeSlope);
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			resultSet = LeakyReLU<Number>::approxLeakyReLU( index, resultSet );
			break;
		default:
			FATAL( "hypro.neuralnets.activation_functions.LeakyReLU", "Invalid analysis method specified" );
	}
	return resultSet;
}

template <typename Number>
std::vector<Starset<Number>> LeakyReLULayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	auto result = std::vector<Starset<Number>>();

	for ( const auto& set : inputSets ) {
		auto resultSets = reachLeakyReLU( set, method, plotIntermediates );

		result.insert( result.end(), resultSets.begin(), resultSets.end() );
	}

	return result;
}

}// namespace hypro