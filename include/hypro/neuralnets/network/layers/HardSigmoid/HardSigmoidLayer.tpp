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
HardSigmoidLayer<Number>::HardSigmoidLayer( unsigned short int layerSize, unsigned short int layerIndex, Number minValue, Number maxValue )
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
std::pair<Point<Number>, Point<Number>> HardSigmoidLayer<Number>::traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const {
	assert( neuronNumber < knownSource.dimension() );
	assert( 0 <= knownSource[neuronNumber] && knownSource[neuronNumber] <= 1 );

	Number knownSource_neuronNumber = knownSource[neuronNumber];
	carl::Relation rel;
	if ( knownSource[neuronNumber] == 0 ) {
		rel = carl::Relation::LEQ;
		knownSource[neuronNumber] = mMinValue;
	} else if ( knownSource[neuronNumber] == 1 ) {
		rel = carl::Relation::GEQ;
		knownSource[neuronNumber] = mMaxValue;
	} else {
		rel = carl::Relation::EQ;
		knownSource[neuronNumber] = ( mMaxValue - mMinValue ) * knownSource[neuronNumber] + mMinValue;
	}

	EvaluationResult<Number> result = hypro::z3GetInternalPoint( newSourceSet.shape(), newSourceSet.limits(), newSourceSet.generator(), newSourceSet.center(), knownSource, neuronNumber, rel );

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			// std::cout << "Backpropagation worked -> continue backpropagation" << std::endl;
			if ( knownSource_neuronNumber == 0 || knownSource_neuronNumber == 1 ) {
				knownSource[neuronNumber] = Point<Number>( newSourceSet.generator() * result.optimumValue + newSourceSet.center() )[neuronNumber];
			}
			return std::make_pair( knownSource, Point<Number>( result.optimumValue ) );

		case SOLUTION::INFEAS:
			// std::cout << "Backpropagation not possible; point is result of over-approximation -> use exact here"<< std::endl;
			return std::make_pair( Point<Number>(), Point<Number>() );

		default:
			assert( result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS );
			break;
	}

	return std::make_pair( Point<Number>(), Point<Number>() );
}

template <typename Number>
std::pair<Point<Number>, Point<Number>> HardSigmoidLayer<Number>::traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const {
	std::vector<carl::Relation> relations;
	for ( int i = 0; i < newSourceSet.generator().rows(); i++ ) {
		if ( upperIndex <= i && i <= lowerIndex ) {
			if ( 0 == knownSource[i] ) {
				knownSource[i] = mMinValue;
				relations.push_back( carl::Relation::LEQ );
			} else if ( 1 == knownSource[i] ) {
				knownSource[i] = mMaxValue;
				relations.push_back( carl::Relation::GEQ );
			} else {
				knownSource[i] = ( mMaxValue - mMinValue ) * knownSource[i] + mMinValue;
				relations.push_back( carl::Relation::EQ );
			}
		} else {
			relations.push_back( carl::Relation::EQ );
		}
	}

	assert( relations.size() == newSourceSet.generator().rows() );

	EvaluationResult<Number> result = hypro::z3GetInternalPoint( newSourceSet.shape(), newSourceSet.limits(), newSourceSet.generator(), newSourceSet.center(), knownSource, relations );
	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			return std::make_pair( Point<Number>( newSourceSet.generator() * result.optimumValue + newSourceSet.center() ), Point<Number>( result.optimumValue ) );
		case SOLUTION::INFEAS:
			return std::make_pair( Point<Number>(), Point<Number>() );
		default:
			assert( result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS );
			break;
	}

	return std::make_pair( Point<Number>(), Point<Number>() );
}

template <typename Number>
std::tuple<int, Point<Number>, Point<Number>> HardSigmoidLayer<Number>::traceUnsatCore( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const {
	std::vector<carl::Relation> relations;
	for ( int i = 0; i < newSourceSet.generator().rows(); i++ ) {
		if ( upperIndex <= i && i <= lowerIndex ) {
			if ( 0 == knownSource[i] ) {
				knownSource[i] = mMinValue;
				relations.push_back( carl::Relation::LEQ );
			} else if ( 1 == knownSource[i] ) {
				knownSource[i] = mMaxValue;
				relations.push_back( carl::Relation::GEQ );
			} else {
				knownSource[i] = ( mMaxValue - mMinValue ) * knownSource[i] + mMinValue;
				relations.push_back( carl::Relation::EQ );
			}
		} else {
			relations.push_back( carl::Relation::EQ );
		}
	}

	assert( relations.size() == newSourceSet.generator().rows() );
	std::pair<EvaluationResult<Number>, std::vector<int>> result = hypro::z3GetInternalPointWithCore( newSourceSet.shape(), newSourceSet.limits(), newSourceSet.generator(), newSourceSet.center(), knownSource, relations );
	switch ( result.first.errorCode ) {
		case SOLUTION::FEAS:
			return std::make_tuple( -1, Point<Number>( newSourceSet.generator() * result.first.optimumValue + newSourceSet.center() ), Point<Number>( result.first.optimumValue ) );
		case SOLUTION::INFEAS: {
			std::vector<int> unsatCore = result.second;
			int next = -1;
			for ( int i : unsatCore ) {
				if ( next < i && upperIndex < i && i < lowerIndex ) {
					next = i;
				}
			}
			// If the unsable part of the unsatCore is empty, default to binary search
			if ( next == -1 ) {
				next = upperIndex + 1;
			}
			return std::make_tuple( next, Point<Number>(), Point<Number>() );
		}
		default:
			assert( result.first.errorCode == SOLUTION::FEAS || result.first.errorCode == SOLUTION::INFEAS );
			break;
	}
	return std::make_tuple( -1, Point<Number>(), Point<Number>() );
}

}  // namespace hypro