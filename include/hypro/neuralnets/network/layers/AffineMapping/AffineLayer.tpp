/**
 * @file AffineLayer.tpp
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "AffineLayer.h"

namespace hypro {

template <typename Number>
AffineLayer<Number>::AffineLayer()
	: LayerBase<Number>() {}

template <typename Number>
AffineLayer<Number>::AffineLayer( unsigned short int layerSize, unsigned short int layerIndex, const vector_t<Number>& bias, const matrix_t<Number>& weights )
	: LayerBase<Number>( layerSize, layerIndex )
	, mBias( bias )
	, mWeights( weights ) {
	assert( bias.rows() == weights.rows() );
	assert( bias.rows() == mLayerSize );
}

template <typename Number>
const NN_LAYER_TYPE AffineLayer<Number>::layerType() const {
	return NN_LAYER_TYPE::AFFINE;
}

template <typename Number>
vector_t<Number> AffineLayer<Number>::bias() const {
	return mBias;
}

template <typename Number>
matrix_t<Number> AffineLayer<Number>::weights() const {
	return mWeights;
}

template <typename Number>
vector_t<Number> AffineLayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	return mBias + mWeights * inputVec;
}

template <typename Number>
std::vector<Starset<Number>> AffineLayer<Number>::forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	std::vector<Starset<Number>> result = std::vector<Starset<Number>>();
	result.push_back( inputSet.affineTransformation( mWeights, mBias ) );
	return result;
}

template <typename Number>
std::vector<Starset<Number>> AffineLayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	std::vector<Starset<Number>> result = std::vector<Starset<Number>>();
	int N = inputSets.size();  // number of input stars

	// #pragma omp parallel for  // TODO: try to set up the thread pool in advance (at the start of the analysis), then here at the for loops just use the existing threads
	// 	for ( int i = 0; i < N; ++i ) {
	// 		Starset<Number> temp = inputSets[i].affineTransformation( mWeights, mBias );
	// 		{
	// #pragma omp critical
	// 			result.push_back( temp );
	// 		}
	// 	}
	for ( int i = 0; i < N; ++i ) {
		result.push_back( inputSets[i].affineTransformation( mWeights, mBias ) );
	}
	return result;
}

template <typename Number>
Point<Number> AffineLayer<Number>::propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const {
	// TODO: implement a smarter way to do this backpropagation which works in all cases
	matrix_t<Number> weightsInverse = mWeights.completeOrthogonalDecomposition().pseudoInverse();
	// std::cout << "affine backpropagation" << std::endl;
	return Point<Number>(weightsInverse * (y.rawCoordinates() - mBias));
}

}  // namespace hypro