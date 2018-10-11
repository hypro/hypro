#pragma once
#include "../IHandler.h"

namespace hypro
{
    class discreteTimeEvolutionHandler : public ITimeEvolutionHandler{
	public:
		discreteTimeEvolutionHandler() = default;

		void handle() {/*no op*/}
		const char* handlerName() {return "discreteTimeEvolutionHandler";}
	};
} // hypro