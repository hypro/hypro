#pragma once
#include "TrafoParameters.h"
#include "../../representations/GeometricObject.h"
#include "../../util/Plotter.h"
#include <carl/util/SFINAE.h>

namespace hypro {
namespace reachability {

template<typename Number, typename Representation, carl::DisableIf< std::is_same<Representation, SupportFunction<Number> > > = carl::dummy>
Representation applyLinearTransformation( const Representation& _in, const TrafoParameters<Number>& parameters ) {
	//std::cout << __func__ << " in: " << _in << std::endl << "matrix: " << parameters.matrix() << std::endl << "vector " << std::endl << parameters.vector() << std::endl;
	return _in.affineTransformation(parameters.matrix(), parameters.vector());
}

template<typename Number, typename Representation, carl::EnableIf< std::is_same<Representation, SupportFunction<Number> > > = carl::dummy>
Representation applyLinearTransformation( const Representation& _in, const TrafoParameters<Number>& parameters) {
	return _in.affineTransformation(parameters.matrix(), parameters.vector());
}

template<typename Number, typename Representation, carl::DisableIf< std::is_same<Representation, SupportFunction<Number> > > = carl::dummy>
void applyReduction( Representation& ) {
}

template<typename Number, typename Representation, carl::EnableIf< std::is_same<Representation, SupportFunction<Number> > > = carl::dummy>
void applyReduction( Representation& _in) {
	_in.forceLinTransReduction();
}

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

template<typename Representation>
void printFlowpipe( const std::vector<Representation>& _flowpipe ) {
	for ( const auto& segment : _flowpipe ) {
		std::cout << segment << ", " << std::endl;
	}
}

template<typename Representation>
void printFlowpipeReduced( const std::vector<Representation>& _flowpipe ) {
	std::cout << *_flowpipe.begin() << ", " << std::endl;
	std::cout << "(...)" << std::endl;
	std::cout << *_flowpipe.back() << std::endl;
}

template <typename Number>
Number hausdorffError( const Number& delta, const matrix_t<Number>& matrix, const Number& _supremum ) {
	Number result;
	// calculate matrix infinity norm
	Number norm = inftyNorm(matrix);

	// Number tmp = delta * t;
	Number tmp = delta * norm;

	double tmpExp = std::exp(carl::toDouble(tmp));
	result = carl::rationalize<Number>(tmpExp);

	//tmp.exp( result );
	result = result - 1 - tmp;
	result *= _supremum;
	return result;
}

template<typename Number, typename Representation>
std::vector<Box<Number>> errorBoxes( const Number& delta, const matrix_t<Number>& flow, const Representation& initialSet, const matrix_t<Number>& trafoMatrix, const Box<Number>& ) {
	std::vector<Box<Number>> res;

	unsigned dim = flow.cols();
	matrix_t<Number> matrixBlock = matrix_t<Number>::Zero(3*dim, 3*dim);
	matrixBlock.block(0,0,dim,dim) = abs(flow);
	matrixBlock.block(0,dim,dim,dim) = matrix_t<Number>::Identity(dim,dim);
	matrixBlock.block(dim,2*dim,dim,dim) = matrix_t<Number>::Identity(dim,dim);
	matrixBlock = delta*matrixBlock;
	matrix_t<double> convertedBlock = convert<Number,double>(matrixBlock);
	//std::cout << "MatrixBlock: " << std::endl << convertedBlock << std::endl;
	convertedBlock = convertedBlock.exp();
	//std::cout << "exp(MatrixBlock): " << std::endl << convertedBlock << std::endl;
	matrixBlock = convert<double,Number>(convertedBlock);

	// TODO: Introduce better variable naming!
	matrix_t<Number> tmpMatrix = flow*(matrix_t<Number>::Identity(dim,dim) - trafoMatrix);
	//std::cout << "Flow: " << flow << std::endl << "trafoMatrix: " << trafoMatrix << std::endl;
	//std::cout << __func__ << " TmpMtrix: " << std::endl << tmpMatrix << std::endl;
	//assert(tmpMatrix.row(dim-1).nonZeros() == 0);
	Representation transformedInitialSet = applyLinearTransformation(initialSet, TrafoParameters<Number>(matrix_t<Number>(tmpMatrix.block(0,0,dim-1,dim-1)), vector_t<Number>(tmpMatrix.block(0,dim-1,dim-1,1))));
	auto b1 = Converter<Number>::toBox(transformedInitialSet);
	if(b1.empty()) { // indicates that the initial set is empty.
	    //std::cout << "B1.empty()!" << std::endl;
		return res;
	}

	// augment b1 by a dimension for the constant parts.
	vector_t<Number> augmentedUpperLimit = vector_t<Number>::Ones(b1.max().dimension()+1);
	//std::cout << "Matrix: " << std::endl << augmentedUpperLimit << std::endl << " vector " << b1.max().rawCoordinates() << std::endl;
	augmentedUpperLimit.block(0,0,dim-1,1) = b1.max().rawCoordinates();
	vector_t<Number> augmentedLowerLimit = vector_t<Number>::Ones(b1.min().dimension()+1);
	augmentedLowerLimit.block(0,0,dim-1,1) = b1.min().rawCoordinates();
	b1 = Box<Number>(std::make_pair(Point<Number>(augmentedLowerLimit), Point<Number>(augmentedUpperLimit)));

	b1 = b1.makeSymmetric();
	assert(b1.isSymmetric());
	b1 = b1.linearTransformation(matrixBlock.block(0,dim,dim,dim));
	//std::cout << "B1: " << std::endl << b1 << std::endl;

	matrix_t<Number> fullTransformationMatrix = (flow*flow*trafoMatrix);
	//assert(fullTransformationMatrix.row(dim-1).nonZeros() == 0);
	matrix_t<Number> tmpTrafo = fullTransformationMatrix.block(0,0,dim-1,dim-1);
	vector_t<Number> tmpTrans = fullTransformationMatrix.block(0,dim-1,dim-1,1);
	// the last row of this matrix should be zero in any case, such that we can decompose the linear transformation.
	//std::cout << "TmpTrafo Matrix: " << std::endl << convert<Number,double>(tmpTrafo) << std::endl;
	//std::cout << "TmpTrafo Vector: " << std::endl << convert<Number,double>(tmpTrans) << std::endl;
	Representation tmp = applyLinearTransformation(initialSet, TrafoParameters<Number>(tmpTrafo, tmpTrans));
	//Box<Number> b2 = Box<Number>(tmp.matrix(), tmp.vector());
	auto b2 = Converter<Number>::toBox(tmp);
	if(b2.empty()) { // indicates that the initial set is empty.
	    //std::cout << "B2.empty()!" << std::endl;
		return res;
	}

	augmentedUpperLimit.block(0,0,dim-1,1) = b2.max().rawCoordinates();
	augmentedLowerLimit.block(0,0,dim-1,1) = b2.min().rawCoordinates();
	b2 = Box<Number>(std::make_pair(Point<Number>(augmentedLowerLimit), Point<Number>(augmentedUpperLimit)));

	b2 = b2.makeSymmetric();
	assert(b2.isSymmetric());
	b2 = b2.linearTransformation(matrixBlock.block(0,2*dim,dim,dim));
	//std::cout << "B2: " << std::endl << b2 << std::endl;

	Box<Number> errorBoxX0 = b1.minkowskiSum(b2);

	/*
	// std::cout << "External Input: " << externalInput << std::endl;
	Box<Number> errorBoxExternalInput = externalInput.affineTransformation(flow.block(0,0,dim-1,dim-1), vector_t<Number>(flow.block(0,dim-1,dim-1,1)));
	//std::cout << "Errorbox first linear transformation: " << convert<Number,double>(matrix_t<Number>(flow.block(0,0,dim-1,dim-1))) << " and b: " << convert<Number,double>(vector_t<Number>(flow.block(0,dim-1,dim-1,1))) << std::endl;
	errorBoxExternalInput.makeSymmetric();
	errorBoxExternalInput = errorBoxExternalInput.linearTransformation(matrix_t<Number>(matrixBlock.block(0,2*dim,dim-1,dim-1)));

	Box<Number> differenceBox(errorBoxX0.minkowskiDecomposition(errorBoxExternalInput));
	assert(!externalInput.empty() || errorBoxX0 == differenceBox);
	*/


	// projection to remove augmented dimension.
	std::vector<unsigned> projectionDimensions;
	for(unsigned i = 0; i < errorBoxX0.dimension()-1; ++i){
		projectionDimensions.push_back(i);
	}

	res.emplace_back(errorBoxX0.project(projectionDimensions));
	//res.emplace_back(errorBoxExternalInput.project(projectionDimensions));
	//res.emplace_back(differenceBox.project(projectionDimensions));

	return res;
}

/**
 * based on the Hausdorff distance, constructs the box (also a polytope) that is used for bloating the initial
 * approximation
 */
template <typename Number, typename Representation, carl::DisableIf< std::is_same<Representation, Zonotope<Number> > > = carl::dummy>
Representation computePolytope( unsigned int _dim, Number _radius ) {
	matrix_t<Number> mat = hypro::matrix_t<Number>::Zero( 2 * _dim, _dim );
	vector_t<Number> vec( 2 * _dim, 1 );
	int i = 0;
	for ( unsigned z = 0; z < _dim; ++z ) {
		vec( i ) = _radius;
		vec( i + 1 ) = _radius;

		mat( i, z ) = 1;
		mat( i + 1, z ) = -1;

		i = i + 2;
	}
	return Representation(mat,vec);
}

template <typename Number, typename Representation, carl::EnableIf< std::is_same<Representation, Zonotope<Number> > > = carl::dummy>
Representation computePolytope( unsigned int _dim, Number _radius ) {
	matrix_t<Number> mat = hypro::matrix_t<Number>::Zero( 2 * _dim, _dim );
	vector_t<Number> vec( 2 * _dim, 1 );
	int i = 0;
	for ( unsigned z = 0; z < _dim; ++z ) {
		vec( i ) = _radius;
		vec( i + 1 ) = _radius;

		mat( i, z ) = 1;
		mat( i + 1, z ) = -1;

		i = i + 2;
	}
	return Converter<Number>::toZonotope(Box<Number>( mat, vec ));
}

} // namespace reachability
} // namespace hypro
