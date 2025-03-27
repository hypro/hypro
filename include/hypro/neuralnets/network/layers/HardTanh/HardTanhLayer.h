/**
 * @file HardTanhLayer.h
 * @author Hana Masara <hana.masara@rwth-aachen.de>
 * @brief
 * @version 0.1
 * @date 2022-11-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include "../LayerBase.h"
#include "hypro/neuralnets/network/activation_functions/HardTanh/HardTanh.h"
#include "hypro/util/plotting/Plotter.h"

namespace hypro {

template <typename Number>
class HardTanhLayer : public LayerBase<Number> {
  private:
	Number mMinValue = -1.0;
	Number mMaxValue = 1.0;

	/**
	 * @brief Applies the given reachability method to the input set
	 *
	 * @param inputSet THe input set
	 * @param method he reachability method
	 * @param[in] plotIntermediates If true, plot the intermediate star sets
	 * @return The resulting set after applying the reachability method
	 */
	std::vector<hypro::Starset<Number>> reachHardTanh( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const;

  public:
	/**
	 * @brief Default constructor
	 */
	HardTanhLayer() = default;

	/**
	 * @brief Constructs a layer with the given size and index
	 *
	 * @param[in] layerSize The layer size
	 * @param[in] layerIndex The layer index
	 * @param[in] minValue The minimum value of the linear region range. Default: -1
	 * @param[in] maxValue The maximum value of the linear region range. Default: 1
	 */
	HardTanhLayer( unsigned short int layerSize, unsigned short int layerIndex, Number minValue = -1, Number maxValue = 1 );

	/**
	 * @brief Default destructor
	 */
	~HardTanhLayer() = default;

	/**
	 * @brief The type of the layer in the form of an enum member
	 * @return The type of the layer
	 */
	[[nodiscard]] virtual const NN_LAYER_TYPE layerType() const;

	/**
	 * @brief Applies the Hardtanh function element-wise to the input vector
	 *
	 * @param[in] inputVec The input vector
	 * @return The resulting vector after applying the Hardtanh function
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

	/**
	 * @brief Traces knownSource back to the previous neuron
	 *
	 * @param[in] knownSource the counterexample candidate to trace back
	 * @param[in] knownSourceAlpha the perdicate value corresponding to knownSource
	 * @param[in] neuronNumber the number of the neuron at which we apply tracing
	 * @param[in] newSourceSet the star which should include the new source
	 * @return the new source of the couterexample in newSourceSet
	 */
	virtual std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const;

	/**
	 * @brief Traces knownSource back through a sequence of activation function operations
	 *
	 * @param[in] knownSource the counterexample candidate to trace back
	 * @param[in] knownSourceAlpha the perdicate value corresponding to knownSource
	 * @param[in] lowerIndex, upperIndex the start and end of the sequence
	 * @param[in] newSourceSet the star which should include the new source
	 * @return the new source of the couterexample in newSourceSet
	 */
	virtual std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const;

	/**
	 * @brief Attempts to trace counterexample to a potential source neuron
	 *
	 * @param[in] knownSource the counterexample or known source to trace to the new source
	 * @param[in] alpha the predicate value for the known source
	 * @param[in] lowerIndex the number of the neuron knownSource was obtained from
	 * @param[in] upperIndex the number of the neuron for the newSourceSet
	 * @param[in] newSourceSet the set that should include the new source
	 * @return tuple<int, Point<Number>, Point<Number>> were the first number indicates the next neuron to attempt tracing or is -1 and the Points contain the new source and predicate value of it
	 */
	virtual std::tuple<int, Point<Number>, Point<Number>> traceUnsatCore( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const;

	/**
	 * @brief Serialization of the current layer.
	 * Prints the layer size and min and max value of the contained hardtanh function to the given output stream
	 *
	 * @param[in] os The output stream to serialize the layer to
	 */
	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
		os << "Hardtanh min value: " << this->mMinValue << std::endl;
		os << "Hardtanh max value: " << this->mMaxValue << std::endl;
	}
};

}  // namespace hypro

#include "HardTanhLayer.tpp"
