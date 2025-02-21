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
#include "hypro/util/plotting/Plotter.h"
#include "HardTanhLayer.h"

namespace hypro {

template <typename Number>
HardTanhLayer<Number>::HardTanhLayer( unsigned short int layerSize, unsigned short int layerIndex, Number minValue, Number maxValue )
	: LayerBase<Number>( layerSize, layerIndex )
	, mMinValue( minValue )
	, mMaxValue( maxValue ) {
}

template <typename Number>
std::vector<hypro::Starset<Number>> HardTanhLayer<Number>::reachHardTanh( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );

	for ( auto i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				resultSet = HardTanh<Number>::exactHardTanh( i, resultSet, mMinValue, mMaxValue );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				resultSet = HardTanh<Number>::approxHardTanh( i, resultSet, mMinValue, mMaxValue );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.hardtanh", "Invalid analysis method specified" );
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
			resultSet = HardTanh<Number>::approxHardTanh( index, resultSet, mMinValue, mMaxValue );
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
// #pragma omp critical
		{ result.insert( result.end(), resultSets.begin(), resultSets.end() ); };
	}

	return result;
}

template <typename Number>
std::pair<Point<Number>,Point<Number>> HardTanhLayer<Number>::propagateCandidateBack( Point<Number> y, Point<Number> alpha, int neuronNumber, Starset<Number> inputSet ) const {
	assert( neuronNumber < y.dimension() );
	assert( mMinValue <= y[neuronNumber] && y[neuronNumber] <= mMaxValue );
	
	carl::Relation rel;
	if ( y[neuronNumber] == mMinValue ){
		rel = carl::Relation::LEQ;
	} else if (y[neuronNumber] == mMaxValue){
		rel = carl::Relation::GEQ;
	} else {
		rel = carl::Relation::EQ;
	}

	EvaluationResult<Number> result = hypro::z3GetInternalPoint(inputSet.shape(),inputSet.limits(),inputSet.generator(), inputSet.center(), y, neuronNumber, rel);

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			// std::cout << "Backpropagation worked -> continue backpropagation" << std::endl;
			if ( y[neuronNumber] == mMinValue || y[neuronNumber] == mMaxValue){
				y[neuronNumber] = Point<Number>( inputSet.generator() * result.optimumValue + inputSet.center() )[neuronNumber];
			}
			return std::make_pair(y,Point<Number>(result.optimumValue));

		case SOLUTION::INFEAS:
			// std::cout << "Backpropagation not possible; point is result of over-approximation -> use exact here"<< std::endl;
            return std::make_pair(Point<Number>(),Point<Number>());

		default:
			assert(result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS);
			break;
	}

	return std::make_pair(Point<Number>(),Point<Number>());
}

template <typename Number>
std::pair<Point<Number>,Point<Number>> HardTanhLayer<Number>::propagateCandidateBack( Point<Number> candidate, Point<Number> candidateAlpha, int lowerIndex, int upperIndex, Starset<Number> ancestorSet ) const {
	std::cout <<"Block HardTanhLayer"<<std::endl;
	std::vector<carl::Relation> relations;
	for (int i = 0; i < ancestorSet.generator().rows(); i++){
		if ( upperIndex <= i && i <= lowerIndex) {
			if ( candidate[i] == mMinValue ){
				relations.push_back(carl::Relation::LEQ);
			} else if (candidate[i] == mMaxValue){
				relations.push_back(carl::Relation::GEQ);
			} else {
				relations.push_back(carl::Relation::EQ);
			}	
		} else {
			relations.push_back( carl::Relation::EQ);	
		}
	}

	assert(relations.size() == ancestorSet.generator().rows());
	
	EvaluationResult<Number> result = hypro::z3GetInternalPoint(ancestorSet.shape(), ancestorSet.limits(), ancestorSet.generator(), ancestorSet.center(), candidate, relations);	
	switch ( result.errorCode ) {
		case SOLUTION::FEAS:						
			return std::make_pair(Point<Number>( ancestorSet.generator() * result.optimumValue + ancestorSet.center()),Point<Number>(result.optimumValue));

		case SOLUTION::INFEAS:
            return std::make_pair(Point<Number>(),Point<Number>());
		default:
			assert(result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS);
			break;
	}

	return std::make_pair(Point<Number>(),Point<Number>());
}

}  // namespace hypro