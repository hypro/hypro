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

#include "hypro/util/plotting/Plotter.h"
#include "StepFunctionLayer.h"

namespace hypro {
template <typename Number>
StepFunctionLayer<Number>::StepFunctionLayer( unsigned short int layerSize, unsigned short int layerIndex, Number value, Number minValue, Number maxValue )
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
			case NN_REACH_METHOD::OVERAPPRX:
				resultSet = StepFunction<Number>::approxStepFunction( i, resultSet, mValue, mMinValue, mMaxValue );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.stepFunction", "Invalid analysis method specified" );
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
			resultSet = StepFunction<Number>::exactStepFunction( index, resultSet, mValue, mMinValue, mMaxValue );
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			resultSet = StepFunction<Number>::approxStepFunction( index, resultSet, mValue, mMinValue, mMaxValue );
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
		// #pragma omp critical
		{ result.insert( result.end(), resultSets.begin(), resultSets.end() ); };
	}

	return result;
}

template <typename Number>
std::pair<Point<Number>,Point<Number>> StepFunctionLayer<Number>::propagateCandidateBack( Point<Number> y, Point<Number> alpha, int neuronNumber, Starset<Number> inputSet ) const {
	assert( neuronNumber < y.dimension() );
	
	carl::Relation rel;
	if ( mMinValue == y[neuronNumber] ) {
		if ( mMinValue == mMaxValue ) {
			rel = carl::Relation::NEQ;
		} else {
			rel = carl::Relation::LESS;
		}
	} else if ( mMaxValue == y[neuronNumber] ) {
		rel = carl::Relation::GEQ;
	} else {
		//If the result of UnitStep is neither of the bounds, it is the result of over-approximation
		return std::make_pair(Point<Number>(), Point<Number>());
	}
	y[neuronNumber] = mValue;
	EvaluationResult<Number> result = hypro::z3GetInternalPoint( inputSet.shape(), inputSet.limits(), inputSet.generator(), inputSet.center(), y, neuronNumber, rel );

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			// std::cout << "Backpropagation worked -> continue backpropagation" << std::endl;
			y[neuronNumber] = Point<Number>( inputSet.generator() * result.optimumValue + inputSet.center() )[neuronNumber];
			return std::make_pair(y, Point<Number>(result.optimumValue));

		case SOLUTION::INFEAS:
			// std::cout << "Backpropagation not possible; point is result of over-approximation -> use exact here"<< std::endl;
			return std::make_pair(Point<Number>(), Point<Number>());

		default:
			assert( result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS );
			break;
	}

	return std::make_pair(Point<Number>(), Point<Number>());
}

template <typename Number>
std::pair<Point<Number>,Point<Number>> StepFunctionLayer<Number>::propagateCandidateBack( Point<Number> candidate, Point<Number> candidateAlpha, int lowerIndex, int upperIndex, Starset<Number> ancestorSet ) const {
	std::cout << "Block StepFunction" << std::endl;
	std::vector<carl::Relation> relations;

	for ( int i = 0; i < ancestorSet.generator().rows(); i++ ) {
		if ( upperIndex <= i && i <= lowerIndex ) {
			if ( mMinValue == candidate[i] ) {
				if ( mMinValue == mMaxValue ) {
					relations.push_back( carl::Relation::NEQ );
				} else {
					relations.push_back( carl::Relation::LESS );
				}
			} else if ( mMaxValue == candidate[i] ) {
				relations.push_back( carl::Relation::GEQ );
			} else {
				// If the result of UnitStep is neither of the bounds, it is the result of over-approximation
				return std::make_pair(Point<Number>(), Point<Number>());
			}
			candidate[i] = mValue;
		} else {
			relations.push_back( carl::Relation::EQ );
		}
	}

	assert( relations.size() == ancestorSet.generator().rows() );
	EvaluationResult<Number> result = hypro::z3GetInternalPoint( ancestorSet.shape(), ancestorSet.limits(), ancestorSet.generator(), ancestorSet.center(), candidate, relations );

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			return std::make_pair(Point<Number>( ancestorSet.generator() * result.optimumValue + ancestorSet.center() ), Point<Number>(result.optimumValue));
		case SOLUTION::INFEAS:
			return std::make_pair(Point<Number>(), Point<Number>());
		default:
			assert( result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS );
			break;
	}

	return std::make_pair(Point<Number>(), Point<Number>());
}

template <typename Number>
std::tuple<int, Point<Number>, Point<Number>>  StepFunctionLayer<Number>::traceUnsatCore(Point<Number> knownSource, Point<Number> alpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet) const{
	std::vector<carl::Relation> relations;
	for (int i = 0; i < newSourceSet.generator().rows(); i++){
		if ( upperIndex <= i && i <= lowerIndex ) {
			if ( mMinValue == knownSource[i] ) {
				if ( mMinValue == mMaxValue ) {
					relations.push_back( carl::Relation::NEQ );
				} else {
					relations.push_back( carl::Relation::LESS );
				}
			} else if ( mMaxValue == knownSource[i] ) {
				relations.push_back( carl::Relation::GEQ );
			} else {
				// If the result of UnitStep is neither of the bounds, it is the result of over-approximation
				return std::make_pair(Point<Number>(), Point<Number>());
			}
			knownSource[i] = mValue;
		} else {
			relations.push_back( carl::Relation::EQ );
		}
	}
	
	assert(relations.size() == newSourceSet.generator().rows());
	std::pair<EvaluationResult <Number>, std::vector<int>> result = hypro::z3GetInternalPointWithCore(newSourceSet.shape(),newSourceSet.limits(),newSourceSet.generator(), newSourceSet.center(), knownSource, relations);	
	switch ( result.first.errorCode ) {
		case SOLUTION::FEAS:						
            return std::make_tuple(-1, Point<Number>( newSourceSet.generator() * result.first.optimumValue + newSourceSet.center()), Point<Number>(result.first.optimumValue));
		case SOLUTION::INFEAS:{
			std::vector<int> unsatCore = result.second;
			int next = -1;
			for (int i : unsatCore){
				if ( next < i && upperIndex < i && i < lowerIndex ){
					next = i;
				}	
			}
			// If the unsable part of the unsatCore is empty, default to binary search 
			if (next == -1){ 
				next = upperIndex + 1;
			}
            return std::make_tuple(next, Point<Number>(), Point<Number>());
		}
		default:
			assert(result.first.errorCode == SOLUTION::FEAS || result.first.errorCode == SOLUTION::INFEAS);
			break;
	}
	return std::make_tuple(-1, Point<Number>(), Point<Number>());
}

}  // namespace hypro
