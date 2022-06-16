/**
 * @file ReLULayer.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../../activation_functions/ReLU.h"
#include "../LayerBase.h"

namespace hypro {

template <typename Number>
class ReLULayer : public LayerBase<Number> {
  private:

  public:
	ReLULayer();
	ReLULayer( unsigned short int layerSize, unsigned short int layerIndex );
	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputVec, NN_REACH_METHOD method, bool plotIntermediates ) const;

	template <typename U>
	friend std::ostream& operator<<( std::ostream& os, const ReLULayer<U>& network );

  private:
	std::vector<hypro::Starset<Number>> reachReLU( const hypro::Starset<Number>& input_star1, NN_REACH_METHOD method, bool plot_intermediates ) const;
};

template <typename Number>
std::ostream& operator<<( std::ostream& ostr, const ReLULayer<Number>& _rhs ) {
	ostr << "ReluLayer with size " << _rhs.mLayerSize << std::endl;
	return ostr;
}

}  // namespace hypro

#include "ReLULayer.tpp"
