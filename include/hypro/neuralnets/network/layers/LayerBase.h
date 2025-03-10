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
#include "../../../types.h"
#include "../../../representations/GeometricObjectBase.h"
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

	/**
	 * @brief Get the size of the layer
	 * @return The size of the layer
	 */
	[[nodiscard]] unsigned short int layerSize() const {
		return mLayerSize;
	}

	/**
	 * @brief Get the index of the layer
	 * @return The index of the layer
	 */
	[[nodiscard]] unsigned short int layerIndex() const {
		return mLayerIndex;
	}

	// ================== methods ==================

	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const = 0;

	/**
	 * @brief Propagates back y to the previous neuron in the layer. I.e. given y, y = f(x), x \in I, return x
	 * 
	 * @param[in] y, the counterexample candidate to propagate back 
	 * @param[in] neuronNumber, the number of the neuron at which we apply the backpropagation
	 * @param[in] inputSet, the input set which should include the result of the backpropagation
	 * @return Point<Number> the backpropagated final result
	 */
	virtual std::pair<Point<Number>,Point<Number>> propagateCandidateBack( Point<Number> y, Point<Number> alpha, int neuronNumber, Starset<Number> inputSet ) const = 0;
	virtual std::pair<Point<Number>,Point<Number>> propagateCandidateBack( Point<Number> y, Point<Number> alpha, int neuronNumber, Starset<Number> inputSet, Starset<Number> currentSet) const {
		return propagateCandidateBack(y, alpha, neuronNumber, inputSet );
	};
	virtual std::pair<Point<Number>,Point<Number>> propagateCandidateBack(Point<Number> candidate, Point<Number> candidateAlpha, int lowerIndex, int upperIndex, Starset<Number> ancestorSet) const {
		assert(false && "binary backpropagation not possible for this layertype");
		return std::make_pair(Point<Number>(), Point<Number>());
	}
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
	virtual std::tuple<int, Point<Number>, Point<Number>> traceUnsatCore(Point<Number> knownSource, Point<Number> alpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet) const{
		assert(false && "unsat core tracing not implemented for this layertype");
		return std::make_tuple(-1, Point<Number>(), Point<Number>());
	}

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
