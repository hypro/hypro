#pragma once
#include "../IHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class ltiResetHandler : public IResetHandler {	
	protected:	
		State_t<Number>*  mState; // A state containing the first segment for each subspace
		matrix_t<Number> mTrafo;
		vector_t<Number> mTranslation;

		size_t mIndex;
	public:

		ltiResetHandler() = delete;
		ltiResetHandler(State_t<Number>* state, size_t index, matrix_t<Number> trafo,vector_t<Number> translation){
			mState = state;
			mIndex = index;
			mTrafo = trafo;
			mTranslation = translation;
		}

		void handle();
		const char* handlerName() {return "ltiResetHandler";}

	};
} // hypro

#include "ltiResetHandler.tpp"
