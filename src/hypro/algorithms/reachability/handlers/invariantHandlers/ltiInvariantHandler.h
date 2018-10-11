#pragma once
#include "../IHandler.h"

namespace hypro
{
    template<class Representation, typename Number>
	class ltiInvariantHandler : public IInvariantHandler {
	protected:
		CONTAINMENT mContainment = CONTAINMENT::NO;
		State_t<Number>*  mState; 
		size_t mIndex;
		bool mMarkedForDelete = false;

	public:
		ltiInvariantHandler() = delete;
		ltiInvariantHandler(State_t<Number>* state, size_t index){
			mState = state;
			mIndex = index;
		}
		
		void handle();
		const char* handlerName() {return "ltiInvariantHandler";}
		// return containment status
		virtual CONTAINMENT getContainment() override {return mContainment;}
		virtual bool getMarkedForDelete() override {return mMarkedForDelete;}
		virtual void setMarkedForDelete(bool toDelete) override { mMarkedForDelete = toDelete;}

	};
} // hypro
