#pragma once
#include "../IHandler.h"

namespace hypro {
class discreteTimeEvolutionHandler : public ITimeEvolutionHandler {
  public:
	discreteTimeEvolutionHandler() = default;

	void handle() { /*no op*/
	}
	const char* handlerName() { return "discreteTimeEvolutionHandler"; }
	bool getMarkedForDelete() { return true; };
	void setMarkedForDelete( bool ){ /*no op*/ };
};
}  // namespace hypro