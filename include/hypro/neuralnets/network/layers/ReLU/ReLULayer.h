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
#include "../LayerBase.h"
#include "hypro/neuralnets/network/activation_functions/ReLU/ReLU.h"

namespace hypro {

template <typename Number>
class ReLULayer : public LayerBase<Number> {
  private:
  public:
	ReLULayer();
	ReLULayer( unsigned short int layerSize, unsigned short int layerIndex );
	~ReLULayer() {}

	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec, const int dimension ) const;
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const;
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
	virtual std::pair<Point<Number>,Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const;

	/**
	 * @brief Traces knownSource back through a sequence of activation function operations
	 *
	 * @param[in] knownSource the counterexample candidate to trace back
	 * @param[in] knownSourceAlpha the perdicate value corresponding to knownSource
	 * @param[in] lowerIndex, upperIndex the start and end of the sequence
	 * @param[in] newSourceSet the star which should include the new source
	 * @return the new source of the couterexample in newSourceSet
	 */
	virtual std::pair<Point<Number>,Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet) const;

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
	virtual std::tuple<int, Point<Number>, Point<Number>> traceUnsatCore(Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet) const;

	/**
	* @brief Attempts to trace counterexample to a potential source neuron by reusing part of the predicate value
	*
	* @param[in] source the counterexample or a known source to trace to the new source
	* @param[in] predicate the predicate value for the source
	* @param[in] lowerIndex the number of the neuron source was obtained from
	* @param[in] upperIndex the number of the neuron for the newSourceSet
	* @param[in] newSourceSet the set that should include the new source
	* @return pair<Point<Number>, Point<Number>> the int is -1 or the dimension tracing failed and the Points contain the new source and new predicate value or empty Points
	*/
	// virtual std::tuple<std::vector<int>, Point<Number>, Point<Number>> reusePredicate(Point<Number> source, Point<Number> predicate, Starset<Number> newSourceSet, int upperIndex, int lowerIndex) const;

	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
	}

  private:
	std::vector<hypro::Starset<Number>> reachReLU( const hypro::Starset<Number>& input_star1, NN_REACH_METHOD method, bool plot_intermediates ) const;
};

}  // namespace hypro

#include "ReLULayer.tpp"
