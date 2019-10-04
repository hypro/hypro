/**
 * tpolyFirstSegmentHandler.h
 *
 * @author Phillip Tse
 * @date 18.9.2019
 */

#pragma once

#include "../IHandler.h"

namespace hypro {

	template<typename State> //TODO: inherit from IFSHandler or from ltiFSHandler?
	class TPolyFirstSegmentHandler : public ltiFirstSegmentHandler<State> {

		using Number = typename State::NumberType;

	  protected:

	  	//Inherits the members from ltiFirstSegmentHandler

	  public:

	  	TPolyFirstSegmentHandler() = delete;
		TPolyFirstSegmentHandler(State* state, size_t index, tNumber timeStep)
			: ltiFirstSegmentHandler<State>(state, index, timeStep) {}
		~TPolyFirstSegmentHandler(){}

		void handle();
		const char* handlerName() {return "TPolyFirstSegmentHandler";}
	
	  private:

		//Computes the gradient of a multivariate but linear function linearFct
	    vector_t<Number> gradientOfLinearFct(const vector_t<Number>& linearFct);

	    //Computes the lie derivative given a direction and an affine vector field (aka the flow)
	    //NOTE: Usually the lie derivative also works with non linear fcts, but since we cannot parse nonlinear functions yet,
	    //we will only use a simple selfwritten derivation function for linear multivariate functions
	    //DETAIL: The input vector dir is interpreted as a function, for example if dir = (3 2 -1) then dir is interpreted as 3x + 2y - z, 
	    //since no constants are allowed.
	    //The gradient of 3x + 2y - z is therefore the vector (3 2 -1), which is the result that will be returned.
	    vector_t<Number> lieDerivative(const vector_t<Number>& dir);

	};

} //namespace hypro

#include "TPolyFirstSegmentHandler.tpp"