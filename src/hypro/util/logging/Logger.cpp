#ifdef HYPRO_LOGGING

#include "Logger.h"

namespace hypro {

	int initializeLogging() {
		carl::logging::logger().configure("logfile", "hypro.log");
		carl::logging::logger().filter("logfile")
	    ("hypro", carl::logging::LogLevel::LVL_TRACE)
		("hypro.representations", carl::logging::LogLevel::LVL_DEBUG)
		;

	  	carl::logging::logger().configure("stdout", std::cout);
		carl::logging::logger().filter("stdout")
	    ("hypro", carl::logging::LogLevel::LVL_TRACE)
		("hypro.representations", carl::logging::LogLevel::LVL_DEBUG)
		;

	  	carl::logging::logger().resetFormatter();
	  	return 0;
	}

} // namespace hypro

#endif
