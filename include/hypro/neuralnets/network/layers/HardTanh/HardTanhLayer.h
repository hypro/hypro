/**
 * @file HardTanhLayer.h
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
class HardTanhLayer : public LayerBase<Number> {
  private:
  public:
	~HardTanhLayer() {}
	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	virtual unsigned short int layerSize() const;	// getter for the size of the layer
	virtual unsigned short int layerIndex() const;	// getter for the index of the layer
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const;
	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
	}
  protected:
};

}  // namespace hypro

#include "HardTanhLayer.tpp"
