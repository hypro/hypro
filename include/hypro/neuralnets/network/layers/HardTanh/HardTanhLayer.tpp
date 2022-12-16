/**
 * @file HardTanhLayer.tpp
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-11-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../hypro/util/plotting/Plotter.h"
#include "HardTanhLayer.h"

namespace hypro {

template <typename Number>
HardTanhLayer<Number>::HardTanhLayer( unsigned short int layerSize, unsigned short int layerIndex, float minValue, float maxValue )
	: LayerBase<Number>( layerSize, layerIndex )
	, mMinValue( minValue )
	, mMaxValue( maxValue ) {
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanhLayer<Number>::reachHardTanh( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool /*plotIntermediates*/ ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	for ( auto i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				resultSet = HardTanh<Number>::exactHardTanh( i, resultSet, mMinValue, mMaxValue );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				resultSet = HardTanh<Number>::approxHardTanh( i, resultSet );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.hardtanh", "Invalid analysis method specified" );
		}
	}
	return resultSet;
}

template <typename Number>
const NN_LAYER_TYPE HardTanhLayer<Number>::layerType() const {
	return NN_LAYER_TYPE::HARD_TANH;
}

template <typename Number>
vector_t<Number> HardTanhLayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	auto outputVec = inputVec;
	for ( auto i = 0; i < outputVec.size(); i++ ) {
		if ( outputVec[i] < this->mMinValue ) {
			outputVec[i] = mMinValue;
		} else if ( outputVec[i] > this->mMaxValue ) {
			outputVec[i] = mMaxValue;
		} else {
			// Identity
		}
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanhLayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			resultSet = HardTanh<Number>::exactHardTanh( index, resultSet, mMinValue, mMaxValue );
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			resultSet = HardTanh<Number>::approxHardTanh( index, resultSet );
			break;
		default:
			FATAL( "hypro.neuralnets.activation_functions.hardtanh", "Invalid analysis method specified" );
	}
	return resultSet;
}

template <typename Number>
std::vector<Starset<Number>> HardTanhLayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	auto result = std::vector<Starset<Number>>();

	for ( const auto& set : inputSets ) {
		auto resultSets = reachHardTanh( set, method, plotIntermediates );

		result.insert( result.end(), resultSets.begin(), resultSets.end() );
	}

	return result;
}

template <typename Number>
Point<Number> HardTanhLayer<Number>::propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const {
	return Point<Number>();
}
}  // namespace hypro