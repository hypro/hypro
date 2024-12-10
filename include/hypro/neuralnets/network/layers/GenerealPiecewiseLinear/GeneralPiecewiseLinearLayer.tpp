#include "GeneralPiecewiseLinearLayer.h"

namespace hypro {

template <typename Number>
GeneralPiecewiseLinearLayer<Number>::GeneralPiecewiseLinearLayer()
	: LayerBase<Number>() {}

template <typename Number>
GeneralPiecewiseLinearLayer<Number>::GeneralPiecewiseLinearLayer( unsigned short int layerSize, unsigned short int layerIndex, size_t numPieces,
																  const std::vector<Number>& lowerBounds, const std::vector<Number>& upperBounds,
																  const std::vector<Number>& slopes, const std::vector<Number>& offsets )
	: LayerBase<Number>( layerSize, layerIndex )
	, mNumPieces( numPieces )
	, mLowerBounds( lowerBounds )
	, mUpperBounds( upperBounds )
	, mSlopes( slopes )
	, mOffsets( offsets ) {
	for ( int i = 0; i < mNumPieces - 1; ++i ) {
		assert( mLowerBounds[i] < mLowerBounds[i + 1] );
		assert( mUpperBounds[i] < mUpperBounds[i + 1] );
		assert( mLowerBounds[i + 1] == mUpperBounds[i] );
	}
}

template <typename Number>
const NN_LAYER_TYPE GeneralPiecewiseLinearLayer<Number>::layerType() const {
	return NN_LAYER_TYPE::GENERAL_PIECEWISE_LINEAR;
}

template <typename Number>
vector_t<Number> GeneralPiecewiseLinearLayer<Number>::forwardPass( const vector_t<Number>& inputVec, int i ) const {
	vector_t<Number> outputVec = inputVec;
	for ( int j = 0; j < mNumPieces; ++j ) {
		if ( mLowerBounds[j] <= inputVec[i] && inputVec[i] <= mUpperBounds[j] ) {
			outputVec[i] = mOffsets[j] + mSlopes[j] * inputVec[i];
		}
	}
	return outputVec;
}

template <typename Number>
vector_t<Number> GeneralPiecewiseLinearLayer<Number>::forwardPass( const vector_t<Number>& inputVec ) const {
	vector_t<Number> outputVec = inputVec;
	for ( int i = 0; i < outputVec.size(); ++i ) {
		for ( int j = 0; j < mNumPieces; ++j ) {
			if ( mLowerBounds[j] <= inputVec[i] && inputVec[i] <= mUpperBounds[j] ) {
				outputVec[i] = mOffsets[j] + mSlopes[j] * inputVec[i];
			}
		}
	}
	return outputVec;
}

template <typename Number>
std::vector<hypro::Starset<Number>> GeneralPiecewiseLinearLayer<Number>::reachGeneralPiecewiseLinear( const hypro::Starset<Number>& inputSet, NN_REACH_METHOD method, bool plotIntermediates ) const {
	hypro::Plotter<Number>& plotter = hypro::Plotter<Number>::getInstance();
    
    std::vector<hypro::Starset<Number>> I_n;
	I_n.push_back( inputSet );
    size_t d = inputSet.generator().rows();
	for ( size_t i = 0; i < d; i++ ) {
		// std::cout << "Neuron index:" << i << std::endl;
		// iterate over the dimensions of the input star
		switch ( method ) {
			case NN_REACH_METHOD::EXACT:
				I_n = GeneralPiecewiseLinear<Number>::stepGeneralPiecewiseLinear( i, I_n, mNumPieces, mLowerBounds, mUpperBounds, mSlopes, mOffsets );
				break;
			case NN_REACH_METHOD::OVERAPPRX:
                // TODO: method not implemented yet
				I_n = GeneralPiecewiseLinear<Number>::approxStepGeneralPiecewiseLinear( i, I_n, mNumPieces, mLowerBounds, mUpperBounds, mSlopes, mOffsets );
				break;
			default:
				FATAL( "hypro.neuralnets.reachability", "Invalid analysis method specified" );
		}

        if ( plotIntermediates ) {
#pragma omp critical
{
            plotter.clear();
            auto color = 1;
            for ( auto& star : I_n ) {
                // std::cout << star << std::endl;
                plotter.addObject(star.vertices(), hypro::plotting::colors[color] );
                color = ( color + 1 ) % 8;
            }
            plotter.plot2d();
}
        }

	}
	return I_n;
}

template <typename Number>
std::vector<hypro::Starset<Number>> GeneralPiecewiseLinearLayer<Number>::forwardPass( const hypro::Starset<Number>& inputSet, unsigned short int index, NN_REACH_METHOD method ) const {
	std::vector<hypro::Starset<Number>> I_n = std::vector<hypro::Starset<Number>>();
	I_n.push_back( inputSet );
	switch ( method ) {
		case NN_REACH_METHOD::EXACT:
			I_n = GeneralPiecewiseLinear<Number>::stepGeneralPiecewiseLinear( index, I_n, mNumPieces, mLowerBounds, mUpperBounds, mSlopes, mOffsets );
			break;
		case NN_REACH_METHOD::OVERAPPRX:
			I_n = GeneralPiecewiseLinear<Number>::approxStepGeneralPiecewiseLinear( index, I_n, mNumPieces, mLowerBounds, mUpperBounds, mSlopes, mOffsets );
			break;
		default:
			FATAL( "hypro.neuralnets.reachability", "Invalid analysis method specified" );
	}
	return I_n;
}

template <typename Number>
std::vector<Starset<Number>> GeneralPiecewiseLinearLayer<Number>::forwardPass( const std::vector<Starset<Number>>& inputSets, NN_REACH_METHOD method, bool plotIntermediates ) const {
	std::vector<Starset<Number>> result;
	size_t N = inputSets.size();  // number of input stars
// #pragma omp parallel for
	for ( size_t i = 0; i < N; ++i ) {
		std::vector<hypro::Starset<Number>> resultSets = reachGeneralPiecewiseLinear( inputSets[i], method, plotIntermediates );
#pragma omp critical
		{
			result.insert( result.end(), resultSets.begin(), resultSets.end() );
		}
	}
	return result;
}

template <typename Number>
Point<Number> GeneralPiecewiseLinearLayer<Number>::propagateCandidateBack( Point<Number> y, int neuronNumber, Starset<Number> inputSet ) const {
	// TODO: implement this
	return y;
}

}  // namespace hypro
