/*
 * Copyright (c) 2023.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "../../datastructures/HybridAutomaton/State.h"
#include "../../datastructures/HybridAutomaton/flow/flow.h"
#include "../../representations/GeometricObjectBase.h"
#include "TrafoParameters.h"

namespace hypro {

    template<typename Number, typename Representation, carl::DisableIf<std::is_same<Representation, SupportFunction<Number>>> = carl::dummy>
    void applyReduction(Representation &) {
    }

    template<typename Number, typename Representation, carl::EnableIf<std::is_same<Representation, SupportFunction<Number>>> = carl::dummy>
    void applyReduction(Representation &_in) {
        _in.evaluateTemplate(4, false);  // temporary, forces reduction to box.
        _in.forceLinTransReduction();
    }

/*
template<typename Number, typename Representation, carl::DisableIf< std::is_same<Representation, SupportFunction<Number>> > = carl::dummy>
void aggregationReduction( Representation&, Transition<Number>* , Number , Number  ) {
}

template<typename Number, typename Representation, carl::EnableIf< std::is_same<Representation, SupportFunction<Number>> > = carl::dummy>
void aggregationReduction( Representation& _in, Transition<Number>* transition, Number timeBound, Number timeStep) {
	Number temp = timeBound/timeStep;
	unsigned long multPerEval = _in.multiplicationsPerEvaluation();
	unsigned long estimatedNumberOfEvaluations =  (transition->guard().mat.rows() + transition->target()->invariant().mat.rows()) * carl::toInt<carl::uint>(carl::ceil(temp));
	unsigned long estimatedCostWithoutReduction = estimatedNumberOfEvaluations * multPerEval;
	unsigned long hyperplanesForReduction = 2* _in.dimension() * (_in.dimension()-1)+ 2* _in.dimension();
	unsigned long estimatedCostWithReduction = hyperplanesForReduction* multPerEval+ estimatedNumberOfEvaluations * carl::pow(hyperplanesForReduction, 2);
	if (estimatedCostWithReduction < estimatedCostWithoutReduction) {
		auto tmpHPoly = Converter<Number>::toHPolytope(_in);
		SupportFunction<Number> newSet(tmpHPoly.matrix(), tmpHPoly.vector());
		_in = newSet;
	}
}
*/

    template<typename Representation>
    void printFlowpipe(const std::vector<Representation> &_flowpipe) {
        for (const auto &segment: _flowpipe) {
            std::cout << segment << ", " << std::endl;
        }
    }

    template<typename Representation>
    void printFlowpipeReduced(const std::vector<Representation> &_flowpipe) {
        std::cout << *_flowpipe.begin() << ", " << std::endl;
        std::cout << "(...)" << std::endl;
        std::cout << *_flowpipe.back() << std::endl;
    }

    template<typename Number>
    Number hausdorffError(const Number &delta, const matrix_t<Number> &matrix, const Number &_supremum) {
        Number result;
        // calculate matrix infinity norm
        Number norm = inftyNorm(matrix);

        // Number tmp = delta * t;
        Number tmp = delta * norm;

        double tmpExp = std::exp(toDouble(tmp));
        result = carl::rationalize<Number>(tmpExp);

        // tmp.exp( result );
        result = result - 1 - tmp;
        result *= _supremum;
        return result;
    }

    template<typename Number, typename State>
    std::vector<Box<Number>> errorBoxes(const Number &delta, const linearFlow<Number> &flow, const State &initialSet,
                                        const matrix_t<Number> &trafoMatrix, const Box<Number> &externalInput) {
        if (initialSet.isEmpty()) {
            return std::vector<Box<Number>>{};
        }
        assert(initialSet.getDimension() == externalInput.dimension());

        std::vector<Box<Number>> res;
        unsigned dim = flow.dimension() + 1;
        // std::cout << "Dim: " << dim << std::endl;
        // std::cout << "Delta: " << delta << std::endl;
        matrix_t<Number> matrixBlock = matrix_t<Number>::Zero(3 * dim, 3 * dim);
        matrixBlock.block(0, 0, dim, dim) = abs(flow.getFlowMatrix());
        matrixBlock.block(0, dim, dim, dim) = matrix_t<Number>::Identity(dim, dim);
        matrixBlock.block(dim, 2 * dim, dim, dim) = matrix_t<Number>::Identity(dim, dim);
        // std::cout << "MatrixBlock: " << matrixBlock << std::endl;
        matrixBlock = delta * matrixBlock;
        // std::cout << "delta*MatrixBlock: " << matrixBlock << std::endl;
        matrix_t<double> convertedBlock = convert<Number, double>(matrixBlock);
        // std::cout << "MatrixBlock: " << std::endl << convertedBlock << std::endl;
        convertedBlock = convertedBlock.exp();
        // std::cout << "exp(MatrixBlock): " << std::endl << convertedBlock << std::endl;
        matrixBlock = convert<double, Number>(convertedBlock);

        // TODO: Introduce better variable naming!
        matrix_t<Number> tmpMatrix = flow.getFlowMatrix() * (matrix_t<Number>::Identity(dim, dim) - trafoMatrix);
        // std::cout << "Flow: " << flow << std::endl << "trafoMatrix: " << trafoMatrix << std::endl;
        // std::cout << __func__ << " TmpMtrix: " << std::endl << tmpMatrix << std::endl;
        // assert(tmpMatrix.row(dim-1).nonZeros() == 0);
        State transformedInitialSet =
                initialSet.affineTransformation(matrix_t<Number>(tmpMatrix.block(0, 0, dim - 1, dim - 1)),
                                                vector_t<Number>(tmpMatrix.block(0, dim - 1, dim - 1, 1)));

        auto b1 = std::visit([](auto representation) {
                                 return Converter<Number>::template toBox<BoxLinearOptimizationOn>(representation);
                             },
                             transformedInitialSet.getSet(0));

        if (b1.empty()) {
            return std::vector<Box<Number>>{};
        }

        // augment b1 by a dimension for the constant parts.
        // std::cout << "B1: " << b1 << std::endl;
        vector_t<Number> augmentedUpperLimit = vector_t<Number>::Ones(b1.max().dimension() + 1);
        augmentedUpperLimit.block(0, 0, dim - 1, 1) = b1.max().rawCoordinates();
        vector_t<Number> augmentedLowerLimit = vector_t<Number>::Ones(b1.min().dimension() + 1);
        augmentedLowerLimit.block(0, 0, dim - 1, 1) = b1.min().rawCoordinates();
        b1 = Box<Number>(std::make_pair(Point<Number>(augmentedLowerLimit), Point<Number>(augmentedUpperLimit)));

        b1 = b1.makeSymmetric();
        assert(b1.isSymmetric());
        b1 = b1.linearTransformation(matrixBlock.block(0, dim, dim, dim));

        matrix_t<Number> fullTransformationMatrix = (flow.getFlowMatrix() * flow.getFlowMatrix() * trafoMatrix);
        // assert(fullTransformationMatrix.row(dim-1).nonZeros() == 0);
        matrix_t<Number> tmpTrafo = fullTransformationMatrix.block(0, 0, dim - 1, dim - 1);
        vector_t<Number> tmpTrans = fullTransformationMatrix.block(0, dim - 1, dim - 1, 1);
        // the last row of this matrix should be zero in any case, such that we can decompose the linear transformation.
        // std::cout << "TmpTrafo Matrix: " << std::endl << tmpTrafo << std::endl;
        State tmp = initialSet.affineTransformation(tmpTrafo, tmpTrans);
        // Box<Number> b2 = Box<Number>(tmp.matrix(), tmp.vector());
        auto b2 = std::visit([](auto representation) {
                                 return Converter<Number>::template toBox<BoxLinearOptimizationOn>(representation);
                             },
                             tmp.getSet(0));
        augmentedUpperLimit.block(0, 0, dim - 1, 1) = b2.max().rawCoordinates();
        augmentedLowerLimit.block(0, 0, dim - 1, 1) = b2.min().rawCoordinates();
        b2 = Box<Number>(std::make_pair(Point<Number>(augmentedLowerLimit), Point<Number>(augmentedUpperLimit)));

        b2 = b2.makeSymmetric();
        assert(b2.isSymmetric());
        b2 = b2.linearTransformation(matrixBlock.block(0, 2 * dim, dim, dim));

        Box<Number> errorBoxX0 = b1.minkowskiSum(b2);

        // std::cout << "External Input: " << externalInput << std::endl;
        // Box<Number> errorBoxExternalInput = externalInput.affineTransformation(flow.block(0,0,dim-1,dim-1), vector_t<Number>(flow.block(0,dim-1,dim-1,1)));
        Box<Number> errorBoxExternalInput = externalInput.linearTransformation(
                flow.getFlowMatrix().block(0, 0, dim - 1, dim - 1));
        // std::cout << "Errorbox first linear transformation: " << convert<Number,double>(matrix_t<Number>(flow.block(0,0,dim-1,dim-1))) << " and b: " <<
        // convert<Number,double>(vector_t<Number>(flow.block(0,dim-1,dim-1,1))) << std::endl;
        errorBoxExternalInput.makeSymmetric();
        // errorBoxExternalInput = errorBoxExternalInput.linearTransformation(matrix_t<Number>(matrixBlock.block(0,2*dim,dim-1,dim-1)));
        errorBoxExternalInput = errorBoxExternalInput.linearTransformation(
                matrix_t<Number>(matrixBlock.block(0, 2 * dim, dim - 1, dim - 1)));

        // projection to remove augmented dimension.
        std::vector<std::size_t> projectionDimensions;
        for (std::size_t i = 0; i < errorBoxX0.dimension() - 1; ++i) {
            projectionDimensions.push_back(i);
        }

        errorBoxX0 = errorBoxX0.projectOn(projectionDimensions);

        Box<Number> differenceBox(errorBoxX0.minkowskiDecomposition(errorBoxExternalInput));
        assert(!externalInput.empty() || errorBoxX0 == differenceBox);

        res.emplace_back(errorBoxX0);
        res.emplace_back(errorBoxExternalInput);
        res.emplace_back(differenceBox);

        return res;
    }

