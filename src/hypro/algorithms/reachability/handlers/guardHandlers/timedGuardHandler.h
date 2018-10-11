#pragma once
#include "../IHandler.h"
#include "ltiGuardHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class timedGuardHandler : public ltiGuardHandler<Representation,Number> {
	public:
		timedGuardHandler() = delete;
		timedGuardHandler(std::shared_ptr<State_t<Number>> state, size_t index, Transition<Number>* transition) : ltiGuardHandler<Representation,Number>(state,index,transition){
			// 0.1 because standard before timed of same dimension
			if(SettingsProvider<Number>::getInstance().decomposeAutomaton()){
				this->mSortIndex = 0.1+SettingsProvider<Number>::getInstance().getSubspaceDecomposition().at(this->mIndex).size();
			}
			else{
				this->mSortIndex = 0;
			}
		}
		
		void handle();
		const char* handlerName() {return "timedGuardHandler";}
		// 1+ because standard before timed of same dimension
		virtual double getSortIndex() override {return this->mSortIndex;}
		virtual void setSortIndex(double sortIndex) override {this->mSortIndex = sortIndex;}

	};
} // hypro