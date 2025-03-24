#include "hypro/representations/GeometricObjectBase.h"
#include "hypro/neuralnets/reachability/ReachNNMethod.h"
#include "hypro/neuralnets/network/layers/AffineMapping/AffineLayer.h"
#include "hypro/neuralnets/network/layers/ReLU/ReLULayer.h"
#include "hypro/neuralnets/network/layers/LeakyReLU/LeakyReLULayer.h"
#include "hypro/neuralnets/network/layers/StepFunction/StepFunctionLayer.h"
#include "hypro/neuralnets/network/layers/HardTanh/HardTanhLayer.h"
#include "hypro/neuralnets/network/layers/HardSigmoid/HardSigmoidLayer.h"

#include <iostream>
#include <z3++.h>
#include <vector>

typedef mpq_class Number;

//Backpropagation Affine
void affine(hypro::matrix_t<Number> W, hypro::vector_t<Number> b, hypro::Starset<Number> input, hypro::Starset<Number> output){
    std::cout << "\n\n================ Affine Layer ================\n";
	hypro::vector_t<Number> point( 2 );
	point << 0, 0;
    
    hypro::AffineLayer<Number> affineLayer(b.rows(),0,b,W);

    std::cout << "Results of backpropagation through an affine layer \n";
	hypro::vector_t<Number> p1 = affineLayer.traceSourceBack( hypro::Point<Number>( point ), 0, input ).rawCoordinates();
	std::cout << "Only providing the input star set for the affine layer:\n"
              <<  p1 
              << "\nCorresponding element of the input:\n"
              << W * p1 + b
              << "\n";
	std::cout << "Providing the input star set and output star set of the layer:\n" 
              << affineLayer.traceSourceBack( hypro::Point<Number>( point ), 0, input, output ) << std::endl;
}

void ReLU(hypro::Starset<Number> input){
    std::cout << "\n\n================ ReLU Layer ================\n";
    //Calculate stars
	hypro::ReLULayer<Number> layer(0, 0);
    std::vector<hypro::Starset<Number>> exactStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::EXACT);
    std::vector<hypro::Starset<Number>> approxStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::OVERAPPRX);
    
    //Points in exact
    hypro::vector_t<Number> inId(2);
    inId << 1,1;
    hypro::vector_t<Number> inZero(2);
    inZero << 1,0;

    //Point not in exact
    hypro::vector_t<Number> notIn(2);
    notIn << 1,2;

    hypro::Point<Number> p;

    //Backpropagation
    std::cout << "The following backpropagation attempts should work returning a value resulting in the input\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass:\n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    
    p = layer.traceSourceBack(hypro::Point<Number>(inZero),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inZero),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    
    //expected output: ()
    std::cout << "The following backpropagation attempts should not work returning the empty point \"()\" (notIn)"<< "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,exactStars[0]) << "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,approxStars[0]) << std::endl;
}

void LeakyReLU(hypro::Starset<Number> input, Number slope = Number(1)/Number(100)){
    std::cout << "\n\n================ LeakyReLU Layer ================\n";
    //Calculate stars
	hypro::LeakyReLULayer<Number> layer(0, 0, slope);
    std::vector<hypro::Starset<Number>> exactStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::EXACT);
    std::vector<hypro::Starset<Number>> approxStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::OVERAPPRX);
    
    //Points in exact
    hypro::vector_t<Number> inId(2);
    inId << 1,1;
    hypro::vector_t<Number> inZero(2);
    inZero << 1, -(Number(1)/Number(100));

    //Point not in exact
    hypro::vector_t<Number> notIn(2);
    notIn << 1,-1;

    hypro::Point<Number> p;

    //Backpropagation
    std::cout << "The following backpropagation attempts should work returning a value resulting in the input\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    
    p = layer.traceSourceBack(hypro::Point<Number>(inZero),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inZero),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << layer.forwardPass(p.rawCoordinates(),1) << "\n";
    
    //expected output: ()
    std::cout << "The following backpropagation attempts should not work returning the empty point \"()\" (notIn)"<< "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,exactStars[0]) << "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,approxStars[0]) << std::endl;
}

hypro::Point<Number> UnitStepForwardPass(hypro::Point<Number> p, int dim, float val, float min, float max){
    p[dim] = (p[dim] < val) ? min : max;
    return p;
}

void UnitStep(hypro::Starset<Number> input, float val = 0, float min = -1, float max = 1){
    std::cout << "\n\n================ UnitStep Layer ================\n";
    //Calculate LeakyReLU
	hypro::StepFunctionLayer<Number> layer(0, 0, val, min, max);
    std::vector<hypro::Starset<Number>> exactStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::EXACT);
    
    //Points in exact ReLU of stepReLU(1,exactStars)
    hypro::vector_t<Number> inId(2);
    inId << 1,1;
    hypro::vector_t<Number> inZero(2);
    inZero << 1,-1;

    //Point not in exact ReLU of stepReLU(1,exactStars) [elements of approxStepReLU(0,approxStars)]
    hypro::vector_t<Number> notIn(2);
    notIn << 1,-5;

    hypro::Point<Number> p;

    //Backpropagation
    std::cout << "The following backpropagation attempts should work returning a value resulting in the input\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1 ,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: " << UnitStepForwardPass(p,1, val, min, max) << "\n";
      
    p = layer.traceSourceBack(hypro::Point<Number>(inZero),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: " << UnitStepForwardPass(p,1, val, min, max) << "\n";
    
    //expected: ()
    std::cout << "The following backpropagation attempt should not work returning the empty point \"()\" (notIn)"<< "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,exactStars[0]) << std::endl;
}

