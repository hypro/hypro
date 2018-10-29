#pragma once
#include "../IHandler.h"
#include "ltiGuardHandler.h"

namespace hypro
{
    template<class Representation,typename Number>
	class discreteGuardHandler : public ltiGuardHandler<Representation,Number> {
	protected:
		bool mComputed = false;
	public:
		discreteGuardHandler() = delete;
		discreteGuardHandler(std::shared_ptr<State_t<Number>> state, size_t index, hypro::Transition<Number>* transition) : ltiGuardHandler<Representation,Number>(state,index,transition){
			this->mSortIndex = 0;
		}
		
		void handle();
		void reinitialize();
		const char* handlerName() {return "discreteGuardHandler";}
		virtual double getSortIndex() override {return this->mSortIndex;}		
		virtual void setSortIndex(double sortIndex) override {this->mSortIndex = sortIndex;}
	};
} // hypro

#include "discreteGuardHandler.tpp"
