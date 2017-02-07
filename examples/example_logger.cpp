
#include "util/logging/Logger.h"

int main()
{
	FATAL("hypro.examples","Test");
	TRACE("hypro.examples","Trace Test");
	DEBUG("hypro.examples","Debug Test");
	COUT("Test" << std::endl);
}
