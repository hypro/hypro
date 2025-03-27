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
	~AffineLayer() {}

	virtual const NN_LAYER_TYPE layerType() const;	// getter for the type of the layer in the form of an enum member
	vector_t<Number> bias() const;
	matrix_t<Number> weights() const;

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
	virtual std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const;
	
	/**
	 * @brief Propagates back y to the previous neuron in the layer. I.e. given y, y = f(x), x \in I, return x
	 *
	 * @param[in] y, the counterexample candidate to propagate back
	 * @param[in] neuronNumber, the number of the neuron at which we apply the backpropagation
	 * @param[in] inputSet, the input set which should include the result of the backpropagation
	 * @param[in] currentSet, the set which includes the point y
	 * @return Point<Number> the backpropagated final result
	 */
	std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet, Starset<Number> knownSourceSet ) const;

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

	virtual void serialize( std::ostream& os ) const {
		os << "Layer size: " << LayerBase<Number>::mLayerSize << std::endl;
		os << "weights size: " << mWeights.rows() << " × " << mWeights.cols() << std::endl;
		// os << "weights: " << mWeights << std::endl;
		os << "bias size: " << mBias.rows() << " × " << mBias.cols() << std::endl;
		// os << "bias: " << mBias << std::endl;
	}
};

}  // namespace hypro

#include "AffineLayer.tpp"
