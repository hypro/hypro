/**
 * @file LeakyReLULayer.h
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../LayerBase.h"
#include "hypro/neuralnets/network/activation_functions/LeakyReLU/LeakyReLU.h"

namespace hypro {

template <typename Number>
class LeakyReLULayer : public LayerBase<Number> {
  private:
	float mNegativeSlope = 0.01;

	/**
	 * @brief Applies the given reachability method to the input set
	 * @param inputSet THe input set
	 * @param method he reachability method
	 * @param[in] plotIntermediates If true, plot the intermediate star sets
	 * @return The resulting set after applying the reachability method
	 */
	std::vector<hypro::Starset<Number>> reachLeakyReLU( const hypro::Starset<Number>& input_star, NN_REACH_METHOD method, bool plot_intermediates ) const;

  public:
	/**
	 * @brief Default constructor
	 */
	LeakyReLULayer() = default;

	/**
	 * @brief Constructs a layer with the given size and index
	 *
	 * @param[in] layerSize The layer size
	 * @param[in] layerIndex The layer index
	 * @param[in] negativeSlope The factor for the negative part of LeakyReLU. Default: 0.01
	 */
	LeakyReLULayer( unsigned short int layerSize, unsigned short int layerIndex, float negativeSlope = 0.01 );

	/**
	 * @brief Default destructor
	 */
	~LeakyReLULayer() = default;

	/**
	 * @brief The type of the layer in the form of an enum member
	 * @return The type of the layer
	 */
	[[nodiscard]] virtual const NN_LAYER_TYPE layerType() const;

	/**
	 * @brief Applies the LeakyReLU function at the given index to the input vector
	 *
	 * @param inputVec The input vector
	 * @param i The index
	 * @return The resulting vector after applying the LeakyReLU function
	 */
	vector_t<Number> forwardPass( const vector_t<Number>& inputVec, int i ) const;

	/**
	 * @brief Applies the LeakyReLU function element-wise to the input vector
	 *
	 * @param[in] inputVec The input vector
	 * @return The resulting vector after applying the LeakyReLU function
	 */
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;

	/**
	 * @brief Applies the given reachability method to the input set at the specified index
	 *
	 * @param[in] inputSet The input set
	 * @param[in] index The index of the layer
	 * @param[in] method The reachability method
	 * @return The resulting set after applying the reachability method to the given layer
	 */
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const;

	/**
	 * @brief Applies the given reachability method to all input sets to every layer
	 *
	 * @param[in] inputSets The input sets
	 * @param[in] method The reachability method
	 * @param[in] plotIntermediates If true, plot the intermediate star sets
	 * @return The resulting set after applying the reachability method
	 */
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const;

	virtual Point<Number> propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const;

	/**
	 * @brief Serialization of the current layer.
	 * Prints the layer size and negative slope of the contained leakyReLU function to the given output stream
	 *
	 * @param[in] os The output stream to serialize the layer to
	 */
	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
		os << "LeakyReLU negative slope " << this->mNegativeSlope << std::endl;
	}
};
}  // namespace hypro

#include "LeakyReLULayer.tpp"