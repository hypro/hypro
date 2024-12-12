#include "NeuralNetwork.h"

namespace hypro {

// ======== constructors and destructor ========
template <typename Number>
NeuralNetwork<Number>::NeuralNetwork()
	: mNumLayers( 0 )
	, mInputSize( 0 )
	, mOutputSize( 0 )
	, mMaxLayerSize( 0 )
	, mMins()
	, mMaxes()
	, mMeans()
	, mRanges()
	, mLayers() {}

template <typename Number>
NeuralNetwork<Number>::NeuralNetwork( const hypro::NNet<Number>& nnet )
	: mNumLayers( 2 * nnet.numLayers() - 1 )  // for the NNet format we have n affine layers + (n - 1) relu layers after each
	, mInputSize( nnet.inputSize() )
	, mOutputSize( nnet.outputSize() )
	, mMaxLayerSize( nnet.maxLayerSize() )
	, mMins( nnet.mins() )
	, mMaxes( nnet.maxes() )
	, mMeans( nnet.means() )
	, mRanges( nnet.ranges() ) {
	// initialize an empty list
	mLayers = std::list<std::shared_ptr<LayerBase<Number>>>();

	// iterate over the layers of the NNet and create the corresponding layers
	unsigned short int prevLayerSize = mInputSize;
	assert( mInputSize == nnet.layerSize( 0 ) );
	for ( unsigned short int i = 0; i < nnet.numLayers(); ++i ) {
		unsigned short int layerSize = nnet.layerSize( i + 1 );
		std::pair<hypro::matrix_t<Number>, hypro::vector_t<Number>> layerParams = nnet.layerParams( i );
		hypro::matrix_t<Number> weights = layerParams.first;
		hypro::vector_t<Number> bias = layerParams.second;
		assert( weights.rows() == layerSize );
		assert( weights.cols() == prevLayerSize );
		prevLayerSize = layerSize;

		// AffineLayer<Number>* affLayer = new AffineLayer<Number>( layerSize, mLayers.size(), bias, weights );
		// mLayers.push_back( affLayer );
		mLayers.push_back( std::make_shared<AffineLayer<Number>>( layerSize, mLayers.size(), bias, weights ) );
		if ( i < nnet.numLayers() - 1 ) {
			// ReLULayer<Number>* relLayer = new ReLULayer<Number>( layerSize, mLayers.size() );
			// mLayers.push_back( relLayer );
			mLayers.push_back( std::make_shared<ReLULayer<Number>>( layerSize, mLayers.size() ) );
		}
	}
	assert( prevLayerSize == mOutputSize );
}

template <typename Number>
NeuralNetwork<Number>::~NeuralNetwork() {
}

// ============ getters and setters ============
template <typename Number>
unsigned short int NeuralNetwork<Number>::numLayers() const {
	return mNumLayers;
}

template <typename Number>
unsigned short int NeuralNetwork<Number>::inputSize() const {
	return mInputSize;
}

template <typename Number>
unsigned short int NeuralNetwork<Number>::outputSize() const {
	return mOutputSize;
}

template <typename Number>
unsigned short int NeuralNetwork<Number>::maxLayerSize() const {
	return mMaxLayerSize;
}

template <typename Number>
hypro::vector_t<Number> NeuralNetwork<Number>::mins() const {
	return mMins;
}

template <typename Number>
hypro::vector_t<Number> NeuralNetwork<Number>::maxes() const {
	return mMaxes;
}

template <typename Number>
hypro::vector_t<Number> NeuralNetwork<Number>::means() const {
	return mMeans;
}

template <typename Number>
hypro::vector_t<Number> NeuralNetwork<Number>::ranges() const {
	return mRanges;
}

template <typename Number>
std::list<std::shared_ptr<LayerBase<Number>>> NeuralNetwork<Number>::layers() const {
	return mLayers;
}

template <typename Number>
std::shared_ptr<LayerBase<Number>> NeuralNetwork<Number>::layers( int index ) const {
	auto layerIter = mLayers.begin();
	std::advance( layerIter, index );
	return ( *layerIter );
}

template <typename Number>
void NeuralNetwork<Number>::setLayer( int index, std::shared_ptr<LayerBase<Number>> layer ) {
	if ( index >= mLayers.size() ) {
		throw std::out_of_range("Index out of range");
	}

	auto it = mLayers.begin();
	std::advance(it, index);
	*it = layer;
}

// ============= utility functions =============

// ================== methods ==================

template <typename Number>
hypro::vector_t<Number> NeuralNetwork<Number>::forwardPass( const hypro::vector_t<Number>& inputVec, bool normalizeInput, bool normalizeOutput ) const {
	assert( inputVec.rows() == mInputSize );

	// Copy the input vector into a temporary vector
	hypro::vector_t<Number> outputVec = inputVec;

	// Normalize inputs
	if ( normalizeInput ) {
		for ( int i = 0; i < mInputSize; i++ ) {
			// Min-Max normalization + mean-range strandardization
			if ( outputVec[i] > mMaxes[i] ) {
				outputVec[i] = ( mMaxes[i] - mMeans[i] ) / mRanges[i];
			} else if ( outputVec[i] < mMins[i] ) {
				outputVec[i] = ( outputVec[i] - mMeans[i] ) / mRanges[i];
			} else {
				outputVec[i] = ( outputVec[i] - mMeans[i] ) / mRanges[i];
			}
		}
	}

	for ( auto layer : mLayers ) {
		outputVec = layer->forwardPass(outputVec);
	}

	// Denormalize the output vector
	if ( normalizeOutput ) {
		for ( int i = 0; i < mOutputSize; i++ ) {
			// denormalize with the output mean and range values
			outputVec[i] = outputVec[i] * mRanges[mInputSize] + mMeans[mInputSize];
		}
	}

	assert( outputVec.rows() == mOutputSize );
	return outputVec;
}

template <typename Number>
std::vector<Starset<Number>> NeuralNetwork<Number>::forwardPass( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	// TODO: consider implementing the input and output normalization/standardization for the representation set here instead of normalizing before calling this function. This

	// This loop currently simulates BFS (Breadth-First-Search), however also DFS (Depth-First-Search) could be implemented
	// Use a queue instead of vector for BFS and use a stack for DFS during the implementation
	// introduce a queue/stack of jobs which all calculate the ReachabilityTree and return the ReachabilityTree instead
	// coupled with the vector of final sets (the leaves of the tree)

	// TODO: add some printed information with cout // TRACE + assertions
	std::vector<Starset<Number>> outputSets = std::vector<hypro::Starset<Number>>();
	outputSets.push_back( inputSet );
	for ( auto layer : mLayers ) {
		std::cout << "Computing output of layer: " << layer->layerIndex() << ", layer type: " << layer->layerType()._to_string() << std::endl;
		outputSets = layer->forwardPass( outputSets, method, plotIntermediates );
		std::cout << "Number of stars: " << outputSets.size() << std::endl;
	}
	return outputSets;
}

template <typename Number>
bool NeuralNetwork<Number>::verifyNetwork( const hypro::HPolytope<Number>& inputSet, const hypro::HPolytope<Number>& safeSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	// this method could verify if the output set violates the safe set
	// it could also plot all the output sets + the safe set
	// think about the plotter (for each node in the search tree one could create a plot)
	// but also a plot is possible for all the output sets and safe set
	// the affine mapping and the star before would be nice if is on the same plot
	// a plotter instance is needed for the nodes and for network

	// TODO: how to define in a good way the safety properties? (e.g. like a logical formula)

	std::vector<hypro::Starset<Number>> outputSets = forwardPass( inputSet, method, plotIntermediates );

	// check the safety properties here

	return false;
}

}  // namespace hypro