/**
 * based on the Hausdorff distance, constructs the box (also a polytope) that is used for bloating the initial
 * approximation
 */
/*
template <typename Number, representation_name Representation>
State<Number> computePolytope( unsigned int _dim, Number _radius ) {
	State_t<Number> res;
	matrix_t<Number> mat = matrix_t<Number>::Zero( 2 * _dim, _dim );
	vector_t<Number> vec( 2 * _dim, 1 );
	int i = 0;
	for ( unsigned z = 0; z < _dim; ++z ) {
		vec( i ) = _radius;
		vec( i + 1 ) = _radius;

		mat( i, z ) = 1;
		mat( i + 1, z ) = -1;

		i = i + 2;
	}
	switch(Representation) {
		case representation_name::box: {
			res.setSet( Box<Number>( mat, vec ));
			break;
		}
		case representation_name::polytope_h: {
			res.setSet( HPolytope<Number>( mat, vec ));
			break;
		}
		case representation_name::polytope_v: {
			res.setSet( VPolytope<Number>( mat, vec ));
			break;
		}
		case representation_name::support_function: {
			res.setSet( SupportFunction<Number>( mat, vec ));
			break;
		}
		case representation_name::zonotope: {
			res.setSet(Converter<Number>::toZonotope(Box<Number>( mat, vec )));
			break;
		}
		default: {
			res.setSet( Box<Number>( mat, vec ));
			break;
		}
	}
	return res;
}
*/
}  // namespace hypro
