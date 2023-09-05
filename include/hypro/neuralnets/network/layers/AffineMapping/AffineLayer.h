/**
 * @file AffineLayer.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../LayerBase.h"

namespace hypro {

template <typename Number>
class AffineLayer : public LayerBase<Number> {
  private:
	vector_t<Number> mBias;
	matrix_t<Number> mWeights;

  public:
	AffineLayer();
	AffineLayer( unsigned short int layerSize, unsigned short int layerIndex, const vector_t<Number>& bias, const matrix_t<Number>& weights );
	~AffineLayer() {}

	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	vector_t<Number> bias() const;
	matrix_t<Number> weights() const;

	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const;

	virtual Point<Number> propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const;

	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
		os << "weights size: " << mWeights.rows() << " × " << mWeights.cols() << std::endl;
		// os << "weights: " << mWeights << std::endl;
		os << "bias size: " << mBias.rows() << " × " << mBias.cols() << std::endl;
		// os << "bias: " << mBias << std::endl;
	}
};

}  // namespace hypro

#include "AffineLayer.tpp"
