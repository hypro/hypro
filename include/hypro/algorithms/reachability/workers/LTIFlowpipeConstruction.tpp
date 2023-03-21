/*
 * Copyright (c) 2022-2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "LTIFlowpipeConstruction.h"

namespace hypro {

template <class Number>
matrix_t<Number> computeTimeTransformation( linearFlow<Number> const& flow, tNumber timeStep ) {
	matrix_t<Number> deltaMatrix = flow.getFlowMatrix() * carl::convert<tNumber, Number>( timeStep );

	// clang-format off
	TRACE( "hypro.worker", "timestep: " << std::endl << timeStep );
	TRACE( "hypro.worker", "flow: " << std::endl << flow.getFlowMatrix() );
    TRACE( "hypro.worker", "delta matrix: " << std::endl << deltaMatrix );
	// clang-format on

	matrix_t<double> doubleMatrix = convert<Number, double>( deltaMatrix );
	matrix_t<double> expMatrix = doubleMatrix.exp();
	matrix_t<Number> resultMatrix = convert<double, Number>( expMatrix );

	// clang-format off
	TRACE( "hypro.worker", "double matrix: " << std::endl << doubleMatrix );
	TRACE( "hypro.worker", "expMatrix: " << std::endl << expMatrix );
    TRACE( "hypro.worker", "result matrix: " << std::endl << resultMatrix );
	// clang-format on

	return resultMatrix;
}

template <class Representation, class Number>
Representation constructFirstSegment( Representation const& initialSet,
									  linearFlow<Number> const& flow,
									  matrix_t<Number> const& rawTransformation,
									  tNumber timeStep ) {
	// Zero'd dummy external input
	Box<Number> externalInput{ std::make_pair(
		  Point<Number>{ vector_t<Number>::Zero( flow.dimension() ) },
		  Point<Number>{ vector_t<Number>::Zero( flow.dimension() ) } ) };

	ErrorBoxes errorBoxes = constructErrorBoxes(
		  carl::convert<tNumber, Number>( timeStep ),
		  flow.getFlowMatrix(),
		  initialSet,
		  rawTransformation,
		  externalInput );

	Representation atDelta = initialSet.affineTransformation( timeTrafoMatrixBlock( rawTransformation ), timeTrafoVectorBlock( rawTransformation ) );

	Representation firstSegment = atDelta.unite( initialSet );

	// Means bloatingSet = convert(1/4 * errorBoxes.DifferenceBox)
	auto scaledErrorBox = Number( Number( 1 ) / Number( 4 ) ) * errorBoxes.DifferenceBox;
	Representation bloatingSet = Representation( scaledErrorBox.matrix(), scaledErrorBox.vector() );

	TRACE( "hypro", "atDelta: " << atDelta.vertices() );
	TRACE( "hypro", "init: " << initialSet.vertices() );
	TRACE( "hypro", "bloatingSet: " << bloatingSet.vertices() );

	firstSegment = firstSegment.minkowskiSum( bloatingSet );
	firstSegment.removeRedundancy();

	return firstSegment;
}

template <class Number, class Representation, class... Rargs>
Representation constructFirstSegment( State<Number, Representation, Rargs...> const& initialSet,
									  linearFlow<Number> const& flow,
									  matrix_t<Number> const& rawTransformation,
									  tNumber timeStep ) {
	// Zero'd dummy external input
	Box<Number> externalInput{ std::make_pair(
		  Point<Number>{ vector_t<Number>::Zero( flow.dimension() ) },
		  Point<Number>{ vector_t<Number>::Zero( flow.dimension() ) } ) };

	ErrorBoxes errorBoxes = constructErrorBoxes(
		  carl::convert<tNumber, Number>( timeStep ),
		  flow.getFlowMatrix(),
		  initialSet,
		  rawTransformation,
		  externalInput );

	auto atDelta = initialSet.affineTransformation( timeTrafoMatrixBlock( rawTransformation ), timeTrafoVectorBlock( rawTransformation ) );

	auto firstSegment = atDelta.unite( initialSet );

	// Means bloatingSet = convert(1/4 * errorBoxes.DifferenceBox)
	auto scaledErrorBox = Number( Number( 1 ) / Number( 4 ) ) * errorBoxes.DifferenceBox;
	auto bloatingSet = Representation( scaledErrorBox.matrix(), scaledErrorBox.vector() );

	TRACE( "hypro", "atDelta: " << atDelta.vertices() );
	TRACE( "hypro", "init: " << initialSet.vertices() );
	TRACE( "hypro", "bloatingSet: " << bloatingSet.vertices() );

	firstSegment = firstSegment.minkowskiSum( bloatingSet );
	firstSegment.removeRedundancy();

	return firstSegment;
}

template <class Representation, class Number>
ErrorBoxes<Number> constructErrorBoxes( Number const& delta, matrix_t<Number> const& flowMatrix, Representation const& initialSet, matrix_t<Number> const& trafoMatrix, Box<Number> const& externalInput ) {
	if ( initialSet.empty() ) return {};

	assert( initialSet.dimension() == externalInput.dimension() );

	size_t dimension = flowMatrix.cols();
	matrix_t<Number> matrixBlock = matrix_t<Number>::Zero( 3 * dimension, 3 * dimension );

	matrixBlock.block( 0, 0, dimension, dimension ) = flowMatrix.cwiseAbs();												   // Upper left block
	matrixBlock.block( 0, dimension, dimension, dimension ) = matrix_t<Number>::Identity( dimension, dimension );			   // Upper middle block
	matrixBlock.block( dimension, 2 * dimension, dimension, dimension ) = matrix_t<Number>::Identity( dimension, dimension );  // Middle right block

	matrixBlock *= delta;

	matrix_t<double> matrixBlockDouble = convert<Number, double>( matrixBlock );
	matrixBlockDouble = matrixBlockDouble.exp();
	matrixBlock = convert<double, Number>( matrixBlockDouble );

	matrix_t<Number> AMatrix = flowMatrix * ( matrix_t<Number>::Identity( dimension, dimension ) - trafoMatrix );

	// Transform initial set by AMatrix
	Representation transformedInitialSetA = initialSet.affineTransformation( AMatrix.block( 0, 0, dimension - 1, dimension - 1 ), AMatrix.block( 0, dimension - 1, dimension - 1, 1 ) );

	Box<Number> boundingBoxA = Converter<Number>::template toBox<BoxLinearOptimizationOn>( transformedInitialSetA );

	if ( boundingBoxA.empty() ) return {};

	// Augment box by a dimension for constants
	boundingBoxA.insert( carl::Interval<Number>{ 1, 1 } );

	boundingBoxA = boundingBoxA.makeSymmetric();
	assert( boundingBoxA.isSymmetric() );

	// Transform by upper middle block
	boundingBoxA = boundingBoxA.linearTransformation( matrixBlock.block( 0, dimension, dimension, dimension ) );

	matrix_t<Number> BMatrix = flowMatrix * flowMatrix * trafoMatrix;

	Representation transformedInitialSetB = initialSet.affineTransformation( AMatrix.block( 0, 0, dimension - 1, dimension - 1 ), AMatrix.block( 0, dimension - 1, dimension - 1, 1 ) );

	Box<Number> boundingBoxB = Converter<Number>::template toBox<BoxLinearOptimizationOn>( transformedInitialSetB );

	// Augment box by a dimension for constants
	boundingBoxB.insert( carl::Interval<Number>{ 1, 1 } );

	boundingBoxB = boundingBoxB.makeSymmetric();
	assert( boundingBoxB.isSymmetric() );

	// Transform by upper right block
	boundingBoxB = boundingBoxB.linearTransformation( matrixBlock.block( 0, 2 * dimension, dimension, dimension ) );

	Box<Number> errorBoxX0 = boundingBoxA.minkowskiSum( boundingBoxB );

	// Remove augmentation via projection
	std::vector<size_t> dims( errorBoxX0.dimension() - 1 );
	std::iota( dims.begin(), dims.end(), 0 );  // fill with 0,1,...
	errorBoxX0 = errorBoxX0.projectOn( dims );

	Box<Number> errorBoxExternalInput = externalInput.linearTransformation( flowMatrix.block( 0, 0, dimension - 1, dimension - 1 ) );

	errorBoxExternalInput.makeSymmetric();
	// Transform by upper right block (without last row and col)
	errorBoxExternalInput = errorBoxExternalInput.linearTransformation( matrixBlock.block( 0, 2 * dimension, dimension - 1, dimension - 1 ) );

	Box<Number> differenceBox = errorBoxX0.minkowskiDecomposition( errorBoxExternalInput );

	// empty external input implies that the errorBox should be the same as the differenceBox
	assert( !externalInput.empty() || errorBoxX0 == differenceBox );

	return { errorBoxX0, errorBoxExternalInput, differenceBox };
}

template <class Representation>
std::vector<TimedValuationSet<Representation>> aggregate( size_t segmentsPerBlock, std::vector<IndexedValuationSet<Representation>>& enabled ) {
	std::vector<TimedValuationSet<Representation>> aggregated{};

	TRACE( "hypro.reachability", "Aggregation to " << segmentsPerBlock << " segments per block for a block of size " << enabled.size() );

	if ( enabled.empty() ) return aggregated;

	size_t blockCount = 0;
	for ( auto& [set, ind] : enabled ) {
		if ( blockCount == 0 ) {
			// beginning of block
			aggregated.emplace_back( TimedValuationSet<Representation>{ set, carl::Interval{ ind, ind } } );
		} else {
			// in a block
			aggregated.back().valuationSet = aggregated.back().valuationSet.unite( set );
		}
		blockCount += 1;

		// block is now full, finish previous and start next one
		if ( blockCount == segmentsPerBlock ) {
			setUpperBound( aggregated.back().time, ind );
			blockCount = 0;
		}
	}
	// closure of last block which might be incomplete
	setUpperBound( aggregated.back().time, enabled.back().index );

	return aggregated;
}

}  // namespace hypro
