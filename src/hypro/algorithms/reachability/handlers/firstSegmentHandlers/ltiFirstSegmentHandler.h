#pragma once
#include "../IHandler.h"

namespace hypro
{
    template<class Representation, typename Number>
	class ltiFirstSegmentHandler : public IFirstSegmentHandler<Number> {
	protected:
		State_t<Number>*  mState; // A state containing the first segment for each subspace
		matrix_t<Number> mTrafo;
		vector_t<Number> mTranslation;

		size_t mIndex;
		tNumber mTimeStep;

	public:
		ltiFirstSegmentHandler() = delete;
		ltiFirstSegmentHandler(State_t<Number>* state, size_t index, tNumber timeStep){
			mState = state;
			mIndex = index;
			mTimeStep = timeStep;
		}

		void handle();
		const char* handlerName() {return "ltiFirstSegmentHandler";}
		matrix_t<Number> computeTrafoMatrix(const Location<Number>* _loc) const;

		matrix_t<Number> getTrafo(){return mTrafo;}
		vector_t<Number> getTranslation(){return mTranslation;}
	};

} // hypro

#include "ltiFirstSegmentHandler.tpp"
