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
#include "hypro/util/plotting/Plotter.h"

namespace hypro {

template <typename Number>
HardSigmoidLayer<Number>::HardSigmoidLayer( unsigned short int layerSize, unsigned short int layerIndex, float minValue, float maxValue )
	: LayerBase<Number>( layerSize, layerIndex )
	, mMinValue( minValue )
	, mMaxValue( maxValue ) {
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardSigmoidLayer<Number>::reachHardSigmoid( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );

	for ( int i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				resultSet = HardSigmoid<Number>::exactHardSigmoid( i, resultSet, mMinValue, mMaxValue );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				resultSet = HardSigmoid<Number>::approxHardSigmoid( i, resultSet, mMinValue, mMaxValue );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.HardSigmoid", "Invalid analysis method specified" );
		}
		if ( plotIntermediates ) {
// #pragma omp critical
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
const NN_LAYER_TYPE HardSigmoidLayer<Number>::layerType() const {
	return NN_LAYER_TYPE::HARD_SIGMOID;
}

template <typename Number>
vector_t<Number> HardSigmoidLayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	auto outputVec = inputVec;
	for ( auto i = 0; i < outputVec.size(); i++ ) {
		if ( outputVec[i] <= this->mMinValue ) {
			outputVec[i] = 0;
		} else if ( outputVec[i] >= this->mMaxValue ) {
			outputVec[i] = 1;
		} else {
			outputVec[i] = ( 1 / ( this->mMaxValue - this->mMinValue ) ) * outputVec[i] + ( this->mMinValue / ( this->mMinValue - this->mMaxValue ) );
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
			resultSet = HardSigmoid<Number>::exactHardSigmoid( index, resultSet, mMinValue, mMaxValue );
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			resultSet = HardSigmoid<Number>::approxHardSigmoid( index, resultSet, mMinValue, mMaxValue );
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
		std::cout << "set in forwardpass:  " << set << std::endl;
		auto resultSets = reachHardSigmoid( set, method, plotIntermediates );
// #pragma omp critical
		result.insert( result.end(), resultSets.begin(), resultSets.end() );
	}

	return result;
}

template <typename Number>
Point<Number> HardSigmoidLayer<Number>::propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const {
	assert( neuronNumber < y.dimension() );
	assert( 0 <= y[neuronNumber]  && y[neuronNumber] <= 1 );

	Number y_neuronNumber = y[neuronNumber];
	carl::Relation rel;
	if ( y[neuronNumber] == 0 ){
		rel = carl::Relation::LEQ;
		y[neuronNumber] = mMinValue;
	} else if (y[neuronNumber] == 1){
		rel = carl::Relation::GEQ;
		y[neuronNumber] = mMaxValue;
	} else {
		rel = carl::Relation::EQ;
		y[neuronNumber] = (mMaxValue - mMinValue) * y[neuronNumber] + mMinValue;
	}

	EvaluationResult<Number> result = hypro::z3GetInternalPoint(inputSet.shape(),inputSet.limits(),inputSet.generator(), inputSet.center(), y, neuronNumber, rel);

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			// std::cout << "Backpropagation worked -> continue backpropagation" << std::endl;
			if ( y_neuronNumber == 0 || y_neuronNumber == 1){
				y[neuronNumber] = Point<Number>( inputSet.generator() * result.optimumValue + inputSet.center() )[neuronNumber];
			} 
			return y;

		case SOLUTION::INFEAS:
			// std::cout << "Backpropagation not possible; point is result of over-approximation -> use exact here"<< std::endl;
            return Point<Number>();

		default:
			assert(result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS);
			break;
	}

	return Point<Number>();
}
}  // namespace hypro