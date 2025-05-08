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
#include "LeakyReLULayer.h"
#include "hypro/util/plotting/Plotter.h"

namespace hypro {

template <typename Number>
LeakyReLULayer<Number>::LeakyReLULayer( unsigned short layerSize, unsigned short layerIndex, Number negativeSlope )
	: LayerBase<Number>( layerSize, layerIndex )
	, mNegativeSlope( negativeSlope ) {
	if ( negativeSlope <= Number( 0 ) || negativeSlope >= Number( 0 ) ) {
		FATAL( "hypro.neuralnets.activation_functions.LeakyReLU", "Invalid value for the negative slope ( 0 < negative slope < 1)" );
	}
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLULayer<Number>::reachLeakyReLU( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();

	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	for ( auto i = 0; i < inputSet.generator().rows(); i++ ) {
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				resultSet = LeakyReLU<Number>::exactLeakyReLU( i, resultSet, mNegativeSlope );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
				resultSet = LeakyReLU<Number>::approxLeakyReLU( i, resultSet, mNegativeSlope );
				break;
			default:
				FATAL( "hypro.neuralnets.activation_functions.LeakyReLU", "Invalid analysis method specified" );
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
const NN_LAYER_TYPE LeakyReLULayer<Number>::layerType() const {
	return NN_LAYER_TYPE::LEAKY_RELU;
}

template <typename Number>
vector_t<Number> LeakyReLULayer<Number>::forwardPass( const vector_t<Number>& inputVec, const int dimension ) const {
	auto outputVec = inputVec;
	outputVec[dimension] = outputVec[dimension] >= 0 ? outputVec[dimension] : ( outputVec[dimension] * mNegativeSlope );
	return outputVec;
}

template <typename Number>
vector_t<Number> LeakyReLULayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	auto outputVec = inputVec;
	for ( int i = 0; i < outputVec.size(); ++i ) {
		outputVec[i] = outputVec[i] >= 0 ? outputVec[i] : ( outputVec[i] * mNegativeSlope );
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> LeakyReLULayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	auto resultSet = std::vector<hypro::Starset<Number>>();
	resultSet.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			resultSet = LeakyReLU<Number>::exactLeakyReLU( index, resultSet, mNegativeSlope );
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			resultSet = LeakyReLU<Number>::approxLeakyReLU( index, resultSet, mNegativeSlope );
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

template <typename Number>
std::pair<Point<Number>, Point<Number>> LeakyReLULayer<Number>::traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const {
	assert( neuronNumber < knownSource.dimension() );

	if ( knownSource.coordinate( neuronNumber ) < 0 ) {
		// knownSource = LeakyReLU(x) = max(mNegativeSlope * x,x) < 0 -> x = (knownSource/mNegativeSlope)
		knownSource[neuronNumber] = ( 1 / mNegativeSlope ) * knownSource[neuronNumber];
	}  // Otherwise x = y

	EvaluationResult<Number> result = hypro::z3GetInternalPoint( newSourceSet.shape(), newSourceSet.limits(), newSourceSet.generator(), newSourceSet.center(), knownSource );
	// std::cout << "ReLU" << std::endl;

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			// std::cout << "Backpropagation worked -> continue backpropagation" << std::endl;
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
std::pair<Point<Number>, Point<Number>> LeakyReLULayer<Number>::traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const {
	for ( int i = 0; i < newSourceSet.generator().rows(); i++ ) {
		if ( upperIndex <= i && i <= lowerIndex && knownSource[i] < 0 ) {
			knownSource[i] = ( 1 / mNegativeSlope ) * knownSource[i];
		}
	}

	EvaluationResult<Number> result = hypro::z3GetInternalPoint( newSourceSet.shape(), newSourceSet.limits(), newSourceSet.generator(), newSourceSet.center(), knownSource );

	switch ( result.errorCode ) {
		case SOLUTION::FEAS:
			return std::make_pair( knownSource, Point<Number>( result.optimumValue ) );
		case SOLUTION::INFEAS:
			return std::make_pair( Point<Number>(), Point<Number>() );
		default:
			assert( result.errorCode == SOLUTION::FEAS || result.errorCode == SOLUTION::INFEAS );
			break;
	}

	return std::make_pair( Point<Number>(), Point<Number>() );
}

template <typename Number>
std::tuple<int, Point<Number>, Point<Number>> LeakyReLULayer<Number>::traceUnsatCore( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const {
	std::vector<carl::Relation> relations;
	for ( int i = 0; i < newSourceSet.generator().rows(); i++ ) {
		if ( upperIndex <= i && i <= lowerIndex && knownSource[i] < 0 ) {
			knownSource[i] = ( 1 / mNegativeSlope ) * knownSource[i];
		}
		relations.push_back( carl::Relation::LEQ );
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