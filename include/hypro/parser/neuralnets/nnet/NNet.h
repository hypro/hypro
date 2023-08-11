/**
 * Class that implements the structure of a Neural Network.
 * @file NNet.h
 * @author László Antal <antal@informatik.rwth-aachen.de>
 * @brief Class to represent simple Feedforward Neural Networks with ReLU activation functions.
 * Can also read input weights files in .nnet format.
 * @since 2022-01-20
 * @version 2022-01-20
 */

#pragma once
#include "hypro/types.h"
#include "hypro/util/logging/Logger.h"

namespace hypro {
template <typename Number>
class NNet {
  protected:
	unsigned int mNumLayers;	 // Number of layers in the network
	unsigned int mInputSize;	 // Number of inputs to the network
	unsigned int mOutputSize;	 // Number of outputs of the network
	unsigned int mMaxLayerSize;	 // Maximum size dimension of a layer in the network
	unsigned int* mLayerSizes;	 // Array of the dimensions of the layers in the network

	vector_t<Number> mMins;	   // Minimum value of inputs
	vector_t<Number> mMaxes;   // Maximum value of inputs
	vector_t<Number> mMeans;   // Array of the means used to scale the inputs and outputs
	vector_t<Number> mRanges;  // Array of the ranges used to scale the inputs and outputs

	matrix_t<Number>* mWeights;	 // Array of weights matrices of each layer
	vector_t<Number>* mBiases;	 // Array of the bias vectors of each layer

  public:
	/**
	 * @brief Default constructor of NNet class.
	 *
	 */
	NNet();

	/**
	 * @brief Builds a Neural Network from the input file.
	 *
	 * @param[in] filename  Input file name.
	 * @return NNet<Number> the resulting network with template parameter Number.
	 */
	NNet( const char* filename );

	NNet( const NNet& nnet )
		: mNumLayers( nnet.mNumLayers )
		, mInputSize( nnet.mInputSize )
		, mOutputSize( nnet.mOutputSize )
		, mMaxLayerSize( nnet.mMaxLayerSize )
		, mMins( nnet.mMins )
		, mMaxes( nnet.mMaxes )
		, mMeans( nnet.mMeans )
		, mRanges( nnet.mRanges ) {
		mLayerSizes = new unsigned int[mNumLayers + 1];
		mWeights = new matrix_t<Number>[mNumLayers];
		mBiases = new vector_t<Number>[mNumLayers];

		for ( int i = 0; i < mNumLayers; i++ ) {
			mLayerSizes[i] = nnet.mLayerSizes[i];
			mWeights[i] = nnet.mWeights[i];
			mBiases[i] = nnet.mBiases[i];
		}
		mLayerSizes[mNumLayers] = nnet.mLayerSizes[mNumLayers];
	}

	/**
	 * @brief Destructor of NNet class.
	 *
	 */
	~NNet();

	/**
	 * @brief Returns the number of layers.
	 *
	 * @return  The number of layers.
	 */
	unsigned int numLayers() const;

	/**
	 * @brief Return the input vector size.
	 *
	 * @return Input vector size.
	 */
	unsigned int inputSize() const;

	/**
	 * @brief Returns the output vector size.
	 *
	 * @return Output vector size.
	 */
	unsigned int outputSize() const;

	/**
	 * @brief Returns the maximum layer size.
	 *
	 * @return Maximum layer size.
	 */
	unsigned int maxLayerSize() const;

	/**
	 * @brief Return the size of each layer as an array.
	 *
	 * @return Unsigned int array of layer sizes.
	 */
	unsigned int* layerSizes() const;

	/**
	 * @brief Return the size of layer i.
	 *
	 * @param[in] i is the number of layer .
	 * @return Size of layer i.
	 */
	unsigned int layerSize( int i ) const;

	/**
	 * @brief Returns the vector of min values.
	 *
	 * @return Min values.
	 */
	vector_t<Number> mins() const;

	/**
	 * @brief Returns the vector of max values.
	 *
	 * @return Max values.
	 */
	vector_t<Number> maxes() const;

	/**
	 * @brief Returns the vector of mean values.
	 *
	 * @return Mean values.
	 */
	vector_t<Number> means() const;

	/**
	 * @brief Returns the vector of ranges.
	 *
	 * @return Ranges.
	 */
	vector_t<Number> ranges() const;

	/**
	 * @brief Returns the array of weight matrices of each layer.
	 *
	 * @return Array of weight matrices.
	 */
	matrix_t<Number>* weights() const;

	/**
	 * @brief Return the array of bias vectors of each layer.
	 *
	 * @return Array of bias vectors.
	 */
	vector_t<Number>* biases() const;

	/**
	 * @brief Return the weight matrix and bias vector of layer i.
	 *
	 * @param[in] i is the number of layer .
	 * @return A pair of the weight matrix and bias vector.
	 */
	std::pair<matrix_t<Number>, vector_t<Number>> layerParams( int i ) const;

	/**
	 * @brief Evaluate the Neural Network given the input vector.
	 *
	 * @param inputs[in] Input vector.
	 * @param normalizeInput[in] Optional parameter for input vector normalization.
	 * @param normalizeOutput[in] Optional parameter for output vector normalization.
	 * @return vector_t<Number> Resulting output vector.
	 */
	vector_t<Number> evaluateNetwork( const vector_t<Number>& inputs, bool normalizeInput = false, bool normalizeOutput = false ) const;
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
std::ostream& operator<<( std::ostream& ostr, const NNet<Number>& _rhs ) {
	ostr << "Number of layers: " << _rhs.numLayers() << std::endl;
	ostr << "Input size: " << _rhs.inputSize() << std::endl;
	ostr << "Output size: " << _rhs.outputSize() << std::endl;
	ostr << "Max layer size: " << _rhs.maxLayerSize() << std::endl;

	ostr << "Layer sizes: ";
	for ( int i = 0; i < _rhs.numLayers() + 1; i++ ) {
		ostr << _rhs.layerSizes()[i] << " ";
	}
	ostr << std::endl;

	ostr << "Min values: ";
	for ( int i = 0; i < _rhs.inputSize(); i++ ) {
		ostr << _rhs.mins()[i] << " ";
	}
	ostr << std::endl;

	ostr << "Max values: ";
	for ( int i = 0; i < _rhs.inputSize(); i++ ) {
		ostr << _rhs.maxes()[i] << " ";
	}
	ostr << std::endl;

	ostr << "Mean values: ";
	for ( int i = 0; i < _rhs.inputSize() + 1; i++ ) {
		ostr << _rhs.means()[i] << " ";
	}
	ostr << std::endl;

	ostr << "Ranges: ";
	for ( int i = 0; i < _rhs.inputSize() + 1; i++ ) {
		ostr << _rhs.ranges()[i] << " ";
	}
	ostr << std::endl;

	ostr << "Network weights and biases: " << std::endl;
	for ( int i = 0; i < _rhs.numLayers(); i++ ) {
		ostr << "====================== Layer" << i << " ======================" << std::endl;
		ostr << "Weights: " << std::endl;
		ostr << _rhs.weights()[i] << std::endl;
		ostr << "Biases: " << std::endl;
		ostr << _rhs.biases()[i] << std::endl;
		ostr << std::endl;
	}
	return ostr;
}

}  // namespace hypro

#include "NNet.tpp"
