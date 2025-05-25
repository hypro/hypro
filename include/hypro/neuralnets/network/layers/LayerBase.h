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
#include "../../../representations/GeometricObjectBase.h"
#include "../../../types.h"
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
	virtual vector_t<Number> forwardPass( const vector_t<Number>& inputVec, const int dimension ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const = 0;
	virtual std::vector<Starset<Number>> forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const = 0;
	
	/** 
	 * @brief Computes forward pass of a star where the result is labled with is computation type
	 * @return A vector of stars corresponding to the reachable sets and an encoding of the computation used for the star where "0" -> over-approximation, i -> specific affine mapping named with 0 < i
	 */
	virtual std::vector<std::pair<Starset<Number>, char>> forwardPassWithHistory( const Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const = 0;

	/**
	 * @brief Traces knownSource back to the previous neuron
	 *
	 * @param[in] knownSource the counterexample candidate to trace back
	 * @param[in] knownSourceAlpha the perdicate value corresponding to knownSource
	 * @param[in] neuronNumber the number of the neuron at which we apply tracing
	 * @param[in] newSourceSet the star which should include the new source
	 * @return the new source of the couterexample in newSourceSet
	 */
	virtual std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet ) const = 0;
	
	/**
	 * @brief Traces knownSource back to the previous neuron
	 *
	 * @param[in] knownSource the counterexample candidate to trace back
	 * @param[in] knownSourceAlpha the perdicate value corresponding to knownSource
	 * @param[in] neuronNumber the number of the neuron at which we apply tracing
	 * @param[in] newSourceSet the star which should include the new source
	 * @param[in] knownSourceSet the star containing knownSource
	 * @return the new source of the couterexample in newSourceSet
	 */
	virtual std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int neuronNumber, Starset<Number> newSourceSet, Starset<Number> knownSourceSet ) const {
		return traceSourceBack( knownSource, knownSourceAlpha, neuronNumber, newSourceSet );
	};

	/**
	 * @brief Traces knownSource back through a sequence of activation function operations
	 *
	 * @param[in] knownSource the counterexample candidate to trace back
	 * @param[in] knownSourceAlpha the perdicate value corresponding to knownSource
	 * @param[in] lowerIndex, upperIndex the start and end of the sequence
	 * @param[in] newSourceSet the star which should include the new source
	 * @return the new source of the couterexample in newSourceSet
	 */
	virtual std::pair<Point<Number>, Point<Number>> traceSourceBack( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const {
		assert( false && "binary backpropagation not possible for this layertype" );
		return std::make_pair( Point<Number>(), Point<Number>() );
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
	virtual std::tuple<int, Point<Number>, Point<Number>> traceUnsatCore( Point<Number> knownSource, Point<Number> knownSourceAlpha, int lowerIndex, int upperIndex, Starset<Number> newSourceSet ) const {
		assert( false && "unsat core tracing not implemented for this layertype" );
		return std::make_tuple( -1, Point<Number>(), Point<Number>() );
	}

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
	virtual std::tuple<std::vector<int>, Point<Number>, Point<Number>> reusePredicate(Point<Number> source, Point<Number> predicate, Starset<Number> newSourceSet, int upperIndex, int lowerIndex)  const{
		// Compute new predicate value
		int varAmount = newSourceSet.generator().cols(); 	
		vector_t<Number> newPredicate;
		assert(varAmount <= predicate.dimension());
		if (varAmount < predicate.dimension()){
			newPredicate = vector_t<Number>::Zero(varAmount);
			for (int i = 0; i < varAmount; i++){
				newPredicate[i] = predicate[i];
			}
		} else {
			newPredicate = predicate.rawCoordinates();
		}
		
		// Compute corresponding starset value
		vector_t<Number> newSource = newSourceSet.center() + newSourceSet.generator() * newPredicate;
		

		
		// Check if newSource is actually a source of source
		std::vector<int> t;
		vector_t<Number> actApl = newSource;
		//std::cout << "Predicate tracing failed at: { ";
		for (int d = upperIndex; d <= lowerIndex; d++){
			actApl = forwardPass(actApl, d);
			if(actApl[d] != source[d]){
				// std::cout << d  << ", ";
				t.push_back(d);
			}
		}
		// std::cout << " }"<< std::endl;
		if (t.size() > 0) return std::make_tuple(t, Point<Number>(), Point<Number>());
		return std::make_tuple(t, Point<Number>(newSource), Point<Number>(newPredicate));
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