hypro::Point<Number> HardTahnForwardPass(hypro::Point<Number> inputVec, int i, float min, float max){
    if ( inputVec[i] < min ) {
			inputVec[i] = min;
		} else if ( inputVec[i] > max ) {
			inputVec[i] = max;
		} else {
			// Identity
		}
    return inputVec;
}

void HardTanh(hypro::Starset<Number> input, float min = -1, float max = 1){
    std::cout << "\n\n================ HardTanh Layer ================\n";
    //Calculate stars
	hypro::HardTanhLayer<Number> layer(0, 0, min, max);
    std::vector<hypro::Starset<Number>> exactStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::EXACT);
    std::vector<hypro::Starset<Number>> approxStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::OVERAPPRX);

    //Points in exact
    hypro::vector_t<Number> inId(2);
    inId << 0,0;
    hypro::vector_t<Number> pMax(2);
    pMax << 0.5,max;
    hypro::vector_t<Number> pMin(2);
    pMin << 0.5,min;

    //Point not in exact
    hypro::vector_t<Number> notIn(2);
    notIn << -.8,0;

    hypro::Point<Number> p;

    //Backpropagation
    std::cout << "The following backpropagation attempts should work returning a value resulting in the input\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << HardTahnForwardPass(p,1,min,max) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << HardTahnForwardPass(p,1,min,max) << "\n";
    
    p = layer.traceSourceBack(hypro::Point<Number>(pMax),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << HardTahnForwardPass(p,1,min,max) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(pMax),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << HardTahnForwardPass(p,1,min,max) << "\n";

    p = layer.traceSourceBack(hypro::Point<Number>(pMin),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << HardTahnForwardPass(p,1,min,max) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(pMin),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << HardTahnForwardPass(p,1,min,max) << "\n";
    
    //expected output: ()
    std::cout << "The following backpropagation attempts should not work returning the empty point \"()\" (notIn)"<< "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,exactStars[0]) << "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,approxStars[0]) << std::endl;
}

hypro::Point<Number> HardSigmoidForwardPass(hypro::Point<Number> inputVec, int i, float min, float max){
    if ( inputVec[i] <= min ) {
			inputVec[i] = 0;
		} else if ( inputVec[i] >= max ) {
			inputVec[i] = 1;
		} else {
			inputVec[i] = (inputVec[i]/(max - min)) + (min / (min - max));
		}
    return inputVec;
}

void HardSigmoid(hypro::Starset<Number> input, float min = -2, float max = 2){
    std::cout << "\n\n================ HardSigmoid Layer ================\n";
    //Calculate stars   
	hypro::HardSigmoidLayer<Number> layer(0, 0, min, max);
    std::vector<hypro::Starset<Number>> exactStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::EXACT);
    std::vector<hypro::Starset<Number>> approxStars = layer.forwardPass(input, 0 , hypro::NN_REACH_METHOD::OVERAPPRX);

    // std::cout<<"exact:\n";
    // for (hypro::Starset<Number> star : exactStars){
    //     std::cout << "\n" << star.vertices() << "\n";
    //     std::vector<hypro::Starset<Number>> out = layer.forwardPass(star, 1 , hypro::NN_REACH_METHOD::EXACT);
    //     for (hypro::Starset<Number> s : out){
    //         std::cout << s.vertices() << "\n";
    //     }
    // }     
    // std::cout<< "approx:\n";
    // std::cout<< approxStars[0].vertices()<< "\n";
    // std::cout<< layer.forwardPass(approxStars[0], 1 , hypro::NN_REACH_METHOD::OVERAPPRX)[0].vertices()<< "\n";

    //Points in exact
    hypro::vector_t<Number> inId(2);
    inId << 0.6,0.6;
    hypro::vector_t<Number> pMax(2);
    pMax << 1,1;
    hypro::vector_t<Number> pMin(2);
    pMin << 1,0;

    //Point not in exact
    hypro::vector_t<Number> notIn(2);
    notIn << .2,.2;

    hypro::Point<Number> p;

    //Backpropagation
    std::cout << "The following backpropagation attempts should work returning a value resulting in the input\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << HardSigmoidForwardPass(p,1,min,max) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(inId),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << HardSigmoidForwardPass(p,1,min,max) << "\n";
    
    p = layer.traceSourceBack(hypro::Point<Number>(pMax),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << HardSigmoidForwardPass(p,1,min,max) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(pMax),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << HardSigmoidForwardPass(p,1,min,max) << "\n";

    p = layer.traceSourceBack(hypro::Point<Number>(pMin),1,exactStars[0]);
    std::cout << "Backpropagated in exact:" << p << " - forwardpass: \n" << HardSigmoidForwardPass(p,1,min,max) << "\n";
    p = layer.traceSourceBack(hypro::Point<Number>(pMin),1,approxStars[0]);
    std::cout << "Backpropagated in approx:" << p << " - forwardpass: \n" << HardSigmoidForwardPass(p,1,min,max) << "\n";
    
    //expected output: ()
    std::cout << "The following backpropagation attempts should not work returning the empty point \"()\" (notIn)"<< "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,exactStars[0]) << "\n";
    std::cout << layer.traceSourceBack(hypro::Point<Number>(notIn),1,approxStars[0]) << std::endl;
}

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

    affine(W, b, input, output);
    ReLU(output);
    LeakyReLU(output);
    UnitStep(output);
    HardTanh(output);
    HardSigmoid(output);

	return 0;
}