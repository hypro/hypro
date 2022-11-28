/**
 * @file NeuralNetwork.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief General wrapper class for representing a Neural Network.
 * @date 2022-06-10
 */

#pragma once
#include "../../parser/neuralnets/nnet/NNet.h"
#include "../../util/logging/Logger.h"
#include "../reachability/ReachNNMethod.h"
#include "layers/AffineMapping/AffineLayer.h"
#include "layers/HardTanh/HardTanhLayer.h"
#include "layers/LayerBase.h"
#include "layers/ReLU/ReLULayer.h"

namespace hypro {

// A Neural Network is a function F = f_1 ∘ f_2 ∘ ... ∘ f_n, where f_i is one layer of the network, i = 1..n
template <typename Number>
class NeuralNetwork {
  private:
	// properties of the neural network
	unsigned short int mNumLayers;	   // Number of layers in the network
	unsigned short int mInputSize;	   // Number of inputs to the network
	unsigned short int mOutputSize;	   // Number of outputs of the network
	unsigned short int mMaxLayerSize;  // Maximum size of a layer in the network

	// for input/output normalization purposes
	hypro::vector_t<Number> mMins;	  // Minimum value of inputs
	hypro::vector_t<Number> mMaxes;	  // Maximum value of inputs
	hypro::vector_t<Number> mMeans;	  // Array of the means used to scale the inputs and outputs
	hypro::vector_t<Number> mRanges;  // Array of the ranges used to scale the inputs and outputs

	std::list<std::shared_ptr<hypro::LayerBase<Number>>> mLayers;  // Composition of the layers

  public:
	// ======== constructors and destructor ========
	NeuralNetwork();								   // default constructor
	NeuralNetwork( const hypro::NNet<Number>& nnet );  // create NeuralNetwork from NNet object

	// other types of constructors go here, e.g. from parsers of different file formats

	~NeuralNetwork();  // destructor

	// ============ getters and setters ============
	/**
	 * @brief Returns the number of layers.
	 *
	 * @return  The number of layers.
	 */
	unsigned short int numLayers() const;

	/**
	 * @brief Returns the input vector size.
	 *
	 * @return Input vector size.
	 */
	unsigned short int inputSize() const;

	/**
	 * @brief Returns the output vector size.
	 *
	 * @return Output vector size.
	 */
	unsigned short int outputSize() const;

	/**
	 * @brief Returns the maximum layer size.
	 *
	 * @return Maximum layer size.
	 */
	unsigned short int maxLayerSize() const;

	/**
	 * @brief Returns the vector of min values.
	 *
	 * @return Min values.
	 */
	hypro::vector_t<Number> mins() const;

	/**
	 * @brief Returns the vector of max values.
	 *
	 * @return Max values.
	 */
	hypro::vector_t<Number> maxes() const;

	/**
	 * @brief Returns the vector of mean values.
	 *
	 * @return Mean values.
	 */
	hypro::vector_t<Number> means() const;

	/**
	 * @brief Returns the vector of ranges.
	 *
	 * @return Ranges.
	 */
	hypro::vector_t<Number> ranges() const;

	/**
	 * @brief Retun an ordered list of the layers of the Neural Network.
	 * @return The list of Layer objects of the network.
	 */
	std::list<std::shared_ptr<LayerBase<Number>>> layers() const;

	/**
	 * @brief Returns the Layer of the Neural Network corresponding to the specified index
	 * @param[in] index - the number of the layer
	 * @return The required Layer object
	 */
	std::shared_ptr<LayerBase<Number>> layers( int index ) const;

	// ============= utility functions =============
	// e.g. printing the network
	template <typename U>
	friend std::ostream& operator<<( std::ostream& os, const NeuralNetwork<U>& network );

	// ================== methods ==================
	// e.g. evaluate point, evaluate set, verify
	/**
	 * @brief Evaluate the Neural Network given the input vector.
	 *
	 * @param inputVec[in] Input vector.
	 * @param normalizeInput[in] Optional parameter for input vector normalization.
	 * @param normalizeOutput[in] Optional parameter for output vector normalization.
	 * @return vector_t<Number> Resulting output vector.
	 */
	hypro::vector_t<Number> forwardPass( const hypro::vector_t<Number>& inputVec, bool normalizeInput = false, bool normalizeOutput = false ) const;

	/**
	 * @brief Evaluate the Neural Network given the input set.
	 *
	 * @param inputSet[in] The input set.
	 * @param method[in] The reachability analysis method.
	 * @param plotIntermediates[in] Flag for plotting intermediate stars.
	 * @return std::vector<hypro::Starset<Number>> Resulting output set.
	 */
	std::vector<hypro::Starset<Number>> forwardPass( const hypro::Starset<Number>& inputSet, hypro::NN_REACH_METHOD method, bool plotIntermediates = false ) const;

	/**
	 * @brief
	 *
	 * @param inputSet[in] The input set.
	 * @param safeSet[in] The safe set.
	 * @param method[in] The reachability analysis method.
	 * @param plotIntermediates[in] Flag for plotting intermediate stars.
	 * @return boolean which indicates if the Neural Network is safe.
	 */
	bool verifyNetwork( const hypro::HPolytope<Number>& inputSet, const hypro::HPolytope<Number>& safeSet, hypro::NN_REACH_METHOD method = hypro::NN_REACH_METHOD::EXACT, bool plotIntermediates = false ) const;
};

/**
 * @brief Outstream operator.
 *
 * @tparam The template parameter is Number.
 * @param ostr The outstream.
 * @param _rhs The neural network.
 * @return A reference to the outstream.
 */
template <typename Number>
std::ostream& operator<<( std::ostream& ostr, const NeuralNetwork<Number>& _rhs ) {
	ostr << "Number of layers: " << _rhs.mNumLayers << std::endl;
	ostr << "Input size: " << _rhs.mInputSize << std::endl;
	ostr << "Output size: " << _rhs.mOutputSize << std::endl;
	ostr << "Max layer size: " << _rhs.mMaxLayerSize << std::endl;

	ostr << "Min values: ";
	for ( int i = 0; i < _rhs.mInputSize; i++ ) {
		ostr << _rhs.mMins[i] << " ";
	}
	ostr << std::endl;

	ostr << "Max values: ";
	for ( int i = 0; i < _rhs.mInputSize; i++ ) {
		ostr << _rhs.mMaxes[i] << " ";
	}
	ostr << std::endl;

	ostr << "Mean values: ";
	for ( int i = 0; i < _rhs.mInputSize + 1; i++ ) {
		ostr << _rhs.mMeans[i] << " ";
	}
	ostr << std::endl;

	ostr << "Ranges: ";
	for ( int i = 0; i < _rhs.mInputSize + 1; i++ ) {
		ostr << _rhs.mRanges[i] << " ";
	}
	ostr << std::endl;

	ostr << "Layers: " << std::endl;
	for ( auto layer : _rhs.mLayers ) {
		ostr << "<------------->" << std::endl;
		ostr << "Layer index: " << layer->layerIndex() << std::endl;
		ostr << ( *layer );
		ostr << "<------------->" << std::endl;
	}
	ostr << std::endl;

	return ostr;
}

}  // namespace hypro

#include "NeuralNetwork.tpp"
