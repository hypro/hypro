#pragma once
#include "../IHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class ltiBadStateHandler : public IBadStateHandler {
	protected:
		bool mIntersects = false;
		State_t<Number>*  mState; 
		bool mNoBadStates = false;
		size_t mIndex;
		bool mMarkedForDelete = false;

	public:
		ltiBadStateHandler() = delete;
		ltiBadStateHandler(State_t<Number>* state, size_t index){
			mState = state;
			mIndex = index;
		}
		
		void handle();
		const char* handlerName() {return "ltiBadStateHandler";}
		// return intersection status
		virtual bool intersectsBadState() override {return mIntersects;}

		virtual bool getMarkedForDelete() override {return mMarkedForDelete;}
		virtual void setMarkedForDelete(bool toDelete) override { mMarkedForDelete = toDelete;}

	};
} // hypro
