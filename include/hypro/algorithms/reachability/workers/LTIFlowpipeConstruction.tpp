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

    template<class Number>
    matrix_t<Number> computeTimeTransformation(linearFlow<Number> const &flow, tNumber timeStep) {
        matrix_t<Number> deltaMatrix = flow.getFlowMatrix() * carl::convert<tNumber, Number>(timeStep);

        // clang-format off
        TRACE("hypro.worker", "timestep: " << std::endl << timeStep);
        TRACE("hypro.worker", "flow: " << std::endl << flow.getFlowMatrix());
        TRACE("hypro.worker", "delta matrix: " << std::endl << deltaMatrix);
        // clang-format on

        matrix_t<double> doubleMatrix = convert<Number, double>(deltaMatrix);
        matrix_t<double> expMatrix = doubleMatrix.exp();
        matrix_t<Number> resultMatrix = convert<double, Number>(expMatrix);

        // clang-format off
        TRACE("hypro.worker", "double matrix: " << std::endl << doubleMatrix);
        TRACE("hypro.worker", "expMatrix: " << std::endl << expMatrix);
        TRACE("hypro.worker", "result matrix: " << std::endl << resultMatrix);
        // clang-format on

        return resultMatrix;
    }

    template<class Representation, class Number>
    Representation constructFirstSegment(Representation const &initialSet,
                                         linearFlow<Number> const &flow,
                                         matrix_t<Number> const &rawTransformation,
                                         tNumber timeStep) {
        

        Representation atDelta = initialSet.affineTransformation(timeTrafoMatrixBlock(rawTransformation),
                                                                 timeTrafoVectorBlock(rawTransformation));
        Representation firstSegment = atDelta.unite(initialSet);

        DEBUG("hypro", "atDelta: " << atDelta.vertices());
        DEBUG("hypro", "init: " << initialSet.vertices());

        DEBUG("hypro", "atDelta: " << atDelta << std::endl);
        DEBUG("hypro", "init: " << initialSet << std::endl);

        DEBUG("hypro", "firstSegment: " << firstSegment << std::endl);
        DEBUG("hypro", "firstSegment: " << firstSegment.vertices() << std::endl);


        bool isFlowIdentity = rawTransformation.block(0, 0, rawTransformation.rows() - 1, rawTransformation.cols() - 1).isApprox(matrix_t<Number>::Identity(rawTransformation.rows()-1, rawTransformation.cols()-1));
        if (!isFlowIdentity) {
                // Zero'd dummy external input
                Box<Number> externalInput{std::make_pair(
                        Point<Number>{vector_t<Number>::Zero(flow.dimension())},
                        Point<Number>{vector_t<Number>::Zero(flow.dimension())})};

                ErrorBoxes errorBoxes = constructErrorBoxes(
                        carl::convert<tNumber, Number>(timeStep),
                        flow.getFlowMatrix(),
                        initialSet,
                        rawTransformation,
                        externalInput);
                // Means bloatingSet = convert(1/4 * errorBoxes.DifferenceBox)
                auto scaledErrorBox = Number(Number(1) / Number(4)) * errorBoxes.DifferenceBox;
                Representation bloatingSet = Representation(scaledErrorBox.matrix(), scaledErrorBox.vector());
                //define projectdim as the dimensions with linear flow
                
                std::vector<std::size_t> projectionDims;
                matrix_t<Number> flowmatrix = flow.getFlowMatrix();
                matrix_t<Number> projMatrix = matrix_t<Number>::Identity(flow.dimension(), flow.dimension());
                for (std::size_t i = 0; i < flow.dimension(); ++i) {
                        if (!flowmatrix.block(i, 0, 1, flowmatrix.cols()-1).isZero()){ // get dimensions where the flow is not constant
                                projectionDims.push_back(i);
                                projMatrix(i, i) = 0;
                        }
                }
                auto bloatingSetpro = bloatingSet.linearTransformation(projMatrix);
                // auto bloatingSetpro = bloatingSet.projectOn(projectionDims);
                DEBUG("hypro", "bloatingSet: " << bloatingSetpro.vertices());
                DEBUG("hypro", "bloatingSet: " << bloatingSetpro << std::endl);

                firstSegment = firstSegment.minkowskiSum(bloatingSetpro);
        }
        DEBUG("hypro.reachability", "first segment = " << firstSegment << std::endl);
        DEBUG("hypro.reachability", "first segment = " << firstSegment.empty() << std::endl);
        
        firstSegment.removeRedundancy();
        return firstSegment;
    }

    template<class Number, class Representation, class... Rargs>
    Representation constructFirstSegment(State<Number, Representation, Rargs...> const &initialSet,
                                         linearFlow<Number> const &flow,
                                         matrix_t<Number> const &rawTransformation,
                                         tNumber timeStep) {
        

        auto atDelta = initialSet.affineTransformation(timeTrafoMatrixBlock(rawTransformation),
                                                       timeTrafoVectorBlock(rawTransformation));
        auto firstSegment = atDelta.unite(initialSet);

        bool isFlowIdentity = rawTransformation.block(0, 0, rawTransformation.rows() - 1, rawTransformation.cols() - 1).isApprox(matrix_t<Number>::Identity(rawTransformation.rows()-1, rawTransformation.cols()-1));
        if (!isFlowIdentity) {
                // Zero'd dummy external input
                Box<Number> externalInput{std::make_pair(
                        Point<Number>{vector_t<Number>::Zero(flow.dimension())},
                        Point<Number>{vector_t<Number>::Zero(flow.dimension())})};

                ErrorBoxes errorBoxes = constructErrorBoxes(
                        carl::convert<tNumber, Number>(timeStep),
                        flow.getFlowMatrix(),
                        initialSet,
                        rawTransformation,
                        externalInput);
                // Means bloatingSet = convert(1/4 * errorBoxes.DifferenceBox)
                auto scaledErrorBox = Number(Number(1) / Number(4)) * errorBoxes.DifferenceBox;
                auto bloatingSet = Representation(scaledErrorBox.matrix(), scaledErrorBox.vector());
                
                matrix_t<Number> flowmatrix = flow.getFlowMatrix();
                matrix_t<Number> projMatrix = matrix_t<Number>::Identity(flow.dimension(), flow.dimension());
                for (std::size_t i = 0; i < flow.dimension(); ++i) {
                        if (!flowmatrix.block(i, 0, 1, flowmatrix.cols()-1).isZero()){ // get dimensions where the flow is not constant
                                projMatrix(i, i) = 0;
                        }
                }
                auto bloatingSetpro = bloatingSet.linearTransformation(projMatrix);
                DEBUG("hypro", "bloatingSet: " << bloatingSetpro.vertices());

                firstSegment = firstSegment.minkowskiSum(bloatingSetpro);
        }

        // firstSegment.removeRedundancy();

        return firstSegment;
    }

    // it creates the under- and over-approximation of the first segment
    // it inly work with HPolytope since the Minkowski difference is only implemented for that state set representation
    template<class Representation, class Number>
    Representation constructFirstSegmentUnder(Representation const &initialSet,
                                         linearFlow<Number> const &flow,
                                         matrix_t<Number> const &rawTransformation,
                                         tNumber timeStep) {

        TRACE("hypro", " inside constructFirstSegmentUnder");
        DEBUG("hypro", "init: " << initialSet.vertices());
        DEBUG("hypro", "init: " << initialSet << std::endl);

        Representation atDelta = initialSet.affineTransformation(timeTrafoMatrixBlock(rawTransformation),
                                                                 timeTrafoVectorBlock(rawTransformation));
        DEBUG("hypro", "atDelta: " << atDelta.vertices());
        DEBUG("hypro", "atDelta: " << atDelta << std::endl);
                                                                 
        Representation firstSegment = atDelta.unite(initialSet);

        DEBUG("hypro", "firstSegment: " << firstSegment << std::endl);

        bool isFlowIdentity = rawTransformation.block(0, 0, rawTransformation.rows() - 1, rawTransformation.cols() - 1).isApprox(matrix_t<Number>::Identity(rawTransformation.rows()-1, rawTransformation.cols()-1));
        // had to add it this way, because the representation check has to be a const expression (so it can be evaluated in compile time)
        if constexpr (std::is_same_v<Representation, HPolytope<Number>> || std::is_same_v<Representation, Starset<Number>>) {
                if (!isFlowIdentity) { //cannot combine the two if-s because this one is not a constant expression
                        // Zero'd dummy external input
                        Box<Number> externalInput{std::make_pair(
                                Point<Number>{vector_t<Number>::Zero(flow.dimension())},
                                Point<Number>{vector_t<Number>::Zero(flow.dimension())})};

                        ErrorBoxes errorBoxes = constructErrorBoxes(
                                carl::convert<tNumber, Number>(timeStep),
                                flow.getFlowMatrix(),
                                initialSet,
                                rawTransformation,
                                externalInput);
                        auto scaledErrorBox = Number(Number(1) / Number(4)) * errorBoxes.DifferenceBox;
                        Representation bloatingSet = Representation(scaledErrorBox.matrix(), scaledErrorBox.vector());
                        
                        matrix_t<Number> flowmatrix = flow.getFlowMatrix();
                        matrix_t<Number> projMatrix = matrix_t<Number>::Identity(flow.dimension(), flow.dimension());
                        for (std::size_t i = 0; i < flow.dimension(); ++i) {
                                if (!flowmatrix.block(i, 0, 1, flowmatrix.cols()-1).isZero()){ // get dimensions where the flow is not constant
                                        projMatrix(i, i) = 0;
                                }
                        }

                        auto bloatingSetpro = bloatingSet.linearTransformation(projMatrix);
                        DEBUG("hypro", "bloatingSet: " << bloatingSetpro.vertices());

                        DEBUG("hypro", "under firstSegment: " << firstSegment.vertices() << std::endl);
                        firstSegment = firstSegment.minkowskiDiff(bloatingSetpro);
                        DEBUG("hypro", "under firstSegment: " << firstSegment << std::endl);
                        DEBUG("hypro", "under firstSegment: " << firstSegment.vertices() << std::endl);

                        if (firstSegment.empty()) {
                                TRACE("hypro", "first segment became empty as a result of Minkowski diff" );
                        }
                }
        }

        // firstSegment.removeRedundancy();
        return firstSegment;
    }

    template<class Representation, class Number>
    ErrorBoxes<Number>
    constructErrorBoxes(Number const &delta, matrix_t<Number> const &flowMatrix, Representation const &initialSet,
                        matrix_t<Number> const &trafoMatrix, Box<Number> const &externalInput) {
        if (initialSet.empty()) return {};

        assert(initialSet.dimension() == externalInput.dimension());

        size_t dimension = flowMatrix.cols();
        matrix_t<Number> matrixBlock = matrix_t<Number>::Zero(3 * dimension, 3 * dimension);

        matrixBlock.block(0, 0, dimension,
                          dimension) = flowMatrix.cwiseAbs();                                                   // Upper left block
        matrixBlock.block(0, dimension, dimension, dimension) = matrix_t<Number>::Identity(dimension,
                                                                                           dimension);               // Upper middle block
        matrixBlock.block(dimension, 2 * dimension, dimension, dimension) = matrix_t<Number>::Identity(dimension,
                                                                                                       dimension);  // Middle right block

        matrixBlock *= delta;

        matrix_t<double> matrixBlockDouble = convert<Number, double>(matrixBlock);
        matrixBlockDouble = matrixBlockDouble.exp();
        matrixBlock = convert<double, Number>(matrixBlockDouble);

        matrix_t<Number> AMatrix = flowMatrix * (matrix_t<Number>::Identity(dimension, dimension) - trafoMatrix);

        // Transform initial set by AMatrix
        Representation transformedInitialSetA = initialSet.affineTransformation(
                AMatrix.block(0, 0, dimension - 1, dimension - 1), AMatrix.block(0, dimension - 1, dimension - 1, 1));

        Box<Number> boundingBoxA = Converter<Number>::template toBox<BoxLinearOptimizationOn>(transformedInitialSetA);

        if (boundingBoxA.empty()) return {};

        // Augment box by a dimension for constants
        boundingBoxA.insert(carl::Interval<Number>{1, 1});

        boundingBoxA = boundingBoxA.makeSymmetric();
        assert(boundingBoxA.isSymmetric());

        // Transform by upper middle block
        boundingBoxA = boundingBoxA.linearTransformation(matrixBlock.block(0, dimension, dimension, dimension));

        matrix_t<Number> BMatrix = flowMatrix * flowMatrix * trafoMatrix;

        Representation transformedInitialSetB = initialSet.affineTransformation(
                AMatrix.block(0, 0, dimension - 1, dimension - 1), AMatrix.block(0, dimension - 1, dimension - 1, 1));

        Box<Number> boundingBoxB = Converter<Number>::template toBox<BoxLinearOptimizationOn>(transformedInitialSetB);

        // Augment box by a dimension for constants
        boundingBoxB.insert(carl::Interval<Number>{1, 1});

        boundingBoxB = boundingBoxB.makeSymmetric();
        assert(boundingBoxB.isSymmetric());

        // Transform by upper right block
        boundingBoxB = boundingBoxB.linearTransformation(matrixBlock.block(0, 2 * dimension, dimension, dimension));

        Box<Number> errorBoxX0 = boundingBoxA.minkowskiSum(boundingBoxB);

        // Remove augmentation via projection
        std::vector<size_t> dims(errorBoxX0.dimension() - 1);
        std::iota(dims.begin(), dims.end(), 0);  // fill with 0,1,...
        errorBoxX0 = errorBoxX0.projectOn(dims);

        Box<Number> errorBoxExternalInput = externalInput.linearTransformation(
                flowMatrix.block(0, 0, dimension - 1, dimension - 1));

        errorBoxExternalInput.makeSymmetric();
        // Transform by upper right block (without last row and col)
        errorBoxExternalInput = errorBoxExternalInput.linearTransformation(
                matrixBlock.block(0, 2 * dimension, dimension - 1, dimension - 1));

        Box<Number> differenceBox = errorBoxX0.minkowskiDecomposition(errorBoxExternalInput);

        // empty external input implies that the errorBox should be the same as the differenceBox
        assert(!externalInput.empty() || errorBoxX0 == differenceBox);

        return {errorBoxX0, errorBoxExternalInput, differenceBox};
    }

    template<class Representation>
    std::vector<TimedValuationSet<Representation>>
    aggregate(size_t segmentsPerBlock, std::vector<IndexedValuationSet<Representation>> &enabled) {
        std::vector<TimedValuationSet<Representation>> aggregated{};

        TRACE("hypro.reachability",
              "Aggregation to " << segmentsPerBlock << " segments per block for a block of size " << enabled.size());

        if (enabled.empty()) return aggregated;

        size_t blockCount = 0;
        for (auto &[set, ind]: enabled) {
            if (blockCount == 0) {
                // beginning of block
                aggregated.emplace_back(TimedValuationSet<Representation>{set, carl::Interval{ind, ind}});
            } else {
                // in a block
                aggregated.back().valuationSet = aggregated.back().valuationSet.unite(set);
            }
            blockCount += 1;

            // block is now full, finish previous and start next one
            if (blockCount == segmentsPerBlock) {
                setUpperBound(aggregated.back().time, ind);
                blockCount = 0;
            }
        }
        // closure of last block which might be incomplete
        setUpperBound(aggregated.back().time, enabled.back().index);

        return aggregated;
    }

}  // namespace hypro
