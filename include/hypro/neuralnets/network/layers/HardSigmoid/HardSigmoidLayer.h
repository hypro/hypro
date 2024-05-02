/**
 * @file HardSigmoidLayer.h
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-12-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include "../LayerBase.h"
#include "hypro/neuralnets/network/activation_functions/HardSigmoid/HardSigmoid.h"
#include "hypro/util/plotting/Plotter.h"

namespace hypro {

template <typename Number>
class HardSigmoidLayer : public LayerBase<Number> {
  private:
	float mMinValue = -3.0;
	float mMaxValue = 3.0;

	/**
	 * @brief Applies the given reachability method to the input set
	 * @param inputSet THe input set
	 * @param method he reachability method
	 * @param[in] plotIntermediates If true, plot the intermediate star sets
	 * @return The resulting set after applying the reachability method
	 */
	std::vector<hypro::Starset<Number>> reachHardSigmoid( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const;

  public:
	/**
	 * @brief Default constructor
	 */
	HardSigmoidLayer() = default;

	/**
	 * @brief Constructs a layer with the given size and index
	 *
	 * @param[in] layerSize The layer size
	 * @param[in] layerIndex The layer index
	 */
	HardSigmoidLayer( unsigned short int layerSize, unsigned short int layerIndex, float minValue = -3.0, float maxValue = 3.0 );

	/**
	 * @brief Default destructor
	 */
	~HardSigmoidLayer() = default;

	/**
	 * @brief The type of the layer in the form of an enum member
	 * @return The type of the layer
	 */
	[[nodiscard]] virtual const NN_LAYER_TYPE layerType() const;

	/**
	 * @brief Applies the HardSigmoid function element-wise to the input vector
	 *
	 * @param inputVec
	 * @return The resulting vector after applying the HardSigmoid function
	 */
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;

	/**
	 * @brief Applies the given reachability method to the input set at the specified index
	 *
	 * @param inputSet The input set
	 * @param index The index of the layer
	 * @param method The reachability method
	 * @return The resulting set after applying the reachability method to the given layer
	 */
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const;

	/**
	 * @brief Applies the given reachability method to all input sets to every layer
	 *
	 * @param inputSets The input sets
	 * @param method The reachability method
	 * @param plotIntermediates If true, plot the intermediate star sets
	 * @return The resulting set after applying the reachability method
	 */
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const;

	virtual Point<Number> propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const;

	/**
	 * @brief Serialization of the current layer.
	 * Prints the layer size
	 *
	 * @param os The output stream to serialize the layer to
	 */
	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
		os << "HardSigmoid min value: " << this->mMinValue << std::endl;
		os << "HardSigmoid max value: " << this->mMaxValue << std::endl;
	}
};
}  // namespace hypro

#include "HardSigmoidLayer.tpp"
