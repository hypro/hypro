//
// Created by stefan on 01.07.16.
//

#include "Logger.h"

#ifdef HYPRO_LOGGING

namespace hypro {

	LogInitializer::LogInitializer() {
		config.configure();
	}

	log4cplus::Logger& LogInitializer::get() {
		if (instance == nullptr) {
			instance = new LogInitializer();
		}
		return instance->getLogger();
	}

	log4cplus::Logger& LogInitializer::getLogger() {
		// Handle log levels
		#ifdef HYPRO_LOG_TRACE
			this->logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
		#elif defined(HYPRO_LOG_INFO)
			this->logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
		#elif defined(HYPRO_LOG_DEBUG)
			this->logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
		#elif defined(HYPRO_LOG_WARN)
			this->logger.setLogLevel(log4cplus::WARN_LOG_LEVEL);
		#elif defined(HYPRO_LOG_FATAL)
			this->logger.setLogLevel(log4cplus::FATAL_LOG_LEVEL);
		#else
		#endif
		return this->logger;
	}

	LogInitializer* LogInitializer::instance = nullptr;
	::log4cplus::Initializer LogInitializer::initializer;
	::log4cplus::BasicConfigurator LogInitializer::config;

	log4cplus::Logger logger = LogInitializer::get();

} // namespace hypro
#endif
