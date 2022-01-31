/**
 * Class that holds the implementation of a Neural Network.
 * @file NNet.tpp
 * 
 * @author László Antal <antal@informatik.rwth-aachen.de>

 * @version 2022-01-20
 * @date 2022-01-20
 */

#include "NNet.h"
// TODO: Do not forget to take a look at types atof, atoi, double, float
// use: e.g.: carl::convert<double, Number>(..double..);

namespace hypro {

template <typename Number>
NNet<Number>::NNet()
	: mNumLayers( 0 )
	, mInputSize( 0 )
	, mOutputSize( 0 )
	, mMaxLayerSize( 0 ) {}

// Deallocate memory used by a neural network
template <typename Number>
NNet<Number>::~NNet() {
	delete[] mLayerSizes;
	delete[] mWeights;
	delete[] mBiases;
}

template <typename Number>
unsigned int NNet<Number>::numLayers() const {
	return mNumLayers;
}

template <typename Number>
unsigned int NNet<Number>::inputSize() const {
	return mInputSize;
}

template <typename Number>
unsigned int NNet<Number>::outputSize() const {
	return mOutputSize;
}

template <typename Number>
unsigned int NNet<Number>::maxLayerSize() const {
	return mMaxLayerSize;
}

template <typename Number>
unsigned int* NNet<Number>::layerSizes() const {
	return mLayerSizes;
}

template <typename Number>
vector_t<Number> NNet<Number>::mins() const {
	return mMins;
}

template <typename Number>
vector_t<Number> NNet<Number>::maxes() const {
	return mMaxes;
}

template <typename Number>
vector_t<Number> NNet<Number>::means() const {
	return mMeans;
}

template <typename Number>
vector_t<Number> NNet<Number>::ranges() const {
	return mRanges;
}

template <typename Number>
matrix_t<Number>* NNet<Number>::weights() const {
	return mWeights;
}

template <typename Number>
vector_t<Number>* NNet<Number>::biases() const {
	return mBiases;
}

template <typename Number>
std::pair<matrix_t<Number>, vector_t<Number>> NNet<Number>::layerParams( int i ) const {
	assert( i >= 0 && i < mNumLayers );
	return std::make_pair( mWeights[i], mBiases[i] );
}

//Take in a .nnet filename with path and load the network from the file
//Inputs:  filename - const char* that specifies the name and path of file
//Outputs: NNet<Number> - the loaded neural network
template <typename Number>
NNet<Number>::NNet( const char* filename ) {
	//Load file and check if it exists
	FILE* fstream = fopen( filename, "r" );
	assert( fstream != NULL );

	if ( fstream == NULL ) {
		FATAL( "Could not open the input file: %s\n", filename );
	}

	//Initialize variables
	int bufferSize = 10240;
	char* buffer = new char[bufferSize];
	char *record, *line;
	int i = 0, layer = 0, row = 0, j = 0, param = 0;

	//Read int parameters of neural network
	line = fgets( buffer, bufferSize, fstream );
	while ( strstr( line, "//" ) != NULL )
		line = fgets( buffer, bufferSize, fstream );  //skip header lines
	record = strtok( line, ",\n" );
	mNumLayers = atoi( record );
	mInputSize = atoi( strtok( NULL, ",\n" ) );
	mOutputSize = atoi( strtok( NULL, ",\n" ) );
	mMaxLayerSize = atoi( strtok( NULL, ",\n" ) );

	//Allocate space for and read values of the array members of the network
	mLayerSizes = new unsigned int[mNumLayers + 1];
	line = fgets( buffer, bufferSize, fstream );
	record = strtok( line, ",\n" );
	for ( i = 0; i < mNumLayers + 1; i++ ) {
		mLayerSizes[i] = atoi( record );
		record = strtok( NULL, ",\n" );
	}

	//Skip the unsused paramter
	line = fgets( buffer, bufferSize, fstream );

	//Load Min and Max values of inputs
	mMins = vector_t<Number>( mInputSize );
	line = fgets( buffer, bufferSize, fstream );
	record = strtok( line, ",\n" );
	for ( i = 0; i < mInputSize; i++ ) {
		mMins[i] = carl::convert<double, Number>( atof( record ) );
		record = strtok( NULL, ",\n" );
	}
	mMaxes = vector_t<Number>( mInputSize );
	line = fgets( buffer, bufferSize, fstream );
	record = strtok( line, ",\n" );
	for ( i = 0; i < mInputSize; i++ ) {
		mMaxes[i] = carl::convert<double, Number>( atof( record ) );
		record = strtok( NULL, ",\n" );
	}

	//Load Mean and Range of inputs
	mMeans = vector_t<Number>( mInputSize );
	line = fgets( buffer, bufferSize, fstream );
	record = strtok( line, ",\n" );
	for ( i = 0; i < mInputSize; i++ ) {
		mMeans[i] = carl::convert<double, Number>( atof( record ) );
		record = strtok( NULL, ",\n" );
	}
	mRanges = vector_t<Number>( mInputSize );
	line = fgets( buffer, bufferSize, fstream );
	record = strtok( line, ",\n" );
	for ( i = 0; i < mInputSize; i++ ) {
		mRanges[i] = carl::convert<double, Number>( atof( record ) );
		record = strtok( NULL, ",\n" );
	}

	//Allocate weights and biases of Neural Network
	mWeights = new matrix_t<Number>[mNumLayers];
	mBiases = new vector_t<Number>[mNumLayers];
	for ( int i = 0; i < mNumLayers; i++ ) {
		mWeights[i] = matrix_t<Number>::Zero( mLayerSizes[i + 1], mLayerSizes[i] );
		mBiases[i] = vector_t<Number>::Zero( mLayerSizes[i + 1] );
		// std::cout << "Layer " << i << ": " << std::endl;
		// std::cout << "\t weights dim: (" << mWeights[i].rows() << ", " << mWeights[i].cols() << ")." << std::endl;
		// std::cout << "\t biases dim: (" << mBiases[i].rows() << ", " << mBiases[i].cols() << ")." << std::endl;
	}

	//Iteration parameters
	layer = 0, param = 0, i = 0, j = 0;

	//Read in parameters and put them in the matrix
	while ( ( line = fgets( buffer, bufferSize, fstream ) ) != NULL ) {
		if ( i >= mLayerSizes[layer + 1] ) {
			if ( param == 0 ) {
				param = 1;
			} else {
				param = 0;
				layer++;
			}
			i = 0;
			j = 0;
		}
		record = strtok( line, ",\n" );
		while ( record != NULL ) {
			// std::cout << "layer: " << layer << ", param: " << param << ", (" << i << ", " << j << ")" << std::endl;
			if ( param == 0 ) {
				// weights
				mWeights[layer]( i, j++ ) = carl::convert<double, Number>( atof( record ) );
			} else {
				// biases
				mBiases[layer]( i, j++ ) = carl::convert<double, Number>( atof( record ) );
			}
			record = strtok( NULL, ",\n" );
		}
		j = 0;
		i++;
	}

	delete[] buffer;
}

//Complete one forward pass for a given set of inputs and return output values
template <typename Number>
vector_t<Number> NNet<Number>::evaluateNetwork( const vector_t<Number>& inputs, bool normalizeInput, bool normalizeOutput ) const {
	assert( mInputSize == inputs.rows() );

	vector_t<Number> outputs = inputs;
	int i, j, layer;

	//Normalize inputs
	if ( normalizeInput ) {
		std::cout << "Normalizing the input vector..." << std::endl;
		for ( i = 0; i < mInputSize; i++ ) {
			if ( outputs[i] > mMaxes[i] ) {
				outputs[i] = ( mMaxes[i] - mMeans[i] ) / mRanges[i];
			} else if ( outputs[i] < mMins[i] ) {
				outputs[i] = ( mMins[i] - mMeans[i] ) / mRanges[i];
			} else {
				outputs[i] = ( outputs[i] - mMeans[i] ) / mRanges[i];
			}
		}
	}

	for ( layer = 0; layer < mNumLayers; layer++ ) {
		assert( outputs.rows() == mWeights[layer].cols() );
		assert( mBiases[layer].rows() == mWeights[layer].rows() );

		outputs = mWeights[layer] * outputs + mBiases[layer];
		if ( layer < ( mNumLayers - 1 ) ) {
			//Perform ReLU
			// outputs = outputs.unaryExpr( []( Number x ) { return max( x, 0 ); } );
			for ( i = 0; i < mLayerSizes[i + 1]; i++ ) {
				if ( outputs[i] < 0.0f )
					outputs[i] = carl::convert<double, Number>( 0.0f );
			}
		}
	}

	//Write the final output value to the allocated spot in memory
	if ( normalizeOutput ) {
		std::cout << "Normalizing the output vector..." << std::endl;
		for ( i = 0; i < mOutputSize; i++ ) {
			outputs[i] = outputs[i] * mRanges[i] + mMeans[i];
		}
	}

	assert( mOutputSize == outputs.rows() );

	//Return the output vector
	return outputs;
}

}  // namespace hypro
