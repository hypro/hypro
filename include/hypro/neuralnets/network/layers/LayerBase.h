/**
 * @file LayerBase.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../../../util/logging/Logger.h"
#include "NNLayerType.h"

namespace hypro {

template <typename Number>
class LayerBase {
  protected:
	unsigned short int mLayerSize;
	unsigned short int mLayerIndex;

  public:
	LayerBase() {}
	LayerBase( unsigned short int layerSize, unsigned short int layerIndex )
		: mLayerSize( layerSize )
		, mLayerIndex( layerIndex ) {}

	// getter (virtual) for the type of the layer in the form of an enum member
	virtual const NN_LAYER_TYPE layerType() const = 0;	

	// getter for the size of the layer
	unsigned short int layerSize() const {
		return mLayerSize;
	}

	// getter for the index of the layer
	unsigned short int layerIndex() const {
		return mLayerIndex;
	}

	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputVec, NN_REACH_METHOD method, bool plotIntermediates ) const = 0;
};

}  // namespace hypro