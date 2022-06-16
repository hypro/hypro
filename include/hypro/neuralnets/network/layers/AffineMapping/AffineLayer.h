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

	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	vector_t<Number> bias() const;
	matrix_t<Number> weights() const;

	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const;

	template <typename U>
	friend std::ostream& operator<<( std::ostream& os, const AffineLayer<U>& network );
};

template <typename Number>
std::ostream& operator<<( std::ostream& ostr, const AffineLayer<Number>& _rhs ) {
	ostr << "AffineLayer with size " << _rhs.mLayerSize << std::endl;
	ostr << "weights size: " << _rhs.mWeights.rows() << " × " << _rhs.mWeights.cols() << std::endl;
	// ostr << "weights: " << _rhs.mWeights << std::endl;
	ostr << "bias size: " << _rhs.mBias.rows() << " × " << _rhs.mBias.cols() << std::endl;
	// ostr << "bias: " << _rhs.mBias << std::endl;
	return ostr;
}

}  // namespace hypro

#include "AffineLayer.tpp"
