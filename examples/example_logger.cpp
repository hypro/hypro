
#include "util/logging/Logger.h"

int main()
{
	FATAL("Test");
	TRACE("Trace Test");
	DEBUG("Debug Test");
	COUT("Test" << std::endl);
}
