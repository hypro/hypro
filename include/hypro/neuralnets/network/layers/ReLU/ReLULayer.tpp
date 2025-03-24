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
		std::cout << "Neuron index:" << i << std::endl;
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
std::pair<Point<Number>,Point<Number>> ReLULayer<Number>::traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const {
	assert( neuronNumber < knownSource.dimension() );
	assert( knownSource[neuronNumber] >= 0 );
	
	EvaluationResult<Number> result;
	if ( 0 == knownSource.coordinate( neuronNumber ) ) {
		// knownSource = ReLU(x) = max(0,x) = 0 -> x <= 0
		result = hypro::z3GetInternalPoint(newSourceSet.shape(),newSourceSet.limits(),newSourceSet.generator(), newSourceSet.center(), knownSource, neuronNumber, carl::Relation::LEQ );
	} else {
		// 0 < knownSource && knownSource = ReLU(x) = max(0,x) -> knownSource = x
		result = hypro::z3GetInternalPoint( newSourceSet.shape(), newSourceSet.limits(), newSourceSet.generator(), newSourceSet.center(), knownSource );
	}

	// std::cout << "ReLU" << std::endl;

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			// std::cout << "Backpropagation worked -> continue backpropagation" << std::endl; 
			if (0 == knownSource.coordinate( neuronNumber )){
				knownSource[neuronNumber] = Point<Number>( newSourceSet.generator() * result.optimumValue + newSourceSet.center() )[neuronNumber];
			}			
            return std::make_pair(knownSource, Point<Number>(result.optimumValue));

		case SOLUTION::INFEAS:
			// std::cout << "Backpropagation not possible; point is result of over-approximation -> use exact here"<< std::endl;
            return std::make_pair(Point<Number>(), Point<Number>());

		default:
			assert(result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS);
			break;
	}

	return std::make_pair(Point<Number>(), Point<Number>());
}

template <typename Number>
std::pair<Point<Number>,Point<Number>> ReLULayer<Number>::traceSourceBack(Point<Number> newSource, Point<Number> newSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet) const{
	std::vector<carl::Relation> relations;
	for (int i = 0; i < newSourceSet.generator().rows(); i++){
		if ( upperIndex <= i && i <= lowerIndex && 0 == newSource[i] ) {
			relations.push_back( carl::Relation::LEQ);
		} else {
			relations.push_back( carl::Relation::EQ);	
		}
	}
	
	assert(relations.size() == newSourceSet.generator().rows());
	EvaluationResult<Number> result = hypro::z3GetInternalPoint(newSourceSet.shape(),newSourceSet.limits(),newSourceSet.generator(), newSourceSet.center(), newSource, relations);	
	switch ( result.errorCode ) {
		case SOLUTION::FEAS:						
            return std::make_pair(Point<Number>( newSourceSet.generator() * result.optimumValue + newSourceSet.center()), Point<Number>(result.optimumValue));
		case SOLUTION::INFEAS:
            return std::make_pair(Point<Number>(), Point<Number>());
		default:
			assert(result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS);
			break;
	}

	return std::make_pair(Point<Number>(), Point<Number>());
}

template <typename Number>
std::tuple<int, Point<Number>, Point<Number>>  ReLULayer<Number>::traceUnsatCore(Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet) const{
	std::vector<carl::Relation> relations;
	for (int i = 0; i < newSourceSet.generator().rows(); i++){
		if ( upperIndex <= i && i <= lowerIndex && 0 == knownSource[i] ) {
			relations.push_back( carl::Relation::LEQ);
		} else {
			relations.push_back( carl::Relation::EQ);	
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
