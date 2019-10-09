/**
 * TPolyTimeEvolutionHandler.h
 *
 * @author Phillip Tse
 * @date 4.10.2019
 */

#pragma once

#include "../IHandler.h"

namespace hypro {

	template<typename State>
	class TPolyTimeEvolutionHandler : public ltiTimeEvolutionHandler<State> {

		using Number = typename State::NumberType;

	  protected:

	  	//Inherits members from ltiTimeEvolutionHandler

	  public:

		TPolyTimeEvolutionHandler() = delete;
		TPolyTimeEvolutionHandler(State* state, size_t index, tNumber timeStep, matrix_t<Number> trafo, vector_t<Number> translation)
			: ltiTimeEvolutionHandler<State>(state, index, timeStep, trafo, translation)
		{}
		~TPolyTimeEvolutionHandler(){}

		//The set integration approximation from [Sankaranarayanan,2008]
		void handle();
		const char* handlerName() { return "TPolyTimeEvolutionHandler"; }
		bool getMarkedForDelete() { return false; };
		void setMarkedForDelete(bool ) { /*no op*/ };

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

} // namespace hypro

#include "TPolyTimeEvolutionHandler.tpp"