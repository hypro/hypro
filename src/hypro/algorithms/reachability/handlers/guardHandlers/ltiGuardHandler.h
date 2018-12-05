#pragma once
#include "../IHandler.h"
#include "../../../../datastructures/reachability/SettingsProvider.h"

namespace hypro
{
    template<typename State>
	class ltiGuardHandler : public IGuardHandler<State> {
		using Number = typename State::NumberType;
	protected:
		bool mSatisfies = false;
		bool mMarkedForDelete =false;
		std::shared_ptr<State> mGuardSatisfyingState;
		Transition<Number>* mTransition;

		size_t mIndex;
		double mSortIndex;
	public:
		ltiGuardHandler() = delete;
		ltiGuardHandler(std::shared_ptr<State> state, size_t index, Transition<Number>* transition){
			mGuardSatisfyingState = state;
			mIndex = index;
			mTransition = transition;
			if(SettingsProvider<State>::getInstance().decomposeAutomaton()){
				mSortIndex = SettingsProvider<State>::getInstance().getSubspaceDecomposition().at(mIndex).size();
			}
			else{
				mSortIndex = 0;
			}
		}

		void handle();
		const char* handlerName() {return "ltiGuardHandler";}
		// return containment status
		virtual bool satisfiesGuard() override {return mSatisfies;}
		virtual std::shared_ptr<State> getState() override{return mGuardSatisfyingState;}
		virtual void setState(std::shared_ptr<State> ptr) override{mGuardSatisfyingState = ptr;}
		void reinitialize();
		virtual double getSortIndex() override {return mSortIndex;}
		virtual void setSortIndex(double sortIndex) override { mSortIndex = sortIndex;}

		virtual bool getMarkedForDelete() override {return mMarkedForDelete;}
		virtual void setMarkedForDelete(bool toDelete) override { mMarkedForDelete = toDelete;}
	};
} // hypro

#include "ltiGuardHandler.tpp"