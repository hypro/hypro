/**
 * @file GeneralPiecewiseLinearLayer.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2024-12-09
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../LayerBase.h"
#include "hypro/neuralnets/network/activation_functions/GeneralPiecewiseLinear/GeneralPiecewiseLinear.h"

namespace hypro {

template <typename Number>
class GeneralPiecewiseLinearLayer : public LayerBase<Number> {
  private:
	size_t mNumPieces;
	std::vector<Number> mLowerBounds;
	std::vector<Number> mUpperBounds;
	std::vector<Number> mSlopes;
	std::vector<Number> mOffsets;
  public:
	GeneralPiecewiseLinearLayer();
	GeneralPiecewiseLinearLayer( unsigned short int layerSize, unsigned short int layerIndex, size_t numPieces,
								 const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
								 const std::vector<Number>& slopes, const std::vector<Number>& offsets );
	~GeneralPiecewiseLinearLayer() {}

	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	
	vector_t<Number> forwardPass( const vector_t<Number>& inputVec, int i ) const;
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, hypro::NN_REACH_METHOD method ) const;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, hypro::NN_REACH_METHOD method, bool plotIntermediates ) const;

	virtual Point<Number> propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const;

	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
	}

  private:
	std::vector<hypro::Starset<Number>> reachGeneralPiecewiseLinear( const hypro::Starset<Number>& input_star1, hypro::NN_REACH_METHOD method, bool plot_intermediates ) const;
};

}  // namespace hypro

#include "GeneralPiecewiseLinearLayer.tpp"
