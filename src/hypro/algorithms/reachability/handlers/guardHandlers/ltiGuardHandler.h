#pragma once
#include "../IHandler.h"
#include "../../../../datastructures/reachability/SettingsProvider.h"

namespace hypro
{
    template<class Representation,typename Number>
	class ltiGuardHandler : public IGuardHandler<Number> {
	protected:
		bool mSatisfies = false;
		bool mMarkedForDelete =false;
		std::shared_ptr<State_t<Number>> mGuardSatisfyingState; 
		hypro::Transition<Number>* mTransition;

		size_t mIndex;
		double mSortIndex;
	public:
		ltiGuardHandler() = delete;
		ltiGuardHandler(std::shared_ptr<State_t<Number>> state, size_t index, hypro::Transition<Number>* transition){
			mGuardSatisfyingState = state;
			mIndex = index;
			mTransition = transition;
			if(SettingsProvider<Number>::getInstance().decomposeAutomaton()){
				mSortIndex = SettingsProvider<Number>::getInstance().getSubspaceDecomposition().at(mIndex).size();
			}
			else{
				mSortIndex = 0;
			}
		}
		
		void handle();
		const char* handlerName() {return "ltiGuardHandler";}
		// return containment status
		virtual bool satisfiesGuard() override {return mSatisfies;}
		virtual std::shared_ptr<State_t<Number>> getState() override{return mGuardSatisfyingState;}		
		virtual void setState(std::shared_ptr<State_t<Number>> ptr) override{mGuardSatisfyingState = ptr;}
		void reinitialize();
		virtual double getSortIndex() override {return mSortIndex;}
		virtual void setSortIndex(double sortIndex) override { mSortIndex = sortIndex;}

		virtual bool getMarkedForDelete() override {return mMarkedForDelete;}
		virtual void setMarkedForDelete(bool toDelete) override { mMarkedForDelete = toDelete;}
	};
} // hypro