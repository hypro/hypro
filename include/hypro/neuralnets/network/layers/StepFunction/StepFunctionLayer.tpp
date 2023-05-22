/**
 * @file StepFunctionLayer.tpp
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2023-04-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../hypro/util/plotting/Plotter.h"
#include "StepFunctionLayer.h"

namespace hypro {
template <typename Number>
StepFunctionLayer<Number>::StepFunctionLayer( unsigned short int layerSize, unsigned short int layerIndex, float value, float minValue, float maxValue )
	: LayerBase<Number>( layerSize, layerIndex )
	, mValue( value )
	, mMinValue( minValue )
	, mMaxValue( maxValue ) {
}

template <typename Number>
std::vector<hypro::Starset<Number>> StepFunctionLayer<Number>::reachStepFunction( const hypro::Starset<Number>& inputSet, hypro::NN_REACH_METHOD method, bool plotIntermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );

	for ( auto i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				resultSet = StepFunction<Number>::exactStepFunction( i, resultSet, mValue, mMinValue, mMaxValue );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.stepFunction", "Invalid analysis method specified" );
		}
		if ( plotIntermediates ) {
#pragma omp critical
			for ( int j = 0; j < resultSet.size(); j++ ) {
				plotter.addObject( resultSet[j].vertices(), hypro::plotting::colors[( 2 * j ) % 9] );
			}
			plotter.plot2d();
			plotter.clear();
		}
	}
	return resultSet;
}

template <typename Number>
const NN_LAYER_TYPE StepFunctionLayer<Number>::layerType() const {
	return NN_LAYER_TYPE::STEP_FUNCTION;
}

template <typename Number>
vector_t<Number> StepFunctionLayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	auto outputVec = inputVec;
	for ( auto i = 0; i < outputVec.size(); i++ ) {
		if ( outputVec[i] < this->mValue ) {
			outputVec[i] = mMinValue;
		} else if ( outputVec[i] >= this->mValue ) {
			outputVec[i] = mMaxValue;
		}
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> StepFunctionLayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			resultSet = StepFunction<Number>::exactStepFunction( index, resultSet,mValue, mMinValue, mMaxValue );
			break;
		default:
			FATAL( "hypro.neuralnets.activation_functions.stepfunction", "Invalid analysis method specified" );
	}
	return resultSet;
}

template <typename Number>
std::vector<Starset<Number>> StepFunctionLayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	auto result = std::vector<Starset<Number>>();

	for ( const auto& set : inputSets ) {
		auto resultSets = reachStepFunction( set, method, plotIntermediates );
#pragma omp critical
		{ result.insert( result.end(), resultSets.begin(), resultSets.end() ); };
	}

	return result;
}

template <typename Number>
Point<Number> StepFunctionLayer<Number>::propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const {
	return Point<Number>();
}
}  // namespace hypro
