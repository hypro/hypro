#pragma once

#include "flags.h"
#include <iostream>

#define DEBUG(expr)
#define TRACE(expr)
#define INFO(expr)
#define WARN(expr)
#define FATAL(expr)

#define COUT(expr) std::cout << expr
#define CERR(expr) std::cerr << expr

#ifdef HYPRO_LOGGING

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/initializer.h>

namespace hypro {

	class LogInitializer {
	public:
		static log4cplus::Logger& get();

	protected:
		LogInitializer();

	private:
		log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main"));
		static LogInitializer* instance;
		log4cplus::Logger& getLogger ();
		static ::log4cplus::Initializer initializer;
		static ::log4cplus::BasicConfigurator config;
	};

	extern log4cplus::Logger logger;
} // namespace hypro

//#include "macros.h"

#undef DEBUG
#undef TRACE
#undef INFO
#undef WARN
#undef FATAL
#define TRACE(expr) LOG4CPLUS_TRACE(hypro::logger, "[" << __func__ << "] " << expr)
#define DEBUG(expr) LOG4CPLUS_DEBUG(hypro::logger, "[" << __func__ << " " << __FILE__ << ":" << __LINE__ << "] " << expr)
#define INFO(expr) LOG4CPLUS_INFO(hypro::logger, expr)
#define WARN(expr) LOG4CPLUS_WARN(hypro::logger, expr)
#define FATAL(expr) LOG4CPLUS_FATAL(hypro::logger, expr)

#endif
