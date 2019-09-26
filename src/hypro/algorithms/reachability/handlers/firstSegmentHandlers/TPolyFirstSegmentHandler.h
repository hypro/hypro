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

	  	State* mState;
		size_t mIndex;
		tNumber mTimeStep;

	  public:

	  	TPolyFirstSegmentHandler() = delete;
		TPolyFirstSegmentHandler(State* state, size_t index, tNumber timeStep){
			mState = state;
			mIndex = index;
			mTimeStep = timeStep;
		}
		~TPolyFirstSegmentHandler(){}

		void handle();
		const char* handlerName() {return "TPolyFirstSegmentHandler";}
		
		//Computes the gradient of a multivariate but linear function linearFct
	    vector_t<Number> gradientOfLinearFct(const vector_t<Number>& linearFct);

	    //Computes the lie derivative given a direction and an affine vector field (aka the flow)
	    //NOTE: Usually the lie derivative also works with non linear fcts, but since we cannot parse nonlinear functions yet,
	    //we will only use a simple selfwritten derivation function for linear multivariate functions
	    vector_t<Number> lieDerivative(const vector_t<Number>& dir);

	    const flowVariant<typename State::NumberType>& getTransformation() const { return flowVariant<typename State::NumberType>(); }

	};

} //namespace hypro

#include "TPolyFirstSegmentHandler.tpp"