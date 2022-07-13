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

	virtual ~LayerBase() {}

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

	// ================== methods ==================

	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const = 0;


	// ============= utility functions =============

	virtual void serialize( std::ostream& os ) const = 0;

	template <typename U>
	friend std::ostream& operator<<( std::ostream& os, const LayerBase<U>& _rhs );
};

template <typename Number>
std::ostream& operator<<( std::ostream& os, const LayerBase<Number>& _rhs ) {
	os << "Layer type: " << _rhs.layerType()._to_string() << std::endl;
	_rhs.serialize( os );
	return os;
}

}  // namespace hypro
