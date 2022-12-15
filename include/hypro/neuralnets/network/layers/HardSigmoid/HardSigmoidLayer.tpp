/**
 * @file HardSigmoidLayer.tpp
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "HardSigmoidLayer.h"

namespace hypro {

template <typename Number>
HardSigmoidLayer<Number>::HardSigmoidLayer(unsigned short int layerSize, unsigned short int layerIndex)
	: LayerBase<Number>(layerSize, layerIndex ) {}

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoidLayer<Number>::reachHardSigmoid( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plot_intermediates ) const {
	std::vector<hypro::Starset<Number>> I_n = std::vector<hypro::Starset<Number>>();
	I_n.push_back( inputSet );
	for ( int i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				I_n = HardSigmoid<Number>::exactHardSigmoid( i, I_n );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				I_n = HardSigmoid<Number>::approxHardSigmoid( i, I_n );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.HardSigmoid", "Invalid analysis method specified" );
		}
	}
	return I_n;
}

template <typename Number>
const NN_LAYER_TYPE HardSigmoidLayer<Number>::layerType() const {
	return NN_LAYER_TYPE::HARD_SIGMOID;
}

template <typename Number>
vector_t<Number> HardSigmoidLayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	auto outputVec = inputVec;
	for ( auto i = 0; i < outputVec.size(); i++ ) {
		if( outputVec[i] <= -3.0){
			outputVec[i] = 0;
		}
		else if ( outputVec[i] >= 3.0 ){
			outputVec[i] = 1;
		} else {
			outputVec[i] = (outputVec[i]/6) + (1/2);
		}
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoidLayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			resultSet = HardSigmoid<Number>::exactHardSigmoid( index, resultSet);
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			resultSet = HardSigmoid<Number>::approxHardSigmoid( index, resultSet );
			break;
		default:
			FATAL( "hypro.neuralnets.activation_functions.hardsigmoid", "Invalid analysis method specified" );
	}
	return resultSet;
}

template <typename Number>
std::vector<Starset<Number>> HardSigmoidLayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	auto result = std::vector<Starset<Number>>();

	for ( const auto& set : inputSets ) {
		auto resultSets = reachHardTanh( set, method, plotIntermediates );

		result.insert( result.end(), resultSets.begin(), resultSets.end() );
	}

	return result;
}

}

