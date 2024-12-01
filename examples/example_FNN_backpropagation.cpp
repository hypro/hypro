#include "hypro/representations/GeometricObjectBase.h"
// #include "hypro/neuralnets/network/activation_functions/ReLU/ReLU.h"
#include "hypro/neuralnets/reachability/ReachNNMethod.h"
#include "hypro/neuralnets/network/layers/AffineMapping/AffineLayer.h"
#include "hypro/neuralnets/network/layers/ReLU/ReLULayer.h"

#include <iostream>
#include <z3++.h>
#include <vector>

typedef mpq_class Number;

int main() {
	// Affine mapping
	hypro::matrix_t<Number> W( 2, 2 );
	W << 2, 1, 1, 3;
	hypro::vector_t<Number> b( 2 );
	b << 1, -1;
	
	// Starset
	hypro::matrix_t<Number> V( 2, 2 );
	V << 1, 0, 0, 1;
	hypro::matrix_t<Number> C( 4, 2 );
	C << 1, 0, -1, 0, 0, 1, 0, -1;
	hypro::vector_t<Number> c( 2 );
	c << 0, 0;
	hypro::vector_t<Number> d( 4 );
	d << 1, 1, 1, 1;
	hypro::Starset<Number> input( c, C, d, V );

	// Calculated output star
	hypro::Starset<Number> output( W * c + b, C, d, W * V );
	hypro::vector_t<Number> point( 2 );
	point << 0, 0;

    //Backpropagation Affine
	hypro::AffineLayer<Number> affineLayer(b.rows(),0,b,W);

    std::cout << "Results of backpropagation through an affine layer \n";
	hypro::vector_t<Number> p1 = affineLayer.propagateCandidateBack( hypro::Point<Number>( point ), 0, input ).rawCoordinates();
	std::cout << "Only providing the input star set for the affine layer:\n"
              <<  p1 
              << "\nCorresponding element of the input:\n"
              << W * p1 + b
              << "\n";
	std::cout << "Providing the input star set and output star set of the layer:\n" 
              << affineLayer.propagateCandidateBack( hypro::Point<Number>( point ), 0, input, output ) << std::endl;

    //Calculate ReLU
	hypro::ReLULayer<Number> ReLULayer(0, 0);
    std::vector<hypro::Starset<Number>> exactReLUStars = ReLULayer.forwardPass(output, 0 , hypro::NN_REACH_METHOD::EXACT);
    std::vector<hypro::Starset<Number>> approxReLUStars = ReLULayer.forwardPass(output, 0 , hypro::NN_REACH_METHOD::OVERAPPRX);
    
    //Points in exact ReLU of stepReLU(1,exactReLUStars)
    hypro::vector_t<Number> inId(2);
    inId << 1,1;
    hypro::vector_t<Number> inZero(2);
    inZero << 1,0;

    //Point not in exact ReLU of stepReLU(1,exactReLUStars) [elements of approxStepReLU(0,approxReLUStars)]
    hypro::vector_t<Number> notIn(2);
    notIn << 1,2;

    //Backpropagation ReLU
    std::cout << "Results of backpropagation through an ReLU node \n";
    std::cout << "The following backpropagation attempts should work returning a value resulting in the input"<< std::endl;
    std::cout << "inId:" << ReLULayer.propagateCandidateBack(hypro::Point<Number>(inId),1,exactReLUStars[0]) << std::endl;
    std::cout << "inId:" << ReLULayer.propagateCandidateBack(hypro::Point<Number>(inId),1,approxReLUStars[0]) << std::endl;
    
    std::cout << "inZero:" << ReLULayer.propagateCandidateBack(hypro::Point<Number>(inZero),1,exactReLUStars[0]) << std::endl;
    std::cout << "inZero:" << ReLULayer.propagateCandidateBack(hypro::Point<Number>(inZero),1,approxReLUStars[0]) << std::endl;
    
    //expected: 0
    std::cout << "The following backpropagation attempts should not work returning the empty point \"()\" (notIn)"<< std::endl;
    std::cout << ReLULayer.propagateCandidateBack(hypro::Point<Number>(notIn),1,exactReLUStars[0]) << std::endl;
    std::cout << ReLULayer.propagateCandidateBack(hypro::Point<Number>(notIn),1,approxReLUStars[0]) << std::endl;

	return 0;
}