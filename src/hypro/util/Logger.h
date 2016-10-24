#pragma once

#ifdef LOGGING_HYPRO

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


#endif
